#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "./imu.h"
#include "../config.h"

// ===== BAROMETER =====

void barometer_setup() {
    i2c_init(BAR_I2C_BLK, BAR_SPEED * 1000);
    gpio_set_function(BAR_SDA, GPIO_FUNC_I2C);
    gpio_set_function(BAR_SCL, GPIO_FUNC_I2C);
}

// returns true if barometer working fine
bool barometer_test() {
    uint8_t id;
    i2c_write_blocking(BAR_I2C_BLK, BAR_I2C_ADDR, BAR_IDREG, 1, true);
    i2c_read_blocking(BAR_I2C_BLK, BAR_I2C_ADDR, &id, 1, false);
    return id == BAR_PRODID;
}

void barometer_read() {
    // WIP
}

/*
    0 -> ok
    1 -> barometer err
*/
uint8_t imu_setup() {

    // barometer setup
    barometer_setup();
    if (!(barometer_test())) return 1;

    return 0;
}