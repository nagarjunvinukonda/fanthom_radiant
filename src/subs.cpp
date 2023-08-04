// #include <ros/ros.h>
// #include <fanthom_radiant/DiffData.h>
// #include <fanthom_radiant/CustomData.h>
// #include <std_msgs/Float32.h>
// #include <boost/date_time.hpp>

// ros::Time last_time;
// ros::Publisher diff_pub;  // Declaration for diff_pub

// // void custom_data_callback(const fanthom_radiant::CustomData::ConstPtr& data)
// // {
// //     const boost::posix_time::ptime current_time = boost::posix_time::from_iso_extended_string(data->time);

// //     if (last_time != ros::Time(0))
// //     {
// //         const double time_diff = (current_time - boost::posix_time::from_time_t(last_time.toSec())).total_seconds();
// //         fanthom_radiant::DiffData diff_msg;
// //         diff_msg.time_difference = time_diff;
// //         diff_pub.publish(diff_msg);
// //     }

// //     last_time = ros::Time::fromBoost(current_time);
// // }


// void custom_data_callback(const fanthom_radiant::CustomData::ConstPtr& data)
// {
//     if (data->time.empty())
//     {
//         ROS_WARN("Received CustomData message with empty time field.");
//         return;
//     }

//     try
//     {
//         const boost::posix_time::ptime current_time = boost::posix_time::from_iso_extended_string(data->time);

//         if (last_time != ros::Time(0))
//         {
//             const double time_diff = (current_time - boost::posix_time::from_time_t(last_time.toSec())).total_seconds();
//             fanthom_radiant::DiffData diff_msg;
//             diff_msg.time_difference = time_diff;
//             diff_pub.publish(diff_msg);
//         }

//         last_time = ros::Time::fromBoost(current_time);
//     }
//     catch (const boost::bad_lexical_cast& e)
//     {
//         ROS_ERROR_STREAM("Error parsing time: " << e.what());
//     }
// }


// int main(int argc, char** argv)
// {
//     ros::init(argc, argv, "csv_subscriber");
//     ros::NodeHandle nh;

//     diff_pub = nh.advertise<fanthom_radiant::DiffData>("/diff", 10);  // Initialize diff_pub
//     // ros::Subscriber sub = nh.subscribe("data", 10, custom_data_callback);
//     ros::Subscriber sub = nh.subscribe<fanthom_radiant::CustomData>("data", 10, custom_data_callback);
//     ros::spin();
    
//     return 0;
// }
#include <ros/ros.h>
#include <fanthom_radiant/CustomData.h>
#include <fanthom_radiant/DiffData.h>
#include <std_msgs/Float32.h>
#include <chrono>
#include <iomanip>
#include <sstream>

ros::Publisher diff_pub;
std::chrono::system_clock::time_point last_time;

void customDataCallback(const fanthom_radiant::CustomData::ConstPtr& data)
{
    std::stringstream ss;
    ss << data->time; // Convert the string to a stringstream
    std::tm tm_time = {};
    ss >> std::get_time(&tm_time, "%Y-%m-%d %H:%M:%S+00:00");

    std::chrono::system_clock::time_point current_time = std::chrono::system_clock::from_time_t(std::mktime(&tm_time));

    if (last_time.time_since_epoch().count() != 0)
    {
        std::chrono::duration<double> time_diff = current_time - last_time;
        fanthom_radiant::DiffData diff_msg;
        diff_msg.time_difference = time_diff.count();
        diff_pub.publish(diff_msg);
    }

    last_time = current_time;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "subs");
    ros::NodeHandle nh;

    ros::Subscriber custom_data_sub = nh.subscribe("data", 10, customDataCallback);
    diff_pub = nh.advertise<fanthom_radiant::DiffData>("/diff", 10);

    ros::spin();

    return 0;
}
