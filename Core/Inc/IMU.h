//
// Created by HiAir on 2025/10/12.
//

#ifndef RM_C_BOARD_TEST_DEV_IMU_H
#define RM_C_BOARD_TEST_DEV_IMU_H

#include "main.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

void imu_init(void);

#ifdef __cplusplus
}
#endif //__cplusplus

#ifdef __cplusplus
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
  float get_roll();
  float get_pitch();
  float debug_get_vector(int number, int axis);


private:
//私有方法
  //读取
  void read_data(void);
  //计算
  //滤波
  void gyro_filter(void);
  //按角速度旋转estimated矢量得到天空矢量
  void gyro_vector_calculate(void);
  //通过加速度计算天空矢量
  void accel_vector_calculate(void);
  //加权平均
  void weighted_average(void);
  //输出
  void output_angles(void);

  //工具函数
  void vector_normalization(float *vector);

//私有变量
  //outdated
  int32_t acc_data[3] = {0};
  int32_t gyro_data[3] = {0};
  //实时更新的解算值 单位 °
  float pitch = 1;
  float roll = 1;


  //积分时间 单位s
  const float integrate_time = 1.0 / 1000.0;
  //滤波常数
  const float gyro_filter_weight = 0.005;
  //gyro_vector加权平均权重
  const float average_weight_gyro = 0.5;

  //加速度值 单位 mg
  int32_t raw_acceleration[3];

  //角速度值  x y z 顺序 单位 °/s
  int32_t raw_angular_velocity[3];
  float filtered_angular_velocity[3];//需要初始化

  //vectors指向天
  float estimated_vector[3];//需要初始化
  float gyro_vector[3];
  float accel_vector[3];



  //



};

extern IMU imu;

#endif //__cplusplus

#endif //RM_C_BOARD_TEST_DEV_IMU_H
