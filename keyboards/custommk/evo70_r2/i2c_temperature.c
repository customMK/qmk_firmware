// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "i2c_temperature.h"
#include "i2c_master.h"
#include "evo70_r2.h"

static int16_t raw_temperature = 0; //signed 16 bit int representing 1/16th of a degree C
static bool NST175_valid = false;

extern user_config_t user_config;

int16_t convert_NST175_tempearture_reading(uint8_t MSB, uint8_t LSB) {
    // Performs sign extension and shifting of 12-bit read value to 16-bit signed integer
    // Each LSB of result is 0.0625 deg C
    // To produce output in deg C, take the return value and divide by 16
    
    uint16_t temp_builder = 0;
    temp_builder = MSB << 4;
    temp_builder += LSB >> 4;
    if (MSB >> 7) {   //most significant bit was 1, so temperature is negative, sign extend
        temp_builder += 0b1111000000000000;
    }
    return (int16_t) temp_builder;
}

void init_temperature_i2c(void) {

    uint8_t ProductIDRegister = 0b00000111;
    i2c_transmit((TEMPERATURE_ADDRESS << 1), &ProductIDRegister, 1, TEMPERATURE_I2C_TIMEOUT);

    uint8_t ProductIDValue;
    i2c_receive((TEMPERATURE_ADDRESS << 1), &ProductIDValue, 1, TEMPERATURE_I2C_TIMEOUT);

    if (ProductIDValue == 161 ) {
        NST175_valid = true;
    }

    uint8_t ConfigurationRegister = 0b00000001;
    uint8_t ConfigurationValue = 0b01100000;
    uint8_t buf[]   = {ConfigurationRegister, ConfigurationValue};
    i2c_transmit((TEMPERATURE_ADDRESS << 1), buf, 2, TEMPERATURE_I2C_TIMEOUT);

    uint8_t TemperatureRegister = 0b00000000;
    i2c_transmit((TEMPERATURE_ADDRESS << 1), &TemperatureRegister, 1, TEMPERATURE_I2C_TIMEOUT);
    
    uint8_t buf2[] = {0,0};
    i2c_receive((TEMPERATURE_ADDRESS << 1), buf2, 2, TEMPERATURE_I2C_TIMEOUT);
    raw_temperature = convert_NST175_tempearture_reading(buf[0], buf[1]);
}

void update_temperature_i2c(void) {
    if (NST175_valid) {
        uint8_t buf[] = {0,0};
        i2c_receive((TEMPERATURE_ADDRESS << 1), buf, 2, TEMPERATURE_I2C_TIMEOUT);
        raw_temperature = convert_NST175_tempearture_reading(buf[0], buf[1]);
    }
}

uint8_t get_tenths_digit(float value) {
    float value10x;
    value10x = value * 10;
    int val10x_int = (int) value10x;
    return (uint8_t)(abs(val10x_int) % 10);
}

char temperature_string[30];
char *get_temperature_str(void) {
    float temperature;
    temperature = (float)raw_temperature/16;
    if (user_config.report_temperature_in_f) {
        temperature = ((float)temperature*9/5) + 32;
        sprintf(temperature_string, "%i.%uF", (int)temperature, get_tenths_digit(temperature));
    } else {
        sprintf(temperature_string, "%i.%uC", (int)temperature, get_tenths_digit(temperature));
    }
    return temperature_string;
}

int16_t get_temperature_10x(void) {
    // return temperature * 10 regardless of units
    float temperature;
    temperature = (float)raw_temperature/16;
    if (user_config.report_temperature_in_f) {
        temperature = ((float)temperature*9/5) + 32;
    }
    return (int)(temperature * 10);
}