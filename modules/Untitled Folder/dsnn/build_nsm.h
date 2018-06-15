static void buildNSM(caerModuleData moduleData);
static void connectNSMSynapses(caerModuleData moduleData);
static void connectStateInput2State(caerModuleData moduleData);
static void connectState2State(caerModuleData moduleData);
static void connectState2WTA(caerModuleData moduleData);
static void connectWTA2WTA(caerModuleData moduleData);
static void connectWTA2State(caerModuleData moduleData);
static void connectState2Gate1st(caerModuleData moduleData);
static void connectGate1st2Gate2nd(caerModuleData moduleData);
static void connectWTA2Gate2nd(caerModuleData moduleData);
static void connectInh2Trans(caerModuleData moduleData);
static void buildCompetitiveNetwork(caerModuleData moduleData);
static void connectOutputSelectingNeuronsToColumns(caerModuleData moduleData);

void buildNSM(caerModuleData moduleData) {
	createNSMPopulations();
	connectNSMSynapses(moduleData);

	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}

void connectNSMSynapses(caerModuleData moduleData) {
//	connectStateInput2State(moduleData);
	connectState2State(moduleData);
	connectState2WTA(moduleData);
	connectWTA2WTA(moduleData);
	connectWTA2State(moduleData);
	connectState2Gate1st(moduleData);
	connectGate1st2Gate2nd(moduleData);
	connectWTA2Gate2nd(moduleData);
	connectInh2Trans(moduleData);

	buildCompetitiveNetwork(moduleData);

//	connectOutputSelectingNeuronsToColumns(moduleData);
}

void connectStateInput2State(caerModuleData moduleData) {
	int64_t row_id, col_id, pre_neuron_id, post_neuron_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = EXTERNAL_REAL_SYNAPSE;
	//connect state neurons
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
				for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
					pre_neuron_addr = nsm_state_input_0[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_state_0[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = nsm_state_input_1[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_state_1[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					/*
					pre_neuron_addr = nsm_state_input_2[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_state_2[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					*/
				}
			}
		}
	}
}

void connectState2State(caerModuleData moduleData) {
	int64_t row_id, col_id, pre_neuron_id, post_neuron_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	//connect state neurons
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
				for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
					if (pre_neuron_id != post_neuron_id) {
						pre_neuron_addr = nsm_state_0[row_id][col_id][pre_neuron_id];
						post_neuron_addr = nsm_state_0[row_id][col_id][post_neuron_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							SLOW_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

						pre_neuron_addr = nsm_state_1[row_id][col_id][pre_neuron_id];
						post_neuron_addr = nsm_state_1[row_id][col_id][post_neuron_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							SLOW_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

						pre_neuron_addr = nsm_state_0[row_id][col_id][pre_neuron_id];
						post_neuron_addr = output_selecting_neurons[row_id][col_id][post_neuron_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							SLOW_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

						/*
						pre_neuron_addr = nsm_state_2[row_id][col_id][pre_neuron_id];
						post_neuron_addr = nsm_state_2[row_id][col_id][post_neuron_id];
						buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
							SLOW_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
						*/
					}
				}
			}
		}
	}
}

void connectState2WTA(caerModuleData moduleData) {
	int64_t row_id, col_id, pre_neuron_id, post_neuron_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	//connect populations
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
				for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
					pre_neuron_addr = nsm_state_0[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_wta_ex[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = nsm_state_1[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_wta_ex[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					/*
					pre_neuron_addr = nsm_state_2[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_wta_ex[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					*/
				}
			}
		}
	}
}

void connectWTA2WTA(caerModuleData moduleData) {
	int64_t row_id, col_id, pre_neuron_id, post_neuron_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	//connect populations
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
				for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
					pre_neuron_addr = nsm_wta_ex[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_wta_in[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
				}
			}
		}
	}
}

void connectWTA2State(caerModuleData moduleData) {
	int64_t row_id, col_id, pre_neuron_id, post_neuron_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	//connect populations
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
				for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
					pre_neuron_addr = nsm_wta_in[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_state_0[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = nsm_wta_in[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_state_1[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					/*
					pre_neuron_addr = nsm_wta_in[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_state_2[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					*/
				}
			}
		}
	}
}

void connectState2Gate1st(caerModuleData moduleData) {
	int64_t row_id, col_id, pre_neuron_id, post_neuron_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;;
	//connect populations
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
				for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
					pre_neuron_addr = nsm_state_0[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_1st_gate_0[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = nsm_state_1[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_1st_gate_1[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					/*
					pre_neuron_addr = nsm_state_2[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_1st_gate_2[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					*/
				}
			}
		}
	}
}

void connectGate1st2Gate2nd(caerModuleData moduleData) {
	int64_t row_id, col_id, pre_neuron_id, post_neuron_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;;
	//connect populations
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
				for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
					pre_neuron_addr = nsm_1st_gate_0[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_2nd_gate_0[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = nsm_1st_gate_1[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_2nd_gate_1[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = nsm_1st_gate_0[row_id][col_id][pre_neuron_id];
					post_neuron_addr = output_selecting_neurons[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = nsm_1st_gate_1[row_id][col_id][pre_neuron_id];
					post_neuron_addr = output_selecting_neurons[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					/*
					pre_neuron_addr = nsm_1st_gate_2[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_2nd_gate_2[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					*/
				}
			}
		}
	}
}

void connectWTA2Gate2nd(caerModuleData moduleData) {
	int64_t row_id, col_id, pre_neuron_id, post_neuron_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	//connect populations
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
				for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
					pre_neuron_addr = nsm_wta_ex[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_2nd_gate_0[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = nsm_wta_ex[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_2nd_gate_1[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					/*
					pre_neuron_addr = nsm_wta_ex[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_2nd_gate_2[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					*/
				}
			}
		}
	}
}

void connectInh2Trans(caerModuleData moduleData) {
	int64_t row_id, col_id, pre_neuron_id, post_neuron_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	//connect populations
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
				for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
					pre_neuron_addr = nsm_2nd_gate_0[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_transition_0[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

					pre_neuron_addr = nsm_2nd_gate_1[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_transition_1[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					/*
					pre_neuron_addr = nsm_2nd_gate_2[row_id][col_id][pre_neuron_id];
					post_neuron_addr = nsm_transition_2[row_id][col_id][post_neuron_id];
					buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
						FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
					*/
				}
			}
		}
	}
}

void buildCompetitiveNetwork(caerModuleData moduleData) {
	int64_t row_id, col_id, pre_neuron_id, post_neuron_id;
	int64_t new_row_id, new_col_id;
	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE_WITHOUT_LEARNING;
	//connect populations
	for (row_id = 0; row_id < NSM_L; row_id++) {
		for (col_id = 0; col_id < NSM_W; col_id++) {
			for (new_row_id = 0; new_row_id < NSM_L; new_row_id++) {
				for (new_col_id = 0; new_col_id < NSM_W; new_col_id++) {
					for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
						for (post_neuron_id = 0; post_neuron_id < NSM_SIZE; post_neuron_id++) {
							if (row_id != new_row_id || col_id != new_col_id) {
								//states excite transitions
								pre_neuron_addr = nsm_state_0[row_id][col_id][pre_neuron_id];
								post_neuron_addr = nsm_transition_0[new_row_id][new_col_id][post_neuron_id];
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

								pre_neuron_addr = nsm_state_1[row_id][col_id][pre_neuron_id]; //nsm_state_1[row_id][col_id][pre_neuron_id];
								post_neuron_addr = nsm_transition_1[new_row_id][new_col_id][post_neuron_id];
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
								/*
								pre_neuron_addr = nsm_state_2[row_id][col_id][pre_neuron_id]; //nsm_state_1[row_id][col_id][pre_neuron_id];
								post_neuron_addr = nsm_transition_1[new_row_id][new_col_id][post_neuron_id];
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

								pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1]; //nsm_state_1[row_id][col_id][pre_neuron_id];
								post_neuron_addr = nsm_transition_2[new_row_id][new_col_id][post_neuron_id];
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
								*/
								//states inhibit transitions
								pre_neuron_addr = nsm_1st_gate_0[row_id][col_id][pre_neuron_id];
								post_neuron_addr = nsm_transition_1[new_row_id][new_col_id][post_neuron_id];
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_IN_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

								//transitions excite states
								pre_neuron_addr = nsm_transition_0[row_id][col_id][pre_neuron_id];
								post_neuron_addr = nsm_state_1[row_id][col_id][post_neuron_id];
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);

								pre_neuron_addr = nsm_transition_1[row_id][col_id][pre_neuron_id];
								post_neuron_addr = nsm_state_0[row_id][col_id][post_neuron_id];
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
								/*
								pre_neuron_addr = nsm_transition_2[row_id][col_id][pre_neuron_id];
								post_neuron_addr = nsm_state_0[row_id][col_id][post_neuron_id];
								buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
									FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, FIRST_CAM_ID);
								*/
							}
						}
					}
				}
			}
		}
	}
}

void connectOutputSelectingNeuronsToColumns(caerModuleData moduleData) {
	int64_t pre_neuron_id, post_row_id, post_col_id;

	uint32_t pre_neuron_addr, post_neuron_addr;
	int8_t virtual_neuron_addr_enable = 0;
	uint32_t virtual_neuron_addr = 0;
	int8_t real_virtual_synapse = REAL_SYNAPSE;
	printf("--------------------- \n");

	for (pre_neuron_id = 0; pre_neuron_id < NSM_SIZE; pre_neuron_id++) {
		pre_neuron_addr = output_selecting_neurons[0][0][pre_neuron_id];
		for (post_row_id = 0; post_row_id < COLUMN_X_0_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_0_EI_W; post_col_id++) {
				post_neuron_addr = column_0_0_ex[post_row_id][post_col_id];
				printf("%d \n", pre_neuron_addr);
				printf("%d \n", post_neuron_addr);
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_1_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_1_EI_W; post_col_id++) {
				post_neuron_addr = column_0_1_ex[post_row_id][post_col_id];
				printf("%d \n", pre_neuron_addr);
				printf("%d \n", post_neuron_addr);
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_2_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_2_EI_W; post_col_id++) {
				post_neuron_addr = column_0_2_ex[post_row_id][post_col_id];
				printf("%d \n", pre_neuron_addr);
				printf("%d \n", post_neuron_addr);
				buildSynapseDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr,
					FAST_EX_SYNAPSE_VALUE, real_virtual_synapse, virtual_neuron_addr_enable, LAST_CAM_ID_OUTPUT_NEURON);
			}
		}
		for (post_row_id = 0; post_row_id < COLUMN_X_3_EI_L; post_row_id++) {
			for (post_col_id = 0; post_col_id < COLUMN_X_3_EI_W; post_col_id++) {
				post_neuron_addr = column_0_3_ex[post_row_id][post_col_id];
				printf("%d \n", pre_neuron_addr);
				printf("%d \n", post_neuron_addr);
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
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}
