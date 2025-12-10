#!/bin/bash
# Template flash script using OpenOCD. Adjust interface and target config files for your board.
set -e
OPENOCD=openocd
CFG_INTERFACE="interface/stlink.cfg"
CFG_TARGET="target/stm32f4x.cfg"

$OPENOCD -f $CFG_INTERFACE -f $CFG_TARGET -c "program firmware.bin verify reset exit"
