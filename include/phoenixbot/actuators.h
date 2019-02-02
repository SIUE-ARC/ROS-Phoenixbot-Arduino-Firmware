#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <stdint.h>

//#define SERVO_ZERO 1500
//#define SERVO_RANGE 500

void setupServos();
void pauseServo(uint8_t channel);
void writeServo(uint8_t channel, float value);
void writePWM(uint8_t channel, uint8_t value);
void writeSolenoid(uint8_t channel, uint8_t value);
void stopActuators(uint8_t value);

#endif
