#include "mbed.h"

// main() runs in its own thread in the OS

int main()
{
    AnalogIn sensor(A0);
    float distance_unfiltered, distance_filtered;
    float a = 0.85;
    float T = 0.01;
    float vin;
    float vout_pre;
    float vout = 0;
    while (true) {
        vout_pre = vout;
        vin = double(sensor) * 3.3;
        vout = a * vout_pre + (1 - a) * double(sensor); // RC filter to smooth the output
        distance_unfiltered = 26.663 * pow(vin, -1.25);
        distance_filtered = 26.663 * pow(vout * 3.3, -1.25);
        printf("%f, %f\n", distance_unfiltered, distance_filtered);
        ThisThread::sleep_for(T*100);
    }
}
