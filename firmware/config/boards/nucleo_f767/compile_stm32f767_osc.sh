#!/bin/bash






# STM32F767 version of the firmware for F767ZI chip NOT on Nucleo board, with a real oscillator

export USE_FATFS=no

export EXTRA_PARAMS="-DSTM32F767xx \
 \
 \
 -DEFI_ENABLE_ASSERTS=FALSE \
 -DCH_DBG_ENABLE_CHECKS=FALSE -DCH_DBG_ENABLE_ASSERTS=FALSE -DCH_DBG_ENABLE_STACK_CHECK=FALSE -DCH_DBG_FILL_THREADS=FALSE -DCH_DBG_THREADS_PROFILING=FALSE"

bash ../common_make.sh nucleo_f767 ARCH_STM32F7

