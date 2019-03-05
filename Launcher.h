#ifndef Launcher_h
#define Launcher_h

/*--------------Global Variables----------------*/
//Flywheel motor pins defined as if using motor driver that requires 3 output pins
#define FLYWHEEL            12  //Not PWM
#define SERVO               6  //PWM pin

class LauncherClass{
    public:
        LauncherClass();
        void startFlywheel();
        void stopFlywheel();
        void incrementBall();
        void returnRotator();
        void stopServo();
    private:
        void begin();
};

extern LauncherClass launcher;

#endif
