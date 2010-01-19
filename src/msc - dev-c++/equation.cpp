#include <cmath>
#include <iostream>
#include <string>
#include "equation.h"
#include "defines.h"

using namespace std;

namespace eq{

void Eq::create_Eq(double a1, double b1, double c1, double d1, double e1, double f1, Uint32 colour){
    a=a1; b=b1; c=c1; d=d1; e=e1; f=f1; color=colour;
    GetType();
};

Eq::Eq(string str_par){
    FromFile=str_par; //konstruktor pro naplneni promennych
    GetNumbers();
    GetType();
};

void Eq::GetNumbers(){
};

void Eq::GetType(){
    if (a==0||b==0) typ=PARA;
};

// y1,2 = ( - ( bx + e ) +- odmocnina(( bx + e )^2 - 4c( ax^2 + dx + f )) ) / ( 2c )

int Eq::return_ifExistsX(int x){
//    long double dis=(((b*x)+e)*((b*x)+e))-4*c*((a*x*a*x) + d*x + f); //doufam ze tohle pojede
//    //fuck, jaktoze je diskriminant vzdycky roven 1???x
//    cout << "DIS: " << dis << endl;
    double prvni, druhy, dis;
    prvni = pow(((b*x)+e),2);
    druhy = (a*pow(double (x), double (2))) + (d*x) + f;
    dis = prvni - (4*c*druhy);
    if (dis<0) return 0;
    else if (dis==0) return 1;
    else return 2;
    // vyřešit elegantneji - dis<0? return 0 : dis=0? return 1 : return 2
};

int Eq::return_ifExistsY(int y){
    double prvni, druhy, dis;
    prvni = pow(((b*y)+d),2);
    druhy = (c*pow(double (y), double (2))) + (e*y) + f;
    dis = prvni - (4*a*druhy);
    if (dis<0) return 0;
    else if (dis==0) return 1;
    else return 2;
}

double Eq::return_y1(int x){
    double prvni, druhy, dis;
    prvni = pow(((b*x)+e),2);
    druhy = (a*pow(double (x),double (2))) + (d*x) + f;
    dis = prvni - (4*c*druhy);
    long double y = (( -((b*x) + e)) + pow(dis,1.0/2))/(2*c);
	return y;
};

double Eq::return_x1(int y){
    double prvni, druhy, dis;
    prvni = pow(((b*y)+d),2);
    druhy = (c*pow(double (y),double (2))) + (e*y) + f;
    dis = prvni - (4*a*druhy);
    long double x = (( - ((b*y) + d)) + pow(dis,1.0/2))/(2*a);
    return x;
};

double Eq::return_y2(int x){
    double prvni, druhy, dis;
    prvni = pow(((b*x)+e),2);
    druhy = (a*pow(double (x), double (2))) + (d*x) + f;
    dis = prvni - (4*c*druhy);
    long double y = (( -((b*x) + e)) - pow(dis,1.0/2))/(2*c);
	return y;
};

double Eq::return_x2(int y){
    double prvni, druhy, dis;
    prvni = pow(((b*y)+d),2);
    druhy = (c*pow(double (y), double (2))) + (e*y) + f;
    dis = prvni - (4*a*druhy);
    long double x = (( - ((b*y) + d)) - pow(dis,1.0/2))/(2*a);
    return x;
};

bool Eq::draw(SDL_Surface* screen){
 bool correct=false;
 if (c!=0){
    for (int X = (0-(RES_X/2)); X<=(RES_X/2); X++){
        if (return_ifExistsX(X)==1){
            //tady vypisu jeden bod pomoci return_y1
            int pozice = return_y1(X);
            pixelColor(screen,(X+(RES_X/2)),(pozice+(RES_Y/2)),eq_color());
            correct=true;
        } else if (return_ifExistsX(X)==2) {
            //tady vypisu dva bod pomoci return_y1 return_y2
            int pozice1 = return_y1(X);
            int pozice2 = return_y2(X);
            pixelColor(screen,(X+(RES_X/2)),(pozice1+(RES_Y/2)),eq_color());
            pixelColor(screen,(X+(RES_X/2)),(pozice2+(RES_Y/2)),eq_color());
            correct=true;
        };
    };
 };
 if (a!=0){
    for (int Y = (0-(RES_Y/2)); Y<=(RES_Y/2); Y++){
        if (return_ifExistsY(Y)==1){
            //tady vypisu jeden bod pomoci return_y1
            int pozice = return_x1(Y);
            pixelColor(screen,(pozice+(RES_X/2)),(Y+(RES_Y/2)),eq_color());
            correct=true;
        } else if (return_ifExistsY(Y)==2) {
            //tady vypisu dva bod pomoci return_y1 return_y2
            int pozice1 = return_x1(Y);
            int pozice2 = return_x2(Y);
            pixelColor(screen,(pozice1+(RES_X/2)),(Y+(RES_Y/2)),eq_color());
            pixelColor(screen,(pozice2+(RES_X/2)),(Y+(RES_Y/2)),eq_color());
            correct=true;
        };
    };
 };
 return correct;
};

};
