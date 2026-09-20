#include "pico/stdlib.h"
#include "hardware/adc.h"

#include "./battery.h"
#include "../pin_defs.h"

void battery_setup() {
    adc_init();
    adc_gpio_init(BAT_SENSE_VD);
    adc_select_input(0);
    gpio_init(BAT_SENSE_EN);
    gpio_put(BAT_SENSE_EN, 0);
}

// returns 0-100 battery percentage
uint8_t battery_read() {
    gpio_put(BAT_SENSE_EN, 1);
    uint16_t value = adc_read();
    gpio_put(BAT_SENSE_EN, 0);
    uint8_t perc = (value * 100) / 4095;
    return perc;
}