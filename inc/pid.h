#ifndef INC_PID_H
#define INC_PID_H

#include <stdbool.h>

void pid_init(float kp, float ki, float kd);
float pid_compute(float setpoint, float measurement, float dt);
void pid_set_gains(float kp, float ki, float kd);
void pid_adapt_if_needed(float velocity_enc, float velocity_fused);
void pid_reset(void);

#endif // INC_PID_H
