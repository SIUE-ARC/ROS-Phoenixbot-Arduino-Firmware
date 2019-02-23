#ifndef PINS_H
#define PINS_H

#include <stdint.h>

#ifdef ARDUINO
  #include <Arduino.h>
#else
//  #define A0 0
//  #define A1 1
//  #define A2 2
//  #define A3 3
//  #define A4 4
#endif


// THESE ARE MESSING THINGS UP BECAUSE THEY GET COMPILED INTO MULTIPLE OBJECTS
const static uint8_t pwm[]      = {2,3,4,5,6,7,11,12,13,44,45,46};
const static uint8_t solenoid[] = {39,40,41,42,43,44};
const static uint8_t analog[]   = {};//A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15};
//const uint8_t analog[]   = {A0,A1,A2,A3,A4};
const static uint8_t digital[]  = {22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
const static uint8_t encoder[]  = {19, 18, 20, 21};
const static uint8_t servos[]   = {13, 12, 11, 10, 9, 8,6,7};

#define ANALOG_COUNT 5
#define DIGITAL_COUNT 5
#define PWM_COUNT      12
#define SERVO_COUNT     8
#define SOLENOID_COUNT  6
#define ENCODER_COUNT  2

#define RED_SOLENOID    solenoid[0]
#define YELLOW_SOLENOID solenoid[1]
#define GREEN_SOLENOID  solenoid[2]
#define BLUE_SOLENOID   solenoid[3]

#define RED_LIGHT    analog[0]
#define YELLOW_LIGHT analog[1]
#define GREEN_LIGHT  analog[2]
#define BLUE_LIGHT   analog[3]
#define SIMON_POT    analog[4]

#define ESTOP digital[0]

#define LEFT_DRIVE_MOTOR_A 2
#define LEFT_DRIVE_MOTOR_B  1

#define RIGHT_DRIVE_MOTOR_A 3
#define RIGHT_DRIVE_MOTOR_B  0



#define SIMON_MOTOR         servos[5]

#define LEFT_DRIVE_ENCODER 0
#define RIGHT_DRIVE_ENCODER 1

#endif
