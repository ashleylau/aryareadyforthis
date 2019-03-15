#include <Arduino.h>
#include <IntervalTimer.h>
#include <Motors.h>
#include <Launcher.h>

void checkOff(void);
void destroyWall(void);
void towersFirst(void);
void reload(void);
void testUltrasonic(void);
long getDistance(void);
void shutItDown(void);


//Global variables  
#define LIMIT_LEFT          9
#define LIMIT_BACK          10
#define LIMIT_FRONT         11
#define DIST_ECHO           16
#define DIST_TRIG           17


int turnTime = 750;       //calibrate this based on how long to turn 90deg
int reloadTime = 3000;   //pauses for 3s to reload the balls
int shootTime = 1000;    //waits a second between shooting each ball
int ballCounter = 0; 

long duration, inches;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  //while(!Serial);

  pinMode(LIMIT_FRONT, INPUT_PULLUP);
  pinMode(LIMIT_BACK, INPUT_PULLUP);
  pinMode(LIMIT_LEFT, INPUT_PULLUP);
  pinMode(DIST_ECHO, INPUT);
  pinMode(DIST_TRIG, OUTPUT);
  Serial.println("hacked the mainframe");

  //Set servo to correct position
  Serial.println("Initial clear from twitch");
  launcher.shootBall();
  launcher.clearSwitch();

  //Run the check-off Casterly Rock shooting process
  checkOff();
  //Detect which mode we want to use
  //If switched to destroy the wall first
  //If switched to destroying more towers before the wall
  towersFirst();
}

void loop() {
  // put your main code here, to run repeatedly:
  //With check-off hard coding nothing should be on loop
}

void checkOff() {
  //Moves the robot to the back of the arena and then turns right
  motors.moveBackward();
  Serial.println("Moving backward; hit front limit switch to move left");
  while(!digitalRead(LIMIT_BACK)){
    //wait
  }
  reload();
  //Starts launching the balls at Casterly Rock
  launcher.startFlywheel();
  motors.rideFrontWallRight();
  delay(400);
  motors.stopMoving();
  Serial.println("Wait two seconds to shoot balls");
  delay(2000);
  int ballCounter = 0;
  
  while (ballCounter < 1){
    Serial.println("Next ball");
    launcher.shootBall();
    launcher.clearSwitch();
    ballCounter++;
    delay(2000);
  }
}

//Focuses on destroying all of the towers before the wall

void towersFirst(void){
  //Hit King's Landing
  motors.rideFrontWallRight();
  int distance = getDistance();
  while(distance > 43){
    //wait
    distance = getDistance();
  }
  motors.stopMoving();
  //Knock over wall
  launcher.startFlywheel();
  launcher.shootBall();
  launcher.clearSwitch();
  launcher.shootBall();
  launcher.clearSwitch();
  launcher.shootBall();
  launcher.clearSwitch();
  delay(500);
  
  //Hit Dragonstone
  motors.rideFrontWallRight();
  distance = getDistance();
  while(distance > 18){
    //wait
    distance = getDistance();
  }
  motors.stopMoving();
  //Knock over wall
  launcher.shootBall();
  launcher.clearSwitch();
  //Shoot Dragonstone
  launcher.shootBall();
  launcher.clearSwitch();
  launcher.shootBall();
  launcher.clearSwitch();
  launcher.shootBall();
  launcher.clearSwitch();
  launcher.shootBall();
  launcher.clearSwitch();

  delay(500);

  //Move backward and reload
  launcher.stopFlywheel();
  motors.moveBackward();
  while(!digitalRead(LIMIT_BACK)){
    //wait
  }
  reload();

  launcher.startFlywheel();
  motors.rideFrontWallRight();
  delay(375);
  motors.stopMoving();
  //Start arbitrarily firing at dragon??
  int counter = 0;
  //If we add sensor to check for dragon, add that here?
  while (counter < 8){
    //if(millis() > 110000) shutItDown();
    delay(1000);
    launcher.shootBall();
    launcher.clearSwitch();
    counter++;
  }
  launcher.stopFlywheel();
  motors.rideFrontWallRight();
  delay(turnTime);
  motors.moveBackward();
  while(!digitalRead(LIMIT_BACK)){
    //wait
  }
  reload();

  launcher.startFlywheel();
  motors.rideFrontWallRight();
  delay(350);
  motors.stopMoving();
  //Start arbitrarily firing at dragon??
  counter = 0;
  //If we add sensor to check for dragon, add that here?
  while (counter < 8){
    //if(millis() > 110000) shutItDown();
    delay(1000);
    launcher.shootBall();
    launcher.clearSwitch();
    counter++;
  }
  launcher.stopFlywheel();
  motors.rideFrontWallRight();
  delay(turnTime);
  motors.moveBackward();
  while(!digitalRead(LIMIT_BACK)){
    //wait
  }
  reload();

  launcher.startFlywheel();
  //Start arbitrarily firing at dragon??
  counter = 0;
  //If we add sensor to check for dragon, add that here?
  while (counter < 8){
    //if(millis() > 110000) shutItDown();
    delay(1000);
    launcher.shootBall();
    launcher.clearSwitch();
    counter++;
  }
  launcher.stopFlywheel();
  motors.stopMoving();
}


//Moves from back corner behind throne room to armoury to front left corner
void reload(void){
   //Moves the robot across the arena to the armoury, pausing when it hits the switch for 7 seconds
  motors.rideBackWall(); 
  //Serial.println("Moving left; hit left limit switch to pause");
  while(!digitalRead(LIMIT_LEFT)){
    //wait
  }
  motors.stopMoving();
  delay(reloadTime); 
  //Turns the robot to move away from the switch to leave the armoury
  motors.moveRight();
  //Serial.println("Moving right a little, then moving forward again until front limit switch hit");
  delay(turnTime);
  //Move to the front wall and start shooting at Casterly Rock
  motors.moveForward();
  while(!digitalRead(LIMIT_FRONT)){
    //wait
  }
  motors.rideFrontWallLeft();
  while(!digitalRead(LIMIT_LEFT)){
    //wait
  }
  motors.stopMoving();
}

long getDistance(){
    digitalWrite(DIST_TRIG, LOW);
    delay(5);
    digitalWrite(DIST_TRIG, HIGH);
    delay(10);
    digitalWrite(DIST_TRIG, LOW);
    duration = pulseIn(DIST_ECHO, HIGH);
    inches = (duration/2)/74;
    return inches;
}
