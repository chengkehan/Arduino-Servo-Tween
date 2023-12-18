#ifndef __JC_SERVO_ANIMATION__
#define __JC_SERVO_ANIMATION__

#include "JC_ServoTween.h"

namespace JCST = JC_ServoTween;

namespace JC_ServoAnimation
{
    class ServoAnimation
    {
    public:
        ServoAnimation(JCST::ServoTween *servoTween);
        
        void Add(JCST::Tween* tween);
        void Loop();
        bool IsPlaying();

    private:
        JCST::ServoTween *servoTween;

        static const int TWEEN_LIST_CAPACITY = 5;
        JCST::Tween* tweenList[TWEEN_LIST_CAPACITY];

        bool isPlaying;
    };
}

#endif