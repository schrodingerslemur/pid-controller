#ifndef INC_SENSOR_FUSION_H
#define INC_SENSOR_FUSION_H

void sensor_fusion_init(float dt);
void sensor_fusion_update(int32_t encoder_delta, float gyro_z, float accel_x, float accel_y);
float sensor_fusion_get_velocity(void);

#endif // INC_SENSOR_FUSION_H
