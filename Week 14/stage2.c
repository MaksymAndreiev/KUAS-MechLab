#include "mbed.h"
#include "hcsr04.h"

AnalogIn sensor0(A0);
AnalogIn sensor1(A1);
AnalogIn sensor2(A2);
AnalogIn sensor3(A3);
AnalogIn sensor4(A4);


PwmOut PWM11(D9); // right wheel
PwmOut PWM12(PA_11_ALT0); // r
PwmOut PWM21(D11); // l
PwmOut PWM22(D12); // l

int obsCount = 0;
int stopCount = 0;

void forward() {
    PWM11.write(0.0f);
    PWM12.write(0.28f);
    PWM21.write(0.34f);
    PWM22.write(0.0f);
}

void forward_obs() {
    PWM11.write(0.0f);
    PWM12.write(1.0f);
    PWM21.write(1.0f);
    PWM22.write(0.0f);
}

void left_obs() {
    PWM11.write(0.0f);
    PWM12.write(1.0f);
    PWM21.write(0.0f);
    PWM22.write(0.0f);
    ThisThread::sleep_for(1ms);
}

void right_obs() {
    PWM11.write(0.0f);
    PWM12.write(0.0f);
    PWM21.write(1.0f);
    PWM22.write(0.0f);
    ThisThread::sleep_for(1ms);
}

void left() {
    PWM11.write(0.0f);
    PWM12.write(0.5f);
    PWM21.write(0.0f);
    PWM22.write(0.0f);
    ThisThread::sleep_for(1ms);
}

void right() {
    PWM11.write(0.0f);
    PWM12.write(0.0f);
    PWM21.write(0.5f);
    PWM22.write(0.0f);
    ThisThread::sleep_for(1ms);
}

void right_rapid() {
    PWM11.write(0.5f);
    PWM12.write(0.0f);
    PWM21.write(0.5f);
    PWM22.write(0.0f);
    ThisThread::sleep_for(1ms);
}

void stop() {
    PWM11.write(0.0f);
    PWM12.write(0.0f);
    PWM21.write(0.0f);
    PWM22.write(0.0f);
}

void avoid() {
    stop();
    ThisThread::sleep_for(1s);
    left_obs();
    ThisThread::sleep_for(150ms);
    stop();
    ThisThread::sleep_for(1s);
    forward_obs();
    ThisThread::sleep_for(300ms);
    stop();
    ThisThread::sleep_for(1s);
    right_obs();
    ThisThread::sleep_for(500ms);
    stop();
    ThisThread::sleep_for(1s);
    left();
    ThisThread::sleep_for(150ms);
}

void avoid2() {
    stop();
    ThisThread::sleep_for(1s);
    left_obs();
    ThisThread::sleep_for(200ms);
    stop();
    ThisThread::sleep_for(1s);
    forward_obs();
    ThisThread::sleep_for(200ms);
    stop();
    ThisThread::sleep_for(1s);
    right_obs();
    ThisThread::sleep_for(400ms);
    stop();
    ThisThread::sleep_for(1s);
    left();
    ThisThread::sleep_for(150ms);
}

int isDetected(AnalogIn sensor) {
    return sensor.read() < 0.6f;
}

int hasAvoided = 0;

int main() {
    HCSR04 usensor(D6, D5);
    PWM11.period(0.01f);
    PWM12.period(0.01f);
    PWM21.period(0.01f);
    PWM22.period(0.01f);

    while (true) {
        usensor.start();
        unsigned int distance = usensor.get_dist_cm();

        if (distance <= 10 && distance > 0 && !hasAvoided) {
            obsCount += 1; // new
            if (obsCount == 2) {
                avoid2();
            } else {
                avoid();
            }
            hasAvoided = 1;
            printf("Obstacle detected. Avoid: %d\n", hasAvoided);
        } else if (hasAvoided) {
            hasAvoided = 0;
            printf("No obstacle. Avoid: %d\n", hasAvoided);

        } else {
            int detected[5];
            detected[0] = isDetected(sensor0);
            detected[1] = isDetected(sensor1);
            detected[2] = isDetected(sensor2);
            detected[3] = isDetected(sensor3);
            detected[4] = isDetected(sensor4);
            int detectedSum = detected[0] + detected[1] + detected[2] + detected[3] + detected[4];


            if (detectedSum == 5) {
                stopCount++;
                if (stopCount == 6) {
                    stopCount = 0;
                    stop();
                    break;
                }
                while (isDetected(sensor0) && isDetected(sensor1) && isDetected(sensor2) && isDetected(sensor3) &&
                       isDetected(sensor4)) {
                    forward();
                }
            } else {
                if ((detected[0] || detected[1]) && !detected[2]) {
                    left();
                } else if (detected[3] || detected[4]) {
                    right_rapid();
                } else if ((detected[3] || detected[4]) && !detected[2]) {
                    right();
                } else {
                    forward();
                }
            }
        }
    }
}
