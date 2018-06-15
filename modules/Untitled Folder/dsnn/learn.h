static void learning(caerModuleData moduleData, caerSpikeEventPacketConst spike);

static int8_t synapse_updated = 0;
static int64_t last_update_time = 0;
static int8_t stability_checked = 1;

void learning(caerModuleData moduleData, caerSpikeEventPacketConst spike) {

	CAER_SPIKE_ITERATOR_VALID_START(spike) //iterate over received spikes

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
			printf("Ready to learn. \n");
//			post_spike_time = ts;
		}
	}

	//Get spike address information
	uint32_t chip_id_t = caerSpikeEventGetChipID(caerSpikeIteratorElement);
	uint32_t chip_id;
	if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U0) {
		chip_id = 1;
	} else if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U1) {
		chip_id = 2;
	} else if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U2) {
		chip_id = 3;
	} else if (chip_id_t == DYNAPSE_CONFIG_DYNAPSE_U3) {
		chip_id = 4;
	} else {
		caerLog(CAER_LOG_ERROR, moduleData->moduleSubSystemString, "Chip ID is out of range.");
		return;
	}
	uint32_t neuron_id = caerSpikeEventGetNeuronID(caerSpikeIteratorElement);
	uint32_t row_id = (uint32_t) (neuron_id / 16);
	uint32_t col_id = neuron_id % 16;
	uint32_t core_id = caerSpikeEventGetSourceCoreID(caerSpikeIteratorElement);

	//	chip ID: 2, core ID: 1, neuron ID: 105.
	if (chip_id == 3 && core_id == 0 && neuron_id == 105) {
		return;
	}

	int8_t spike_valid = 0;
	//Put spikes into the buffer
	if (chip_id == 4 && core_id == 3) {
		uint32_t new_core_id = 1;
		int64_t spike_addr = chip_id << NEURON_CHIPID_SHIFT | new_core_id << NEURON_COREID_SHIFT | neuron_id;
		memory.spike_fifo->buffer2d[memory.wr_pointer][0] = spike_addr; //put spike address into the queue
		memory.spike_fifo->buffer2d[memory.wr_pointer][1] = ts; //put spike address into the queue
		memory.wr_pointer = (memory.wr_pointer + 1) % SPIKE_QUEUE_LENGTH;

		spike_valid = 1;

		memory.start_rd_pointer = memory.wr_pointer;
		int64_t start_spike_time = ts;
		int64_t current_spike_addr, current_spike_time, delta_time;
		int64_t spike_num = 0;
		uint8_t end_searching = 0;
		for (uint64_t current_rd_pointer = (memory.start_rd_pointer - 1) % SPIKE_QUEUE_LENGTH;
			end_searching != 1;
			current_rd_pointer = (current_rd_pointer - 1) % SPIKE_QUEUE_LENGTH) {

			current_spike_addr = memory.spike_fifo->buffer2d[current_rd_pointer][0];
			current_spike_time = memory.spike_fifo->buffer2d[current_rd_pointer][1];

			delta_time = (int64_t) (start_spike_time - current_spike_time) / 1000;

			if (delta_time > 0 && delta_time <= SILENCE_CHECKING_PERIOD) {
				spike_num += 1;
			}
			if (delta_time > SILENCE_CHECKING_PERIOD) {
				end_searching = 1;
				break;
			}
			if (current_spike_addr == 0) {
				end_searching = 1;
				break;
			}
		}
		if (spike_num < last_spike_num - SPIKE_REDUCED_NUM) {
			applyNotReadySignal(moduleData);
			synapse_updated = 0; //not silent
			post_spike_time = ts;
			last_spike_num = 0;
		}
		else if (spike_num >= SILENCE_CHECKING_SPIKES_THRESHOULD) {
			last_spike_num = spike_num;
			last_wr_pointer = memory.wr_pointer;
		}
	}


	//Start the input pattern learning
	//Update after a period of silence
	if ((ts - post_spike_time > REFRACTORY_PERIOD * 1000) && synapse_updated == 0 && spike_valid == 1) {
		// Here the synapse delay is important for making decisions.

		removeNotReadySignal(moduleData);

		synapse_updated = 1;

		memory.start_rd_pointer = last_wr_pointer; //memory.wr_pointer;

//		int64_t start_spike_addr = spike_addr;
		int64_t start_spike_time = post_spike_time;
		int64_t current_spike_addr, current_spike_time, delta_time;
		int64_t spike_num = 0;

		uint8_t end_searching = 0;
		for (uint64_t current_rd_pointer = (memory.start_rd_pointer - 1) % SPIKE_QUEUE_LENGTH;
			end_searching != 1;
			current_rd_pointer = (current_rd_pointer - 1) % SPIKE_QUEUE_LENGTH) {

			current_spike_addr = memory.spike_fifo->buffer2d[current_rd_pointer][0];
			current_spike_time = memory.spike_fifo->buffer2d[current_rd_pointer][1];

			delta_time = (int64_t) (start_spike_time - current_spike_time) / 1000;

//			printf("Delta time: %d. \n", delta_time);

			if (delta_time > 0 && delta_time <= CONSIDERING_PERIOD) {
//				printf("Update memory. \n");
				updateMemory(current_spike_addr);
				spike_num += 1;
			}
			if (delta_time > CONSIDERING_PERIOD) { //500 = 500ms = 0.5s
				if (spike_num >= CONSIDERED_SPIKES_THRESHOULD) {
					printf("Reconfigure synapses. \n");
					updateConfiguration(moduleData);
					printf("%d >= %d spikes in %d ms. \n", (int) spike_num, CONSIDERED_SPIKES_THRESHOULD, (int) delta_time);
				} else {
					printf("%d < %d spikes in %d ms. \n", (int) spike_num, CONSIDERED_SPIKES_THRESHOULD, (int) delta_time);
				}
				end_searching = 1;
				last_update_time = post_spike_time;
				stability_checked = 0;
				disableLearning(moduleData);
				stopNSMWinnerReady(moduleData); //
				filtered_input_ready = 0;
				break;
			}
			if (current_spike_addr == 0) {
				end_searching = 1;
				break;
			}
		}
	}

//	if (stability_checked == 0) {
//		printf("ts: %d, last_update_time: %d \n", ts, last_update_time);
//	}

	/********************************************************************************/
	//Check the stability of the learned input
	if (chip_id == 3 && (core_id == 1 || core_id == 3)) {
		int64_t spike_addr = chip_id << NEURON_CHIPID_SHIFT | core_id << NEURON_COREID_SHIFT | neuron_id;
		memory.spike_fifo_check->buffer2d[memory.wr_pointer_check][0] = spike_addr; //put spike address into the queue
		memory.spike_fifo_check->buffer2d[memory.wr_pointer_check][1] = ts; //put spike address into the queue
		memory.wr_pointer_check = (memory.wr_pointer_check + 1) % SPIKE_QUEUE_LENGTH;
	}

	if (ts - last_update_time > CHECK_STABILITY_PERIOD * 1000 && stability_checked == 0) { // && learned_pixels_above_threshold == 1
		stability_checked = 1;

		struct check_return feature_neurons_statistics = {0, 0};
		int64_t start_spike_time = ts;
		int64_t current_spike_addr, current_spike_time, delta_time;
		int64_t spike_num = 0;

		memory.start_rd_pointer_check = memory.wr_pointer_check;
		uint8_t end_searching = 0;
		for (uint64_t current_rd_pointer = (memory.start_rd_pointer_check - 1) % SPIKE_QUEUE_LENGTH;
			end_searching != 1;
			current_rd_pointer = (current_rd_pointer - 1) % SPIKE_QUEUE_LENGTH) {

			current_spike_addr = memory.spike_fifo_check->buffer2d[current_rd_pointer][0];
			current_spike_time = memory.spike_fifo_check->buffer2d[current_rd_pointer][1];

			delta_time = (int64_t) (start_spike_time - current_spike_time) / 1000;

			if (delta_time > 0 && delta_time <= CONSIDERING_PERIOD_CHECK) {
				updateMemoryCheck(current_spike_addr);
				spike_num += 1;
//				printf("Update. \n");
			}
			if (delta_time > CONSIDERING_PERIOD_CHECK) { //500 = 500ms = 0.5s
				if (spike_num >= CONSIDERED_SPIKES_THRESHOULD_CHECK) {
					feature_neurons_statistics = updateConfigurationCheck();
//					printf("Count. \n");
				}
				end_searching = 1;
				break;
			}
			if (current_spike_addr == 0) {
				end_searching = 1;
				break;
			}
		}

		if (feature_neurons_statistics.feature_neurons_num >= FEATURE_NEURONS_NUM_THRESHOLD) {
			printf("@ Learning input turns on: %d >= %d feature neurons; original: %d. \n",
				(int) feature_neurons_statistics.feature_neurons_num, FEATURE_NEURONS_NUM_THRESHOLD,
				(int) feature_neurons_statistics.feature_neurons_original_num);
			enableLearning(moduleData);
			filtered_input_ready = 1;
			set_first_ts_output = 0;
		} else {
			printf("@ Learning input keeps off: %d < %d feature neurons; original: %d. \n",
				(int) feature_neurons_statistics.feature_neurons_num, FEATURE_NEURONS_NUM_THRESHOLD,
				(int) feature_neurons_statistics.feature_neurons_original_num);
			filtered_input_ready = 0;
		}
	}

	/********************************************************************************/
	if (filtered_input_ready == 1) {

		if (set_first_ts_output == 0) {
			first_ts_output = ts;
			set_first_ts_output = 1;
		}
		if (ini_finished_output == 0) {
			if (ts - first_ts_output < CONSIDERING_PERIOD_CHECK * 2) {
				return;
			} else {
				ini_finished_output = 1;
				printf("Ready to learn on the output neurons. \n");
			}
		}

		int64_t spike_addr = chip_id << NEURON_CHIPID_SHIFT | core_id << NEURON_COREID_SHIFT | neuron_id;
		if ((chip_id == 1 && (core_id == 0 || core_id == 2)) || chip_id == 3) {
			memory.spike_fifo_nsm->buffer2d[memory.wr_pointer_nsm][0] = spike_addr; //put spike address into the queue
			memory.spike_fifo_nsm->buffer2d[memory.wr_pointer_nsm][1] = ts; //put spike address into the queue
			memory.wr_pointer_nsm = (memory.wr_pointer_nsm + 1) % SPIKE_QUEUE_LENGTH;
		}

		if (chip_id == 1 && (core_id == 0 || core_id == 2)) {
			int64_t start_spike_time = ts;
			int64_t current_spike_addr, current_spike_time, delta_time;

			memory.start_rd_pointer_feature = memory.wr_pointer_feature;
			uint8_t end_searching = 0;
			for (uint64_t current_rd_pointer = (memory.start_rd_pointer_feature - 1) % SPIKE_QUEUE_LENGTH;
				end_searching != 1;
				current_rd_pointer = (current_rd_pointer - 1) % SPIKE_QUEUE_LENGTH) {

				current_spike_addr = memory.spike_fifo_feature->buffer2d[current_rd_pointer][0];
				current_spike_time = memory.spike_fifo_feature->buffer2d[current_rd_pointer][1];

				delta_time = (int64_t) (start_spike_time - current_spike_time) / 1000;

				if (delta_time > 0 && delta_time <= CONSIDERING_PERIOD_CHECK) {
					learnColumnUpdate(current_spike_addr, spike_addr);
				}
				if (delta_time > CONSIDERING_PERIOD_CHECK) {
					printf("@@@ Learn the feature combination. \n");
					learnColumnConfigure(moduleData, spike_addr);
//					learned_object_num += 1;
					printf("Learning....... \n");
//					filtered_input_ready = 0; //
					end_searching = 1;
					break;
				}
				if (current_spike_addr == 0) {
					end_searching = 1;
					break;
				}
			}
		}
	}


	CAER_SPIKE_ITERATOR_VALID_END

	if (learned_object_num == TRAINING_OBJECT_NUM) { //first ++, then == inside a < block, useful for denoting the end
		printf("The training is finished. \n");
		saveConnectivity(moduleData);
	}

}
