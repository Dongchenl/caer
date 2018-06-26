static bool resetNetworkDSNN(caerModuleData moduleData);

//reset the network connectivity and the learning algorithm to their initial states
bool resetNetworkDSNN(caerModuleData moduleData) {

	initializeMemory();

	resetBiasesLowDCDSNN(moduleData); //reset all the biases for high activity

	clearAllCamDSNN(moduleData); //clear all the CAMs

	//Initializes random number generator
	srand(1);

	resetBiasesDSNN(moduleData);

	if (load_previous_connectivity == 0) {
		createInputNeurons();
		createFeatureNeurons();
		createOutputNeurons();
		createWTANeurons();
		createArbitratorNeurons();

		buildInputNeurons(moduleData);
		buildFeatureNeurons(moduleData);
		buildOutputNeurons(moduleData);
		buildWTANeurons(moduleData);
		buildArbitratorNeurons(moduleData);
	}
	else {
		loadConnectivity(moduleData);
	}

	if (enable_output_to_rolls == 1) {
		createOutputNeurons();
		setOutputToOtherChips(moduleData);
	}

	if (davis_input == 1) {
		setDavisInput(moduleData);
	}

	network_reseted = 1;

	return (true);
}
