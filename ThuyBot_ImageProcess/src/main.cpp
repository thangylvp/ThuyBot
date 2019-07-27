#include "opencv2/opencv.hpp"
#include <iostream>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#define CAM_DEBUG 0

int main(int argc, char** argv){

    std::cout << "OpenCV version : " << CV_VERSION << std::endl;
    std::cout << "Major version : " << CV_MAJOR_VERSION << std::endl;
    std::cout << "Minor version : " << CV_MINOR_VERSION << std::endl;
    std::cout << "Subminor version : " << CV_SUBMINOR_VERSION << std::endl;

    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("camera/image", 1);
    sensor_msgs::ImagePtr msg;
    ros::Rate loop_rate(30);

    cv::VideoCapture cap(0); 
    cv::Mat frame;


    bool succ = cap.set(cv::CAP_PROP_FPS , 30);
    if (CAM_DEBUG) {
        std::cerr << "Set fps : " << succ << std::endl;
    }
    if (!cap.isOpened())  
        return -1;

    
    while (nh.ok()) {    
        cap >> frame;
        
        if (!frame.empty()) {
            msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
            pub.publish(msg);
        } 
    
        if (CAM_DEBUG) {
            std::cerr << frame.rows << " " << frame.cols << " " << cap.get(CV_CAP_PROP_FPS) << std::endl;
            cv::imshow("edges", frame);
            if (cv::waitKey(10) == 'q') {
                break;
            }
        }

        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;    
}
