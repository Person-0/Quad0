# **Quad0**

*quadcopter with a custom flight controller, firmware that supports both brushed and brushless motors*

## Design
This is a custom flight controller with minimal stuff required to fly a quadcopter on-board, supporting both brushless and brushed motors.

Planned onboard components include:

- a powerful enough MCU
- IMU (Accelerometer, Gyroscope, Magnetometer, Barometer): Might add/remove depending upon requirements
- MOSFET motor drivers for brushed motors

It implements support for both brushless and brushed motors by providing separate solder pads or connectors (like JST 2pin/3pin, 2.54mm headers) for connecting the ESC's signal pin or controlling the MOSFET gate.

The board will be designed in a way such that it can fly with standard 8520 coreless motors and a tiny lipo battery for brushed mode.

As for the brushless mode, I will be targeting 2204 size brushless motors with a 2S configuration (5inch prop size, ~5inch frame)

Note that the frame will be different for brushed and brushless modes due to weight and size requirements, and I will be designing both myself!