#include "inc/pid.h"
#include <math.h>
#include <stdio.h>

static float Kp = 1.0f, Ki = 0.0f, Kd = 0.0f;
static float integrator = 0.0f;
static float prev_error = 0.0f;
static float integral_limit = 1000.0f;

void pid_init(float kp, float ki, float kd) {
    Kp = kp; Ki = ki; Kd = kd;
    integrator = 0.0f; prev_error = 0.0f;
}

void pid_set_gains(float kp, float ki, float kd) {
    Kp = kp; Ki = ki; Kd = kd;
}

float pid_compute(float setpoint, float measurement, float dt) {
    float error = setpoint - measurement;
    integrator += error * dt;
    // anti-windup
    if (integrator > integral_limit) integrator = integral_limit;
    if (integrator < -integral_limit) integrator = -integral_limit;
    float derivative = (error - prev_error) / dt;
    float out = Kp * error + Ki * integrator + Kd * derivative;
    prev_error = error;
    return out;
}

void pid_adapt_if_needed(float velocity_enc, float velocity_fused) {
    // Simple heuristic: if absolute discrepancy exceeds threshold, slightly raise Kp temporarily
    float discrepancy = fabsf(velocity_enc - velocity_fused);
    const float THRESH = 0.1f; // tune per-system
    if (discrepancy > THRESH) {
        // bump gains
        Kp *= 1.01f;
        if (Kp > 10.0f) Kp = 10.0f;
    } else {
        // slowly decay Kp back towards nominal (1.0)
        Kp += (1.0f - Kp) * 0.001f;
    }
}

void pid_reset(void) {
    integrator = 0.0f; prev_error = 0.0f;
}
