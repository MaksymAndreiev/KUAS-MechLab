#include "mbed.h"
#include <cstdio>

// main() runs in its own thread in the OS
int main() {
    PwmOut mypwm(D12);
    mypwm.period(0.02f);
    while (true) {
        for (float p = 0.0f; p <= 0.5f; p += 0.1f) {
            mypwm.write(p);
            printf("%f\n", p);
            ThisThread::sleep_for(1000ms);
        }
        for (float p = 0.5f; p >= 0.0f; p -= 0.1f) {
            mypwm.write(p);
            printf("%f\n", p);
            ThisThread::sleep_for(1000ms);
        }
    }
}