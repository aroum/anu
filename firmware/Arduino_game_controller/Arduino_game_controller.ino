
#include <Gamepad.h>


int leftXcenter = 500;
int leftYcenter = 500;
double multiplierLX = 0.254;
double multiplierLY = 0.254;

Gamepad gp;

void setup() {
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(4,  INPUT_PULLUP); //A
  pinMode(3,  INPUT_PULLUP); //X
  pinMode(2,  INPUT_PULLUP); //B  
  
  calibrate();
}

void loop() {
  int lx, ly;
  lx = analogRead(A1);
  ly = analogRead(A2);
  //we need to convert a 0-1000 to -127 - 127
  lx = floor((lx - leftXcenter) * multiplierLX);
  ly = floor((ly - leftYcenter) * multiplierLY);
  if(lx > 127) lx = 127;
  if(ly > 127) ly = 127;
  gp.setLeftXaxis(lx);
  gp.setLeftYaxis(ly);
  
  int UPLEFT, UPRIGHT, UP, DOWN, LEFT, RIGHT, RIGHTBUTTON, LEFTBUTTON, X, Y, A, B;
  A = digitalRead(4);
  X = digitalRead(3);
  B = digitalRead(2);
  

  if(A == LOW)
    gp.setButtonState(10, true);
  else
    gp.setButtonState(10, false);  
  if(X == LOW)
    gp.setButtonState(8, true);
  else
    gp.setButtonState(8, false);
  if(B == LOW)
    gp.setButtonState(11, true);
  else
    gp.setButtonState(11, false);       

  delay(20);
}

void calibrate()
{
  int lx, ly;
  int i = 0;
  while(i < 13)
  {
    lx = analogRead(A3);
    ly = analogRead(A2);
    bool validLX = lx > (leftXcenter - 100) && lx < (leftXcenter + 100);
    bool validLY = ly > (leftYcenter - 100) && ly < (leftYcenter + 100);
    if(validLX && validLY)
      {
      i++;
      //nothing to do here!
    }
    else i = 0;
    delay(20);
  }
  leftXcenter = lx;
  leftYcenter = ly;
  multiplierLX = (double)127 / (double)lx;
  multiplierLY = (double)127 / (double)ly;
}
