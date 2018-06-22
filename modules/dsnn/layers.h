static void createLayers(void);
static void buildInputLayer01(caerModuleData moduleData);
static void buildFeatureLayer0(caerModuleData moduleData);
static void buildFeatureLayer1(caerModuleData moduleData);
static void buildFeatureLayer2(caerModuleData moduleData);
static void buildFeatureLayer3(caerModuleData moduleData);

//the input neurons for recognition
uint32_t input_layer_0_ex[INPUT_LAYER_EI_L][INPUT_LAYER_EI_W];
uint32_t input_layer_0_in[INPUT_LAYER_EI_L][INPUT_LAYER_EI_W];

//the input neurons for learning
uint32_t input_layer_1_ex[INPUT_LAYER_EI_L][INPUT_LAYER_EI_W];
uint32_t input_layer_1_in[INPUT_LAYER_EI_L][INPUT_LAYER_EI_W];

//the feature neurons for recognition
uint32_t feature_layer_0_ex[FEATURE_LAYER_EI_L][FEATURE_LAYER_EI_W]; //on cells
uint32_t feature_layer_0_in[FEATURE_LAYER_EI_L][FEATURE_LAYER_EI_W]; //off cells

uint32_t feature_layer_1_ex[FEATURE_LAYER_EI_L][FEATURE_LAYER_EI_W]; //on cells
uint32_t feature_layer_1_in[FEATURE_LAYER_EI_L][FEATURE_LAYER_EI_W]; //off cells

//the feature neurons for learning
uint32_t feature_layer_2_ex[FEATURE_LAYER_EI_L][FEATURE_LAYER_EI_W]; //on cells
uint32_t feature_layer_2_in[FEATURE_LAYER_EI_L][FEATURE_LAYER_EI_W]; //off cells

uint32_t feature_layer_3_ex[FEATURE_LAYER_EI_L][FEATURE_LAYER_EI_W]; //on cells
uint32_t feature_layer_3_in[FEATURE_LAYER_EI_L][FEATURE_LAYER_EI_W]; //off cells

uint32_t output_layer_ex[OUTPUT_LAYER_EI_L][OUTPUT_LAYER_EI_W];

void createLayers() {
	int64_t row_id, col_id;
	uint32_t chip_id, encoded_neuron_address;
	//input layer 0
	for (row_id = 0; row_id < INPUT_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < INPUT_LAYER_EI_W; col_id++) {
			chip_id = CHIP_DOWN_RIGHT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id + TOTAL_NEURON_NUM_ON_CORE_X, col_id + TOTAL_NEURON_NUM_ON_CORE_Y);
			input_layer_0_ex[row_id][col_id] = encoded_neuron_address;
		}
	}
	for (row_id = 0; row_id < INPUT_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < INPUT_LAYER_EI_W; col_id++) {
			chip_id = CHIP_DOWN_RIGHT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id + TOTAL_NEURON_NUM_ON_CORE_X, col_id);
			input_layer_0_in[row_id][col_id] = encoded_neuron_address;
		}
	}
	//input layer 1
	for (row_id = 0; row_id < INPUT_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < INPUT_LAYER_EI_W; col_id++) {
			chip_id = CHIP_DOWN_RIGHT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id, col_id + TOTAL_NEURON_NUM_ON_CORE_Y);
			input_layer_1_ex[row_id][col_id] = encoded_neuron_address;
		}
	}
	for (row_id = 0; row_id < INPUT_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < INPUT_LAYER_EI_W; col_id++) {
			chip_id = CHIP_DOWN_RIGHT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id, col_id);
			input_layer_1_in[row_id][col_id] = encoded_neuron_address;
		}
	}

	//feature layer 0
	for (row_id = 0; row_id < FEATURE_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < FEATURE_LAYER_EI_W; col_id++) {
			chip_id = CHIP_UP_RIGHT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id, col_id + TOTAL_NEURON_NUM_ON_CORE_Y);
			feature_layer_0_ex[row_id][col_id] = encoded_neuron_address;
		}
	}
	for (row_id = 0; row_id < FEATURE_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < FEATURE_LAYER_EI_W; col_id++) {
			chip_id = CHIP_UP_RIGHT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id, col_id);
			feature_layer_0_in[row_id][col_id] = encoded_neuron_address;
		}
	}
	//feature layer 1
	for (row_id = 0; row_id < FEATURE_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < FEATURE_LAYER_EI_W; col_id++) {
			chip_id = CHIP_UP_RIGHT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id + TOTAL_NEURON_NUM_ON_CORE_X, col_id + TOTAL_NEURON_NUM_ON_CORE_Y);
			feature_layer_1_ex[row_id][col_id] = encoded_neuron_address;
		}
	}
	for (row_id = 0; row_id < FEATURE_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < FEATURE_LAYER_EI_W; col_id++) {
			chip_id = CHIP_UP_RIGHT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id + TOTAL_NEURON_NUM_ON_CORE_X, col_id);
			feature_layer_1_in[row_id][col_id] = encoded_neuron_address;
		}
	}
	//feature layer 2
	for (row_id = 0; row_id < FEATURE_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < FEATURE_LAYER_EI_W; col_id++) {
			chip_id = CHIP_DOWN_LEFT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id, col_id + TOTAL_NEURON_NUM_ON_CORE_Y);
			feature_layer_2_ex[row_id][col_id] = encoded_neuron_address;
		}
	}
	for (row_id = 0; row_id < FEATURE_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < FEATURE_LAYER_EI_W; col_id++) {
			chip_id = CHIP_DOWN_LEFT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id, col_id);
			feature_layer_2_in[row_id][col_id] = encoded_neuron_address;
		}
	}
	//feature layer 3
	for (row_id = 0; row_id < FEATURE_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < FEATURE_LAYER_EI_W; col_id++) {
			chip_id = CHIP_DOWN_LEFT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id + TOTAL_NEURON_NUM_ON_CORE_X, col_id + TOTAL_NEURON_NUM_ON_CORE_Y);
			feature_layer_3_ex[row_id][col_id] = encoded_neuron_address;
		}
	}
	for (row_id = 0; row_id < FEATURE_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < FEATURE_LAYER_EI_W; col_id++) {
			chip_id = CHIP_DOWN_LEFT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id + TOTAL_NEURON_NUM_ON_CORE_X, col_id);
			feature_layer_3_in[row_id][col_id] = encoded_neuron_address;
		}
	}
	//output layer
	for (row_id = 0; row_id < OUTPUT_LAYER_EI_L; row_id++) {
		for (col_id = 0; col_id < OUTPUT_LAYER_EI_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id + TOTAL_NEURON_NUM_ON_CORE_X, col_id + TOTAL_NEURON_NUM_ON_CORE_Y);
			output_layer_ex[row_id][col_id] = encoded_neuron_address;
		}
	}

}

void buildInputLayer01(caerModuleData moduleData) {
	int64_t pre_row_id, pre_col_id, post_row_id, post_col_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse;
	//input 0 EX to input 0 IN
	for (post_row_id = 0; post_row_id < INPUT_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < INPUT_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = input_layer_0_in[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < INPUT_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < INPUT_LAYER_EI_W; pre_col_id++) {
					if (pre_row_id == post_row_id && pre_col_id == post_col_id) {
						pre_neuron_addr = input_layer_0_ex[pre_row_id][pre_col_id];
						real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
	//input 1 EX to input 1 IN
	for (post_row_id = 0; post_row_id < INPUT_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < INPUT_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = input_layer_1_in[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < INPUT_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < INPUT_LAYER_EI_W; pre_col_id++) {
					if (pre_row_id == post_row_id && pre_col_id == post_col_id) {
						pre_neuron_addr = input_layer_1_ex[pre_row_id][pre_col_id];
						real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}

	for (post_row_id = 0; post_row_id < INPUT_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < INPUT_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = input_layer_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					if (pre_row_id == FEATURE_LAYER_EI_L-1 && pre_col_id == FEATURE_LAYER_EI_W-1) { //
						pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id]; //input_layer_0_in
						real_virtual_synapse = VIRTUAL_SYNAPSE; //REAL_SYNAPSE_WITHOUT_LEARNING; //VIRTUAL_SYNAPSE;
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}

	for (post_row_id = 0; post_row_id < OUTPUT_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < OUTPUT_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = output_layer_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					if (pre_row_id == FEATURE_LAYER_EI_L-1 && pre_col_id == FEATURE_LAYER_EI_W-1 &&
						post_row_id == OUTPUT_LAYER_EI_L-1 && post_col_id == OUTPUT_LAYER_EI_W-1) { //
						pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id]; //input_layer_0_in[0][0];
						real_virtual_synapse = VIRTUAL_SYNAPSE; //REAL_SYNAPSE_WITHOUT_LEARNING; //VIRTUAL_SYNAPSE;
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
	for (post_row_id = 0; post_row_id < OUTPUT_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < OUTPUT_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = output_layer_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					if (pre_row_id == FEATURE_LAYER_EI_L-1 && pre_col_id == FEATURE_LAYER_EI_W-1 &&
						post_row_id == OUTPUT_LAYER_EI_L-1 && post_col_id == OUTPUT_LAYER_EI_W-2) { //
						pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id]; //input_layer_0_in[0][0];
						real_virtual_synapse = VIRTUAL_SYNAPSE; //REAL_SYNAPSE_WITHOUT_LEARNING; //VIRTUAL_SYNAPSE;
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}

}

void buildFeatureLayer0(caerModuleData moduleData) {
	int64_t pre_row_id, pre_col_id, post_row_id, post_col_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse;
	//feature layer 1 EX to IN
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_0_in[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					if (pre_row_id == post_row_id && pre_col_id == post_col_id) {
						pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
						real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
	//excitation 1
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_0_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < INPUT_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < INPUT_LAYER_EI_W; pre_col_id++) {
					if (post_col_id >= KERNEL_EDGE/2 && post_col_id <= 15 - KERNEL_EDGE/2) { //horizontal
						if (pre_row_id >= (post_row_id - KERNEL_EDGE/2) && pre_row_id < (post_row_id - KERNEL_EDGE/2) + KERNEL_EDGE &&
							pre_col_id >= (post_col_id - KERNEL_EDGE/2) && pre_col_id < (post_col_id - KERNEL_EDGE/2) + KERNEL_EDGE) {
							if (pre_row_id == post_row_id) { //horizontal
								pre_neuron_addr = input_layer_0_ex[pre_row_id][pre_col_id];
								real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
							}
						}
					}
				}
			}
		}
	}
	//inhibition 1
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_0_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < INPUT_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < INPUT_LAYER_EI_W; pre_col_id++) {
					if (post_col_id >= KERNEL_EDGE/2 && post_col_id <= 15 - KERNEL_EDGE/2) { //horizontal
						if (pre_row_id >= (post_row_id - KERNEL_EDGE/2) && pre_row_id < (post_row_id - KERNEL_EDGE/2) + KERNEL_EDGE &&
							pre_col_id >= (post_col_id - KERNEL_EDGE/2) && pre_col_id < (post_col_id - KERNEL_EDGE/2) + KERNEL_EDGE) {
							if (pre_row_id == post_row_id) { //horizontal
								pre_neuron_addr = input_layer_0_in[pre_row_id][pre_col_id];
								real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
							}
						}
					}
				}
			}
		}
	}
}

void buildFeatureLayer1(caerModuleData moduleData) {
	int64_t pre_row_id, pre_col_id, post_row_id, post_col_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse;
	//Build synapses from on cells to off cells
	virtual_neuron_addr_enable = 0;
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_1_in[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					if (pre_row_id == post_row_id && pre_col_id == post_col_id) {
						pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
						real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
	//Build synapses from input layer to the on cells
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < INPUT_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < INPUT_LAYER_EI_W; pre_col_id++) {
					if (post_row_id >= KERNEL_EDGE/2 && post_row_id <= 15 - KERNEL_EDGE/2) { //vertical
						if (pre_row_id >= (post_row_id - KERNEL_EDGE/2) && pre_row_id < (post_row_id - KERNEL_EDGE/2) + KERNEL_EDGE &&
							pre_col_id >= (post_col_id - KERNEL_EDGE/2) && pre_col_id < (post_col_id - KERNEL_EDGE/2) + KERNEL_EDGE) {
							if (pre_col_id == post_col_id) { //vertical
								pre_neuron_addr = input_layer_0_ex[pre_row_id][pre_col_id];
								real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
							}
						}
					}
				}
			}
		}
	}
	//inhibition 2
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < INPUT_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < INPUT_LAYER_EI_W; pre_col_id++) {
					if (post_row_id >= KERNEL_EDGE/2 && post_row_id <= 15 - KERNEL_EDGE/2) { //vertical
						if (pre_row_id >= (post_row_id - KERNEL_EDGE/2) && pre_row_id < (post_row_id - KERNEL_EDGE/2) + KERNEL_EDGE &&
							pre_col_id >= (post_col_id - KERNEL_EDGE/2) && pre_col_id < (post_col_id - KERNEL_EDGE/2) + KERNEL_EDGE) {
							if (pre_col_id == post_col_id) { //vertical
								pre_neuron_addr = input_layer_0_in[pre_row_id][pre_col_id];
								real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
							}
						}
					}
				}
			}
		}
	}
}

void buildFeatureLayer2(caerModuleData moduleData) {
	int64_t pre_row_id, pre_col_id, post_row_id, post_col_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse;
	//feature layer 1 EX to IN
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_2_in[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					if (pre_row_id == post_row_id && pre_col_id == post_col_id) {
						pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
						real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
	//excitation 1
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_2_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < INPUT_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < INPUT_LAYER_EI_W; pre_col_id++) {
					if (post_col_id >= KERNEL_EDGE/2 && post_col_id <= 15 - KERNEL_EDGE/2) { //horizontal
						if (pre_row_id >= (post_row_id - KERNEL_EDGE/2) && pre_row_id < (post_row_id - KERNEL_EDGE/2) + KERNEL_EDGE &&
							pre_col_id >= (post_col_id - KERNEL_EDGE/2) && pre_col_id < (post_col_id - KERNEL_EDGE/2) + KERNEL_EDGE) {
							if (pre_row_id == post_row_id) { //horizontal
								pre_neuron_addr = input_layer_1_ex[pre_row_id][pre_col_id];
								real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
							}
						}
					}
				}
			}
		}
	}
	//inhibition 1
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_2_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < INPUT_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < INPUT_LAYER_EI_W; pre_col_id++) {
					if (post_col_id >= KERNEL_EDGE/2 && post_col_id <= 15 - KERNEL_EDGE/2) { //horizontal
						if (pre_row_id >= (post_row_id - KERNEL_EDGE/2) && pre_row_id < (post_row_id - KERNEL_EDGE/2) + KERNEL_EDGE &&
							pre_col_id >= (post_col_id - KERNEL_EDGE/2) && pre_col_id < (post_col_id - KERNEL_EDGE/2) + KERNEL_EDGE) {
							if (pre_row_id == post_row_id) { //horizontal
								pre_neuron_addr = input_layer_1_in[pre_row_id][pre_col_id];
								real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
							}
						}
					}
				}
			}
		}
	}
}

void buildFeatureLayer3(caerModuleData moduleData) {
	int64_t pre_row_id, pre_col_id, post_row_id, post_col_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse;
	//feature layer 2 EX to IN
	virtual_neuron_addr_enable = 0;
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_3_in[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					if (pre_row_id == post_row_id && pre_col_id == post_col_id) {
						pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
						real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
	//excitation 2
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_3_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < INPUT_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < INPUT_LAYER_EI_W; pre_col_id++) {
					if (post_row_id >= KERNEL_EDGE/2 && post_row_id <= 15 - KERNEL_EDGE/2) { //vertical
						if (pre_row_id >= (post_row_id - KERNEL_EDGE/2) && pre_row_id < (post_row_id - KERNEL_EDGE/2) + KERNEL_EDGE &&
							pre_col_id >= (post_col_id - KERNEL_EDGE/2) && pre_col_id < (post_col_id - KERNEL_EDGE/2) + KERNEL_EDGE) {
							if (pre_col_id == post_col_id) { //vertical
								pre_neuron_addr = input_layer_1_ex[pre_row_id][pre_col_id];
								real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
							}
						}
					}
				}
			}
		}
	}
	//inhibition 2
	for (post_row_id = 0; post_row_id < FEATURE_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < FEATURE_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = feature_layer_3_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < INPUT_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < INPUT_LAYER_EI_W; pre_col_id++) {
					if (post_row_id >= KERNEL_EDGE/2 && post_row_id <= 15 - KERNEL_EDGE/2) { //vertical
						if (pre_row_id >= (post_row_id - KERNEL_EDGE/2) && pre_row_id < (post_row_id - KERNEL_EDGE/2) + KERNEL_EDGE &&
							pre_col_id >= (post_col_id - KERNEL_EDGE/2) && pre_col_id < (post_col_id - KERNEL_EDGE/2) + KERNEL_EDGE) {
							if (pre_col_id == post_col_id) { //vertical
								pre_neuron_addr = input_layer_1_in[pre_row_id][pre_col_id];
								real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
							}
						}
					}
				}
			}
		}
	}
}
