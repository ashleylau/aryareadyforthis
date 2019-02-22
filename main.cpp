#include <Arduino.h>
#include <IntervalTimer.h>

int checkSwitches(void);

//Global variables
#define LEFT_MOTOR_ENABLE   3
#define LEFT_MOTOR_DIR1     4
#define LEFT_MOTOR_DIR2     5
#define RIGHT_MOTOR_ENABLE  22
#define RIGHT_MOTOR_DIR1     23
#define RIGHT_MOTOR_DIR2     21
#define LIMIT_FRONT         14
#define LIMIT_BACK          15

int left_dir1 = HIGH;
int right_dir1 = HIGH;
int left_dir2 = LOW;
int right_dir2 = LOW;
int speed = 127;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  pinMode(LEFT_MOTOR_ENABLE, OUTPUT);
  pinMode(LEFT_MOTOR_DIR1, OUTPUT);
  pinMode(LEFT_MOTOR_DIR2, OUTPUT);
  pinMode(RIGHT_MOTOR_ENABLE, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR1, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR2, OUTPUT);
  pinMode(LIMIT_FRONT, INPUT_PULLUP);
  pinMode(LIMIT_BACK, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(LEFT_MOTOR_ENABLE, speed);
  analogWrite(RIGHT_MOTOR_ENABLE, speed);
  
  int sideHit = checkSwitches();
  if (sideHit == 0){
    //do nothing
  }
  else if (sideHit == 1){
    //Front limit switch hit; set both motors to low
    left_dir1 = LOW;
    right_dir1 = LOW;
    left_dir2 = HIGH;
    right_dir2 = HIGH;
    digitalWrite(LEFT_MOTOR_DIR1, left_dir1);
    digitalWrite(LEFT_MOTOR_DIR2, left_dir2);
    digitalWrite(RIGHT_MOTOR_DIR1, right_dir1);
    digitalWrite(RIGHT_MOTOR_DIR2, right_dir2);
  }
  else if (sideHit == 2){
    //Back limit switch hit; set both motors to high
    left_dir1 = HIGH;
    right_dir1 = HIGH;
    left_dir2 = LOW;
    right_dir2 = LOW;
    digitalWrite(LEFT_MOTOR_DIR1, left_dir1);
    digitalWrite(LEFT_MOTOR_DIR2, left_dir2);
    digitalWrite(RIGHT_MOTOR_DIR1, right_dir1);
    digitalWrite(RIGHT_MOTOR_DIR2, right_dir2);
  }
}

int checkSwitches(void){
  if(LIMIT_FRONT) return 1;
  if(LIMIT_BACK) return 2;
  return 0;
}
