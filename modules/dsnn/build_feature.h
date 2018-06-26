static void buildFeatureNeurons(caerModuleData moduleData);
static void buildFeatureLayer0(caerModuleData moduleData);
static void buildFeatureLayer1(caerModuleData moduleData);
static void buildFeatureLayer2(caerModuleData moduleData);
static void buildFeatureLayer3(caerModuleData moduleData);

void buildFeatureNeurons(caerModuleData moduleData) {
	buildFeatureLayer0(moduleData);
	buildFeatureLayer1(moduleData);
	buildFeatureLayer2(moduleData);
	buildFeatureLayer3(moduleData);

	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
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
			post_neuron_addr = feature_layer_0_ex[post_row_id][post_col_id];
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
			post_neuron_addr = feature_layer_1_ex[post_row_id][post_col_id];
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
