//
// Created by HiAir on 2025/10/12.
//

#ifndef RM_C_BOARD_TEST_DEV_IMU_H
#define RM_C_BOARD_TEST_DEV_IMU_H

#include "main.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

class IMU {
public:
  void acc_calculate();
  void gyro_calculate();

  //getter & setter
  int32_t acc_x_get();
  int32_t acc_y_get();
  int32_t acc_z_get();
  int32_t gyro_x_get();
  int32_t gyro_y_get();
  int32_t gyro_z_get();
private:
  int32_t acc_data[3];
  int32_t gyro_data[3];
};

#endif //RM_C_BOARD_TEST_DEV_IMU_H
