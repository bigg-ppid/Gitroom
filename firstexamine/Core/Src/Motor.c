#include "tim.h"
//
// Created by king on 2026/10/6.
//
void Motor_Set(float speed) {
    //确定方向
    if (speed > 0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    } else if (speed < 0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
    float speed_real = (speed < 0) ? -speed : speed;
    if (speed_real > 100) {
        speed_real = 100;
    }
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, speed_real);
}