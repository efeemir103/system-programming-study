/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DAC_HandleTypeDef hdac;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint16_t timeCounter; // Time in milliseconds.
int waveNumber; // sine (0), triangle (1), square (2) waves.
int frequencyOfWave = 1; // Unit in Hz.
int powerOn; // Whether output should be given or not.
int waveButtonPressed; // To debounce wave changing button.
int frequencyButtonPressed; // To debounce frequency changing button.
int powerButtonPressed; // To debounce power button.
double samplingRate = 1000; // The ratio we have to divide by time to get exact time in seconds.
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DAC_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
static double triangle(double t, double frequency);
static double square(double t, double frequency);
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
  MX_DAC_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  timeCounter = 0;
  double amplitude; // Amplitude of wave at the current moment.
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1); // Will use to send analog waves.
  __HAL_UART_ENABLE_IT(&huart2, UART_IT_TC); // Send debug data over UART.
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(waveButtonPressed){
		  HAL_Delay(200); // Debounce button.
		  waveButtonPressed = 0;
		  timeCounter = 0; // Set the time to start.
	  }
	  if(frequencyButtonPressed){
		  HAL_Delay(200); // Debounce button.
		  frequencyButtonPressed = 0;
		  timeCounter = 0; // Set the time to start.
	  }
	  if(powerButtonPressed){
		  HAL_Delay(200); // Debounce button.
		  powerButtonPressed = 0;
		  timeCounter = 0; // Set the time to start.
	  }
	  if(powerOn){ // If power on then you should give corresponding voltage at current time from dac channel 1.
		  if((double)timeCounter / samplingRate >= 1/(double)frequencyOfWave){
			  timeCounter = 0; // If current time greater then or equal to period of wave then time should reset.
		  }
		  switch(waveNumber){ // Handle type of wave to calculate current amplitude (voltage value) of wave.
		  	  case 0:
		  		  // sine wave with dc gain.
		  		  amplitude = 1.65 * sin(2*M_PI*frequencyOfWave*timeCounter / samplingRate) + 1.65;
		  		  break;
		  	  case 1:
		  		  // triangle wave
		  		  amplitude = 3.3 * triangle(2*M_PI*frequencyOfWave*timeCounter / samplingRate, frequencyOfWave);
		  		  break;
		  	  case 2:
		  		  // square wave
		  		  amplitude = 3.3 * square(2*M_PI*frequencyOfWave*timeCounter / samplingRate, frequencyOfWave);
		  		  break;
		  }
		  // Create debug string to send over UART.
		  char info[38];
		  sprintf(info, "At t = %5d, V = %2.2lf, f = %6d\n\r", timeCounter, amplitude, frequencyOfWave); // Please include printf_float formatting in project properties.
		  HAL_UART_Transmit_IT(&huart2, (uint8_t *) info, 38); // Baudrate 115200 bit/s.
		  // Set dac to output here.
		  HAL_DAC_Stop(&hdac, DAC_CHANNEL_1);
		  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
		  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint32_t)(amplitude / 3.3 * 4095)); // Scale the amplitude.
	  }
	  else{
		  HAL_DAC_Stop(&hdac, DAC_CHANNEL_1);
		  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
		  // If power is off then output must be off.
		  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */
  /** DAC Initialization 
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT1 config 
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 2097;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA7 PA8 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */
// Just a easy triangle wave function.
static double triangle(double t, double frequency)
{
	t /= (2 * M_PI * frequency); // Radians to seconds.
	double period = 1 / frequency;
	double res = (t < period / 2) ? 2*t/period : 2*(period - t) / period; // Use slope to find out voltage value.
	return res;
}

// Just a easy square wave function.
static double square(double t, double frequency){
	t /= (2 * M_PI * frequency); // Radians to seconds.
	double period = 1 / frequency;
	return (t < period / 2) ? 0 : 1; // Check if on half period or over.
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_10){ // Button 1
		if(!waveButtonPressed && powerOn){ // If power is on and wave button was pressed for first time then handle it.
				waveButtonPressed = 1; // Button was clicked so lock it.
				switch(waveNumber){ // Handle weave type.
					case 0:
						HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15); // Set green led off.
						HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); // Set yellow led on.
						waveNumber++;
						break;
					case 1:
						HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); // Set yellow led off.
						HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13); // Set red led on.
						waveNumber++;
						break;
					case 2:
						HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13); // Set red led off.
						HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15); // Set green led on.
						waveNumber = 0;
						break;
				}
		}
	}
	if(GPIO_Pin == GPIO_PIN_7){ // Button 2
		if(!frequencyButtonPressed && powerOn){ // If power is on and frequency button was pressed for first time then handle it.
			frequencyButtonPressed = 1; // Button was clicked so lock it.
			frequencyOfWave = (frequencyOfWave == 10) ? 1 : frequencyOfWave+1; // Increment frequency by one every button click unless it is 10 then reset to 1.
		}
	}
	if(GPIO_Pin == GPIO_PIN_8){ // Button 3
		if(!powerButtonPressed){ // If power button was pressed for first time then handle it.
			powerButtonPressed = 1; // Button was clicked so lock it.
			powerOn = !powerOn; // Toggle the button logic.
			switch(waveNumber){ // Find out which led is set then set it off.
				case 0:
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
					break;
				case 1:
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
					break;
				case 2:
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
					break;
			}
		}
	}
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
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

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
