# Introduction
* Code for on-line learning and to interface the DYNAP neuromorphic chip is in this repository. <br />
* Code to interface the omni-directional robot and the ROLLS neuromorphic chip is in repository:
https://github.com/ldcyx/omnibot_rolls.git

# Caer
Caer is a software that configures, monitors, analyzes the data from neuromorphic chips. 

# On-line learning code
The on-line learning algorithm is implemented as a module at 'caer/modules/dsnn/' (https://github.com/ldcyx/caer/tree/master/modules/dsnn). <br />
In the 'dsnn' module, <br />

File Name | Main Usage
------------ | -------------
dsnn.c | The main function. It is called in the main loop of Caer. 
dsnn.h | Define the parameters. 
basic.h | Define the basic low-level functions.
encode_neuron.h | Encode the address of silicon neurons.
synapse.h | Build physical synapses on neuromorphic hardware. 
layers.h | Build feature neurons. 
update.h | Update the synapse weights in memory and update them on neuromorphic hardware. 
create_column.h | Create multiple groups of output neurons. 
build_column.h | Connect the feature neurons to output neurons. 
scale_up_down.h | Simulate the mapping neurons of the recognition network. 
create_nsm.h | Create the neural state machines to build the winner-take-all mechanism. 
learn_column.h | Learn the synapse weight between feature neurons and the output neurons. 
stability.h | Check whether a simulated saccade is stopped. 
load_save.h | Load and save the learned synapse weights. 
learn.h | Control the writing and reading of the ring buffer. 
biases.h | Configure the biases of the analog neuron and synapse circuits on chip. 
initialize.h | Initialize the network. 
build_nsm.h | Build synapses of the Neural State Machines (NSMs) to form a Winner-Take-All (WTA) mechanism. 
connect_davis.h | Configure the input neurons to receive events from DAVIS/DVS silicon retina. 
dynapse_output.h | Configure the output neurons to send spikes to the ROLLS chip. 
reset.h | Reset the learning algorithm and the network.
record.h | Record the neural activity on chip. 

# Usage

## Software dependency
Caer has to compile and run with libcaer: https://github.com/ldcyx/libcaer.git <br />

## Hardware dependency
Caer has to run with the DYNAP neuromorphic hardware connected to the computer. The connection is through a USB 2.0/3.0 interface. <br />

## Commands
Use the commands below to compile and run Caer. <br />
Compile Caer: <br />
$sh make_file_onlinele.sh <br />
Run Caer: <br />
$sh run_onlinele.sh <br />
