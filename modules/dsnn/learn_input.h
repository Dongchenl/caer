static void updateMemory(int64_t post_neuron_addr);
static void updateConfiguration(caerModuleData moduleData);

void updateMemory(int64_t post_neuron_addr) {
	int64_t pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1];
	if (memory.connection_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {
		if (memory.connection_map_ei->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1)
			memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] += 1;
	}
}

void updateConfiguration(caerModuleData moduleData) {
	int32_t synapse_type, current_synapse_type;
	int32_t cam_id = 0;
	int64_t pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1]; //4 << 10 | 2 << 8 | 0;
	int64_t pixel_num = 0;
	int64_t pixel_minimum_num = CONSIDERED_SPIKES_THRESHOULD;
	int64_t pixel_maximum_num = 0;
	for (int64_t post_neuron_addr = (4 << 10) | (1 << 8) | 0; post_neuron_addr <= ((4 << 10) | (1 << 8) | 255); post_neuron_addr++) {
		if (memory.connection_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {
			if (memory.connection_map_ei->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {
				int64_t delta_weight = memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
				if (delta_weight > NUM_SPIKES_THRESHOULD) {
					memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 2;
					memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
					pixel_num += 1;
					if (delta_weight < pixel_minimum_num)
						pixel_minimum_num = delta_weight;
					if (delta_weight > pixel_maximum_num)
						pixel_maximum_num = delta_weight;
				}
				else
					memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0; //test 2; //real 0;
			}
		}
	}

	for (int64_t post_neuron_addr = (4 << 10) | (1 << 8) | 0; post_neuron_addr <= ((4 << 10) | (1 << 8) | 255); post_neuron_addr++) {
		synapse_type = memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET]; //weight_map
		current_synapse_type = memory.synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
		if (current_synapse_type != synapse_type) {
			writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
			memory.synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
		}
	}

	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}
