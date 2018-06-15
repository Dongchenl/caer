static void setOutputToOtherChips(caerModuleData moduleData);

void setOutputToOtherChips(caerModuleData moduleData) {
	//write SRAM for ROLLS
	int64_t pre_row_id, pre_col_id, pre_neuron_id;
	uint32_t pre_neuron_addr;
	uint32_t virtual_neuron_addr = 1 << 10 | 0 << 8 | 0;
	int8_t virtual_neuron_addr_enable = 1;

	printf("Set output to ROLLs. \n");
	for (pre_row_id = 0; pre_row_id < OUTPUT_POPULATION_EI_L; pre_row_id++) {
		for (pre_col_id = 0; pre_col_id < OUTPUT_POPULATION_EI_W; pre_col_id++) {
			for (pre_neuron_id = 0; pre_neuron_id < OUTPUT_POPULATION_EI_SIZE; pre_neuron_id++) {
				pre_neuron_addr = output_population_ex[pre_row_id][pre_col_id][pre_neuron_id];
				uint32_t sram_id = 2; //1;
				int8_t stdp = 0;
				uint32_t chip_core_id;
				chip_core_id = 0xf << 6 | CORE_UP_LEFT_ID << 4 | 0xf;
				writeSramDSNN(moduleData, pre_neuron_addr, chip_core_id,
					virtual_neuron_addr, sram_id, virtual_neuron_addr_enable, stdp);
//				printf("Write SRAM. \n");
			}
		}
	}

}
