static void learnMultipleScable(caerModuleData moduleData, int64_t pre_neuron_addr, int64_t nsm_winner_neuron_id, int32_t synapse_type, int32_t cam_id);

void learnMultipleScable(caerModuleData moduleData, int64_t pre_neuron_addr, int64_t nsm_winner_neuron_id, int32_t synapse_type, int32_t cam_id) {

	int64_t pre_chip_id = (pre_neuron_addr & NEURON_CHIPID_BITS) >> NEURON_CHIPID_SHIFT;
	int64_t pre_core_id = (pre_neuron_addr & NEURON_COREID_BITS) >> NEURON_COREID_SHIFT;
	int64_t pre_row_id = (pre_neuron_addr & NEURON_ROWID_BITS) >> NEURON_ROWID_SHIFT;
	int64_t pre_col_id = (pre_neuron_addr & NEURON_COLID_BITS) >> NEURON_COLID_SHIFT;

//	int32_t post_neuron_id = (post_neuron_addr & NEURON_NEURONID_BITS) >> NEURON_NEURONID_SHIFT;

	if (nsm_winner_neuron_id == 0) {
		int64_t post_neuron_addr = column_0_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
//		printf("Write CAMs for output %d. Pre: %d. Post: %d. Synapse type: %d. CAM ID: %d. \n", (int) nsm_winner_neuron_id, (int) pre_neuron_addr, (int) post_neuron_addr, synapse_type, cam_id);
		writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
		memory.synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
		memory.synapse_map_cam_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;

		for (int post_row_id = 0; post_row_id < COLUMN_X_1_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_1_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_0_1_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 3)
					new_pre_row_id = pre_row_id + 1 + post_row_id - (int) (COLUMN_X_1_EI_L/2);
				else if (pre_row_id >= 8 + 3)
					new_pre_row_id = pre_row_id - 1 + post_row_id - (int) (COLUMN_X_1_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id  - (int) (COLUMN_X_1_EI_L/2);

				if (pre_col_id <= 7 - 3)
					new_pre_col_id = pre_col_id + 1 + post_col_id - (int) (COLUMN_X_1_EI_W/2);
				else if (pre_col_id >= 8 + 3)
					new_pre_col_id = pre_col_id - 1 + post_col_id - (int) (COLUMN_X_1_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_1_EI_W/2);

				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
		for (int post_row_id = 0; post_row_id < COLUMN_X_2_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_2_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_0_2_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 2)
					new_pre_row_id = pre_row_id + 2 + post_row_id - (int) (COLUMN_X_2_EI_L/2);
				else if (pre_row_id >= 8 + 2)
					new_pre_row_id = pre_row_id - 2 + post_row_id - (int) (COLUMN_X_2_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id - (int) (COLUMN_X_2_EI_L/2);

				if (pre_col_id <= 7 - 2)
					new_pre_col_id = pre_col_id + 2 + post_col_id - (int) (COLUMN_X_2_EI_W/2);
				else if (pre_col_id >= 8 + 2)
					new_pre_col_id = pre_col_id - 2 + post_col_id - (int) (COLUMN_X_2_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_2_EI_W/2);

				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
		for (int post_row_id = 0; post_row_id < COLUMN_X_3_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_3_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_0_3_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 1)
					new_pre_row_id = min((pre_row_id + 3),8) + post_row_id - (int) (COLUMN_X_3_EI_L/2);
				else if (pre_row_id >= 8 + 1)
					new_pre_row_id = max((pre_row_id - 3),7) + post_row_id - (int) (COLUMN_X_3_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id - (int) (COLUMN_X_3_EI_L/2);

				if (pre_col_id <= 7 - 1)
					new_pre_col_id = min((pre_col_id + 3),8) + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				else if (pre_col_id >= 8 + 1)
					new_pre_col_id = max((pre_col_id - 3),7) + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
	} else if (nsm_winner_neuron_id == 1) {
		int64_t post_neuron_addr = column_1_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
//		printf("Write CAMs for output %d. Pre: %d. Post: %d. Synapse type: %d. CAM ID: %d. \n", (int) nsm_winner_neuron_id, (int) pre_neuron_addr, (int) post_neuron_addr, synapse_type, cam_id);
		writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
		memory.synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
		memory.synapse_map_cam_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;

		for (int post_row_id = 0; post_row_id < COLUMN_X_1_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_1_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_1_1_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 3)
					new_pre_row_id = pre_row_id + 1 + post_row_id - (int) (COLUMN_X_1_EI_L/2);
				else if (pre_row_id >= 8 + 3)
					new_pre_row_id = pre_row_id - 1 + post_row_id - (int) (COLUMN_X_1_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id  - (int) (COLUMN_X_1_EI_L/2);

				if (pre_col_id <= 7 - 3)
					new_pre_col_id = pre_col_id + 1 + post_col_id - (int) (COLUMN_X_1_EI_W/2);
				else if (pre_col_id >= 8 + 3)
					new_pre_col_id = pre_col_id - 1 + post_col_id - (int) (COLUMN_X_1_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_1_EI_W/2);

				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
		for (int post_row_id = 0; post_row_id < COLUMN_X_2_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_2_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_1_2_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 2)
					new_pre_row_id = pre_row_id + 2 + post_row_id - (int) (COLUMN_X_2_EI_L/2);
				else if (pre_row_id >= 8 + 2)
					new_pre_row_id = pre_row_id - 2 + post_row_id - (int) (COLUMN_X_2_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id - (int) (COLUMN_X_2_EI_L/2);

				if (pre_col_id <= 7 - 2)
					new_pre_col_id = pre_col_id + 2 + post_col_id - (int) (COLUMN_X_2_EI_W/2);
				else if (pre_col_id >= 8 + 2)
					new_pre_col_id = pre_col_id - 2 + post_col_id - (int) (COLUMN_X_2_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_2_EI_W/2);

				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
		for (int post_row_id = 0; post_row_id < COLUMN_X_3_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_3_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_1_3_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 1)
					new_pre_row_id = min((pre_row_id + 3),8) + post_row_id - (int) (COLUMN_X_3_EI_L/2);
				else if (pre_row_id >= 8 + 1)
					new_pre_row_id = max((pre_row_id - 3),7) + post_row_id - (int) (COLUMN_X_3_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id - (int) (COLUMN_X_3_EI_L/2);

				if (pre_col_id <= 7 - 1)
					new_pre_col_id = min((pre_col_id + 3),8) + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				else if (pre_col_id >= 8 + 1)
					new_pre_col_id = max((pre_col_id - 3),7) + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
	} else if (nsm_winner_neuron_id == 2) {
		int64_t post_neuron_addr = column_2_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
//		printf("Write CAMs for output %d. Pre: %d. Post: %d. Synapse type: %d. CAM ID: %d. \n", (int) nsm_winner_neuron_id, (int) pre_neuron_addr, (int) post_neuron_addr, synapse_type, cam_id);
		writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
		memory.synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
		memory.synapse_map_cam_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;

		for (int post_row_id = 0; post_row_id < COLUMN_X_1_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_1_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_2_1_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 3)
					new_pre_row_id = pre_row_id + 1 + post_row_id - (int) (COLUMN_X_1_EI_L/2);
				else if (pre_row_id >= 8 + 3)
					new_pre_row_id = pre_row_id - 1 + post_row_id - (int) (COLUMN_X_1_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id  - (int) (COLUMN_X_1_EI_L/2);

				if (pre_col_id <= 7 - 3)
					new_pre_col_id = pre_col_id + 1 + post_col_id - (int) (COLUMN_X_1_EI_W/2);
				else if (pre_col_id >= 8 + 3)
					new_pre_col_id = pre_col_id - 1 + post_col_id - (int) (COLUMN_X_1_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_1_EI_W/2);

				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
		for (int post_row_id = 0; post_row_id < COLUMN_X_2_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_2_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_2_2_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 2)
					new_pre_row_id = pre_row_id + 2 + post_row_id - (int) (COLUMN_X_2_EI_L/2);
				else if (pre_row_id >= 8 + 2)
					new_pre_row_id = pre_row_id - 2 + post_row_id - (int) (COLUMN_X_2_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id - (int) (COLUMN_X_2_EI_L/2);

				if (pre_col_id <= 7 - 2)
					new_pre_col_id = pre_col_id + 2 + post_col_id - (int) (COLUMN_X_2_EI_W/2);
				else if (pre_col_id >= 8 + 2)
					new_pre_col_id = pre_col_id - 2 + post_col_id - (int) (COLUMN_X_2_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_2_EI_W/2);

				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
		for (int post_row_id = 0; post_row_id < COLUMN_X_3_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_3_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_2_3_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 1)
					new_pre_row_id = min((pre_row_id + 3),8) + post_row_id - (int) (COLUMN_X_3_EI_L/2);
				else if (pre_row_id >= 8 + 1)
					new_pre_row_id = max((pre_row_id - 3),7) + post_row_id - (int) (COLUMN_X_3_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id - (int) (COLUMN_X_3_EI_L/2);

				if (pre_col_id <= 7 - 1)
					new_pre_col_id = min((pre_col_id + 3),8) + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				else if (pre_col_id >= 8 + 1)
					new_pre_col_id = max((pre_col_id - 3),7) + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
	} else if (nsm_winner_neuron_id == 3) {
		int64_t post_neuron_addr = column_3_0_ex[COLUMN_X_0_EI_L-1][COLUMN_X_0_EI_W-1];
//		printf("Write CAMs for output %d. Pre: %d. Post: %d. Synapse type: %d. CAM ID: %d. \n", (int) nsm_winner_neuron_id, (int) pre_neuron_addr, (int) post_neuron_addr, synapse_type, cam_id);
		writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
		memory.synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
		memory.synapse_map_cam_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;

		for (int post_row_id = 0; post_row_id < COLUMN_X_1_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_1_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_3_1_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 3)
					new_pre_row_id = pre_row_id + 1 + post_row_id - (int) (COLUMN_X_1_EI_L/2);
				else if (pre_row_id >= 8 + 3)
					new_pre_row_id = pre_row_id - 1 + post_row_id - (int) (COLUMN_X_1_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id  - (int) (COLUMN_X_1_EI_L/2);

				if (pre_col_id <= 7 - 3)
					new_pre_col_id = pre_col_id + 1 + post_col_id - (int) (COLUMN_X_1_EI_W/2);
				else if (pre_col_id >= 8 + 3)
					new_pre_col_id = pre_col_id - 1 + post_col_id - (int) (COLUMN_X_1_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_1_EI_W/2);

				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
		for (int post_row_id = 0; post_row_id < COLUMN_X_2_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_2_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_3_2_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 2)
					new_pre_row_id = pre_row_id + 2 + post_row_id - (int) (COLUMN_X_2_EI_L/2);
				else if (pre_row_id >= 8 + 2)
					new_pre_row_id = pre_row_id - 2 + post_row_id - (int) (COLUMN_X_2_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id - (int) (COLUMN_X_2_EI_L/2);

				if (pre_col_id <= 7 - 2)
					new_pre_col_id = pre_col_id + 2 + post_col_id - (int) (COLUMN_X_2_EI_W/2);
				else if (pre_col_id >= 8 + 2)
					new_pre_col_id = pre_col_id - 2 + post_col_id - (int) (COLUMN_X_2_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_2_EI_W/2);

				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
		for (int post_row_id = 0; post_row_id < COLUMN_X_3_EI_L; post_row_id++) {
			for (int post_col_id = 0; post_col_id < COLUMN_X_3_EI_W; post_col_id++) {
				uint32_t new_post_neuron_addr = column_3_3_ex[post_row_id][post_col_id];

				int64_t new_pre_row_id, new_pre_col_id;
				if (pre_row_id <= 7 - 1)
					new_pre_row_id = min((pre_row_id + 3),8) + post_row_id - (int) (COLUMN_X_3_EI_L/2);
				else if (pre_row_id >= 8 + 1)
					new_pre_row_id = max((pre_row_id - 3),7) + post_row_id - (int) (COLUMN_X_3_EI_L/2);
				else
					new_pre_row_id = pre_row_id + post_row_id - (int) (COLUMN_X_3_EI_L/2);

				if (pre_col_id <= 7 - 1)
					new_pre_col_id = min((pre_col_id + 3),8) + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				else if (pre_col_id >= 8 + 1)
					new_pre_col_id = max((pre_col_id - 3),7) + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				else
					new_pre_col_id = pre_col_id + post_col_id - (int) (COLUMN_X_3_EI_W/2);
				int64_t new_pre_neuron_addr = pre_chip_id << 10 | pre_core_id << 8 | new_pre_row_id << 4 | new_pre_col_id;
				if (memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] != synapse_type) {
					writeCamDSNN(moduleData, (uint32_t) new_pre_neuron_addr, (uint32_t) new_post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					memory.synapse_map_type->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
					memory.synapse_map_cam_no->buffer2d[new_pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][new_post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = cam_id;
				}
			}
		}
	}

}