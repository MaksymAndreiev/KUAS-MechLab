#include "mbed.h"

// main() runs in its own thread in the OS
int main() {
    PwmOut motorv1(D11);
    PwmOut motorv2(D12);
    motorv1.period(0.02f);
    motorv2.period(0.02f);

    while (true) {
        motorv1 = 0.2f;
        motorv2 = 0.2f;
        ThisThread::sleep_for(1000ms);
        motorv1 = 1.0f;
        motorv2 = 1.0f;
        ThisThread::sleep_for(1000ms);
        motorv1 = 0.0f;
        motorv2 = 0.2f;
        ThisThread::sleep_for(1000ms);
        motorv1 = 0.0f;
        motorv2 = 0.0f;
        ThisThread::sleep_for(1000ms);
    }
}