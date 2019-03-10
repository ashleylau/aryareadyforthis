#include <Arduino.h>
#include <Metro.h>
#include <Motors.h>
#include <Launcher.h>
#include <NewPing.h>

//Global variables
#define LIMIT_LEFT      9
#define LIMIT_BACK      10
#define LIMIT_FRONT     11
#define DIST_ECHO       16
#define DIST_TRIG       17

int shootTime = 1000;
int ballCounter = 0;
bool timeOut = false;
bool KLalive = true;
bool DSalive = true;
bool KLdist = 43;
bool DSdist = 18;

enum state{
    reloading, 
    repositioning,
    realign,
    movingBackward,
    movingForward,
    movingRight,
    ridingFrontWallLeft,
    ridingFrontWallRight,
    ridingBackWall,
    shooting,
    shootingKL,
    shootingDS
};

state currentState;

long duration, inches;

int getDistance();

NewPing sonar(DIST_TRIG, DIST_ECHO, 250);


static Metro reloadTimer = Metro(3000);
static Metro repositionTimer = Metro(750);
static Metro shootingTimer = Metro(750);
static Metro ballJamTimer = Metro(5000);
static Metro gameTimer = Metro(130000);


void setup() {
    //put your setup code here, to run once:
    //Comment this out to upload to Teensy!
    Serial.begin(9600);
    while(!Serial);

    pinMode(LIMIT_FRONT, INPUT_PULLUP);
    pinMode(LIMIT_BACK, INPUT_PULLUP);
    pinMode(LIMIT_LEFT, INPUT_PULLUP);
    pinMode(DIST_ECHO, INPUT);
    pinMode(DIST_TRIG, OUTPUT);

    //Start 2min 10 sec game time
    gameTimer.reset();
    
    //Set servo to correct position
    launcher.turnOffServo();
    launcher.powerServo();
    launcher.shootBall();
    launcher.clearSwitch();

    //Set initial state before moving in to loop:
    currentState = movingBackward;
    motors.moveBackward();
}

void loop() {
    //put your main code here, to run repeatedly:
    if(gameTimer.check()){
        //We want this to stop everything regardless of state
        while(true){
            motors.stopMoving();
            launcher.stopFlywheel();
            launcher.stopServo();
        }
    }
    if(digitalRead(LIMIT_BACK)){
        if(currentState == movingBackward){
            currentState = ridingBackWall;
            motors.rideBackWall();
        }
    }
    if(digitalRead(LIMIT_LEFT)){
        if(currentState == ridingBackWall){
            currentState = reloading;
            motors.stopMoving();
            reloadTimer.reset();
        }
        if(currentState == realign){
            currentState = ridingFrontWallRight;
            motors.rideFrontWallRight();
        }
        if(currentState == ridingFrontWallLeft){
            currentState = shooting;
            motors.stopMoving();
            launcher.startFlywheel();
            shootingTimer.reset();
        }
    }
    if(digitalRead(LIMIT_FRONT)){
        if(currentState == movingForward){
            currentState = realign;
            motors.rideFrontWallLeft();
        }
    }
    if(reloadTimer.check()){
        if(currentState == reloading){
            currentState = repositioning;
            motors.moveRight();
            repositionTimer.reset();
        }
    }
    if(repositionTimer.check()){
        if(currentState == repositioning){
            currentState = movingForward;
            motors.moveForward();
        }
    }
    if(shootingTimer.check()){
        if(currentState == shooting){
            if(ballCounter < 6){
                launcher.shootBall();
                launcher.clearSwitch();
                ballCounter ++;
                shootingTimer.reset();
            }
            if(ballCounter >= 6){
                ballCounter = 0;
                currentState = movingBackward;
                motors.moveBackward();
            }
        }
        if(currentState == shootingKL){
            if(ballCounter < 3){
                launcher.shootBall();
                launcher.clearSwitch();
                ballCounter ++;
                shootingTimer.reset();
            }
            if(ballCounter >= 3){
                ballCounter = 0;
                KLalive = false;
                currentState = ridingFrontWallRight;
                motors.rideFrontWallRight();
            }
        }
        if(currentState == shootingDS){
            if(ballCounter < 3){
                launcher.shootBall();
                launcher.clearSwitch();
                ballCounter ++;
                shootingTimer.reset();
            }
            if(ballCounter >= 3){
                ballCounter = 0;
                DSalive = false;
                currentState = movingBackward;
                motors.moveBackward();
            }
        }
    }
    if((getDistance() < 44) && (getDistance() > 42) && KLalive){
        if(currentState == ridingFrontWallRight){
            currentState = shootingKL;
            motors.stopMoving();
            shootingTimer.reset();
        }
    }
    if((getDistance() < 19) && (getDistance() > 17) && DSalive){
        if(currentState == ridingFrontWallRight){
            currentState = shootingDS;
            motors.stopMoving();
            shootingTimer.reset();
        }
    }   
}

int getDistance(){
  return sonar.ping_in();
}
