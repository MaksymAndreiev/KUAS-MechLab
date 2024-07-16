#include "mbed.h"
// #include <QTRSensors.h>

AnalogIn sensor0(A0);
AnalogIn sensor1(A1);
AnalogIn sensor2(A2);
AnalogIn sensor3(A3);
AnalogIn sensor4(A4);

PwmOut PWM11(D9); // right wheel
PwmOut PWM12(PA_11_ALT0); // r
PwmOut PWM21(D11); // l
PwmOut PWM22(D12); // l

int stopCount = 0;

void forward() {
    PWM11.write(0.0f);
    PWM12.write(0.28f);
    PWM21.write(0.28f);
    PWM22.write(0.0f);
}

void left(){
    PWM11.write(0.0f);
    PWM12.write(0.5f);
    PWM21.write(0.0f);
    PWM22.write(0.0f);
    ThisThread::sleep_for(1ms);
}

void right(){
    PWM11.write(0.0f);
    PWM12.write(0.0f);
    PWM21.write(0.5f);
    PWM22.write(0.0f);
    ThisThread::sleep_for(1ms);
}

void right_rapid(){
    PWM11.write(0.5f);
    PWM12.write(0.0f);
    PWM21.write(0.5f);
    PWM22.write(0.0f);
    ThisThread::sleep_for(1ms);
}

void stop() {
    PWM11.write(0.0f);
    PWM12.write(0.0f);
    PWM21.write(0.0f);
    PWM22.write(0.0f);
}

int isDetected(AnalogIn sensor){
    return sensor.read() < 0.6f;
}

int main() {
    PWM11.period(0.01f);
    PWM12.period(0.01f);
    PWM21.period(0.01f);
    PWM22.period(0.01f);

    while (true) {
        int detected[5];
        detected[0] = isDetected(sensor0);
        detected[1] = isDetected(sensor1);
        detected[2] = isDetected(sensor2);
        detected[3] = isDetected(sensor3);
        detected[4] = isDetected(sensor4);
        int detectedSum = detected[0] + detected[1] + detected[2] + detected[3] + detected[4];

        if (detectedSum == 5) {
            stopCount++;
            if (stopCount == 6) {
                stopCount = 0;
                stop();
                break;
            }
            while (isDetected(sensor0) && isDetected(sensor1) && isDetected(sensor2) && isDetected(sensor3) &&
                   isDetected(sensor4)) {
                forward();
            }
        } else {
            if ((detected[0] || detected[1]) && !detected[2]) {
                left();
            } else if (detected[3] || detected[4]) {
                right_rapid();
            } else if ((detected[3] || detected[4]) && !detected[2]) {
                right();
            } else {
                forward();
            }
        }
    }
}