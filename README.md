# caer

The caer code has to compile and run with libcaer and run with the DYNAP neuromorphic hardware connected to the computer. <br />
The on-line learning algorithm is implemented as a module at 'caer/modules/dsnn/'. <br />

In the 'dsnn' module, <br />
"dsnn.h" defines the parameters. <br />
"basic.h" defines the basic low-level functions. <br />
"encode_neuron.h" encodes the address of silicon neurons. <br />
"synapse.h" builds physical synapses on neuromorphic hardware. <br />
"layers.h" builds feature neurons. <br />

