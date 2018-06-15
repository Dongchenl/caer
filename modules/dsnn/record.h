static void recordOutputEvents(caerSpikeEventPacketConst spike);
static void recordInputOutputEvents(caerSpikeEventPacketConst spike);

void recordOutputEvents(caerSpikeEventPacketConst spike) {

	CAER_SPIKE_ITERATOR_VALID_START(spike)

	//Get spike timing information
	int64_t ts = caerSpikeEventGetTimestamp64(caerSpikeIteratorElement, spike); //get values on which to operate.

	//Wait the initialization to be finished
	if (set_first_ts == 0) {
		first_ts = ts;
		set_first_ts = 1;
	}
	if (ini_finished == 0) {
		if (ts - first_ts < 100000 * 1000) {
			return;
		} else {
			ini_finished = 1;
			char buf_0[0x100];
			snprintf(buf_0, sizeof(buf_0), "recorded_events/recorded_events_%d_%d.txt", trial_id, testing_object_id);
			f = fopen(buf_0, "w");
			if (f == NULL)
			{
			    printf("Error opening file! \n");
			    exit(1);
			}
			fprintf(f, "");
			fclose(f);
			char buf_1[0x100];
			snprintf(buf_1, sizeof(buf_1), "recorded_events/recorded_events_%d_%d.txt", trial_id, testing_object_id);
//			f = fopen(buf_1, "a");
//			if (f == NULL)
//			{
//			    printf("Error opening file! \n");
//			    exit(1);
//			}
			printf("The No. %d recording for object %d starts. \n", trial_id, testing_object_id);
		}
	}

	if (testing_pause == 1) {
//		testing_pause = 0;
		printf("Please enter c to continue the recording for object %d. \n", testing_object_id);
		scanf("%c", &letter);
		if (letter == 'c') {
			testing_pause = 0;
			char buf_0[0x100];
			snprintf(buf_0, sizeof(buf_0), "recorded_events/recorded_events_%d_%d.txt", trial_id, testing_object_id);
			printf(buf_0);
			f = fopen(buf_0, "w");
//			f = fopen("recorded_events/recorded_events_9_9.txt", "a");
			if (f == NULL)
			{
			    printf("Error opening file! \n");
			    exit(1);
			}
			fprintf(f, "");
			fclose(f);
			char buf_1[0x100];
			snprintf(buf_1, sizeof(buf_1), "recorded_events/recorded_events_%d_%d.txt", trial_id, testing_object_id);
			printf(buf_1);
			f = fopen(buf_1, "a");
//			f = fopen("recorded_events/recorded_events_9_9.txt", "a");
			if (f == NULL)
			{
			    printf("Error opening file! \n");
			    exit(1);
			}
			printf("The No. %d recording for object %d starts. \n", trial_id, testing_object_id);
		}
		else {
			return;
		}
	}

	if (testing_pause == 1) {
		return;
	}

	if (ts - recording_first_ts < 5000 * 1000) { //3000 * 1000
		return;
	}

	uint32_t core_id = caerSpikeEventGetSourceCoreID(caerSpikeIteratorElement);
	uint32_t chip_id_t = caerSpikeEventGetChipID(caerSpikeIteratorElement);
	uint32_t neuron_id = caerSpikeEventGetNeuronID(caerSpikeIteratorElement);
	uint32_t row_id = (neuron_id & NEURON_ROWID_BITS) >> NEURON_ROWID_SHIFT;
	uint32_t col_id = (neuron_id & NEURON_COLID_BITS) >> NEURON_COLID_SHIFT;
	uint32_t object_id = 255;

	uint32_t chip_id;
	if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U0) //note: not DYNAPSE_CONFIG_DYNAPSE_U0
		chip_id = 1;
	else if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U1)
		chip_id = 2;
	else if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U2)
		chip_id = 3;
	else if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U3)
		chip_id = 4;
	else
		chip_id = 4;

	if (chip_id == 1 && core_id == 3 &&
		row_id >= NSM_SIZE / 2 * 6 && row_id < NSM_SIZE / 2 * 7 &&
		col_id >= NSM_SIZE / 2 * 4 && col_id < NSM_SIZE / 2 * 8) {

		if (col_id >= NSM_SIZE / 2 * 4 && col_id < NSM_SIZE / 2 * 5) {
			object_id = 0;
		} else if (col_id >= NSM_SIZE / 2 * 5 && col_id < NSM_SIZE / 2 * 6) {
			object_id = 1;
		} else if (col_id >= NSM_SIZE / 2 * 6 && col_id < NSM_SIZE / 2 * 7) {
			object_id = 2;
		} else if (col_id >= NSM_SIZE / 2 * 7 && col_id < NSM_SIZE / 2 * 8) {
			object_id = 3;
		} else {
		    printf("Error object ID! \n");
		    exit(1);
		}

		f = fopen("recorded_events/recorded_events_0_0.txt", "a");
		fprintf(f, "%d %d %d %d %d \n", (int) ts, (int) neuron_id, (int) core_id, (int) chip_id, (int) object_id);
		fclose(f);
//		printf("Written! \n");

		recognized_object_num += 1;
		if (recognized_object_num == -1) { //MAXIMUM_RECORDED_EVENTS_PER_OBJECT
			fclose(f);
			printf("The No. %d recording for object %d is finished. \n", trial_id, testing_object_id);
			recognized_object_num = 0;
			testing_pause = 1;
			testing_object_id += 1;
			if (testing_object_id == TRAINING_OBJECT_NUM) {
				testing_object_id = 0;
				trial_id += 1;
			}
//			recording_set_first_ts = 0;
			recording_first_ts = ts;
			return;
		}

	}

	CAER_SPIKE_ITERATOR_VALID_END

}

void recordInputOutputEvents(caerSpikeEventPacketConst spike) {

	CAER_SPIKE_ITERATOR_VALID_START(spike)

	//Get spike timing information
	int64_t ts = caerSpikeEventGetTimestamp64(caerSpikeIteratorElement, spike); //get values on which to operate.

	//Wait the initialization to be finished
	if (set_first_ts == 0) {
		first_ts = ts;
		set_first_ts = 1;
	}
	if (ini_finished == 0) {
		if (ts - first_ts < 100000 * 1000) {
			return;
		} else {
			ini_finished = 1;
			char buf_0[0x100];
			snprintf(buf_0, sizeof(buf_0), "recorded_events/recorded_events_input_output.txt", trial_id, testing_object_id);
			f = fopen(buf_0, "w");
			if (f == NULL)
			{
			    printf("Error opening file! \n");
			    exit(1);
			}
			fprintf(f, "");
			fclose(f);
			char buf_1[0x100];
			snprintf(buf_1, sizeof(buf_1), "recorded_events/recorded_events_input_output.txt", trial_id, testing_object_id);
			printf("The recording for input output layers starts. \n", trial_id, testing_object_id);
		}
	}

	if (ts - recording_first_ts < 5000 * 1000) { //3000 * 1000
		return;
	}

	uint32_t core_id = caerSpikeEventGetSourceCoreID(caerSpikeIteratorElement);
	uint32_t chip_id_t = caerSpikeEventGetChipID(caerSpikeIteratorElement);
	uint32_t neuron_id = caerSpikeEventGetNeuronID(caerSpikeIteratorElement);
	uint32_t row_id = (neuron_id & NEURON_ROWID_BITS) >> NEURON_ROWID_SHIFT;
	uint32_t col_id = (neuron_id & NEURON_COLID_BITS) >> NEURON_COLID_SHIFT;

	uint32_t chip_id;
	if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U0) //note: not DYNAPSE_CONFIG_DYNAPSE_U0
		chip_id = 1;
	else if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U1)
		chip_id = 2;
	else if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U2)
		chip_id = 3;
	else if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U3)
		chip_id = 4;
	else
		chip_id = 4;

	if ((chip_id == 1 && (core_id == 0 || core_id == 2)) || (chip_id == 4 && core_id == 3) ||
		(chip_id == 2 && (core_id == 1 || core_id == 3)) ) {
		f = fopen("recorded_events/recorded_events_input_output.txt", "a");
		fprintf(f, "%d %d %d %d %d \n", (int) ts, (int) row_id, (int) col_id, (int) core_id, (int) chip_id);
		fclose(f);
	}

	CAER_SPIKE_ITERATOR_VALID_END

}


