#include <ros/ros.h>
#include <fathom_radiant/CustomData.h>
#include <fathom_radiant/DiffData.h>
#include <std_msgs/Float32.h>
#include <chrono>
#include <iomanip>
#include <sstream>

ros::Publisher diff_pub;
std::chrono::system_clock::time_point last_time;

void customDataCallback(const fathom_radiant::CustomData::ConstPtr& data)
{
    std::stringstream ss;
    ss << data->time; // Convert the string to a stringstream
    std::tm tm_time = {};
    ss >> std::get_time(&tm_time, "%Y-%m-%d %H:%M:%S+00:00");

    std::chrono::system_clock::time_point current_time = std::chrono::system_clock::from_time_t(std::mktime(&tm_time));

    if (last_time.time_since_epoch().count() != 0)
    {
        std::chrono::duration<double> time_diff = current_time - last_time;
        fathom_radiant::DiffData diff_msg;
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
    diff_pub = nh.advertise<fathom_radiant::DiffData>("/diff", 10);

    ros::spin();

    return 0;
}
