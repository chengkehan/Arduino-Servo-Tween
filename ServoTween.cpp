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
    if (servoTweenType == ServoTweenTypeCubicEaseInOut)
    {
        return new ServoTweenCubicEaseInOut(beginning, changing, duration, timeScale);
    }

    if (servoTweenType == ServoTweenTypeQuadEaseIn)
    {
        return new ServoTweenQuadEaseIn(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == ServoTweenTypeQuadEaseOut)
    {
        return new ServoTweenQuadEaseOut(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == ServoTweenTypeQuadEaseInOut)
    {
        return new ServoTweenQuadEaseInOut(beginning, changing, duration, timeScale);
    }

    if (servoTweenType == ServoTweenTypeQuartEaseIn)
    {
        return new ServoTweenQuartEaseIn(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == ServoTweenTypeQuartEaseOut)
    {
        return new ServoTweenQuartEaseOut(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == ServoTweenTypeQuartEaseInOut)
    {
        return new ServoTweenQuartEaseInOut(beginning, changing, duration, timeScale);
    }

    if (servoTweenType == ServoTweenTypeQuintEaseIn)
    {
        return new ServoTweenQuintEaseIn(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == ServoTweenTypeQuintEaseOut)
    {
        return new ServoTweenQuintEaseOut(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == ServoTweenTypeQuintEaseInOut)
    {
        return new ServoTweenQuintEaseInOut(beginning, changing, duration, timeScale);
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

//----------------------- ServoTweenQuadEaseIn -----------------

ServoTweenQuadEaseIn::ServoTweenQuadEaseIn(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenQuadEaseIn::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    return c * (t /= d) * t + b;
}

//----------------------- ServoTweenQuadEaseOut -----------------

ServoTweenQuadEaseOut::ServoTweenQuadEaseOut(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenQuadEaseOut::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    return -c * (t /= d) * (t - 2) + b;
}

//----------------------- ServoTweenQuadEaseInOut -----------------

ServoTweenQuadEaseInOut::ServoTweenQuadEaseInOut(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenQuadEaseInOut::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    if ((t /= d / 2) < 1)
    {
        return c / 2 * t * t + b;
    }
    return -c / 2 * ((--t) * (t - 2) - 1) + b;
}

//----------------------- ServoTweenCubicEaseIn -----------------

ServoTweenCubicEaseIn::ServoTweenCubicEaseIn(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenCubicEaseIn::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    return c * (t /= d) * t * t + b; 
}

//----------------------- ServoTweenCubicEaseOut -----------------

ServoTweenCubicEaseOut::ServoTweenCubicEaseOut(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenCubicEaseOut::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    return c * ((t = t / d - 1) * t * t + 1) + b;
}

//----------------------- ServoTweenCubicEaseInOut -----------------

ServoTweenCubicEaseInOut::ServoTweenCubicEaseInOut(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenCubicEaseInOut::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    if ((t /= d / 2) < 1)
    {
        return c / 2 * t * t * t + b;
    }
    return c / 2 * ((t -= 2) * t * t + 2) + b;
}

//----------------------- ServoTweenQuartEaseIn -----------------

ServoTweenQuartEaseIn::ServoTweenQuartEaseIn(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenQuartEaseIn::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    return c * (t /= d) * t * t * t + b;
}

//----------------------- ServoTweenQuartEaseOut -----------------

ServoTweenQuartEaseOut::ServoTweenQuartEaseOut(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenQuartEaseOut::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    return -c * ((t = t / d - 1) * t * t * t - 1) + b;
}

//----------------------- ServoTweenQuartEaseInOut -----------------

ServoTweenQuartEaseInOut::ServoTweenQuartEaseInOut(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenQuartEaseInOut::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    if ((t /= d / 2) < 1)
    {
        return c / 2 * t * t * t * t + b;
    }
    return -c / 2 * ((t -= 2) * t * t * t - 2) + b;
}

//----------------------- ServoTweenQuintEaseIn -----------------

ServoTweenQuintEaseIn::ServoTweenQuintEaseIn(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenQuintEaseIn::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    return c * (t /= d) * t * t * t * t + b;
}

//----------------------- ServoTweenQuintEaseOut -----------------

ServoTweenQuintEaseOut::ServoTweenQuintEaseOut(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenQuintEaseOut::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    return c * ((t = t / d - 1)* t * t * t * t + 1) + b;
}

//----------------------- ServoTweenQuintEaseInOut -----------------

ServoTweenQuintEaseInOut::ServoTweenQuintEaseInOut(int b, int c, int d, float timeScale) : ServoTweenBase(b, c, d, timeScale) { }

int ServoTweenQuintEaseInOut::exe()
{
    ServoTweenBase::exe();
    long double t = this->t;
    if ((t /= d / 2) < 1)
    {
        return c / 2 * t * t * t * t * t + b;
    }
    return c / 2 * ((t -= 2) * t * t * t * t + 2) + b;
}
