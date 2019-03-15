#ifndef Launcher_h
#define Launcher_h

/*--------------Global Variables----------------*/
//Flywheel motor pins defined as if using motor driver that requires 3 output pins
#define LOADER_MOSFET       7  //Not PWM
#define LIMIT_SERVO         8
#define FLYWHEEL            15 //Not PWM

class LauncherClass{
    public:
        LauncherClass();
        void startFlywheel();
        void stopFlywheel();
        void moveServo();
        void stopServo();
        void powerServo();
        void turnOffServo();
        void clearSwitch();
        void shootBall();
    private:
        void begin();
};

extern LauncherClass launcher;

#endif