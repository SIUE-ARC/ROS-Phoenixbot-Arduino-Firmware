#include "arduino-mock/Arduino.h"
#include "gtest/gtest.h"

#include "../src/pid.c"

using ::testing::Return;

class PIDTest : public ::testing::Test {
 protected:
  void SetUp() override {
    accumulated_error[0] = 0;
    accumulated_error[1] = 0;
    pid_time[0] = 0;
    pid_time[1] = 0;
    last_error[0] = 0;
    last_error[1] = 0;
    output[0] = 0;
    output[1] = 0;
  }
};

TEST_F(PIDTest, p_velocity_controller) {
  ArduinoMock* arduinoMock = arduinoMockInstance();

  EXPECT_CALL(*arduinoMock, millis()).Times(4);

  setKp(0, 1);
  setKi(0, 0);
  setKd(0, 0);
  setSetpoint(0, 1);
  arduinoMock->setMillisRaw(100);

  EXPECT_FLOAT_EQ(loopPID(0, 0, 0), 1);
  arduinoMock->addMillisRaw(100);

  EXPECT_FLOAT_EQ(loopPID(0, 1, 0), 1);
  arduinoMock->addMillisRaw(100);

  EXPECT_FLOAT_EQ(loopPID(0, 1, 0), 1);
  arduinoMock->addMillisRaw(100);

  EXPECT_FLOAT_EQ(loopPID(0, 2, 0), 0);

  releaseArduinoMock();
}

float linear(float x) {
  return x * 2;
}

TEST_F(PIDTest, velocity_convergence) {
  ArduinoMock* arduinoMock = arduinoMockInstance();

  EXPECT_CALL(*arduinoMock, millis()).Times(45);

  setKp(0, 0.45);
  setKi(0, 0);
  setKd(0, 0.8);
  arduinoMock->setMillisRaw(0);

  float sensor = 0;
  for (int sp = 10; sp < 100; sp += 10) {
    setSetpoint(0, sp);
    for (int i = 0; i < 5; i++) {
      arduinoMock->addMillisRaw(100);
      float control = loopPID(0, sensor, 0);

      sensor = linear(control);
    }
    EXPECT_NEAR(sensor, sp, 0.1);
  }

  releaseArduinoMock();
}

TEST_F(PIDTest, position_convergence) {
  ArduinoMock* arduinoMock = arduinoMockInstance();

  EXPECT_CALL(*arduinoMock, millis()).Times(45);

  setKp(0, 0.40);
  setKi(0, 0);
  setKd(0, 0);
  arduinoMock->setMillisRaw(0);

  // Modeling a position setpoint
  float sensor = 0;
  for (int sp = 10; sp < 100; sp += 10) {
    setSetpoint(0, 10);
    for (int i = 0; i < 5; i++) {
      arduinoMock->addMillisRaw(100);
      float control = loopPID(0, sensor, 1);

      sensor += linear(control);
    }
    EXPECT_NEAR(sensor, 10, 0.1);
  }

  releaseArduinoMock();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

