#ifndef __SERVO_TWEEN
#define __SERVO_TWEEN

#include <Arduino.h>
#include <Servo.h>

//----------------------- ServoTweenType -----------------

enum ServoTweenType
{
    ServoTweenTypeLinear,
    ServoTweenTypeQuadEaseIn,
    ServoTweenTypeQuadEaseOut,
    ServoTweenTypeQuadEaseInOut,
    ServoTweenTypeCubicEaseIn,
    ServoTweenTypeCubicEaseOut,
    ServoTweenTypeCubicEaseInOut,
    ServoTweenTypeQuartEaseIn,
    ServoTweenTypeQuartEaseOut,
    ServoTweenTypeQuartEaseInOut,
    ServoTweenTypeQuintEaseIn,
    ServoTweenTypeQuintEaseOut,
    ServoTweenTypeQuintEaseInOut
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
    static ServoTweenBase* create(ServoTweenType servoTweenType, int beginning, int changing, int duration, float timeScale = 1);
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

//----------------------- ServoTweenQuadEaseIn -----------------

class ServoTweenQuadEaseIn : public ServoTweenBase
{
public:
    ServoTweenQuadEaseIn(int b, int c, int d, float timeScale);
    int exe() override; 
};

//----------------------- ServoTweenQuadEaseOut -----------------

class ServoTweenQuadEaseOut : public ServoTweenBase
{
public:
    ServoTweenQuadEaseOut(int b, int c, int d, float timeScale);
    int exe() override; 
};

//----------------------- ServoTweenQuadEaseInOut -----------------

class ServoTweenQuadEaseInOut : public ServoTweenBase
{
public:
    ServoTweenQuadEaseInOut(int b, int c, int d, float timeScale);
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

//----------------------- ServoTweenCubicEaseInOut -----------------

class ServoTweenCubicEaseInOut : public ServoTweenBase
{
public:
    ServoTweenCubicEaseInOut(int b, int c, int d, float timeScale);
    int exe() override;
};

//----------------------- ServoTweenQuartEaseIn -----------------

class ServoTweenQuartEaseIn : public ServoTweenBase
{
public:
    ServoTweenQuartEaseIn(int b, int c, int d, float timeScale);
    int exe() override;
};

//----------------------- ServoTweenQuartEaseOut -----------------

class ServoTweenQuartEaseOut : public ServoTweenBase
{
public:
    ServoTweenQuartEaseOut(int b, int c, int d, float timeScale);
    int exe() override;
};

//----------------------- ServoTweenQuartEaseInOut -----------------

class ServoTweenQuartEaseInOut : public ServoTweenBase
{
public:
    ServoTweenQuartEaseInOut(int b, int c, int d, float timeScale);
    int exe() override;
};

//----------------------- ServoTweenQuintEaseIn -----------------

class ServoTweenQuintEaseIn : public ServoTweenBase
{
public:
    ServoTweenQuintEaseIn(int b, int c, int d, float timeScale);
    int exe() override;
};

//----------------------- ServoTweenQuintEaseOut -----------------

class ServoTweenQuintEaseOut : public ServoTweenBase
{
public:
    ServoTweenQuintEaseOut(int b, int c, int d, float timeScale);
    int exe() override;
};

//----------------------- ServoTweenQuintEaseInOut -----------------

class ServoTweenQuintEaseInOut : public ServoTweenBase
{
public:
    ServoTweenQuintEaseInOut(int b, int c, int d, float timeScale);
    int exe() override;
};

#endif