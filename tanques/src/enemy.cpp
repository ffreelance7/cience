#include "enemy.h"

enemy::enemy()
{
    //ctor
}
enemy::enemy(float x,float y)
{
    //ctor
}
tank_basic::tank_basic(float x,float y){

    this->x=x;
    this->y=y;
    speed=3;
    vida=100;
    score=0;
    state=false;
    ene_image=al_load_bitmap("tank22.png");
    heigh=al_get_bitmap_height(ene_image);
    weigh=al_get_bitmap_width(ene_image);

}
tank_hard::tank_hard(float x,float y){

    this->x=x;
    this->y=y;
    speed=3;
    vida=100;
    score=0;
    state=false;
    ene_image=al_load_bitmap("tank22.png");
    heigh=al_get_bitmap_height(ene_image);
    weigh=al_get_bitmap_width(ene_image);

}
void tank_basic:: atacar(){


}
void tank_basic:: printImage(){
     al_draw_rotated_bitmap(ene_image,0,0,this->x,this->y,0,NULL);

}
void tank_hard:: atacar(){


}
void tank_hard:: printImage(){
     al_draw_rotated_bitmap(ene_image,0,0,this->x,this->y,0,NULL);

}

