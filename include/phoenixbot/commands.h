#ifndef COMMANDS_H
#define COMMANDS_H

#ifdef ARDUINO
  #include <stdint.h>
#endif


int handleAnalog(uint8_t channel);
int handleEncoder(int8_t channel);
int handleDigital(uint8_t channel);
int handleSolenoid(uint8_t channel, uint8_t value);
int handleHalt(uint8_t value);
int handleSimon(uint8_t value);
int handlePID(uint8_t channel, char pid_property, float value);
int handlePWM(uint8_t channel, int value);
int handleMotor(uint8_t channel, int value);
int handleServo(uint8_t buttonPress);

#endif
