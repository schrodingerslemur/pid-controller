#ifndef INC_IMU_MPU6050_H
#define INC_IMU_MPU6050_H

#include <stdint.h>
void imu_init(void);
void imu_update(void);
float imu_get_gyro_z(void);
float imu_get_accel_x(void);
float imu_get_accel_y(void);

#endif
