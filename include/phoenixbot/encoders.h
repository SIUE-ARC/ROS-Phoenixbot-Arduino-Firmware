#ifndef ENCODERS_H
#define ENCODERS_H

#include <stdint.h>

void attachEncoderInterrupts();
long encoderCount(const uint8_t id);
float encoderVelocity(const uint8_t id);
void zeroEncoder(const uint8_t id);
void updateEncoders(float dt);

#endif
