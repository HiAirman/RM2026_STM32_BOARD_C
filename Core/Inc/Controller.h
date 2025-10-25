//
// Created by HiAir on 2025/10/25.
//

#ifndef RM_C_BOARD_TEST_DEV_CONTROLLER_H
#define RM_C_BOARD_TEST_DEV_CONTROLLER_H

#include "main.h"

//RC channel definition
#define RC_CH_VALUE_MIN ((uint16_t)364)
#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
#define RC_CH_VALUE_MAX ((uint16_t)1684)
//RC switch definition
#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

void ControllerInit(void);

#ifdef __cplusplus
}
#endif //__cplusplus

#ifdef __cplusplus
class Controller {
public:
    void init();
    bool IsConnected();
    void RxCallBackHandler(uint8_t size);
    void TimerCallbackHandler();

private:
    bool is_connected_ = false;
    uint16_t last_tick_ = 0;
    uint8_t rx_buffer_[32];
    uint8_t rx_data_[32];

    struct {
        uint16_t ch0;
        uint16_t ch1;
        uint16_t ch2;
        uint16_t ch3;
        uint8_t s1;
        uint8_t s2;
    } rc;

    bool is_data_refreshed = false;
};

extern Controller controller;
#endif

#endif //RM_C_BOARD_TEST_DEV_CONTROLLER_H
