#include <stdio.h>
#include "pico/stdlib.h"

#include "./config.h"
#include "./src/battery.h"
#include "./src/wifi.h"
#include "./src/motors.h"

void blink_stat(uint8_t times, uint8_t interval) {
    while(times > 0) {
        times -= 1;
        gpio_put(STAT_LED, 1);
        sleep_ms(interval / 2);
        gpio_put(STAT_LED, 0);
        sleep_ms(interval / 2);
    }
}

// returns 1 if battery too less, else 0
bool battery_status_check() {
    if (battery_read() <= 15) {
        blink_stat(2, 250);
        return 1;
    }
    return 0;
}

int main() {
    stdio_init_all();

    // stat led
    gpio_init(STAT_LED);
    gpio_put(STAT_LED, 0);

    // battery setup
    battery_setup();
    if (battery_status_check()) return 0;

    // wifi setup
    wifi_setup();

    // motor setup
    motor_setup();

    // main loop
    while (true) {

        wifi_task();

        // read battery in defined interval (in battery_status_check),
        // exit if check failed
        if (battery_should_read() && battery_status_check()) {
            break;
        }

    }

    return 0;
}
