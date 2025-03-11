#include "main.h"
#include "led.h"

// Глобальные переменные
TIM_HandleTypeDef htim2;
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

// Простая функция задержки
void Delay_us(uint32_t us) {
    htim2.Instance->CNT = 0;  // Сброс счетчика таймера
    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);  // Сброс флага обновления
    volatile uint32_t cnt = htim2.Instance->CNT;
    while (cnt <= us) {
        cnt = htim2.Instance->CNT;
    }
}

// Простая функция задержки
void Delay_ms(uint32_t ms) {
    while (ms--) {
        Delay_us(1000);  // Задержка на 1 миллисекунду
    }
}

// Инициализация таймера TIM2
void TIM2_Init(void) {
    __HAL_RCC_TIM2_CLK_ENABLE();  // Включаем тактирование TIM2

    htim2.Instance = TIM2;      // Инициализация TIM2
    htim2.Init.Prescaler = (SystemCoreClock / 4 / 1000000) - 1;  // 1 тик = 1 мкс
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
   // htim2.Init.Period = 0xF0000000;
    htim2.Init.Period = 0x00FFFFFF;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    
    // Установка регистра TIM2_EGR для генерации события обновления
    __HAL_TIM_ENABLE(&htim2);
    __HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
    htim2.Instance->EGR = TIM_EGR_UG;  // Генерация события обновления

    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        // Инициализация не удалась
        while (1);
    }

    if (HAL_TIM_Base_Start(&htim2) != HAL_OK) {
        // Запуск таймера не удался
        while (1);
    }
}

int main(void) {
    // Инициализация HAL библиотеки
    HAL_Init();

    // Настройка системного тактирования
    SystemClock_Config();

    // Инициализация таймера TIM2
    TIM2_Init();

    // Инициализация светодиода на пине PA5
    LED_Init(GPIOA, GPIO_PIN_5);

    while (1) {
        // Включение светодиода
        LED_Toggle(GPIOA, GPIO_PIN_5);
        Delay_us(2000000);  // Задержка в миллисекундах (1 секунда)
    }
}

// Настройка системного тактирования
void SystemClock_Config(void) {
    // Инициализация главного внутреннего регулятора напряжения
    HAL_PWR_EnableBkUpAccess();     // Разрешение доступа к Backup области
    __HAL_RCC_PWR_CLK_ENABLE();     // Включение тактирования PWR

    // Инициализация тактирования
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE; // Использование внешнего источника тактирования
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;                   // Включение внешнего источника тактирования
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;               // Включение PLL
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;       // Источник тактирования для PLL
    RCC_OscInitStruct.PLL.PLLM = 16;                           // Коэффициент деления для HSE
    RCC_OscInitStruct.PLL.PLLN = 120;                          // Умножение на 160
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;                // Делитель для PLL
    RCC_OscInitStruct.PLL.PLLQ = 7;                            // Делитель для USB OTG FS, SDIO и RNG
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {       
        // Инициализация не удалась
        while (1);
    }

    // Инициализация тактирования CPU, AHB и APB
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;   // Источник тактирования для SYSCLK    
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;          // AHB тактируется на частоте SYSCLK
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;           // APB1 тактируется на частоте HCLK/2
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;           // APB2 тактируется на частоте HCLK

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        // Инициализация не удалась
        while (1);
    }
}