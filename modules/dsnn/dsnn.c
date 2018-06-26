#include "dsnn.h"
#include "basic.h"
#include "biases.h"
#include "encode_neuron.h"
#include "synapse.h"
#include "initialize.h"
#include "connect_retina.h"
#include "load_save.h"
#include "record.h"

#include "create_input.h"
#include "create_feature.h"
#include "create_output.h"
#include "create_wta.h"
#include "create_arbitrator.h"

#include "build_input.h"
#include "build_feature.h"
#include "build_output.h"
#include "build_wta.h"
#include "build_arbitrator.h"

#include "scale_up_down.h"
#include "learn_input.h"
#include "learn_output.h"
#include "learn_wta.h"
#include "motor.h"
#include "learn.h"

#include "events_output.h"
#include "reset.h"

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

#include <unistd.h>

static bool caerDSNNInit(caerModuleData moduleData);
static void caerDSNNRun(caerModuleData moduleData, caerEventPacketContainer in, caerEventPacketContainer *out);
static void caerDSNNConfig(caerModuleData moduleData);
static void caerDSNNExit(caerModuleData moduleData);
static void caerDSNNReset(caerModuleData moduleData, uint16_t resetCallSourceID);

static struct caer_module_functions caerDSNNFunctions = { .moduleInit =
	&caerDSNNInit, .moduleRun = &caerDSNNRun, .moduleConfig =
	&caerDSNNConfig, .moduleExit = &caerDSNNExit, .moduleReset =
	&caerDSNNReset };

static const struct caer_event_stream_in moduleInputs[] = {
    { .type = SPIKE_EVENT, .number = 1, .readOnly = true }
};

//static const struct caer_event_stream_out moduleOutputs[] = { { .type = FRAME_EVENT } };

static const struct caer_module_info moduleInfo = {
	.version = 1, .name = "DSNN",
	.description = "Deep spiking neural network",
	.type = CAER_MODULE_OUTPUT,
	.memSize = sizeof(struct DSNN_state),
	.functions = &caerDSNNFunctions,
	.inputStreams = moduleInputs,
	.inputStreamsSize = CAER_EVENT_STREAM_IN_SIZE(moduleInputs),
    .outputStreams = NULL,
    .outputStreamsSize = 0
};

caerModuleInfo caerModuleGetInfo(void) {
    return (&moduleInfo);
}

static bool caerDSNNInit(caerModuleData moduleData) {

	DSNNState state = moduleData->moduleState;

	int16_t *inputs = caerMainloopGetModuleInputIDs(moduleData->moduleID, NULL);
	if (inputs == NULL) {
		return (false);
	}

	int16_t sourceID = inputs[0];
	state->sourceID = sourceID;
	state->eventSourceConfigNode = caerMainloopGetSourceNode(sourceID);
	state->eventSourceModuleState = (caerDeviceHandle) caerMainloopGetSourceState(state->sourceID);

	free(inputs);

	sshsNodeCreateBool(moduleData->moduleNode, "learning", true, SSHS_FLAGS_NORMAL, "Start/Stop learning. ");

	sshsNodeAddAttributeListener(moduleData->moduleNode, moduleData, &caerModuleConfigDefaultListener);

	state->event_source_id = 0;

	return (true); // Nothing that can fail here.
}
static void caerDSNNConfig(caerModuleData moduleData) {
	caerModuleConfigUpdateReset(moduleData);
	DSNNState state = moduleData->moduleState;

	state->learning = sshsNodeGetBool(moduleData->moduleNode, "learning");
}
static void caerDSNNExit(caerModuleData moduleData) {
	sshsNodeRemoveAttributeListener(moduleData->moduleNode, moduleData, &caerModuleConfigDefaultListener);

	sshsNode sourceInfoNode = sshsGetRelativeNode(moduleData->moduleNode, "sourceInfo/");
	sshsNodeClearSubTree(sourceInfoNode,true);
}
static void caerDSNNReset(caerModuleData moduleData, uint16_t resetCallSourceID) {
	UNUSED_ARGUMENT(moduleData);
	UNUSED_ARGUMENT(resetCallSourceID);
}
static void caerDSNNRun(caerModuleData moduleData, caerEventPacketContainer in, caerEventPacketContainer *out) {


	DSNNState state = moduleData->moduleState;

	caerSpikeEventPacketConst spike = (caerSpikeEventPacketConst) caerEventPacketContainerFindEventPacketByTypeConst(in, SPIKE_EVENT);


	if (state->event_source_id == 0) {
		if (spike != NULL)
			state->event_source_id = (uint16_t) caerEventPacketHeaderGetEventSource(&spike->packetHeader);
		else
			state->event_source_id = EVENTSOURCEID;
	}


	if (memory.connection_map == NULL) {
		caerLog(CAER_LOG_NOTICE, moduleData->moduleSubSystemString, "Initialize module DSNN...");
		caerLog(CAER_LOG_NOTICE, moduleData->moduleSubSystemString, "Programming..");
		if (!resetNetworkDSNN(moduleData)) { // Failed to allocate memory, nothing to do.
			caerLog(CAER_LOG_ERROR, moduleData->moduleSubSystemString, "Failed to initialize the network.");
			return;
		}
		caerLog(CAER_LOG_NOTICE, moduleData->moduleSubSystemString, "Done");

	}
	caerDSNNConfig(moduleData); // Update parameters


	//triggered by one spike
	if(spike == NULL) {
		return;
	}

	if (load_previous_connectivity == 0) {
		if (learned_object_num < TRAINING_OBJECT_NUM) {
			learning(moduleData, spike);
		}
	}

	if (record_output_events == 1) {
		recordOutputEvents(spike);
	}

}
