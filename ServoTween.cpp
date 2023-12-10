#include "HardwareSerial.h"
#include "ServoTween.h"

//----------------------- ServoTweenBase -----------------

ServoTweenBase::ServoTweenBase(int b, int c, int d, float timeScale)
{
    this->b = b;
    this->c = c;
    this->d = d;
    this->timeScale = timeScale;
    t0 = -1;
}

int ServoTweenBase::exe()
{
    if (t0 == -1)
    {
        t0 = millis();
    }
    t = millis() - t0;
    t *= timeScale;
    return 0;
}

bool ServoTweenBase::isComplete()
{
    return t >= d;
}

//----------------------- ServoTweenFactory -----------------

ServoTweenBase* ServoTweenFactory::create(ServoTweenType servoTweenType, int beginning, int changing, int duration, float timeScale)
{
    if (servoTweenType == ServoTweenTypeLinear)
    {
        return new ServoTweenLinear(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == ServoTweenTypeCubicEaseIn)
    {
        return new ServoTweenCubicEaseIn(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == ServoTweenTypeCubicEaseOut)
    {
        return new ServoTweenCubicEaseOut(beginning, changing, duration, timeScale);
    }

    return nullptr;
}

void ServoTweenFactory::destroy(ServoTweenBase *servoTweenBase)
{
    if (servoTweenBase != nullptr)
    {
        delete servoTweenBase;
        servoTweenBase = nullptr;
    }
}

//----------------------- ServoTween -----------------

ServoTween::ServoTween()
{
    toAngle = 0;
    tween = nullptr;
}

ServoTween::~ServoTween()
{
    destroyTween();
}

void ServoTween::setup(int limitMin, int limitMax, int pin, int initialAngleInMs)
{
    this->limitMin = limitMin;
    this->limitMax = limitMax;
    this->pin = pin;

    servo.writeMicroseconds(initialAngleInMs);
    servo.attach(this->pin);
}

void ServoTween::to(ServoTweenBase *tween)
{
    destroyTween();
    this->tween = tween;
}

void ServoTween::loop()
{
    if (tween != nullptr) 
    {
        int angleInMs = tween->exe();
        angleInMs = clampAngleInMs(angleInMs);
        servo.writeMicroseconds(angleInMs);
        if (tween->isComplete())
        {
            destroyTween();
        }
    }
}

void ServoTween::destroyTween()
{
    ServoTweenFactory::destroy(tween);
    tween = nullptr;
}

int ServoTween::clampAngleInMs(int angleInMs)
{
    return min(max(angleInMs, limitMin), limitMax);
}

//----------------------- ServoTweenLinear -----------------

ServoTweenLinear::ServoTweenLinear(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenLinear::exe()
{
    ServoTweenBase::exe();
    return c * t / d + b;
}

//----------------------- ServoTweenCubicEaseIn -----------------

ServoTweenCubicEaseIn::ServoTweenCubicEaseIn(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenCubicEaseIn::exe()
{
    ServoTweenBase::exe();
    long double t = this->t / d;
    return c * t * t * t + b; 
}

//----------------------- ServoTweenCubicEaseOut -----------------

ServoTweenCubicEaseOut::ServoTweenCubicEaseOut(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenCubicEaseOut::exe()
{
    ServoTweenBase::exe();
    long double t = this->t / d - 1;
    return c * (t * t * t + 1) + b;
}
