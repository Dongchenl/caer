static void setDavisInput(caerModuleData moduleData);

void setDavisInput(caerModuleData moduleData) {
	clearInputLayerCamDSNN(moduleData);

	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
	configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);

	setDavisInputLayerBiases(moduleData);
}
