#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/String.h>
#include <ros/console.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <iomanip>


std_msgs::String output; 

void centre(const sensor_msgs::ImageConstPtr& msg){
    cv_bridge::CvImagePtr raw;
    raw = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    
    cv::Mat gray;
    cv::cvtColor(raw->image, gray, CV_BGR2GRAY);

    cv::threshold(gray,gray,60,255,CV_THRESH_BINARY_INV);

    std::vector<std::vector<cv::Point> > contours;
	cv::findContours(gray.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    std::vector<cv::Moments> sc(contours.size());
    for( size_t i=0;i<contours.size();i++){
        sc[i] = moments( contours[i] );
    output.data= std::to_string(sc[i].m10/(sc[i].m00 + 1e-5)) + "," + std::to_string(sc[i].m01/(sc[i].m00 + 1e-5));
    std::cout<<sc[i].m10/(sc[i].m00 + 1e-5)<<" , "<<sc[i].m01/(sc[i].m00 + 1e-5)<<std::endl;
    }
    return;   

}
int main(int argc, char **argv){
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("/magnus/camera/image_raw",10, centre);
  ros::Publisher pub = nh.advertise<std_msgs::String>("centre_coordinates",10);
  ros::Rate loopRate(30);
  while(ros::ok()){
  	ros::spinOnce();
  	pub.publish(output);
  	loopRate.sleep();
  }
  return 0;
}

