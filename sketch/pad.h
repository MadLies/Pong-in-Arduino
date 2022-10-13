#pragma once
#include <Arduino.h>
#include "rect.h"
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

class Pad : public Rect
{
  public:
  Pad(byte posX,byte posY, byte width, byte height);   //constructor
  void setPos(byte posX, byte posY);
};