/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ins.h"
#include "stdio.h"
#include "string.h"
#include "OLED.h"
#include "PID.h"
#include "Motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define  SPEED_FULL_SCALE 54.0 //一轮满速度计数
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t last = 0;
int set = 0;
int16_t Speed;
int i,o;
//int16_t difference = 0;
PID_t angle = {
  .Kp = 1.5,
  .Ki = 0,
  .Kd = 0.2,
  .outmax = 100,
  .outmin = -100,
};
PID_t speed = {
  .Kp = 1.3,
  .Ki = 0,
  .Kd = 0,
  .outmax = 50,
  .outmin = -50,
};
// PID_t place = {
//   .Kp = 0.5,
//   .Ki  =0.01,
//   .Kd = 0.2,
//   .outmax = 100,
//   .outmin = -100,
// };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();
  ins_init();
  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  ins_data_t *ins = ins_data();
  char buff[256];
  OLED_Clear();
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET) {//和屏幕的交互
    o = 1;//本来觉得可以直接if（按钮状态），但是有问题，所以加入中间变量。
  }
  if (o = 1) {
    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET){}
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET) {
      while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET){}
      OLED_ShowString(10, 0, "please select mode", 12, 0);
      OLED_ShowString(2, 5, "mode1", 12, 0);
      OLED_ShowString(60, 5, "Stay tuned", 12, 0);
      for (i = 0; i <= 100; i++);
    }

    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET){}//目前只有一个模式，所以只等待B0
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET) {
      OLED_Clear();
      for (i = 0; i <= 50; i++)
      {
        OLED_ShowString(20, 3, "mode1-balance", 16, 0);
      }
      OLED_Clear();
      o = 0;
    }
  }
  while (1) {
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET) {//改变角度
      //set = 1;
      angle.target = 50;
      while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET);
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_SET) {//恢复水平
      //set = 0;
      angle.target = 0;
      while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_SET);
    }
    ins_update();

    HAL_UART_Transmit(&huart1, (uint8_t *)buff, strlen(buff), HAL_MAX_DELAY);
    //if (set == 0) {
    OLED_Showdecimal(3, 1, angle.target, 3, 2, 12, 0);
    OLED_Showdecimal(3, 3, angle.actual, 3, 2, 12, 0);
    OLED_Showdecimal(3, 5, speed.target, 3, 2, 12, 0);
    OLED_Showdecimal(3, 7, speed.actual, 3, 2, 12, 0);
    //}
    // if (set == 1) {
    //   OLED_Showdecimal(3, 1, place.target, 3, 2, 12, 0);
    //   OLED_Showdecimal(3, 3, place.actual, 3, 2, 12, 0);
    //   OLED_Showdecimal(3, 5, speed.target, 3, 2, 12, 0);
    //   OLED_Showdecimal(3, 7, speed.actual, 3, 2, 12, 0);
    // }
    if (HAL_GetTick() - last >= 20){
      uint32_t t=HAL_GetTick();
      last = t;
      sprintf(buff, "%.3f, %.3f, %.3f, %.2f, %.2f, %.2f, %.2f\n",
              ins->roll, ins->pitch, ins->yaw,                        // 姿态角 °
              angle.target, angle.actual, speed.target, speed.actual);// PID：目标角度，实际角度，实际速度，目标速度

    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
     static uint16_t Count1 = 0, Count2 = 0;
     if (htim->Instance != TIM3) {
      return;
     }
    //if (set == 0) {//雪糕棒保持水平
      if (Count1++ >= 40)//每40ms一次
      {
        Count1 = 0;
        angle.actual = ins_data()->roll;
        PID_Update(&angle);
        if(angle.errorint < -500) {angle.errorint = -500;}
        if(angle.errorint >  500) {angle.errorint =  500;}
        //防止速度过小，导致pwm过小，电机转不起来
        if (angle.out >  0.1 && angle.out <  5) angle.out =  5;
        if (angle.out < -0.1 && angle.out > -5) angle.out = -5;
        speed.target = angle.out;
      }
      if (Count2++ >= 40)//每40ms一次
      {
        Count2 = 0;
        Speed = __HAL_TIM_GET_COUNTER(&htim1);//只记录一轮的数
        __HAL_TIM_SET_COUNTER(&htim1, 0);
        speed.actual = Speed*100.0 / SPEED_FULL_SCALE;
        PID_Update(&speed);
        if(speed.errorint < -500) {speed.errorint = -500;}
        if(speed.errorint >  500) {speed.errorint =  500;}
      }
      if (speed.target == 0) {speed.errorint = 0;}
      if (speed.out >  0.1 && speed.out <  10) {speed.out =  10;}
      if (speed.out < -0.1 && speed.out > -10) {speed.out = -10;}
      Motor_Set(speed.out);
    //}
    // if (set == 1) {//本来想着反过来电机保持水平，暂时还没搞明白，先留着
    //   if (++Count1 >= 40)//每40ms一次
    //   {
    //     Count1 = 0;
    //     place.target = ins_data()->roll / 360 * 540;
    //     place.actual = __HAL_TIM_GET_COUNTER(&htim1) - 500;            
    //     PID_Update(&place);
    //     if(place.errorint < -500) {place.errorint = -500;}
    //     if(place.errorint >  500) {place.errorint =  500;}
    //     //防止速度过小，导致pwm过小，电机转不起来
    //     if (place.out >  0.1 && place.out <  5) place.out =  5;
    //     if (place.out < -0.1 && place.out > -5) place.out = -5;
    //     speed.target = place.out;
    //   }
    //   if (++Count2 >= 40)//每40ms一次
    //   {
    //     Count2 = 0;
    //     difference = __HAL_TIM_GET_COUNTER(&htim1) - Speed - 500;
    //     Speed = __HAL_TIM_GET_COUNTER(&htim1) - 500;
    //     //__HAL_TIM_SET_COUNTER(&htim1, 0);
    //     speed.actual = difference * 100.0 / SPEED_FULL_SCALE;
    //     PID_Update(&speed);
    //     if(speed.errorint < -500) {speed.errorint = -500;}
    //     if(speed.errorint >  500) {speed.errorint =  500;}
    //   }
    //   if (speed.target == 0) {speed.errorint = 0;}
    //   if (speed.out >  0.1 && speed.out <  10) {speed.out =  10;}
    //   if (speed.out < -0.1 && speed.out > -10) {speed.out = -10;}
    //   Motor_Set(speed.out);
    //   if (place.error0 > -5 && place.error0 < 5)   __HAL_TIM_SET_COUNTER(&htim1, 0);
    // }
 }
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
