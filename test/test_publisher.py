#!/usr/bin/env python

import unittest
import rospy
from fathom_radiant.msg import CustomData

class TestPublisher(unittest.TestCase):

    def test_publishing_data_types(self):
        rospy.init_node('test_publisher_node')

        # list to store received messages
        received_msgs = []

        def custom_data_callback(data):
            received_msgs.append(data)

        # Subscriber to listen to the 'data' topic
        rospy.Subscriber('data', CustomData, custom_data_callback)

        # Wait for a few seconds to allow messages to be received and processed
        rospy.sleep(1)

        # Check the data types of each message value
        for msg in received_msgs:
            self.assertTrue(isinstance(msg.longitude, float))
            self.assertTrue(isinstance(msg.latitude, float))
            self.assertTrue(isinstance(msg.altitude, float))
            self.assertTrue(isinstance(msg.time, str))
            self.assertTrue(isinstance(msg.actual_speed, float))

    def test_publishing_topic_publish(self):
        rospy.init_node('test_publisher_node')

        published_topics = rospy.get_published_topics()

        # Check if the '/data' topic is in the list of published topics
        self.assertTrue('/data' in [topic for topic, msg_type in published_topics])

        # Wait for a few seconds to allow messages to be received and processed
        rospy.sleep(1)

if __name__ == '__main__':
    import rostest
    rostest.rosrun('fathom_radiant', 'test_publisher', TestPublisher)
