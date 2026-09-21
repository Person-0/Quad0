#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"

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


// ===== Accelerometer, Gyro =====
//  refer as ICM (ICM-42688)

void icm_setup() {
    spi_init(ICM_SPI_BLK, SPI_SPEED * 1000000);
    spi_set_format(
        ICM_SPI_BLK,
        8,
        SPI_CPOL_0,
        SPI_CPHA_0,
        SPI_MSB_FIRST
    );

    gpio_set_function(ICM_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(ICM_MISO, GPIO_FUNC_SPI);
    gpio_set_function(ICM_SCK,  GPIO_FUNC_SPI);

    gpio_init(ICM_CSB);
    gpio_set_dir(ICM_CSB, GPIO_OUT);
    gpio_put(ICM_CSB, 1);

    gpio_init(ICM_INT1);
    gpio_set_dir(ICM_INT1, GPIO_IN);
    gpio_init(ICM_INT2);
    gpio_set_dir(ICM_INT2, GPIO_IN);
}

// returns true if ICM-42688 working fine
bool icm_test() {
    uint8_t tx = ICM_WAI_REG | 0x80;
    uint8_t rx;

    gpio_put(ICM_CSB, 0);
    spi_write_blocking(ICM_SPI_BLK, &tx, 1);
    spi_read_blocking(ICM_SPI_BLK, 0x00, &rx, 1);
    gpio_put(ICM_CSB, 1);

    return rx == ICM_WAI_VAL;
}

void icm_read() {
    // WIP
}


// ===============================
// ========== IMU FULL ===========
// ===============================

/*
    0 -> ok
    1 -> barometer err
    2 -> magnetometer err
    3 -> accelerometer + gyro err
*/
uint8_t imu_setup() {

    i2c_init(I2C_BLK, I2C_SPEED * 1000);

    // barometer setup
    barometer_setup();
    if (!(barometer_test())) return 1;

    magnetometer_setup();
    if (!(magnetometer_test())) return 2;

    icm_setup();
    if (!(icm_test())) return 3;

    return 0;
}