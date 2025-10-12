//
// Created by HiAir on 2025/10/12.
//

#include "IMU.h"
#include <math.h>
#include "bmi088.h"

uint8_t raw_range = 0;
uint8_t rx_acc_data[6];
uint8_t rx_gyro_data[6];
void IMU::acc_calculate() {
  //bmi088_accel_write_single_reg(0x41, 0x01);

  bmi088_accel_read_reg(0x41, &raw_range, 1);
  bmi088_accel_read_reg(0x12, rx_acc_data, 6);

  //calculate data 单位毫重力单位mg
  IMU::acc_data[0] = (int16_t)(rx_acc_data[1] << 8 | rx_acc_data[0]) * 1000.f * 1.5f * pow(2, (raw_range + 1)) / 32768.f;//X
  IMU::acc_data[1] = (int16_t)(rx_acc_data[3] << 8 | rx_acc_data[2]) * 1000.f * 1.5f * pow(2, (raw_range + 1)) / 32768.f;//Y
  IMU::acc_data[2] = (int16_t)(rx_acc_data[5] << 8 | rx_acc_data[4]) * 1000.f * 1.5f * pow(2, (raw_range + 1)) / 32768.f;//Z
}

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

//private 区域

void IMU::gyro_angle_integration() {
  raw_angles[0] += gyro_data[1] * integrate_time;
  raw_angles[1] += gyro_data[0] * integrate_time;
    //不做限制于0-360方便滤波
}
void IMU::gyro_angle_process() {
  //filter
  temp_angles[0] = (previously_temp_angles[0] + gyro_angle_filter_weight * raw_angles[0]) / (1 + gyro_angle_filter_weight);
  temp_angles[1] = (previously_temp_angles[1] + gyro_angle_filter_weight * raw_angles[1]) / (1 + gyro_angle_filter_weight);

  previously_temp_angles[0] = temp_angles[0];//记录原先值
  previously_temp_angles[1] = temp_angles[1];

  //regular
  if (temp_angles[0] > 0) {
    processed_angles[0] = temp_angles[0] - fmod(temp_angles[0], 360);
  } else {
    processed_angles[0] = 360.0 + fmod(temp_angles[0], 360);
  }

  if (temp_angles[1] > 0) {
    processed_angles[1] = temp_angles[1] - fmod(temp_angles[1], 360);
  } else {
    processed_angles[1] = 360.0 + fmod(temp_angles[1], 360);
  }
}




