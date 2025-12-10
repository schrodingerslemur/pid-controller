#ifndef INC_TELEMETRY_H
#define INC_TELEMETRY_H

void telemetry_init(int baud);
void telemetry_send(float position, float vel_enc, float vel_fused, float control);

#endif
