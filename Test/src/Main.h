#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx_hal.h"
void Delay_us(uint32_t us);         // Простая функция задержки
void Delay_ms(uint32_t ms);   // Простая функция задержки
int main(void);                      // Основная функция
void SystemClock_Config(void);       // Настройка системного тактирования

// Глобальные переменные
extern TIM_HandleTypeDef htim2;     // Глобальная переменная для таймера TIM2
extern RCC_OscInitTypeDef RCC_OscInitStruct; // Глобальная переменная для настройки осциллятора
extern RCC_ClkInitTypeDef RCC_ClkInitStruct; // Глобальная переменная для настройки тактирования

#endif // MAIN_H
