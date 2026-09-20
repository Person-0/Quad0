#include <stdio.h>
#include "pico/stdlib.h"

#include "./pin_defs.h"
#include "./src/battery.h"

void blink_stat(uint8_t times, uint8_t interval) {
    while(times > 0) {
        times -= 1;
        gpio_put(STAT_LED, 1);
        sleep_ms(interval / 2);
        gpio_put(STAT_LED, 0);
        sleep_ms(interval / 2);
    }
}

int main() {
    stdio_init_all();

    // initialize the stat led
    gpio_init(STAT_LED);
    gpio_put(STAT_LED, 0);

    // initialize battery info
    setup_battery_info();
    if (battery_read() <= 15) { // don't continue if battery < 15%
        blink_stat(2, 250);
        return 0;
    }

    while (true) {
        sleep_ms(1000);
    }

    return 0;
}
