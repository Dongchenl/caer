static void enableLearning(caerModuleData moduleData);
static void disableLearning(caerModuleData moduleData);
static void showNSMWinnerReady(caerModuleData moduleData);
static void stopNSMWinnerReady(caerModuleData moduleData);

void enableLearning(caerModuleData moduleData) {

	int32_t cam_id = 0;
	int32_t synapse_type = 2;
	int64_t pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1]; //input_layer_0_in[0][0];
	int64_t post_neuron_addr = output_layer_ex[OUTPUT_LAYER_EI_L-1][OUTPUT_LAYER_EI_W-1]; //output_layer_ex[15][15];

	printf("Enable the input of feature learning. \n");
	writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);

	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
//	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
//	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
//	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}

void disableLearning(caerModuleData moduleData) {

	int32_t cam_id = 0;
	int32_t synapse_type = 0;
	int64_t pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1]; //input_layer_0_in[0][0];
	int64_t post_neuron_addr = output_layer_ex[OUTPUT_LAYER_EI_L-1][OUTPUT_LAYER_EI_W-1]; //output_layer_ex[15][15];

	printf("Disable the input of feature learning. \n");
	writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);

	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
//	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
//	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
//	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}

void showNSMWinnerReady(caerModuleData moduleData) {
	int32_t cam_id = 0;
	int32_t synapse_type = 2;
	int64_t pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1]; //input_layer_0_in[0][0];
	int64_t post_neuron_addr = output_layer_ex[OUTPUT_LAYER_EI_L-1][OUTPUT_LAYER_EI_W-2]; //output_layer_ex[15][15];

	printf("Enable the input of feature learning. \n");
	writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);

	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
}

void stopNSMWinnerReady(caerModuleData moduleData) {
	int32_t cam_id = 0;
	int32_t synapse_type = 0;
	int64_t pre_neuron_addr = feature_layer_0_in[FEATURE_LAYER_EI_L-1][FEATURE_LAYER_EI_W-1]; //input_layer_0_in[0][0];
	int64_t post_neuron_addr = output_layer_ex[OUTPUT_LAYER_EI_L-1][OUTPUT_LAYER_EI_W-2]; //output_layer_ex[15][15];

	printf("Disable the input of feature learning. \n");
	writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, 0, (uint32_t) cam_id, synapse_type, 0, 0);

	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
}
