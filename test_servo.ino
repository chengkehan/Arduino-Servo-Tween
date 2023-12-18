#include "JC_ServoTween.h"
#include "JC_ServoAnimation.h"

namespace JCST = JC_ServoTween;
namespace JCSA = JC_ServoAnimation;

JCST::ServoTween base;
JCST::ServoTween left;
JCST::ServoTween right;
JCST::ServoTween claw;

JCSA::ServoAnimation baseAnim(&base);
JCSA::ServoAnimation leftAnim(&left);
JCSA::ServoAnimation rightAnim(&right);
JCSA::ServoAnimation clawAnim(&claw);

void setup() {
    Serial.begin(9600);

    base.Setup(500, 2500, 6, 500);
    for (int i = 0; i < 2; ++i)
    {
        baseAnim.Add(JCST::Factory::Fetch2(JCST::QuadEaseInOut, 500, 2500, 5 * 1000, 2));
        baseAnim.Add(JCST::Factory::Fetch2(JCST::QuadEaseInOut, 2500, 500, 5 * 1000, 2));
    }
    baseAnim.Add(JCST::Factory::Fetch2(JCST::QuadEaseInOut, 500, 1500, 2 * 1000, 2));

    left.Setup(1500, 2100, 9, 1500);
    for (int i = 0; i < 2; ++i)
    {
        leftAnim.Add(JCST::Factory::Fetch2(JCST::Linear, 1500, 2100, 3 * 1000, 2));
        leftAnim.Add(JCST::Factory::Fetch2(JCST::QuadEaseInOut, 2100, 1500, 3 * 1000, 2));
    }

    right.Setup(1500, 2200, 10, 1500);
    for (int i = 0; i < 2; ++i)
    {
        rightAnim.Add(JCST::Factory::Fetch2(JCST::QuadEaseInOut, 1500, 2200, 3 * 1000, 2));
        rightAnim.Add(JCST::Factory::Fetch2(JCST::QuadEaseInOut, 2200, 1500, 3 * 1000, 2));
    }
    
    claw.Setup(1700, 1900, 11, 1700);
    for (int i = 0; i < 2; ++i)
    {
        clawAnim.Add(JCST::Factory::Fetch2(JCST::Linear, 1700, 1900, 1 * 1000, 4));
        clawAnim.Add(JCST::Factory::Fetch2(JCST::Linear, 1900, 1700, 1 * 1000, 4));
    }

    delay(1000);
}

void loop() {
    baseAnim.Loop();
    leftAnim.Loop();
    rightAnim.Loop();
    clawAnim.Loop();

    delay(1);
}
