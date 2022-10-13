#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ball class
#include "rect.h"
#include "ball.h"
#include "pad.h"
#include "score.h"


#include "ArduinoTrace.h"

#include <TaskScheduler.h>
Scheduler ts;

#define SCREEN_WIDTH        128 // OLED display width, in pixels
#define SCREEN_HEIGHT        64 // OLED display height, in pixels

#define PAD_HEIGHT 10
#define PAD_WIDTH 2

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET            4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//---- TASKS ----------------------------------------
void oledDisplayCB();
Task tOledDisplay(50,TASK_FOREVER,&oledDisplayCB,&ts);

void moveProcessCB();
Task tMoveProcess(50,TASK_FOREVER,&moveProcessCB,&ts);


//---- Potentiometers ----------
#define CONTROL_A A0
#define CONTROL_B A1

//----------------------------------------------------
Rect upperWall(0,0,SCREEN_WIDTH,1);
Rect lowerWall(0,SCREEN_HEIGHT-1,SCREEN_WIDTH,1);

//--- Pads ------------------------------------------//
Pad pad1(10,(SCREEN_HEIGHT-PAD_HEIGHT)/2,PAD_WIDTH,PAD_HEIGHT);
Pad pad2(SCREEN_WIDTH-10,(SCREEN_HEIGHT-PAD_HEIGHT)/2,PAD_WIDTH,PAD_HEIGHT);
//----- balls objects -------------------------------//
Ball ball1(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
//--------------------------------------------------//

Rect* obstacles[] = {&upperWall, &lowerWall, &pad1, &pad2};
Rect* drawables[] = {&ball1, &upperWall, &lowerWall, &pad1, &pad2};

Score score(0,0,3);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // initialize and clear display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  splash();

  tOledDisplay.enableDelayed();
  tMoveProcess.enableDelayed();
  tMoveProcess.delay(45);

  // ball speed
  ball1.velX = 1;
  ball1.velY = 1;
  display.clearDisplay();
  display.display();

}

//Splash Screen
void splash()
{
  display.clearDisplay(); 

  display.setTextColor(WHITE);
  centerPrint("PONG",0,3);
  centerPrint("Tecnologia Digital",33,1);

  display.fillRect(0,SCREEN_HEIGHT-10,SCREEN_WIDTH,10,WHITE);
  display.setTextColor(BLACK);
  centerPrint("Move paddle to start!",SCREEN_HEIGHT-9,1);

  display.display();

  int controlA = analogRead(CONTROL_A);
  int controlB = analogRead(CONTROL_B);

  while (abs(controlA - analogRead(CONTROL_A) + controlB - analogRead(CONTROL_B)) < 10) {
    // show as long as the total absolute change of 
    // both potmeters is smaler than 5
  }

  //soundStart();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(score.scoreA);
  //Serial.println(score.scoreB);
  //Serial.println(score.max_score);
  if (score.scoreA < score.max_score && score.scoreB < score.max_score) {
    ts.execute();
  }
  else {
    display.clearDisplay(); 
    display.setTextColor(WHITE);
    if (score.scoreA >= score.max_score) {
      centerPrint("A won",SCREEN_HEIGHT/2,3);
    }
    else {
      centerPrint("B won",SCREEN_HEIGHT/2,3);
    }
    display.display();
  }
}

void moveProcessCB()
{
  for (Rect* obs : obstacles) {
    ball1.collide(*obs);
    int point = ball1.outOfBounds();
    if(point==1){
      score.increaseA();
    }
    if(point==2){
      
      score.increaseB();
    }
    //Serial.println(score.scoreA);
  }

  //myBall1.collide(lowerWall);
  //myBall1.collide(upperWall);
  ball1.move();
}


void oledDisplayCB()        //run every 50 ms
{
  //erase graph memory
  display.clearDisplay();

  for (int i=0; i<SCREEN_HEIGHT; i+=4) {
    display.drawFastVLine(SCREEN_WIDTH/2, i, 2, WHITE);
  }

  for (Rect* drawable : drawables) {
    //Serial.println("drawing");
    drawable->draw();
    //DUMP(drawable->posX);
    //DUMP(drawable == &ball1);
  }

  ball1.draw();
  score.draw();
  // pads movement
  int controlA = analogRead(CONTROL_A);
  int controlB = analogRead(CONTROL_B);
  pad1.setPos(10, map(controlA, 0, 1023, 0, SCREEN_HEIGHT - PAD_HEIGHT - 2));
  pad2.setPos(SCREEN_WIDTH -10, map(controlB, 0, 1023, 0, SCREEN_HEIGHT - PAD_HEIGHT - 2));

  display.display();
}


void centerPrint(char *text, int y, int size)
{
  display.setTextSize(size);
  display.setCursor(SCREEN_WIDTH/2 - ((strlen(text))*6*size)/2,y);
  display.print(text);
}
