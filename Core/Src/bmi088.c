//
// Created by HiAir on 2025/10/12.
//

#include "bmi088.h"

void bmi088_init(void) {
  // Soft Reset ACCEL
  BMI088_ACCEL_NS_L();
  bmi088_write_reg(0x7E, 0xB6); // Write 0xB6 to ACC_SOFTRESET(0x7E)
  HAL_Delay(1);
  BMI088_ACCEL_NS_H();

  // Soft Reset GYRO
  BMI088_GYRO_NS_L();
  bmi088_write_reg(0x14, 0xB6); // Write 0xB6 to GYRO_SOFTRESET(0x14)
  HAL_Delay(30);
  BMI088_GYRO_NS_H();

  // Switch ACCEL to Normal Mode
  BMI088_ACCEL_NS_L();
  HAL_Delay(1);
  bmi088_write_reg(0x7D, 0x04); // Write 0x04 to ACC_PWR_CTRL(0x7D)
  HAL_Delay(1);
  BMI088_ACCEL_NS_H();
}

//写入一个byte的数据
void bmi088_write_byte(uint8_t tx_data) {
  HAL_SPI_Transmit(&hspi1, &tx_data, 1, 1000);
  while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX)
    ;
}

//读取一个byte的数据 存至rx_data中
void bmi088_read_byte(uint8_t* rx_data, uint8_t length) {
  HAL_SPI_Receive(&hspi1, rx_data, length, 1000);
  while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_RX)
    ;
}

//写入一个byte至寄存器
void bmi088_write_reg(uint8_t reg, uint8_t data) {
  reg = reg & 0x7F;
  HAL_SPI_Transmit(&hspi1, &reg, 1, 1000);
  while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX)
    ;
  HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
  while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX)
    ;
}

//片选CS
//加速度器LOW下拉开始通信
void BMI088_ACCEL_NS_L(void) {
  HAL_GPIO_WritePin(CS_ACC_GPIO_Port, CS_ACC_Pin, GPIO_PIN_RESET);
}
//加速度器HIGH上拉结束通信
void BMI088_ACCEL_NS_H(void) {
  HAL_GPIO_WritePin(CS_ACC_GPIO_Port, CS_ACC_Pin, GPIO_PIN_SET);
}
//陀螺仪LOW下拉开始通信
void BMI088_GYRO_NS_L(void) {
  HAL_GPIO_WritePin(CS_GYR_GPIO_Port, CS_GYR_Pin, GPIO_PIN_RESET);
}
//陀螺仪HIGH上拉结束通信
void BMI088_GYRO_NS_H(void) {
  HAL_GPIO_WritePin(CS_GYR_GPIO_Port, CS_GYR_Pin, GPIO_PIN_SET);
}

//acc写入单个寄存器
void bmi088_accel_write_single_reg(uint8_t reg, uint8_t data) {
  BMI088_GYRO_NS_H();
  BMI088_ACCEL_NS_L();

  bmi088_write_reg(reg, data);

  BMI088_ACCEL_NS_H();
}
//gyr写入单个寄存器
void bmi088_gyro_write_single_reg(uint8_t reg, uint8_t data) {
  BMI088_ACCEL_NS_H();
  BMI088_GYRO_NS_L();

  bmi088_write_reg(reg, data);

  BMI088_GYRO_NS_H();
}
//acc读取
void bmi088_accel_read_reg(uint8_t reg, uint8_t* rx_data, uint8_t length) {
  BMI088_GYRO_NS_H();
  BMI088_ACCEL_NS_L();

  bmi088_write_byte(reg & 0xFF);
  bmi088_read_byte(NULL, 1);
  bmi088_read_byte(rx_data, length);

  BMI088_ACCEL_NS_H();
}
//gyr读取
void bmi088_gyro_read_reg(uint8_t reg, uint8_t* rx_data, uint8_t length) {
  BMI088_ACCEL_NS_H();
  BMI088_GYRO_NS_L();

  bmi088_write_byte(reg & 0xFF);
  bmi088_read_byte(rx_data, length);

  BMI088_GYRO_NS_H();
}