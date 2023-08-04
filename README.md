# fanthom_radiant Programming Challenge: ROS1

The aim of this project is to read the csv file and compute the time differnce between each row and compare with the existing ground truth in dataset. This projects reads the existsing Dataset.csv in fanthom_radiant/src folder. Hence, no need provide path for csv. I have also ensured if the user has a prefernce of providing csv path he can project it in launch file as ros param and comments to modify the code. 

Though the project requires me to complete using ROS2. My PC dosnt have eough resources and system requirments to install *ROS2*, *Calcon*. Hence, I am using Ubuntu 18.0.4 ROS1 melodic for this project to simplify and complete within 4hrs time.


## Developer: 
**Nagarjun Vinukonda**

## Pre-requesites:

The following softwares needs to be installed ahead:

**Note:** This package is for Ubuntu 18.0.4 ROS1 Melodic i.e. Python 2.7.

If system is Ubuntu 18.0.4 install [ROS Melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)

I have also built cpp files for the same project. In case the user wants to run on higher Ubuntu version like 20.0.4. This should help out of python version conficts with higher version of Ubuntu ROS1. 


Colcon notes:<br />
* Colcon is not supported for Ubuntu 18.0.4 ROS1 version. Hence we will be doing catkin_make. Although there are experimental packages of Colcon which might cause conflict problems <br />
* Reason:- One of the reason is Colcon uses Python3 and ROS Melodic by default is Python 2.7. Which brings conflicts. <br />
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
git clone https://repo-fn.roboticresearch.com/nvinukonda.fn/camera_calibration_ros_wiki_gui.git
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

If User wants to specify path of the .csv file please specify in data_python.launch for the value in ros param for lauching python scripts.<br/>

## Running the project:

Open terminal:

```
cd catkin_ws
roslaunch fanthom_radiant data_python.launch
```

In case you are running on higher version and having Ros melodic Python2.7 conflicts. I ensure to create c++ scripts to run the project on different versions of Ubuntu with ROS1 version. 

```
cd catkin_ws
roslaunch fanthom_radiant data_cpp.launch
```

### Running testing framework
Once you have lauched the publisher subscriber scripts using launch file. Now you can run unit tests for publisher and subscriber <br/>
Unit test for publisher:
```
rosrun fanthom_radiant test_publisher.py
```

Unit test for subscriber:
```
rosrun fanthom_radiant test_subscriber.py
```

## Do's & Dont's:

**Note:** Please dont change the location of .csv file if you are not providing csv path are ros param for data_python.launch.


## Process of Project:
The pub.py node publishs topic called "/data" after reading Dataset.csv file. "Longitude, Latitude, Altitude, Time and Actual_Speed" along with "Time_diff" for testing using CustomData.msg. Later the sub.py node subscribes "/data" topic and computes the time difference between current and previous "Time" and publishes to "/diff" topic via DiffData.msg. 


## Directory strcuture:

```
fanthom_radiant/
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

Once data_python.launch has runned.<br/>

To vizualize final time diff:
```
rostopic echo /diff
``` 

To vizualize data from .csv:
```
rostopic echo /data
``` 



