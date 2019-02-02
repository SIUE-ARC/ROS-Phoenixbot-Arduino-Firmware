#ifndef PID_H
#define PID_H

#include <stdint.h>

void pausePID(uint8_t value);
void setSetpoint(uint8_t channel, float value);
void setKp(uint8_t channel, float value);
void setKi(uint8_t channel, float value);
void setKd(uint8_t channel, float value);
float loopPID(uint8_t channel, float dt, float value, uint8_t position);

#endif
