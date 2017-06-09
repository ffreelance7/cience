#include <iostream>
#include <cstdio>
#include <character.h>
#include <game.h>
#include <enemy.h>
#include <allegro_primitives.h>

using namespace std;
vector<float>point_array;
vector<float>point_array_enemies;
 int cancha[19][19]={{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
                    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
                    {1,0,0,0,0,0,0,1,0,0,0,2,0,0,1,0,0,0,1},
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
                    {1,1,1,1,1,0,0,1,1,1,0,0,1,0,1,0,0,0,1},
                    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
                    {1,0,0,0,0,0,0,1,0,0,0,2,0,0,1,0,0,2,1},
                    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
                    {1,0,0,0,0,0,0,1,0,2,0,0,0,0,1,0,0,0,1},
                    {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
                    {1,1,1,1,1,0,0,1,1,0,1,1,0,0,1,0,1,1,1},
                    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
                    {1,0,0,2,0,0,0,1,0,0,0,2,0,0,1,0,0,0,1},
                    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,2,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}


};
void load_mapa(){
    for(int i=0,y=0;i<19;i++,y++){
          for(int j=0,x=0;j<19;j++,x++){
            if(cancha[j][i]==1){
                   al_draw_filled_rectangle(i*80, j*80, (i+1)*80,(j+1)*80, al_map_rgb(40,40,40));
                    point_array.push_back(i*80);
                    point_array.push_back(j*80);

                    }
             else if(cancha[j][i]==2){
                    point_array_enemies.push_back(i*80);
                    point_array_enemies.push_back(j*80);
                }
            }
        }
}

int main(int argc, char **argv){


    enum DIREC{DOWN=0,RIGHT=1,LEFT=2,UP=3,UP_LEFT=4,UP_RIGHT=5,DOWN_LEFT=6,DOWN_RIGHT=7};
    int screenWidth = 600;
    int screenHeight = 488;
    bool static colison=true;
    // the world size
    int worldWidth = 1520;
    int worldHeight = 1520;


    // the camera's position
    float cameraX = 0;
    float cameraY = 0;

    int MOVE=-1;

    if(!al_init()) {
      fprintf(stderr, "failed to initiñŔ108uj7,i8alize allegro!\n");
      return -1;
    }
    if(!al_init_image_addon()){
      fprintf(stderr, "failed to initialize image!\n");
      return -1;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    if(!al_install_audio()) {
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
    }
    if(!al_init_acodec_addon()){
       fprintf(stderr, "failed to initialize audio codec!\n");
      return -1;
    }

    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font = al_load_ttf_font("ff.otf",30,0 );
    ALLEGRO_TRANSFORM camera;
    display = al_create_display(screenWidth, screenHeight);
    al_set_window_position(display,120,150);
    al_set_window_title(display,"Tanque");

    bool state_control[8]={false,false,false,false,false,false,false,false};
    bool state_bool=false;
    float xmouse,ymouse;
    character player(screenWidth/2,screenHeight/2);
    vector<enemy*>enemigos;
    tank_basic pp(150,150);
    //for(int i=0;i<2;i+=2){
       // tank_basic pp(point_array_enemies[i],point_array_enemies[i+1]);
        //enemigos(tank_basic());
       // tank_basic pp(point_array_enemies[i],point_array_enemies[i+1]);
        //enemigos.push_back(&pp);
    //}


    float xtank,ytank;
    const float UserFPS=30.0;

    float countx=0;
    float county=0;

    al_install_keyboard();
    al_install_mouse();
    ALLEGRO_KEYBOARD_STATE keyState;
    ALLEGRO_MOUSE_STATE mouseState;
    ALLEGRO_BITMAP *mapa;

    mapa=al_load_bitmap("cancha.png");

    ALLEGRO_EVENT_QUEUE *event_queue =al_create_event_queue();
    ALLEGRO_TIMER *timerUser = al_create_timer(1.0/UserFPS);

    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_register_event_source(event_queue,al_get_timer_event_source(timerUser));
    al_register_event_source(event_queue,al_get_mouse_event_source());

    al_start_timer(timerUser);
    load_mapa();

    bool juego=true;
    while(juego){

        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue,&events);
                                                                                                                                                                                                                                                                                                 al_get_keyboard_state(&keyState);
        al_get_mouse_state(&mouseState);

        if(events.type==ALLEGRO_EVENT_KEY_UP){
            switch(events.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    juego=false;
                    break;
               default :
                break;
            }
        }
        cameraX = player.getX() - screenWidth / 2;
        cameraY = player.getY() - screenHeight / 2;

        xtank=player.getX();
        ytank=player.getY();


        if(al_key_down(&keyState,ALLEGRO_KEY_UP) && al_key_down(&keyState,ALLEGRO_KEY_LEFT)){
            if(cameraX ==0 || cameraY==0){
                county-=player.speed;
                countx-=player.speed;
            }else{
                countx=0;

            }
            if(state_control[0]!=true){
                player.setY(player.getY()-player.speed);
                player.setX(player.getX()-player.speed);
                MOVE=UP_LEFT;
            }

        }
        else if(al_key_down(&keyState,ALLEGRO_KEY_UP) &&  al_key_down(&keyState,ALLEGRO_KEY_RIGHT)){
             if(cameraX > worldWidth - screenWidth || cameraY==0){
                county-=player.speed;
                countx+=player.speed;
                }else{
                    countx=0;

                }
                if(state_control[1]!=true){
                    player.setY(player.getY()-player.speed);
                    player.setX(player.getX()+player.speed);
                    MOVE=UP_RIGHT;
                 }
        }
        else if(al_key_down(&keyState,ALLEGRO_KEY_DOWN) &&  al_key_down(&keyState,ALLEGRO_KEY_LEFT)){
            if(cameraY > worldHeight - screenHeight || cameraX==0){
                county+=player.speed;
                countx-=player.speed;
            }else{
                countx=0;

            }
            if(state_control[2]!=true){
                player.setY(player.getY()+player.speed);
                player.setX(player.getX()-player.speed);
                MOVE=DOWN_LEFT;
            }

        }
        else if(al_key_down(&keyState,ALLEGRO_KEY_DOWN) &&  al_key_down(&keyState,ALLEGRO_KEY_RIGHT)){
            if(cameraX > worldWidth - screenWidth || cameraY> worldHeight-screenHeight){
                county+=player.speed;
                countx+=player.speed;
            }else{
                countx=0;

            }
            if(state_control[3]!=true){
                player.setY(player.getY()+player.speed);
                player.setX(player.getX()+player.speed);
                MOVE=DOWN_RIGHT;
            }

        }
        else if(al_key_down(&keyState,ALLEGRO_KEY_DOWN)){
            if(cameraY > worldHeight - screenHeight){
                county+=player.speed;
            }else{
                county=0;
            }
            if(state_control[4]!=true){
                player.setY(player.getY()+player.speed);
                MOVE=DOWN;
            }

        }
        else if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT)){
            if(cameraX > worldWidth - screenWidth){
                countx+=player.speed;
            }else{
                countx=0;
            }
            if(state_control[5]!=true){
                player.setX(player.getX()+player.speed);
                MOVE=RIGHT;
            }

        }
        else if(al_key_down(&keyState,ALLEGRO_KEY_LEFT)){
            if(cameraX > worldWidth - screenWidth){
                countx-=player.speed;
            }else{
                countx=0;

            }
            if(state_control[6]!=true){
                player.setX(player.getX()-player.speed);
                MOVE=LEFT;
            }
        }
        else if(al_key_down(&keyState,ALLEGRO_KEY_UP) ){
            if(cameraY > worldHeight - screenHeight){
                county-=player.speed;
            }else{
                county=0;

            }
            if(state_control[7]!=true){
                player.setY(player.getY()-player.speed);
                MOVE=UP;
            }
        }
        xmouse=mouseState.x+(player.getX()-screenWidth/2);
        ymouse=mouseState.y+(player.getY()-screenHeight/2);

        if(al_mouse_button_down(&mouseState,mouseState.buttons & 1)){

                if(cameraX > worldWidth - screenWidth){
                    xmouse=mouseState.x+(player.getX()-screenWidth/2)-countx;
                }
                if(cameraY > worldHeight-screenHeight){
                    ymouse=mouseState.y+(player.getY()-screenHeight/2)-county;
                }
                if(cameraX < 0){
                    xmouse=mouseState.x;
                }
                if(cameraY< 0){
                    ymouse=mouseState.y;
                }
                player.atacar(xmouse,ymouse);

        }

        if (cameraX < 0){
            cameraX = 0;
        }
        if (cameraY < 0){
            cameraY = 0;
        }
        if (cameraX > worldWidth - screenWidth){
            cameraX = worldWidth - screenWidth;
        }
        if (cameraY > worldHeight - screenHeight){
            cameraY = worldHeight - screenHeight;
        }
       al_identity_transform(&camera);
       al_translate_transform(&camera,-cameraX,-cameraY);

       al_use_transform(&camera);
    if(true){

        for(int i=0,y=0;i<19;i++,y++){
          for(int j=0,x=0;j<19;j++,x++){

            if(cancha[j][i]==1){
                   al_draw_filled_rectangle(i*80, j*80, (i+1)*80,(j+1)*80, al_map_rgb(40,40,40));
                    }
                }

            }
            for(int i=0;i<point_array.size()-2;i+=2){
                colison=player.coliision(point_array[i],point_array[i+1],80);
                if(colison==true){
                    al_draw_textf(font, al_map_rgb(0,0,0),100,80,0,"Collistion");
                    state_bool=true;
                }
            }
            if(state_bool==true){
                switch(MOVE){
                    case 0:
                        state_control[4]=true;
                        break;
                    case 1:
                        state_control[5]=true;
                        break;
                    case 2:
                        state_control[6]=true;
                        break;
                    case 3:
                        state_control[7]=true;
                        break;
                    case 4:
                        state_control[0]=true;
                        break;
                    case 5:
                        state_control[1]=true;
                        break;
                    case 6:
                        state_control[2]=true;
                        break;
                    case 7:
                        state_control[3]=true;
                        break;
                    default:
                        break;

                }
                state_bool=false;
            }else{
                for(int i=0;i<8;i++){
                    state_control[i]=false;
                }

            }

           // pp.printImage();
            player.printImage(mouseState.x+(player.getX()-screenWidth/2),mouseState.y+(player.getY()-screenHeight/2),xtank,ytank,point_array);
            al_flip_display();
            al_clear_to_color(al_map_rgb(255,255,255));
        }
    }
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   al_destroy_timer(timerUser);
    return 0;


}
