#define SERVO_ZERO 1500
#define SERVO_RANGE 500

#ifdef ARDUINO
  #include <Servo.h>

  #include "actuators.h"
  #include "pins.h"

#else
  #include "phoenixbot/actuators.h"
#endif

//#define SERIAL_DEBUG


Servo _servos[6];
uint8_t stopped = 0;

void setupServos() {
  if (stopped) return;
  for(int i = 0; i < SERVO_COUNT; i++) {
    _servos[i].attach(servos[i]);
    writeServo(i, 0);
  }
}

void pauseServo(uint8_t channel) {
  writeServo(channel, SERVO_ZERO);
  _servos[channel].detach();
}

void writeServo(uint8_t channel, float value) {
  if (stopped) value = 0;
  value = SERVO_ZERO + value;

#ifdef SERIAL_DEBUG
  Serial.print("WRITING:");
  Serial.print(value);
  Serial.print(" to ");
  Serial.println(servos[channel]);
#endif
  
  _servos[channel].writeMicroseconds(value);
}

void writePWM(uint8_t channel, uint8_t value) {
  if (stopped) value = 0;

#ifdef SERIAL_DEBUG
  Serial.print("WRITING:");
  Serial.print(value);
  Serial.print(" to ");
  Serial.println(pwm[channel]);
#endif
  
  analogWrite(pwm[channel], value);
}

void writeSolenoid(uint8_t channel, uint8_t value) {
  if (stopped) value = 0;

#ifdef SERIAL_DEBUG
  Serial.print("WRITING:");
  Serial.print(value);
  Serial.print(" to ");
  Serial.println(solenoid[channel]);
#endif

  digitalWrite(solenoid[channel], value);
}

void stopActuators(uint8_t value) {
  if (value) {
    stopped = 1;
    for (int i = 0; i < SERVO_COUNT; i++)
      pauseServo(i);
    for (int i = 0; i < SOLENOID_COUNT; i++)
      writeSolenoid(i, 0);
    for (int i = 0; i < PWM_COUNT; i++)
      writePWM(i, 0);
  } else {
    setupServos();
  }
}
