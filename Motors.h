#ifndef Motors_h
#define Motors_h

/*--------------Global Variables----------------*/
#define LEFT_RIGHT_DIR1         1   //Not PWM
#define LEFT_RIGHT_DIR2         2   //Not PWM
#define LEFT_RIGHT_ENABLE       3   //PWM

#define FRONT_BACK_DIR1         18  //Not PWM
#define FRONT_BACK_DIR2         19  //Not PWM
#define FRONT_BACK_ENABLE       20  //PWM

/* ---- Note about naming: -----
For reference: "Front" should be pointing towards the arena wall
Left and Right refer to the left and right motors (not the direction the robot is moving)
    To drive front/back: Drive the left and right motors
Front and Back refer to the front and back motors (not the direction the robot is moving)
    To drive left/right: Drive the front and back motors
**/

class MotorsClass{
    public:
        MotorsClass();
        void moveForward();
        void moveBackward();
        void rideWall();
        void moveLeft();
        void moveRight();
        void stopMoving();
    private:
        void begin();
};

extern MotorsClass motors;

#endif
