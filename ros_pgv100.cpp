//#include "ros/ros.h"
//#include "std_msgs/String.h"
//#include "Rs485.h"
//#include "PGV100.h"
//#include <sstream>

//int main(int argc, char **argv)
//{
//    ros::init(argc, argv, "pgv100");
//    ros::NodeHandle nh;

//    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("pgv_msg", 500);

//    //Rs485 rs = Rs485("/dev/ttyUSB0", Rs485::BR115200);
//    Rs485 rs = Rs485();
///*
//    bool succ = rs.opendevice("/dev/ttyUSB0");
//    if(!succ){
//        std::cout << "open device error!" << std::endl;
//        ros::shutdown();
//        return -1;
//    }
//*/
//    PGV100 sensor = PGV100(rs, 0);

//    ros::Rate loop_rate(1);//10
//    while (ros::ok())
//    {
//        sensor.grab();

//        //ROS_INFO("positionX: %f, positionY: %f, angel: %f , tagID: %d,", sensor.positionX(), sensor.positionY(), sensor.angel(), sensor.tagID());

//        std_msgs::String msg;

//        std::stringstream ss;
//        //proto 'x|y|thita|ID'
//        ss << sensor.positionX() << "|" << sensor.positionY() << "|" << sensor.angel() << "|" << sensor.tagID();
//        msg.data = ss.str();

//        chatter_pub.publish(msg);

//        ros::spinOnce();
//        loop_rate.sleep();
//    }

//    return 0;
//}
