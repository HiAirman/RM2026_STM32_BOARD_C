//
// Created by HiAir on 2025/10/12.
//

#include "main.h"
#include "IMU.h"


extern int32_t accel_data[3];
extern int32_t gyro_data[3];
extern float roll, pitch;

float vectorxs[3];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM6) {
    for (int i = 0; i < 3; i++) {
      vectorxs[i] = imu.debug_get_vector(i,0);
    }
    imu.acc_calculate();
    imu.gyro_calculate();
    accel_data[0] = imu.acc_x_get();
    accel_data[1] = imu.acc_y_get();
    accel_data[2] = imu.acc_z_get();
    gyro_data[0] = imu.gyro_x_get();
    gyro_data[1] = imu.gyro_y_get();
    gyro_data[2] = imu.gyro_z_get();
    imu.imu_calculate();
    roll = imu.get_roll();
    pitch = imu.get_pitch();
    for (int i = 0; i < 3; i++) {
      vectorxs[i] = imu.debug_get_vector(i,0);
    }
  }
}

