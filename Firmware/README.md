# **Quad0**: Firmware

This directory contains custom flight controller firmware for Quad0.

## Current State

The firmware is currently work-in-progress and will be updated as I build the project physically. Since this project requires extensive physical testing (Checks for current firmware, PID Tuning, runtime errors etc.), the firmware will be updated progressively as I test while building instead of doing everything before and then rewriting most of the stuff again (which would be a huge waste of time).

### Boot flow
1. MCU Powered-on, Stat LED initialized
2. Battery status checking logic initialized
3. Battery read, if equal-to or below 15%, boot halted with status indication
4. Other components initialized (WiFI Rx, IMU, Motors)
5. Main loop starts and calls all methods at every iteration


### What is expected to work?
The following stuff is expected to happen on powering the MCU, with sufficient battery charge (or USB power):
- MCU Boots
- Power LED lights up
- Status LED does not light up at all (battery charge is above 15%)
- All components are properly initialized, Status LED does not blink (no IMU error)
- Program flow proceeds to the main loop
- Status LED does not light up at all again (battery charge above 5%)

### What is left?
- Receiving Instructions from the WiFi receiver: will be done after ESP01 is confirmed to be working fine with the current initialization setup.
- Reading IMU sensors data: again, will be done after any errors that show up during IMU initialization after real world testing are fixed.
- Drone stabilization, calibration / PID Tuning: will be done after the previous two steps are complete.

### Status LED Indications

These are the error codes currently coded in the firmware. If these are displayed, it means the MCU encountered a fatal error and cannot continue normal operation.

- `2` blinks, `250ms` interval -> Battery percentage too low to boot or continue operation.
- `5` blinks, `250ms` interval -> IMU setup failed, check serial log for more info.

### Specific Error Codes
- IMU setup failed:
    - `Code` is available in serial console
    - `1`: barometer_test() returned false
    - `2`: magnetometer_test() returned false
    - `3`: icm_test() returned false (ICM-42688, Accelerometer + Gyro)


## Firmware Compiling / Flashing
- Install the [Raspberry Pi Pico VS Code extension](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico)
- Clone this repository
- Open this folder (/firmware) in VS Code
- The extension will automatically detect your workspace and install necessary toolchains that will be used to compile the firmware
- Edit files if required
- Press `Compile` at the bottom bar to test whether the firmware compiles successfully
- Hold the boot tactile switch on the XIAO-RP040 while plugging it into your PC, this will allow us to flash the firmware
- Use the `Run` button next to the Compile button at the bottom bar to compile, flash the firmware to the Pico. After the firmware is flashed, the Pico will auto reboot and you will see the results directly.

## Special Notes

- Use the official Raspberry Pi Pico VS Code extension to build or flash the firmware as it will save you lots of time and config messes.


## Pin Definiions
Available in [config.h](./config.h).