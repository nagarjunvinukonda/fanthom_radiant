#!/usr/bin/env python

import rospy
from fathom_radiant.msg import CustomData
import csv
import time
import os
import signal

def get_csv_file_path():
    # Get the current directory where the script is located
    script_dir = os.path.dirname(os.path.realpath(__file__))
    # Define the specific CSV file name you want to read
    csv_file_name = "Dataset.csv"
    file_path = os.path.join(script_dir, csv_file_name)
    # Check if the specific file exists in the script directory
    if os.path.isfile(file_path):
        return file_path

    return None

def publish_csv_data(file_path, publisher, rate_hz=3):
    def signal_handler(sig, frame):
        rospy.loginfo("Received Ctrl+C, shutting down...")
        rospy.signal_shutdown("Ctrl+C")

    signal.signal(signal.SIGINT, signal_handler)

    with open(file_path) as csvfile:
        data_reader = csv.reader(csvfile)
        headers = next(data_reader) # Read and skip the header row
        rate = rospy.Rate(rate_hz)
        for row in data_reader:
            if rospy.is_shutdown():
                break

            data_msg = CustomData(
                longitude=float(row[1]),
                latitude=float(row[2]),
                altitude=float(row[3]),
                time=row[4],
                actual_speed=float(row[5])
            )
            publisher.publish(data_msg)
            rate.sleep()

def main():
    rospy.init_node('csv_publisher')
    pub = rospy.Publisher('data', CustomData, queue_size=10)
    
    # if you want to use User defined ros param then comment below 
    file_path = get_csv_file_path()

    # if you want to use User defined ros param then uncomment below 
    # file_path = rospy.get_param('~file_path')

    if file_path is None:
        rospy.logerr("CSV file not found in the publisher script folder.")
        return

    rate_hz = 3
    try:
        publish_csv_data(file_path, pub, rate_hz)
    except rospy.ROSInterruptException:
        pass
    finally:
        rospy.loginfo("Shutting down...")

if __name__ == '__main__':
    main()

