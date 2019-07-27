#include "opencv2/opencv.hpp"
#include <iostream>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#define CAM_DEBUG 0

cv::Mat rgbMat;
bool rgbReceive = false;

void rgbCallback(const sensor_msgs::ImageConstPtr &msg_rgb) 
{
	cv_bridge::CvImagePtr rgbPtr = cv_bridge::toCvCopy(*msg_rgb, sensor_msgs::image_encodings::TYPE_8UC3);
    rgbMat = rgbPtr->image.clone();
    
    rgbReceive = true;
}


int main(int argc, char** argv){

    std::cout << "OpenCV version : " << CV_VERSION << std::endl;
    std::cout << "Major version : " << CV_MAJOR_VERSION << std::endl;
    std::cout << "Minor version : " << CV_MINOR_VERSION << std::endl;
    std::cout << "Subminor version : " << CV_SUBMINOR_VERSION << std::endl;

    ros::init(argc, argv, "ImageProcess");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber rgb_sub;

    rgb_sub = it.subscribe("/camera/image", 1, rgbCallback);
    ros::Rate loop_rate(1);

    cv::Mat frame;
    
    while (ros::ok()) {    
        
        if (rgbReceive) {
            rgbReceive = false;
            cv::imshow("xxx", rgbMat);
            if (cv::waitKey(10) == 'q') break;
        }

        ros::spinOnce();
        // loop_rate.sleep();
        
        

        
    }
    
    return 0;    
}
