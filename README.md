# Formula 1 video-record tracking system
This is the Formula 1 video-record tracking system project of team 22, ENG5220: Real Time Embedded Programming (2022-23) of University of Glasgow. 
## Contents
- [Background](#background)
- [Contributor](#contributor)
- [Features](#features)
- [Install & Guidance](#install--guidance)
- [Task list]()
- WIP
## Background
In Formula-1 match, it is always a challenge to keep a steady track on the target for a photographer holding his camera by hand. This project develops a system installed on ground or drones to tracking the cars with the help of raspberry, and the servo motors. This can also be used on other object tracking situation, like rocket launching record.<br>
In this project, a Raspberry 4B will be used as main control unit. C++ is mainly used in this project.
## Contributor
This project's development thanks to these contributors<br>  
|Name|ID|
|------|------|
|[Haihang Xia](https://github.com/Haihang-Xia)| *2743062X*|<br>
|[Yuge Wang](https://github.com/Cecilia-Yuge-Wang) |*2809017W*|<br>
|[Minghao Xuan](https://github.com/Ranger5120) |*2782500X*|<br>
|[Chengjia Yu](https://github.com/CHENGJIA-YU)|*2780667Y*|<br>
## Features
This system includes three parts. A camera installed on the platform driven by two motors is used to capture the video and send it back to raspberry. The raspberry deals with the tracking algorithm and gives instruction to the servo motors, to achieve the tracking process.<br>
<br>
The video can be transmitted to the cellphone, iPad, or laptop etc..Only needs to be able to connect with WiFi.<br>
The system can switch between manual target selection and automatic target selection.<br>

>**WIP: Xbox Controller controlling**<br>
>This is a work in progress planning. We hope to use an Xbox controller (Playstation, NS controller and etc...) to control the camera platform rotating and lock on in manual mode. However, this is only a WIP planning. **It may be cancelled due to the final result and timetable.**<br>

## Install & Guidance
### OpenCV Installation
This project needs to use OpenCV. You need to set up the environment of OpenCV at first. The following steps will guide you how to make it. in this project, the openCV's version we use is 4.7.0. The Raspberry 4B is installed with system of Raspberry Pi OS with desktop (32-bit)<br>
1. Install dependent package
```
sudo apt-get install build-essential
sudo apt-get install cmake libgtk2.0-dev pkg-config libswscale-dev
sudo apt-get install libjpeg-dev libpng-dev libtiff-dev
```
2. Compile the files
```
mkdir
cd build
cmake ..
sudo make //this process may take a very long time bruhhhhhh
sudo make install
```

After this, you have finished the install of OpenCV if there's not any mistake information.<br>
<br>

### WiringPi Installation
In this project, GPIO would be used to control the servo motors. WiringPi Library is used in this project. Follow the steps below would setup the WiringPi. <br>
>As WiringPi official anounced, the WiringPi is **PRE-INSTALLED** with standard Raspbian systems, and official download source is not available anymore. So a third-party source would be used in this instruction.<br>
1. Checking if you have had the library.  
```
gpio -v
```
If you receive an output of version information about the GPIO, then you have had the library. just ignore the instruction if you know what to do.<br>

2. clone the repositories
```
git clone https://github.com/WiringPi/WiringPi.git
```
3. compile the source file
```
cd WiringPi
git pull origin
./build
```
Wait until the information of finishing the building process, and use 
```
gpio -v
```
to check library information, and use 
```
gpio readall
```
to draw a table of all the pinout.
