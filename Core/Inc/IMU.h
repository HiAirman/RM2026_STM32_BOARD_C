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
//私有方法
  //数值初始化：赋值raw_angles, previously_temp_anlgles
  void gyro_initialization(void);
  //角速度积分得到角度
  void gyro_angle_integration(void);
  //角度滤波与正规化
  void gyro_angle_process(void);
  //解算地面矢量R

//私有变量
  int32_t acc_data[3] = {0};
  int32_t gyro_data[3] = {0};

  //积分时间
  const float integrate_time = 1.0 / 1000.0;
  //滤波常数
  const float gyro_angle_filter_weight = 0.3;

  //角度值 Axz Ayz 顺序
  float raw_angles[2];
  float previously_temp_angles[2];
  float temp_angles[2];
  float processed_angles[2];

  //



};

#endif //RM_C_BOARD_TEST_DEV_IMU_H
