static uint32_t encodeNeuronAddress4Chip(int64_t chip_id, int64_t chip_row_id_t, int64_t chip_col_id_t);
static uint32_t encodeNeuronAddress4Core(int64_t chip_id, int64_t core_id,
	int64_t reference_row_id, int64_t reference_col_id,
	int64_t row_id, int64_t col_id, int64_t neuron_id);

uint32_t encodeNeuronAddress4Chip(int64_t chip_id, int64_t chip_row_id_t, int64_t chip_col_id_t) {
	uint32_t encoded_neuron_address;
	int64_t chip_row_id, chip_col_id;
	int64_t core_row_id, core_col_id;
	int64_t core_id, neuron_id;
	chip_row_id = chip_row_id_t;
	chip_col_id = chip_col_id_t;
	core_row_id = chip_row_id % DYNAPSE_CORE_SIZE_Y;
	core_col_id = chip_col_id % DYNAPSE_CORE_SIZE_X;
	core_id = (int64_t)(chip_row_id / DYNAPSE_CORE_SIZE_Y)*2 + (int64_t)(chip_col_id / DYNAPSE_CORE_SIZE_X);
	neuron_id = core_row_id << 4 | core_col_id;
	encoded_neuron_address = (uint32_t)(chip_id << NEURON_CHIPID_SHIFT | core_id << NEURON_COREID_SHIFT | neuron_id);
	return(encoded_neuron_address);
}

uint32_t encodeNeuronAddress4Core(int64_t chip_id, int64_t core_id,
	int64_t reference_row_id, int64_t reference_col_id,
	int64_t row_id, int64_t col_id, int64_t neuron_id) {
	uint32_t encoded_neuron_address;
	int64_t core_row_id, core_col_id;
	core_row_id = reference_row_id + row_id*2 + (int64_t) (neuron_id/2);
	core_col_id = reference_col_id + col_id*2 + neuron_id%2;
	encoded_neuron_address = (uint32_t)(chip_id << NEURON_CHIPID_SHIFT | core_id << NEURON_COREID_SHIFT | core_row_id << 4 | core_col_id);
	return(encoded_neuron_address);
}
