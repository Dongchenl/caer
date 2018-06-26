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

Basic functions. <br />

File Name | Main Usage
------------ | -------------
dsnn.h | Define the parameters. 
basic.h | Define the basic low-level functions.
biases.h | Configure the biases of the analog neuron and synapse circuits on the chips. 
encode_neuron.h | Encode the address of silicon neurons.
synapse.h | Build physical synapses on neuromorphic hardware. 
initialize.h | Initialize the network. 
connect_davis.h | Configure the input neurons to receive events from DAVIS/DVS silicon retina. 
load_save.h | Load and save the learned synapse weights. 
record.h | Record the neural activity on the chips. 

Assign the silicon neurons on the chips to different neuron groups.  <br />

File Name | Main Usage
------------ | -------------
create_input.h | Create input neurons on the chips.
create_feature.h | Create feature neurons on the chips. 
create_output.h | Create multiple groups of output neurons on the chips.
create_wta.h | Create the Neural State Machines (NSMs) for building the Winner-Take-All (WTA) mechanism, as well as the output selecting neurons.
create_arbitor.h | Create neurons for the arbitration between learning and recognition pathways.

Connect neurons with synapses on the chips.  <br />

File Name | Main Usage
------------ | -------------
build_input.h | Connect the input neurons. 
build_feature.h | Connect the feature neurons. 
build_ouput.h | Connect the feature neurons to the output neurons. 
build_wta.h | Connect the NSMs to form the WTA mechanism. 
build_arbitrator.h | Connect the neurons for arbitration. 

Perform the learning rules. <br /> 

File Name | Main Usage
------------ | -------------
scale_up_down.h | Simulate the mapping neurons of the recognition network. 
learn_input.h | Learn to maintain the visibility during the simulated microsaccades and update them on neuromorphic hardware.
learn_output.h | Learn the synapse weights between feature neurons and the output neurons.
learn_wta.h | Learn the synapse weight between feature neurons and the output neurons. 
motor.h | Simulate the events sent from motor neurons. 
learn.h | Control the writing and reading of the ring buffer. 

Overall control of configuring the chips and the computing in the 'dsnn' module. <br />

File Name | Main Usage
------------ | -------------
dynapse_output.h | Configure the output neurons to send spikes to the ROLLS chip. 
reset.h | Reset the learning algorithm and the network.

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
