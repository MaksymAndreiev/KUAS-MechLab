#include "mbed.h"

PwmOut PWM11(D9);
PwmOut PWM12(PA_11_ALT0);

// main() runs in its own thread in the OS
int main() {
    PWM11.period(1.0f);
    PWM12.period(1.0f);
    while (true) {
        PWM11.write(0.5f);
        PWM12.write(0.0f);
        printf("Forward...\r\n\n");
        ThisThread::sleep_for(1s);

        PWM11.write(0.0f);
        PWM12.write(0.5f);
        printf("Reverse...\r\n\n");
        ThisThread::sleep_for(1s);
    }
}