#include "ServoTween.h"

ServoTween base;

void setup() {
    Serial.begin(9600);

    base.setup(500, 2500, 6, 1500);
    base.to(ServoTweenFactory::create(ServoTweenTypeCubicEaseIn, 1500, 1000, 5 * 1000, 1));
    delay(1000);
}

void loop() {
    base.loop();

    delay(1);
}
