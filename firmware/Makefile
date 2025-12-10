# Simple Makefile for STM32 Cortex-M (adjust MCU, LINKER, and startup files as needed)
MCU=Cortex-M4
CPU=cortex-m4
F_CPU=72000000

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
CFLAGS=-mcpu=$(CPU) -mthumb -O2 -Wall -ffunction-sections -fdata-sections -g -I../inc
LDFLAGS=-Tstm32_flash.ld -nostartfiles -Wl,--gc-sections

SRCS=../src/main.c ../src/pid.c ../src/sensor_fusion.c ../src/imu_mpu6050.c ../src/encoder.c
OBJS=$(SRCS:.c=.o)

all: firmware.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

firmware.elf: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

firmware.bin: firmware.elf
	$(OBJCOPY) -O binary firmware.elf firmware.bin

clean:
	rm -f *.o firmware.elf firmware.bin

.PHONY: all clean
