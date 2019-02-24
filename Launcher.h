#ifndef Launcher_h
#define Launcher_h

/*--------------Global Variables----------------*/
//Flywheel motor pins defined as if using motor driver that requires 3 output pins
#define FLYWHEEL_ENABLE     10  //PWM pin
#define FLYWHEEL_DIR1       11  //Not PWM
#define FLYWHEEL_DIR2       12  //Not PWM
#define SERVO               21  //PWM pin

class LauncherClass{
    public:
        LauncherClass();
        void startFlywheel();
        void stopFlywheel();
        void incrementBall();
    private:
        void begin();
};

extern LauncherClass launcher;

#endif