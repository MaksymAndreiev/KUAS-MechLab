#include "mbed.h"

#define Threshold 0.1f

// main() runs in its own thread in the OS
int main()
{
    AnalogIn photo(A0);
    while (true) {
        if (photo.read() > Threshold){
            printf("ADC_read = %f, White\n", photo.read());
        } else {
            printf("ADC_read = %f, Black or No object\n", photo.read());
        }
        ThisThread::sleep_for(100ms);
    }
}
