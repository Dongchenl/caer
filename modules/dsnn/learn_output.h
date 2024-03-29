static void learnColumnUpdate(int64_t nsm_winner_neuron_id, int64_t feature_neuron_address);
static void learnColumnConfigure(caerModuleData moduleData, int64_t nsm_winner_neuron_id);

void learnColumnUpdate(int64_t feature_neuron_address, int64_t output_neuron_address) {
	int64_t pre_neuron_addr = feature_neuron_address;
	int64_t post_neuron_addr = output_neuron_address;
	if (memory.connection_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {
		memory.post_neuron_activity_record->buffer2d[post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][0] = 1;
		if (memory.connection_map_ei->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {
			memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] += 1;
		} else {
			memory.delta_weight_map_in->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] += 1;
		}
	}
}

void learnColumnConfigure(caerModuleData moduleData, int64_t output_neuron_address) {
	int32_t weight, synapse_type;
	int32_t cam_id = 0;
	int64_t post_neuron_addr = output_neuron_address;
	int32_t num_ex = 0;
	int32_t num_in = 0;

	for (int64_t pre_neuron_addr = 1024 + 1024*2; pre_neuron_addr < 1024 + 1024*3; pre_neuron_addr++) {
		synapse_type = 0;
		if (memory.connection_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 1) {
			int32_t ei = memory.connection_map_ei->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
			if (ei == 1) {
				int64_t delta_weight = memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
				weight = memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
				if (delta_weight > 0) { //10
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

			if (synapse_type != memory.synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] &&
				synapse_type != 0) {
				int64_t pre_chip_id = (pre_neuron_addr & NEURON_CHIPID_BITS) >> NEURON_CHIPID_SHIFT;
				int64_t pre_core_id = (pre_neuron_addr & NEURON_COREID_BITS) >> NEURON_COREID_SHIFT;
				int64_t pre_neuron_id = (pre_neuron_addr & NEURON_NEURONID_BITS) >> NEURON_NEURONID_SHIFT;

				if (!(pre_chip_id == 3 && pre_core_id == 0 &&
						(pre_neuron_id == 39 || pre_neuron_id == 86 || pre_neuron_id == 105 || pre_neuron_id == 166)) &&
					!(pre_chip_id == 3 && pre_core_id == 2 &&
						(pre_neuron_id == 152 || pre_neuron_id == 179))) {
					learnMultipleScable(moduleData, pre_neuron_addr, output_neuron_address, synapse_type, cam_id);
					cam_id++;
					if (synapse_type > 0) {
						num_ex += 1;
					} else if (synapse_type < 0) {
						num_in += 1;
					}
				}
			}

			if (cam_id >= LAST_CAM_ID_OUTPUT_NEURON) { //63
				printf("Warning! No enough CAMs. %d %d \n", num_ex, num_in);
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
				return;
			}
		}
	}
	printf("Learn %d EX synapses, %d IN synapses. \n", num_ex, num_in);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}


