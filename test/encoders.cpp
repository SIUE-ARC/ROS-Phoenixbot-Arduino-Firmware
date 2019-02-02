#include "arduino-mock/Arduino.h"
#include "gtest/gtest.h"

#include "phoenixbot/pins.h"


#define digitalPinToInterrupt(x) x
#include "../src/encoders.c"

using ::testing::Return;

class EncoderTest : public ::testing::Test {
 protected:
  void SetUp() override { }
};


TEST_F(EncoderTest, count_up) {
  ArduinoMock* arduinoMock = arduinoMockInstance();

  EXPECT_CALL(*arduinoMock, digitalRead(encoder[0]))
      .WillOnce(Return(1))
      .WillOnce(Return(1))
      .WillOnce(Return(0))
      .WillOnce(Return(0))
    ;
  EXPECT_CALL(*arduinoMock, digitalRead(encoder[1]))
      .WillOnce(Return(0))
      .WillOnce(Return(1))
      .WillOnce(Return(1))
      .WillOnce(Return(0))
    ;

  zeroEncoder(0);
  EXPECT_EQ(encoderCount(0), 0);

  encoder00_ISR();
  EXPECT_EQ(encoderCount(0), 1);
  encoder01_ISR();
  EXPECT_EQ(encoderCount(0), 2);
  encoder00_ISR();
  EXPECT_EQ(encoderCount(0), 3);
  encoder01_ISR();
  EXPECT_EQ(encoderCount(0), 4);

  releaseArduinoMock();
}

TEST_F(EncoderTest, count_down) {
  ArduinoMock* arduinoMock = arduinoMockInstance();

  EXPECT_CALL(*arduinoMock, digitalRead(encoder[0]))
      .WillOnce(Return(0))
      .WillOnce(Return(1))
      .WillOnce(Return(1))
      .WillOnce(Return(0))
    ;
  EXPECT_CALL(*arduinoMock, digitalRead(encoder[1]))
      .WillOnce(Return(1))
      .WillOnce(Return(1))
      .WillOnce(Return(0))
      .WillOnce(Return(0))
    ;

  zeroEncoder(0);
  EXPECT_EQ(encoderCount(0), 0);

  encoder01_ISR();
  EXPECT_EQ(encoderCount(0), -1);
  encoder00_ISR();
  EXPECT_EQ(encoderCount(0), -2);
  encoder01_ISR();
  EXPECT_EQ(encoderCount(0), -3);
  encoder00_ISR();
  EXPECT_EQ(encoderCount(0), -4);

  releaseArduinoMock();
}

TEST_F(EncoderTest, count_up_and_down) {
  ArduinoMock* arduinoMock = arduinoMockInstance();

  EXPECT_CALL(*arduinoMock, digitalRead(encoder[0]))
      .WillOnce(Return(1))
      .WillOnce(Return(1))

      .WillOnce(Return(1))
      .WillOnce(Return(0))
    ;
  EXPECT_CALL(*arduinoMock, digitalRead(encoder[1]))
      .WillOnce(Return(0))
      .WillOnce(Return(1))

      .WillOnce(Return(0))
      .WillOnce(Return(0))
    ;

  zeroEncoder(0);
  EXPECT_EQ(encoderCount(0), 0);

  encoder00_ISR();
  EXPECT_EQ(encoderCount(0), 1);
  encoder01_ISR();
  EXPECT_EQ(encoderCount(0), 2);

  encoder01_ISR();
  EXPECT_EQ(encoderCount(0), 1);
  encoder00_ISR();
  EXPECT_EQ(encoderCount(0), 0);

  releaseArduinoMock();
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

