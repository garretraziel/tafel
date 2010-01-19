/*
 *  Tafel - program pro vykreslovani kuzelosecek
 *  mb Garret Raziel, Boloomka interactive
 *
 *  Rocnikova prace 2008/2009
 *
 *
 */

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <windows.h>
#include "equation.h"
#include "defines.h"
#include "version.h"

using namespace std;
using namespace eq;

struct numeros{
        int an;
        int bn;
        int cn;
        int dn;
        int en;
        int fn;
        Uint32 col;
};

int count_eqs;

void draw_axis(SDL_Surface *screen); //nakresli osy
int handle_arguments(int argc, char** argv, int &arg, int &count, numeros* metas);
void create_meta_conics(int count,numeros* metas);

int main ( int argc, char** argv )
{
    //TODO: automake, apod.

    if (argc <= 1){
        //Nejdou argumenty, vypise pouziti
        cout << "Tafel\n" << AutoVersion::FULLVERSION_STRING << " 2009 Jan Sedlák, Boloomka interactive\n";
        cout << "distributed under the terms of the GNU General Public Licence.\n";
        cout << "---------------------------------\n";
        cout << "USAGE:\n"
            << "   " << argv[0] << " [options] [-fn <filename>] [options]\n"
            << " options:\n"
            << "   -a: number with x^2 (-a or -c requied!)\n"
            << "   -b: number with xy (propably not used)\n"
            << "   -c: number with y^2 (-a or -c requied!)\n"
            << "   -d: number with x\n"
            << "   -e: number with y\n"
            << "   -f: standalone number\n"
            << " default of all numbers is zero\n"
            << "   -ec: color of this equation (default red) - red, white, green, blue, black, yellow, purple\n"
            << "   -n: for inputing next eqation\n"
           // << "   -fn: input numbers from file <filename>\n"
            << "   -v: show version\n"
            << "   -h: helpfile\n";
        return 1;
    }

	//vypsani verze programu
	for (int i=0; i<argc; i++)
		if (strcmp(argv[i],"-v")==0) {
			cout << AutoVersion::FULLVERSION_STRING << endl;
			return 0;
		}

	//vypsani helpfile
	for (int i=0; i<argc; i++)
		if (strcmp(argv[i],"-h")==0) {
			//cout << help; //TODO: helpfile
			return 0;
		}

	//spocitam pocet kuzelosecek
    count_eqs=1;
    for (int par = 0; par<argc; par++)
        if (strcmp(argv[par],"-n")==0) count_eqs++;

	numeros array_eqs[count_eqs];
	create_meta_conics(count_eqs,array_eqs);

	int count=1;
	int count_i=0;

    handle_arguments(argc,argv,count,count_i,array_eqs);

	Eq meta_conics[count_eqs];

	for (int i=0;i<count_eqs;i++) {
		meta_conics[i].create_Eq(array_eqs[i].an,array_eqs[i].bn,array_eqs[i].cn,array_eqs[i].dn,array_eqs[i].en,array_eqs[i].fn,array_eqs[i].col);
	}

    //string colours;
    //if (argc>=8) colours = argv[7];
    //else colours = "red";
    //Uint32 colours_i;
    //if (colours=="white") colours_i=WHITE;
    //else if (colours=="blue") colours_i=BLUE;
    //else if (colours=="yellow") colours_i=YELLOW;
    //else if (colours=="black") colours_i=BLACK;
    //else if (colours=="green") colours_i=GREEN;
    //else if (colours=="purple") colours_i=PURPLE;
    //else colours_i=RED;

    //Eq meta_conic(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi(argv[5]),atoi(argv[6]),colours_i);

    //TODO: rozliseni souboru a hodnot

    /*
     *  Odtud uz probiha pouze vykreslovani
     *
     *
     *
     *
     */

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(RES_X, RES_Y, COLOR,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 800x600 video: %s\n", SDL_GetError());
        return 1;
    }

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE


        // ZDE BUDE VYKRESLENI KUZELOSECKY
        // gfxPrimitives mozna neni potreba, pouziji putpixel, obecna rovnice kuzelosecek to poresi
        draw_axis(screen); //nakresli osy
//        if (!draw_eq(screen,meta_conic)){
//            cout << "Chyba!";
//            done=true;
//            break;
//        }
        for (int i=0;i<count_eqs;i++) {
			if (!meta_conics[i].draw(screen)) cerr << "Vykresleni kuzelosecky "
				<< i+1 << " se nepodarilo\n";
		}

        //TODO: stred, osy, asymptoty
        //TODO: bod X[1,0], meneni meritka

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
};

//TODO: popis kuzelosecek, vypis vlastnosti, vypisovani chyb na osu

void draw_axis(SDL_Surface *screen){
    hlineColor(screen,0,RES_X,RES_Y/2.0,WHITE);
    vlineColor(screen,RES_X/2,0,RES_Y,WHITE);
    characterColor(screen,RES_X/2.0-12, RES_Y/2+7,'0',WHITE);
    characterColor(screen,RES_X/2.0-12, 10, 'y',WHITE);
    characterColor(screen,RES_X-12,RES_Y/2.0+7, 'x',WHITE);
    //pixelColor(screen,RES_X/2,RES_Y/2,0x0000ffff);
//    hlineColor(screen,RES_X/2+10,RES_Y/2-5,RES_Y+5,WHITE);
//    vlineColor(screen,RES_X/2-5,RES_X/2+5,RES_Y/2+10,WHITE);
//    characterColor(screen,(RES_X/2+10)-3,RES_Y/2+10,'1',WHITE);
//    characterColor(screen,(RES_X/2-15),(RES_Y/2-10)-3,'1',WHITE);
};

int handle_arguments(int argc, char** argv, int &arg, int &count, numeros* metas) {
if (arg>=argc) {return 0;}
	else {
		if (strcmp(argv[arg],"-a")==0) {
			//a nastav a kontroluj dal
			metas[count].an=atoi(argv[arg+1]);
			arg=arg+2;
			handle_arguments(argc,argv,arg,count,metas);
		} else if (strcmp(argv[arg],"-b")==0) {
			//b nastav a kontroluj dal
			metas[count].bn=atoi(argv[arg+1]);
			arg=arg+2;
			handle_arguments(argc,argv,arg,count,metas);
		} else if (strcmp(argv[arg],"-c")==0) {
			//c nastav a kontroluj dal
			metas[count].cn=atoi(argv[arg+1]);
			arg=arg+2;
			handle_arguments(argc,argv,arg,count,metas);
		} else if (strcmp(argv[arg],"-d")==0) {
			//d nastav a kontroluj dal
			metas[count].dn=atoi(argv[arg+1]);
			arg=arg+2;
			handle_arguments(argc,argv,arg,count,metas);
		} else if (strcmp(argv[arg],"-e")==0) {
			//e nastav a kontroluj dal
			metas[count].en=atoi(argv[arg+1]);
			arg=arg+2;
			handle_arguments(argc,argv,arg,count,metas);
		} else if (strcmp(argv[arg],"-f")==0) {
			//f nastav a kotrnoluj dal
			metas[count].fn=atoi(argv[arg+1]);
			arg=arg+2;
			handle_arguments(argc,argv,arg,count,metas);
		} else if (strcmp(argv[arg],"-ec")==0) {
			//nastav barvu a kontroluj dal
			if (strcmp(argv[arg+1],"white")==0) metas[count].col=WHITE;
			else if (strcmp(argv[arg+1],"blue")==0) metas[count].col=BLUE;
			else if (strcmp(argv[arg+1],"yellow")==0) metas[count].col=YELLOW;
			else if (strcmp(argv[arg+1],"black")==0) metas[count].col=BLACK;
			else if (strcmp(argv[arg+1],"green")==0) metas[count].col=GREEN;
			else if (strcmp(argv[arg+1],"purple")==0) metas[count].col=PURPLE;
			else metas[count].col=RED;
			arg=arg+2;
            handle_arguments(argc,argv,arg,count,metas);
		} else if (strcmp(argv[arg],"-n")==0) {
			//tohle bude peklo poresit, dalsi kuzelosecka
			count++;
			arg++;
			handle_arguments(argc,argv,arg,count,metas);
		} else if (strcmp(argv[arg],"-fn")==0) {
			//tohle bude taky peklo poresit, vstup ze souboru
			//TODO: vstup ze souboru
			ifstream fin;
			fin.open(argv[arg+1]);
			if (!fin.good()) {
			    cerr << "Bad file input!\n";
			    return 1;
			}
            char arguments[7];
            //fin.get(arguments[]
		} else handle_arguments(argc,argv,++arg,count,metas);
	}
	return 0;
};

void create_meta_conics(int count,numeros* metas) {
	for (int i=0;i<count;i++) {
		metas[i].an=0;
		metas[i].bn=0;
		metas[i].cn=0;
		metas[i].dn=0;
		metas[i].en=0;
		metas[i].fn=0;
		metas[i].col=RED;
	}
}
