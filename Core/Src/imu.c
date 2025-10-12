//
// Created by HiAir on 2025/10/12.
//

#include "imu.h"


//写入一个byte的数据
void bmi088_write_byte(uint8_t tx_data) {
    HAL_SPI_Transmit(&hspi1, &tx_data, 1, 1000);
    while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX);
}

//读取一个byte的数据 存至rx_data中
void bmi088_read_byte(uint8_t *rx_data, uint8_t length) {
    HAL_SPI_Receive(&hspi1, rx_data, length, 1000);
    while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_RX);
}

//写入一个byte至寄存器
void bmi088_write_reg(uint8_t reg, uint8_t data) {
    HAL_SPI_Transmit(&hspi1, &reg, 1, 1000);
    while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX);
    HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
    while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX);
}


//片选CS
//加速度器LOW下拉开始通信
void BMI088_ACCEL_NS_L(void) {

}
//加速度器HIGH上拉结束通信
void BMI088_ACCEL_NS_H(void) {

}
//陀螺仪LOW下拉开始通信
void BMI088_GYRO_NS_L(void) {

}
//陀螺仪HIGH上拉结束通信
void BMI088_GYRO_NS_H(void) {

}