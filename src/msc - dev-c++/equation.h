#ifndef EQUATION_H_INCLUDED
#define EQUATION_H_INCLUDED
#include <string>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
/*
 *
 *  Fuck me, to je tezky jak hovado!!!
 *  Nejak to budu muset poresit, ale nemam poneti jak.
 *  Obecna rovnice je:
 *
 *  ax^2 + bxy + cy^2 + dx + ey + f = 0
 *
 *
 *  y se pak rovná:
 *
 *  y1,2 = ( - ( bx + e ) +- odmocnina(( bx + e )^2 - 4c( ax^2 + dx + f )) ) / ( 2c )
 *
 */
using namespace std;
namespace eq{

//TODO: GetNumbers ze stringu souboru, GetType
enum type {POINT, LINE, CIRCxLE, ELLYPSE, PARA, HYPER};

class Eq
{
    private:
        void GetNumbers(); //ziska cisla ze stringu
        void GetType(); //zjisti typ kuzelosecky, mozna neni potreba
        string FromFile; //uchovava string, co jsem nacetl ze souboru
        double a,b,c,d,e,f; //jednotlive cleny
        Uint32 color;
        type typ;
    public:
        type eq_type; //typ rovnice
        Eq(){}; //prazdny konstruktor
        void create_Eq(double a1, double b1, double c1, double d1, double e1, double f1, Uint32 colour);
        Eq(string str_par); //konstruktor kde predavam string co jsem ziskal ze souboru
        ~Eq() {}; //k nicemu
        int return_ifExistsX(int x); //vraci O kdyz pro dane x neni y, 1 kdyz jenom Y a 2 kdyz oba
        int return_ifExistsY(int y); //----------------------y-||---x---------------X-------------
        double return_y1(int x); //vraci Y1 pro zadane x
        double return_x1(int y); //vraci X1 pro zadane y
        double return_y2(int x); //vraci Y2 pro zadane x
        double return_x2(int y); //vraci X2 pro zadane y
        Uint32 eq_color() {return color;}
        bool draw(SDL_Surface* screen);
};
}
#endif // EQUATION_H_INCLUDED
