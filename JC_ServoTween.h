#ifndef __JC_SERVO_TWEEN__
#define __JC_SERVO_TWEEN__

#include <Arduino.h>
#include <Servo.h>

namespace JC_ServoTween
{
    //----------------------- ServoTweenType -----------------

    enum TweenType
    {
        Linear,
        QuadEaseIn,
        QuadEaseOut,
        QuadEaseInOut,
        CubicEaseIn,
        CubicEaseOut,
        CubicEaseInOut,
        QuartEaseIn,
        QuartEaseOut,
        QuartEaseInOut,
        QuintEaseIn,
        QuintEaseOut,
        QuintEaseInOut,
        SineEaseIn,
        SineEaseOut,
        SineEaseInOut,
        ExpoEaseIn,
        ExpoEaseOut,
        ExpoEaseInOut,
        CircEaseIn,
        CircEaseOut,
        CircEaseInOut,
        BounceEaseIn,
        BounceEaseOut,
        BounceEaseInOut
    };

    //----------------------- TweenBase -----------------

    class TweenBase
    {
    public:
        TweenBase(int b, int c, int d, float timeScale);
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

    //----------------------- Factory -----------------

    class Factory
    {
    public:
        static TweenBase* create(TweenType servoTweenType, int beginning, int changing, int duration, float timeScale = 1);
        static void destroy(TweenBase* servoTweenBase);
    };

    //----------------------- ServoTween -----------------

    class ServoTween
    {
    public:
        ServoTween();
        ~ServoTween();

        void setup(int limitMin, int limitMax, int pin, int initialAngleInMs);
        void to(TweenBase *tween);
        void loop();

    private:
        void destroyTween();
        int clampAngleInMs(int angleInMs);

        Servo servo;
        int limitMin;
        int limitMax;
        int pin;
        int toAngle;
        TweenBase *tween;
    };

    //----------------------- TweenLinear -----------------

    class TweenLinear : public TweenBase
    {
    public:
        TweenLinear(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenQuadEaseIn -----------------

    class TweenQuadEaseIn : public TweenBase
    {
    public:
        TweenQuadEaseIn(int b, int c, int d, float timeScale);
        int exe() override; 
    };

    //----------------------- TweenQuadEaseOut -----------------

    class TweenQuadEaseOut : public TweenBase
    {
    public:
        TweenQuadEaseOut(int b, int c, int d, float timeScale);
        int exe() override; 
    };

    //----------------------- TweenQuadEaseInOut -----------------

    class TweenQuadEaseInOut : public TweenBase
    {
    public:
        TweenQuadEaseInOut(int b, int c, int d, float timeScale);
        int exe() override; 
    };

    //----------------------- TweenCubicEaseIn -----------------

    class TweenCubicEaseIn : public TweenBase
    {
    public:
        TweenCubicEaseIn(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenCubicEaseOut -----------------

    class TweenCubicEaseOut : public TweenBase
    {
    public:
        TweenCubicEaseOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenCubicEaseInOut -----------------

    class TweenCubicEaseInOut : public TweenBase
    {
    public:
        TweenCubicEaseInOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenQuartEaseIn -----------------

    class TweenQuartEaseIn : public TweenBase
    {
    public:
        TweenQuartEaseIn(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenQuartEaseOut -----------------

    class TweenQuartEaseOut : public TweenBase
    {
    public:
        TweenQuartEaseOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenQuartEaseInOut -----------------

    class TweenQuartEaseInOut : public TweenBase
    {
    public:
        TweenQuartEaseInOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenQuintEaseIn -----------------

    class TweenQuintEaseIn : public TweenBase
    {
    public:
        TweenQuintEaseIn(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenQuintEaseOut -----------------

    class TweenQuintEaseOut : public TweenBase
    {
    public:
        TweenQuintEaseOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenQuintEaseInOut -----------------

    class TweenQuintEaseInOut : public TweenBase
    {
    public:
        TweenQuintEaseInOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenSineEaseIn -----------------

    class TweenSineEaseIn : public TweenBase
    {
    public:
        TweenSineEaseIn(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenSineEaseOut -----------------

    class TweenSineEaseOut : public TweenBase
    {
    public:
        TweenSineEaseOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenSineEaseInOut -----------------

    class TweenSineEaseInOut : public TweenBase
    {
    public:
        TweenSineEaseInOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenExpoEaseIn -----------------

    class TweenExpoEaseIn : public TweenBase
    {
    public:
        TweenExpoEaseIn(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenExpoEaseOut -----------------

    class TweenExpoEaseOut : public TweenBase
    {
    public:
        TweenExpoEaseOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenExpoEaseInOut -----------------

    class TweenExpoEaseInOut : public TweenBase
    {
    public:
        TweenExpoEaseInOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenCircEaseIn -----------------

    class TweenCircEaseIn : public TweenBase
    {
    public:
        TweenCircEaseIn(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenCircEaseOut -----------------

    class TweenCircEaseOut : public TweenBase
    {
    public:
        TweenCircEaseOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenCircEaseInOut -----------------

    class TweenCircEaseInOut : public TweenBase
    {
    public:
        TweenCircEaseInOut(int b, int c, int d, float timeScale);
        int exe() override;
    };

    //----------------------- TweenBounceEaseIn -----------------

    class TweenBounceEaseIn : public TweenBase
    {
    public:
        TweenBounceEaseIn(int b, int c, int d, float timeScale);
        int exe() override;
        static int calculate(int t, int b, int c, int d);
    };

    //----------------------- TweenBounceEaseOut -----------------

    class TweenBounceEaseOut : public TweenBase
    {
    public:
        TweenBounceEaseOut(int b, int c, int d, float timeScale);
        int exe() override;
        static int calculate(int t, int b, int c, int d);
    };

    //----------------------- TweenBounceEaseInOut -----------------

    class TweenBounceEaseInOut : public TweenBase
    {
    public:
        TweenBounceEaseInOut(int b, int c, int d, float timeScale);
        int exe() override;
    };
}

#endif