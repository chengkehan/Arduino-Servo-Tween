#ifndef __JC_SERVO_TWEEN__
#define __JC_SERVO_TWEEN__

#include <Arduino.h>
#include <Servo.h>

namespace JC_ServoTween
{
    //----------------------- ServoTweenType -----------------

    enum TweenType
    {
        Undefined,
        Linear,
        QuadEaseIn,
        QuadEaseOut,
        QuadEaseInOut,
    };

    //----------------------- TweenBase -----------------

    class Tween
    {
    public:
        typedef int (*Operator)(long double t, int b, int c, int d);

        bool Set(TweenType tweenType, int b, int c, int d, float timeScale);
        int Execute();
        bool IsComplete();
        TweenType Type();

        static int OP_Linear(long double t, int b, int c, int d);
        
        static int OP_QuadEaseIn(long double t, int b, int c, int d);
        static int OP_QuadEaseOut(long double t, int b, int c, int d);
        static int OP_QuadEaseInOut(long double t, int b, int c, int d);

    private:
        Operator op;
        TweenType type;
        int b; // beginning value
        int c; // changed in value
        long double t; // current time
        int d; // duration
        float timeScale;
        unsigned long t0;
        bool isFree;
    };

    //----------------------- Factory -----------------

    class Factory
    {
    public:
        static Tween* Fetch(TweenType tweenType, int beginning, int changing, int duration, float timeScale = 1);
        static bool Release(Tween* tween);

    private:
        static const int TWEEN_POOL_CAPACITY = 20;
        static Tween* tweenPool;
    };

    //----------------------- ServoTween -----------------

    class ServoTween
    {
    public:
        ServoTween();
        ~ServoTween();

        void Setup(int limitMin, int limitMax, int pin, int initialAngleInMs);
        void To(Tween *tween);
        bool IsIdle();
        void Loop();
        int GetLimitMin();
        int GetLimitMax();

    private:
        void destroyTween();
        int clampAngleInMs(int angleInMs);

        Servo servo;
        int limitMin;
        int limitMax;
        int pin;
        int toAngle;
        Tween *tween;
    };
}

#endif