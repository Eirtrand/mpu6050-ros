cmake_minimum_required(VERSION 2.8.3)

include_directories(${ROS_LIB_DIR})

# Remove this if using an Arduino without native USB (eg, other than Leonardo)
# add_definitions(-DUSB_CON)

generate_arduino_firmware(mpu6050_ros
    SRCS mpu6050_ros.cpp I2Cdev.cpp ${ROS_LIB_DIR}/time.cpp
#     HDRS Adafruit_BNO055.h
    #BOARD atmega328
    #PORT /dev/ttyUSB0
    BOARD mega2560
    PORT /dev/ttyACM0
)
