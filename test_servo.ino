#include "JC_ServoTween.h"

namespace JCST = JC_ServoTween;

JCST::ServoTween base;
JCST::ServoTween left;
JCST::ServoTween right;
JCST::ServoTween claw;

void setup() {
    Serial.begin(9600);

    base.setup(500, 2500, 6, 1500);
    base.to(JCST::Factory::create(JCST::QuadEaseInOut, 1500, 1000, 7 * 1000, 0, 0, 0, 1));

    left.setup(1500, 2100, 9, 1500);
    left.to(JCST::Factory::create(JCST::QuadEaseInOut, 1500, 2100, 7 * 1000, 0, 0, 0, 1));

    right.setup(1500, 2200, 10, 1500);
    right.to(JCST::Factory::create(JCST::QuadEaseInOut, 1500, 2200, 7 * 1000, 0, 0, 0, 1));

    claw.setup(1700, 1900, 11, 1700);
    claw.to(JCST::Factory::create(JCST::QuadEaseInOut, 1700, 1900, 7 * 1000, 0, 0, 0, 1));

    delay(1000);
}

void loop() {
    // base.loop();
    // left.loop();
    // right.loop();
    // claw.loop();

    delay(1);
}
