#pragma once
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH        128 // OLED display width, in pixels
#define SCREEN_HEIGHT        64
extern Adafruit_SSD1306 display;

class Rect
{
  public:
  typedef enum {RIGHT = 1,LEFT = 2, TOP = 3, BOTTOM = 4} side;
  byte posX,posY;
  int height,width;
  Rect(byte posX,byte posY, int height, int width);   //constructor
  void move(int delta_x,int delta_y);
  side collision(Rect &other);
  void draw();
};