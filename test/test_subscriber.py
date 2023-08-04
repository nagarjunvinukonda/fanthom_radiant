#!/usr/bin/env python

import unittest
import rospy
from fathom_radiant.msg import DiffData
from fathom_radiant.msg import CustomData

class TestSubscriber(unittest.TestCase):

    def test_subscriber_dataLength(self):
        rospy.init_node('test_subscriber_node')

        # Get the list of published topics and their message types
        published_topics = rospy.get_published_topics()
        # Check if the '/diff' topic is in the list of published topics
        self.assertTrue('/diff' in [topic for topic, msg_type in published_topics])
        # a list to store received messages
        received_msgs = []

        def diff_data_callback(data):
            received_msgs.append(data)

        # subscriber to listen to the '/diff' topic
        rospy.Subscriber('/diff', DiffData, diff_data_callback)
        # Wait for a few seconds to allow messages to be received and processed
        rospy.sleep(2)
        # Check if messages have been received
        self.assertTrue(len(received_msgs) > 0)
        # Check the data types of each message value
        for msg in received_msgs:
            self.assertTrue(isinstance(msg.time_difference, float))

    def test_subscribing_dataDiff(self):
        rospy.init_node('test_subscriber_node')

        # list to store received time differences and known time differences
        received_diffs = []
        known_diffs = []

        def diff_data_callback(data):
            received_diffs.append(data)

        # subscriber to listen to the 'diff' topic
        rospy.Subscriber('/diff', DiffData, diff_data_callback)

        def data_callback(data):
            known_diffs.append(data)

        # subscriber to listen to the 'diff' topic
        rospy.Subscriber('/data', CustomData, data_callback)
        rospy.sleep(2)
        
        for diff_msg, expected_diff in zip(received_diffs, known_diffs):
            # assertion here is to validate each received time difference from expected or known time difference
            self.assertAlmostEqual(diff_msg.time_difference, expected_diff.time_difference, delta=0.1)

if __name__ == '__main__':
    import rostest
    rostest.rosrun('fathom_radiant', 'test_subscriber', TestSubscriber)
