#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "phoenixbot/pins.h"

// We have to include mocking definitions before source files to stop real
// header files from being included
#include "mock_commands.h"

// We have to include the source file directly to be able to test c modules
#include "../src/parser.c"

class ParserTest : public ::testing::Test {
 protected:
  void SetUp() override {
    mockCommand = new MockCommandModule; 
  }

  void TearDown() override {
    delete mockCommand;
  }
};

TEST_F(ParserTest, rejectUnknown) {
  EXPECT_EQ(parseCommand("FD\r"), UNKNOWN_COMMAND);
  EXPECT_EQ(parseCommand("\r"),   UNKNOWN_COMMAND);
  EXPECT_EQ(parseCommand("\0\r"), UNKNOWN_COMMAND);
}

TEST_F(ParserTest, parseAnalogRead) {
  EXPECT_CALL(*mockCommand, handleAnalog(0));
  EXPECT_CALL(*mockCommand, handleAnalog(1));
  EXPECT_CALL(*mockCommand, handleAnalog(2));
  EXPECT_CALL(*mockCommand, handleAnalog(3));

  EXPECT_EQ(parseCommand("A 0\r"), 0);
  EXPECT_EQ(parseCommand("a 1\r"), 0);
  EXPECT_EQ(parseCommand("A 2\r"), 0);
  EXPECT_EQ(parseCommand("a 3\r"), 0);

  EXPECT_EQ(parseCommand("a -1\r"),  MALFORMED_COMMAND);
  EXPECT_EQ(parseCommand("a 7\r"),   MALFORMED_COMMAND);
  EXPECT_EQ(parseCommand("a 1 7\r"), MALFORMED_COMMAND);
  EXPECT_EQ(parseCommand("a\r"),     MALFORMED_COMMAND);
}

TEST_F(ParserTest, parseDigitalRead) {
  EXPECT_CALL(*mockCommand, handleDigital(0));
  EXPECT_CALL(*mockCommand, handleDigital(1));
  EXPECT_CALL(*mockCommand, handleDigital(2));
  EXPECT_CALL(*mockCommand, handleDigital(3));

  EXPECT_EQ(parseCommand("D 0\r"), 0);
  EXPECT_EQ(parseCommand("d 1\r"), 0);
  EXPECT_EQ(parseCommand("D 2\r"), 0);
  EXPECT_EQ(parseCommand("d 3\r"), 0);

  EXPECT_EQ(parseCommand("d -1\r"),  MALFORMED_COMMAND);
  EXPECT_EQ(parseCommand("d 1 5\r"), MALFORMED_COMMAND);
  EXPECT_EQ(parseCommand("D 7\r"),   MALFORMED_COMMAND);
  EXPECT_EQ(parseCommand("d\r"),     MALFORMED_COMMAND);
}

TEST_F(ParserTest, parseEncoder) {
  EXPECT_CALL(*mockCommand, handleEncoder(0));
  EXPECT_CALL(*mockCommand, handleEncoder(1));
  EXPECT_CALL(*mockCommand, handleEncoder(-1));

  EXPECT_EQ(parseCommand("E 0\r"), 0);
  EXPECT_EQ(parseCommand("e 1\r"), 0);
  EXPECT_EQ(parseCommand("e -1\r"), 0);

  EXPECT_EQ(parseCommand("E -2\r"),  MALFORMED_COMMAND);
  EXPECT_EQ(parseCommand("E 1 3\r"), MALFORMED_COMMAND);
  EXPECT_EQ(parseCommand("e 7\r"),   MALFORMED_COMMAND);
  EXPECT_EQ(parseCommand("e\r"),     MALFORMED_COMMAND);
}


TEST_F(ParserTest, parseSolenoid) {
  EXPECT_CALL(*mockCommand, handleSolenoid(0, 1));
  EXPECT_CALL(*mockCommand, handleSolenoid(0, 0));
  EXPECT_CALL(*mockCommand, handleSolenoid(1, 0));
  EXPECT_CALL(*mockCommand, handleSolenoid(1, 1));

  EXPECT_EQ(parseCommand("S 0 1\r"), 0);
  EXPECT_EQ(parseCommand("s 0 0\r"), 0);
  EXPECT_EQ(parseCommand("S 1 0\r"), 0);
  EXPECT_EQ(parseCommand("S 1 1\r"), 0);

  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("S 1 5\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("S -1 1\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("S 1\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("s -3\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("s 874\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("s\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("s 1 1 4\r"));
}

TEST_F(ParserTest, parseHalt) {
  EXPECT_CALL(*mockCommand, handleHalt(0)).Times(2);
  EXPECT_CALL(*mockCommand, handleHalt(1)).Times(2);

  EXPECT_EQ(parseCommand("H 0\r"), 0);
  EXPECT_EQ(parseCommand("H 1\r"), 0);
  EXPECT_EQ(parseCommand("h 0\r"), 0);
  EXPECT_EQ(parseCommand("h 1\r"), 0);

  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("H\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("H 17\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("H 8 1 2311\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("H -3\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("h 874\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("h\r"));
}

TEST_F(ParserTest, parseSimon) {
  EXPECT_CALL(*mockCommand, handleSimon(0)).Times(2);
  EXPECT_CALL(*mockCommand, handleSimon(1)).Times(2);

  EXPECT_EQ(parseCommand("N 0\r"), 0);
  EXPECT_EQ(parseCommand("N 1\r"), 0);
  EXPECT_EQ(parseCommand("n 0\r"), 0);
  EXPECT_EQ(parseCommand("n 1\r"), 0);

  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("N\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("N 17\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("n 8 1 2311\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("n 1 2\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("N -3\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("N 874\r"));
  EXPECT_EQ(MALFORMED_COMMAND, parseCommand("N\r"));
}

//TEST_F(ParserTest, parsePWM) {
//}

//TEST_F(ParserTest, parseMotor) {
//}

//TEST_F(ParserTest, parsePID) {
//}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

