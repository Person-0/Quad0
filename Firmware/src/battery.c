#include "pico/stdlib.h"
#include "hardware/adc.h"

#include "./battery.h"
#include "../config.h"

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

uint16_t lastRead = 15000;
bool battery_should_read() {
    uint32_t timeSinceBootMS = to_ms_since_boot(get_absolute_time());
    if (timeSinceBootMS - lastRead >= 15000) {
        lastRead = 0;
        return true;
    }
    return false;
}