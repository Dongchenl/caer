static void createFeatureNeurons(void);

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

void createFeatureNeurons() {
	int64_t row_id, col_id;
	uint32_t chip_id, encoded_neuron_address;
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
}
