#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "./motors.h"
#include "../config.h"

uint8_t MotorsIndexed[] = {MOTOR1, MOTOR2, MOTOR3, MOTOR4};

void motor_setup() {
    uint _slices[] = {
        pwm_gpio_to_slice_num(MOTOR1),
        pwm_gpio_to_slice_num(MOTOR2),
        pwm_gpio_to_slice_num(MOTOR3),
        pwm_gpio_to_slice_num(MOTOR4)
    };
    for (uint8_t i = 0; i < 4; i++) {
        gpio_set_function(MotorsIndexed[i], GPIO_FUNC_PWM);
        pwm_set_wrap(_slices[i], MOTOR_MAX_VAL);
        pwm_set_gpio_level(_slices[i], 0);
        pwm_set_enabled(_slices[i], true);
    }

}

/*
    motorNum: Motor Index (1-4)
    speed: 0 - MOTOR_MAX_VAL
*/
void motor_set_speed(uint8_t motorNum, uint16_t speed) {
    if (motorNum < 1 || motorNum > 4) return; // invalid motor num!
    pwm_set_gpio_level(MotorsIndexed[motorNum-1], speed);
}