#include "HardwareSerial.h"
#include "JC_ServoAnimation.h"

using namespace JC_ServoAnimation;

ServoAnimation::ServoAnimation(JCST::ServoTween *servoTween)
{
    this->servoTween = servoTween;

    for (int i = 0; i < TWEEN_LIST_CAPACITY; i++)
    {
        tweenList[i] = nullptr;
    }
    
    isPlaying = false;
}

void ServoAnimation::Add(JCST::Tween *tween)
{
    if (isPlaying)
    {
        return;
    }

    for (int i = 0; i < TWEEN_LIST_CAPACITY; i++)
    {
        if (tweenList[i] == nullptr)
        {
            tweenList[i] = tween;
            break;
        }
    }
}

void ServoAnimation::Loop()
{
    if (servoTween != nullptr)
    {
        isPlaying = true;

        if (servoTween->IsIdle())
        {
            bool tweenPlayed = false;
            
            for (int i = 0; i < TWEEN_LIST_CAPACITY; i++)
            {
                if (tweenList[i] != nullptr)
                {
                    JCST::Tween *tween = tweenList[i];
                    tweenList[i] = nullptr;
                    servoTween->To(tween);
                    tweenPlayed = true;
                    break;
                }
            }

            if (!tweenPlayed)
            {
                isPlaying = false;
            }
            
        }
        else
        {
            servoTween->Loop();
        }
    }
}

bool ServoAnimation::IsPlaying()
{
    return isPlaying;
}