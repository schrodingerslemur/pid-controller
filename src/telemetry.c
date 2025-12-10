#include "inc/telemetry.h"
#include <stdio.h>

// Replace printf with HAL_UART_Transmit in real firmware

void telemetry_init(int baud) {
    // init UART at baud
}

void telemetry_send(float position, float vel_enc, float vel_fused, float control) {
    // Simple CSV: timestamp,position,vel_enc,vel_fused,control
    // In real firmware use a buffer and UART transmit
    printf("%lu,%.6f,%.6f,%.6f,%.6f\n", (unsigned long)0, position, vel_enc, vel_fused, control);
}
