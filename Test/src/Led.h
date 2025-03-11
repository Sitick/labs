#ifndef LED_H
#define LED_H

#include "main.h"  // Подключаем Main.h, который уже включает stm32f4xx_hal.h

// Прототипы функций
void LED_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  // Инициализация светодиода
void LED_On(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);    // Включение светодиода
void LED_Off(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);   // Выключение светодиода
void LED_Toggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);// Переключение состояния светодиода
void EnableGPIOClock(GPIO_TypeDef* GPIOx) ;             // Включение тактирования для указанного порта GPIO
#endif // LED_H