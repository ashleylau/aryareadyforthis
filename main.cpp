#include <Arduino.h>
#include <IntervalTimer.h>
#include <Motors.h>
#include <Launcher.h>
#include <NewPing.h>

void checkOff(void);
void destroyWall(void);
void towersFirst(void);
void reload(void);

//NEED TO MAKE SURE WE STOP EVERYTHING AFTER 2:10

//Global variables  
#define LIMIT_LEFT          9
#define LIMIT_BACK          10
#define LIMIT_FRONT         11
#define DIST_TRIG           16
#define DIST_ECHO           17

NewPing sonar(DIST_TRIG, DIST_ECHO, 250);

int turnTime = 750;        //calibrate this based on how long to turn 90deg
int reloadTime = 3000;   //pauses for 3s to reload the balls
int shootTime = 1000;    //waits a second between shooting each ball
int ballCounter = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  pinMode(LIMIT_FRONT, INPUT_PULLUP);
  pinMode(LIMIT_BACK, INPUT_PULLUP);
  pinMode(LIMIT_LEFT, INPUT_PULLUP);
  pinMode(DIST_ECHO, INPUT);
  pinMode(DIST_TRIG, OUTPUT);


  //Set servo to correct position
  launcher.turnOffServo();
  launcher.powerServo();
  Serial.println("Initial clear from twitch");
  launcher.shootBall();
  launcher.clearSwitch();

  //Run the check-off Casterly Rock shooting process
  checkOff();
  //Detect which mode we want to use
  //If switched to destroy the wall first
  destroyWall();
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
  //launcher.startFlywheel();
  Serial.println("Wait two seconds to shoot balls");
  delay(2000);
  int counter = 0;
  while (counter < 12){
    Serial.println("Next ball");
    launcher.shootBall();
    launcher.clearSwitch();
    counter ++;
    delay(2000);
  }
}

void destroyWall(void){
  int halfWallDist = 46;
  //Knock down bricks 4,5,6,7,8
  for(int i = 0; i < 5; i++){
    motors.rideFrontWallRight();
    while(sonar.ping_in() > (halfWallDist - (6*i))){
      //wait
    }
    motors.stopMoving();
    launcher.shootBall();
    launcher.clearSwitch();
  }
  //Start moving back to reload
  launcher.stopFlywheel();
  motors.rideFrontWallRight();
  while(sonar.ping_in() > 5){
    //wait
  }
  motors.moveBackward();
  while(!digitalRead(LIMIT_BACK)){
    //wait
  }
  reload();
  //Shoot kings landing
  motors.rideFrontWallRight();
  while(sonar.ping_in() > 46){
    //wait
  }
  //launcher.startFlywheel();
  motors.stopMoving();
  launcher.shootBall();
  launcher.clearSwitch();
  //Knock over brick 9
  motors.rideFrontWallRight();
  while(sonar.ping_in() > 22){
    //wait
  }
  motors.stopMoving();
  launcher.shootBall();
  launcher.clearSwitch();
  //Knock over brick 10, hit dragonstone
  motors.rideFrontWallRight();
  while(sonar.ping_in() > 18){
    //wait
  }
  motors.stopMoving();
  launcher.shootBall();
  launcher.clearSwitch();
  launcher.shootBall();
  launcher.clearSwitch();
  //Destroy rest of wall
  motors.rideFrontWallLeft();
  while(sonar.ping_in() < 52){
    //wait
  }
  motors.stopMoving();
  launcher.shootBall();
  launcher.clearSwitch();
  motors.rideFrontWallLeft();
  while(sonar.ping_in() < 58){
    //wait
  }
  motors.stopMoving();
  launcher.shootBall();
  launcher.clearSwitch();
  //Move back to reload
  launcher.stopFlywheel();
  motors.moveBackward();
  while(!digitalRead(LIMIT_BACK)){
    //wait
  }
  reload();
  //Start arbitrarily firing at dragon??
  //launcher.startFlywheel();
  int counter = 0;
  //If we add sensor to check for dragon, add that here?
  while (counter < 6){
    delay(1000);
    launcher.shootBall();
    launcher.clearSwitch();
  }
  launcher.stopFlywheel();
}

//Focuses on destroying all of the towers before the wall
void towersFirst(void){
  //Hit King's Landing
  motors.rideFrontWallRight();
  while(sonar.ping_in() > 43){
    //wait
  }
  //Knock over wall
  //launcher.startFlywheel();
  launcher.shootBall();
  launcher.clearSwitch();
  //Hit King's Landing
  launcher.shootBall();
  launcher.clearSwitch();
  
  //Hit Dragonstone
  motors.rideFrontWallRight();
  while(sonar.ping_in() > 18){
    //wait
  }
  //Knock over wall
  launcher.shootBall();
  launcher.clearSwitch();
  launcher.shootBall();
  launcher.clearSwitch();

  //Move backward and reload
  launcher.stopFlywheel();
  motors.moveBackward();
  while(!digitalRead(LIMIT_BACK)){
    //wait
  }
  reload();

  //Destroy wall
  motors.rideFrontWallRight();
  //launcher.startFlywheel();
  while(sonar.ping_in() > 64){
    //wait
  }
  motors.stopMoving();
  launcher.shootBall();
  launcher.clearSwitch();
  int initBlock = 51;
  //Knock down most of the wall
  for(int i = 0; i < 5; i++){
    motors.rideFrontWallRight();
    while(sonar.ping_in() > (initBlock - (i*6))){
      //wait
    }
    motors.stopMoving();
    launcher.shootBall();
    launcher.clearSwitch();
  }
  motors.rideFrontWallRight();
  while(sonar.ping_in() > 5){
    //wait
  }
  motors.moveBackward();
  while(!digitalRead(LIMIT_BACK)){
    //wait
  }
  reload();
  //Start arbitrarily firing at dragon??
  //launcher.startFlywheel();
  int counter = 0;
  //If we add sensor to check for dragon, add that here?
  while (counter < 6){
    delay(1000);
    launcher.shootBall();
    launcher.clearSwitch();
  }
  launcher.stopFlywheel();
}

//Moves from back corner behind throne room to armoury to front left corner
void reload(void){
   //Moves the robot across the arena to the armoury, pausing when it hits the switch for 7 seconds
  motors.rideBackWall(); 
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
  motors.rideFrontWallLeft();
  while(!digitalRead(LIMIT_LEFT)){
    //wait
  }
  motors.stopMoving();
}