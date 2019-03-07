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

//NEED TO MAKE SURE WE STOP EVERYTHING AFTER 2:10

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
  Serial.begin(9600);
  while(!Serial);

  pinMode(LIMIT_FRONT, INPUT_PULLUP);
  pinMode(LIMIT_BACK, INPUT_PULLUP);
  pinMode(LIMIT_LEFT, INPUT_PULLUP);
  pinMode(DIST_ECHO, INPUT);
  pinMode(DIST_TRIG, OUTPUT);
  Serial.println("hacked the mainframe");

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
  //towersFirst();
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
  
  while (counter < 2){
    Serial.println("Next ball");
    launcher.shootBall();
    launcher.clearSwitch();
    counter++;
    delay(2000);
  }
  
}

void destroyWall(void){
  int halfWallDist = 46;
  //Knock down bricks 4,5,6,7,8
  for(int i = 0; i < 5; i++){
    int distance = getDistance();
    motors.rideFrontWallRight();
    while(distance > (halfWallDist - (6*i))){
      //wait
      distance = getDistance();
      Serial.println(distance);
    }
    Serial.println(distance);
    motors.stopMoving();
    delay(2000);
    launcher.shootBall();
    launcher.clearSwitch();
  }
  //Start moving back to reload
  //launcher.stopFlywheel();
  Serial.println("out of tower destroying while loop");
  motors.rideFrontWallRight();
  
  int distance = getDistance();
  while(distance > 5){
    //wait
    distance = getDistance();
  }
  
  motors.moveBackward();
  while(!digitalRead(LIMIT_BACK)){
    //wait
  }
  reload();
  //Shoot kings landing
  motors.rideFrontWallRight();
  
  int distance = getDistance();
  while(distance > 46){
    //wait
    distance = getDistance();
  }
  
  //launcher.startFlywheel();
  motors.stopMoving();
  launcher.shootBall();
  launcher.clearSwitch();
  //Knock over brick 9
  motors.rideFrontWallRight();
  int distance = getDistance();
  while(distance > 22){
    //wait
    distance = getDistance();
  }
  motors.stopMoving();
  launcher.shootBall();
  launcher.clearSwitch();
  //Knock over brick 10, hit dragonstone
  motors.rideFrontWallRight();
  
  int distance = getDistance();
  while(distance> 18){
    //wait
    distance = getDistance();
  }
  
  motors.stopMoving();
  launcher.shootBall();
  launcher.clearSwitch();
  launcher.shootBall();
  launcher.clearSwitch();
  //Destroy rest of wall
  motors.rideFrontWallLeft();

  int distance = getDistance();
  while(distance < 52){
    //wait
    distance = getDistance();
  }

  motors.stopMoving();
  launcher.shootBall();
  launcher.clearSwitch();
  motors.rideFrontWallLeft();
  
  int distance = getDistance();
  while(distance < 58){
    //wait
    distance = getDistance();
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
  int distance = getDistance();
  while(distance > 43){
    //wait
    distance = getDistance();
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
  int distance = getDistance();
  while(distance > 18){
    //wait
    distance = getDistance();
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
  int distance = getDistance();
  while(distance > 64){
    //wait
    distance = getDistance();
  }
  motors.stopMoving();
  launcher.shootBall();
  launcher.clearSwitch();
  int initBlock = 51;
  //Knock down most of the wall
  for(int i = 0; i < 5; i++){
    motors.rideFrontWallRight();
    int distance = getDistance();
    while(distance > (initBlock - (i*6))){
      //wait
      distance = getDistance();
    }
    motors.stopMoving();
    launcher.shootBall();
    launcher.clearSwitch();
  }
  motors.rideFrontWallRight();
  int distance;
  while(distance > 5){
    //wait
    distance = getDistance();
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
