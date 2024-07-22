#include "mbed.h"
#include <time.h>

AnalogIn sensor0(A0);
AnalogIn sensor1(A1);
AnalogIn sensor2(A2);
AnalogIn sensor3(A3);
AnalogIn sensor4(A4);

PwmOut PWM11(D9);
PwmOut PWM12(PA_11_ALT0);
PwmOut PWM21(D11);
PwmOut PWM22(D12);

int stopCount = 0;

void forward() {
    PWM11.write(0.22f);
    PWM12.write(0.0f);
    PWM21.write(0.22f);
    PWM22.write(0.0f);
}

void left() {
    PWM11.write(0.18f);
    PWM12.write(0.0f);
    PWM21.write(0.05f);
    PWM22.write(0.0f); //fast
}

void right() {
    PWM11.write(0.05f);
    PWM12.write(0.0f); // fast
    PWM21.write(0.18f);
    PWM22.write(0.0f);
}

void r_left() {
    PWM11.write(0.4f);
    PWM12.write(0.0f);
    PWM21.write(0.1f);
    PWM22.write(0.0f);
    ThisThread::sleep_for(1ms);
}

void r_right() {
    PWM11.write(0.1f);
    PWM12.write(0.0f);
    PWM21.write(0.4f);
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
    return sensor.read() < 0.4f;
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

        if (detectedSum == 5){
            stopCount++;
            if (stopCount == 6){
                stopCount = 0;
                stop();
                break;
            }
            while (isDetected(sensor0) && isDetected(sensor1) && isDetected(sensor2) && isDetected(sensor3) && isDetected(sensor4)) {
                forward();
            }
        } else {
            forward();
        }
        if (detected[0] && detected[1]){
            r_right();
        }
        else if (detected[3] && detected[4]){
            r_left();
        }
        else if (detected[1]){
            right();
        }
        else if (detected[3]){
            left();
        }
        else if(detected[0]){
            r_right();
        }
        else if(detected[4]){
            r_left();
        } else {
            forward();
        }
    }
}