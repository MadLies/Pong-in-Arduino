#pragma once
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH        128 // OLED display width, in pixels
#define SCREEN_HEIGHT        64
extern Adafruit_SSD1306 display;

class Score{
  public:
    int scoreA;
    int scoreB;
    int max_score;
    Score(int A, int B, int max_score);
    void increaseA();
    void increaseB();
    void draw();
};