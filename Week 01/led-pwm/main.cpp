#include "mbed.h"

int main(){
    PwmOut led(D12);
    led.period(0.02f);
    while (true) {
        for (float p = 0.0f; p < 1.0f; p += 0.1f) {
            led.write(p);
            ThisThread::sleep_for(100ms);
        }
        for (float p = 1.0f; p > 0.0f; p -= 0.1f) {
            led.write(p);
            ThisThread::sleep_for(100ms);
        }
    }
}
