#include "mbed.h"

// main() runs in its own thread in the OS

int main()
{
    AnalogIn sensor(A0);
    float distance;
    while (true) {
        distance = 26.663 * pow((double(sensor) * 3.3), -1.25);
        printf("Distance =%f cm\n", distance);
        ThisThread::sleep_for(100ms);
    }
}