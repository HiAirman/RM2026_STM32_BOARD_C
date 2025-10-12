//
// Created by HiAir on 2025/10/12.
//

#ifndef RM_C_BOARD_TEST_DEV_IMU_H
#define RM_C_BOARD_TEST_DEV_IMU_H

#include "main.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

//初始化
void bmi088_init(void);

//写入一个byte的数据
void bmi088_write_byte(uint8_t tx_data);

//读取一个byte的数据 存至rx_data中
void bmi088_read_byte(uint8_t *rx_data, uint8_t length);

//写入一个byte至寄存器
void bmi088_write_reg(uint8_t reg, uint8_t data);

//片选CS
void BMI088_ACCEL_NS_L(void);
void BMI088_ACCEL_NS_H(void);
void BMI088_GYRO_NS_L(void);
void BMI088_GYRO_NS_H(void);

//第二次打包
//acc写入单个寄存器
void bmi088_accel_write_single_reg(uint8_t reg, uint8_t data);
//gyr写入单个寄存器
void bmi088_gyro_write_single_reg(uint8_t reg, uint8_t data);

//acc读取
void bmi088_accel_read_reg(uint8_t reg, uint8_t *rx_data, uint8_t length);
//gyr读取
void bmi088_gyro_read_reg(uint8_t reg, uint8_t *rx_data, uint8_t length);

#endif //RM_C_BOARD_TEST_DEV_IMU_H
