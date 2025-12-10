/*
 * main.c - Adaptive Motor Control demo (HAL-style pseudocode)
 * This file is illustrative: adapt pin names and HAL init to your MCU and CubeMX config.
 */

#include "inc/pid.h"
#include "inc/sensor_fusion.h"
#include "inc/imu_mpu6050.h"
#include "inc/encoder.h"
#include "inc/telemetry.h"

#include <stdint.h>
#include <stdbool.h>

#define CONTROL_HZ 1000  // control loop frequency
#define DT (1.0f/CONTROL_HZ)

int main(void) {
    // HAL_Init(); SystemClock_Config(); MX_GPIO_Init(); MX_TIM_PWM_Init(); MX_I2C1_Init(); MX_ADC1_Init(); MX_USART2_UART_Init();
    telemetry_init(115200);

    // Init modules
    encoder_init();
    imu_init();
    sensor_fusion_init(DT);
    pid_init(1.0f, 0.0f, 0.0f); // conservative starting gains

    uint32_t tick = 0;
    while (1) {
        // --- Read sensors (non-blocking / DMA preferred in real app) ---
        encoder_update();
        imu_update(); // reads accel/gyro via I2C

        // --- State estimation ---
        float position = encoder_get_position();
        float velocity_enc = encoder_get_velocity();
        sensor_fusion_update(encoder_get_delta(), imu_get_gyro_z(), imu_get_accel_x(), imu_get_accel_y());
        float velocity = sensor_fusion_get_velocity();

        // --- Control ---
        float setpoint = 0.0f; // example: hold position or follow trajectory
        float control = pid_compute(setpoint, position, DT);

        // Send to PWM driver (scale control -> duty)
        // pwm_set_duty(control);

        // Adaptive heuristic: if discrepancy between encoder vel and fused vel is large, adjust gains
        pid_adapt_if_needed(velocity_enc, velocity);

        // Telemetry packet every 10ms
        if ((tick % (CONTROL_HZ/100)) == 0) {
            telemetry_send(position, velocity_enc, velocity, control);
        }

        tick++;
        // wait until next control tick (use timer interrupt or delay)
        // HAL_Delay_us(1000/CONTROL_HZ);    // placeholder
    }
    return 0;
}
