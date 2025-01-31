// this section was generated automatically by rusEFI tool config_definition_base.jar based on (unknown script) controllers/trigger/trigger_state.txt Fri Oct 06 17:24:04 UTC 2023
// by class com.rusefi.output.CHeaderConsumer
// begin
#pragma once
#include "rusefi_types.h"
// start of trigger_state_s
struct trigger_state_s {
	/**
	 * sync: Crank sync counter
	 * Usually matches crank revolutions
	 * offset 0
	 */
	uint32_t crankSynchronizationCounter = (uint32_t)0;
	/**
	 * offset 4
	 */
	float vvtSyncGapRatio = (float)0;
	/**
	us
	 * offset 8
	 */
	uint32_t vvtToothDurations0 = (uint32_t)0;
	/**
	sync: Primary Cam Position
	 * offset 12
	 */
	float vvtCurrentPosition = (float)0;
	/**
	sync: Cam Tooth Position
	 * offset 16
	 */
	float vvtToothPosition[4];
	/**
	 * @@GAUGE_NAME_TRG_GAP@@
	 * offset 32
	 */
	float triggerSyncGapRatio = (float)0;
	/**
	 * offset 36
	 */
	uint8_t triggerStateIndex = (uint8_t)0;
	/**
	 * sync: Phase Re-Sync Counter
	 * offset 37
	 */
	uint8_t camResyncCounter = (uint8_t)0;
	/**
	 * offset 38
	 */
	uint8_t vvtStateIndex = (uint8_t)0;
	/**
	 * need 4 byte alignment
	units
	 * offset 39
	 */
	uint8_t alignmentFill_at_39[1];
};
static_assert(sizeof(trigger_state_s) == 40);

// end
// this section was generated automatically by rusEFI tool config_definition_base.jar based on (unknown script) controllers/trigger/trigger_state.txt Fri Oct 06 17:24:04 UTC 2023
