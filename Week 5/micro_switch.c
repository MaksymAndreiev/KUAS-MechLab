#include "mbed.h"

// main() runs in its own thread in the OS
int main(){
    DigitalIn din(D12);
    din.mode(PullUp);
    while (true) {
        if (din.read() == 1) {
            printf("high\n");
        } else {
            printf("low\n");
        }
        ThisThread::sleep_for(100ms);
    }
}