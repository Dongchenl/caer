static void buildSynapseDSNN(caerModuleData moduleData, uint32_t pre_neuron_addr, uint32_t post_neuron_addr, uint32_t virtual_neuron_addr,
	int32_t synapse_type, int8_t real_or_virtual_synapse, int8_t virtual_neuron_addr_enable, uint32_t cam_id_search_start);
//static void writeCamDSNN(caerModuleData moduleData, uint32_t pre_neuron_addr, uint32_t post_neuron_addr, uint32_t virtual_neuron_addr,
//	uint32_t cam_id, int32_t synapse_type, int8_t virtual_neuron_addr_enable, int8_t stdp);
static void writeSramDSNN(caerModuleData moduleData, uint32_t pre_neuron_addr, uint32_t chip_core_id, uint32_t virtual_neuron_addr,
	uint32_t sram_id, int8_t virtual_neuron_addr_enable, int8_t stdp);
static void writeCamDSNN(caerModuleData moduleData, uint32_t pre_neuron_addr, uint32_t post_neuron_addr, uint32_t virtual_neuron_addr,
	uint32_t cam_id, int32_t synapse_type, int8_t virtual_neuron_addr_enable, int8_t stdp);
static uint32_t getWriteCamBitsDSNN(uint32_t pre_neuron_addr, uint32_t post_neuron_addr, uint32_t virtual_neuron_addr,
	uint32_t cam_id, int32_t synapse_type, int8_t virtual_neuron_addr_enable);
static uint32_t getWriteSramBitsDSNN(uint32_t pre_neuron_addr, uint32_t chip_core_id, uint32_t virtual_neuron_addr,
	uint32_t sram_id, int8_t virtual_neuron_addr_enable);

uint32_t getWriteCamBitsDSNN(uint32_t pre_neuron_addr, uint32_t post_neuron_addr, uint32_t virtual_neuron_addr,
	uint32_t cam_id, int32_t synapse_type, int8_t virtual_neuron_addr_enable) {
	//get neuron CAM bits when a synapse is built or modified
	uint32_t bits;
	uint32_t ei = 0;
	uint32_t fs = 0;
	uint32_t address = pre_neuron_addr & NEURON_ADDRESS_BITS;
	uint32_t source_core = 0;
	if (virtual_neuron_addr_enable == 0)
		source_core = (pre_neuron_addr & NEURON_COREID_BITS) >> NEURON_COREID_SHIFT;
	else
		source_core = (virtual_neuron_addr & NEURON_COREID_BITS) >> NEURON_COREID_SHIFT;
	if (synapse_type > 0)
		ei = EXCITATORY_SYNAPSE_ID;
	else
		ei = INHIBITORY_SYNAPSE_ID;
	if (abs(synapse_type) == FAST_SYNAPSE_VALUE)
		fs = FAST_SYNAPSE_ID;
	else if (abs(synapse_type) == SLOW_SYNAPSE_VALUE)
		fs = SLOW_SYNAPSE_ID;
	else if (abs(synapse_type) == NO_SYNAPSE_ID) {
		address = NO_SYNAPSE_ADDRESS;
		source_core = NO_SYNAPSE_CORE;
	}
	uint32_t core_id = (post_neuron_addr & NEURON_COREID_BITS) >> NEURON_COREID_SHIFT;
	uint32_t neuron_row = (post_neuron_addr & NEURON_ROWID_BITS) >> NEURON_ROWID_SHIFT;
	uint32_t synapse_row = cam_id;
	uint32_t row = neuron_row << CAM_NEURON_ROW_SHIFT | synapse_row;
	uint32_t column = post_neuron_addr & NEURON_COLID_BITS;
	bits = ei << CXQ_CAM_EI_SHIFT | fs << CXQ_CAM_FS_SHIFT |
		address << CXQ_ADDR_SHIFT | source_core << CXQ_SOURCE_CORE_SHIFT |
		CXQ_PROGRAM |
		core_id << CXQ_PROGRAM_COREID_SHIFT | row << CXQ_PROGRAM_ROW_SHIFT | column << CXQ_PROGRAM_COLUMN_SHIFT;
	return (bits);
}

uint32_t getWriteSramBitsDSNN(uint32_t pre_neuron_addr, uint32_t chip_core_id, uint32_t virtual_neuron_addr,
	uint32_t sram_id, int8_t virtual_neuron_addr_enable) {
	//get neuron SRAM bits when a synapse is built or modified
	uint32_t bits;
	uint32_t virtual_core_id = 0;
	if (virtual_neuron_addr_enable == 0)
		virtual_core_id = (pre_neuron_addr & NEURON_COREID_BITS) >> NEURON_COREID_SHIFT;
	else
		virtual_core_id = (virtual_neuron_addr & NEURON_COREID_BITS) >> NEURON_COREID_SHIFT;
	uint32_t source_chipId = (pre_neuron_addr >> NEURON_CHIPID_SHIFT) - 1;
	uint32_t destination_chipId = (chip_core_id >> CHIPCOREID_CHIPID_SHIFT) - 1;
	uint32_t sy, dy, sx, dx;
	if ((source_chipId / BOARD_CHIPS_Y_NUM) >= (destination_chipId / BOARD_CHIPS_Y_NUM))
		sy = EVENT_DIRECTION_Y_UP;
	else
		sy = EVENT_DIRECTION_Y_DOWN;
	if ((source_chipId % BOARD_CHIPS_X_NUM) <= (destination_chipId % BOARD_CHIPS_X_NUM))
		sx = EVENT_DIRECTION_X_RIGHT;
	else
		sx = EVENT_DIRECTION_X_LEFT;
	if (source_chipId == destination_chipId) {
		dx = 0;
		dy = 0;
	} else {
		dx = (uint32_t) abs((int32_t)(source_chipId % BOARD_CHIPS_X_NUM) - (int32_t)(destination_chipId % BOARD_CHIPS_X_NUM));
		dy = (uint32_t) abs((int32_t)(source_chipId / BOARD_CHIPS_Y_NUM) - (int32_t)(destination_chipId / BOARD_CHIPS_Y_NUM));
	}
	if (source_chipId == 0 && destination_chipId == 1) {
		sx = 0;
		dx = 0;
		sy = EVENT_DIRECTION_Y_UP;
		dy = 2;
	}
	if (source_chipId == 0 && destination_chipId == 3) {
		sx = 0;
		dx = 0;
		sy = EVENT_DIRECTION_Y_UP;
		dy = 1;
	}
	if (source_chipId == 0 && destination_chipId == 0xf - 1) {
		sx = EVENT_DIRECTION_X_LEFT; //0;
		dx = 1; //0;
		sy = 0; //EVENT_DIRECTION_Y_UP;
		dy = 0; //1;
	}

	uint32_t destination_coreId = chip_core_id & DESTINATION_COREID_BITS;
	uint32_t core_id = (pre_neuron_addr & NEURON_COREID_BITS) >> NEURON_COREID_SHIFT;
	uint32_t neuron_row = (pre_neuron_addr & NEURON_ROWID_BITS) >> NEURON_ROWID_SHIFT;
	uint32_t neuron_column = pre_neuron_addr & NEURON_COLID_BITS;
	uint32_t synapse_row = sram_id;
	uint32_t row = neuron_row << SRAM_NEURON_ROW_SHIFT | neuron_column << SRAM_NEURON_COL_SHIFT | synapse_row;
	uint32_t column = SRAM_COL_VALUE;
	bits = virtual_core_id << CXQ_SRAM_VIRTUAL_SOURCE_CORE_SHIFT |
		sy << CXQ_SRAM_SY_SHIFT | dy << CXQ_SRAM_DY_SHIFT | sx << CXQ_SRAM_SX_SHIFT | dx << CXQ_SRAM_DX_SHIFT |
		destination_coreId << CXQ_SRAM_DEST_CORE_SHIFT |
		CXQ_PROGRAM |
		core_id << CXQ_PROGRAM_COREID_SHIFT | row << CXQ_PROGRAM_ROW_SHIFT | column << CXQ_PROGRAM_COLUMN_SHIFT;
	return (bits);
}

void writeCamDSNN(caerModuleData moduleData, uint32_t pre_neuron_addr, uint32_t post_neuron_addr, uint32_t virtual_neuron_addr,
	uint32_t cam_id, int32_t synapse_type, int8_t virtual_neuron_addr_enable, int8_t stdp) {
//void writeCamDSNN(caerModuleData moduleData, uint32_t pre_neuron_addr, uint32_t post_neuron_addr, uint32_t virtual_neuron_addr,
//	uint32_t cam_id, int32_t synapse_type, int8_t virtual_neuron_addr_enable, int8_t stdp) {
	//write neuron CAM when a synapse is built or modified
	DSNNState state = moduleData->moduleState;
	uint32_t chip_id, bits;
	chip_id = getWriteCamSramChipIdDSNN(post_neuron_addr);
	bits = getWriteCamBitsDSNN(pre_neuron_addr, post_neuron_addr, virtual_neuron_addr, cam_id, synapse_type, virtual_neuron_addr_enable);
	if (stdp == 0) {
		if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U0) {
			if (num_config_chip_U0 == usb_packet_maximum_size)
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
			bits_chip_U0[num_config_chip_U0] = (uint32_t) bits;
			num_config_chip_U0++;
		} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U1) {
			if (num_config_chip_U1 == usb_packet_maximum_size)
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
			bits_chip_U1[num_config_chip_U1] = (uint32_t) bits;
			num_config_chip_U1++;
		} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U2) {
			if (num_config_chip_U2 == usb_packet_maximum_size)
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
			bits_chip_U2[num_config_chip_U2] = (uint32_t) bits;
			num_config_chip_U2++;
		} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U3) {
			if (num_config_chip_U3 == usb_packet_maximum_size)
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
			bits_chip_U3[num_config_chip_U3] = (uint32_t) bits;
			num_config_chip_U3++;
		}
	} else {
		caerDeviceConfigSet(state->eventSourceModuleState, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, chip_id);
		caerDeviceConfigSet(state->eventSourceModuleState, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_CONTENT, bits); //this is the 30 bits
	}
}

void writeSramDSNN(caerModuleData moduleData, uint32_t pre_neuron_addr, uint32_t chip_core_id, uint32_t virtual_neuron_addr,
	uint32_t sram_id, int8_t virtual_neuron_addr_enable, int8_t stdp) {
	//write neuron SRAM when a synapse is built
	DSNNState state = moduleData->moduleState;
	uint32_t chip_id, bits;
	chip_id = getWriteCamSramChipIdDSNN(pre_neuron_addr);
	bits = getWriteSramBitsDSNN(pre_neuron_addr, chip_core_id, virtual_neuron_addr, sram_id, virtual_neuron_addr_enable);
	if (stdp == 0) {
		if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U0) {
			if (num_config_chip_U0 == usb_packet_maximum_size)
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U0);
			bits_chip_U0[num_config_chip_U0] = (uint32_t) bits;
			num_config_chip_U0++;
		} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U1) {
			if (num_config_chip_U1 == usb_packet_maximum_size)
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U1);
			bits_chip_U1[num_config_chip_U1] = (uint32_t) bits;
			num_config_chip_U1++;
		} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U2) {
			if (num_config_chip_U2 == usb_packet_maximum_size)
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U2);
			bits_chip_U2[num_config_chip_U2] = (uint32_t) bits;
			num_config_chip_U2++;
		} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U3) {
			if (num_config_chip_U3 == usb_packet_maximum_size)
				configureChipDSNN(moduleData, DYNAPSE_CONFIG_DYNAPSE_U3);
			bits_chip_U3[num_config_chip_U3] = (uint32_t) bits;
			num_config_chip_U3++;
		}
	} else {
		caerDeviceConfigSet(state->eventSourceModuleState, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, chip_id);
		caerDeviceConfigSet(state->eventSourceModuleState, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_CONTENT, bits); //this is the 30 bits
	}

}

void buildSynapseDSNN(caerModuleData moduleData, uint32_t pre_neuron_addr, uint32_t post_neuron_addr, uint32_t virtual_neuron_addr,
	int32_t synapse_type, int8_t real_or_virtual_synapse, int8_t virtual_neuron_addr_enable, uint32_t cam_id_search_start) {
	//build synapses when reseting
	uint32_t sram_id, cam_id, sram_id_t, cam_id_t;
	uint32_t chip_core_id; //chip_core_id: chip_id (4 bits), source_core_id (2 bits), destination_core_id (4 bits)
	uint32_t chip_id, destCoreId, source_core_id;

	int sram_found, sram_slot_found, camFound, availableCamFound;
	int sramAvailable;
	int32_t core_neuron_id, new_core_neuron_id;

	//for SRAM
	if (real_or_virtual_synapse != EXTERNAL_REAL_SYNAPSE && real_or_virtual_synapse != VIRTUAL_SYNAPSE_WITHOUT_SRAM) {
		sram_found = 0;
		sram_slot_found = 0;
		for (sram_id_t = 1; sram_id_t < TOTAL_SRAM_NUM; sram_id_t++) { //search for available SRAM
			chip_id = (post_neuron_addr >> 10);
			destCoreId = (post_neuron_addr & 0x300) >> 8;
			if (virtual_neuron_addr_enable == 0)
				source_core_id = (pre_neuron_addr & 0x300) >> 8;
			else
				source_core_id = (virtual_neuron_addr & 0x300) >> 8;
			if (memory.sram_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][sram_id_t] == 1) {
				if (memory.sram_map_content->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][sram_id_t] >> 6 == (int) chip_id &&
					(memory.sram_map_content->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][sram_id_t] & 0x30) >> 4 == (int) source_core_id) {
					if (((memory.sram_map_content->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][sram_id_t] & 0xf) & (1 << destCoreId)) != 0) {
						sram_found = 1;
					} else {
						sram_slot_found = 1;
					}
					sram_id = sram_id_t;
					break;
				}
			}
		}
		if (sram_slot_found == 1) {
			chip_core_id = (uint32_t) (memory.sram_map_content->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][sram_id] | (1 << ((post_neuron_addr & 0x300) >> 8)));
			writeSramDSNN(moduleData, pre_neuron_addr, chip_core_id, virtual_neuron_addr, sram_id, virtual_neuron_addr_enable, 0);
			memory.sram_map_content->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][sram_id] = (int) chip_core_id; //SRAM is taken
		}
		if (sram_found == 0 && sram_slot_found == 0) {
			sramAvailable = 0;
			for (sram_id_t = 0; sram_id_t < TOTAL_SRAM_NUM-1; sram_id_t++) { //search for available SRAM
				if (sramAvailable == 0
					&& memory.sram_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][(sram_id_t + 1) % TOTAL_SRAM_NUM] == 0) {
					sramAvailable = 1;
					sram_id = (sram_id_t + 1) % TOTAL_SRAM_NUM;
				}
			}
			if (sramAvailable == 1 && sram_id != 0) {
				if (virtual_neuron_addr_enable == 0)
					source_core_id = (uint32_t) ((pre_neuron_addr & 0x300) >> 8);
				else
					source_core_id = (uint32_t) ((virtual_neuron_addr & 0x300) >> 8);
				chip_core_id = (((post_neuron_addr >> 10) << 6) | (source_core_id << 4) | (uint32_t) (1 << ((post_neuron_addr & 0x300) >> 8)));
				writeSramDSNN(moduleData, pre_neuron_addr, chip_core_id, virtual_neuron_addr, sram_id, virtual_neuron_addr_enable, 0);
				memory.sram_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][sram_id] = 1; //SRAM is taken
				memory.sram_map_content->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][sram_id] = (int) chip_core_id;
			}
		}
	}
	//for CAM
	camFound = 0;
	for (cam_id_t = 0; cam_id_t < TOTAL_CAM_NUM; cam_id_t++) { //search for existing CAM
		if (memory.cam_map->buffer2d[post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][cam_id_t] == 1) {
			core_neuron_id = memory.cam_map_source_id->buffer2d[post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][cam_id_t] & 0x3ff;
			if (virtual_neuron_addr_enable == 0)
				new_core_neuron_id = pre_neuron_addr & 0x3ff;
			else
				new_core_neuron_id = virtual_neuron_addr & 0x3ff;
			if (core_neuron_id == new_core_neuron_id) {
				camFound = 1;
				cam_id = cam_id_t;
				break;
			}
		}
	}
	if (camFound == 0) {
		availableCamFound = 0;
		for (cam_id_t = cam_id_search_start; cam_id_t < TOTAL_CAM_NUM; cam_id_t++) { //search for available CAM
			if (memory.cam_map->buffer2d[post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][cam_id_t] == 0) {
				cam_id = cam_id_t;
				availableCamFound = 1;
				break;
			}
		}
		if (availableCamFound == 1) {
			if (real_or_virtual_synapse != VIRTUAL_SYNAPSE && real_or_virtual_synapse != VIRTUAL_SYNAPSE_WITHOUT_SRAM) {
				writeCamDSNN(moduleData, pre_neuron_addr, post_neuron_addr, virtual_neuron_addr, cam_id, synapse_type, virtual_neuron_addr_enable, 0);
				memory.cam_map->buffer2d[post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][cam_id] = 1;
			}
			if (virtual_neuron_addr_enable == 0)
				new_core_neuron_id = pre_neuron_addr & 0x3ff;
			else
				new_core_neuron_id = virtual_neuron_addr & 0x3ff;
			memory.cam_map_source_id->buffer2d[post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][cam_id] = new_core_neuron_id;
		} else {
			perror("No CAM is available. ");
		}
	}
	//memories for the chip
	if (real_or_virtual_synapse == REAL_SYNAPSE) {
		memory.connection_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
		if (synapse_type > 0)
			memory.connection_map_ei->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
		memory.synapse_map_cam_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = (int32_t) cam_id;
		memory.synapse_map_sram_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = (int32_t) sram_id;
	}
	if (real_or_virtual_synapse == VIRTUAL_SYNAPSE || real_or_virtual_synapse == VIRTUAL_SYNAPSE_WITHOUT_SRAM) {
//		printf("Build one virtual synapse. \n");
//		printf("Pre: %d, Post: %d. \n", binary_conversion(pre_neuron_addr), binary_conversion(post_neuron_addr));
		memory.connection_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
		if (synapse_type > 0)
			memory.connection_map_ei->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
		memory.synapse_map_sram_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = (int32_t) sram_id;
	}
	if (real_or_virtual_synapse == REAL_SYNAPSE) {
		memory.synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
	}
	if (virtual_neuron_addr_enable == 1) {
		memory.virtual_neuron_addr_enable->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
		memory.virtual_neuron_addr->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = (int32_t) virtual_neuron_addr;
	}
	if (real_or_virtual_synapse == REAL_SYNAPSE_WITHOUT_LEARNING) {
		memory.non_learning_connection_map->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
		memory.synapse_map_cam_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = (int32_t) cam_id;
		memory.synapse_map_sram_no->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = (int32_t) sram_id;
		memory.non_learning_synapse_map_type->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = synapse_type; //
		if (synapse_type > 0)
			memory.connection_map_ei->buffer2d[pre_neuron_addr - MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr - MEMORY_NEURON_ADDR_OFFSET] = 1;
	}
}
