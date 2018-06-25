static void buildColumn(caerModuleData moduleData);
static void connectColumnSynapses(caerModuleData moduleData);
static void connectColumnSynapses4Learning(caerModuleData moduleData);
static void connectColumnSynapses4Recognition(caerModuleData moduleData);
static void connectColumn2Output(caerModuleData moduleData);
static void connectOutput2Output(caerModuleData moduleData);
static void connectOutputSelectingNeuronsToColumns(caerModuleData moduleData);

void buildColumn(caerModuleData moduleData) {
	createColumnPopulations();
	connectColumnSynapses(moduleData);
}

void connectColumnSynapses(caerModuleData moduleData) {
	connectColumnSynapses4Learning(moduleData);
	connectColumnSynapses4Recognition(moduleData);
	connectColumn2Output(moduleData);
	connectOutput2Output(moduleData);
	connectOutputSelectingNeuronsToColumns(moduleData);

	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}

void connectColumnSynapses4Learning(caerModuleData moduleData) {
	int64_t pre_row_id, pre_col_id, post_row_id, post_col_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = VIRTUAL_SYNAPSE; //VIRTUAL_SYNAPSE_WITHOUT_SRAM
	//for the first scale
	for (post_row_id = 0; post_row_id < COLUMN_X_0_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_X_0_EI_W; post_col_id++) {
			post_neuron_addr = column_0_0_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_1_0_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_2_0_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_3_0_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//for the second scale
	for (post_row_id = 0; post_row_id < COLUMN_X_1_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_X_1_EI_W; post_col_id++) {
			post_neuron_addr = column_0_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_1_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_2_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_3_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//for the third scale
	for (post_row_id = 0; post_row_id < COLUMN_X_2_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_X_2_EI_W; post_col_id++) {
			post_neuron_addr = column_0_2_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_1_2_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_2_2_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_3_2_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//for the fourth scale
	for (post_row_id = 0; post_row_id < COLUMN_X_3_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_X_3_EI_W; post_col_id++) {
			post_neuron_addr = column_0_3_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_1_3_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_2_3_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_3_3_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_2_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_2_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_3_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
}

void connectColumnSynapses4Recognition(caerModuleData moduleData) {
	int64_t pre_row_id, pre_col_id, post_row_id, post_col_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = VIRTUAL_SYNAPSE;
	//for the first scale
	for (post_row_id = 0; post_row_id < COLUMN_X_0_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_X_0_EI_W; post_col_id++) {
			post_neuron_addr = column_0_0_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_1_0_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_2_0_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_3_0_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//for the second scale
	for (post_row_id = 0; post_row_id < COLUMN_X_1_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_X_1_EI_W; post_col_id++) {
			post_neuron_addr = column_0_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_1_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_2_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_3_1_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//for the third scale
	for (post_row_id = 0; post_row_id < COLUMN_X_2_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_X_2_EI_W; post_col_id++) {
			post_neuron_addr = column_0_2_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_1_2_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_2_2_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_3_2_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
	//for the fourth scale
	for (post_row_id = 0; post_row_id < COLUMN_X_3_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_X_3_EI_W; post_col_id++) {
			post_neuron_addr = column_0_3_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_1_3_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_2_3_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}

			post_neuron_addr = column_3_3_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < FEATURE_LAYER_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < FEATURE_LAYER_EI_W; pre_col_id++) {
					pre_neuron_addr = feature_layer_0_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_ex[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = feature_layer_0_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					pre_neuron_addr = feature_layer_1_in[pre_row_id][pre_col_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
}

void connectColumn2Output(caerModuleData moduleData) {
	int64_t pre_row_id, pre_col_id, post_row_id, post_col_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	for (post_row_id = 0; post_row_id < COLUMN_OUTPUT_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_OUTPUT_EI_W; post_col_id++) {
			post_neuron_addr = column_output_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < COLUMN_X_0_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_0_EI_W; pre_col_id++) {
					if (post_row_id == 0 && post_col_id == 0) {
						pre_neuron_addr = column_0_0_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_0_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_0_EI_W; pre_col_id++) {
					if (post_row_id == 0 && post_col_id == 1) {
						pre_neuron_addr = column_1_0_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_0_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_0_EI_W; pre_col_id++) {
					if (post_row_id == 0 && post_col_id == 2) {
						pre_neuron_addr = column_2_0_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_0_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_0_EI_W; pre_col_id++) {
					if (post_row_id == 0 && post_col_id == 3) {
						pre_neuron_addr = column_3_0_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}

	for (post_row_id = 0; post_row_id < COLUMN_OUTPUT_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_OUTPUT_EI_W; post_col_id++) {
			post_neuron_addr = column_output_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < COLUMN_X_1_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_1_EI_W; pre_col_id++) {
					if (post_row_id == 1 && post_col_id == 0) {
						pre_neuron_addr = column_0_1_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_1_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_1_EI_W; pre_col_id++) {
					if (post_row_id == 1 && post_col_id == 1) {
						pre_neuron_addr = column_1_1_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_1_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_1_EI_W; pre_col_id++) {
					if (post_row_id == 1 && post_col_id == 2) {
						pre_neuron_addr = column_2_1_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_1_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_1_EI_W; pre_col_id++) {
					if (post_row_id == 1 && post_col_id == 3) {
						pre_neuron_addr = column_3_1_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}

	for (post_row_id = 0; post_row_id < COLUMN_OUTPUT_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_OUTPUT_EI_W; post_col_id++) {
			post_neuron_addr = column_output_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < COLUMN_X_2_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_2_EI_W; pre_col_id++) {
					if (post_row_id == 2 && post_col_id == 0) {
						pre_neuron_addr = column_0_2_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_2_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_2_EI_W; pre_col_id++) {
					if (post_row_id == 2 && post_col_id == 1) {
						pre_neuron_addr = column_1_2_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_2_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_2_EI_W; pre_col_id++) {
					if (post_row_id == 2 && post_col_id == 2) {
						pre_neuron_addr = column_2_2_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_2_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_2_EI_W; pre_col_id++) {
					if (post_row_id == 2 && post_col_id == 3) {
						pre_neuron_addr = column_3_2_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}

	for (post_row_id = 0; post_row_id < COLUMN_OUTPUT_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < COLUMN_OUTPUT_EI_W; post_col_id++) {
			post_neuron_addr = column_output_ex[post_row_id][post_col_id];
			for (pre_row_id = 0; pre_row_id < COLUMN_X_3_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_3_EI_W; pre_col_id++) {
					if (post_row_id == 3 && post_col_id == 0) {
						pre_neuron_addr = column_0_3_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_3_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_3_EI_W; pre_col_id++) {
					if (post_row_id == 3 && post_col_id == 1) {
						pre_neuron_addr = column_1_3_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_3_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_3_EI_W; pre_col_id++) {
					if (post_row_id == 3 && post_col_id == 2) {
						pre_neuron_addr = column_2_3_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
			for (pre_row_id = 0; pre_row_id < COLUMN_X_3_EI_L; pre_row_id++) {
				for (pre_col_id = 0; pre_col_id < COLUMN_X_3_EI_W; pre_col_id++) {
					if (post_row_id == 3 && post_col_id == 3) {
						pre_neuron_addr = column_3_3_ex[pre_row_id][pre_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
}

void connectOutput2Output(caerModuleData moduleData) {
	uint32_t pre_row_id, pre_col_id, post_row_id, post_col_id, post_neuron_id, pre_neuron_id; //pre_chip_id,
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	for (post_row_id = 0; post_row_id < OUTPUT_POPULATION_EI_L; post_row_id++) {
		for (post_col_id = 0; post_col_id < OUTPUT_POPULATION_EI_W; post_col_id++) {
			for (pre_col_id = 0; pre_col_id < COLUMN_OUTPUT_EI_W; pre_col_id++) {
				if (post_col_id == pre_col_id) {
					for (pre_row_id = 0; pre_row_id < COLUMN_OUTPUT_EI_L; pre_row_id++) {
						for (post_neuron_id = 0; post_neuron_id < OUTPUT_POPULATION_EI_SIZE; post_neuron_id++) {
							pre_neuron_addr = column_output_ex[pre_row_id][pre_col_id];
							post_neuron_addr = output_population_ex[post_row_id][post_col_id][post_neuron_id];
							buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
								FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
						}
					}
				}
			}
		}
	}

	for (pre_row_id = 0; pre_row_id < OUTPUT_POPULATION_EI_L; pre_row_id++) {
		for (pre_col_id = 0; pre_col_id < OUTPUT_POPULATION_EI_W; pre_col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < OUTPUT_POPULATION_EI_SIZE; pre_neuron_id++) {
				for (post_row_id = 0; post_row_id < OUTPUT_POPULATION_EI_L; post_row_id++) {
					for (post_col_id = 0; post_col_id < OUTPUT_POPULATION_EI_W; post_col_id++) {
						for (post_neuron_id = 0; post_neuron_id < OUTPUT_POPULATION_EI_SIZE; post_neuron_id++) {
							if (pre_row_id == post_row_id && pre_col_id == post_col_id) {
								pre_neuron_addr = output_population_ex[pre_row_id][pre_col_id][pre_neuron_id];
								post_neuron_addr = output_population_in[post_row_id][post_col_id][post_neuron_id];
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
							}
						}
					}
				}
			}
		}
	}
	for (pre_row_id = 0; pre_row_id < OUTPUT_POPULATION_EI_L; pre_row_id++) {
		for (pre_col_id = 0; pre_col_id < OUTPUT_POPULATION_EI_W; pre_col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < OUTPUT_POPULATION_EI_SIZE; pre_neuron_id++) {
				for (post_row_id = 0; post_row_id < OUTPUT_POPULATION_EI_L; post_row_id++) {
					for (post_col_id = 0; post_col_id < OUTPUT_POPULATION_EI_W; post_col_id++) {
						for (post_neuron_id = 0; post_neuron_id < OUTPUT_POPULATION_EI_SIZE; post_neuron_id++) {
							if (!(pre_row_id == post_row_id && pre_col_id == post_col_id)) {
								pre_neuron_addr = output_population_in[pre_row_id][pre_col_id][pre_neuron_id];
								post_neuron_addr = output_population_ex[post_row_id][post_col_id][post_neuron_id];
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
							}
						}
					}
				}
			}
		}
	}

	//connect output to hub neurons
//	virtual_neuron_addr_enable = 1;
	for (pre_row_id = 0; pre_row_id < OUTPUT_POPULATION_EI_L; pre_row_id++) {
		for (pre_col_id = 0; pre_col_id < OUTPUT_POPULATION_EI_W; pre_col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < OUTPUT_POPULATION_EI_SIZE; pre_neuron_id++) {
				for (post_row_id = 0; post_row_id < HUB_L; post_row_id++) {
					for (post_col_id = 0; post_col_id < HUB_W; post_col_id++) {
						pre_neuron_addr = output_population_ex[pre_row_id][pre_col_id][pre_neuron_id];
//						pre_chip_id = (pre_neuron_addr & NEURON_CHIPID_BITS) >> NEURON_CHIPID_SHIFT;
//						pre_neuron_id = (pre_neuron_addr & NEURON_NEURONID_BITS) >> NEURON_NEURONID_SHIFT;
//						virtual_neuron_addr = pre_chip_id << NEURON_CHIPID_SHIFT | 2 << NEURON_COREID_SHIFT | pre_neuron_id;
						post_neuron_addr = hub_neurons[post_row_id][post_col_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					}
				}
			}
		}
	}
//	virtual_neuron_addr_enable = 0;

}

void connectOutputSelectingNeuronsToColumns(caerModuleData moduleData) {
	int64_t pre_neuron_id, post_row_id, post_col_id;

	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;

	for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
		pre_neuron_addr = output_selecting_neurons[0][0][pre_neuron_id];
		for (post_row_id = 0; post_row_id < COLUMN_X_0_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_0_EI_W; post_col_id++) {
				post_neuron_addr = column_0_0_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_1_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_1_EI_W; post_col_id++) {
				post_neuron_addr = column_0_1_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_2_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_2_EI_W; post_col_id++) {
				post_neuron_addr = column_0_2_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_3_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_3_EI_W; post_col_id++) {
				post_neuron_addr = column_0_3_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
	}


	for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
		pre_neuron_addr = output_selecting_neurons[0][1][pre_neuron_id];
		for (post_row_id = 0; post_row_id < COLUMN_X_0_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_0_EI_W; post_col_id++) {
				post_neuron_addr = column_1_0_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_1_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_1_EI_W; post_col_id++) {
				post_neuron_addr = column_1_1_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_2_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_2_EI_W; post_col_id++) {
				post_neuron_addr = column_1_2_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_3_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_3_EI_W; post_col_id++) {
				post_neuron_addr = column_1_3_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
	}

	for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
		pre_neuron_addr = output_selecting_neurons[0][2][pre_neuron_id];
		for (post_row_id = 0; post_row_id < COLUMN_X_0_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_0_EI_W; post_col_id++) {
				post_neuron_addr = column_2_0_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_1_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_1_EI_W; post_col_id++) {
				post_neuron_addr = column_2_1_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_2_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_2_EI_W; post_col_id++) {
				post_neuron_addr = column_2_2_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_3_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_3_EI_W; post_col_id++) {
				post_neuron_addr = column_2_3_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
	}

	for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
		pre_neuron_addr = output_selecting_neurons[0][3][pre_neuron_id];
		for (post_row_id = 0; post_row_id < COLUMN_X_0_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_0_EI_W; post_col_id++) {
				post_neuron_addr = column_3_0_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_1_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_1_EI_W; post_col_id++) {
				post_neuron_addr = column_3_1_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_2_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_2_EI_W; post_col_id++) {
				post_neuron_addr = column_3_2_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_3_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_3_EI_W; post_col_id++) {
				post_neuron_addr = column_3_3_ex[post_row_id][post_col_id];
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
	}
}
