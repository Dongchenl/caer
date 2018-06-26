//for the arbitration mechanism
static void createArbitratorNeurons(void);

uint32_t motor_neurons_ex[MOTOR_L][MOTOR_W];
uint32_t motor_neurons_in[MOTOR_L][MOTOR_W];
uint32_t learning_pathway_neurons[LEARNING_L][LEARNING_W];
uint32_t arbitration_neurons_ex[ARBITRATION_L][ARBITRATION_W];
uint32_t arbitration_neurons_in[ARBITRATION_L][ARBITRATION_W];

void createArbitratorNeurons(void) {
	int64_t row_id, col_id;
	int64_t reference_row_id, reference_col_id;
	uint32_t chip_id, core_id, encoded_neuron_address;

	//learning pathway neurons
	for (row_id = 0; row_id < LEARNING_L; row_id++) {
		for (col_id = 0; col_id < LEARNING_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;
			core_id = CORE_UP_RIGHT_ID;
			reference_row_id = 10;
			reference_col_id = 14; //14;
			encoded_neuron_address = encodeNeuronAddress(chip_id, core_id,
				reference_row_id, reference_col_id,
				row_id, col_id);
			learning_pathway_neurons[row_id][col_id] = encoded_neuron_address;
		}
	}
	//motor neurons EX
	for (row_id = 0; row_id < MOTOR_L; row_id++) {
		for (col_id = 0; col_id < MOTOR_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;
			core_id = CORE_UP_RIGHT_ID;
			reference_row_id = 12;
			reference_col_id = 12; //12;
			encoded_neuron_address = encodeNeuronAddress(chip_id, core_id,
				reference_row_id, reference_col_id,
				row_id, col_id);
			motor_neurons_ex[row_id][col_id] = encoded_neuron_address;
		}
	}
	//motor neurons IN
	for (row_id = 0; row_id < MOTOR_L; row_id++) {
		for (col_id = 0; col_id < MOTOR_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;
			core_id = CORE_UP_RIGHT_ID;
			reference_row_id = 12;
			reference_col_id = 14; //14;
			encoded_neuron_address = encodeNeuronAddress(chip_id, core_id,
				reference_row_id, reference_col_id,
				row_id, col_id);
			motor_neurons_in[row_id][col_id] = encoded_neuron_address;
		}
	}
	//arbitration neurons EX
	for (row_id = 0; row_id < ARBITRATION_L; row_id++) {
		for (col_id = 0; col_id < ARBITRATION_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;
			core_id = CORE_UP_RIGHT_ID;
			reference_row_id = 14;
			reference_col_id = 12; //14;
			encoded_neuron_address = encodeNeuronAddress(chip_id, core_id,
				reference_row_id, reference_col_id,
				row_id, col_id);
			arbitration_neurons_ex[row_id][col_id] = encoded_neuron_address;
		}
	}
	//arbitration neurons IN
	for (row_id = 0; row_id < ARBITRATION_L; row_id++) {
		for (col_id = 0; col_id < ARBITRATION_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;
			core_id = CORE_UP_RIGHT_ID;
			reference_row_id = 14;
			reference_col_id = 14; //14;
			encoded_neuron_address = encodeNeuronAddress(chip_id, core_id,
				reference_row_id, reference_col_id,
				row_id, col_id);
			arbitration_neurons_in[row_id][col_id] = encoded_neuron_address;
		}
	}
}
