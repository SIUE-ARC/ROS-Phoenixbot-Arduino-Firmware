#ifdef ARDUINO
  #include "pid.h"
  #include "Arduino.h"
#else
  #include "phoenixbot/pid.h"
#endif

// Tunables
float kp[] = {0.0025,0.0025};
float ki[] = {0.0004,0.00042,0.0};
float kd[] = {0,0};
uint32_t DT = 2e4;

// State
float last_error[]        = {0, 0};
float accumulated_error[] = {0, 0};
long pid_time[] = {0, 0};
float output[] = {0, 0};

// Goal
float setpoint[] = {0,0};

void setSetpoint(uint8_t channel, float value) {
  setpoint[channel] = value;
}
void setKp(uint8_t channel, float value) {
  kp[channel] = value;
}
void setKi(uint8_t channel, float value) {
  ki[channel] = value;
}2
void setKd(uint8_t channel, float value) {
  kd[channel] = value;
}

void pausePID(uint8_t channel) {
  accumulated_error[0] = 0;
  accumulated_error[1] = 0;
  pid_time[0] = 0;
  pid_time[1] = 0;
  last_error[0] = 0;
  last_error[1] = 0;
  output[0] = 0;
}

float loopPID(uint8_t channel, float dt, float measured, uint8_t position) {
  float control;

  const float error = setpoint[channel] - measured;
  const float de_dt = (float)( error - last_error[channel] ) / dt;
  last_error[channel] = error;

  //Serial.println(error);

  accumulated_error[channel] += error * dt;

  last_error[channel] = error;
  
  control = 
      kp[channel] * error
    + ki[channel] * accumulated_error[channel]
    + kd[channel] * de_dt;

  if (position) {
    output[channel] = control;
  } else {
    output[channel] += control;
  }

  output[channel] = output[channel] > 500.0f ? 500.0f : output[channel];

  return output[channel];
}
