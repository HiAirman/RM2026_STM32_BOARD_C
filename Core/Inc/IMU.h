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
  //数值初始化：
  void imu_initialization(void);
  //已打包解算程序
  void imu_calculate(void);

  //outdated
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
  //读取
  void read_data(void);
  //计算
  void gyro_filter(void);
  void gyro_vector_calculate(void);
  void accel_vector_calculate(void);
  void weighted_average(void);
  //输出
  void output_angles(void);

  //工具函数
  void vector_normalization(float *vector);

//私有变量
  //outdated
  int32_t acc_data[3] = {0};
  int32_t gyro_data[3] = {0};

  //积分时间
  const float integrate_time = 1.0 / 1000.0;
  //滤波常数
  const float gyro_filter_weight = 0.3;
  //gyro_vector加权平均权重
  const float average_weight_gyro = 0.5;

  //加速度值mg
  float raw_acceleration[3];

  //角速度值  x y z 顺序
  float raw_anglar_velocity[3];
  float filtered_angular_velocity[3];

  //vectors
  float estimated_vector[3];//指向天

  float gyro_vector[3];
  float accel_vector[3];



  //



};

#endif //RM_C_BOARD_TEST_DEV_IMU_H
