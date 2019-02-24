#ifndef Motors_h
#define Motors_h

/*--------------Global Variables----------------*/
#define LEFT_MOTOR_ENABLE   3   //PWM pin
#define LEFT_MOTOR_DIR1     2   //Not PWM pin
#define LEFT_MOTOR_DIR2     1   //Not PWM
#define RIGHT_MOTOR_ENABLE  20  //PWM
#define RIGHT_MOTOR_DIR1    19  //Not PWM
#define RIGHT_MOTOR_DIR2    18  //Not PWM

class MotorsClass{
    public:
        MotorsClass();
        void moveForward();
        void moveBackward();
        void turnLeft();
        void turnRight();
        void stopMotors();
    private:
        void begin();
};

extern MotorsClass motors;

#endif