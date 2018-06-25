#ifndef NSMFILTER_H_
#define NSMFILTER_H_

#define LOAD_PREVIOUS_CONNECTIVITY 0 //0: start a new learning; 1: load learned connectivity
#define DAVIS_INPUT 1 //1: receive input events from DAVIS
#define ENABLE_OUTPUT_TO_ROLLS 0 //1: send output events to ROLLS
#define RECORD_OUTPUT_EVENTS 0 //1: record the events of the input/output layer into a file

#define CONNECTIVITY_NUM 50000
#define PATTERN_PERIOD_TESTING 2
#define INTERVAL_OF_PATTERN_PERIOD_TESTING 1

#define TRAINING_OBJECT_NUM 4
#define ARTIFICIAL_WINNERS_NUM TRAINING_OBJECT_NUM
#define KERNEL_EDGE 8

#define MAXIMUM_RECORDED_EVENTS_PER_OBJECT 20000

#define SILENCE_CHECKING_PERIOD 20 //50 //ms
#define OUPUT_NEURON_FIRING_CHECK_PERIOD 50 //ms
#define CONSIDERING_PERIOD 50 //100 //20 //100 //ms
#define CONSIDERING_PERIOD_CHECK 500 //50 //200 //250 //ms

#define SILENCE_CHECKING_SPIKES_THRESHOULD 100
#define REFRACTORY_PERIOD 10

#define CONSIDERED_SPIKES_THRESHOULD 80
#define NUM_SPIKES_THRESHOULD 2

#define CHECK_STABILITY_PERIOD (1000 * 5) //not important

#define CONSIDERED_SPIKES_THRESHOULD_CHECK 0
#define NUM_SPIKES_THRESHOULD_CHECK 5


#define SPIKE_REDUCED_NUM 4 //40

#define WEIGHT_THRESHOULD 0 //2 //40

#define LEARNED_PIXELS_THRESHOLD 16 //*2 //*2
#define FEATURE_NEURONS_NUM_THRESHOLD 8 //* 2

#define NSM_WINNER_SPIKES_NUM_THRESHOULD 10

//for learning algorithm
#define EX_IN_BALANCE_THRESHOLD_L 0
#define EX_IN_BALANCE_THRESHOLD_H 160
#define EX_FS_THRESHOLD 40
#define IN_FS_THRESHOLD -40

#define REPLACE_TAG 1

//for USB packet
#define USB_PACKET_MAXIMUM_SIZE_INITIALIZATION 1024 //1366
#define USB_PACKET_MAXIMUM_SIZE_LEARNING 1024 //1366

//parameter determined by the main loop
#define EVENTSOURCEID 1

//spike queue parameters
#define SPIKE_QUEUE_LENGTH 10000000
#define SPIKE_QUEUE_WIDTH 2
#define DYNAPSE_CONFIG_DYNAPSE_U0_SPECIAL 1

//learning algorithm parameters
#define MAXIMUM_CONSIDERED_SPIKE_INTERVAL 80
#define MINIMUM_CONSIDERED_SPIKE_INTERVAL 0
#define MAXIMUM_CONSIDERED_SPIKE_NUM 100000
#define MINIMUM_CONSIDERED_SPIKE_NUM 100

//memory offset for neuron addresses because the chip ID starts from 1
#define MEMORY_NEURON_ADDR_OFFSET 1024

//chip parameters
#define TOTAL_NEURON_NUM_IN_CORE 256
#define DYNAPSE_CORE_SIZE_X 16
#define DYNAPSE_CORE_SIZE_Y 16
#define TOTAL_NEURON_NUM_ON_CHIP 1024
#define TOTAL_NEURON_NUM_ON_CHIP_X 32
#define TOTAL_NEURON_NUM_ON_CHIP_Y 32
#define TOTAL_NEURON_NUM_ON_CORE_X 16
#define TOTAL_NEURON_NUM_ON_CORE_Y 16
#define TOTAL_NEURON_NUM_ON_BOARD (TOTAL_NEURON_NUM_ON_CHIP * 4)

//total CAM number and available CAM number for learning
#define FIRST_CAM_ID 0
#define LAST_CAM_ID 63
#define LAST_CAM_ID_OUTPUT_NEURON 60
#define NON_PROTECTED_LAST_CAM_ID 62
#define PROTECTED_FIRST_CAM_ID 63
#define TOTAL_CAM_NUM 64

//total SRAM number
#define TOTAL_SRAM_NUM 4

//synapse type for initializing the network connectivity
#define VIRTUAL_SYNAPSE 0
#define REAL_SYNAPSE 1
#define REAL_SYNAPSE_WITH_LEARNING 1
#define EXTERNAL_REAL_SYNAPSE 2
#define REAL_SYNAPSE_WITHOUT_LEARNING 3
#define VIRTUAL_SYNAPSE_WITHOUT_SRAM 4
#define REAL_SYNAPSE_WITHOUT_CAM_CONNECTED 5

//chip & core ID in standard neuron address format
#define VIRTUAL_CHIP_ID 0
#define CHIP_UP_LEFT_ID 1
#define CHIP_UP_RIGHT_ID 2
#define CHIP_DOWN_LEFT_ID 3
#define CHIP_DOWN_RIGHT_ID 4
#define CHIP_EXTRA_ID 5

#define CORE_UP_LEFT_ID 0
#define CORE_UP_RIGHT_ID 1
#define CORE_DOWN_LEFT_ID 2
#define CORE_DOWN_RIGHT_ID 3

//layer size
#define INPUT_LAYER_EI_L 16
#define INPUT_LAYER_EI_W 16

#define FEATURE_LAYER_EI_L 16
#define FEATURE_LAYER_EI_W 16

#define COLUMN_X_0_EI_L 1
#define COLUMN_X_0_EI_W 1
#define COLUMN_X_1_EI_L 3
#define COLUMN_X_1_EI_W 3
#define COLUMN_X_2_EI_L 5
#define COLUMN_X_2_EI_W 5
#define COLUMN_X_3_EI_L 7
#define COLUMN_X_3_EI_W 7

#define COLUMN_OUTPUT_EI_L 4
#define COLUMN_OUTPUT_EI_W 4

#define OUTPUT_POPULATION_EI_L 1
#define OUTPUT_POPULATION_EI_W 4
#define OUTPUT_POPULATION_EI_SIZE 4

#define NSM_L 1
#define NSM_W 4
#define NSM_SIZE 4

#define MOTOR_L 2
#define MOTOR_W 2

#define HUB_L 2
#define HUB_W 2

#define LEARNING_L 2
#define LEARNING_W 2

#define ARBITRATION_L 2
#define ARBITRATION_W 2

//memory size
#define CAM_MAP_SIZE_WIDTH 1
#define POST_NEURON_ACTIVITY_SIZE_WIDTH 1
#define POST_NEURON_TAKEN_SIZE_WIDTH 1

//for encoding the chip input commands
#define CXQ_PROGRAM  (0x80 << 10)

#define CXQ_ADDR_SHIFT 20
#define CXQ_SOURCE_CORE_SHIFT 18

#define CXQ_PROGRAM_COREID_SHIFT 15
#define CXQ_PROGRAM_ROW_SHIFT 5
#define CXQ_PROGRAM_COLUMN_SHIFT 0

#define CXQ_SRAM_VIRTUAL_SOURCE_CORE_SHIFT 28
#define CXQ_SRAM_SY_SHIFT 27
#define CXQ_SRAM_DY_SHIFT 25
#define CXQ_SRAM_SX_SHIFT 24
#define CXQ_SRAM_DX_SHIFT 22
#define CXQ_SRAM_DEST_CORE_SHIFT 18

#define CXQ_CAM_EI_SHIFT 29
#define CXQ_CAM_FS_SHIFT 28

//chip core neuron ID bits and shift for configuration command
#define NEURON_ADDRESS_BITS 0xff
#define NEURON_NEURONID_BITS 0xff
#define NEURON_COREID_BITS 0x300
#define NEURON_CHIPID_BITS 0x3c00
#define NEURON_ROWID_BITS 0xf0
#define NEURON_COLID_BITS 0xf

#define NEURON_CHIPID_SHIFT 10
#define NEURON_COREID_SHIFT 8
#define NEURON_NEURONID_SHIFT 0
#define NEURON_ROWID_SHIFT 4
#define NEURON_COLID_SHIFT 0

#define CAM_NEURON_ROW_SHIFT 6

//chip core ID bits and shift for SRAM memory
#define CHIPCOREID_CHIPID_SHIFT 6
#define DESTINATION_COREID_BITS 0xf
#define CHIPCOREID_SOURCECOREID_BITS 0x30
#define CHIPCOREID_SOURCECOREID_SHIFT 4

//SRAM address coding
#define SRAM_NEURON_ROW_SHIFT 6
#define SRAM_NEURON_COL_SHIFT 2
#define SRAM_COL_VALUE 16

//synapses ID and values
#define FAST_EX_SYNAPSE_VALUE 2
#define SLOW_EX_SYNAPSE_VALUE 1
#define FAST_IN_SYNAPSE_VALUE (-2)
#define SLOW_IN_SYNAPSE_VALUE (-1)

#define FAST_SYNAPSE_VALUE 2
#define SLOW_SYNAPSE_VALUE 1
#define FAST_SYNAPSE_ID 1
#define SLOW_SYNAPSE_ID 0
#define EXCITATORY_SYNAPSE_ID 1
#define INHIBITORY_SYNAPSE_ID 0

#define NO_SYNAPSE_ID 0
#define NO_SYNAPSE_ADDRESS 0xff
#define NO_SYNAPSE_CORE 0x3

#define EXCITATORY_SYNAPSE_SIGN 1
#define EXCITATORY_FAST_SYNAPSE_ID (EXCITATORY_SYNAPSE_SIGN * FAST_SYNAPSE_ID)
#define EXCITATORY_SLOW_SYNAPSE_ID (EXCITATORY_SYNAPSE_SIGN * SLOW_SYNAPSE_ID)

//synapse bits and shift
#define SYNAPSE_EI_TYPE_BITS 1
#define SYNAPSE_FS_TYPE_BITS 1
#define SYNAPSE_EI_TYPE_SHIFT 1
#define SYNAPSE_FS_TYPE_SHIFT 0

//board size
#define BOARD_CHIPS_Y_NUM 2
#define BOARD_CHIPS_X_NUM 2

//event routing directions
#define EVENT_DIRECTION_Y_UP 0
#define EVENT_DIRECTION_Y_DOWN 1
#define EVENT_DIRECTION_X_RIGHT 0
#define EVENT_DIRECTION_X_LEFT 1

#define DYNAPSE_MAX_USER_USB_PACKET_SIZE 1024

#include "main.h"

#include <libcaer/events/spike.h>
#include <libcaer/events/frame.h> //for the display

void caerDSNN(uint16_t moduleID, caerSpikeEventPacket spike);

#endif /* LEARNINGFILTER_H_ */
