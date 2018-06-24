static void removeNotReadySignal(caerModuleData moduleData);
static void applyNotReadySignal(caerModuleData moduleData);

void removeNotReadySignal(caerModuleData moduleData) {
	if (not_ready_added == 1) {
		int64_t pre_row_id, post_row_id, post_col_id, post_neuron_id;
		uint32_t pre_neuron_addr, post_neuron_addr;
		int32_t cam_id, synapse_type;
		for (post_row_id = 0; post_row_id < NSM_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < NSM_W; post_col_id++) {
				for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
					for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L-1; pre_row_id++) {
						pre_neuron_addr = feature_layer_0_in[pre_row_id][FEATURE_LAYER_EI_W-1];
						post_neuron_addr = nsm_state_1[post_row_id][post_col_id][post_neuron_id];
						cam_id = memory.synapse_map_cam_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
						synapse_type = 0;
						writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);

						post_neuron_addr = nsm_transition_1[post_row_id][post_col_id][post_neuron_id];
						cam_id = memory.synapse_map_cam_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
						synapse_type = 0;
						writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					}
				}
			}
		}
		not_ready_added = 0;
	}
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}

void applyNotReadySignal(caerModuleData moduleData) {
	if (not_ready_added == 0) {
		int64_t pre_row_id, post_row_id, post_col_id, post_neuron_id;
		uint32_t pre_neuron_addr, post_neuron_addr;
		int32_t cam_id, synapse_type;
		for (post_row_id = 0; post_row_id < NSM_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < NSM_W; post_col_id++) {
				for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
					for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L-1; pre_row_id++) {
						pre_neuron_addr = feature_layer_0_in[pre_row_id][FEATURE_LAYER_EI_W-1];
						post_neuron_addr = nsm_state_1[post_row_id][post_col_id][post_neuron_id];
						cam_id = memory.synapse_map_cam_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
						synapse_type = 2;
						writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);

						post_neuron_addr = nsm_transition_1[post_row_id][post_col_id][post_neuron_id];
						cam_id = memory.synapse_map_cam_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET];
						synapse_type = -2;
						writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);
					}
				}
			}
		}
		not_ready_added = 1;
	}
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}
