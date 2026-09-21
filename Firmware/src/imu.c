#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "./imu.h"
#include "../config.h"

// ===== BAROMETER =====

void barometer_setup() {
    gpio_set_function(BAR_SDA, GPIO_FUNC_I2C);
    gpio_set_function(BAR_SCL, GPIO_FUNC_I2C);
}

// returns true if barometer working fine
bool barometer_test() {
    uint8_t reg = BAR_IDREG;
    uint8_t id;
    i2c_write_blocking(I2C_BLK, BAR_I2C_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_BLK, BAR_I2C_ADDR, &id, 1, false);
    return id == BAR_PRODID;
}

void barometer_read() {
    // WIP
    // INT pin unused currently
}


// ===== MAGNETOMETER =====

void magnetometer_setup() {
    gpio_set_function(MG_SDA, GPIO_FUNC_I2C);
    gpio_set_function(MG_SCL, GPIO_FUNC_I2C);
}

// returns true if magnetometer working fine
bool magnetometer_test() {
    uint8_t reg = MG_IDREG;
    uint8_t id;
    i2c_write_blocking(I2C_BLK, MG_I2C_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_BLK, MG_I2C_ADDR, &id, 1, false);
    return id == MG_PRODID;
}

void magnetometer_read() {
    // WIP
    // INT, DRDY pin unused currently
}


// ===============================
// ========== IMU FULL ===========
// ===============================

/*
    0 -> ok
    1 -> barometer err
*/
uint8_t imu_setup() {

    i2c_init(I2C_BLK, I2C_SPEED * 1000);

    // barometer setup
    barometer_setup();
    if (!(barometer_test())) return 1;

    magnetometer_setup();
    if (!(magnetometer_test())) return 2;

    return 0;
}