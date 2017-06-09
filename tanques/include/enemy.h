#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <game.h>
#include <queue>


class enemy
{
   public:
        enemy();
        enemy(float,float);
        int getX();
        int getY();
        void setX(int);
        void setY(int);
        virtual void atacar()=0;
        virtual void printImage()=0;

    protected:
        int weigh;
        int heigh;
        int speed;
        int state;
        ALLEGRO_BITMAP *ene_image;
        float score;
        float x;
        float y;
        float vida;
};

class tank_basic:public enemy
{
    public:

        tank_basic(float x,float y);
        virtual void atacar();
        virtual void printImage();

};
class tank_hard:public enemy
{

    public:
        tank_hard(float x,float y);
        virtual void atacar();
        virtual void printImage();

    private:


};
#endif // ENEMY_H
