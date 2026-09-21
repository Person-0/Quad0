# **Quad0**: Firmware

This directory contains custom flight controller firmware for Quad0.

## Current State

The firmware is currently work-in-progress and will be updated as I build the project physically. Since this project requires extensive physical testing (Checks for current firmware, PID Tuning, runtime errors etc.), the firmware will be updated progressively as I test while building instead of doing everything before and then rewriting most of the stuff again (which would be a huge waste of time). 

### Boot flow
1. MCU Powered-on, Stat LED initialized
2. Battery status checking logic initialized
3. Battery read, if equal-to or below 15%, boot halted with status indication.
4. Other components initialized
5. Main loop starts with all required functions.

### Status LED Indications

These are the error codes currently coded in the firmware. If these are displayed, it means the MCU encountered a fatal error and cannot continue normal operation.

- 2 blinks, 250ms interval -> Battery too low