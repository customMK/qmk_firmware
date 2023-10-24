// Copyright 2022 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#pragma once

#ifndef TEMPERATURE_ADDRESS
#    define TEMPERATURE_ADDRESS 0x48
#endif

#ifndef TEMPERATURE_I2C_TIMEOUT
#    define TEMPERATURE_I2C_TIMEOUT 100
#endif

void init_temperature_i2c(void);

//because temps change slowly and i2c is slow, only call this occasionally, it reads updated vales from the temp sensor
void update_temperature_i2c(void);

char *get_temperature_str(void);

int16_t get_temperature_10x(void);