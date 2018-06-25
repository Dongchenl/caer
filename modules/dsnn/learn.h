static void learning(caerModuleData moduleData, caerSpikeEventPacketConst spike);

static int8_t synapse_updated = 0;
static int64_t last_update_time = 0;
//static int8_t stability_checked = 1;

void learning(caerModuleData moduleData, caerSpikeEventPacketConst spike) {

	CAER_SPIKE_ITERATOR_VALID_START(spike) //iterate over received spikes

	int8_t spike_not_considered = 0;

	//Get spike timing information
	int64_t ts = caerSpikeEventGetTimestamp64(caerSpikeIteratorElement, spike); //get values on which to operate.

	//Wait the initialization to be finished
	if (set_first_ts == 0 && ts > 0) {
		first_ts = ts;
		set_first_ts = 1;
	}
	if (ini_finished == 0) {
		if (ts - first_ts >= 1000 * 1000 * 110) {
			ini_finished = 1;
			applyMotorSignal(moduleData);
			printf("Ready to learn. \n");
			filtered_input_ready = 1;
		} else {
			spike_not_considered = 1;
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

	if (chip_id == 3 && core_id == 1 && neuron_id == 105) { //malfunction neuron
		spike_not_considered = 1;
	}
	int32_t random_number = rand() % 100;
	if (random_number > 20) { //10
		spike_not_considered = 1;
	}

	//record spikes from the input layer
	if (spike_not_considered == 0) {
		if (chip_id == 4 && core_id == 3) {
			uint32_t new_core_id = 1;
			int64_t spike_addr = chip_id << NEURON_CHIPID_SHIFT | new_core_id << NEURON_COREID_SHIFT | neuron_id;
			memory.spike_fifo->buffer2d[memory.wr_pointer][0] = spike_addr; //put spike address into the queue
			memory.spike_fifo->buffer2d[memory.wr_pointer][1] = ts; //put spike address into the queue
			memory.wr_pointer = (memory.wr_pointer + 1) % SPIKE_QUEUE_LENGTH;
		}

		//Check the silence
		int8_t spike_valid = 0;
		if (chip_id == 4 && core_id == 3 && micro_saccade_finished == 1) {
			//calculate the number of spikes in a period
			spike_valid = 1;
			memory.start_rd_pointer = memory.wr_pointer;
			start_spike_time = ts;
			int64_t spike_num = 0;
			end_searching = 0;
			for (uint64_t current_rd_pointer = (memory.start_rd_pointer - 1) % SPIKE_QUEUE_LENGTH;
				end_searching != 1;
				current_rd_pointer = (current_rd_pointer - 1) % SPIKE_QUEUE_LENGTH) {

				current_spike_addr = memory.spike_fifo->buffer2d[current_rd_pointer][0];
				current_spike_time = memory.spike_fifo->buffer2d[current_rd_pointer][1];
				delta_time = (float) (start_spike_time - current_spike_time) / 1000;

				if (delta_time > 0 && delta_time <= SILENCE_CHECKING_PERIOD) {
					spike_num += 1;
				}
				if (delta_time > SILENCE_CHECKING_PERIOD) {
					end_searching = 1;
				}
				if (current_spike_addr == 0) {
					end_searching = 1;
					printf("Warning! \n");
				}
			}
			if (spike_num >= SILENCE_CHECKING_SPIKES_THRESHOULD) {
				//if not silent, update the memory of time-stamp
				last_spike_num = spike_num;
				last_wr_pointer = memory.wr_pointer;
			}
			else if (spike_num < last_spike_num - SPIKE_REDUCED_NUM) {
				//if the spike number is decreased
				applyMotorSignal(moduleData);
				synapse_updated = 0;
				post_spike_time = ts; //update the memory of time-stamp
				last_spike_num = 0;
			}
		}

		//start the input pattern learning after a period of silence
		if ((ts - post_spike_time > REFRACTORY_PERIOD) && //REFRACTORY_PERIOD * 1000
			synapse_updated == 0 &&
			spike_valid == 1) {
			synapse_updated = 1;
			memory.start_rd_pointer = last_wr_pointer;
			start_spike_time = post_spike_time;
			int64_t spike_num = 0;
			end_searching = 0;
			for (uint64_t current_rd_pointer = (memory.start_rd_pointer - 1) % SPIKE_QUEUE_LENGTH;
				end_searching != 1;
				current_rd_pointer = (current_rd_pointer - 1) % SPIKE_QUEUE_LENGTH) {
				current_spike_addr = memory.spike_fifo->buffer2d[current_rd_pointer][0];
				current_spike_time = memory.spike_fifo->buffer2d[current_rd_pointer][1];
				delta_time = (float) (start_spike_time - current_spike_time) / 1000;
				if (delta_time > 0 && delta_time <= CONSIDERING_PERIOD) {
					spike_num += 1;
					updateMemory(current_spike_addr);
				}
				if (delta_time > CONSIDERING_PERIOD) {
					updateConfiguration(moduleData);
					end_searching = 1;
					last_update_time = post_spike_time;
					filtered_input_ready = 0;
					break;
				}
				if (current_spike_addr == 0) {
					end_searching = 1;
					break;
				}
			}
		}

		//check the stability of the input patterns
		if (ts - last_update_time > CHECK_STABILITY_PERIOD * 1000 && filtered_input_ready == 0) {
			removeMotorSignal(moduleData); //stop the simulated motor signal
			micro_saccade_finished = 0;
			filtered_input_ready = 1;
			set_first_ts_output = 0;
			ini_finished_output = 0;
			learned_object_num_updated = 0;
		}

		//learn the connectivity
		if (micro_saccade_finished == 0) {

			int64_t spike_addr = chip_id << NEURON_CHIPID_SHIFT | core_id << NEURON_COREID_SHIFT | neuron_id;
			if (chip_id == 3) {
				memory.spike_fifo_output->buffer2d[memory.wr_pointer_output][0] = spike_addr;
				memory.spike_fifo_output->buffer2d[memory.wr_pointer_output][1] = ts;
				memory.wr_pointer_output = (memory.wr_pointer_output + 1) % SPIKE_QUEUE_LENGTH;

				if (set_first_ts_output == 0) { //not necessary
					first_ts_output = ts;
					set_first_ts_output = 1;
				}
				if (ini_finished_output == 0) {
					if ((float) (ts - first_ts_output) / 1000 >= CONSIDERING_PERIOD_CHECK * 8) { //4
						ini_finished_output = 1;
						printf("Ready to learn on the output neurons. \n");
					}
				}
				if ((float) (ts - first_ts_output) / 1000 > CONSIDERING_PERIOD_CHECK * 20) {
					applyMotorSignal(moduleData);
					updateConfiguration(moduleData);
					micro_saccade_finished = 1;
					printf("The learning is finished. \n");
					if (learned_object_num_updated == 1)
						learned_object_num += 1;
//					return; //no return between CAER_SPIKE_ITERATOR_VALID_START(spike) and CAER_SPIKE_ITERATOR_VALID_END,
//					otherwise lose the rest of the events in the package.
				}
			}

			//write the ring buffer for the learning on NSMs
			if ((chip_id == 1 && core_id == 1 && row_id < 2 && col_id <= 7) ||
				(chip_id == 1 && core_id == 3 && row_id >= NSM_SIZE / 2 * 4 && row_id < NSM_SIZE / 2 * 4 + 2 && col_id <= 7)) {
				memory.spike_fifo_nsm->buffer2d[memory.wr_pointer_nsm][0] = spike_addr;
				memory.spike_fifo_nsm->buffer2d[memory.wr_pointer_nsm][1] = ts;
				memory.wr_pointer_nsm = (memory.wr_pointer_nsm + 1) % SPIKE_QUEUE_LENGTH;
			}

			//perform the learning on output neurons
			if ((chip_id == 1 && (core_id == 0 || core_id == 2)) && ini_finished_output == 1 && micro_saccade_finished == 0) {

				int32_t learned_post_neuron = memory.learned_post_synaptic_neuron->buffer2d[spike_addr - MEMORY_NEURON_ADDR_OFFSET][0];
				if (learned_post_neuron == 0) {

					learned_object_num_updated = 1;

					memory.learned_post_synaptic_neuron->buffer2d[spike_addr - MEMORY_NEURON_ADDR_OFFSET][0] = 1;
					start_spike_time = ts;

					int64_t spike_num = 0;
					memory.start_rd_pointer_output = memory.wr_pointer_output;
					end_searching = 0;
					for (uint64_t current_rd_pointer = (memory.start_rd_pointer_output - 1) % SPIKE_QUEUE_LENGTH;
						end_searching != 1;
						current_rd_pointer = (current_rd_pointer - 1) % SPIKE_QUEUE_LENGTH) {
						current_spike_addr = memory.spike_fifo_output->buffer2d[current_rd_pointer][0];
						current_spike_time = memory.spike_fifo_output->buffer2d[current_rd_pointer][1];
						delta_time = (float) (start_spike_time - current_spike_time) / 1000;
						if (current_spike_addr == 0) {
							end_searching = 1;
						}
						if (end_searching == 0) {
							if (delta_time > 0 && delta_time <= CONSIDERING_PERIOD_CHECK) {
								spike_num += 1;
								learnColumnUpdate(current_spike_addr, spike_addr);
							}
							else if (delta_time > CONSIDERING_PERIOD_CHECK) {
								learnColumnConfigure(moduleData, spike_addr);
								end_searching = 1;
							}
						}
					}
				}
			}

			//perform the learning on NSMs
			if ((chip_id == 1 && core_id == 1 && row_id < 2 && col_id <= 7) &&
				ini_finished_output == 1 && micro_saccade_finished == 0) {

				int32_t learned_post_neuron = memory.learned_post_synaptic_neuron->buffer2d[spike_addr - MEMORY_NEURON_ADDR_OFFSET][0];
				if (learned_post_neuron == 0) {

					memory.learned_post_synaptic_neuron->buffer2d[spike_addr - MEMORY_NEURON_ADDR_OFFSET][0] = 1;
					start_spike_time = ts;
					int64_t spike_num = 0;
					memory.start_rd_pointer_nsm = memory.wr_pointer_nsm;
					end_searching = 0;
					for (uint64_t current_rd_pointer = (memory.start_rd_pointer_nsm - 1) % SPIKE_QUEUE_LENGTH;
						end_searching != 1;
						current_rd_pointer = (current_rd_pointer - 1) % SPIKE_QUEUE_LENGTH) {
						current_spike_addr = memory.spike_fifo_nsm->buffer2d[current_rd_pointer][0];
						current_spike_time = memory.spike_fifo_nsm->buffer2d[current_rd_pointer][1];
						delta_time = (float) (start_spike_time - current_spike_time) / 1000;
						if (current_spike_addr == 0) {
							end_searching = 1;
						}
						if (end_searching == 0) {
							if (delta_time > 0 && delta_time <= CONSIDERING_PERIOD_CHECK) {
								spike_num += 1;
								learnNSMUpdate(current_spike_addr, spike_addr);
							}
							else if (delta_time > CONSIDERING_PERIOD_CHECK) {
								learnNSMConfigure(moduleData, spike_addr);
								end_searching = 1;
							}
						}
					}
				}
			}
		}
	}

	CAER_SPIKE_ITERATOR_VALID_END

	if (learned_object_num == TRAINING_OBJECT_NUM) { //useful for denoting the end of learning
		printf("The training is finished. \n");
		saveConnectivity();
	}

}
