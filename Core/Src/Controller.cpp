//
// Created by HiAir on 2025/10/25.
//

#include "Controller.h"

#include <string.h>

#include "usart.h"

void ControllerInit() {
    controller.init();
}

void Controller::init() {
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buffer_, 32);
}
bool Controller::IsConnected() {
    if (last_tick_ + 100 < HAL_GetTick()) {
        is_connected_ = false;
    } else {
        is_connected_ = true;
    }
    return is_connected_;
}

void Controller::RxCallBackHandler(uint8_t size) {
    if (size != 16) {
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buffer_, 32);
        return;
    }
    last_tick_ = HAL_GetTick();
    memcpy(rx_data_, rx_buffer_, 32);
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buffer_, 32);
}

void Controller::TimerCallbackHandler() {
    rc.ch0 = ((int16_t)rx_data_[0] | ((int16_t)rx_data_[1] << 8)) & 0x07FF;
    rc.ch1 = (((int16_t)rx_data_[1] >> 3) | ((int16_t)rx_data_[2] << 5)) & 0x07FF;
    rc.ch2 = (((int16_t)rx_data_[2] >> 6) | ((int16_t)rx_data_[3] << 2) | ((int16_t)rx_data_[4] << 10)) & 0x07FF;
    rc.ch3 = (((int16_t)rx_data_[4] >> 1) | ((int16_t)rx_data_[5] << 7)) & 0x07FF;

    rc.s1 = ((rx_data_[5] >> 4) & 0x000C) >> 2;
    rc.s2 = ((rx_data_[5] >> 5) & 0x0003);
}

Controller controller;