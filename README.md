# Introduction
* Code for on-line learning and to interface the DYNAP neuromorphic chip is in this repository. <br />
* Code to interface the omni-directional robot and the ROLLS neuromorphic chip is in repository:
https://github.com/ldcyx/omnibot_rolls.git

# Caer
Caer is a software that configures and monitors the DYNAP neuromorphic chips and analyzes the firing activity of the silicon neurons on the chips. 
It enables online reconfiguration of the connectivity between neurons and the weights of synapses. 

# On-line learning code
The on-line learning algorithm is implemented as a module at 'caer/modules/dsnn/' (https://github.com/ldcyx/caer/tree/master/modules/dsnn). <br />
In the 'dsnn' module, there are 22 scripts. They are written in C. The main usage of the scripts is listed below. <br />

The main function.  <br />
File Name | Main Usage
------------ | ------------- 
dsnn.c | The main function. It is called in the main loop of Caer. 

# Usage

## Software dependency
Caer has to compile and run with libcaer: https://github.com/ldcyx/libcaer.git <br />

## Hardware dependency
Caer has to run with the DYNAP neuromorphic hardware connected to the computer. The connection is through a USB 2.0/3.0 interface. <br />

## Commands
Run the scripts below to compile and run Caer. <br />
To compile Caer: <br />
$sh make_file_onlinele.sh <br />
To run Caer: <br />
$sh run_onlinele.sh <br />
