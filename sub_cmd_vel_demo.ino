// Author: Sung Jik Cha
// Credits:
//   http://forum.arduino.cc/index.php?topic=8652.0
//   Dallaby   http://letsmakerobots.com/node/19558#comment-49685
//   Bill Porter  http://www.billporter.info/?p=286
//   bobbyorr (nice connection diagram) http://forum.pololu.com/viewtopic.php?f=15&t=1923

//ROS headers
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#include <ros.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/Twist.h>
#include <ros/time.h>

ros::NodeHandle nh;

struct Point2D {
  double x;
  double z;
};

byte serialVal;
Point2D linear;
Point2D angular;

geometry_msgs::Twist cmd_debug;
ros::Publisher cmd_debug_pub("cmd_debug", &cmd_debug);

void handle_cmd( const geometry_msgs::Twist& cmd_msg) {
  cmd_debug.linear.x = 0;
  cmd_debug.angular.z = 0;
  cmd_debug = cmd_msg;
  
  linear.x = cmd_msg.linear.x;
  angular.z = cmd_msg.angular.z;
  
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", handle_cmd);

void setup() {
 nh.initNode();
 nh.getHardware()->setBaud(9600);
 nh.advertise(cmd_debug_pub);
 nh.subscribe(sub);
 //Serial.begin(9600);

 pinMode(9, OUTPUT);
 pinMode(10, OUTPUT);

}

void loop() {

  nh.spinOnce();
  cmd_debug_pub.publish(&cmd_debug);

  //Low_forward
  if ((linear.x > 0.0 && linear.x <= 0.05) && angular.z == 0.0) {
     analogWrite(9, 127);
     analogWrite(10, 70);
  }

  //Hi_forward
  if (linear.x > 0.05 && angular.z == 0.0) {
     analogWrite(9, 127);
     analogWrite(10, 65);
  }

  //Low_back
  if ((linear.x < 0.0 && linear.x >= -0.05) && angular.z == 0.0) {
    analogWrite(9, 127);
    analogWrite(10, 150);
  }

  //Hi_back
  if (linear.x < -0.05 && angular.z == 0.0) {
    analogWrite(9, 127);
    analogWrite(10, 155);
  }

  //Low_forwardright
  if ((linear.x > 0.01 && linear.x <= 0.05) && angular.z < 0.0) {
      analogWrite(9, 100);
      analogWrite(10, 70);
  }

  //Hi_forwardright
  if ((linear.x > 0.05) && angular.z < 0.0) {
      analogWrite(9, 100);
      analogWrite(10, 65);
  }
  
  //Low_forwardleft
  if ((linear.x > 0.01 && linear.x <= 0.05) && angular.z > 0.0) {
     analogWrite(9, 150);
     analogWrite(10, 70);
  }
  
  //Hi_forwardleft
  if ((linear.x > 0.05) && angular.z > 0.0) {
     analogWrite(9, 150);
     analogWrite(10, 65);
  }

  //Low_right
  if ((linear.x >= 0.0 && linear.x <= 0.01) && (angular.z < 0.0 && angular.z >= -0.05)) {
      analogWrite(9, 70);
      analogWrite(10, 127);
  }
  
  //Hi_right
  if ((linear.x >= 0.0 && linear.x <= 0.01) && angular.z < -0.05) {
      analogWrite(9, 65);
      analogWrite(10, 127);
  }
  
  //Low_left
  if ((linear.x >= 0.0 && linear.x <= 0.01) && (angular.z > 0.0 && angular.z <= 0.05)) {
     analogWrite(9, 160);
     analogWrite(10, 127);
  }
    
  //Hi_left
  if ((linear.x >= 0.0 && linear.x <= 0.01) && angular.z > 0.05) {
     analogWrite(9, 165);
     analogWrite(10, 127);
  }
  
  //stop
  if ((linear.x == 0.0) && (angular.z == 0.0)) {
     analogWrite(9, 127);
     analogWrite(10, 127);
  }

/*
  if (Serial.available() > 0) {
    serialVal = Serial.read();
    serialVal = serialVal - 0x30; // 追加の行
    //Serial.println(serialVal);
    //serialEnum = serialVal;
  }

  //stop
  if (serialVal == 0) {
      analogWrite(9, 127);
      analogWrite(10, 127);
      Serial.println('0');
  }

  //forward
  if (serialVal == 1) {
     analogWrite(9, 127);
     analogWrite(10, 50);
     Serial.println('1');
  }

  //back
  if (serialVal == 2) {
     analogWrite(9, 127);
     analogWrite(10, 170);
     Serial.println('2');
  }

  //forwardright
  if (serialVal == 3) {
     analogWrite(9, 100);
     analogWrite(10, 50);
     Serial.println('3');
  }

  //forwardleft
  if (serialVal == 4) {
     analogWrite(9, 150);
     analogWrite(10, 70);
     Serial.println('4');
  }

  //right
  if (serialVal == 5) {
      //analogWrite(9, 60);
      analogWrite(9, 40);
      analogWrite(10, 127);
      Serial.println('5');
  }

  //left
  if (serialVal == 6) {
      //analogWrite(9, 170);
      analogWrite(9, 190);
      analogWrite(10, 127);
      Serial.println('6');
  }
*/


/*
  //forward
  if ((cmd_debug.linear.x > 0) && (cmd_debug.angular.z == 0)) {
     analogWrite(9, 127);
     analogWrite(10, 72);
  }
  
  //forwardright
  if (((cmd_debug.linear.x == 0) && (cmd_debug.angular.z < 0))
      || ((cmd_debug.linear.x > 0) && (cmd_debug.angular.z < 0))) {
     analogWrite(9, 100);
     analogWrite(10, 72);
  }
  
  //forwardleft
  if (((cmd_debug.linear.x == 0) && (cmd_debug.angular.z > 0))
      || ((cmd_debug.linear.x > 0) && (cmd_debug.angular.z > 0))) {
     analogWrite(9, 150);
     analogWrite(10, 72);
  }
  
  //stop
  if ((cmd_debug.linear.x == 0) && (cmd_debug.angular.z == 0)) {
     analogWrite(9, 127);
     analogWrite(10, 127);
  }
*/

  /*
  //forward
  if ((cmd_debug.linear.x > 0) && (cmd_debug.angular.z == 0)) {
     analogWrite(9, 125);
     analogWrite(10, 83);
  }
  
  //forwardright
  if ((cmd_debug.linear.x > 0) && (cmd_debug.angular.z < 0)) {
     analogWrite(9, 103);
     analogWrite(10, 83);
  }
  
  //forwardleft
  if ((cmd_debug.linear.x > 0) && (cmd_debug.angular.z > 0)) {
     analogWrite(9, 151);
     analogWrite(10, 83);
  }

  
  //right
  if ((cmd_debug.linear.x == 0) && (cmd_debug.angular.z < 0)) {
     analogWrite(9, 53);
     analogWrite(10, 167);
  }
  
  //left
  if ((cmd_debug.linear.x == 0) && (cmd_debug.angular.z > 0)) {
     analogWrite(9, 200);
     analogWrite(10, 167);
  }
  
  //stop
  if ((cmd_debug.linear.x == 0) && (cmd_debug.angular.z == 0)) {
     analogWrite(9, 127);
     analogWrite(10, 127);
  } */
  
  delay(10);
}


