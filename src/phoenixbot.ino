#include <stdint.h>

#ifdef ARDUINO
  #include "actuators.h"
  #include "commands.h"
  #include "encoders.h"
  #include "parser.h"
  #include "pid.h"
  #include "pins.h"
#else
  #include "phoenixbot/actuators.h"
  #include "phoenixbot/commands.h"
  #include "phoenixbot/encoders.h"
  #include "phoenixbot/parser.h"
  #include "phoenixbot/pid.h"
  #include "phoenixbot/pins.h"
#endif

#define BUFF_SIZE 64

// FRONT RIGHT MOTOR Third From Back
// FRONT LEFT MOTOR  4th
// BACK RIGHT MOTOR  Farthest back
// BACK LEFT MOTOR   Second From Back

// FRONT RIGHT MOTOR 2
// FRONT LEFT MOTOR  1
// BACK RIGHT MOTOR  4
// BACK LEFT MOTOR   3

void buffer_Flush(char *ptr);
void handleCommands();

char rcv_buffer[BUFF_SIZE];

void setup()
{
  Serial.begin(1000000);

#ifdef ARDUINO
  // According to the arduino source files, this evaluates to a constant false
  while(!Serial);
#endif
  Serial.println("Beep boop, I am a robot.");

  attachEncoderInterrupts();
  setupServos();

  buffer_Flush(rcv_buffer);
}

long last_t = 0;

void loop()
{
    long t = micros();
    handleCommands();

    if (t - last_t > 2e4) {
      float dt = (t - last_t) / 1e6;
      updateEncoders(dt);
      
      float left_drive = loopPID(0, dt, encoderVelocity(LEFT_DRIVE_ENCODER), 0);
      writeServo(LEFT_DRIVE_MOTOR_A, left_drive);
      writeServo(LEFT_DRIVE_MOTOR_B, left_drive);

      float right_drive = loopPID(1, dt, encoderVelocity(RIGHT_DRIVE_ENCODER), 0);
      writeServo(RIGHT_DRIVE_MOTOR_A, right_drive);
      writeServo(RIGHT_DRIVE_MOTOR_B, right_drive);


      last_t = t;
    }

    // Run PID loops
    //float left_drive  = loopPID(0, encoderVelocity(LEFT_DRIVE_ENCODER), 0);
    //float right_drive = loopPID(1, encoderVelocity(RIGHT_DRIVE_ENCODER), 0);
    //float simon_motor = loopPID(2, analogRead(SIMON_POT), 1);

    //writeServo(LEFT_DRIVE_MOTOR_B, left_drive);

    //writeServo(RIGHT_DRIVE_MOTOR_A, right_drive);
    //writeServo(RIGHT_DRIVE_MOTOR_B, right_drive);

    //writeServo(SIMON_MOTOR, simon_motor);
}


void buffer_Flush(char *ptr)
{
  for(int i = 0; i < BUFF_SIZE; i++)
  {
    ptr[i] = 0;
  }
}

void handleCommands()
{
  static byte index = 0;
  char terminator = '\r';
  while(Serial.available() > 0)
  {
    rcv_buffer[index] = Serial.read();
    if(rcv_buffer[index] == terminator)
    {
      index = 0;
      uint8_t success = parseCommand(rcv_buffer);
      if (success == UNKNOWN_COMMAND) Serial.println("Serial Error: Unknown command");
      if (success == MALFORMED_COMMAND) Serial.println("Serial Error: Malformed command");
      buffer_Flush(rcv_buffer);
    }
    else
    {
      index++;
      if(index >= 64)
      {
        Serial.println("buffer overflow");
        index = 0;
        buffer_Flush(rcv_buffer);
      }
    }
  }

}
