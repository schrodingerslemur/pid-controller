#ifndef INC_ENCODER_H
#define INC_ENCODER_H

#include <stdint.h>

void encoder_init(void);
void encoder_update(void);
int32_t encoder_get_delta(void);
float encoder_get_position(void);
float encoder_get_velocity(void);

#endif
