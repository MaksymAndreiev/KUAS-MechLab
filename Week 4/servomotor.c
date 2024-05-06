#include "mbed.h"

// main() runs in its own thread in the OS
int main() {
    PwmOut mypwm(D12);
    mypwm.period(0.02f);

    while (true) {
        mypwm = 0.07f;
        ThisThread::sleep_for(1000ms);
        mypwm = 0.11f;
        ThisThread::sleep_for(1000ms);
        mypwm = 0.07f;
        ThisThread::sleep_for(1000ms);
        mypwm = 0.03f;
        ThisThread::sleep_for(1000ms);
    }
}