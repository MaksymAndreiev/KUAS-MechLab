#include "mbed.h"
#include "hcsr04.h"

// main() runs in its own thread in the OS
int main(){
    HCSR04 usensor(D4, D6);
    while (true) {
        usensor.start();
        ThisThread::sleep_for(500ms);
        unsigned int distance = usensor.get_dist_cm();
        printf("Distance =%d cm\n", distance);
    }
}