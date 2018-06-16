# caer

The caer code has to compile and run with libcaer and run with the DYNAP neuromorphic hardware connected to the computer. <br />
The on-line learning algorithm is implemented as a module at 'caer/modules/dsnn/'. <br />

In the 'dsnn' module, <br />
"dsnn.h" defines the parameters. <br />
"basic.h" defines the basic low-level functions. <br />
"encode_neuron.h" encodes the address of silicon neurons. <br />
"synapse.h" builds physical synapses on neuromorphic hardware. <br />
"layers.h" builds feature neurons. <br />
"update.h" updates the synapse weight from software to neuromorphic hardware. <br />
"create_column.h" creates multiple groups of output neurons. <br />
"build_column.h" connects the feature neurons to output neurons. <br />
"scale_up_down.h" simulates the mapping neurons of the recognition network. <br />
"create_nsm.h" creates the neural state machines to build the winner-take-all mechanism. <br />
"learn_column.h" learns the synapse weight between feature neurons and the output neurons. <br />
"stability.h" checks whether a simulated saccade is stopped. <br />
"load_save.h" loads and saves the learned synapse weights. <br />
"learn.h" controls the writing and reading of the ring buffer. <br />
"biases.h" configures the biases of the analog neuron circuits on chip. <br />
"initialize.h" initializes the network. <br />
"build_nsm.h" builds synapses of the neural state machines. <br /> 
"connect_davis.h" configures the input to receive events from DAVIS/DVS silicon retina. <br />
"dynapse_output.h" configures the output neurons to send spikes to the ROLLS chip. <br />
"reset.h" resets the learning algorithm and the network. <br />
"record.h" records the neural activity on chips. <br />
