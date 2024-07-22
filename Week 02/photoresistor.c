#include "mbed.h"

// main() runs in its own thread in the OS
int main()
{
    AnalogIn photo(A0);
    while (true) {
        printf("ADC_read = %f, Vr = %f\n", photo.read(), photo.read()*3.3f);
        ThisThread::sleep_for(100ms);
    }
}

