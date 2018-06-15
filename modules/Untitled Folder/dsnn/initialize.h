static void clearAllCamDSNN(caerModuleData moduleData);
static void clearInputLayerCamDSNN(caerModuleData moduleData);

void clearAllCamDSNN(caerModuleData moduleData) {
	//clear all the CAMs on board
	uint32_t neuronId, camId;
	for (neuronId = 0; neuronId < TOTAL_NEURON_NUM_ON_CHIP; neuronId++)
		for (camId = 0; camId < TOTAL_CAM_NUM; camId++) {
			writeCamDSNN(moduleData, (3 << 8) | 255, (1 << 10) | neuronId, 0, camId, 0, 0, 0);
			writeCamDSNN(moduleData, (3 << 8) | 255, (2 << 10) | neuronId, 0, camId, 0, 0, 0);
			writeCamDSNN(moduleData, (3 << 8) | 255, (3 << 10) | neuronId, 0, camId, 0, 0, 0);
			writeCamDSNN(moduleData, (3 << 8) | 255, (4 << 10) | neuronId, 0, camId, 0, 0, 0);
		}
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}

void clearInputLayerCamDSNN(caerModuleData moduleData) {
	//clear all the CAMs on board
	uint32_t neuronId, camId;
	for (neuronId = 0; neuronId < TOTAL_NEURON_NUM_IN_CORE; neuronId++)
		for (camId = 0; camId < TOTAL_CAM_NUM; camId++) {
			writeCamDSNN(moduleData, (3 << 8) | 255, (4 << 10) | (3 << 8) | neuronId, 0, camId, 0, 0, 0);
		}
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);

	int32_t synapse_type = FAST_EX_SYNAPSE_VALUE;
	camId = 0;
    for (neuronId = 0; neuronId < TOTAL_NEURON_NUM_IN_CORE; neuronId++) {
    	if (neuronId != 255) {
        	uint32_t neuron_row = (neuronId & NEURON_ROWID_BITS) >> NEURON_ROWID_SHIFT;
        	uint32_t neuron_column = neuronId & NEURON_COLID_BITS;
            uint32_t new_neuronId = neuron_column << NEURON_ROWID_SHIFT | neuron_row;
        	writeCamDSNN(moduleData, (1 << 10) | new_neuronId, (4 << 10) | (3 << 8) | neuronId, 0, camId, synapse_type, 0, 0);
    	}
    }
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
}
