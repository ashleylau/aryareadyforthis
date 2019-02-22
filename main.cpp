#include <Arduino.h>
#include <IntervalTimer.h>

int checkSwitches(void);

//Global variables
#define LEFT_MOTOR_ENABLE   3
#define LEFT_MOTOR_DIR      4
#define RIGHT_MOTOR_ENABLE  22
#define RIGHT_MOTOR_DIR     23
#define LIMIT_FRONT         14
#define LIMIT_BACK          15

int left_dir = HIGH;
int right_dir = HIGH;
int speed = 127;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  pinMode(LEFT_MOTOR_ENABLE, OUTPUT);
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_ENABLE, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);
  pinMode(LIMIT_FRONT, INPUT_PULLUP);
  pinMode(LIMIT_BACK, INPUT_PULLUP);
  analogWrite(LEFT_MOTOR_ENABLE, speed);
  analogWrite(RIGHT_MOTOR_ENABLE, speed);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sideHit = checkSwitches();
  if (sideHit == 0){
    //do nothing
  }
  else if (sideHit == 1){
    //Front limit switch hit; set both motors to low
    left_dir = LOW;
    right_dir = LOW;
    digitalWrite(LEFT_MOTOR_DIR, left_dir);
    digitalWrite(RIGHT_MOTOR_DIR, right_dir);
  }
  else if (sideHit == 2){
    //Back limit switch hit; set both motors to high
    left_dir = HIGH;
    right_dir = HIGH;
    digitalWrite(LEFT_MOTOR_DIR, left_dir);
    digitalWrite(RIGHT_MOTOR_DIR, right_dir);
  }
}

int checkSwitches(void){
  if(LIMIT_FRONT) return 1;
  if(LIMIT_BACK) return 2;
  return 0;
}