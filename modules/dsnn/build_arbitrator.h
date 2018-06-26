static void buildArbitratorNeurons(caerModuleData moduleData);
static void buildArbitratorNetwork(caerModuleData moduleData);

void buildArbitratorNeurons(caerModuleData moduleData) {
	buildArbitratorNetwork(moduleData);

	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}

void buildArbitratorNetwork(caerModuleData moduleData) {
	uint32_t pre_chip_id, pre_neuron_id, post_neuron_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse; //REAL_SYNAPSE_WITHOUT_LEARNING;
	//to simulate SACCADES
	//connect the arbitration neurons to the NSMs
	int64_t pre_row_id, pre_col_id, post_row_id, post_col_id;
	real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	for (post_row_id = 0; post_row_id < NSM_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < NSM_W; post_col_id++) {
			for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
				for (pre_row_id = 0; pre_row_id < ARBITRATION_L; pre_row_id++) {
					for (pre_col_id = 0; pre_col_id < ARBITRATION_W; pre_col_id++) {
						pre_neuron_addr = arbitration_neurons_ex[pre_row_id][pre_col_id];
						post_neuron_addr = nsm_state_1[post_row_id][post_col_id][post_neuron_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
	for (post_row_id = 0; post_row_id < NSM_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < NSM_W; post_col_id++) {
			for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
				for (pre_row_id = 0; pre_row_id < ARBITRATION_L; pre_row_id++) {
					for (pre_col_id = 0; pre_col_id < ARBITRATION_W; pre_col_id++) {
						pre_neuron_addr = arbitration_neurons_in[pre_row_id][pre_col_id];
						post_neuron_addr = nsm_transition_1[post_row_id][post_col_id][post_neuron_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
	for (post_row_id = 0; post_row_id < NSM_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < NSM_W; post_col_id++) {
			for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
				for (pre_row_id = 0; pre_row_id < ARBITRATION_L; pre_row_id++) {
					for (pre_col_id = 0; pre_col_id < ARBITRATION_W; pre_col_id++) {
						pre_neuron_addr = arbitration_neurons_in[pre_row_id][pre_col_id];
						post_neuron_addr = nsm_state_0[post_row_id][post_col_id][post_neuron_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
	//connect the arbitration neurons to the feature neurons of the learning pathway
	real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	virtual_neuron_addr_enable = 1;
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < ARBITRATION_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < ARBITRATION_W; pre_col_id++) {
					pre_neuron_addr = arbitration_neurons_in[pre_row_id][pre_col_id];
					pre_chip_id = (pre_neuron_addr & NEURON_CHIPID_BITS) >> NEURON_CHIPID_SHIFT;
					pre_neuron_id = (pre_neuron_addr & NEURON_NEURONID_BITS) >> NEURON_NEURONID_SHIFT;
					virtual_neuron_addr = pre_chip_id << NEURON_CHIPID_SHIFT | 2 << NEURON_COREID_SHIFT | pre_neuron_id;

					post_neuron_addr = feature_layer_2_ex[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					post_neuron_addr = feature_layer_2_in[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < ARBITRATION_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < ARBITRATION_W; pre_col_id++) {
					pre_neuron_addr = arbitration_neurons_in[pre_row_id][pre_col_id];
					pre_chip_id = (pre_neuron_addr & NEURON_CHIPID_BITS) >> NEURON_CHIPID_SHIFT;
					pre_neuron_id = (pre_neuron_addr & NEURON_NEURONID_BITS) >> NEURON_NEURONID_SHIFT;
					virtual_neuron_addr = pre_chip_id << NEURON_CHIPID_SHIFT | 2 << NEURON_COREID_SHIFT | pre_neuron_id;

					post_neuron_addr = feature_layer_3_ex[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					post_neuron_addr = feature_layer_3_in[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//connect the learning pathway neurons to the feature neurons of the recognition pathway
	real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	virtual_neuron_addr_enable = 1;
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < LEARNING_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < LEARNING_W; pre_col_id++) {
					pre_neuron_addr = learning_pathway_neurons[pre_row_id][pre_col_id];
					pre_chip_id = (pre_neuron_addr & NEURON_CHIPID_BITS) >> NEURON_CHIPID_SHIFT;
					pre_neuron_id = (pre_neuron_addr & NEURON_NEURONID_BITS) >> NEURON_NEURONID_SHIFT;
					virtual_neuron_addr = pre_chip_id << NEURON_CHIPID_SHIFT | 2 << NEURON_COREID_SHIFT | pre_neuron_id;

					post_neuron_addr = feature_layer_0_ex[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					post_neuron_addr = feature_layer_0_in[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < LEARNING_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < LEARNING_W; pre_col_id++) {
					pre_neuron_addr = learning_pathway_neurons[pre_row_id][pre_col_id];
					pre_chip_id = (pre_neuron_addr & NEURON_CHIPID_BITS) >> NEURON_CHIPID_SHIFT;
					pre_neuron_id = (pre_neuron_addr & NEURON_NEURONID_BITS) >> NEURON_NEURONID_SHIFT;
					virtual_neuron_addr = pre_chip_id << NEURON_CHIPID_SHIFT | 2 << NEURON_COREID_SHIFT | pre_neuron_id;

					post_neuron_addr = feature_layer_1_ex[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					post_neuron_addr = feature_layer_1_in[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}

	//connect motor neurons EX to motor neurons IN
	real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	virtual_neuron_addr_enable = 0;
	for (post_row_id = 0; post_row_id < MOTOR_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < MOTOR_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < MOTOR_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < MOTOR_W; pre_col_id++) {
					pre_neuron_addr = motor_neurons_ex[pre_row_id][pre_col_id];
					post_neuron_addr = motor_neurons_in[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//connect motor neurons to arbitration neurons EX
	real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	virtual_neuron_addr_enable = 0;
	for (post_row_id = 0; post_row_id < ARBITRATION_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < ARBITRATION_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < MOTOR_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < MOTOR_W; pre_col_id++) {
					pre_neuron_addr = motor_neurons_ex[pre_row_id][pre_col_id];
					post_neuron_addr = arbitration_neurons_ex[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//connect arbitration neurons EX to arbitration neurons IN
	real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	virtual_neuron_addr_enable = 0;
	for (post_row_id = 0; post_row_id < ARBITRATION_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < ARBITRATION_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < ARBITRATION_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < ARBITRATION_W; pre_col_id++) {
					pre_neuron_addr = arbitration_neurons_ex[pre_row_id][pre_col_id];
					post_neuron_addr = arbitration_neurons_in[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//connect hub neurons to learning pathway neurons
	real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	virtual_neuron_addr_enable = 0;
	for (post_row_id = 0; post_row_id < LEARNING_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < LEARNING_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < MOTOR_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < MOTOR_W; pre_col_id++) {
					pre_neuron_addr = motor_neurons_in[pre_row_id][pre_col_id];
					post_neuron_addr = learning_pathway_neurons[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//connect learning pathway neurons to arbitration neurons EX
	real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	virtual_neuron_addr_enable = 0;
	for (post_row_id = 0; post_row_id < ARBITRATION_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < ARBITRATION_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < LEARNING_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < LEARNING_W; pre_col_id++) {
					pre_neuron_addr = learning_pathway_neurons[pre_row_id][pre_col_id];
					post_neuron_addr = arbitration_neurons_ex[post_row_id][post_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//connect learning pathway to learning pathway neurons
	real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	virtual_neuron_addr_enable = 0;
	for (post_row_id = 0; post_row_id < LEARNING_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < LEARNING_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L-1; pre_row_id++) {
				pre_neuron_addr = feature_layer_2_in[pre_row_id][0];
				post_neuron_addr = learning_pathway_neurons[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
			}
		}
	}

	//connect event source to motor neurons (with learning)
	real_virtual_synapse = REAL_SYNAPSE;
	virtual_neuron_addr_enable = 0;
	for (post_row_id = 0; post_row_id < MOTOR_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < MOTOR_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L-1; pre_row_id++) {
				pre_neuron_addr = feature_layer_0_in[pre_row_id][FEATURE_LAYER_EI_W-1];
				post_neuron_addr = motor_neurons_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
			}
		}
	}
	real_virtual_synapse = REAL_SYNAPSE;
	virtual_neuron_addr_enable = 0;
	for (post_row_id = 0; post_row_id < MOTOR_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < MOTOR_W; post_col_id++) {
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L-1; pre_row_id++) {
				pre_neuron_addr = feature_layer_2_in[pre_row_id][FEATURE_LAYER_EI_W-1];
				post_neuron_addr = motor_neurons_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
			}
		}
	}

}
