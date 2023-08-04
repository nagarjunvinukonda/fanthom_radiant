#include <ros/ros.h>
#include <ros/package.h> // Add this line for ros::package::getPath
#include <fanthom_radiant/CustomData.h>
#include <fstream>
#include <sstream>
#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem; // Create an alias for the filesystem namespace
std::string get_csv_file_path()
{
    // Get the package path
    std::string package_path = ros::package::getPath("fanthom_radiant");

    // Define the specific CSV file name you want to read
    std::string csv_file_name = "Dataset.csv";
    fs::path file_path = fs::path(package_path);
    file_path.append("src");
    file_path.append(csv_file_name);

    // Check if the specific file exists
    std::string the_path = file_path;

    if (the_path.length()!=0)
    {
        return the_path;
    }

    return "";
}

void publish_csv_data(const std::string& file_path, ros::Publisher& publisher, double rate_hz = 3)
{
    std::ifstream csvfile(file_path);
    std::string line;
    getline(csvfile, line); // Read and skip the header row

    ros::Rate rate(rate_hz);
    while (ros::ok() && getline(csvfile, line))
    {
        std::istringstream iss(line);
        std::string token;

        fanthom_radiant::CustomData data_msg;
        getline(iss, token, ','); // Skip the index column
        getline(iss, token, ','); // Longitude
        data_msg.longitude = std::stod(token);
        getline(iss, token, ','); // Latitude
        data_msg.latitude = std::stod(token);
        getline(iss, token, ','); // Altitude
        data_msg.altitude = std::stod(token);
        getline(iss, token, ','); // Time
        data_msg.time = token;
        getline(iss, token, ','); // Actual_Speed
        data_msg.actual_speed = std::stod(token);

        publisher.publish(data_msg);
        rate.sleep();
    }
    
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pubs");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<fanthom_radiant::CustomData>("data", 10);
    std::string file_path;

    //if you want to use ros::param un comment this, but ensure you sepcified right path in launch file
    // ros::param::get("/file_path", file_path);

    // if you want to use ros param comment this below line, but ensure you sepcified right path in launch file
    file_path = get_csv_file_path();

    if(file_path.length()!=0)
    {
        publish_csv_data(file_path, pub);

    }
    else
    {
        ROS_ERROR("Failed to get parameter 'file_path'.");
    }

    ROS_INFO("Shutting down...");
    return 0;
}
