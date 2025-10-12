//
// Created by HiAir on 2025/10/12.
//

#include "IMU.h"

#include "bmi088.h"

#include <tgmath.h>

void IMU::acc_calculate() {
  uint8_t raw_range;
  uint8_t rx_acc_data[6];
  bmi088_accel_read_reg(0x41, &raw_range, 1);
  bmi088_accel_read_reg(0x12, rx_acc_data, 6);

  //calculate data 单位毫重力单位mg
  IMU::acc_data[0] = (rx_acc_data[1] << 8 | rx_acc_data[0]) / 32768 * 1000 * pow(2, (raw_range + 1)) * 1.5;//X
  IMU::acc_data[1] = (rx_acc_data[3] << 8 | rx_acc_data[2]) / 32768 * 1000 * pow(2, (raw_range + 1)) * 1.5;//Y
  IMU::acc_data[2] = (rx_acc_data[5] << 8 | rx_acc_data[4]) / 32768 * 1000 * pow(2, (raw_range + 1)) * 1.5;//Z
}

void IMU::gyro_calculate() {
  uint8_t raw_range;
  uint8_t rx_gyro_data[6];
  bmi088_gyro_read_reg(0x0F, &raw_range, 1);
  bmi088_gyro_read_reg(0x02, rx_gyro_data, 6);

  //calculate data 单位degree/s
  IMU::gyro_data[0] = (rx_gyro_data[1] << 8 | rx_gyro_data[0]) / 32768 * 1000 / pow(2, (raw_range - 1));
  IMU::gyro_data[1] = (rx_gyro_data[3] << 8 | rx_gyro_data[2]) / 32768 * 1000 / pow(2, (raw_range - 1));
  IMU::gyro_data[2] = (rx_gyro_data[5] << 8 | rx_gyro_data[4]) / 32768 * 1000 / pow(2, (raw_range - 1));
}

//getter
uint32_t IMU::acc_x_get() {
  return IMU::acc_data[0];
}
uint32_t IMU::acc_y_get() {
  return IMU::acc_data[1];
}
uint32_t IMU::acc_z_get() {
  return IMU::acc_data[2];
}
uint32_t IMU::gyro_x_get() {
  return IMU::gyro_data[0];
}
uint32_t IMU::gyro_y_get() {
  return IMU::gyro_data[1];
}
uint32_t IMU::gyro_z_get() {
  return IMU::gyro_data[2];
}