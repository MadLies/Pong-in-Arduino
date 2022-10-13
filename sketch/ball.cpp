#include "ball.h"
#include "score.h"
Ball::Ball(byte x,byte y):Rect(x,y,3,3){
  velX = 0;
  velY = 0;
}

void Ball::move()
{
  Rect::move(velX,velY);
}

void Ball::collide(Rect& other)
{
  //Serial.println("Colliding");
  Rect::side collision_side = Rect::collision(other);
  switch(collision_side) {
    case Rect::TOP:
      
      velY = -velY;
      break;
    case Rect::BOTTOM:
      
      velY = -velY;
      break;
    case Rect::LEFT:
      
      velX = -velX;
      break;
    case Rect::RIGHT:
      
      velX = -velX;
      break;
    default:
      //Serial.println("Null collision");
      break;
  }
}

int Ball::outOfBounds(){
  if (this->posX >= SCREEN_WIDTH - this->width || this->posX <= 0) {
    
    if (posX >= SCREEN_WIDTH - this->width) {
      this->posX = SCREEN_WIDTH / 4 ;
      return 1;
      //score.increaseA();
     // Serial.println(score.scoreA);
    }
    if (posX <= 0) {
      this->posX = (SCREEN_WIDTH / 4) * 3;
      
      return 2;
      //score.increaseB();
    }
  }
  return 3;
}
