//
// Created by HiAir on 2025/10/12.
//

#include "IMU.h"
#include <math.h>
#include "bmi088.h"

uint8_t raw_range = 0;
uint8_t rx_acc_data[6];
uint8_t rx_gyro_data[6];
//c调用初始化函数
void imu_init() {
  imu.imu_initialization();
}


//initialization
void IMU::imu_initialization(void) {
  read_data();
  accel_vector_calculate();
  for (int i = 0; i < 3; ++i) {
    estimated_vector[i] = accel_vector[i];
  }
  for (int i = 0; i < 3; ++i) {
    filtered_angular_velocity[i] = raw_anglar_velocity[i];
  }
}
//打包解算函数
void IMU::imu_calculate() {
  read_data();
  gyro_filter();
  gyro_vector_calculate();
  accel_vector_calculate();
  weighted_average();
  output_angles();
}

//outdated
void IMU::acc_calculate() {
  //bmi088_accel_write_single_reg(0x41, 0x01);

  bmi088_accel_read_reg(0x41, &raw_range, 1);
  bmi088_accel_read_reg(0x12, rx_acc_data, 6);

  //calculate data 单位毫重力单位mg
  IMU::acc_data[0] = (int16_t)(rx_acc_data[1] << 8 | rx_acc_data[0]) * 1000.f * 1.5f * pow(2, (raw_range + 1)) / 32768.f;//X
  IMU::acc_data[1] = (int16_t)(rx_acc_data[3] << 8 | rx_acc_data[2]) * 1000.f * 1.5f * pow(2, (raw_range + 1)) / 32768.f;//Y
  IMU::acc_data[2] = (int16_t)(rx_acc_data[5] << 8 | rx_acc_data[4]) * 1000.f * 1.5f * pow(2, (raw_range + 1)) / 32768.f;//Z
}
//outdated
void IMU::gyro_calculate() {

  bmi088_gyro_read_reg(0x0F, &raw_range, 1);
  bmi088_gyro_read_reg(0x02, rx_gyro_data, 6);

  //calculate data 单位degree/s
  IMU::gyro_data[0] = (int16_t)(rx_gyro_data[1] << 8 | rx_gyro_data[0]) * 1000 / pow(2, (raw_range - 1)) / 32768.f;
  IMU::gyro_data[1] = (int16_t)(rx_gyro_data[3] << 8 | rx_gyro_data[2]) * 1000 / pow(2, (raw_range - 1)) / 32768.f;
  IMU::gyro_data[2] = (int16_t)(rx_gyro_data[5] << 8 | rx_gyro_data[4]) * 1000 / pow(2, (raw_range - 1)) / 32768.f;
}

//getter
int32_t IMU::acc_x_get() {
  return IMU::acc_data[0];
}
int32_t IMU::acc_y_get() {
  return IMU::acc_data[1];
}
int32_t IMU::acc_z_get() {
  return IMU::acc_data[2];
}
int32_t IMU::gyro_x_get() {
  return IMU::gyro_data[0];
}
int32_t IMU::gyro_y_get() {
  return IMU::gyro_data[1];
}
int32_t IMU::gyro_z_get() {
  return IMU::gyro_data[2];
}
float IMU::get_pitch() {
  return pitch;
}
float IMU::get_roll() {
  return roll;
}

//private 区域


  //读取
void IMU::read_data() {
  for (int i = 0; i < 3; ++i) {
    raw_acceleration[i] = (int16_t)(rx_acc_data[1] << 8 | rx_acc_data[0]) * 1000.f * 1.5f * pow(2, (raw_range + 1)) / 32768.f;
    raw_anglar_velocity[i] = (int16_t)(rx_gyro_data[2 * i + 1] << 8 | rx_gyro_data[2 * i]) * 1000.f / pow(2, (raw_range - 1)) / 32768.f;
  }
}


  //计算
void IMU::gyro_filter() {
  for (int i = 0; i < 3; ++i) {
    filtered_angular_velocity[i] = (filtered_angular_velocity[i] + gyro_filter_weight * raw_anglar_velocity[i]) / (gyro_filter_weight + 1);
  }
}

void IMU::gyro_vector_calculate() {
  //角速度矢量
  float angular_velocity[3];
  const float degree_to_rad = 3.14159265 / 180;
  for (int i = 0; i < 3; ++i) {
    angular_velocity[i] = filtered_angular_velocity[i] * degree_to_rad;
  }
  //叉乘
  float unnormalized_vector[3];
  unnormalized_vector[0] = estimated_vector[0] + angular_velocity[1] * estimated_vector[2] - angular_velocity[2] * estimated_vector[1];
  unnormalized_vector[1] = estimated_vector[1] + angular_velocity[2] * estimated_vector[0] - angular_velocity[0] * estimated_vector[2];
  unnormalized_vector[2] = estimated_vector[2] + angular_velocity[0] * estimated_vector[1] - angular_velocity[1] * estimated_vector[0];
  //归一化
  vector_normalization(unnormalized_vector);
  //赋值
  for (int i = 0; i < 3; ++i) {
    gyro_vector[i] = unnormalized_vector[i];
  }
}

void IMU::accel_vector_calculate() {
  //存下加速度方便归一化
  float unnormalized_vector[3];
  for (int i = 0; i < 3; ++i) {
    unnormalized_vector[i] = raw_acceleration[i];
  }
  //归一化
  vector_normalization(unnormalized_vector);
  //赋值
  for (int i = 0; i < 3; ++i) {
    accel_vector[i] = unnormalized_vector[i];
  }
}

void IMU::weighted_average() {
  for (int i = 0; i < 3; ++i) {
    estimated_vector[i] = (1 - average_weight_gyro) * accel_vector[i] + average_weight_gyro * gyro_vector[i];
  }
}

void IMU::output_angles() {
  roll = - (float)atan2(estimated_vector[1], estimated_vector[2]); //-atan2(y,z)
  pitch = - (float)atan2(estimated_vector[0], sqrt(pow(estimated_vector[1],2) + pow(estimated_vector[2], 2))); //-atan2(x,(y^2 + z^2)^(1/2))
}




void IMU::vector_normalization(float* vector) {
  float length = sqrt(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
  for (int i = 0; i < 3; i++) {
    vector[0] = vector[0] / length;
  }
}

IMU imu;


