// this section was generated automatically by rusEFI tool config_definition_base.jar based on (unknown script) controllers/actuators/idle_state.txt Mon Sep 25 12:41:04 UTC 2023
// by class com.rusefi.output.CHeaderConsumer
// begin
#pragma once
#include "rusefi_types.h"
// start of idle_state_s
struct idle_state_s {
	/**
	 * offset 0
	 */
	idle_state_e idleState = (idle_state_e)0;
	/**
	 * "idle: current position
	 * that's current position with CLT and IAT corrections"
	 * offset 4
	 */
	percent_t currentIdlePosition = (percent_t)0;
	/**
	 * "idle: base value
	 * current position without adjustments (iacByTpsTaper, afterCrankingIACtaperDuration)"
	 * offset 8
	 */
	percent_t baseIdlePosition = (percent_t)0;
	/**
	 * idle: iacByTpsTaper portion
	 * offset 12
	 */
	percent_t iacByTpsTaper = (percent_t)0;
	/**
	 * idle: throttlePedalUpState
	 * true in IDLE throttle pedal state, false if driver is touching the pedal
	 * todo: better name for this field?
	 * offset 16
	 */
	int throttlePedalUpState = (int)0;
	/**
	 * idle: mightResetPid
	 * The idea of 'mightResetPid' is to reset PID only once - each time when TPS > idlePidDeactivationTpsThreshold.
	 * The throttle pedal can be pressed for a long time, making the PID data obsolete (thus the reset is required).
	 * We set 'mightResetPid' to true only if PID was actually used (i.e. idlePid.getOutput() was called) to save some CPU resources.
	 * See automaticIdleController().
	offset 20 bit 0 */
	bool mightResetPid : 1 {};
	/**
	 * Idle: shouldResetPid
	offset 20 bit 1 */
	bool shouldResetPid : 1 {};
	/**
	 * Idle: wasResetPid
	 * This is needed to slowly turn on the PID back after it was reset.
	offset 20 bit 2 */
	bool wasResetPid : 1 {};
	/**
	 * Idle: mustResetPid
	 * This is used when the PID configuration is changed, to guarantee the reset
	offset 20 bit 3 */
	bool mustResetPid : 1 {};
	/**
	 * Idle: cranking
	offset 20 bit 4 */
	bool isCranking : 1 {};
	/**
	offset 20 bit 5 */
	bool isIacTableForCoasting : 1 {};
	/**
	offset 20 bit 6 */
	bool notIdling : 1 {};
	/**
	 * Idle: reset
	offset 20 bit 7 */
	bool needReset : 1 {};
	/**
	 * Idle: dead zone
	offset 20 bit 8 */
	bool isInDeadZone : 1 {};
	/**
	offset 20 bit 9 */
	bool isBlipping : 1 {};
	/**
	offset 20 bit 10 */
	bool useClosedLoop : 1 {};
	/**
	offset 20 bit 11 */
	bool badTps : 1 {};
	/**
	offset 20 bit 12 */
	bool looksLikeRunning : 1 {};
	/**
	offset 20 bit 13 */
	bool looksLikeCoasting : 1 {};
	/**
	offset 20 bit 14 */
	bool looksLikeCrankToIdle : 1 {};
	/**
	 * Idle: coasting
	offset 20 bit 15 */
	bool isIdleCoasting : 1 {};
	/**
	offset 20 bit 16 */
	bool unusedBit_21_16 : 1 {};
	/**
	offset 20 bit 17 */
	bool unusedBit_21_17 : 1 {};
	/**
	offset 20 bit 18 */
	bool unusedBit_21_18 : 1 {};
	/**
	offset 20 bit 19 */
	bool unusedBit_21_19 : 1 {};
	/**
	offset 20 bit 20 */
	bool unusedBit_21_20 : 1 {};
	/**
	offset 20 bit 21 */
	bool unusedBit_21_21 : 1 {};
	/**
	offset 20 bit 22 */
	bool unusedBit_21_22 : 1 {};
	/**
	offset 20 bit 23 */
	bool unusedBit_21_23 : 1 {};
	/**
	offset 20 bit 24 */
	bool unusedBit_21_24 : 1 {};
	/**
	offset 20 bit 25 */
	bool unusedBit_21_25 : 1 {};
	/**
	offset 20 bit 26 */
	bool unusedBit_21_26 : 1 {};
	/**
	offset 20 bit 27 */
	bool unusedBit_21_27 : 1 {};
	/**
	offset 20 bit 28 */
	bool unusedBit_21_28 : 1 {};
	/**
	offset 20 bit 29 */
	bool unusedBit_21_29 : 1 {};
	/**
	offset 20 bit 30 */
	bool unusedBit_21_30 : 1 {};
	/**
	offset 20 bit 31 */
	bool unusedBit_21_31 : 1 {};
	/**
	 * idle: target by CLT
	 * offset 24
	 */
	int targetRpmByClt = (int)0;
	/**
	 * idle: A/C bump
	 * offset 28
	 */
	int targetRpmAcBump = (int)0;
	/**
	 * idle: iacByRpmTaper portion
	 * offset 32
	 */
	percent_t iacByRpmTaper = (percent_t)0;
	/**
	 * idle: Lua Adder
	 * offset 36
	 */
	percent_t luaAdd = (percent_t)0;
};
static_assert(sizeof(idle_state_s) == 40);

// end
// this section was generated automatically by rusEFI tool config_definition_base.jar based on (unknown script) controllers/actuators/idle_state.txt Mon Sep 25 12:41:04 UTC 2023
