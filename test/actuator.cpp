#include "arduino-mock/Arduino.h"
#include "gtest/gtest.h"

#include "phoenixbot/pins.h"


#define digitalPinToInterrupt(x) x
#include "../src/actuators.c"

using ::testing::Return;

class ActuatorTest : public ::testing::Test {
 protected:
  void SetUp() override { }
};


TEST_F(ActuatorTest, a) {
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

