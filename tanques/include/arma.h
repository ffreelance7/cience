#ifndef ARMA_H
#define ARMA_H

#include <iostream>
#include <vector>
#include <game.h>
using namespace std;

class arma
{
     public:
        arma(float,float);
        ~arma();
        float getX();
        float getY();
        void setX(float);
        void setY(float);
        bool printImage(vector<float>);
        bool collision(float,float,float);
        int speed;
        float x1;
        float y1;
    private:
        ALLEGRO_BITMAP * image;
//        ALLEGRO_ANIMATION * ex;
        float x;
        float y;
        int weigh;
        int heigh;
};

#endif // ARMA_H
