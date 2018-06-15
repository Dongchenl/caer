static void createNSMPopulations(void);

uint32_t nsm_state_input_0[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_state_input_1[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_state_input_2[NSM_L][NSM_W][NSM_SIZE];
//16 * 10 neurons
//core 1
uint32_t nsm_state_0[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_state_1[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_state_2[NSM_L][NSM_W][NSM_SIZE];

//core 2
uint32_t nsm_wta_ex[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_wta_in[NSM_L][NSM_W][NSM_SIZE];

//core 3
uint32_t nsm_1st_gate_0[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_1st_gate_1[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_1st_gate_2[NSM_L][NSM_W][NSM_SIZE];

uint32_t nsm_2nd_gate_0[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_2nd_gate_1[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_2nd_gate_2[NSM_L][NSM_W][NSM_SIZE];

uint32_t nsm_transition_0[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_transition_1[NSM_L][NSM_W][NSM_SIZE];
uint32_t nsm_transition_2[NSM_L][NSM_W][NSM_SIZE];

void createNSMPopulations(void) {
	//4 (2*2) neurons per population
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

				reference_row_id = NSM_SIZE / 2 * 2;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_state_input_2[row_id][col_id][neuron_id] = encoded_neuron_address;
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

				reference_row_id = NSM_SIZE / 2 * 2;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_state_2[row_id][col_id][neuron_id] = encoded_neuron_address;
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

				reference_row_id = NSM_SIZE / 2 * 5;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_1st_gate_2[row_id][col_id][neuron_id] = encoded_neuron_address;
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

				reference_row_id = NSM_SIZE / 2 * 2;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_2nd_gate_2[row_id][col_id][neuron_id] = encoded_neuron_address;
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

				reference_row_id = NSM_SIZE / 2 * 5;
				reference_col_id = 0;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				nsm_transition_2[row_id][col_id][neuron_id] = encoded_neuron_address;
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
}
