#include "main.h"
#include "led.h"

// Инициализация светодиода
void LED_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    // Включение тактирования GPIOA
    EnableGPIOClock(GPIOx);
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// Включение светодиода
void LED_On(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}

// Выключение светодиода
void LED_Off(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

// Переключение состояния светодиода
void LED_Toggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
}
// Включение тактирования для указанного порта GPIO
void EnableGPIOClock(GPIO_TypeDef* GPIOx) {
    if (GPIOx == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (GPIOx == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }
}