#include "mbed.h"

#define Threshold 0.1f

// main() runs in its own thread in the OS
int main()
{
    AnalogIn photo(A0);
    DigitalOut led(D12);
    while (true) {
        if (photo.read() > Threshold){
            led =0;
        } else {
            led = 1;
        }
        ThisThread::sleep_for(100ms);
    }
}