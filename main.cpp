#include <Arduino.h>
#include <IntervalTimer.h>
#include <Motors.h>
#include <Launcher.h>

void checkOff(void);

//Global variables
#define LIMIT_FRONT         15
#define LIMIT_BACK          14
#define LIMIT_LEFT          13

int turnTime = 1000;        //calibrate this based on how long to turn 90deg
int reloadTime = 5000;   //pauses for 7s to reload the balls
int shootTime = 5000;    //waits a second between shooting each ball
int ballCounter = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  pinMode(LIMIT_FRONT, INPUT_PULLUP);
  pinMode(LIMIT_BACK, INPUT_PULLUP);
  pinMode(LIMIT_LEFT, INPUT_PULLUP);

  //Start of the check-off process
  checkOff();

  //Eventually start the good code after check-off
}

void loop() {
  // put your main code here, to run repeatedly:
  //With check-off hard coding nothing should be on loop
}

void checkOff() {
  //Moves the robot to the back of the arena and then turns right
  /*motors.moveBackward();
  Serial.println("Moving backward; hit front limit switch to move left");
  while(!digitalRead(LIMIT_BACK)){
    //wait
  }
  //Moves the robot across the arena to the armoury, pausing when it hits the switch for 7 seconds
  motors.moveLeft(); 
  Serial.println("Moving left; hit left limit switch to pause");
  while(!digitalRead(LIMIT_LEFT)){
    //wait
  }
  motors.stopMoving();
  delay(reloadTime); 
  //Turns the robot to move away from the switch to leave the armoury
  motors.moveRight();
  Serial.println("Moving right a little, then moving forward again until front limit switch hit");
  delay(turnTime);
  //Move to the front wall and start shooting at Casterly Rock
  motors.moveForward();
  while(!digitalRead(LIMIT_FRONT)){
    //wait
  }
  motors.moveLeft();
  while(!digitalRead(LIMIT_LEFT)){
    //wait
  }
  motors.stopMoving();
  */
  //Starts launching the balls at Casterly Rock
  launcher.startFlywheel();
  while (ballCounter < 12){
    launcher.incrementBall();
    Serial.println("Shoot ball");
    delay(ballCounter + shootTime);
    ballCounter++;
  }
  launcher.stopFlywheel();
}