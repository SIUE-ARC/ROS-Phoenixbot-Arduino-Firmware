cmake_minimum_required (VERSION 2.8.8)
set (CMAKE_CXX_STANDARD 11)

include_directories(include/)

#set(CMAKE_TOOLCHAIN_FILE /home/zach/Documents/projects/arc/ROS-Phoenixbot-Arduino-Firmware/cmake/Arduino-CMake-NG/cmake/Arduino-Toolchain.cmake)
#set(ARDUINO_SDK_PATH /home/zach/arduino-1.8.8)
#message(${ARDUINO_SDK_PATH})
#get_board_id(mega_board atmega328)

#add_arduino_executable(phoenixbot.hex ${mega_board} src/phoenixbot.ino)
#upload_arduino_target(phoenixbot.hex "${mega_board}" /dev/ttyACM0)

option(build_tests "Build tests" ON)
if (build_tests)
  add_subdirectory(lib/googletest)
  add_subdirectory(lib/arduino-mock)

  enable_testing()
  add_executable(encoderTests test/encoders.cpp)
  target_link_libraries(encoderTests arduino_mock gtest gmock)

  add_executable(pidTests test/pid.cpp)
  target_link_libraries(pidTests arduino_mock gtest gmock)

  add_executable(parserTests test/parser.cpp)
  target_link_libraries(parserTests arduino_mock gtest gmock)

  find_package(GTest)
  gtest_discover_tests(parserTests)
  gtest_discover_tests(encoderTests)
  gtest_discover_tests(pidTests)

  #add_test(encoderTests encoderTests)
  #add_test(pidTests pidTests)
  #add_test(pidTests parserTests)
endif()

