#include "HardwareSerial.h"
#include "JC_ServoTween.h"

using namespace JC_ServoTween;

//----------------------- TweenBase -----------------

TweenBase::TweenBase(int b, int c, int d, float timeScale)
{
    this->b = b;
    this->c = c;
    this->d = d;
    this->timeScale = timeScale;
    t0 = -1;
}

int TweenBase::exe()
{
    if (t0 == -1)
    {
        t0 = millis();
    }
    t = millis() - t0;
    t *= timeScale;
    return 0;
}

bool TweenBase::isComplete()
{
    return t >= d;
}

//----------------------- Factory -----------------

TweenBase* Factory::create(TweenType servoTweenType, int beginning, int changing, int duration, float timeScale)
{
    if (servoTweenType == Linear)
    {
        return new TweenLinear(beginning, changing, duration, timeScale);
    }

    if (servoTweenType == CubicEaseIn)
    {
        return new TweenCubicEaseIn(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == CubicEaseOut)
    {
        return new TweenCubicEaseOut(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == CubicEaseInOut)
    {
        return new TweenCubicEaseInOut(beginning, changing, duration, timeScale);
    }

    if (servoTweenType == QuadEaseIn)
    {
        return new TweenQuadEaseIn(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == QuadEaseOut)
    {
        return new TweenQuadEaseOut(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == QuadEaseInOut)
    {
        return new TweenQuadEaseInOut(beginning, changing, duration, timeScale);
    }

    if (servoTweenType == QuartEaseIn)
    {
        return new TweenQuartEaseIn(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == QuartEaseOut)
    {
        return new TweenQuartEaseOut(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == QuartEaseInOut)
    {
        return new TweenQuartEaseInOut(beginning, changing, duration, timeScale);
    }

    if (servoTweenType == QuintEaseIn)
    {
        return new TweenQuintEaseIn(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == QuintEaseOut)
    {
        return new TweenQuintEaseOut(beginning, changing, duration, timeScale);
    }
    if (servoTweenType == QuintEaseInOut)
    {
        return new TweenQuintEaseInOut(beginning, changing, duration, timeScale);
    }

    return nullptr;
}

void Factory::destroy(TweenBase *servoTweenBase)
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

void ServoTween::to(TweenBase *tween)
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
    Factory::destroy(tween);
    tween = nullptr;
}

int ServoTween::clampAngleInMs(int angleInMs)
{
    return min(max(angleInMs, limitMin), limitMax);
}

//----------------------- TweenLinear -----------------

TweenLinear::TweenLinear(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenLinear::exe()
{
    TweenBase::exe();
    return c * t / d + b;
}

//----------------------- TweenQuadEaseIn -----------------

TweenQuadEaseIn::TweenQuadEaseIn(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenQuadEaseIn::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return c * (t /= d) * t + b;
}

//----------------------- TweenQuadEaseOut -----------------

TweenQuadEaseOut::TweenQuadEaseOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenQuadEaseOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return -c * (t /= d) * (t - 2) + b;
}

//----------------------- TweenQuadEaseInOut -----------------

TweenQuadEaseInOut::TweenQuadEaseInOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenQuadEaseInOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    if ((t /= d / 2) < 1)
    {
        return c / 2 * t * t + b;
    }
    return -c / 2 * ((--t) * (t - 2) - 1) + b;
}

//----------------------- TweenCubicEaseIn -----------------

TweenCubicEaseIn::TweenCubicEaseIn(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenCubicEaseIn::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return c * (t /= d) * t * t + b; 
}

//----------------------- TweenCubicEaseOut -----------------

TweenCubicEaseOut::TweenCubicEaseOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenCubicEaseOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return c * ((t = t / d - 1) * t * t + 1) + b;
}

//----------------------- TweenCubicEaseInOut -----------------

TweenCubicEaseInOut::TweenCubicEaseInOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenCubicEaseInOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    if ((t /= d / 2) < 1)
    {
        return c / 2 * t * t * t + b;
    }
    return c / 2 * ((t -= 2) * t * t + 2) + b;
}

//----------------------- TweenQuartEaseIn -----------------

TweenQuartEaseIn::TweenQuartEaseIn(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenQuartEaseIn::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return c * (t /= d) * t * t * t + b;
}

//----------------------- TweenQuartEaseOut -----------------

TweenQuartEaseOut::TweenQuartEaseOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenQuartEaseOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return -c * ((t = t / d - 1) * t * t * t - 1) + b;
}

//----------------------- TweenQuartEaseInOut -----------------

TweenQuartEaseInOut::TweenQuartEaseInOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenQuartEaseInOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    if ((t /= d / 2) < 1)
    {
        return c / 2 * t * t * t * t + b;
    }
    return -c / 2 * ((t -= 2) * t * t * t - 2) + b;
}

//----------------------- TweenQuintEaseIn -----------------

TweenQuintEaseIn::TweenQuintEaseIn(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenQuintEaseIn::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return c * (t /= d) * t * t * t * t + b;
}

//----------------------- TweenQuintEaseOut -----------------

TweenQuintEaseOut::TweenQuintEaseOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenQuintEaseOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return c * ((t = t / d - 1)* t * t * t * t + 1) + b;
}

//----------------------- TweenQuintEaseInOut -----------------

TweenQuintEaseInOut::TweenQuintEaseInOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenQuintEaseInOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    if ((t /= d / 2) < 1)
    {
        return c / 2 * t * t * t * t * t + b;
    }
    return c / 2 * ((t -= 2) * t * t * t * t + 2) + b;
}
