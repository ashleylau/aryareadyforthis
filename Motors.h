#ifndef Motors_h
#define Motors_h

/*--------------Global Variables----------------*/
#define LEFT_RIGHT_DIR1         1   //Not PWM
#define LEFT_RIGHT_DIR2         2   //Not PWM
#define LEFT_RIGHT_ENABLE       3   //PWM

#define FRONT_BACK_DIR1         18  //Not PWM
#define FRONT_BACK_DIR2         19  //Not PWM
#define FRONT_BACK_ENABLE       20  //PWM

class MotorsClass{
    public:
        MotorsClass();
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();
        void stopMoving();
    private:
        void begin();
};

extern MotorsClass motors;

#endif