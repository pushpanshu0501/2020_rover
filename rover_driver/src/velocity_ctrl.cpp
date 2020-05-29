#include "ros/ros.h"
#include "geometry_msgs/Twist.h" 
#include "std_msgs/Float64.h"

#include <stdlib.h> 

int main(int argc, char **argv) {
      //Initializes ROS, and sets up a node
      ros::init(argc, argv, "velocity_commands");
      ros::NodeHandle nh;

      ros::Publisher pub =nh.advertise<geometry_msgs::Twist>("rover_cmd", 100);

      srand(time(0));
      ros::Rate rate(10);

        while(ros::ok()) {
           //Declares the message to be sent
           geometry_msgs::Twist msg;

           msg.linear.x = 10.00;
           msg.angular.z=0.00;
           pub.publish(msg);
           
         

           //Delays untill it is time to send another message
           rate.sleep();
         }
}