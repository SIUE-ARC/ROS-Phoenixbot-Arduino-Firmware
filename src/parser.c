#ifdef ARDUINO
  #include "parser.h"
  #include "commands.h"
  #include "pins.h"
#else
  #include "phoenixbot/parser.h"
  #include "phoenixbot/commands.h"
#endif

int parseCommand(const char* buffer)
{
  const char command = buffer[0];
  const char* arguments = buffer + 2;
  int n;

  switch(command)
  {
    // Analog read: A analog_channel
    case 'A':
    case 'a':
    {
      uint8_t channel;
      
      if (sscanf(arguments, "%hhu%n", &channel, &n) != 1) return MALFORMED_COMMAND;
      if (channel < 0 || channel >= ANALOG_COUNT) return MALFORMED_COMMAND;
      if (arguments[n] != '\r') return MALFORMED_COMMAND;

      return handleAnalog(channel);
    }
          
    // Set PID: C pid_channel pid_property new_value
    case 'C':
    case 'c':
    {
      uint8_t pid_channel;
      char pid_property;
      long value;

      if (sscanf(arguments, "%hhu %c %ld%n", &pid_channel, &pid_property, &value, &n) != 3) return MALFORMED_COMMAND;
      // TODO Validate arguments

      return handlePID(pid_channel, pid_property, value / 1000);
    }

    // Digital read: D digital_channel
    case 'D':
    case 'd':
    {
      uint8_t channel;
            
      if (sscanf(arguments, "%hhu%n", &channel, &n) != 1) return MALFORMED_COMMAND;
      if (channel < 0 || channel >= DIGITAL_COUNT)    return MALFORMED_COMMAND;
      if (arguments[n] != '\r') return MALFORMED_COMMAND;

      return handleDigital(channel);
    }
       
    // Encoder read: E encoder (-1 for all)
    case 'E':
    case 'e':
    {
      int8_t channel; 

      if (sscanf(arguments, "%hhd%n", &channel, &n) != 1) return MALFORMED_COMMAND;
      if (channel < -1 || channel >= ENCODER_COUNT)   return MALFORMED_COMMAND;
      if (arguments[n] != '\r') return MALFORMED_COMMAND;

      return handleEncoder(channel);
    }

    // Halt: H halt_state
    case 'H':
    case 'h':
    {
      uint8_t value;

      if (sscanf(arguments, "%hhd%n", &value, &n) != 1) return MALFORMED_COMMAND;
      if (value < 0 || value > 1) return MALFORMED_COMMAND;
      if (arguments[n] != '\r') return MALFORMED_COMMAND;

      return handleHalt(value);
    }

    // Motor write: M channel value (value is fixed point decimal
    case 'M':
    case 'm':
    {
      uint8_t channel;
      int16_t value;
          
      if (sscanf(arguments, "%hhd %hd%n", &channel, &value, &n) != 2) return MALFORMED_COMMAND;
      if (channel < 0 || channel > SERVO_COUNT || value < -500 || value > 500) return MALFORMED_COMMAND;
      if (arguments[n] != '\r') return MALFORMED_COMMAND;

      return handleMotor(channel, value);
    }

    // Simon write: N simon_state
    case 'N':
    case 'n':
    {
      uint8_t value;

      if (sscanf(arguments, "%hhd%n", &value, &n) != 1) return MALFORMED_COMMAND;
      if (value < 0 || value > 1) return MALFORMED_COMMAND;
      if (arguments[n] != '\r') return MALFORMED_COMMAND;

      return handleSimon(value);
    }
           
    // PWM write: P pwm_channel value (value is fixed point decimal)
    case 'P':
    case 'p':
    {
      uint8_t channel;
      uint16_t value;

      if (sscanf(arguments, "%hhd %hu%n", &channel, &value, &n) != 2) return MALFORMED_COMMAND;
      if (channel < 0 || channel > PWM_COUNT || value < 0 || value > 255) return MALFORMED_COMMAND;
      if (arguments[n] != '\r') return MALFORMED_COMMAND;
      return handlePWM(channel, value);
    }

    case 'S':
    case 's':
    {
      uint8_t channel;
      uint8_t value;
          
      if (sscanf(arguments, "%hhd %hhd%n", &channel, &value, &n) != 2) return MALFORMED_COMMAND;
      if (channel < 0 || channel > SOLENOID_COUNT || value < 0 || value > 1) return MALFORMED_COMMAND;
      if (arguments[n] != '\r') return MALFORMED_COMMAND;
      return handleSolenoid(channel, value);
    }
    case 'v':
    case 'V':
    {
      uint8_t buttonPress;
      // 0-3
      Serial.print("Hello");
      if(sscanf(arguments, "%hhd%n",&buttonPress,&n) != 1); return MALFORMED_COMMAND;
      Serial.print("hello");
      //if (!(buttonPress >= 0 || buttonPress < 5)) return MALFORMED_COMMAND;
      //if (arguments[n] != '\r')  return MALFORMED_COMMAND;
      return handleServo(buttonPress);
    } 

    default:
      return UNKNOWN_COMMAND;
  }
}
