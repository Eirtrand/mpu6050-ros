# sensor_interface
This package provides a interface between arduino, ros and the mpu6050 imu. The sensor is read from an Arduino board, which acts as a ROS node by means of `rosserial_arduino`.

## Running the code
* Build and upload the Arduino code
* Run a translator node on the host
`rosrun rosserial_python serial_node.py /dev/ttyUSB0`
(Note: May also be `/dev/ttyACM0` or something else.)

## Building and uploading the code
* Build the package
`catkin_make` or `catkin_make mpu6050_ros_firmware_mpu6050_ros`
* Upload to Arduino
`catkin_make mpu6050_ros_firmware_mpu6050_ros-upload`
Make sure that the correct Arduino board and serial port is specified in `firmware/CMakeLists.txt`.

## Dependencies
* [rosserial](http://wiki.ros.org/rosserial)
`sudo apt-get install ros-kinetic-rosserial`
* [rosserial_arduino](http://wiki.ros.org/rosserial_arduino)
`sudo apt-get install ros-kinetic-rosserial-arduino`

## Tested 
 Some problems accured when running on arduino nano(ATmega328(p)). It works on arduino mega(ATmega2560). on the host side its been tested together with the jetson tx1
<!-- ## Notes -->



