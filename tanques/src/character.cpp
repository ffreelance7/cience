#include "character.h"

character::character(int x,int y){

    this->x=x;
    this->y=y;
    speed=3;
    vida=100;
    score=0;
    state=false;
    image=al_load_bitmap("tank22.png");
    image_up=al_load_bitmap("tank11.png");
    heigh=al_get_bitmap_height(image);
    weigh=al_get_bitmap_width(image);
}
float character::getX(){
    return this->x;
}
float character::getY(){
    return this->y;

}
void character::setX(float x){
    this->x=x;

}
void character::setY(float y){
    this->y=y;

}
void character::atacar(float xd,float yd){

    arma *ar=new arma(this->x,this->y);
    ar->x1=xd;
    ar->y1=yd;
    bala.push_back(ar);
    state=true;
}
void character::printImage(float xrota,float yrota,float xtan,float ytan,vector<float>cc){

    for(int i=0;i<bala.size();i++){
        bala[i]->setX(bala[i]->getX()+cos(atan2 (bala[i]->y1-bala[i]->getY(),bala[i]->x1-bala[i]->getX()))*bala[i]->speed);
        bala[i]->setY(bala[i]->getY()+sin(atan2 (bala[i]->y1-bala[i]->getY(),bala[i]->x1-bala[i]->getX()))*bala[i]->speed);
        if(bala[i]->printImage(cc)){
           // delete bala[i];
        };
    }

    // al_draw_rotated_bitmap(image,20,35,this->x,this->y,atan2(ytan-this->y,xtan-this->x),NULL);
    al_draw_rotated_bitmap(image,0,0,this->x,this->y,0,NULL);
   al_draw_rotated_bitmap(image_up,20,20,this->x+30,this->y+35,atan2(yrota-this->y,xrota-this->x),NULL);

}
bool character::coliision(float x1,float y1,float weight){

    float left1,right1,top1,bottom1;

    left1=this->x;
    right1=this->x+this->weigh;
    top1=this->y;
    bottom1=this->y+this->heigh;


    float left,right,top,bottom;

    left=x1;
    right=x1+weight;
    top=y1;
    bottom=y1+weight;

    if(right1>=left && left1<=right && top1<=bottom && bottom1>=top){
        return true;
    }else{
        return false;
    }

}

