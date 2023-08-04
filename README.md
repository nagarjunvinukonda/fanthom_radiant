# fathom_radiant Programming Challenge: ROS1

The aim of this project is to read the csv file and compute the time difference between each row and compare with the existing ground truth in dataset. This project reads the existing Dataset.csv in fathom_radiant/src folder. Hence, no need to provide path for csv. I have also ensured if the user has a preference for providing csv path, he can provide it in the launch file as a ros param and comment out to modify the code accordingly. 

Though the project requires me to complete using ROS2. My PC doesn't have enough resources and system requirements to install *ROS2*, *Calcon*. Hence, I am using Ubuntu 18.0.4 ROS1 melodic for this project to simplify and complete it within 4hrs time.


## Developer: 
**Nagarjun Vinukonda**

## Pre-requisites:

The following software needs to be installed ahead:

**Note:** This package is for Ubuntu 18.0.4 ROS1 Melodic i.e. Python 2.7.

If system is Ubuntu 18.0.4 install [ROS Melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)

I have also built cpp files for the same project. In case the user wants to run on higher Ubuntu version like 20.0.4. This should help out of Python version conflicts with higher version of Ubuntu ROS1. 


Colcon notes:<br />
* Colcon is not supported for Ubuntu 18.0.4 ROS1 version. Hence we will be doing catkin_make. Although there are experimental packages of Colcon which might cause conflict problems <br />
* Reason:- One of the reasons is Colcon uses Python3 and ROS Melodic by default is Python 2.7. Which brings conflicts. <br />
[Colcon for ros1 ubuntu 20.0.4](https://colcon.readthedocs.io/en/released/user/installation.html)

Installation:<br />
```
sudo apt update
sudo apt install python3-colcon-common-extensions
```
If you want to install using pip:<br />
```
pip install -U colcon-common-extensions
```

## Project building:

Create catkin_ws or any workspace with your name: <br />

```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/
```
* Note: If you choose to use catkin_make which is stable, do catkin_make after creating catkin_ws:
```
catkin_make 
```

Download this repo and put it in the src folder of the catkin_ws and unzip it.
```
cd ~/catkin_ws/src/
git clone https://github.com/nagarjunvinukonda/fathom_radiant.git
```


### Build using catkin_make
Perform catkin_make after downloading:<br />
```
cd ~/catkin_ws/
catkin_make
```
### Build using Colcon
```
cd ~/catkin_ws/
colcon build
```

Now source your catkin_ws:<br />
`source devel/setup.bash`

## Parameters specification:

If User wants to specify path of the .csv file please specify in data_python.launch or data_cpp.launch in the value section, in the ros param section.<br/>

## Running the project:

Open terminal:

```
cd catkin_ws
roslaunch fathom_radiant data_python.launch
```

In case you are running on higher version and having ROS melodic Python2.7 conflicts. I ensure to create c++ scripts to run the project on different versions of Ubuntu with ROS1 version. 

```
cd catkin_ws
roslaunch fathom_radiant data_cpp.launch
```

### Running testing framework
Once you have launched the publisher and subscriber scripts using the launch file. Now you can run unit tests for publisher and subscriber <br/>
Unit test for publisher:
```
rosrun fathom_radiant test_publisher.py
```

Unit test for subscriber:
```
rosrun fathom_radiant test_subscriber.py
```
### Information on tests:
The test_publsiher:<br/>
1) test_publishing_data_types: It checks for correct data types in the message file as expected from CSV.
2) test_publishing_topic_publish: It checks if the topic '/data' is published or not <br/>

The test_subscriber: <br/>
1) test_subscriber_dataLength: It checks if the topic '/diff' is published or not, the message time difference data type is float and the length of the message received is >0 and exists. 
2) test_subscribing_dataDiff: It checks if the time difference computed from '/diff' and the time difference available in .csv are equal or not

## Do's & Dont's:

**Note:** Please dont change the location of .csv file if you are not providing csv path as the ros param in data_python.launch or data_cpp.launch.


## Process of Project:
The pub.py node publishes topic called "/data" after reading Dataset.csv file. "Longitude, Latitude, Altitude, Time and Actual_Speed" along with "Time_diff" for testing using CustomData.msg. Later the sub.py node subscribes "/data" topic and computes the time difference between current and previous "Time" and publishes to "/diff" topic via DiffData.msg. 


## Directory structure:

```
fathom_radiant/
├── CMakeLists.txt
├── launch
│   └── data_python.launch
│   └── data_cpp.launch
├── msg
│   └── CustomData.msg
│   └── DiffData.msg
├── package.xml
|
├── src
│   ├── pub.py
│   └── sub.py
│   └── Dataset.csv
│   ├── pubs.cpp
│   └── subs.cpp 
└── test
    ├── test_publisher.py
    └── test_subscriber.py

```

## output:

Once data_python.launch has launched.<br/>

Dont forget to source your repo on the terminal.<br/>
```
source devel/setup.bash
```

To visualize final time diff:
```
rostopic echo /diff
``` 

To vizualize data from .csv:
```
rostopic echo /data
``` 



