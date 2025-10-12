//
// Created by HiAir on 2025/10/12.
//

#include "main.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "IMU.h"

IMU imu;

extern uint32_t accel_data[3];
extern uint32_t gyro_data[3];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM6) {
    imu.acc_calculate();
    imu.gyro_calculate();
    accel_data[0] = imu.gyro_x_get();
    accel_data[1] = imu.gyro_y_get();
    accel_data[2] = imu.gyro_z_get();
    gyro_data[0] = imu.gyro_x_get();
    gyro_data[1] = imu.gyro_y_get();
    gyro_data[2] = imu.gyro_z_get();
  }
}

