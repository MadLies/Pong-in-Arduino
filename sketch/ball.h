#pragma once
#include <Arduino.h>
#include "rect.h"
#include "score.h"
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

class Ball : public Rect
{
  public:
  byte velX,velY;
  Ball(byte posX,byte posY);   //constructor
  void move();
  void collide(Rect &other);
  int outOfBounds();
};