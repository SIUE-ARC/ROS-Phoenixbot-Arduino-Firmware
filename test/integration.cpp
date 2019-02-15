#include <gtest/gtest.h>

#include "arduino-mock/Arduino.h"
#include "arduino-mock/Serial.h"

#include "../src/phoenixbot.ino"

using ::testing::Return;

TEST(commands, parse_motor) {
  ArduinoMock* arduinoMock = arduinoMockInstance();

  releaseArduinoMock();
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

