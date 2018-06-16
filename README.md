# caer

The caer code has to compile and run with libcaer and run with the DYNAP neuromorphic hardware connected to the computer. 
The on-line learning algorithm is implemented as a module at 'caer/modules/dsnn/'. 

In the 'dsnn' module,
"dsnn.h" defines the parameters. 
"basic.h" defines the basic low-level functions. 
"encode_neuron.h" encodes the address of silicon neurons. 
"synapse.h" builds physical synapses on neuromorphic hardware. 
"layers.h" builds feature neurons. 
