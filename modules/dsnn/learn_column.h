static void learnColumnUpdate(int64_t nsm_winner_neuron_id, int64_t feature_neuron_address);
static void learnColumnConfigure(caerModuleData moduleData, int64_t nsm_winner_neuron_id);
static void shiftWinner(caerModuleData moduleData, int64_t nsm_winner_neuron_id);

void learnColumnUpdate(int64_t nsm_winner_neuron_id, int64_t feature_neuron_address) {
	int64_t pre_neuron_addr = feature_neuron_address;
	int64_t post_neuron_addr;
	if (nsm_winner_neuron_id == 0)
		post_neuron_addr = column_0_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
	else if (nsm_winner_neuron_id == 1)
		post_neuron_addr = column_1_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
	else if (nsm_winner_neuron_id == 2)
		post_neuron_addr = column_2_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
	else if (nsm_winner_neuron_id == 3)
		post_neuron_addr = column_3_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
	if (memory.connection_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {

		memory.post_neuron_activity_record->buffer2d[post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][0] = 1;

		if (memory.connection_map_ei->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1)
			memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1; //+= 1;
		else
			memory.delta_weight_map_in->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1; //+= 1;
	}
}

void learnColumnConfigure(caerModuleData moduleData, int64_t nsm_winner_neuron_id) {
	int32_t synapse_type;
	int32_t cam_id = 0;
	int64_t post_neuron_addr; // int64_t post_neuron_addr = 1 << 10 | 0 << 8 | nsm_winner_neuron_id;
	int32_t num_ex = 0;
	int32_t num_in = 0;
	if (nsm_winner_neuron_id == 0)
		post_neuron_addr = column_0_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
	else if (nsm_winner_neuron_id == 1)
		post_neuron_addr = column_1_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
	else if (nsm_winner_neuron_id == 2)
		post_neuron_addr = column_2_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
	else if (nsm_winner_neuron_id == 3)
		post_neuron_addr = column_3_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
	for (int64_t pre_neuron_addr = 1024 + 1024*1; pre_neuron_addr < 1024 + 1024*2; pre_neuron_addr++) { //virtual address?
		if (memory.connection_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {
			if (memory.connection_map_ei->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {
				int64_t delta_weight = memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
				if (delta_weight > 0) { //10
					memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 2;
					memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
				} else {
					memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
					memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
				}
			} else {
				int64_t delta_weight = memory.delta_weight_map_in->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
				if (delta_weight > 0) { //10
					memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
					memory.delta_weight_map_in->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
				} else {
					memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = -2;
					memory.delta_weight_map_in->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
				}
			}

			synapse_type = memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];

			if (synapse_type != memory.synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] &&
				synapse_type != 0) {
				int64_t pre_chip_id = (pre_neuron_addr & NEURON_CHIPID_BITS) >> NEURON_CHIPID_SHIFT;
				int64_t pre_core_id = (pre_neuron_addr & NEURON_COREID_BITS) >> NEURON_COREID_SHIFT;
				int64_t pre_neuron_id = (pre_neuron_addr & NEURON_NEURONID_BITS) >> NEURON_NEURONID_SHIFT;
				if (!(pre_chip_id == 3 && pre_core_id == 0 && (pre_neuron_id == 39 || pre_neuron_id == 86 || pre_neuron_id == 105 || pre_neuron_id == 166)) &&
					!(pre_chip_id == 3 && pre_core_id == 2 && (pre_neuron_id == 152 || pre_neuron_id == 179))) {
					learnMultipleScable(moduleData, pre_neuron_addr, nsm_winner_neuron_id, synapse_type, cam_id);
					cam_id++;
					if (synapse_type > 0) {
						num_ex += 1;
					} else if (synapse_type < 0) {
						num_in += 1;
					}
				}
			}
			if (cam_id > 63) {
				return;
			}
		}
	}
	printf("@@@@ Learn %d EX synapses, %d IN synapses. Current winner NSM %d is shifted. \n", num_ex, num_in, (int) nsm_winner_neuron_id);
	shiftWinner(moduleData, nsm_winner_neuron_id);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}

void shiftWinner(caerModuleData moduleData, int64_t nsm_winner_neuron_id) {
	int64_t pre_row_id, post_row_id, post_col_id, post_neuron_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
//	pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1];
	for (post_row_id = 0; post_row_id < NSM_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < NSM_W; post_col_id++) {
			for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
				if (post_col_id == nsm_winner_neuron_id) {
					for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L-1; pre_row_id++) {
						pre_neuron_addr = feature_layer_0_in[pre_row_id][FEATURE_LAYER_EI_W-1];

						post_neuron_addr = nsm_state_2[post_row_id][post_col_id][post_neuron_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

						post_neuron_addr = nsm_transition_2[post_row_id][post_col_id][post_neuron_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
}