BOARDCPPSRC = $(BOARD_DIR)/board_configuration.cpp

DDEFS += -DFIRMWARE_ID=\"t-b-g\"
DDEFS += -DSTATIC_BOARD_ID=STATIC_BOARD_ID_TBG
SHORT_BOARD_NAME=t-b-g

DDEFS += -DHAL_USE_ADC=FALSE
DDEFS += -DHAL_USE_GPT=FALSE