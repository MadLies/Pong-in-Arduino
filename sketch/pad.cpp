#include "pad.h"


Pad::Pad(byte x,byte y, byte w, byte h):Rect(x,y,w,h){}

void Pad::setPos(byte x, byte y) {
  x = max(min(x,SCREEN_WIDTH - this->width), 0);
  y = max(min(y,SCREEN_HEIGHT - this->height), 0);
  this->posX = x;
  this->posY = y;
}