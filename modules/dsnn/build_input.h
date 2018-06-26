static void buildInputNeurons(caerModuleData moduleData);

static void buildInputLayer0(caerModuleData moduleData);
static void buildInputLayer1(caerModuleData moduleData);

void buildInputNeurons(caerModuleData moduleData) {
	buildInputLayer0(moduleData);
	buildInputLayer1(moduleData);

	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}

void buildInputLayer0(caerModuleData moduleData) {
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
}

void buildInputLayer1(caerModuleData moduleData) {
	int64_t pre_row_id, pre_col_id, post_row_id, post_col_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse;
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
			for (pre_row_id = 0; pre_row_id < INPUT_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < INPUT_LAYER_EI_W; pre_col_id++) {
					if (pre_row_id == post_row_id && pre_col_id == post_col_id) {
						pre_neuron_addr = input_layer_0_ex[pre_row_id][pre_col_id];
						real_virtual_synapse = REAL_SYNAPSE;
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID);
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
	for (post_row_id = 0; post_row_id < INPUT_LAYER_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < INPUT_LAYER_EI_W; post_col_id++) {
			post_neuron_addr = input_layer_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					if (pre_row_id == FEATURE_LAYER_EI_L-1 && pre_col_id == FEATURE_LAYER_EI_W-1) { //
						pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id]; //input_layer_0_in
						real_virtual_synapse = VIRTUAL_SYNAPSE; //REAL_SYNAPSE_WITHOUT_LEARNING; //VIRTUAL_SYNAPSE;
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}

}
