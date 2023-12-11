#include "JC_ServoTween.h"

namespace JCST = JC_ServoTween;

JCST::ServoTween base;

void setup() {
    Serial.begin(9600);

    base.setup(500, 2500, 6, 1500);
    base.to(JCST::Factory::create(JCST::CubicEaseInOut, 1500, 1000, 5 * 1000));
    delay(1000);
}

void loop() {
    // base.loop();

    delay(1);
}
