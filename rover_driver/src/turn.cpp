#include "ros/ros.h"
#include "geometry_msgs/Twist.h" 
#include "std_msgs/Float64.h"

#include <stdlib.h> 
double angular_z;

int main(int argc, char **argv) {
      //Initializes ROS, and sets up a node
      ros::init(argc, argv, "turn_commands");
      ros::NodeHandle nh;
      const double  PI = 3.1415926535897;
 
      std::cout<<"Entre you turn angle: ";
      std::cin>>angular_z;

      double angle = angular_z*PI/180;

      ros::Publisher pub1=nh.advertise<std_msgs::Float64>("rover/corner_lf_wheel_lf_controller/command", 100);
      ros::Publisher pub2=nh.advertise<std_msgs::Float64>("rover/bogie_left_wheel_lm_controller/command", 100);
      ros::Publisher pub3=nh.advertise<std_msgs::Float64>("rover/corner_lb_wheel_lb_controller/command", 100);
      ros::Publisher pub4=nh.advertise<std_msgs::Float64>("rover/corner_rb_wheel_rb_controller/command", 100);  
      ros::Publisher pub5=nh.advertise<std_msgs::Float64>("rover/bogie_right_wheel_rm_controller/command", 100);
      ros::Publisher pub6=nh.advertise<std_msgs::Float64>("rover/corner_rf_wheel_rf_controller/command", 100);

      srand(time(0));

      ros::Rate rate(10);

      while(ros::ok()) {
           //Declares the message to be sent
           std_msgs::Float64 msg1;
           std_msgs::Float64 msg2;

           msg1.data = angle*10;
           msg2.data = angle*10;

           //Publish the message
           pub1.publish(msg1);
           pub2.publish(msg1);
           pub3.publish(msg1);
           pub4.publish(msg2);
           pub5.publish(msg2);
           pub6.publish(msg2);

           //Delays untill it is time to send another message
           rate.sleep();
        }
}