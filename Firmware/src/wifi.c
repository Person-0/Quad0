#include "pico/stdlib.h"
#include "hardware/uart.h"

#include "./wifi.h"
#include "../pin_defs.h"

#define WIFI_UART WIFI_UART_BLOCK == 1 ? uart1 : uart0

char _wifi_data[64] = {};
uint8_t _wifi_data_index = 0;

bool wifi_test() {
    uart_puts(WIFI_UART, "AT\r\n");
}

void wifi_setup() {
    uart_init(WIFI_UART, 115200);
    gpio_set_function(WIFI_RX, GPIO_FUNC_UART);
    gpio_set_function(WIFI_TX, GPIO_FUNC_UART);
}

void wifi_task() {
    if (uart_is_readable(WIFI_UART)) {
        char c = uart_getc(WIFI_UART);
        _wifi_data[_wifi_data_index] = c;
        _wifi_data_index += 1;
        if (_wifi_data_index > 63) {
            _wifi_data_index = 0;
            // data overwritten!!!
            printf("Wifi Warning: Data was overwritten!");
        }
    }
}