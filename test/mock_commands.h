#ifndef COMMANDS_H
#define COMMANDS_H

#include "gmock/gmock.h"

// This file is really ugly, but its the only way we can inject mock interfaces
// for c modules. This header pretends to be the real commands.h header, references
// the same functions, but redirects them to a google mock object instead of
// the real code.

class MockCommandModule {
  public:
    MOCK_METHOD1(handleAnalog   ,int(uint8_t));
    MOCK_METHOD1(handleEncoder  ,int(uint8_t));
    MOCK_METHOD1(handleDigital  ,int(uint8_t));
    MOCK_METHOD2(handleSolenoid ,int(uint8_t, uint8_t));
    MOCK_METHOD1(handleHalt     ,int(uint8_t));
    MOCK_METHOD1(handleSimon    ,int(uint8_t));
    MOCK_METHOD3(handlePID      ,int(uint8_t, char, int));
    MOCK_METHOD2(handlePWM      ,int(uint8_t, int));
    MOCK_METHOD2(handleMotor    ,int(uint8_t, int));
};

MockCommandModule* mockCommand;

int handleAnalog(uint8_t channel) {
  mockCommand->handleAnalog(channel);
}

int handleEncoder(uint8_t channel) {
  mockCommand->handleEncoder(channel);
}

int handleDigital(uint8_t channel) {
  mockCommand->handleDigital(channel);
}

int handleSolenoid(uint8_t channel, uint8_t value) {
  mockCommand->handleSolenoid(channel, value);
}

int handleHalt(uint8_t value) {
  mockCommand->handleHalt(value);
}

int handleSimon(uint8_t value) {
  mockCommand->handleSimon(value);
}

int handlePID(uint8_t channel, char pid_property, int value) {
  mockCommand->handlePID(channel, pid_property, value);
}

int handlePWM(uint8_t channel, int value) {
  mockCommand->handlePWM(channel, value);
}

int handleMotor(uint8_t channel, int value) {
  mockCommand->handleMotor(channel, value);
}

#endif

