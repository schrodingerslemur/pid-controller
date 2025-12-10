# Tuning Guide

1. Verify sensors: ensure encoder counts and IMU outputs are sensible.
2. Start with Kp = 1.0, Ki = 0.0, Kd = 0.0.
3. Increase Kp until system responds quickly but without sustained oscillation.
4. Add Ki to remove steady-state error. Keep Ki small to avoid wind-up.
5. Add Kd to damp overshoot.
6. Use telemetry logs to plot error, actuator command, and sensor readings. Adjust dt-based filtering and complementary alpha.
7. Adaptive thresholds:
   - Discrepancy threshold (encoder vs fused) ~ 5-10% of nominal velocity.
   - If triggered, temporarily increase Kp by 5-10% and log events.
