# ROS-Phoenixbot-Arduino-Firmware

Check main PhoenixBot  wiki for Arduino Commands (https://github.com/SIUE-ARC/phoenixbot/wiki)

## Commands
// Analog read
// Usage: A analog_channel

// PID write
// Usage: C pid_id pid_value new_value
// pid_value:
//   p: kp
//   i: ki
//   d: kd
//   s: setpoint
//   t: DT
//
// Encoder read
// Reads the encoder count and last velocity of the requested encoder
// Usage: E encoder_id
// -1 reads both values
     
// PWM write
// Usage: P pwm_channel pwm_value
// pwm is dumped straight into analog write. Not a servo pwm
     
// Solenoid write
// Sets the state of a solenoid
// Usage: S solenoid_id state

// Digital read
// Usage: D digital_channel

// Motor write
// Usage: M motor_id motor_speed
// motor speed is used as an offset from ZEROPOINT writeMicroseconds
        
// Halt
// Immediately stop the robot and reset PID
// Usage: H state

// Simon control
// Move the simon arm up or down
// Usage: N state

## Running tests
```
mkdir build
cd build
cmake ..
make
make test
```
