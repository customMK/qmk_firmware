// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "moonphase.h"

uint32_t days_since_01_01_0001(uint8_t month, uint8_t day, uint16_t year) {
    uint32_t numdays;
    int num_leapyears = 0;
    int days_given_month[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int i;

    // Number of leapyears since year one
    for(i = 1; i < year; i++)
        if((i % 4 == 0 && i % 100 != 0) || (i % 4 == 0 && i % 400 == 0))
            num_leapyears++;

    // Add a day for months after March on leapyears
    if((year % 4 == 0 && year % 100 != 0) || (year % 4 == 0 && year % 400 == 0))
        for(i = 2; i < 12; i++)
            days_given_month[i]++;

    numdays = (year - 1) * 365 + num_leapyears + days_given_month[month - 1] + day;

    return numdays;
}

uint16_t calc_moon_phase(uint8_t month, uint8_t day, uint16_t year, uint8_t hour) {
    uint32_t numdays;
    float days_since_new_moon;

    numdays = days_since_01_01_0001(month, day, year);
    days_since_new_moon = (numdays - 730124.5) + hour/24.0;
    // 730125 is the days_since_01_01_0001(1, 6, 2000), which is used as a new moon reference date, around noon
    // Refer to https://omnicalculator.com/everyday-life/moon-phase
    float number_of_moon_cycles = days_since_new_moon / 29.53058770576;
    if (number_of_moon_cycles < 0) {
        // We don't care about the integer portion of the number of cycles
        // So just add a big enough integer to force it to be positive for uint purposes
        number_of_moon_cycles += 30000;
    }
    uint32_t intpart = (uint32_t)number_of_moon_cycles;
    float cycle_fraction = number_of_moon_cycles - intpart;
    
    // Return the current moon phase as a fraction of 1000
    return (uint16_t)(cycle_fraction*1000);
}
