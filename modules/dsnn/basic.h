#include "base/mainloop.h"
#include "base/module.h"
#include "ext/buffers.h"
#include "libcaer/devices/dynapse.h"
#include "modules/ini/dynapse_utils.h"
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>
#ifdef _WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

struct DSNN_state {
	caerDeviceHandle eventSourceModuleState;
	sshsNode eventSourceConfigNode;
	uint16_t event_source_id;
	bool learning;
	int16_t sourceID;
};

struct DSNN_memory {
	//connection between neurons
	simple2DBufferInt connection_map;
	simple2DBufferInt non_learning_connection_map;
	simple2DBufferInt connection_map_ei;
	simple2DBufferInt weight_map;
	simple2DBufferInt neighbor_count_map;
	simple2DBufferInt filtered_weight_map;
	simple2DBufferInt delta_weight_map_ex;
	simple2DBufferInt delta_weight_map_in;
	simple2DBufferInt synapse_map_type;
	simple2DBufferInt synapse_map_cam_no;
	simple2DBufferInt synapse_map_sram_no;
	simple2DBufferInt post_neuron_activity_record;
	simple2DBufferInt post_neuron_taken_record; //Problem of the chip: inhibition is not strong enough
	simple2DBufferInt learned_post_synaptic_neuron;

	//for saving connectivity
	simple2DBufferInt virtual_neuron_addr;
	simple2DBufferInt virtual_neuron_addr_enable;
	simple2DBufferInt non_learning_synapse_map_type;

	//CAM memory
	simple2DBufferInt cam_map;
	simple2DBufferInt cam_map_source_id;
//	simple2DBufferInt cam_map_size;

	//SRAM memory
	simple2DBufferInt sram_map;
	simple2DBufferInt sram_map_content;

	//spike queue
	simple2DBufferLong spike_fifo;
	uint64_t spike_cnt;
	uint64_t start_rd_pointer;
	uint64_t wr_pointer;

	//second spike queue
	simple2DBufferLong spike_fifo_check;
	uint64_t start_rd_pointer_check;
	uint64_t wr_pointer_check;

	//third spike queue
	simple2DBufferLong spike_fifo_nsm;
	uint64_t start_rd_pointer_nsm;
	uint64_t wr_pointer_nsm;

	//fourth spike queue
	simple2DBufferLong spike_fifo_feature;
	uint64_t start_rd_pointer_feature;
	uint64_t wr_pointer_feature;

	simple2DBufferLong spike_fifo_output;
	uint64_t start_rd_pointer_output;
	uint64_t wr_pointer_output;

	simple2DBufferLong 	spike_fifo_output_firing_check;
	uint64_t start_rd_pointer_output_firing_check;
	uint64_t wr_pointer_output_firing_check;

	//learning algorithm
	uint64_t package_spike_counter;
	uint64_t pre_rd_pointer_old;
};

typedef struct DSNN_state *DSNNState;
typedef struct DSNN_memory DSNNMemory;
static DSNNMemory memory;

struct check_return {
	int64_t feature_neurons_num;
	int64_t feature_neurons_original_num;
};

static uint32_t bits_chip_U0[DYNAPSE_MAX_USER_USB_PACKET_SIZE];
static uint32_t bits_chip_U1[DYNAPSE_MAX_USER_USB_PACKET_SIZE];
static uint32_t bits_chip_U2[DYNAPSE_MAX_USER_USB_PACKET_SIZE];
static uint32_t bits_chip_U3[DYNAPSE_MAX_USER_USB_PACKET_SIZE];
static int num_config_chip_U0 = 0;
static int num_config_chip_U1 = 0;
static int num_config_chip_U2 = 0;
static int num_config_chip_U3 = 0;

static int8_t filtered_input_ready = 1;

static int usb_packet_maximum_size = USB_PACKET_MAXIMUM_SIZE_INITIALIZATION;

//static int8_t nsm_winner_ready = 0;
//static int64_t nsm_winner_id = 255;
//static int64_t nsm_winner_spikes_num = 0;

static int64_t learned_object_num = 0;

static int64_t last_spike_num = 0;
static uint64_t last_wr_pointer = 0;

static int8_t not_ready_added = 1;

static int32_t micro_saccade_finished = 1;

static int8_t output_neuron_firing = 1;

//static int64_t spike_num = 0;

static void setBiasBitsDSNN(caerModuleData moduleData, uint32_t chip_id, uint32_t core_id, const char *biasName,
	uint8_t coarseValue, uint16_t fineValue, const char *lowHigh, const char *npBias);
static uint32_t getWriteCamSramChipIdDSNN(uint32_t neuron_addr);
static void configureChipDSNN(caerModuleData moduleData, int8_t chip_id);
static void initializeMemory(void);
//static int binary_conversion(int64_t num);
static int64_t max(int64_t num1, int64_t num2);
static int64_t min(int64_t num1, int64_t num2);

void setBiasBitsDSNN(caerModuleData moduleData, uint32_t chip_id, uint32_t core_id, const char *biasName,
	uint8_t coarseValue, uint16_t fineValue, const char *lowHigh, const char *npBias) {
	//configure one bias on chip
	DSNNState state = moduleData->moduleState;
	int a = (int) strlen(lowHigh);
	a = a + 1;
	int b = (int) strlen(npBias);
	b = b + 1;
	caerDynapseSetBiasCore(state->eventSourceConfigNode, (uint8_t) chip_id, (uint8_t) core_id, biasName, coarseValue, (uint8_t) fineValue, true);
}


uint32_t getWriteCamSramChipIdDSNN(uint32_t neuron_addr) {
	//get chip id based on post neuron address
	uint32_t chip_id_t, chip_id;
	chip_id_t = (neuron_addr & NEURON_CHIPID_BITS) >> NEURON_CHIPID_SHIFT;
	if (chip_id_t == 1)
		chip_id = DYNAPSE_CONFIG_DYNAPSE_U0;
	else if (chip_id_t == 2)
		chip_id = DYNAPSE_CONFIG_DYNAPSE_U1;
	else if (chip_id_t == 3)
		chip_id = DYNAPSE_CONFIG_DYNAPSE_U2;
	else if (chip_id_t == 4)
		chip_id = DYNAPSE_CONFIG_DYNAPSE_U3;
	return (chip_id);
}

void configureChipDSNN(caerModuleData moduleData, int8_t chip_id) {
	//configure the connectivity on chip
	DSNNState state = moduleData->moduleState;
	if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U0 && num_config_chip_U0 > 0) {
		caerDeviceConfigSet(state->eventSourceModuleState, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, DYNAPSE_CONFIG_DYNAPSE_U0);
		if (!caerDynapseSendDataToUSB(state->eventSourceModuleState, bits_chip_U0, (size_t) num_config_chip_U0))
			caerLog(CAER_LOG_ERROR, moduleData->moduleSubSystemString, "USB transfer failed");
		num_config_chip_U0 = 0;
	} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U1 && num_config_chip_U1 > 0) {
		caerDeviceConfigSet(state->eventSourceModuleState, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, DYNAPSE_CONFIG_DYNAPSE_U1);
		if (!caerDynapseSendDataToUSB(state->eventSourceModuleState, bits_chip_U1, (size_t) num_config_chip_U1))
			caerLog(CAER_LOG_ERROR, moduleData->moduleSubSystemString, "USB transfer failed");
		num_config_chip_U1 = 0;
	} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U2 && num_config_chip_U2 > 0) {
		caerDeviceConfigSet(state->eventSourceModuleState, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, DYNAPSE_CONFIG_DYNAPSE_U2);
		if (!caerDynapseSendDataToUSB(state->eventSourceModuleState, bits_chip_U2, (size_t) num_config_chip_U2))
			caerLog(CAER_LOG_ERROR, moduleData->moduleSubSystemString, "USB transfer failed");
		num_config_chip_U2 = 0;
	} else if (chip_id == DYNAPSE_CONFIG_DYNAPSE_U3 && num_config_chip_U3 > 0) {
		caerDeviceConfigSet(state->eventSourceModuleState, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, DYNAPSE_CONFIG_DYNAPSE_U3);
		if (!caerDynapseSendDataToUSB(state->eventSourceModuleState, bits_chip_U3, (size_t) num_config_chip_U3))
			caerLog(CAER_LOG_ERROR, moduleData->moduleSubSystemString, "USB transfer failed");
		num_config_chip_U3 = 0;
	}
}

void initializeMemory(void) {
	memory.connection_map = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.wr_pointer = 0;
	//spike queue
	memory.spike_fifo = simple2DBufferInitLong((size_t) SPIKE_QUEUE_LENGTH, (size_t) SPIKE_QUEUE_WIDTH);
	//second spike queue
	memory.spike_fifo_check = simple2DBufferInitLong((size_t) SPIKE_QUEUE_LENGTH, (size_t) SPIKE_QUEUE_WIDTH);
	//third spike queue
	memory.spike_fifo_nsm = simple2DBufferInitLong((size_t) SPIKE_QUEUE_LENGTH, (size_t) SPIKE_QUEUE_WIDTH);
	//fourth spike queue
	memory.spike_fifo_feature = simple2DBufferInitLong((size_t) SPIKE_QUEUE_LENGTH, (size_t) SPIKE_QUEUE_WIDTH);

	memory.spike_fifo_output = simple2DBufferInitLong((size_t) SPIKE_QUEUE_LENGTH, (size_t) SPIKE_QUEUE_WIDTH);

	memory.spike_fifo_output_firing_check = simple2DBufferInitLong((size_t) SPIKE_QUEUE_LENGTH, (size_t) SPIKE_QUEUE_WIDTH);

	//connection between neurons
	memory.connection_map = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.non_learning_connection_map = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.connection_map_ei = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.weight_map = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.neighbor_count_map = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.filtered_weight_map = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.delta_weight_map_ex = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.delta_weight_map_in = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.synapse_map_type = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.synapse_map_cam_no = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.synapse_map_sram_no = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);

	memory.virtual_neuron_addr = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.virtual_neuron_addr_enable = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);
	memory.non_learning_synapse_map_type = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_NEURON_NUM_ON_BOARD);

	//CAM memory
	memory.cam_map = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_CAM_NUM); //CAM is taken or not
	memory.cam_map_source_id = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_CAM_NUM);

	//SRAM memory
	memory.sram_map = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_SRAM_NUM); //SRAM is taken or not
	memory.sram_map_content = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) TOTAL_SRAM_NUM);

	//record synapse activity for each trial
	memory.post_neuron_activity_record = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) POST_NEURON_ACTIVITY_SIZE_WIDTH);
	memory.post_neuron_taken_record = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) POST_NEURON_TAKEN_SIZE_WIDTH);

	memory.learned_post_synaptic_neuron = simple2DBufferInitInt((size_t) TOTAL_NEURON_NUM_ON_BOARD, (size_t) 1);
}

int64_t max(int64_t num1, int64_t num2) {
    return ((num1 > num2 ) ? num1 : num2);
}

int64_t min(int64_t num1, int64_t num2) {
    return ((num1 > num2 ) ? num2 : num1);
}
