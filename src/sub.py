#!/usr/bin/env python

import rospy
from fanthom_radiant.msg import DiffData, CustomData
from std_msgs.msg import Float32
from datetime import datetime

last_time = None

def custom_data_callback(data):
    global last_time
    current_time = datetime.strptime(data.time, '%Y-%m-%d %H:%M:%S+00:00')
    
    if last_time is not None:
        time_diff = (current_time - last_time).total_seconds()
        diff_msg = DiffData(time_difference=float(time_diff))
        diff_pub.publish(diff_msg)

    last_time = current_time

def main():
    rospy.init_node('csv_subscriber')
    rospy.Subscriber('data', CustomData, custom_data_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        diff_pub = rospy.Publisher('/diff', DiffData, queue_size=10)
        main()
    except rospy.ROSInterruptException:
        pass
