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
    void ImuInitialization(void);
    //已打包解算程序
    void ImuCalculate(void);

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
    float roll_get();
    float pitch_get();
    float debug_get_vector(int number, int axis);

private:
    //私有方法
    //读取
    void ReadData(void);
    //计算
    //滤波
    void GyroFilter(void);
    //按角速度旋转estimated矢量得到天空矢量
    void GyroVectorCalculate(void);
    //通过加速度计算天空矢量
    void AccelVectorCalculate(void);
    //加权平均
    void WeightedAverage(void);
    //输出
    void OutputAngles(void);

    //工具函数
    void VectorNormalization(float* vector);

    //私有变量
    //outdated
    int32_t acc_data_[3] = { 0 };
    int32_t gyro_data_[3] = { 0 };
    //实时更新的解算值 单位 °
    float pitch_ = 1;
    float roll_ = 1;


    //积分时间 单位s
    const float integrate_time_ = 1.0 / 1000.0;
    //滤波常数
    const float gyro_filter_weight_ = 0.0005;
    //gyro_vector加权平均权重
    const float average_weight_gyro_ = 0.7;

    //加速度值 单位 mg
    int32_t raw_acceleration_[3];

    //角速度值  x y z 顺序 单位 °/s
    int32_t raw_angular_velocity_[3];
    float filtered_angular_velocity_[3]; //需要初始化

    //vectors指向天
    float estimated_vector_[3]; //需要初始化
    float gyro_vector_[3];
    float accel_vector_[3];
};

extern IMU imu;

#endif //__cplusplus

#endif //RM_C_BOARD_TEST_DEV_IMU_H
