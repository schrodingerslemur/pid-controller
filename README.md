# Adaptive Motor Control | Sensor-Fusion PID on STM32

**September 2025 – November 2025**

A portfolio-quality embedded project that implements a closed-loop motor control system on an STM32 MCU using sensor fusion between a quadrature encoder and an IMU (gyro/accel). The system runs a self-tuning PID controller that adapts gains when large disturbances are detected. Telemetry and tuning are exposed over UART and a small Python dashboard for realtime plotting and logging.

## Features
- STM32 (HAL) project structure (CMSIS/HAL-compatible).
- Quadrature encoder input, PWM motor drive, current sense (ADC), and IMU (I²C) reading.
- Sensor fusion module (complementary filter + optional simplified Kalman).
- PID controller with gain scheduling (self-tuning heuristic).
- UART telemetry protocol (CSV-like) and a Python dashboard tool (`telemetry/telemetry.py`) that logs and plots data.
- Makefile for arm-none-eabi-gcc toolchain and `flash.sh` script template for OpenOCD/ST-Link.
- Container-friendly: included `docker/` files show how to wrap the Python dashboard.

## What you get in this repo
- `src/` : embedded C sources (main + modules)
- `inc/` : headers
- `firmware/` : Makefile, linker script template
- `telemetry/` : Python telemetry client to read UART and plot/save data
- `docs/` : design notes and tuning guide

## Quick start (developer machine)
1. Install ARM toolchain (e.g. `arm-none-eabi-gcc`) and OpenOCD or use STM32CubeIDE.
2. Build:
```bash
cd firmware
make
```
3. Flash with OpenOCD or via CubeProgrammer. Example (OpenOCD):
```bash
./flash.sh
```
4. Run telemetry (on host):
```bash
python3 telemetry/telemetry.py --port /dev/ttyUSB0 --baud 115200
```

## Files of interest
- `src/main.c` – system init, control loop, UART telemetry.
- `src/pid.c` / `inc/pid.h` – PID implementation & adaptive logic.
- `src/sensor_fusion.c` / `inc/sensor_fusion.h` – complementary filter & state estimator.
- `telemetry/telemetry.py` – simple real-time plotting and logging (uses pyserial & matplotlib).

## Hardware connections (example)
- Motor driver PWM -> TIMx_CHy (PAx / PBx depending on board)
- Encoder A/B -> EXTI / TIM encoder interface pins
- IMU (e.g. MPU6050) -> I2C1 (SCL/SDA)
- Current sense -> ADC1_INx
- UART TX/RX -> USB-UART or ST-Link VCP

## Tuning notes
Start with conservative PID gains (small P, zero I/D). Increase P until oscillation, add I to eliminate steady-state error, then D to damp. Adaptive routine will increase gains slightly under heavy load conditions detected by discrepancy between encoder velocity and IMU-derived velocity.

---

If you'd like, I can:
- Produce a CubeMX `.ioc` skeleton (STM32CubeMX project).
- Convert Makefile to PlatformIO configuration.
- Add simulated testbench code that runs on host (unit tests).
