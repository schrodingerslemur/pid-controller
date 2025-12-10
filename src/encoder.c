#include "inc/encoder.h"
#include <stdint.h>
#include <stdlib.h>

// Simplified encoder module: in real hardware read TIM encoder or EXTI counters
static int32_t last_count = 0;
static int32_t delta = 0;
static float position_m = 0.0f;
static float velocity_m_s = 0.0f;
static const float TICKS_TO_M = 0.0000488f; // example conversion

void encoder_init(void) {
    last_count = 0;
    delta = 0;
    position_m = 0.0f;
    velocity_m_s = 0.0f;
}

void encoder_update(void) {
    // read hardware counter e.g. TIMx->CNT
    int32_t new_count = last_count; // placeholder - replace with actual read
    delta = new_count - last_count;
    last_count = new_count;
    position_m += delta * TICKS_TO_M;
    // velocity computed elsewhere with dt
    velocity_m_s = delta * TICKS_TO_M / 0.001f;
}

int32_t encoder_get_delta(void) { return delta; }
float encoder_get_position(void) { return position_m; }
float encoder_get_velocity(void) { return velocity_m_s; }
