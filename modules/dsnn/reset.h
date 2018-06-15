static bool resetNetworkDSNN(caerModuleData moduleData);


static int8_t load_previous_connectivity = LOAD_PREVIOUS_CONNECTIVITY; //0; //1;
static int8_t record_output_events = RECORD_OUTPUT_EVENTS;
static int8_t record_input_output_events = RECORD_INPUT_OUTPUT_EVENTS;
static FILE *f;
static char letter;
static int32_t testing_object_id = 0;
static int64_t recognized_object_num = 0;
static int8_t testing_pause = 0;
static int32_t trial_id = 0;
static int8_t davis_input = DAVIS_INPUT;
//static int8_t load_half_previous_connectivity = LOAD_HALF_PREVIOUS_CONNECTIVITY; //0; //1;

//for overall control of learning and testing
static int8_t network_reseted = 0;

bool resetNetworkDSNN(caerModuleData moduleData) {
	//reset the network connectivity and the learning algorithm to their initial states

	initializeMemory();

	resetBiasesLowDCDSNN(moduleData); //reset all the biases for high activity
	//clear all the CAMs

	clearAllCamDSNN(moduleData);

	//Initializes random number generator
	srand(1);

	//reset input stimuli patterns
//	stimuli_pattern = 0;


	//construct all the layers
	//feature layer 0

	if (load_previous_connectivity == 0) {
		createLayers();
		buildInputLayer01(moduleData);
		buildFeatureLayer0(moduleData);
		buildFeatureLayer1(moduleData);
		buildFeatureLayer2(moduleData);
		buildFeatureLayer3(moduleData);

		buildNSM(moduleData);

		buildColumn(moduleData);
	}
	else {
		loadConnectivity(moduleData);
	}

	int8_t enable_output_to_rolls = ENABLE_OUTPUT_TO_ROLLS;
	if (enable_output_to_rolls == 1) {
		createColumnPopulations();
		setOutputToOtherChips(moduleData);
	}

	resetBiasesDSNN(moduleData);

	if (davis_input == 1) {
		setDavisInput(moduleData);
	}

	network_reseted = 1;
	return (true);
}
