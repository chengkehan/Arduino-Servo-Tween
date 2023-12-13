#include "HardwareSerial.h"
#include "JC_ServoTween.h"

using namespace JC_ServoTween;

const float EPSINON = 0.000001f;
#define EQUAL_ZERO(x) ((x >= - EPSINON) && (x <= EPSINON)) ? true : false

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

TweenBase* Factory::create(TweenType tweenType, int beginning, int changing, int duration, float timeScale)
{
    if (tweenType == Linear)
    {
        return new TweenLinear(beginning, changing, duration, timeScale);
    }

    if (tweenType == CubicEaseIn)
    {
        return new TweenCubicEaseIn(beginning, changing, duration, timeScale);
    }
    if (tweenType == CubicEaseOut)
    {
        return new TweenCubicEaseOut(beginning, changing, duration, timeScale);
    }
    if (tweenType == CubicEaseInOut)
    {
        return new TweenCubicEaseInOut(beginning, changing, duration, timeScale);
    }

    if (tweenType == QuadEaseIn)
    {
        return new TweenQuadEaseIn(beginning, changing, duration, timeScale);
    }
    if (tweenType == QuadEaseOut)
    {
        return new TweenQuadEaseOut(beginning, changing, duration, timeScale);
    }
    if (tweenType == QuadEaseInOut)
    {
        return new TweenQuadEaseInOut(beginning, changing, duration, timeScale);
    }

    if (tweenType == QuartEaseIn)
    {
        return new TweenQuartEaseIn(beginning, changing, duration, timeScale);
    }
    if (tweenType == QuartEaseOut)
    {
        return new TweenQuartEaseOut(beginning, changing, duration, timeScale);
    }
    if (tweenType == QuartEaseInOut)
    {
        return new TweenQuartEaseInOut(beginning, changing, duration, timeScale);
    }

    if (tweenType == QuintEaseIn)
    {
        return new TweenQuintEaseIn(beginning, changing, duration, timeScale);
    }
    if (tweenType == QuintEaseOut)
    {
        return new TweenQuintEaseOut(beginning, changing, duration, timeScale);
    }
    if (tweenType == QuintEaseInOut)
    {
        return new TweenQuintEaseInOut(beginning, changing, duration, timeScale);
    }

    if (tweenType == SineEaseIn)
    {
        return new TweenSineEaseIn(beginning, changing, duration, timeScale);
    }
    if (tweenType == SineEaseOut)
    {
        return new TweenSineEaseOut(beginning, changing, duration, timeScale);
    }
    if (tweenType == SineEaseInOut)
    {
        return new TweenSineEaseInOut(beginning, changing, duration, timeScale);
    }

    if (tweenType == ExpoEaseIn)
    {
        return new TweenExpoEaseIn(beginning, changing, duration, timeScale);
    }
    if (tweenType == ExpoEaseOut)
    {
        return new TweenExpoEaseOut(beginning, changing, duration, timeScale);
    }
    if (tweenType == ExpoEaseInOut)
    {
        return new TweenExpoEaseInOut(beginning, changing, duration, timeScale);
    }

    if (tweenType == CircEaseIn)
    {
        return new TweenCircEaseIn(beginning, changing, duration, timeScale);
    }
    if (tweenType == CircEaseOut)
    {
        return new TweenCircEaseOut(beginning, changing, duration, timeScale);
    }
    if (tweenType == CircEaseInOut)
    {
        return new TweenCircEaseInOut(beginning, changing, duration, timeScale);
    }

    if (tweenType == BounceEaseIn)
    {
        return new TweenBounceEaseIn(beginning, changing, duration, timeScale);
    }
    if (tweenType == BounceEaseOut)
    {
        return new TweenBounceEaseOut(beginning, changing, duration, timeScale);
    }
    if (tweenType == BounceEaseInOut)
    {
        return new TweenBounceEaseInOut(beginning, changing, duration, timeScale);
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

int ServoTween::getLimitMin()
{
    return this->limitMin;
}

int ServoTween::getLimitMax()
{
    return this->limitMax;
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

//----------------------- TweenSineEaseIn -----------------

TweenSineEaseIn::TweenSineEaseIn(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenSineEaseIn::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return -c * cos(t / d * (PI / 2)) + c + b;
}

//----------------------- TweenSineEaseOut -----------------

TweenSineEaseOut::TweenSineEaseOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenSineEaseOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return c * sin(t / d * (PI / 2)) + b;
}

//----------------------- TweenSineEaseInOut -----------------

TweenSineEaseInOut::TweenSineEaseInOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenSineEaseInOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return -c / 2 * (cos(PI * t/ d) - 1) + b;
}

//----------------------- TweenExpoEaseIn -----------------

TweenExpoEaseIn::TweenExpoEaseIn(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenExpoEaseIn::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
}

//----------------------- TweenExpoEaseOut -----------------

TweenExpoEaseOut::TweenExpoEaseOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenExpoEaseOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
}

//----------------------- TweenExpoEaseInOut -----------------

TweenExpoEaseInOut::TweenExpoEaseInOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenExpoEaseInOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    if (t == 0)
    {
        return b;
    }
    if (t == d)
    {
        return b + c;
    }
    if ((t /= d / 2) < 1)
    {
        return c / 2 * pow(2, 10 * (t - 1)) + b;
    }
    return c / 2 * (-pow(2, -10 * --t) + 2) + b;
}

//----------------------- TweenCircEaseIn -----------------

TweenCircEaseIn::TweenCircEaseIn(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenCircEaseIn::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return -c * (sqrt(1 - (t /= d) * t) - 1) + b;
}

//----------------------- TweenCircEaseOut -----------------

TweenCircEaseOut::TweenCircEaseOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenCircEaseOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return c * sqrt(1 - (t = t / d - 1) * t) + b;
}

//----------------------- TweenCircEaseInOut -----------------

TweenCircEaseInOut::TweenCircEaseInOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenCircEaseInOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    if ((t /= d / 2) < 1)
    {
        return -c / 2 * (sqrt(1 - t * t) - 1) + b;
    }
    return c / 2 * (sqrt(1 - (t -= 2) * t) + 1) + b;
}

//----------------------- TweenBounceEaseIn -----------------

TweenBounceEaseIn::TweenBounceEaseIn(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenBounceEaseIn::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return TweenBounceEaseIn::calculate(t, b, c, d);
}

int TweenBounceEaseIn::calculate(int t, int b, int c, int d)
{
    return c - TweenBounceEaseOut::calculate(d - t, 0, c, d) + b;
}

//----------------------- TweenBounceEaseOut -----------------

TweenBounceEaseOut::TweenBounceEaseOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenBounceEaseOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    return TweenBounceEaseOut::calculate(t, b, c, d);
}

int TweenBounceEaseOut::calculate(int t, int b, int c, int d)
{
    if ((t /= d) < (1 / 2.75))
    {
        return c * (7.5625 * t * t) + b;
    }
    else if (t < (2 / 2.75))
    {
        return c * (7.5625 * (t -= (1.5 / 2.75)) * t + 0.75) + b;
    }
    else if (t < (2.5 / 2.75))
    {
        return c * (7.5625 * (t -= (2.25 / 2.75)) * t + 0.9375) + b;
    }
    else
    {
        return c * (7.5625 * (t -= (2.625 / 2.75)) * t + 0.984375) + b;
    }
}

//----------------------- TweenBounceEaseInOut -----------------

TweenBounceEaseInOut::TweenBounceEaseInOut(int b, int c, int d, float timeScale) : TweenBase(b, c, d, timeScale) { }

int TweenBounceEaseInOut::exe()
{
    TweenBase::exe();
    long double t = this->t;
    if (t < d / 2)
    {
        return TweenBounceEaseIn::calculate(t * 2, 0, c, d) * 0.5 + b;
    }
    else 
    {   
        return TweenBounceEaseOut::calculate(t * 2 - d, 0, c, d) * 0.5 + c * 0.5 + b;
    }
}


