#include "score.h"
#include <ArduinoTrace.h>

Score::Score(int a, int b, int m){
  scoreA = a;
  scoreB = b;
  max_score = m;
}

void Score::increaseA() {
  this->scoreA ++;
}

void Score::increaseB() {
  this->scoreB ++;
}
void Score::draw(){
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(SCREEN_WIDTH/2 - 20,3);
  display.print(scoreA);

  display.setCursor(SCREEN_WIDTH/2 + 11,3); //+1 because of dotted line.
  display.print(scoreB);
}