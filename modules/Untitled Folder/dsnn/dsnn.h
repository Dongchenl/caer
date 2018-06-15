/*
 * Created on: Feb. 2016
 * Author: dongchen@ini.uzh.ch
 */

#ifndef NSMFILTER_H_
#define NSMFILTER_H_

#define LOAD_PREVIOUS_CONNECTIVITY 0 //1 //0 //0 //1 //0 //0 //0 //0 //1 //0
#define DAVIS_INPUT 1 //0 //1 //0
#define ENABLE_OUTPUT_TO_ROLLS 0 //1 //0 //1 //0 //1 //1 //0 //1 //0 //1 //0 //1 //0 //1// 0 //
#define RECORD_OUTPUT_EVENTS 0 //1 //0 //1 //0 //1 //0 //1 //0 //

//#define LOAD_HALF_PREVIOUS_CONNECTIVITY 0 //1 //1 //0 //1
//#define INPUT_NUM 2 //3 //2 //3 //2 //8 //10 //8 //4 //5
#define CONNECTIVITY_NUM 50000 //30000 //12958 //14393 //12958 //27352
#define PATTERN_PERIOD_TESTING 2 //1 //3 //1 //100000 almost //50000 us almost //100000 yes //0 s no //1 yes //1 //3
#define INTERVAL_OF_PATTERN_PERIOD_TESTING 1 //100000 almost //50000 us almost //100000 yes //1 s no //0 yes //1 //1

#define TRAINING_OBJECT_NUM 4
#define ARTIFICIAL_WINNERS_NUM TRAINING_OBJECT_NUM //4 //1 //4
#define KERNEL_EDGE 8 //6 //8

#define MAXIMUM_RECORDED_EVENTS_PER_OBJECT 20000 //1000 //20000
/*
The best when the input layer is not right
#define SILENCE_CHECKING_PERIOD 5 //10
#define SILENCE_CHECKING_SPIKES_THRESHOULD 500 //100 //500 //100

#define CONSIDERING_PERIOD 5 //10 //50 //1000 //500 //2000 //500 //100 //5 //10 //10 //50
#define CONSIDERING_PERIOD_CHECK 50 //5
#define REFRACTORY_PERIOD 100 //1000 //10 //10 //50
#define CHECK_STABILITY_PERIOD 1000 // * 2
#define CONSIDERED_SPIKES_THRESHOULD 100 //500 //1000 //2000 //200
#define CONSIDERED_SPIKES_THRESHOULD_CHECK 0
#define NUM_SPIKES_THRESHOULD 10 //50 //10 //50 //10 //50 //500 //40 //8
#define NUM_SPIKES_THRESHOULD_CHECK 5 //2 //10
*/

/************************************************************/
//important
/*
#define SILENCE_CHECKING_PERIOD 5
#define SILENCE_CHECKING_SPIKES_THRESHOULD 500 //1000 * 2
#define REFRACTORY_PERIOD 0 //100

#define CONSIDERING_PERIOD 60 //100 //50 //30 // 2 //20
#define CONSIDERED_SPIKES_THRESHOULD 100
#define NUM_SPIKES_THRESHOULD 10 //20 //50 //10
*/

#define SILENCE_CHECKING_PERIOD 5
#define SILENCE_CHECKING_SPIKES_THRESHOULD 150 //100 //200 //500 //1000
#define REFRACTORY_PERIOD 0 //100 //100

#define CONSIDERING_PERIOD 100 //60 //50 //80 //60 //50 //30 //20
#define CONSIDERED_SPIKES_THRESHOULD 80 //100
#define NUM_SPIKES_THRESHOULD 10 //20 //50 //50 //10
/************************************************************/
//not important
#define CHECK_STABILITY_PERIOD 1000 //10000 //5000 //2000 //5000

#define CONSIDERING_PERIOD_CHECK 50
#define CONSIDERED_SPIKES_THRESHOULD_CHECK 0
#define NUM_SPIKES_THRESHOULD_CHECK 5
/************************************************************/

#define SPIKE_REDUCED_NUM 40

#define LEARNED_PIXELS_THRESHOLD 16 //* 2 //*2
#define FEATURE_NEURONS_NUM_THRESHOLD 8 //* 2

#define NSM_WINNER_SPIKES_NUM_THRESHOULD 10

//for constructing layers
#define NON_LEARNING_LAYER0_N 256
#define LEARNING_LAYER0_N 256
#define NON_LEARNING_LAYER1_N 256
#define LEARNING_LAYER1_N 256
#define NON_LEARNING_LAYER2_N 256
#define LEARNING_LAYER2_N 64
#define NON_LEARNING_LAYER3_N 8

//for learning algorithm
#define EX_IN_BALANCE_THRESHOLD_L 0
#define EX_IN_BALANCE_THRESHOLD_H 160 //140 //160 //80
#define EX_FS_THRESHOLD 40 //40
#define IN_FS_THRESHOLD -40 //0 //0

#define NEURON_LOW_HIGH_ACTIVITY_THRESHOLD 140 //1000

#define WEIGHT_IN_TOTAL 200 //120 //1010 //1000

#define WEIGHT_EX_UP_THRESHOLD 160 //80 //60 fine //40 //20 //60 //200 //100 //2 //100 //100
#define WEIGHT_IN_UP_THRESHOLD -200 //-200 //-100 //-2 //100 //100
#define ROUNDED_WEIGHT_EX_UP_THRESHOLD 2 //100 //100
#define ROUNDED_WEIGHT_IN_UP_THRESHOLD -2 //100 //100

#define PROBABILITY_PHASE1 0.1f //1 //0.1f //0.5f //0.5f
//#define PROBABILITY_PHASE2 0.1f //0.5f //0.1f //0.1f //0.5f //0.5f //0.2f //1 //0.1f //0.2f //1 //0.5f //0.1f //1 //0.01f //0.5f //(1/2) //1 //(1/2) //0.5 //0.5
#define PROBABILITY_INJECTING 0.05f
#define PALASTICITY_PROBABILITY 0.02f
#define OUTPUT_PROBABILITY 0.2f //0.02f

#define FORWARD_LEARNING_RATE 1
#define FORWARD_LEARNING_RATE_F1 1 //0.1 //10 //(1/2) //1 //5 //1
#define FORWARD_LEARNING_RATE_F2 0.1 //0.1 //10 //(1/2) //1 //5 //1
#define BACKWARD_LEARNING_RATE 1 //0.1 //1

#define REPLACE_TAG 1

//for USB packet
#define USB_PACKET_MAXIMUM_SIZE_INITIALIZATION 1024 //128 //1024 //1366
#define USB_PACKET_MAXIMUM_SIZE_LEARNING 1024 //1366 //2 //64 //1366 //16 is good //128   32 4 is not good

//period for one pattern
#define PATTERN_PERIOD_LEARNING_PHASE1 5 //2 //4 //2 // //6 //4 //12 //4 //6 //3 //6 //6 //3 //6 //3 //12
//#define PATTERN_PERIOD_LEARNING_PHASE2 3 //6 //3 //6 //6 //3 //12 //6 //12 //6 //3 //12
//#define PATTERN_PERIOD_TESTING 1 //1 //6 //3 //1
#define INTERVAL_OF_PATTERN_PERIOD_LEARNING 5 //2 //1 //2 //1 //4
//#define INTERVAL_OF_PATTERN_PERIOD_TESTING 0 //1
#define DELAY_PERIOD_OF_LEARNING 1 //2 //1 //4

//period for learning
#define PREPARE_EVENTS_PERIOD 10 //3 //1 //5 //5
#define PREPARE_ARRAY_PERIOD 10 //3 //1 //5 //5
#define TRAINING_ITERATIONS_NUM 1 //2 //6 //3
#define SELF_SUPERVISED_LEARING_PERIOD_PHASE1 ((PATTERN_PERIOD_LEARNING_PHASE1 + INTERVAL_OF_PATTERN_PERIOD_LEARNING)*INPUT_NUM) //10 //20 //10 //0 //((PATTERN_PERIOD_LEARNING_PHASE1 + INTERVAL_OF_PATTERN_PERIOD_LEARNING)*(INPUT_NUM+1)) //(10+1) //10*2 //*3*4 //100
#define UNSUPERVISED_LEARNING_PERIOD_PHASE1 0 //((PATTERN_PERIOD_LEARNING_PHASE1 + INTERVAL_OF_PATTERN_PERIOD_LEARNING)*(10+1)) //10*2 //*3*4 /100
//#define SELF_SUPERVISED_LEARING_PERIOD_PHASE2 ((PATTERN_PERIOD_LEARNING_PHASE2 + INTERVAL_OF_PATTERN_PERIOD_LEARNING)*4*4) //*3*4 //100
//#define UNSUPERVISED_LEARNING_PERIOD_PHASE2 ((PATTERN_PERIOD_LEARNING_PHASE2 + INTERVAL_OF_PATTERN_PERIOD_LEARNING)*4*4) //*3*4 /100

//parameter determined by the main loop
#define EVENTSOURCEID 1

//for visualizer
#define VMIN 0
#define VMAX 20
#define WHITE_EDGE_COLOR_VALUE 0.5f

//loop-up table parameters for synapse weight updating
#define DELTA_WEIGHT_LUT_LENGTH 80 //8000 //20000 //80 //800 //80
#define SYNAPSE_UPGRADE_THRESHOLD_LUT_LENGTH 128 //800 //80

//spike queue parameters
#define SPIKE_QUEUE_LENGTH 2000000 //200000 too short for a learning with 5 second events
#define SPIKE_QUEUE_WIDTH 2
#define DYNAPSE_CONFIG_DYNAPSE_U0_SPECIAL 1

//learning algorithm parameters
#define MAXIMUM_CONSIDERED_SPIKE_INTERVAL 80 //8000 //80 //10*1000 //80 //80 //1000 //200 //80 //???what is the unit of time stamps??? microsecond
#define MINIMUM_CONSIDERED_SPIKE_INTERVAL 0 //0 //2
#define MAXIMUM_CONSIDERED_SPIKE_NUM 100000 //10000 //200 //500 //50 //200 //100 //10
#define MINIMUM_CONSIDERED_SPIKE_NUM 100 //200 //500 //50 //200 //100 //10

//memory offset for neuron addresses
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

//chip & core ID in standard neuron address format
#define VIRTUAL_CHIP_ID 0
#define CHIP_UP_LEFT_ID 1
#define CHIP_UP_RIGHT_ID 2
#define CHIP_DOWN_LEFT_ID 3
#define CHIP_DOWN_RIGHT_ID 4
#define CHIP_EXTRA_ID 5

#define CORE_UP_LEFT_ID 0
#define CORE_UP_RIGHT_ID 1 //2
#define CORE_DOWN_LEFT_ID 2 //1
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

#define OUTPUT_LAYER_EI_L 16
#define OUTPUT_LAYER_EI_W 16

#define COLUMN_OUTPUT_EI_L 4
#define COLUMN_OUTPUT_EI_W 4

#define OUTPUT_POPULATION_EI_L 1 //OUTPUT_TO_ROLLS_EI_L 1
#define OUTPUT_POPULATION_EI_W 4 //OUTPUT_TO_ROLLS_EI_W 4
#define OUTPUT_POPULATION_EI_SIZE 4

#define NSM_L 1 //for a single state
#define NSM_W 4
#define NSM_SIZE 4

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
#define NO_SYNAPSE_ADDRESS 0xff //0
#define NO_SYNAPSE_CORE 0x3 //0

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
//#include "modules/ini/dynapse_common.h"

#include <libcaer/events/spike.h>
#include <libcaer/events/frame.h> //for display

void caerDSNN(uint16_t moduleID, caerSpikeEventPacket spike);

#endif /* LEARNINGFILTER_H_ */




