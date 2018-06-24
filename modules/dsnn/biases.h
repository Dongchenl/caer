static void resetBiasesDSNN(caerModuleData moduleData);
static void resetBiasesLowDCDSNN(caerModuleData moduleData);
static void setDavisInputLayerBiases(caerModuleData moduleData);

void resetBiasesDSNN(caerModuleData moduleData) {
	//reset all the biases on chip
	DSNNState state = moduleData->moduleState;

	uint32_t chip_id_t, chip_id, core_id;
	for (chip_id_t = 0; chip_id_t < 4; chip_id_t++) {

		if (chip_id_t == 0)
			chip_id = DYNAPSE_CONFIG_DYNAPSE_U0;
		else if (chip_id_t == 1)
			chip_id = DYNAPSE_CONFIG_DYNAPSE_U1;
		else if (chip_id_t == 2)
			chip_id = DYNAPSE_CONFIG_DYNAPSE_U2;
		else if (chip_id_t == 3)
			chip_id = DYNAPSE_CONFIG_DYNAPSE_U3;
		caerDeviceConfigSet(state->eventSourceModuleState, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, chip_id);

		for (core_id = 0; core_id < 4; core_id++) {
			//sweep all the biases
			if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U0) {
				if (core_id == 0) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 4, 30, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 1, 43, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 7, 5, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 2, 254, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 3, 153, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 1, 200, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 4, 20, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 0, 60, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 205, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 5, 109, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				}
				if (core_id == 1) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 1, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 2, 199, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 5, 249, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 3, 200, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 5, 150, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 3, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 5, 105, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 3, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 5, 26, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 1, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 0, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 5, 89, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				} else if (core_id == 2) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 4, 30, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 1, 225, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 3, 241, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 2, 254, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 3, 153, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 1, 200, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 5, 20, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 0, 100, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 205, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 5, 109, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				} else if (core_id == 3) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 0, 254, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 1, 225, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 3, 241, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 1, 254, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 3, 153, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 0, 200, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 6, 8, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 3, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 5, 26, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 1, 200, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 4, 8, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 0, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 0, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 0, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 5, 109, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				}
			} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U1) {
				if (core_id == 0 || core_id == 2) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 3, 134, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 3, 30, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 3, 228, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 2, 110, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 3, 11, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 6, 19, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 236, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				} else if (core_id == 1) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 1, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 1, 100, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 1, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 1, 38, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 4, 219, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 1, 200, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 5, 60, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 3, 222, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 250, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 2, 10, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				} else if (core_id == 3) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 1, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 1, 100, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 1, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 1, 38, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 4, 219, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 1, 200, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 5, 60, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 3, 222, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 250, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 2, 10, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				}
			} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U2) {
				if (core_id == 0) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 3, 246, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 3, 30, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 3, 228, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 2, 110, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 3, 11, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 6, 19, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 236, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				} else if (core_id == 2) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 3, 118, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 3, 30, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 3, 228, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 2, 110, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 3, 11, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 6, 19, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 236, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				} else if (core_id == 1) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 1, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 1, 48, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 1, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 1, 38, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 4, 219, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 1, 200, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 5, 60, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 3, 222, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 250, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 2, 7, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				} else if (core_id == 3) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 1, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 0, 48, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 1, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 1, 38, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 4, 219, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 1, 200, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 5, 60, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 3, 222, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 250, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 2, 7, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				}
			} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U3) {
				if (core_id == 0) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 3, 134, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 3, 30, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 3, 228, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 2, 110, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 3, 11, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 6, 19, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 236, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				} else if (core_id == 2) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 3, 134, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 3, 30, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 3, 228, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 2, 110, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 3, 11, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 6, 19, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 236, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				} else if (core_id == 1) {
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 1, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 1, 48, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 2, 215, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 1, 38, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 6, 219, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 3, 222, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 2, 7, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				} else if (core_id == 3) {
					//the best bias
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 0, 255, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 2, 135, "LowBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 2, 250, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 1, 100, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 6, 159, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 1, 200, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 7, 200, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 0, 250, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 250, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 0, "HighBias", "NBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 2, 30, "HighBias", "PBias");
					setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
				}
			}
		}
	}
}

void resetBiasesLowDCDSNN(caerModuleData moduleData) {
	//reset all the biases on chip
	DSNNState state = moduleData->moduleState;

	uint32_t chip_id_t, chip_id, core_id;
	//sweep all the biases
	for (chip_id_t = 0; chip_id_t < 4; chip_id_t++) {

		if (chip_id_t == 0)
			chip_id = DYNAPSE_CONFIG_DYNAPSE_U0;
		else if (chip_id_t == 1)
			chip_id = DYNAPSE_CONFIG_DYNAPSE_U1;
		else if (chip_id_t == 2)
			chip_id = DYNAPSE_CONFIG_DYNAPSE_U2;
		else if (chip_id_t == 3)
			chip_id = DYNAPSE_CONFIG_DYNAPSE_U3;
		caerDeviceConfigSet(state->eventSourceModuleState, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, chip_id);

		for (core_id = 0; core_id < 4; core_id++) {
			setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 1, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 1, "HighBias", "PBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 3, 80, "HighBias", "PBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 1, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 5, 2, "HighBias", "PBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 1, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 2, 180, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 3, 40, "LowBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 6, 15, "LowBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 3, 180, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 6, 150, "HighBias", "PBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 7, 40, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 4, 220, "HighBias", "PBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 6, 150, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 7, 40, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 0, 220, "HighBias", "PBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 0, 70, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 1, 250, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 0, 250, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 1, 250, "HighBias", "NBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 3, 50, "HighBias", "PBias");
			setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
		}
	}
}

void setDavisInputLayerBiases(caerModuleData moduleData) { //FPGA local filter 2006010905
	uint32_t chip_id = DYNAPSE_CONFIG_DYNAPSE_U3;
	uint32_t core_id = 3;

	setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTAU_N", 7, 35, "LowBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHTHR_N", 7, 1, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_AHW_P", 7, 1, "HighBias", "PBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_BUF_P", 7, 0, "HighBias", "PBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_CASC_N", 7, 1, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_DC_P", 7, 2, "HighBias", "PBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_NMDA_N", 7, 1, "HighBias", "PBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_RFR_N", 4, 108, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU1_N", 5, 50, "LowBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_TAU2_N", 5, 15, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "IF_THR_N", 0, 176, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_F_P", 0, 220, "HighBias", "PBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_F_P", 5, 51, "HighBias", "PBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_THR_S_P", 7, 0, "HighBias", "PBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPIE_TAU_S_P", 0, 255, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_F_P", 7, 0, "HighBias", "PBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_F_P", 0, 255, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_THR_S_P", 7, 0, "HighBias", "PBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "NPDPII_TAU_S_P", 0, 255, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_F_N", 0, 120, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_EXC_S_N", 7, 1, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_F_N", 7, 1, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "PS_WEIGHT_INH_S_N", 7, 1, "HighBias", "NBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "PULSE_PWLK_P", 0, 255, "HighBias", "PBias");
	setBiasBitsDSNN(moduleData, chip_id, core_id, "R2R_P", 4, 85, "HighBias", "PBias");
}
