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
bool CRalive = true;
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
    shootingCR,
    shootingDS
};

state currentState;

int getDistance();

NewPing sonar(DIST_TRIG, DIST_ECHO, 250);

long duration, inches;

static Metro reloadTimer = Metro(3000);
static Metro repositionTimer = Metro(750);
static Metro shootingTimer = Metro(750);
static Metro ballJamTimer = Metro(10000);
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
    launcher.shootBall();
    launcher.clearSwitch();

    //Set initial state before moving in to loop:
    currentState = movingBackward;
    motors.moveBackward();
    ballJamTimer.reset();
}

void loop() {
    //put your main code here, to run repeatedly:
    Serial.println(getDistance());
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
            ballJamTimer.reset();
        }
    }
    if(digitalRead(LIMIT_LEFT)){
        if(currentState == ridingBackWall){
            currentState = reloading;
            motors.stopMoving();
            reloadTimer.reset();
            ballJamTimer.reset();
        }
        if(currentState == realign){
            if(CRalive){
                currentState = shootingCR;
                motors.stopMoving();
                shootingTimer.reset();
                ballJamTimer.reset();
            }
            else if(!CRalive && !DSalive && !KLalive){
                currentState = shooting;
                motors.stopMoving();
                shootingTimer.reset();
                ballJamTimer.reset();
            }
            else{
                currentState = ridingFrontWallRight;
                motors.rideFrontWallRight();
                ballJamTimer.reset();
            }
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
            ballJamTimer.reset();
            launcher.startFlywheel();
        }
    }
    if(reloadTimer.check()){
        if(currentState == reloading){
            currentState = repositioning;
            motors.moveRight();
            ballJamTimer.reset();
            repositionTimer.reset();
        }
    }
    if(repositionTimer.check()){
        if(currentState == repositioning){
            currentState = movingForward;
            motors.moveForward();
            ballJamTimer.reset();
        }
    }
    if(shootingTimer.check()){
        if(currentState == shooting){
            if(ballCounter < 6){
                launcher.startFlywheel();
                launcher.shootBall();
                launcher.clearSwitch();
                ballCounter ++;
                shootingTimer.reset();
            }
            if(ballCounter >= 6){
                launcher.stopFlywheel();
                ballCounter = 0;
                currentState = movingBackward;
                motors.moveBackward();
                ballJamTimer.reset();
            }
        }
        if(currentState == shootingCR){
            if(ballCounter < 2){
                launcher.startFlywheel();
                launcher.shootBall();
                launcher.clearSwitch();
                ballCounter ++;
                shootingTimer.reset();
                ballJamTimer.reset();
            }
            if(ballCounter >= 2){
                ballCounter = 0;
                CRalive = false;
                currentState = ridingFrontWallRight;
                motors.rideFrontWallRight();
                ballJamTimer.reset();
            }
        }
        if(currentState == shootingKL){
            if(ballCounter < 1){
                launcher.startFlywheel();
                launcher.shootBall();
                launcher.clearSwitch();
                ballCounter ++;
                shootingTimer.reset();
                ballJamTimer.reset();
            }
            if(ballCounter >= 1){
                ballCounter = 0;
                KLalive = false;
                currentState = ridingFrontWallRight;
                motors.rideFrontWallRight();
                ballJamTimer.reset();
            }
        }
        if(currentState == shootingDS){
            if(ballCounter < 3){
                launcher.shootBall();
                launcher.clearSwitch();
                ballCounter ++;
                shootingTimer.reset();
                ballJamTimer.reset();
            }
            if(ballCounter >= 3){
                launcher.stopFlywheel();
                ballCounter = 0;
                DSalive = false;
                currentState = movingBackward;
                motors.moveBackward();
                ballJamTimer.reset();
            }
        }
    }
    if((getDistance() < (KLdist+3)) && (getDistance() > (KLdist-3)) && KLalive){
        if(currentState == ridingFrontWallRight){
            currentState = shootingKL;
            motors.stopMoving();
            ballJamTimer.reset();
            shootingTimer.reset();
        }
    }
    if((getDistance() < (DSdist+3)) && (getDistance() > (DSdist))){
        if(currentState == ridingFrontWallRight && DSalive){
            currentState = shootingDS;
            motors.stopMoving();
            ballJamTimer.reset();
            shootingTimer.reset();
        }
        if(currentState == ridingFrontWallRight && !DSalive){
            currentState = movingBackward;
            motors.moveBackward();
            ballJamTimer.reset();
        }
    }
    if(ballJamTimer.check()){
        if(currentState == movingBackward){
            //Would only jam against a ball moving backward if at the back wall
            currentState = ridingBackWall;
            motors.rideBackWall();
            ballJamTimer.reset();
        }
        if(currentState == movingForward){
            //Can't reach the front, just go left
            currentState = ridingFrontWallLeft;
            motors.rideFrontWallLeft();
            ballJamTimer.reset();
        }
        if(currentState == ridingFrontWallLeft){
            motors.stopMoving();
            ballJamTimer.reset();
        }
    }
}

int getDistance(){
    double microseconds = sonar.ping_median(7);
    return sonar.convert_in(microseconds);
}
