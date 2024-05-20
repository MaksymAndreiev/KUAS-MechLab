#include "mbed.h"

AnalogIn sensor0(A0);
AnalogIn sensor1(A1);
AnalogIn sensor2(A2);
AnalogIn sensor3(A3);
AnalogIn sensor4(A4);

PwmOut PWM11(D9);
PwmOut PWM12(PA_11_ALT0);
PwmOut PWM21(D11);
PwmOut PWM22(PB_4_ALT0);

void forward() {
    PWM11.write(0.5f);
    PWM12.write(0.0f);
    PWM21.write(0.5f);
    PWM22.write(0.0f);
}

void left() {
    PWM11.write(0.5f);
    PWM12.write(0.0f);
    PWM21.write(0.0f);
    PWM22.write(0.0f); //fast
}

void right() {
    PWM11.write(0.0f);
    PWM12.write(0.0f); // fast
    PWM21.write(0.5f);
    PWM22.write(0.0f);
}

void stop() {
    PWM11.write(0.0f);
    PWM12.write(0.0f);
    PWM21.write(0.0f);
    PWM22.write(0.0f);
}

int isDetected(AnalogIn sensor){
    return sensor.read() < 0.5f;
}

int main() {
    PWM11.period(1.0f);
    PWM12.period(1.0f);
    PWM21.period(1.0f);
    PWM22.period(1.0f);
    int stopCount = 0;
    while (true) {
        int detected [5];
        detected[0] = isDetected(sensor0);
        detected[1] = isDetected(sensor1);
        detected[2] = isDetected(sensor2);
        detected[3] = isDetected(sensor3);
        detected[4] = isDetected(sensor4);
        int detectedSum = detected[0] + detected[1] + detected[2] + detected[3] + detected[4];
        if (detected[2]){
            if (detectedSum >= 2){
                if (detectedSum >= 3){
                    if (detectedSum == 5){
                        stopCount++;
                        if (stopCount == 6){
                            stopCount = 0;
                            stop();
                        }
                    } else {
                        forward();
                    }
                } else {
                    if (detected[1]){
                        right();
                    } else if (detected[3]){
                        left();
                    } else {
                        forward();
                    }
                }
            } else {
                forward();
            }
        }
    }
}