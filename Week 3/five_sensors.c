#include "mbed.h'

AnalogIn sensor0(A0);

AnalogIn sensor1(A1);

AnalogIn sensor2(A2);

AnalogIn sensor3(A3);

AnalogIn sensor4(A4);

int main() {
    while (true) {
        printf("Sensor 0: %.5f Sensor 1: %.5f Sensor 2: %.5f Sensor 3: %.5f Sensor 4: %.5f\r\n", sensor0.read(),
               sensor1.read(), sensor2.read(), sensor3.read(), sensor4.read());
        ThisThread::sleep_for(1s);
    }
}
