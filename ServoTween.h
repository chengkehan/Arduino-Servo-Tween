#ifndef __SERVO_TWEEN
#define __SERVO_TWEEN

#include <Arduino.h>
#include <Servo.h>

//----------------------- ServoTweenType -----------------

enum ServoTweenType
{
    ServoTweenTypeLinear,
    ServoTweenTypeCubicEaseIn,
    ServoTweenTypeCubicEaseOut
};

//----------------------- ServoTweenBase -----------------

class ServoTweenBase
{
public:
    ServoTweenBase(int b, int c, int d, float timeScale);
    virtual int exe();
    bool isComplete();

protected:
    int b; // beginning value
    int c; // changed in value
    long double t; // current time
    int d; // duration
    float timeScale;
    unsigned long t0;
};

//----------------------- ServoTweenFactory -----------------

class ServoTweenFactory
{
public:
    static ServoTweenBase* create(ServoTweenType servoTweenType, int beginning, int changing, int duration, float timeScale);
    static void destroy(ServoTweenBase* servoTweenBase);
};

//----------------------- ServoTween -----------------

class ServoTween
{
public:
    ServoTween();
    ~ServoTween();

    void setup(int limitMin, int limitMax, int pin, int initialAngleInMs);
    void to(ServoTweenBase *tween);
    void loop();

private:
    void destroyTween();
    int clampAngleInMs(int angleInMs);

    Servo servo;
    int limitMin;
    int limitMax;
    int pin;
    int toAngle;
    ServoTweenBase *tween;
};

//----------------------- ServoTweenLinear -----------------

class ServoTweenLinear : public ServoTweenBase
{
public:
    ServoTweenLinear(int b, int c, int d, float timeScale);
    int exe() override;
};

//----------------------- ServoTweenCubicEaseIn -----------------

class ServoTweenCubicEaseIn : public ServoTweenBase
{
public:
    ServoTweenCubicEaseIn(int b, int c, int d, float timeScale);
    int exe() override;
};

//----------------------- ServoTweenCubicEaseOut -----------------

class ServoTweenCubicEaseOut : public ServoTweenBase
{
public:
    ServoTweenCubicEaseOut(int b, int c, int d, float timeScale);
    int exe() override;
};

#endif