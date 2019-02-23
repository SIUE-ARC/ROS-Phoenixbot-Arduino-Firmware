#ifdef ARDUINO
  #include "commands.h"
  #include "pins.h"
  #include "actuators.h"
  #include "pid.h"
  #include "encoders.h"
#else
  #include "phoenixbot/commands.h"
  #include "phoenixbot/pins.h"
  #include "phoenixbot/actuators.h"
  #include "phoenixbot/pid.h"
#endif

int handleHalt(uint8_t value) {
  stopActuators(value);
  pausePID(value);
  return 0;
}

int handlePID(uint8_t channel, char pid_property, float value) {
  switch (pid_property) {
    case 'P':
    case 'p':
      setKp(channel, value);
      break;
    case 'I':
    case 'i':
      setKi(channel, value);
      break;
    case 'D':
    case 'd':
      setKd(channel, value);
      break;
    case 'S':
    case 's':
      setSetpoint(channel, value);
      break;
      

  }
  return 0;
}

// Inputs
int handleAnalog(uint8_t channel) {
  // TODO Print to serial
  analogRead(analog[channel]);
}

int handleEncoder(int8_t channel) {
  if (channel == -1) {
    for(uint8_t i = 0; i < ENCODER_COUNT; i++)
      handleEncoder(i);
    return 0;
  }
      
  Serial.print(encoderVelocity(channel));
  Serial.print(" ");
  Serial.println(encoderCount(channel));
  return 0;
}

int handleDigital(uint8_t channel) {
  // TODO Print to serial
  digitalRead(digital[channel]);
  return 0;
}

// Outputs
int handleSolenoid(uint8_t channel, uint8_t value) {
  writeSolenoid(channel, value);
  return 0;
}

int handleSimon(uint8_t value) {
}

int handlePWM(uint8_t channel, int value) {
  writePWM(channel, value);
  return 0;
}

int handleMotor(uint8_t channel, int value) {
  writeServo(channel, value);
  return 0;
}

int handleServo(uint8_t buttonPress)
{
  switch(buttonPress)
  {
    case 0:
      pauseServo(7);
      pauseServo(6);
      break;
    case 1:
      writeServo(7,500);
      break;
    case 2:
      writeServo(7,-500);
      break;
    case 3:
      writeServo(6,500);
      break;
    case 4:
      writeServo(6,-500);
      break;
    default:
      pauseServo(6);
      pauseServo(7);
      break;
  }
  
}
