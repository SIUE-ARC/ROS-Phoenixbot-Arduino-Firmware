#ifdef ARDUINO
  #include "encoders.h"
  #include "pins.h"
  #include <Arduino.h>
#else
  #include "phoenixbot/encoders.h"
  #include "phoenixbot/pins.h"
#endif

#define ENCODER_ISR(id, channel) void encoder##id##channel##_ISR() { \
  encoderISR(id, channel); \
}

volatile long _encoderCount[] = {0, 0};
float _velocity[] = {0, 0};
long _last[] = {0, 0};

void updateEncoders(float dt) {
  for (int i = 0; i <= 1; i++) {
    _velocity[i] = (_encoderCount[i] - _last[i]) / dt;
    _last[i] = _encoderCount[i];
  }
}

float encoderVelocity(const uint8_t id) {
  return _velocity[id];
}

long encoderCount(const uint8_t id) {
  return _encoderCount[id];
}

void zeroEncoder(const uint8_t id) {
  _encoderCount[id] = 0;
}

// CW  (@A, A != B; @B, A == B)
// A _/‾‾‾\___/‾‾‾\___
// B ___/‾‾‾\___/‾‾‾\__
//
// CCW (@A, A == B; @B, A != B)
// A ___/‾‾‾\___/‾‾‾\___
// B _/‾‾‾\___/‾‾‾\__
void encoderISR(const char id, const char channel) {
  const char a = digitalRead(encoder[id * 2]);
  const char b = digitalRead(encoder[id * 2 + 1]);

  const char a_edge = (channel == 0) ? 1 : -1;
  const char b_edge = (channel << 1) - 1;

  // If A != B, then CW if on A edge or CCW if on B edge
  if (a != b)
    _encoderCount[id] += a_edge;

  // If A == B, then CCW if on A edge or CW if on B edge
  else
    _encoderCount[id] -= a_edge;
}

/******* SETUP INTERRUPTS *******/

ENCODER_ISR(0, 0);
ENCODER_ISR(0, 1);
ENCODER_ISR(1, 0);
ENCODER_ISR(1, 1);

void attachEncoderInterrupts() {
  attachInterrupt(digitalPinToInterrupt(encoder[0]), encoder00_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder[1]), encoder01_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder[2]), encoder10_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder[3]), encoder11_ISR, CHANGE);
}
