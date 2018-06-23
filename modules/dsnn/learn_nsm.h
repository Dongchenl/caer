static void learnNSMUpdate(int64_t nsm_winner_neuron_id, int64_t feature_neuron_address);
static void learnNSMConfigure(caerModuleData moduleData, int64_t nsm_winner_neuron_id);

void learnNSMUpdate(int64_t transition_neuron_address, int64_t state_neuron_address) {
	int64_t pre_neuron_addr = transition_neuron_address;
	int64_t post_neuron_addr = state_neuron_address;
	if (memory.connection_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {
		memory.post_neuron_activity_record->buffer2d[post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][0] = 1;
		if (memory.connection_map_ei->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {
			memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] += 1;
		} else {
			memory.delta_weight_map_in->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] += 1;
		}
	}
}

void learnNSMConfigure(caerModuleData moduleData, int64_t state_neuron_address) {
	int32_t weight, synapse_type;
	int32_t cam_id = 0;
	int64_t post_neuron_addr = state_neuron_address;
	for (int64_t pre_neuron_addr = 1024 + 256*3; pre_neuron_addr < 1024 + 256*4; pre_neuron_addr++) {
		synapse_type = 0;
		if (memory.connection_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {
			int32_t ei = memory.connection_map_ei->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
			if (ei == 1) {
				int64_t delta_weight = memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
				weight = memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
				if (delta_weight > 0) {
					memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] =
						weight + 1;
					weight = weight + 1;
				}
				else {
					memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] =
						weight - 1;
					weight = weight - 1;
				}
				memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
				if (weight > WEIGHT_THRESHOULD)
					synapse_type = 2;
			}
			else {
				int64_t delta_weight = memory.delta_weight_map_in->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
				weight = memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
				if (delta_weight > 0) {
					memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] =
						weight + 1;
					weight = weight + 1;
				}
				else {
					memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] =
						weight - 1;
					weight = weight - 1;
				}
				memory.delta_weight_map_in->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
				if (weight < WEIGHT_THRESHOULD)
					synapse_type = -2;
			}
			if (synapse_type != memory.synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET]) {
				cam_id = memory.synapse_map_cam_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
				writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
				memory.synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
				printf("Update NSM synapse. \n");
			}
		}
	}
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}
