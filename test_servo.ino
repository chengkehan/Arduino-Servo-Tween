#include "JC_ServoTween.h"

namespace JCST = JC_ServoTween;

JCST::ServoTween base;
JCST::ServoTween left;
JCST::ServoTween right;
JCST::ServoTween claw;

void setup() {
    Serial.begin(9600);

    base.Setup(500, 2500, 6, 1500);
    base.To(JCST::Factory::Fetch(JCST::QuadEaseInOut, 1500, 1000, 5 * 1000, 1));

    // left.Setup(1500, 2100, 9, 1500);
    // left.To(JCST::Factory::Fetch(JCST::QuadEaseInOut, 1500, 2100, 7 * 1000, 1));

    // right.Setup(1500, 2200, 10, 1500);
    // right.To(JCST::Factory::Fetch(JCST::QuadEaseInOut, 1500, 2200, 7 * 1000, 1));

    // claw.Setup(1700, 1900, 11, 1700);
    // claw.To(JCST::Factory::Fetch(JCST::QuadEaseInOut, 1700, 1900, 7 * 1000, 1));

    delay(1000);
}

void loop() {
    base.Loop();
    // left.loop();
    // right.loop();
    // claw.loop();

    delay(1);
}
