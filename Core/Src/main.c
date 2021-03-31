/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "retarget.h"

#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"
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

/* USER CODE BEGIN PV */

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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  RetargetInit(&huart2);
  printf("lib_vl53l0x\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  VL53L0X_Dev_t dev;
  VL53L0X_DeviceInfo_t VL53L0X_DeviceInfo;
  VL53L0X_RangingMeasurementData_t VL53L0X_RangingMeasurementData;
  uint8_t status = VL53L0X_ERROR_NONE;
  uint8_t data_ready = 0;

  dev.I2cHandle = &hi2c1;
  dev.I2cDevAddr = 0x52;
  dev.comms_speed_khz = 400;
  dev.comms_type = 1;

  VL53L0X_GetDeviceInfo(&dev, &VL53L0X_DeviceInfo);
  printf("Name = %s\r\n",VL53L0X_DeviceInfo.Name);
  printf("Type = %s\r\n",VL53L0X_DeviceInfo.Type);
  printf("ProductId = %s\r\n",VL53L0X_DeviceInfo.ProductId);
  printf("ProductType = %d\r\n",VL53L0X_DeviceInfo.ProductType);
  printf("ProductRevisionMajor = %d\r\n",VL53L0X_DeviceInfo.ProductRevisionMajor);
  printf("ProductRevisionMinor = %d\r\n",VL53L0X_DeviceInfo.ProductRevisionMinor);

  status = VL53L0X_DataInit(&dev);
  printf("DataInit() : %d\r\n",status);

  status = VL53L0X_StaticInit(&dev);
  printf("StaticInit() : %d\r\n",status);

  uint32_t refSpadCount;
  uint8_t isApertureSpads;
  status = VL53L0X_PerformRefSpadManagement(&dev, &refSpadCount, &isApertureSpads);
  printf("PerformRefSpadManagement() : %d\r\n",status);

  int32_t OffsetCalibrationDataMicroMeter = 0;
  status = VL53L0X_SetOffsetCalibrationDataMicroMeter(&dev, OffsetCalibrationDataMicroMeter);
  printf("SetOffsetCalibrationDataMicroMeter() : %d\r\n",status);

  FixPoint1616_t XTalkCompensationRateMegaCps = 0;
  status = VL53L0X_SetXTalkCompensationRateMegaCps(&dev, XTalkCompensationRateMegaCps);
  printf("SetXTalkCompensationRateMegaCps() : %d\r\n",status);

  status = VL53L0X_SetDeviceMode(&dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
  printf("StaticInit() : %d\r\n",status);

  status = VL53L0X_StartMeasurement(&dev);
  printf("StartMeasurement() : %d\r\n",status);

  while (1)
  {
	  do{
		  status = VL53L0X_GetMeasurementDataReady(&dev, &data_ready);
	  } while(data_ready != 1);

	status = VL53L0X_GetRangingMeasurementData(&dev, &VL53L0X_RangingMeasurementData);
	printf("Distance = %d\r\n",VL53L0X_RangingMeasurementData.RangeMilliMeter);

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
