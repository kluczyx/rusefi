/*
 * @file persistent_configuration.h
 *
 * @date Feb 27, 2020
 * @author Andrey Belomutskiy, (c) 2012-2020
 */

#pragma once

#include "engine_configuration_generated_structures.h"

typedef struct {
	int version;
	int size;
	persistent_config_s persistentConfiguration;
	uint32_t crc;
} persistent_config_container_s;
