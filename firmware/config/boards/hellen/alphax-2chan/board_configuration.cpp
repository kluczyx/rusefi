/**
 * @file board_configuration.cpp
 *
 *
 * @brief Configuration defaults for the 2chan board
 *
 * @author andreika <prometheus.pcb@gmail.com>
 * @author Andrey Belomutskiy, (c) 2012-2020
 */

#include "pch.h"
#include "hellen_meta.h"
#include "defaults.h"

static OutputPin alphaTachPullUp;
static OutputPin alphaTempPullUp;
static OutputPin alphaCrankPPullUp;
static OutputPin alphaCrankNPullUp;
static OutputPin alpha2stepPullDown;
static OutputPin alphaCamPullDown;

static void setInjectorPins() {
	engineConfiguration->injectionPins[0] = Gpio::H144_LS_1;
	engineConfiguration->injectionPins[1] = Gpio::H144_LS_2;
	engineConfiguration->injectionPins[2] = Gpio::Unassigned;
	engineConfiguration->injectionPins[3] = Gpio::Unassigned;

	engineConfiguration->clutchDownPin = Gpio::Unassigned;
	engineConfiguration->clutchDownPinMode = PI_PULLDOWN;
	engineConfiguration->launchActivationMode = CLUTCH_INPUT_LAUNCH;
	engineConfiguration->malfunctionIndicatorPin = Gpio::Unassigned;
}

static void setIgnitionPins() {
	engineConfiguration->ignitionPins[0] = Gpio::H144_IGN_1;
	engineConfiguration->ignitionPins[1] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[2] = Gpio::H144_IGN_2;
	engineConfiguration->ignitionPins[3] = Gpio::Unassigned;
}

static void setupVbatt() {
	// 4.7k high side/4.7k low side = 2.0 ratio divider
	engineConfiguration->analogInputDividerCoefficient = 2.0f;

	// set vbatt_divider 5.835
	// 33k / 6.8k
	engineConfiguration->vbattDividerCoeff = (33 + 6.8) / 6.8; // 5.835

	engineConfiguration->vbattAdcChannel = H144_IN_VBATT;

	engineConfiguration->adcVcc = 3.29f;
}

static void setupDefaultSensorInputs() {
	// trigger inputs, hall
	engineConfiguration->triggerInputPins[0] = Gpio::H144_IN_CRANK;
	engineConfiguration->triggerInputPins[1] = Gpio::H144_IN_CAM;
	engineConfiguration->camInputs[0] = Gpio::Unassigned;

	engineConfiguration->tps1_1AdcChannel = H144_IN_TPS;

	engineConfiguration->mafAdcChannel = EFI_ADC_NONE;

	engineConfiguration->afr.hwChannel = EFI_ADC_1;

	engineConfiguration->clt.adcChannel = H144_IN_CLT;

	engineConfiguration->iat.adcChannel = H144_IN_IAT;
}

void boardInitHardware() {

	alphaTachPullUp.initPin("a-tach", Gpio::H144_OUT_IO1);
	alphaTempPullUp.initPin("a-temp", Gpio::H144_OUT_IO4);
	alphaCrankPPullUp.initPin("a-crank-p", Gpio::H144_OUT_IO2);
	alphaCrankNPullUp.initPin("a-crank-n", Gpio::H144_OUT_IO5);
	alpha2stepPullDown.initPin("a-2step", Gpio::H144_OUT_IO7);
	alphaCamPullDown.initPin("a-cam", Gpio::H144_OUT_IO8);
	boardOnConfigurationChange(nullptr);
}

void boardOnConfigurationChange(engine_configuration_s * /*previousConfiguration*/) {
	alphaTachPullUp.setValue(engineConfiguration->boardUseTachPullUp);
	alphaTempPullUp.setValue(engineConfiguration->boardUseTempPullUp);
	alphaCrankPPullUp.setValue(engineConfiguration->boardUseCrankPullUp);
	alphaCrankNPullUp.setValue(engineConfiguration->boardUseCrankPullUp);
	alpha2stepPullDown.setValue(engineConfiguration->boardUse2stepPullDown);
	alphaCamPullDown.setValue(engineConfiguration->boardUseCamPullDown);
}

#include "hellen_leds_144.cpp"

static bool isMegaModuleRevision() {
    int16_t hellenBoardId = engine->engineState.hellenBoardId;
    return hellenBoardId != BOARD_ID_ALPHA2CH_B && hellenBoardId != BOARD_ID_ALPHA2CH_C && hellenBoardId != BOARD_ID_ALPHA2CH_D;
}

void setBoardConfigOverrides() {
	setupVbatt();
    int16_t hellenBoardId = engine->engineState.hellenBoardId;

	// rev.D uses SPI1 pins for CAN2, but rev.E and later uses mega-module meaning SPI1 for SD-card
	if (isMegaModuleRevision()) {
		setHellenSdCardSpi1();
		configureHellenMegaAccCS2Pin();
	    setHellenMegaEnPin();
	} else {
	    setHellenEnPin(Gpio::H144_OUT_IO3);
	}

	// todo: is it time for some helper method to work with sets?!
	bool isBeforeRevG = hellenBoardId == BOARD_ID_ALPHA2CH_B ||
	                    hellenBoardId == BOARD_ID_ALPHA2CH_C ||
	                    hellenBoardId == BOARD_ID_ALPHA2CH_D ||
	                    hellenBoardId == BOARD_ID_ALPHA2CH_E ||
	                    hellenBoardId == BOARD_ID_ALPHA2CH_F;

	if (isBeforeRevG) {
	    engineConfiguration->vrThreshold[0].pin = Gpio::H144_OUT_PWM6;
	} else {
	    engineConfiguration->vrThreshold[0].pin = Gpio::Unassigned; // rev G started to use MAX9924
	}

    engineConfiguration->vrThreshold[1].pin = Gpio::Unassigned; // 2chan never had second VR
    setDefaultHellenAtPullUps();

	setHellenCan();
}

/**
 * @brief   Board-specific configuration defaults.
 *
 * See also setDefaultEngineConfiguration
 *
 * @todo    Add your board-specific code, if any.
 */
void setBoardDefaultConfiguration() {
	setInjectorPins();
	setIgnitionPins();

	if (isMegaModuleRevision()) {
	    setHellenMMbaro();
	    engineConfiguration->map.sensor.hwChannel = H144_IN_MAP3; // On-board MAP
	    engineConfiguration->map.sensor.type = MT_MPXH6400;
	} else {
	    engineConfiguration->map.sensor.hwChannel = H144_IN_MAP2; // B2 external signal
	    engineConfiguration->baroSensor.type = MT_MPXH6400;
    	engineConfiguration->baroSensor.hwChannel = H144_IN_MAP3; // On-board MAP
	}

    engineConfiguration->boardUseTempPullUp = true;

	engineConfiguration->fuelPumpPin = Gpio::H144_OUT_PWM2;
	engineConfiguration->fanPin = Gpio::H144_OUT_PWM4;
    engineConfiguration->tachOutputPin = Gpio::H144_OUT_PWM3;

	// "required" hardware is done - set some reasonable defaults
	setupDefaultSensorInputs();

	setInline4();

	engineConfiguration->ignitionMode = IM_INDIVIDUAL_COILS; // IM_WASTED_SPARK

	engineConfiguration->launchActivationMode = CLUTCH_INPUT_LAUNCH;
// ?	engineConfiguration->malfunctionIndicatorPin = Gpio::G4; //1E - Check Engine Light
}

void boardPrepareForStop() {
	// Wake on the CAN RX pin
	palEnableLineEvent(PAL_LINE(GPIOD, 0), PAL_EVENT_MODE_RISING_EDGE);
}

static Gpio OUTPUTS[] = {
		Gpio::H144_LS_1,
		Gpio::H144_LS_2,
};

int getBoardMetaOutputsCount() {
    return efi::size(OUTPUTS);
}

Gpio* getBoardMetaOutputs() {
    return OUTPUTS;
}

