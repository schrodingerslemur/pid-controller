/* Minimal linker script placeholder. Replace with MCU-specific FLASH/SECTIONS sizes. */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256K
  RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
  .text : { KEEP(*(.isr_vector)) *(.text*) } > FLASH
  .data : { *(.data*) } > RAM
  .bss  : { *(.bss*) } > RAM
}
