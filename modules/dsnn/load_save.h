static void loadConnectivity(caerModuleData moduleData);
static void saveConnectivity(void);

void loadConnectivity(caerModuleData moduleData) {
	    int i = 0, j = 0;
	    int synapse_memory[CONNECTIVITY_NUM][8]; //7
		FILE *file;
		file = fopen("saved_connectivity.txt", "r");
		if (file) {
			for (i = 0; i < CONNECTIVITY_NUM; i++) {
			    for (j = 0; j < 8; j++) {
			    	fscanf(file, "%d", &synapse_memory[i][j]);
			    }
			}
		    if (ferror(file)) {
		    }
		    fclose(file);
		}
		for (i = 0; i < CONNECTIVITY_NUM; i++) {
	    	int32_t pre_neuron_addr = synapse_memory[i][0];
	    	int32_t post_neuron_addr = synapse_memory[i][1];
	    	int32_t virtual_neuron_addr = synapse_memory[i][2];
	    	int32_t virtual_neuron_addr_enable = synapse_memory[i][3];
	    	int32_t synapse_type = synapse_memory[i][4];
	    	int32_t cam_id = synapse_memory[i][5];
	    	int32_t sram_id = synapse_memory[i][6];
	    	int32_t chip_core_id = synapse_memory[i][7];
	    	if (pre_neuron_addr < 1024 || pre_neuron_addr >= 1024 + 1024*4)
	    		break;
	    	writeCamDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) post_neuron_addr, (uint32_t) virtual_neuron_addr,
	    		(uint32_t) cam_id, synapse_type, (int8_t) virtual_neuron_addr_enable, 0);

	    	memory.sram_map_content->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][sram_id] = chip_core_id;
	   		writeSramDSNN(moduleData, (uint32_t) pre_neuron_addr, (uint32_t) chip_core_id, (uint32_t) virtual_neuron_addr,
	   			(uint32_t) sram_id, (int8_t) virtual_neuron_addr_enable, 0);

	    	if (virtual_neuron_addr_enable == 1) {
	    		memory.virtual_neuron_addr_enable->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET] = 1;
	    		memory.virtual_neuron_addr->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET] = virtual_neuron_addr;
	    	}
	    	memory.synapse_map_cam_no->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET] = cam_id;
	    	memory.synapse_map_sram_no->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET] = sram_id;
	    	memory.non_learning_connection_map->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET] = 1;
	    	memory.non_learning_synapse_map_type->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET] = synapse_type;
	    	memory.sram_map_content->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][sram_id] = chip_core_id;
		}

		FILE *f = fopen("saved_connectivity_check.txt", "w");
		if (f == NULL)
		{
		    printf("Error opening file!\n");
		    exit(1);
		}
		for (int32_t pre_neuron_addr = MEMORY_NEURON_ADDR_OFFSET; pre_neuron_addr < MEMORY_NEURON_ADDR_OFFSET + TOTAL_NEURON_NUM_ON_BOARD; pre_neuron_addr++) {
			for (int32_t post_neuron_addr = MEMORY_NEURON_ADDR_OFFSET; post_neuron_addr < MEMORY_NEURON_ADDR_OFFSET + TOTAL_NEURON_NUM_ON_BOARD; post_neuron_addr++) {
				int32_t connection_record, non_learning_connection_record;
				connection_record = memory.connection_map->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
				non_learning_connection_record = memory.non_learning_connection_map->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
				if (connection_record == 1) {
					int32_t virtual_neuron_addr = 0;
					int32_t virtual_neuron_addr_enable = 0;
					int32_t synapse_type = memory.synapse_map_type->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
					int32_t cam_id = memory.synapse_map_cam_no->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
					int32_t sram_id = memory.synapse_map_sram_no->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
					int32_t chip_core_id = memory.sram_map_content->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][sram_id];
					if (synapse_type != 0) {
						fprintf(f, "%d", (int) pre_neuron_addr);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) post_neuron_addr);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) virtual_neuron_addr);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) virtual_neuron_addr_enable);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) synapse_type);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) cam_id);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) sram_id);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) chip_core_id);
						fprintf(f, "\n");
					}
				} else if (non_learning_connection_record == 1) {
					int32_t virtual_neuron_addr = memory.virtual_neuron_addr->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
					int32_t virtual_neuron_addr_enable = memory.virtual_neuron_addr_enable->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
					int32_t synapse_type = memory.non_learning_synapse_map_type->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
					int32_t cam_id = memory.synapse_map_cam_no->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
					int32_t sram_id = memory.synapse_map_sram_no->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
					int32_t chip_core_id = memory.sram_map_content->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][sram_id];
					if (synapse_type != 0) {
						fprintf(f, "%d", (int) pre_neuron_addr);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) post_neuron_addr);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) virtual_neuron_addr);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) virtual_neuron_addr_enable);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) synapse_type);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) cam_id);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) sram_id);
						fprintf(f, "\t");
						fprintf(f, "%d", (int) chip_core_id);
						fprintf(f, "\n");
					}
				}
			}
		}
		fclose(f);
		printf("The learned connectivity is loaded from file \'saved_connectivity.txt\'. \n");
}

void saveConnectivity() {
	FILE *f = fopen("saved_connectivity.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	for (int32_t pre_neuron_addr = MEMORY_NEURON_ADDR_OFFSET; pre_neuron_addr < MEMORY_NEURON_ADDR_OFFSET + TOTAL_NEURON_NUM_ON_BOARD; pre_neuron_addr++) {
		for (int32_t post_neuron_addr = MEMORY_NEURON_ADDR_OFFSET; post_neuron_addr < MEMORY_NEURON_ADDR_OFFSET + TOTAL_NEURON_NUM_ON_BOARD; post_neuron_addr++) {
			int32_t connection_record, non_learning_connection_record;
			connection_record = memory.connection_map->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
			non_learning_connection_record = memory.non_learning_connection_map->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
			if (connection_record == 1) {
				int32_t virtual_neuron_addr = 0;
				int32_t virtual_neuron_addr_enable = 0;
				int32_t synapse_type = memory.synapse_map_type->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
				int32_t cam_id = memory.synapse_map_cam_no->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
				int32_t sram_id = memory.synapse_map_sram_no->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
				int32_t chip_core_id = memory.sram_map_content->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][sram_id];
				if (synapse_type != 0) {
					fprintf(f, "%d", (int) pre_neuron_addr);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) post_neuron_addr);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) virtual_neuron_addr);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) virtual_neuron_addr_enable);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) synapse_type);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) cam_id);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) sram_id);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) chip_core_id);
					fprintf(f, "\n");
				}
			} else if (non_learning_connection_record == 1) {
				int32_t virtual_neuron_addr = memory.virtual_neuron_addr->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
				int32_t virtual_neuron_addr_enable = memory.virtual_neuron_addr_enable->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
				int32_t synapse_type = memory.non_learning_synapse_map_type->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
				int32_t cam_id = memory.synapse_map_cam_no->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
				int32_t sram_id = memory.synapse_map_sram_no->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][post_neuron_addr-MEMORY_NEURON_ADDR_OFFSET];
				int32_t chip_core_id = memory.sram_map_content->buffer2d[pre_neuron_addr-MEMORY_NEURON_ADDR_OFFSET][sram_id];
				if (synapse_type != 0) {
					fprintf(f, "%d", (int) pre_neuron_addr);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) post_neuron_addr);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) virtual_neuron_addr);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) virtual_neuron_addr_enable);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) synapse_type);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) cam_id);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) sram_id);
					fprintf(f, "\t");
					fprintf(f, "%d", (int) chip_core_id);
					fprintf(f, "\n");
				}
			}
		}
	}
	fclose(f);
	printf("The learned connectivity is stored in file \'saved_connectivity.txt\'. \n");
}
