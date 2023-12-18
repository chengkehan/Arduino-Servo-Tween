#include "HardwareSerial.h"
#include "JC_ServoTween.h"

using namespace JC_ServoTween;

//----------------------- TweenBase -----------------

bool Tween::Set(TweenType tweenType, int b, int c, int d, float timeScale)
{
    this->type = tweenType;
    this->b = b;
    this->c = c;
    this->d = d;
    this->timeScale = timeScale;
    t0 = -1;

    this->op = nullptr;
    if (tweenType == Linear)
    {
        this->op = OP_Linear;
    }
    if (tweenType == QuadEaseIn)
    {
        this->op = OP_QuadEaseIn;
    }
    if (tweenType == QuadEaseOut)
    {
        this->op = OP_QuadEaseOut;
    }
    if (tweenType == QuadEaseInOut)
    {
        this->op = OP_QuadEaseInOut;
    }
}

int Tween::Execute()
{
    if (t0 == -1)
    {
        t0 = millis();
    }
    t = millis() - t0;
    t *= timeScale;
    if (op != nullptr)
    {
        return OP_QuadEaseInOut(t, b, c, d);
    }
    return 0;
}

bool Tween::IsComplete()
{
    return t >= d;
}

TweenType Tween::Type()
{
    return type;
}

int Tween::OP_Linear(long double t, int b, int c, int d)
{
    return c * t / d + b;
}

int Tween::OP_QuadEaseIn(long double t, int b, int c, int d)
{
    return c * (t /= d) * t + b;
}

int Tween::OP_QuadEaseOut(long double t, int b, int c, int d)
{
    return -c * (t /= d) * (t - 2) + b;
}

int Tween::OP_QuadEaseInOut(long double t, int b, int c, int d)
{
    if ((t /= d / 2) < 1)
    {
        return c / 2 * t * t + b;
    }
    return -c / 2 * ((--t) * (t - 2) - 1) + b;
}

//----------------------- Factory -----------------

Tween* Factory::tweenPool = nullptr;

Tween* Factory::Fetch(TweenType tweenType, int beginning, int changing, int duration, float timeScale)
{
    if (tweenPool == nullptr)
    {
        tweenPool = new Tween[TWEEN_POOL_CAPACITY];
        if (tweenPool != nullptr)
        {
            for (int i = 0; i < TWEEN_POOL_CAPACITY; ++i) 
            {
                Tween* tween = &tweenPool[i];
                tween->Set(Undefined, 0, 0, 0, 0);
            }
        }
    }

    if (tweenPool != nullptr)
    {
        for (int i = 0; i < TWEEN_POOL_CAPACITY; i++)
        {
            Tween *tween = &tweenPool[i];
            if (tween->Type() == Undefined)
            {
                tween->Set(tweenType, beginning, changing, duration, timeScale);
                return tween;
            }
        }
    }
    
    return nullptr;
}

Tween* Factory::Fetch2(TweenType tweenType, int beginning, int ending, int duration, float timeScale)
{
    return Factory::Fetch(tweenType, beginning, ending - beginning, duration, timeScale);
}

bool Factory::Release(Tween *pTween)
{
    if (pTween != nullptr)
    {
        for (int i = 0; i < TWEEN_POOL_CAPACITY; i++)
        {
            Tween *tween = &tweenPool[i];
            if (tween == pTween)
            {
                tween->Set(Undefined, 0, 0, 0, 0);
                return true;
            }
        }
    }
    
    return false;
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

void ServoTween::Setup(int limitMin, int limitMax, int pin, int initialAngleInMs)
{
    this->limitMin = limitMin;
    this->limitMax = limitMax;
    this->pin = pin;

    servo.writeMicroseconds(initialAngleInMs);
    servo.attach(this->pin);
}

void ServoTween::To(Tween *tween)
{
    destroyTween();
    this->tween = tween;
}

bool ServoTween::IsIdle()
{
    return tween == nullptr;
}

void ServoTween::Loop()
{
    if (tween != nullptr) 
    {
        int angleInMs = tween->Execute();
        angleInMs = clampAngleInMs(angleInMs);
        servo.writeMicroseconds(angleInMs);
        if (tween->IsComplete())
        {
            destroyTween();
        }
    }
}

void ServoTween::destroyTween()
{
    Factory::Release(tween);
    tween = nullptr;
}

int ServoTween::clampAngleInMs(int angleInMs)
{
    return min(max(angleInMs, limitMin), limitMax);
}

int ServoTween::GetLimitMin()
{
    return this->limitMin;
}

int ServoTween::GetLimitMax()
{
    return this->limitMax;
}
