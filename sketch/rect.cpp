#include "rect.h"
#include <ArduinoTrace.h>
Rect::Rect(byte x,byte y, int w, int h): posX(x),posY(y),height(h),width(w) {};

void Rect::draw() {
  display.fillRect(posX,posY,width,height,WHITE);
}

void Rect::move(int delta_x, int delta_y) {
  int new_x = posX + delta_x;
  int new_y = posY + delta_y;
  posX = new_x % SCREEN_WIDTH;
  posY = new_y % SCREEN_HEIGHT;
}

Rect::side Rect::collision(Rect& other){
    int dx=(this->posX+this->width/2)-(other.posX+other.width/2);
    int dy=(this->posY+this->height/2)-(other.posY+other.height/2);
    int mean_width=(this->width+other.width)/2;
    int mean_height=(this->height+other.height)/2;
    int crossWidth=mean_width*dy;
    int crossHeight=mean_height*dx;
    Rect::side collision=NULL;
    //
    if(abs(dx)<=mean_width && abs(dy)<=mean_height){
        if(crossWidth>crossHeight){
            collision=(crossWidth>(-crossHeight))? BOTTOM: LEFT;
        }else{
            collision=(crossWidth>-(crossHeight))? RIGHT : TOP;
        }
    }
    return(collision);
}
