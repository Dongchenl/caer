static void createNSMPopulations(void);

uint32_t nsm_state_input_0[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_state_input_1[NSM_L][NSM_W][NSM_SIZE];

uint32_t nsm_state_0[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_state_1[NSM_L][NSM_W][NSM_SIZE];

uint32_t nsm_wta_ex[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_wta_in[NSM_L][NSM_W][NSM_SIZE];

uint32_t nsm_1st_gate_0[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_1st_gate_1[NSM_L][NSM_W][NSM_SIZE];

uint32_t nsm_2nd_gate_0[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_2nd_gate_1[NSM_L][NSM_W][NSM_SIZE];

uint32_t nsm_transition_0[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_transition_1[NSM_L][NSM_W][NSM_SIZE];

uint32_t output_selecting_neurons[NSM_L][NSM_W][NSM_SIZE];

uint32_t motor_neurons[MOTOR_L][MOTOR_W];
uint32_t hub_neurons[HUB_L][HUB_W];
uint32_t learning_neurons[LEARNING_L][LEARNING_W];
uint32_t arbitration_neurons[ARBITRATION_L][ARBITRATION_W];

void createNSMPopulations(void) {
	int64_t row_id, col_id;
	int64_t reference_row_id, reference_col_id;
	uint32_t chip_id, core_id, neuron_id, encoded_neuron_address;

	//external input
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (neuron_id = 0; neuron_id < NSM_SIZE; neuron_id++) {
				chip_id = CHIP_UP_LEFT_ID;
				core_id = CORE_UP_LEFT_ID;
				reference_row_id = 0;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_state_input_0[row_id][col_id][neuron_id] = encoded_neuron_address;

				reference_row_id = NSM_SIZE / 2 * 1;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_state_input_1[row_id][col_id][neuron_id] = encoded_neuron_address;
			}
		}
	}
	//state neurons
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (neuron_id = 0; neuron_id < NSM_SIZE; neuron_id++) {
				chip_id = CHIP_UP_LEFT_ID;
				core_id = CORE_UP_RIGHT_ID;
				reference_row_id = 0;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_state_0[row_id][col_id][neuron_id] = encoded_neuron_address;

				reference_row_id = NSM_SIZE / 2 * 1;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_state_1[row_id][col_id][neuron_id] = encoded_neuron_address;
			}
		}
	}
	//first gate neurons
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (neuron_id = 0; neuron_id < NSM_SIZE; neuron_id++) {
				chip_id = CHIP_UP_LEFT_ID;
				core_id = CORE_UP_RIGHT_ID;
				reference_row_id = NSM_SIZE / 2 * 3;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_1st_gate_0[row_id][col_id][neuron_id] = encoded_neuron_address;

				reference_row_id = NSM_SIZE / 2 * 4;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_1st_gate_1[row_id][col_id][neuron_id] = encoded_neuron_address;
			}
		}
	}
	//second gate neurons
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (neuron_id = 0; neuron_id < NSM_SIZE; neuron_id++) {
				chip_id = CHIP_UP_LEFT_ID;
				core_id = CORE_DOWN_RIGHT_ID;
				reference_row_id = 0;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_2nd_gate_0[row_id][col_id][neuron_id] = encoded_neuron_address;

				reference_row_id = NSM_SIZE / 2 * 1;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_2nd_gate_1[row_id][col_id][neuron_id] = encoded_neuron_address;
			}
		}
	}
	//transition neurons
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (neuron_id = 0; neuron_id < NSM_SIZE; neuron_id++) {
				chip_id = CHIP_UP_LEFT_ID;
				core_id = CORE_DOWN_RIGHT_ID;
				reference_row_id = NSM_SIZE / 2 * 3;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_transition_0[row_id][col_id][neuron_id] = encoded_neuron_address;

				reference_row_id = NSM_SIZE / 2 * 4;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_transition_1[row_id][col_id][neuron_id] = encoded_neuron_address;
			}
		}
	}
	//WTA neurons
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (neuron_id = 0; neuron_id < NSM_SIZE; neuron_id++) {
				chip_id = CHIP_UP_LEFT_ID;
				core_id = CORE_DOWN_RIGHT_ID;
				reference_row_id = NSM_SIZE / 2 * 6;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_wta_ex[row_id][col_id][neuron_id] = encoded_neuron_address;

				reference_row_id = NSM_SIZE / 2 * 7;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_wta_in[row_id][col_id][neuron_id] = encoded_neuron_address;
			}
		}
	}
	//output_selecting_neurons
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (neuron_id = 0; neuron_id < NSM_SIZE; neuron_id++) {
				chip_id = CHIP_UP_LEFT_ID;
				core_id = CORE_DOWN_RIGHT_ID;
				reference_row_id = 0;
				reference_col_id = NSM_SIZE / 2 *4;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				output_selecting_neurons[row_id][col_id][neuron_id] = encoded_neuron_address;
			}
		}
	}
	//motor neurons
	for (row_id = 0; row_id < MOTOR_L; row_id++) {
		for (col_id = 0; col_id < MOTOR_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;
			core_id = CORE_UP_RIGHT_ID;
			reference_row_id = 12;
			reference_col_id = 12; //12;
			encoded_neuron_address = encodeNeuronAddress(chip_id, core_id,
				reference_row_id, reference_col_id,
				row_id, col_id);
			motor_neurons[row_id][col_id] = encoded_neuron_address;
		}
	}
	//hub neurons
	for (row_id = 0; row_id < HUB_L; row_id++) {
		for (col_id = 0; col_id < HUB_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;
			core_id = CORE_UP_RIGHT_ID;
			reference_row_id = 14;
			reference_col_id = 14; //14;
			encoded_neuron_address = encodeNeuronAddress(chip_id, core_id,
				reference_row_id, reference_col_id,
				row_id, col_id);
			hub_neurons[row_id][col_id] = encoded_neuron_address;
		}
	}
	//learning neurons
	for (row_id = 0; row_id < LEARNING_L; row_id++) {
		for (col_id = 0; col_id < LEARNING_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;
			core_id = CORE_UP_RIGHT_ID;
			reference_row_id = 14;
			reference_col_id = 12; //14;
			encoded_neuron_address = encodeNeuronAddress(chip_id, core_id,
				reference_row_id, reference_col_id,
				row_id, col_id);
			learning_neurons[row_id][col_id] = encoded_neuron_address;
		}
	}
	//arbitration neurons
	for (row_id = 0; row_id < ARBITRATION_L; row_id++) {
		for (col_id = 0; col_id < ARBITRATION_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;
			core_id = CORE_UP_RIGHT_ID;
			reference_row_id = 12;
			reference_col_id = 14; //14;
			encoded_neuron_address = encodeNeuronAddress(chip_id, core_id,
				reference_row_id, reference_col_id,
				row_id, col_id);
			arbitration_neurons[row_id][col_id] = encoded_neuron_address;
		}
	}
}
