static void createOutputNeurons(void);

uint32_t column_0_0_ex[COLUMN_X_0_EI_L][COLUMN_X_0_EI_W];
uint32_t column_0_1_ex[COLUMN_X_1_EI_L][COLUMN_X_1_EI_W];
uint32_t column_0_2_ex[COLUMN_X_2_EI_L][COLUMN_X_2_EI_W];
uint32_t column_0_3_ex[COLUMN_X_3_EI_L][COLUMN_X_3_EI_W];

uint32_t column_1_0_ex[COLUMN_X_0_EI_L][COLUMN_X_0_EI_W];
uint32_t column_1_1_ex[COLUMN_X_1_EI_L][COLUMN_X_1_EI_W];
uint32_t column_1_2_ex[COLUMN_X_2_EI_L][COLUMN_X_2_EI_W];
uint32_t column_1_3_ex[COLUMN_X_3_EI_L][COLUMN_X_3_EI_W];

uint32_t column_2_0_ex[COLUMN_X_0_EI_L][COLUMN_X_0_EI_W];
uint32_t column_2_1_ex[COLUMN_X_1_EI_L][COLUMN_X_1_EI_W];
uint32_t column_2_2_ex[COLUMN_X_2_EI_L][COLUMN_X_2_EI_W];
uint32_t column_2_3_ex[COLUMN_X_3_EI_L][COLUMN_X_3_EI_W];

uint32_t column_3_0_ex[COLUMN_X_0_EI_L][COLUMN_X_0_EI_W];
uint32_t column_3_1_ex[COLUMN_X_1_EI_L][COLUMN_X_1_EI_W];
uint32_t column_3_2_ex[COLUMN_X_2_EI_L][COLUMN_X_2_EI_W];
uint32_t column_3_3_ex[COLUMN_X_3_EI_L][COLUMN_X_3_EI_W];

uint32_t column_output_ex[COLUMN_OUTPUT_EI_L][COLUMN_OUTPUT_EI_W];
uint32_t output_population_ex[OUTPUT_POPULATION_EI_L][OUTPUT_POPULATION_EI_W][OUTPUT_POPULATION_EI_SIZE];
uint32_t output_population_in[OUTPUT_POPULATION_EI_L][OUTPUT_POPULATION_EI_W][OUTPUT_POPULATION_EI_SIZE];

void createOutputNeurons(void) {
	int64_t row_id, col_id, neuron_id;
	int64_t reference_row_id, reference_col_id;
	int64_t row_id_shift, col_id_shift;
	uint32_t core_id, chip_id;
	uint32_t encoded_neuron_address;

	for (row_id = 0; row_id < COLUMN_X_0_EI_L; row_id++) {
		for (col_id = 0; col_id < COLUMN_X_0_EI_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;

			row_id_shift = 0;
			col_id_shift = 0;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id, col_id_shift + col_id);
			column_0_0_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = 0;
			col_id_shift = TOTAL_NEURON_NUM_ON_CORE_X / 2;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id, col_id_shift + col_id);
			column_1_0_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = TOTAL_NEURON_NUM_ON_CORE_Y;
			col_id_shift = 0;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id, col_id_shift + col_id);
			column_2_0_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = TOTAL_NEURON_NUM_ON_CORE_Y;
			col_id_shift = TOTAL_NEURON_NUM_ON_CORE_X / 2;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id, col_id_shift + col_id);
			column_3_0_ex[row_id][col_id] = encoded_neuron_address;
		}
	}
	for (row_id = 0; row_id < COLUMN_X_1_EI_L; row_id++) {
		for (col_id = 0; col_id < COLUMN_X_1_EI_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;

			row_id_shift = 0;
			col_id_shift = 0;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1, col_id_shift + col_id);
			column_0_1_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = 0;
			col_id_shift = TOTAL_NEURON_NUM_ON_CORE_X / 2;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1, col_id_shift + col_id);
			column_1_1_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = TOTAL_NEURON_NUM_ON_CORE_Y;
			col_id_shift = 0;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1, col_id_shift + col_id);
			column_2_1_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = TOTAL_NEURON_NUM_ON_CORE_Y;
			col_id_shift = TOTAL_NEURON_NUM_ON_CORE_X / 2;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1, col_id_shift + col_id);
			column_3_1_ex[row_id][col_id] = encoded_neuron_address;
		}
	}
	for (row_id = 0; row_id < COLUMN_X_2_EI_L; row_id++) {
		for (col_id = 0; col_id < COLUMN_X_2_EI_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;

			row_id_shift = 0;
			col_id_shift = 0;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1 + 3, col_id_shift + col_id);
			column_0_2_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = 0;
			col_id_shift = TOTAL_NEURON_NUM_ON_CORE_X / 2;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1 + 3, col_id_shift + col_id);
			column_1_2_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = TOTAL_NEURON_NUM_ON_CORE_Y;
			col_id_shift = 0;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1 + 3, col_id_shift + col_id);
			column_2_2_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = TOTAL_NEURON_NUM_ON_CORE_Y;
			col_id_shift = TOTAL_NEURON_NUM_ON_CORE_X / 2;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1 + 3, col_id_shift + col_id);
			column_3_2_ex[row_id][col_id] = encoded_neuron_address;
		}
	}
	for (row_id = 0; row_id < COLUMN_X_3_EI_L; row_id++) {
		for (col_id = 0; col_id < COLUMN_X_3_EI_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;

			row_id_shift = 0;
			col_id_shift = 0;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1 + 3 + 5, col_id_shift + col_id);
			column_0_3_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = 0;
			col_id_shift = TOTAL_NEURON_NUM_ON_CORE_X / 2;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1 + 3 + 5, col_id_shift + col_id);
			column_1_3_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = TOTAL_NEURON_NUM_ON_CORE_Y;
			col_id_shift = 0;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1 + 3 + 5, col_id_shift + col_id);
			column_2_3_ex[row_id][col_id] = encoded_neuron_address;

			row_id_shift = TOTAL_NEURON_NUM_ON_CORE_Y;
			col_id_shift = TOTAL_NEURON_NUM_ON_CORE_X / 2;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id, row_id_shift + row_id + 1 + 3 + 5, col_id_shift + col_id);
			column_3_3_ex[row_id][col_id] = encoded_neuron_address;
		}
	}

	for (row_id = 0; row_id < COLUMN_OUTPUT_EI_L; row_id++) {
		for (col_id = 0; col_id < COLUMN_OUTPUT_EI_W; col_id++) {
			chip_id = CHIP_UP_LEFT_ID;
			encoded_neuron_address = encodeNeuronAddress4Chip(chip_id,
				row_id + TOTAL_NEURON_NUM_ON_CORE_Y + OUTPUT_POPULATION_EI_SIZE / 2 * 3,
				col_id + TOTAL_NEURON_NUM_ON_CORE_X + OUTPUT_POPULATION_EI_SIZE / 2 * OUTPUT_POPULATION_EI_W);
			column_output_ex[row_id][col_id] = encoded_neuron_address;
		}
	}

	for (row_id = 0; row_id < OUTPUT_POPULATION_EI_L; row_id++) {
		for (col_id = 0; col_id < OUTPUT_POPULATION_EI_W; col_id++) {
			for (neuron_id = 0; neuron_id < OUTPUT_POPULATION_EI_SIZE; neuron_id++) {
				chip_id = CHIP_UP_LEFT_ID;
				core_id = CORE_DOWN_RIGHT_ID;
				reference_row_id = OUTPUT_POPULATION_EI_SIZE / 2 * 6;
				reference_col_id = OUTPUT_POPULATION_EI_SIZE / 2 * OUTPUT_POPULATION_EI_W;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				output_population_ex[row_id][col_id][neuron_id] = encoded_neuron_address;
			}
		}
	}

	for (row_id = 0; row_id < OUTPUT_POPULATION_EI_L; row_id++) {
		for (col_id = 0; col_id < OUTPUT_POPULATION_EI_W; col_id++) {
			for (neuron_id = 0; neuron_id < OUTPUT_POPULATION_EI_SIZE; neuron_id++) {
				chip_id = CHIP_UP_LEFT_ID;
				core_id = CORE_DOWN_RIGHT_ID;
				reference_row_id = OUTPUT_POPULATION_EI_SIZE / 2 * 5;
				reference_col_id = OUTPUT_POPULATION_EI_SIZE / 2 * OUTPUT_POPULATION_EI_W;
				encoded_neuron_address = encodeNeuronAddress4Core(chip_id, core_id,
					reference_row_id, reference_col_id,
					row_id, col_id, neuron_id);
				output_population_in[row_id][col_id][neuron_id] = encoded_neuron_address;
			}
		}
	}

}
