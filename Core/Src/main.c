/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LEDConfig.h"
#include "TempSensorConfig.h"
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
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim15;

/* USER CODE BEGIN PV */
uint8_t g_u8LedCallGreenData = 0;
uint8_t g_u8LedRespGreenData = 0;
uint8_t g_u8LedCallRedData = 0;
uint8_t g_u8LedRespRedData = 0;

//uint8_t g_u8AllLedCallGreenData = 0;
//uint8_t g_u8AllLedRespGreenData = 0;
//uint8_t g_u8AllLedCallRedData = 0;
//uint8_t g_u8AllLedRespRedData = 0;

uint8_t g_u8ActiveRow = 0;
uint8_t g_u8ActiveRowColor = 1;
uint8_t g_u8ActiveLed = 0;
uint8_t g_u8StepNumber = 0;
uint8_t g_u8CallLineNumber = 0;
uint8_t g_u8ResponseLineNumber = 0;

/*поменять на ноль если режим мигание и потом все горят сразу и снова мигание*/
//uint8_t g_u8AllLinesUnicolor = 4;
uint8_t g_u8ChangeColor = 1;
//uint8_t g_u8DisplayAllLinesUnicolor = 0;
uint8_t g_u8ColumnGreen = 0b00000000;
uint8_t g_u8ColumnRed = 0b00000000;

uint8_t g_u8NeedToDisplayLedData = 0;
//uint8_t g_u8NeedToDefineLedGreenData = 0;
//uint8_t g_u8NeedToDefineLedRedData = 0;
//uint8_t g_u8NeedToDefineLedNothingData = 0;
/*далее обнулить и единичить по таймеру 10-100кгц*/
uint8_t g_u8RingDataReadyToReadFlag = 0;
uint16_t g_u16TimeCounter = 0;
uint8_t g_u8CallWireStep = 0;
uint8_t g_u8NeedToAnalyzeCableDataFlag = 0;

RCC_ClkInitTypeDef sClokConfig;
uint16_t g_u16PrescalerHtim3;
uint16_t g_u16PrescalerHtim6;
uint16_t g_u16Prescalerhtim15;
uint32_t g_u32frequencyTim;
uint32_t g_u32TimePeriodCallRespLed = 0;
uint16_t g_u16TimePeriodTempSensor = 0;
uint16_t g_u16TimePeriodRingLine = 0;
uint16_t g_u16TimePeriodStartIndication = 0;

uint32_t g_u32DebugTimeBegin;
uint32_t g_u32DebugTimeEnd;
uint32_t g_u32DebugTimeDifference;

//uint8_t g_u8CallData = 0b10000000;
uint8_t g_u8ActiveWireCheck = 0;
//uint8_t g_u8CallDataMemory = 0;
uint8_t g_u8SummResponsesWire = 0;
uint8_t g_u8SummResponsesArray = 0;
uint8_t g_u8CounterUnitsDigits = 0;
uint8_t g_u8StartIndicationFlag = 1;
uint8_t g_u8NeedToDisplayStartLedData = 0;


//uint32_t uwTick;


uint8_t g_au8ResponsesData [NUMBER_OF_LINES][NUMBER_OF_LINES] = {
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}};

uint8_t g_au8GreenCalls[NUMBER_OF_LINES] = {
		CALL_GREEN_LED_8_POS,
		CALL_GREEN_LED_7_POS,
		CALL_GREEN_LED_6_POS,
		CALL_GREEN_LED_5_POS,
		CALL_GREEN_LED_4_POS,
		CALL_GREEN_LED_3_POS,
		CALL_GREEN_LED_2_POS,
		CALL_GREEN_LED_1_POS};

uint8_t g_au8GreenResponses[NUMBER_OF_LINES] = {
		RESP_GREEN_LED_8_POS,
		RESP_GREEN_LED_7_POS,
		RESP_GREEN_LED_6_POS,
		RESP_GREEN_LED_5_POS,
		RESP_GREEN_LED_4_POS,
		RESP_GREEN_LED_3_POS,
		RESP_GREEN_LED_2_POS,
		RESP_GREEN_LED_1_POS};

uint8_t g_au8RedCalls[NUMBER_OF_LINES] = {
		CALL_RED_LED_8_POS,
		CALL_RED_LED_7_POS,
		CALL_RED_LED_6_POS,
		CALL_RED_LED_5_POS,
		CALL_RED_LED_4_POS,
		CALL_RED_LED_3_POS,
		CALL_RED_LED_2_POS,
		CALL_RED_LED_1_POS};

uint8_t g_au8RedResponses[NUMBER_OF_LINES] = {
		RESP_RED_LED_8_POS,
		RESP_RED_LED_7_POS,
		RESP_RED_LED_6_POS,
		RESP_RED_LED_5_POS,
		RESP_RED_LED_4_POS,
		RESP_RED_LED_3_POS,
		RESP_RED_LED_2_POS,
		RESP_RED_LED_1_POS};


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM15_Init(void);
/* USER CODE BEGIN PFP */
void clearLedSr(void);
void loadLedSr(void);
void changeColorLedSr(void);
void changeRowLedSr(void);
void clearCallSr(void);
void usDelay(uint16_t u16useconds);
void readResponsesSr(void);
void analyzeCableData(void);
void startIndicationLeds(void);

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
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_TIM15_Init();
  /* USER CODE BEGIN 2 */

    //Установить все линии в первоначальное положение светодиодов
    HAL_GPIO_WritePin(STP_SR_LED_nCLR_GPIO_Port, STP_SR_LED_nCLR_Pin,
    		GPIO_PIN_SET);
    HAL_GPIO_WritePin(STP_SR_LED_CLK_GPIO_Port, STP_SR_LED_CLK_Pin,
    		GPIO_PIN_RESET);
    //Установить все линии в первоначальное положение прозвонки и чтения
    HAL_GPIO_WritePin(LINE_CALL_SR_CLK_GPIO_Port, LINE_CALL_SR_CLK_Pin,
    		GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LINE_RESPONSE_SR_CLK_GPIO_Port, LINE_RESPONSE_SR_CLK_Pin,
    		GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LINE_CALL_SR_nCLR_GPIO_Port, LINE_CALL_SR_nCLR_Pin,
    		GPIO_PIN_SET);
    HAL_GPIO_WritePin(LINE_RESPONSE_SR_SHnLD_GPIO_Port, LINE_RESPONSE_SR_SHnLD_Pin,
    		GPIO_PIN_SET);

    clearLedSr();
    clearCallSr();

    // Запустить таймер
    if (USE_TIMER) {
        HAL_TIM_Base_Start_IT(&htim3);
        HAL_TIM_Base_Start_IT(&htim6);
        HAL_TIM_Base_Start_IT(&htim15);

    }

    /*TIME SETTINGS*/

    g_u32frequencyTim = HAL_RCC_GetPCLK1Freq();
    g_u16PrescalerHtim3 = htim3.Init.Prescaler;
    g_u16PrescalerHtim6 = htim6.Init.Prescaler;
    g_u16Prescalerhtim15 = htim15.Init.Prescaler;

    /*TIME SETTINGS FOR CALL-RESP LEDs*/

 /*   g_u32TimePeriodCallRespLed = ((g_u32frequencyTim * TIME_BLINKING_LED_MS) /
    		((g_u32Prescaler + 1) * 1000)) - 1;
    __HAL_TIM_SET_AUTORELOAD(&htim3, g_u32TimePeriodCallRespLed); */

    /*TIME SETTINGS FOR TEMP SENSOR*/

    g_u16TimePeriodTempSensor = ((g_u32frequencyTim) / ((g_u16PrescalerHtim3 + 1) *
    		1000)) * ((uint16_t)PERIOD_OF_BLINKING_TEMP_SENSOR_LED_MS / 2);
    __HAL_TIM_SET_AUTORELOAD(&htim3, g_u16TimePeriodTempSensor);

    /*TIME SETTINGS FOR CHECK LINE*/

    g_u16TimePeriodRingLine = ((g_u32frequencyTim) / ((g_u16PrescalerHtim6 + 1) *
    		1000 * 1000)) * ((uint16_t)PERIOD_OF_RINGING_LINE_US);
    __HAL_TIM_SET_AUTORELOAD(&htim6, g_u16TimePeriodRingLine);

    /*TIME SETTINGS FOR START INDICATION*/

    g_u16TimePeriodStartIndication = ((g_u32frequencyTim) / ((g_u16Prescalerhtim15 + 1) *
    		1000)) * ((uint16_t)TIME_BLINKING_LED_MS);
    __HAL_TIM_SET_AUTORELOAD(&htim15, g_u16TimePeriodStartIndication);

    /*START SETTINGS FOR TS*2*/

//	HAL_GPIO_WritePin(Temp_sensor_cable_RED_LED_GPIO_Port,
//			Temp_sensor_cable_RED_LED_Pin, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    while (1)
    {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    		/*ringing of lines*/
    		/*хочу чтобы 01111111 прошёл поочерёдно по 8 линиям и
    		 	 	 * результат записался в двумерный массив*/
    	/*вставить мультик и сделать флаг на запись таймера как только в ответе хоть где-то единица*/

    	if (g_u8StartIndicationFlag) {
    		startIndicationLeds ();
    		//g_u8StartIndicationFlag = 0;
    	}
    	if (!USE_TIMER) {
    		g_u8NeedToDisplayStartLedData = 1;
    	}
    	if (g_u8NeedToDisplayStartLedData) {
        	clearLedSr();
        	loadLedSr();
    		g_u8ActiveLed++;
    		if (g_u8ActiveLed == NUMBER_OF_LEDS) {
    			g_u8ActiveRowColor++;
    			g_u8ActiveLed = 0;
    			if (g_u8ActiveRowColor == NUMBER_OF_COLORS) {
    				g_u8ActiveRowColor = 1;
    			}
    		}
    		if (g_u8ActiveRow == NUMBER_OF_LINES) {
    			g_u8ActiveRow = 0;
    		}
    		g_u8ActiveRow++;
    		g_u8NeedToDisplayStartLedData = 0;
    	}

        if (g_u8RingDataReadyToReadFlag) {
        	readResponsesSr();
	        g_u8RingDataReadyToReadFlag = 0;
        }

        if (g_u8NeedToAnalyzeCableDataFlag) {
        	analyzeCableData();
        	g_u8NeedToAnalyzeCableDataFlag = 0;
        }
        if (g_u8NeedToDisplayLedData) {
        	clearLedSr();
        	loadLedSr();
        	g_u8NeedToDisplayLedData = 0;
        }

        //перевернуть запись с 1 на ноль - сделано
        //тогда суммарно будет работать
        //переключение с мультика на отображение засчет суммы массива больше 1

        /* data processing */
        //хочу чтобы двумерный массив обработался и
        //на основе обработки сгенерировались данные для отображения
        //сформировали что отобразить
        /****************************************************/

//        if (g_u8StepNumber == 0) {
//
//            if (g_u8ActiveRowColor == GREEN_COLOR) {
//                if ((g_u8ActiveLed >= 0) && (g_u8ActiveLed < NUMBER_OF_LEDS / 2)) {
//		            g_u8LedCallGreenData = (LED_ON << g_au8GreenCalls[g_u8ActiveRow]);
//                    g_u8LedCallRedData = LED_OFF;
//		        }
//                if ((g_u8ActiveLed >= NUMBER_OF_LEDS / 2) &&
//                		(g_u8ActiveLed < NUMBER_OF_LEDS)) {
//                	g_u8LedRespGreenData = (LED_ON <<
//                			g_au8GreenResponses[NUMBER_OF_LINES - g_u8ActiveRow - 1]);
//                	g_u8LedRespRedData = LED_OFF;
//                }
//            }
//
//            if (g_u8ActiveRowColor == RED_COLOR) {
//            	if ((g_u8ActiveLed >= 0) && (g_u8ActiveLed < NUMBER_OF_LEDS / 2)) {
//            		g_u8LedCallRedData = LED_ON << g_au8RedCalls[g_u8ActiveRow];
//            		g_u8LedCallGreenData = LED_OFF;
//            	}
//            	if ((g_u8ActiveLed >= NUMBER_OF_LEDS / 2) &&
//            			(g_u8ActiveLed < NUMBER_OF_LEDS)) {
//            		g_u8LedRespRedData = LED_ON <<
//            				g_au8RedResponses[NUMBER_OF_LINES - g_u8ActiveRow - 1];
//            		g_u8LedRespGreenData = LED_OFF;
//            	}
//            }
//
//            if (g_u8ActiveRowColor == YELLOW_COLOR) {
//            	if ((g_u8ActiveLed >= 0) && (g_u8ActiveLed < NUMBER_OF_LEDS / 2)) {
//            		g_u8LedCallGreenData = LED_ON << g_au8GreenCalls[g_u8ActiveRow];
//            		g_u8LedCallRedData = LED_ON << g_au8RedCalls[g_u8ActiveRow];
//            	}
//            	if ((g_u8ActiveLed >= NUMBER_OF_LEDS / 2) &&
//            			(g_u8ActiveLed < NUMBER_OF_LEDS)) {
//            		g_u8LedRespGreenData = LED_ON <<
//            				g_au8GreenResponses[NUMBER_OF_LINES - g_u8ActiveRow - 1];
//            		g_u8LedRespRedData = LED_ON <<
//            				g_au8RedResponses[NUMBER_OF_LINES - g_u8ActiveRow - 1];
//            	}
//            }
//        }
//
//        if (g_u8StepNumber != 0) {
        /**********************************************************************/

        	/*для того, чтобы осталось перемигиваться раскомментить*/

	  /*g_u8BinaryGreen = g_u8BinaryGreen | (SR_DATA_bm << g_au8GreenCalls
        	[NUMBER_OF_LINES - g_u8StepNumber]);*/

	 /* g_u8BinaryRed = g_u8BinaryRed | (SR_DATA_bm << g_au8RedCalls
        	[NUMBER_OF_LINES - g_u8StepNumber]);*/

//        	if (g_u8ActiveRowColor == GREEN_COLOR) {
//
//        		g_u8LedCallGreenData = (LED_ON << g_au8GreenCalls[g_u8ActiveRow]) |
//        				(g_u8ColumnGreen);
//        		g_u8LedRespGreenData = (LED_ON << g_au8GreenResponses
//        				[NUMBER_OF_LINES - g_u8ActiveRow]) | (g_u8ColumnGreen);
//			  	g_u8LedCallRedData = LED_OFF /*| (g_u8BinaryRed)*/;
//			  	g_u8LedRespRedData = LED_OFF /*| (g_u8BinaryRed)*/;
//        	}
//        	if (g_u8ActiveRowColor == RED_COLOR) {
//
//        		g_u8LedCallRedData = (LED_ON << g_au8RedCalls[g_u8ActiveRow]) |
//        				(g_u8ColumnRed);
//        		g_u8LedRespRedData = (LED_ON << g_au8RedResponses
//        				[NUMBER_OF_LINES - g_u8ActiveRow]) | (g_u8ColumnRed);
//        		g_u8LedCallGreenData = LED_OFF /*| (g_u8BinaryGreen)*/;
//        		g_u8LedRespGreenData = LED_OFF /*| (g_u8BinaryGreen)*/;
//        	}
//        }
//
//
//        //отобразили
//
//        if (g_u8NeedToDisplayLedData) {
//        	clearLedSr();
//        	loadLedSr();
//
//
//        	if (USE_TIMER) {
//        		g_u8NeedToDisplayLedData = 0;
//        	}
//        	g_u8ActiveLed++;
//        	if (g_u8ActiveLed == NUMBER_OF_LEDS) {
//        		g_u8ActiveRowColor++;
//        		g_u8ActiveLed = 0;
//        		if (g_u8ActiveRowColor == NUMBER_OF_COLORS) {
//        			g_u8ActiveRowColor = 1;
//
//        		}
//        	}
//		 // g_u8ActiveRow++;
//
//        	if (g_u8ActiveRow/* + g_u8StepNumber */== NUMBER_OF_LINES) {
//        		g_u8ActiveRow = 0;
//			  //g_u8StepNumber++;
//			}
//        	g_u8ActiveRow++;
//        	if (g_u8StepNumber == NUMBER_OF_LINES) {
//				//break;
//        		g_u8StepNumber = 0;
//				g_u8ColumnGreen = 0b00000000;
//				g_u8ColumnRed = 0b00000000;
//        	}
////				g_u8AllLinesUnicolor++;
////			  	if (g_u8AllLinesUnicolor == NUMBER_OF_COLORS) {
////				  	g_u8AllLinesUnicolor = 0;
////			  	}
////			    g_u8DisplayAllLinesUnicolor = 1;
//        }
//
//        if (g_u8AllLinesUnicolor == GREEN_COLOR) {
//
//        	g_u8AllLedCallGreenData = LED_ON;
//        	g_u8AllLedRespGreenData = LED_ON;
//        	g_u8AllLedCallRedData = LED_OFF;
//        	g_u8AllLedRespRedData = LED_OFF;
//        }
//
//        if (g_u8AllLinesUnicolor == RED_COLOR) {
//
//        	g_u8AllLedCallGreenData = LED_OFF;
//        	g_u8AllLedRespGreenData = LED_OFF;
//        	g_u8AllLedCallRedData = LED_ON;
//        	g_u8AllLedRespRedData = LED_ON;
//        }
//
//        if (g_u8AllLinesUnicolor == YELLOW_COLOR) {
//
//        	/*так горит жёлтый, в зависимости от того, что OFF будет другой цвет -
//        	 	 	 * цикл?? условие7??? чтобы по порядку с прерыванием*/
//        	g_u8AllLedCallGreenData = LED_ON;
//        	g_u8AllLedRespGreenData = LED_ON;
//        	g_u8AllLedCallRedData = LED_ON;
//        	g_u8AllLedRespRedData = LED_ON;
//        }
//
//
//        if (g_u8DisplayAllLinesUnicolor) {
//
//        	HAL_GPIO_WritePin(LED_CALL_GREEN_SR_DATA_GPIO_Port,
//        			LED_CALL_GREEN_SR_DATA_Pin, g_u8AllLedCallGreenData);
//        	HAL_GPIO_WritePin(LED_RESP_GREEN_SR_DATA_GPIO_Port,
//        			LED_RESP_GREEN_SR_DATA_Pin, g_u8AllLedRespGreenData);
//        	HAL_GPIO_WritePin(LED_CALL_RED_SR_DATA_GPIO_Port,
//        			LED_CALL_RED_SR_DATA_Pin, g_u8AllLedCallRedData);
//        	HAL_GPIO_WritePin(LED_RESP_RED_SR_DATA_GPIO_Port,
//        			LED_RESP_RED_SR_DATA_Pin, g_u8AllLedRespRedData);
//        	for (uint8_t n = 0; n < NUMBER_OF_LINES; n++) {
//        		HAL_GPIO_WritePin(STP_SR_LED_CLK_GPIO_Port, STP_SR_LED_CLK_Pin,
//        				GPIO_PIN_SET);
//        		HAL_GPIO_WritePin(STP_SR_LED_CLK_GPIO_Port, STP_SR_LED_CLK_Pin,
//        				GPIO_PIN_RESET);
//        	}
//        	g_u8DisplayAllLinesUnicolor = 0;
//        }

//	  if (!USE_TIMER) {
//		  g_u8ActiveRowColor++;
//		  if (g_u8ActiveRowColor == NUMBER_OF_COLORS) {
//			  g_u8ActiveRowColor = 0;
//		  }
//	  }


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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 15999;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 500;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 15;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM15 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM15_Init(void)
{

  /* USER CODE BEGIN TIM15_Init 0 */

  /* USER CODE END TIM15_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM15_Init 1 */

  /* USER CODE END TIM15_Init 1 */
  htim15.Instance = TIM15;
  htim15.Init.Prescaler = 15999;
  htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim15.Init.Period = 500;
  htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim15.Init.RepetitionCounter = 0;
  htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM15_Init 2 */

  /* USER CODE END TIM15_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RESP_RED_SR_DATA_Pin|LED_RESP_GREEN_SR_DATA_Pin|LED_CALL_RED_SR_DATA_Pin|LED_CALL_GREEN_SR_DATA_Pin
                          |STP_SR_LED_nCLR_Pin|STP_SR_LED_CLK_Pin|LINE_RESPONSE_SR_SHnLD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Temp_sensor_cable_RED_LED_Pin|LINE_RESPONSE_SR_CLK_Pin|LINE_CALL_SR_nCLR_Pin|LINE_CALL_SR_CLK_Pin
                          |LINE_CALL_SR_DATA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RESP_RED_SR_DATA_Pin LED_RESP_GREEN_SR_DATA_Pin LED_CALL_RED_SR_DATA_Pin LED_CALL_GREEN_SR_DATA_Pin
                           STP_SR_LED_nCLR_Pin STP_SR_LED_CLK_Pin */
  GPIO_InitStruct.Pin = LED_RESP_RED_SR_DATA_Pin|LED_RESP_GREEN_SR_DATA_Pin|LED_CALL_RED_SR_DATA_Pin|LED_CALL_GREEN_SR_DATA_Pin
                          |STP_SR_LED_nCLR_Pin|STP_SR_LED_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Temp_sensor_cable_RED_LED_Pin LINE_RESPONSE_SR_CLK_Pin LINE_CALL_SR_nCLR_Pin LINE_CALL_SR_CLK_Pin
                           LINE_CALL_SR_DATA_Pin */
  GPIO_InitStruct.Pin = Temp_sensor_cable_RED_LED_Pin|LINE_RESPONSE_SR_CLK_Pin|LINE_CALL_SR_nCLR_Pin|LINE_CALL_SR_CLK_Pin
                          |LINE_CALL_SR_DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LINE_RESPONSE_SR_SHnLD_Pin */
  GPIO_InitStruct.Pin = LINE_RESPONSE_SR_SHnLD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LINE_RESPONSE_SR_SHnLD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LINE_RESPONSE_SR_DATA_Pin */
  GPIO_InitStruct.Pin = LINE_RESPONSE_SR_DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LINE_RESPONSE_SR_DATA_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void clearLedSr(void)
{

	HAL_GPIO_WritePin(STP_SR_LED_nCLR_GPIO_Port, STP_SR_LED_nCLR_Pin,
			GPIO_PIN_RESET);
	HAL_GPIO_WritePin(STP_SR_LED_nCLR_GPIO_Port, STP_SR_LED_nCLR_Pin,
			GPIO_PIN_SET);
}

void loadLedSr(void)
{

	for (uint8_t i = 0; i < NUMBER_OF_LINES; i++) {
        HAL_GPIO_WritePin(LED_CALL_GREEN_SR_DATA_GPIO_Port,
        		LED_CALL_GREEN_SR_DATA_Pin, (g_u8LedCallGreenData & SR_DATA_bm));
		HAL_GPIO_WritePin(LED_RESP_GREEN_SR_DATA_GPIO_Port,
				LED_RESP_GREEN_SR_DATA_Pin, (g_u8LedRespGreenData & SR_DATA_bm));
		HAL_GPIO_WritePin(LED_CALL_RED_SR_DATA_GPIO_Port,
				LED_CALL_RED_SR_DATA_Pin, (g_u8LedCallRedData & SR_DATA_bm));
		HAL_GPIO_WritePin(LED_RESP_RED_SR_DATA_GPIO_Port,
				LED_RESP_RED_SR_DATA_Pin, (g_u8LedRespRedData & SR_DATA_bm));

		HAL_GPIO_WritePin(STP_SR_LED_CLK_GPIO_Port, STP_SR_LED_CLK_Pin,
				GPIO_PIN_SET);
		HAL_GPIO_WritePin(STP_SR_LED_CLK_GPIO_Port, STP_SR_LED_CLK_Pin,
				GPIO_PIN_RESET);

		g_u8LedCallGreenData = g_u8LedCallGreenData >> 1;
		g_u8LedRespGreenData = g_u8LedRespGreenData >> 1;
		g_u8LedCallRedData = g_u8LedCallRedData >> 1;
		g_u8LedRespRedData = g_u8LedRespRedData >> 1;
	}
}

void clearCallSr(void)
{
	HAL_GPIO_WritePin(LINE_CALL_SR_nCLR_GPIO_Port, LINE_CALL_SR_nCLR_Pin,
			GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LINE_CALL_SR_nCLR_GPIO_Port, LINE_CALL_SR_nCLR_Pin,
			GPIO_PIN_SET);
}


void readResponsesSr(void)
{
	HAL_GPIO_WritePin(LINE_RESPONSE_SR_SHnLD_GPIO_Port,
			LINE_RESPONSE_SR_SHnLD_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LINE_RESPONSE_SR_SHnLD_GPIO_Port,
	    	LINE_RESPONSE_SR_SHnLD_Pin, GPIO_PIN_SET);

	for (g_u8ResponseLineNumber = 0; g_u8ResponseLineNumber < NUMBER_OF_LINES;
			g_u8ResponseLineNumber++) {

		HAL_GPIO_WritePin(LINE_RESPONSE_SR_CLK_GPIO_Port,
				LINE_RESPONSE_SR_CLK_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LINE_RESPONSE_SR_CLK_GPIO_Port,
				LINE_RESPONSE_SR_CLK_Pin, GPIO_PIN_RESET);

		if (HAL_GPIO_ReadPin(LINE_RESPONSE_SR_DATA_GPIO_Port,
				LINE_RESPONSE_SR_DATA_Pin)) {
			g_au8ResponsesData[g_u8ActiveWireCheck][g_u8ResponseLineNumber] = WIRE_NACK;
		}
		else {
			g_au8ResponsesData[g_u8ActiveWireCheck][g_u8ResponseLineNumber] = WIRE_ACK;
			HAL_TIM_Base_Stop_IT(&htim15); /*запрещаем стартовую по прерыванию*/
			g_u8StartIndicationFlag = 0;
		}
	}
	HAL_TIM_Base_Stop_IT(&htim6); /*разрешаем прерывания*/
	g_u8NeedToAnalyzeCableDataFlag = 1;
//	g_u8ActiveWireCheck++; /*так знаем какую линию звоним*/ /***переместить в анализ??????????????***/
//	if (g_u8ActiveWireCheck == NUMBER_OF_LINES){
//		g_u8ActiveWireCheck = 0;
//		/*флаг для будущего анализа  + запрет на прерывания*/
//	}
}
// todo: переименовать SR_DATA_bm в MASK_LOW_BIT_UNIT ???????

void analyzeCableData(void)
{
	for (g_u8ResponseLineNumber = 0; g_u8ResponseLineNumber < NUMBER_OF_LINES;
			g_u8ResponseLineNumber++){
		if (g_au8ResponsesData[g_u8ActiveWireCheck][g_u8ResponseLineNumber]) {
			g_u8SummResponsesWire++;
			g_u8SummResponsesArray++;
		}
	}
	if ((g_u8SummResponsesArray == 0) && (g_u8ActiveWireCheck == NUMBER_OF_LINES)) {
		/*включить 15 тим*/
		/*выключить 3 тим*/
		HAL_TIM_Base_Stop_IT(&htim3);
		HAL_TIM_Base_Start_IT(&htim15); /*разрешаем прерывания*/
	}
	if ((g_au8ResponsesData[g_u8ActiveWireCheck][g_u8ActiveWireCheck]) && (g_u8SummResponsesWire = 1)) {
		g_u8LedCallGreenData = g_u8LedCallGreenData | (SR_DATA_bm << g_u8ActiveWireCheck);
		g_u8LedRespGreenData = g_u8LedRespGreenData | (SR_DATA_bm << g_u8ActiveWireCheck);
	}
	else if (g_u8SummResponsesWire == 0) {
		g_u8LedCallRedData = g_u8LedCallRedData | (SR_DATA_bm << g_u8ActiveWireCheck);
		g_u8LedRespRedData = g_u8LedRespRedData | (SR_DATA_bm << g_u8ActiveWireCheck);
	}
	else if ((g_u8SummResponsesWire > 1) && (g_au8ResponsesData[g_u8ActiveWireCheck][g_u8ActiveWireCheck])) {
		g_u8LedCallRedData = g_u8LedCallRedData | (SR_DATA_bm << g_u8ActiveWireCheck);
		g_u8LedRespRedData = g_u8LedRespRedData | (SR_DATA_bm << g_u8ActiveWireCheck);
		g_u8LedCallGreenData = g_u8LedCallGreenData | (SR_DATA_bm << g_u8ActiveWireCheck);
		g_u8LedRespGreenData = g_u8LedRespGreenData | (SR_DATA_bm << g_u8ActiveWireCheck);
		for (g_u8ResponseLineNumber = 0; g_u8ResponseLineNumber < NUMBER_OF_LINES;
				g_u8ResponseLineNumber++){
			if (g_au8ResponsesData[g_u8ActiveWireCheck][g_u8ResponseLineNumber]) {
				g_u8LedRespGreenData = g_u8LedRespGreenData | (SR_DATA_bm << g_u8CounterUnitsDigits);
				g_u8LedRespRedData = g_u8LedRespRedData | (SR_DATA_bm << g_u8CounterUnitsDigits);
			}
			g_u8CounterUnitsDigits++;
		}
	}
	else if ((g_au8ResponsesData[g_u8ActiveWireCheck][g_u8ActiveWireCheck] == 0) && (g_u8SummResponsesWire >= 1)) {
		g_u8LedCallRedData = g_u8LedCallRedData | (SR_DATA_bm << g_u8ActiveWireCheck);
		g_u8LedRespRedData = g_u8LedRespRedData | (SR_DATA_bm << g_u8ActiveWireCheck);
		for (g_u8ResponseLineNumber = 0; g_u8ResponseLineNumber < NUMBER_OF_LINES;
				g_u8ResponseLineNumber++){
			if (g_au8ResponsesData[g_u8ActiveWireCheck][g_u8ResponseLineNumber]) {
				g_u8LedCallGreenData = g_u8LedCallRedData | (SR_DATA_bm << g_u8CounterUnitsDigits);
				g_u8LedRespRedData = g_u8LedRespRedData | (SR_DATA_bm << g_u8CounterUnitsDigits);
				g_u8LedCallGreenData = g_u8LedCallGreenData | (SR_DATA_bm << g_u8ActiveWireCheck);
			}
			g_u8CounterUnitsDigits++;
		}
	}
	g_u8ActiveWireCheck++; /*так знаем какую линию звоним*/
	if (g_u8ActiveWireCheck == NUMBER_OF_LINES){
		g_u8ActiveWireCheck = 0;
		/*запрет на прерывания??*/
		g_u8SummResponsesArray = 0;
	}
	g_u8SummResponsesWire = 0;
	//HAL_TIM_Base_Start_IT(&htim6); /*разрешаем прерывания после того как отобразили первое*/
	HAL_TIM_Base_Start_IT(&htim3);



}

void startIndicationLeds(void)
{
	if (g_u8ActiveRowColor == GREEN_COLOR) {
		if ((g_u8ActiveLed >= 0) && (g_u8ActiveLed < NUMBER_OF_LEDS / 2)) {
			g_u8LedCallGreenData = (LED_ON << g_au8GreenCalls[g_u8ActiveRow]);
			g_u8LedCallRedData = LED_OFF;
		}
		if ((g_u8ActiveLed >= NUMBER_OF_LEDS / 2) && (g_u8ActiveLed < NUMBER_OF_LEDS)) {
			g_u8LedRespGreenData = (LED_ON <<
					g_au8GreenResponses[NUMBER_OF_LINES - g_u8ActiveRow - 1]);
			g_u8LedRespRedData = LED_OFF;
		}
	}

	if (g_u8ActiveRowColor == RED_COLOR) {
		if ((g_u8ActiveLed >= 0) && (g_u8ActiveLed < NUMBER_OF_LEDS / 2)) {
			g_u8LedCallRedData = LED_ON << g_au8RedCalls[g_u8ActiveRow];
			g_u8LedCallGreenData = LED_OFF;
		}
		if ((g_u8ActiveLed >= NUMBER_OF_LEDS / 2) && (g_u8ActiveLed < NUMBER_OF_LEDS)) {
			g_u8LedRespRedData = LED_ON <<
					g_au8RedResponses[NUMBER_OF_LINES - g_u8ActiveRow - 1];
			g_u8LedRespGreenData = LED_OFF;
		}
	}

	if (g_u8ActiveRowColor == YELLOW_COLOR) {
		if ((g_u8ActiveLed >= 0) && (g_u8ActiveLed < NUMBER_OF_LEDS / 2)) {
			g_u8LedCallGreenData = LED_ON << g_au8GreenCalls[g_u8ActiveRow];
			g_u8LedCallRedData = LED_ON << g_au8RedCalls[g_u8ActiveRow];
		}
		if ((g_u8ActiveLed >= NUMBER_OF_LEDS / 2) && (g_u8ActiveLed < NUMBER_OF_LEDS)) {
			g_u8LedRespGreenData = LED_ON <<
					g_au8GreenResponses[NUMBER_OF_LINES - g_u8ActiveRow - 1];
			g_u8LedRespRedData = LED_ON <<
					g_au8RedResponses[NUMBER_OF_LINES - g_u8ActiveRow - 1];
		}
	}
    HAL_TIM_Base_Start_IT(&htim15);
}

void usDelay(uint16_t u16useconds)
{
	//Обнуляем счетчик таймера
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
	//ждем пока счетчик не достигнет заданного времени
	while(__HAL_TIM_GET_COUNTER(&htim6) < u16useconds) {
		//Ставим проверку, если вдруг счетчик переполнится
		if (__HAL_TIM_GET_FLAG(&htim6, TIM_FLAG_UPDATE) != RESET) {
			break;
		}
	}
}

//void ChangeRowLEDSR(void)
//{
//	ActiveRow++;
//		  if (ActiveRow == NUMBER_OF_LINES) {
//			  ActiveRow = 0;
//		  }
//}
//
//void ChangeColorLEDSR(void)
//{
//	ActiveRowColor++;
//	if (ActiveRowColor == NUMBER_OF_COLORS) {
//		ActiveRowColor = 0;
//	}
//}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

//	if (htim == &htim3)
//	{
//		//g_u8NeedToDisplayLedData = 1;
//	HAL_TIM_Base_Start_IT(&htim6); /*разрешаем прерывания после того как отобразили первое*/
//		HAL_GPIO_TogglePin(Temp_sensor_cable_RED_LED_GPIO_Port,
//				Temp_sensor_cable_RED_LED_Pin);
//	}
//
//	if (htim == &htim6)
//	{
//		HAL_GPIO_WritePin(LINE_CALL_SR_DATA_GPIO_Port, LINE_CALL_SR_DATA_Pin,
//				(~(SR_DATA_bm << g_u8ActiveWireCheck) & (SR_DATA_bm << g_u8CallWireStep) ));
//
//		HAL_GPIO_WritePin(LINE_CALL_SR_CLK_GPIO_Port,
//				LINE_CALL_SR_CLK_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(LINE_CALL_SR_CLK_GPIO_Port,
//				LINE_CALL_SR_CLK_Pin, GPIO_PIN_RESET);
//
//		g_u8CallWireStep++; /*считаем позиции регистра*/
//
//		if (g_u8CallWireStep == NUMBER_OF_LINES) {
//			/*разрешаем считывать как выставили 8 позиций в регистре*/
//			g_u8RingDataReadyToReadFlag = 1;
//			g_u8CallWireStep = 0;
//	        HAL_TIM_Base_Stop_IT(&htim6); /*запрещаем прерывания*/
//		}
//	}
	if (htim == &htim15)
	{
		g_u8StartIndicationFlag = 1;
		g_u8NeedToDisplayStartLedData = 1;
		//HAL_TIM_Base_Stop_IT(&htim15); /*запрещаем прерывания*/
	}
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
