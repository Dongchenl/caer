static void createInputNeurons(void);

//the input neurons for recognition
uint32_t input_layer_0_ex[INPUT_LAYER_EI_L][INPUT_LAYER_EI_W];
uint32_t input_layer_0_in[INPUT_LAYER_EI_L][INPUT_LAYER_EI_W];

//the input neurons for learning
uint32_t input_layer_1_ex[INPUT_LAYER_EI_L][INPUT_LAYER_EI_W];
uint32_t input_layer_1_in[INPUT_LAYER_EI_L][INPUT_LAYER_EI_W];

void createInputNeurons() {
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
}
