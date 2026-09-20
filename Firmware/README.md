# **Quad0**: Firmware

This directory contains custom flight controller firmware for Quad0.

## Current State

The firmware is currently work-in-progress.

### Boot flow:
1. MCU Powered-on, Stat LED initialized
2. Battery status checking logic initialized
3. Battery read, if equal-to or below 15%, boot halted. Stat led blinks 2 times in an interval of 250ms.