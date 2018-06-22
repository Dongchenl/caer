static int8_t set_first_ts = 0;
static int8_t ini_finished = 0;
static int64_t first_ts;
static int64_t recording_first_ts;

static int8_t set_first_ts_output = 0;
static int8_t ini_finished_output = 0;
static int64_t first_ts_output;
static int64_t recording_first_ts_output;

static int8_t set_first_ts_output_check = 0;
static int8_t ini_finished_output_check = 0;
static int64_t first_ts_output_check;
static int64_t recording_first_ts_output_check;

static int64_t post_spike_time = 0;

static void updateMemory(int64_t post_neuron_addr);
static void updateConfiguration(caerModuleData moduleData);
static int64_t count_neighbor(int64_t post_neuron_addr);
static void filter_neighbor(int64_t post_neuron_addr);
static void updateMemoryCheck(int64_t post_neuron_addr);
static struct check_return updateConfigurationCheck(void);

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

/*
	for (int64_t post_neuron_addr = (4 << 10) | (1 << 8) | 0; post_neuron_addr <= ((4 << 10) | (1 << 8) | 255); post_neuron_addr++) {
		int64_t row_id = (post_neuron_addr & NEURON_ROW_BITS) >> NEURON_ROW_SHIFT;
		int64_t col_id = post_neuron_addr & NEURON_COL_BITS;
		int64_t new_row_id;
		int64_t new_col_id;
		int64_t neighbor_pixel_sum = 0;
		int64_t new_post_neuron_addr;
		if (row_id >= 1) {
			new_row_id = row_id - 1;
			new_col_id = col_id;
			new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
			if (memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2) {
				neighbor_pixel_sum += 1;
			}
		}
		if (row_id <= 14) {
			new_row_id = row_id + 1;
			new_col_id = col_id;
			new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
			if (memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2) {
				neighbor_pixel_sum += 1;
			}
		}
		if (col_id >= 1) {
			new_row_id = row_id;
			new_col_id = col_id - 1;
			new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
			if (memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2) {
				neighbor_pixel_sum += 1;
			}
		}
		if (col_id <= 14) {
			new_row_id = row_id;
			new_col_id = col_id + 1;
			new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
			if (memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2) {
				neighbor_pixel_sum += 1;
			}
		}
		if (row_id >= 1 && col_id >= 1) {
			new_row_id = row_id - 1;
			new_col_id = col_id - 1;
			new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
			if (memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2) {
				neighbor_pixel_sum += 1;
			}
		}
		if (row_id <= 14 && col_id >= 1) {
			new_row_id = row_id + 1;
			new_col_id = col_id - 1;
			new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
			if (memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2) {
				neighbor_pixel_sum += 1;
			}
		}
		if (row_id >= 1 && col_id <= 14) {
			new_row_id = row_id - 1;
			new_col_id = col_id + 1;
			new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
			if (memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2) {
				neighbor_pixel_sum += 1;
			}
		}
		if (row_id <= 14 && col_id <= 14) {
			new_row_id = row_id + 1;
			new_col_id = col_id + 1;
			new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
			if (memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2) {
				neighbor_pixel_sum += 1;
			}
		}
		if (neighbor_pixel_sum < 1) {
//			printf("Cancel learned synapse. \n");
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
		}
	}
*/
	//find the maximum neighbor
	int64_t neighbor_maximum_num[ARTIFICIAL_WINNERS_NUM];
	int64_t neighbor_maximum_address[ARTIFICIAL_WINNERS_NUM];
	for (int64_t item_id = 0; item_id < ARTIFICIAL_WINNERS_NUM; item_id++) {
		neighbor_maximum_num[item_id] = 0;
		neighbor_maximum_address[item_id] = 0;
	}

	for (int64_t post_neuron_addr = (4 << 10) | (1 << 8) | 0; post_neuron_addr <= ((4 << 10) | (1 << 8) | 255); post_neuron_addr++) {
		memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
	}

	for (int64_t item_id = 0; item_id < ARTIFICIAL_WINNERS_NUM; item_id++) {
		for (int64_t post_neuron_addr = (4 << 10) | (1 << 8) | 0; post_neuron_addr <= ((4 << 10) | (1 << 8) | 255); post_neuron_addr++) {
			for (int64_t post_neuron_addr_t = (4 << 10) | (1 << 8) | 0; post_neuron_addr_t <= ((4 << 10) | (1 << 8) | 255); post_neuron_addr_t++) {
				memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr_t - MEMORY_NEURON_ADDR_OFFSET] = 0;
			}
			int64_t neighbor_num = count_neighbor(post_neuron_addr);
			if (neighbor_num > neighbor_maximum_num[item_id]) {
				neighbor_maximum_num[item_id] = neighbor_num;
				neighbor_maximum_address[item_id] = post_neuron_addr;
			}
		}
		if (neighbor_maximum_address[item_id] != 0) {
			for (int64_t post_neuron_addr = (4 << 10) | (1 << 8) | 0; post_neuron_addr <= ((4 << 10) | (1 << 8) | 255); post_neuron_addr++) {
				memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
			}
			filter_neighbor(neighbor_maximum_address[item_id]);
		}
	}

/*
	if (neighbor_maximum_num > 200) {
		printf("Too many events. \n");
		return;
	}
*/

	int64_t minimum_spike_num = CONSIDERED_SPIKES_THRESHOULD;
	int64_t maximum_spike_num = 0;
	for (int64_t post_neuron_addr = (4 << 10) | (1 << 8) | 0; post_neuron_addr <= ((4 << 10) | (1 << 8) | 255); post_neuron_addr++) {
		if (memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2) {
			int64_t filtered_weight = memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
			if (filtered_weight < minimum_spike_num)
				minimum_spike_num = filtered_weight; //CONSIDERED_SPIKES_THRESHOULD; //filtered_weight;
			if (filtered_weight > maximum_spike_num)
				maximum_spike_num = filtered_weight; //0; //filtered_weight;
		}
		memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
	}

	for (int64_t post_neuron_addr = (4 << 10) | (1 << 8) | 0; post_neuron_addr <= ((4 << 10) | (1 << 8) | 255); post_neuron_addr++) {
		synapse_type = memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET]; //weight_map
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
//	printf("Mim %d, Max %d spikes. \n", (int) pixel_minimum_num, (int) pixel_maximum_num);
//	printf("Mim %d, Max %d filtered spikes. \n", (int) minimum_spike_num, (int) maximum_spike_num);

	int64_t learned_pixels_num;
	for (int64_t item_id = 0; item_id < ARTIFICIAL_WINNERS_NUM; item_id++) {
		learned_pixels_num += neighbor_maximum_num[item_id];
	}
	if (learned_pixels_num >= LEARNED_PIXELS_THRESHOLD) {
//		printf("%d captured pixels, %d selected pixels >= %d. \n", (int) pixel_num, (int) learned_pixels_num, LEARNED_PIXELS_THRESHOLD);
		learned_pixels_above_threshold = 1;
	} else {
//		printf("%d captured pixels, %d selected pixels < %d. \n", (int) pixel_num, (int) learned_pixels_num, LEARNED_PIXELS_THRESHOLD);
		learned_pixels_above_threshold = 0;
	}
}

int64_t count_neighbor(int64_t post_neuron_addr) {
	int64_t row_id = (post_neuron_addr & NEURON_ROWID_BITS) >> NEURON_ROWID_SHIFT;
	int64_t col_id = post_neuron_addr & NEURON_COLID_BITS;
	int64_t new_row_id;
	int64_t new_col_id;
	int64_t pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1]; //4 << 10 | 2 << 8 | 0;
	int64_t neighbor_num = 1;
	int64_t new_post_neuron_addr;
	memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
	if (row_id >= 1) {
		new_row_id = row_id - 1;
		new_col_id = col_id;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
//			memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
			neighbor_num += count_neighbor(new_post_neuron_addr);
		}
	}
	if (row_id <= 14) {
		new_row_id = row_id + 1;
		new_col_id = col_id;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
//			memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
			neighbor_num += count_neighbor(new_post_neuron_addr);
		}
	}
	if (col_id >= 1) {
		new_row_id = row_id;
		new_col_id = col_id - 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
//			memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
			neighbor_num += count_neighbor(new_post_neuron_addr);
		}
	}
	if (col_id <= 14) {
		new_row_id = row_id;
		new_col_id = col_id + 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
//			memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
			neighbor_num += count_neighbor(new_post_neuron_addr);
		}
	}
	if (row_id >= 1 && col_id >= 1) {
		new_row_id = row_id - 1;
		new_col_id = col_id - 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
//			memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
			neighbor_num += count_neighbor(new_post_neuron_addr);
		}
	}
	if (row_id <= 14 && col_id >= 1) {
		new_row_id = row_id + 1;
		new_col_id = col_id - 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
//			memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
			neighbor_num += count_neighbor(new_post_neuron_addr);
		}
	}
	if (row_id >= 1 && col_id <= 14) {
		new_row_id = row_id - 1;
		new_col_id = col_id + 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
//			memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
			neighbor_num += count_neighbor(new_post_neuron_addr);
		}
	}
	if (row_id <= 14 && col_id <= 14) {
		new_row_id = row_id + 1;
		new_col_id = col_id + 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
//			memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
			neighbor_num += count_neighbor(new_post_neuron_addr);
		}
	}
	return (neighbor_num);
}

void filter_neighbor(int64_t post_neuron_addr) {
	int64_t row_id = (post_neuron_addr & NEURON_ROWID_BITS) >> NEURON_ROWID_SHIFT;
	int64_t col_id = post_neuron_addr & NEURON_COLID_BITS;
	int64_t new_row_id;
	int64_t new_col_id;
	int64_t pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1]; //4 << 10 | 2 << 8 | 0;
//	int64_t neighbor_num = 1;
	int64_t new_post_neuron_addr;
	memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
	memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 2;
	if (row_id >= 1) {
		new_row_id = row_id - 1;
		new_col_id = col_id;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
			filter_neighbor(new_post_neuron_addr);
		}
	}
	if (row_id <= 14) {
		new_row_id = row_id + 1;
		new_col_id = col_id;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
			filter_neighbor(new_post_neuron_addr);
		}
	}
	if (col_id >= 1) {
		new_row_id = row_id;
		new_col_id = col_id - 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
			filter_neighbor(new_post_neuron_addr);
		}
	}
	if (col_id <= 14) {
		new_row_id = row_id;
		new_col_id = col_id + 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
			filter_neighbor(new_post_neuron_addr);
		}
	}
	if (row_id >= 1 && col_id >= 1) {
		new_row_id = row_id - 1;
		new_col_id = col_id - 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
			filter_neighbor(new_post_neuron_addr);
		}
	}
	if (row_id <= 14 && col_id >= 1) {
		new_row_id = row_id + 1;
		new_col_id = col_id - 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
			filter_neighbor(new_post_neuron_addr);
		}
	}
	if (row_id >= 1 && col_id <= 14) {
		new_row_id = row_id - 1;
		new_col_id = col_id + 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
			filter_neighbor(new_post_neuron_addr);
		}
	}
	if (row_id <= 14 && col_id <= 14) {
		new_row_id = row_id + 1;
		new_col_id = col_id + 1;
		new_post_neuron_addr = (4 << 10) | (1 << 8) | (new_row_id << 4) | new_col_id;
		if (memory.neighbor_count_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0 &&
			memory.weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 2 &&
			memory.filtered_weight_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] == 0) {
			filter_neighbor(new_post_neuron_addr);
		}
	}
}

void updateMemoryCheck(int64_t post_neuron_addr) {
	int64_t pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1]; //4 << 10 | 2 << 8 | 0;
	memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] += 1;;
}

struct check_return updateConfigurationCheck() {
	int64_t pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1]; //4 << 10 | 2 << 8 | 0;
	int64_t feature_neurons_num = 0;
	int64_t feature_neurons_original_num = 0;
	for (int64_t post_neuron_addr = (3 << 10) | (1 << 8) | 0; post_neuron_addr <= ((3 << 10) | (1 << 8) | 255); post_neuron_addr++) {
		int64_t delta_weight = memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
		if (delta_weight > NUM_SPIKES_THRESHOULD_CHECK) {
			feature_neurons_num += 1;
		}
		if (delta_weight > 0) {
			feature_neurons_original_num += 1;
		}
		memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
	}
	for (int64_t post_neuron_addr = (3 << 10) | (3 << 8) | 0; post_neuron_addr <= ((3 << 10) | (3 << 8) | 255); post_neuron_addr++) {
		int64_t delta_weight = memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
		if (delta_weight > NUM_SPIKES_THRESHOULD_CHECK) {
			feature_neurons_num += 1;
		}
		if (delta_weight > 0) {
			feature_neurons_original_num += 1;
		}
		memory.delta_weight_map_ex->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 0;
	}
	struct check_return feature_neurons_satistics = {feature_neurons_num, feature_neurons_original_num};
	return(feature_neurons_satistics);
}
