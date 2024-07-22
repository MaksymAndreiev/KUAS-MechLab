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

int stopCount = 0;

void forward() {
    PWM11.write(0.22f);
    PWM12.write(0.0f);
    PWM22.write(0.22f);
    PWM21.write(0.0f);
}

void left() {
    PWM11.write(0.18f);
    PWM12.write(0.0f);
    PWM22.write(0.05f);
    PWM21.write(0.0f);
}

void right() {
    PWM11.write(0.05f);
    PWM12.write(0.0f);
    PWM22.write(0.18f);
    PWM21.write(0.0f);
}

void rapid_left() {
    PWM11.write(0.4f);
    PWM12.write(0.0f);
    PWM22.write(0.1f);
    PWM21.write(0.0f);
}

void rapid_right() {
    PWM11.write(0.1f);
    PWM12.write(0.0f);
    PWM22.write(0.4f);
    PWM21.write(0.0f);
}

void stop() {
    PWM11.write(0.0f);
    PWM12.write(0.0f);
    PWM22.write(0.0f);
    PWM21.write(0.0f);
}

int isDetected(AnalogIn sensor){
    return sensor.read() < 0.5f;
}

int main() {
    PWM11.period(0.05f);
    PWM12.period(0.05f);
    PWM21.period(0.05f);
    PWM22.period(0.05f);
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
                            break;
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
        } else{
            if (detectedSum == 1) {
                if (detected[0]) {
                    rapid_right();
                } else if (detected[1]) {
                    right();
                } else if (detected[3]) {
                    left();
                } else if (detected[4]) {
                    rapid_left();
                }
            } else if (detectedSum == 2){
                if (detected[0] && detected[1]) {
                    rapid_right();
                } else if (detected[3] && detected[4]) {
                    rapid_left();
                }
            }
        }
    }
}