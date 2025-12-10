#include "inc/sensor_fusion.h"
#include <math.h>
#include <stdint.h>

// Complementary filter parameters
static float alpha = 0.98f;
static float dt_global = 0.001f;
static float velocity_est = 0.0f;

// Example conversion constants (tune for your encoder and mounting)
static const float TICKS_PER_REV = 2048.0f;
static const float WHEEL_CIRCUMFERENCE_M = 0.1f; // example
static const float TICKS_TO_M = WHEEL_CIRCUMFERENCE_M / TICKS_PER_REV;

void sensor_fusion_init(float dt) {
    dt_global = dt;
    velocity_est = 0.0f;
}

void sensor_fusion_update(int32_t encoder_delta, float gyro_z, float accel_x, float accel_y) {
    // encoder_delta: ticks since last sample -> encoder velocity (m/s)
    float vel_enc = (encoder_delta * TICKS_TO_M) / dt_global;

    // approx from gyro (rad/s) -> linear velocity if mounted (application specific)
    float vel_gyro = gyro_z; // placeholder: depends on mounting geometry

    // simple complementary filter
    velocity_est = alpha * (velocity_est + vel_gyro * dt_global) + (1.0f - alpha) * vel_enc;
}

float sensor_fusion_get_velocity(void) {
    return velocity_est;
}
