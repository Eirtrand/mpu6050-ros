#include <ros.h>
#include <std_msgs/String.h>
#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <string.h>
#include <sensor_msgs/Imu.h>
//#include <time.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13


ros::NodeHandle nh;
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

bool blinkState = false;



sensor_msgs::Imu data_out;
ros::Publisher imu_publisher("mpu_6050",&data_out);


const double limg = 1000;  // used to convert rotational accel to deg/s
const double lima = 2*9.8; 
 MPU6050 imu;



std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
char hello[13] = "hello world!";




void setup()
{
  nh.initNode();
  nh.advertise(imu_publisher);
  nh.advertise(chatter);

    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    imu.initialize();
    accelgyro.initialize();
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{

      str_msg.data = hello;
  chatter.publish( &str_msg );
    imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

   //data_out.header.stamp = ros::Time::now();  // time stamp the measurement

    data_out.linear_acceleration.x = (double)((ax+32767)*2*lima)/65534;  // acc
    data_out.linear_acceleration.y = (double)((ay+32767)*2*lima)/65534;
    data_out.linear_acceleration.z = (double)((az+32767)*2*lima)/65534;

    data_out.angular_velocity.x = (double)((gx+32767)*2*limg)/65534*3.1415926/180;  // gyro
    data_out.angular_velocity.y = (double)((gy+32767)*2*limg)/65534*3.1415926/180;
    data_out.angular_velocity.z = (double)((gz+32767)*2*limg)/65534*3.1415926/180;



  imu_publisher.publish(&data_out);
  nh.spinOnce();
  delay(1);

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}

