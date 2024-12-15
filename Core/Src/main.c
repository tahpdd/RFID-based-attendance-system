/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include <stdio.h>
#include "stm32f4xx.h"
#include "sdram_cfg.h"
#include "ltdc_cfg.h"
#include "drawing.h"
#include "clock_cfg.h"
#include "spi_cfg.h"
#include "ili9341.h"
#include "string.h"

#include "ds1307_for_stm32_hal.h"
#include "rc522.h"
#include "flash_mem.h"
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
uint8_t status;
uint8_t str[MAX_LEN]; // Max_LEN = 16
uint8_t sNum[5];
#define NextPg 	100
#define PrevPg 	101
#define ScanID 	102
#define Reset 	103
#define None 	104
#define Test	105
#define End		106

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int Npage = 0, Ppage = 0, state = ScanID, endScan = 0;
const char *DAYS_OF_WEEK[7] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
uint8_t keyG = 0, keyB = 0, keyY = 0, keyR = 0;
struct Student {
    uint8_t order;
	char ID[10];
	char name[30];
	char time[50];
	uint32_t addr;
};
struct Page {
	uint8_t size;
	struct Student student[6];
};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_2)
    {
    	if (keyG == 0) {
    		keyG = 1;
    	} else {
    		keyG = 0;
    		state = NextPg;
    	}
    }
    if (GPIO_Pin == GPIO_PIN_12)
    {
    	if (keyB == 0) {
    		keyB = 1;
    	} else {
    		keyB = 0;
    		state = PrevPg;
    	}
    }
    if (GPIO_Pin == GPIO_PIN_0)
    {
    	if (keyY == 0) {
    		keyY = 1;
    	} else {
    		keyY = 0;
    		state = Reset;
    	}
    }
}
void Set_Time() {
	DS1307_SetTimeZone(+7, 00);
	DS1307_SetDate(11);
	DS1307_SetMonth(12);
	DS1307_SetYear(2024);
	DS1307_SetDayOfWeek(3);
	DS1307_SetHour(23);
	DS1307_SetMinute(15);
	DS1307_SetSecond(01);
}

void UI_Init(uint8_t page, uint8_t size) {
	Fill_Black(0, LCD_ACTIVE_WIDTH, 0, LCD_ACTIVE_HEIGHT);
	char buffer[50];
	Draw_String(30, 10, "CLASS: CE224.P14", COLOR_WHITE, COLOR_BLACK);
	sprintf(buffer, "SS: %d/53", size);
	Draw_String(150, 10, buffer, COLOR_WHITE, COLOR_BLACK);
	//Draw_String(150, 10, "SS: 0/53", COLOR_WHITE, COLOR_BLACK);
	for (uint16_t x = 0; x < LCD_ACTIVE_WIDTH; x++) {
		Draw_Pixel(x, 20, COLOR_WHITE);
	}
	for (uint16_t y = 0; y < 308; y++) {
		Draw_Pixel(20, y, COLOR_WHITE);
	}
	uint16_t ty = 20;
	while (ty != 356)
	{
		for (uint16_t x = 0; x < LCD_ACTIVE_WIDTH; x++) {
			Draw_Pixel(x, ty, COLOR_WHITE);
		}
		ty = ty + 48;
	}
	sprintf(buffer, "- PAGE %d -", page);
	Draw_String(90,311, buffer, COLOR_WHITE, COLOR_BLACK);
}
void New_Page_Init(uint8_t page) {
	uint16_t sy = 21, ey = 63;
	uint16_t sy2 = 44, ey2 = 54;
	Fill_Black(30, 180, sy, ey);
	Fill_Black(0, 15, sy2, ey2);
	Fill_Black(30, 180, sy+=48, ey+=48);
	Fill_Black(0, 15, sy2+=48, ey2+=48);
	Fill_Black(30, 180, sy+=48, ey+=48);
	Fill_Black(0, 15, sy2+=48, ey2+=48);
	Fill_Black(30, 180, sy+=48, ey+=48);
	Fill_Black(0, 15, sy2+=48, ey2+=48);
	Fill_Black(30, 180, sy+=48, ey+=48);
	Fill_Black(0, 15, sy2+=48, ey2+=48);
	Fill_Black(30, 180, sy+=48, ey+=48);
	Fill_Black(0, 15, sy2+=48, ey2+=48);
	Fill_Black(90, 140, 311, 320);
	char buffer[50];
	sprintf(buffer, "- PAGE %d -", page);
	Draw_String(90, 311, buffer, COLOR_WHITE, COLOR_BLACK);
}
void printStudent(struct Page* p, uint8_t page, uint8_t order) {
	uint16_t ty1 = 32 + (48 * order);
	uint16_t ty2 = 44 + (48 * order);
	uint16_t ty3 = 56 + (48 * order);
	char buffer[50];
	sprintf(buffer, "%d", p[page].student[order].order);
	if (p[page].student[order].order >= 10) {
		Draw_String(3, ty2, buffer, COLOR_WHITE, COLOR_BLACK);
	}
	else {
		Draw_String(7, ty2, buffer, COLOR_WHITE, COLOR_BLACK);
	}
	Draw_String(30, ty1, "AAAAA AAAAA AAAAA AAAAA", COLOR_WHITE, COLOR_BLACK);


	sprintf(buffer, "MSSV: %s", p[page].student[order].ID);
	Draw_String(30, ty2, buffer, COLOR_WHITE, COLOR_BLACK);

	Draw_String(30, ty3, p[page].student[order].time, COLOR_WHITE, COLOR_BLACK);
}
void Print_Students_InPg(struct Page* p, uint8_t page, uint8_t size) {
	for (int i = 0; i < size; i++) {
		printStudent(p, page, i);
	}
}
void Get_Time(char* buffer) {
	uint8_t  date   = DS1307_GetDate();
	uint8_t  month  = DS1307_GetMonth();
	uint16_t year   = DS1307_GetYear();
	uint8_t  dow    = DS1307_GetDayOfWeek();
	uint8_t  hour   = DS1307_GetHour();
	uint8_t  minute = DS1307_GetMinute();
	uint8_t  second = DS1307_GetSecond();
	sprintf(buffer, "%02d:%02d:%02d - %02d/%02d/%04d - %s\n",
			hour, minute, second, date, month, year, DAYS_OF_WEEK[dow]);
}

void Address_Init(struct Page* p, uint8_t page) {
	uint32_t a = 0x080E0000;
	uint8_t order = 0;
	for (int i = 1; i <= page; i++) {
		for (int j = 0; j < 6; j++) {
			a = a + 0x50;
			p[i].student[j].addr = a;
			order++;
			p[i].student[j].order = order;
		}
	}
}
void New_SS(uint8_t size) {
	char buffer[20];
	sprintf(buffer, "SS: %d/53", size);
	Draw_String(150, 10, buffer, COLOR_WHITE, COLOR_BLACK);
}
uint8_t isDuplicateID(struct Page* p, uint8_t currentPage, uint8_t currentSize, const char* newID)
{
	if (currentPage == 1 && currentSize == 0) return 0;
    for (uint8_t page = 1; page <= currentPage; page++) {
        uint8_t maxStudents = (page == currentPage) ? currentSize : 6;
        for (uint8_t i = 0; i < maxStudents; i++) {
            if (strcmp(p[page].student[i].ID, newID) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
    //Clock_Init();

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  PLLSAI_Init();
  SysTick_Config(1800);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_SPI4_Init();
  MX_I2C3_Init();
  /* USER CODE BEGIN 2 */
  MFRC522_Init();
  SDRAM_IO_Init();
  SDRAM_Init();
  LTDC_IO_Init();
  LTDC_Core_Init();
  SPI5_IO_Init();
  SPI5_Core_Init();
  ili9341_IO_Init();
  ili9341_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  char buffer[50], buffer2[50];
  //char buffer1[50], buffer3[50], buffer4[50];
  uint8_t currentPage = 1, currentSize = 0, totalSize = 0, totalPage = 1;
  //UI_Init(currentPage, currentSize);
  struct Page page[12];
  DS1307_Init(&hi2c3);
  Address_Init(page, 10);


  //Flash_Erase_Sector11();
  for (int i = 1; i <= 10; i++) {
	  for (int j = 0; j < 6; j++) {
		  if (Flash_Read_CharArr(buffer2, page[i].student[j].addr) == 0) {
			  break;
		  }
		  strcpy(page[i].student[j].ID, buffer2);
		  if (Flash_Read_CharArr(buffer2, page[i].student[j].addr + 0x30) == 0) {
			  break;
		  }
		  strcpy(page[i].student[j].time, buffer2);
		  currentSize = j + 1;
		  totalSize++;
		  currentPage = i;
		  totalPage = i;
	  }
  }
  if (currentPage >= 1 && currentSize != 0) {
	  UI_Init(currentPage, totalSize);
	  Print_Students_InPg(page, currentPage, currentSize);
  }
  else {
	  currentPage = 1, currentSize = 0, totalSize = 0, totalPage = 1;
	  UI_Init(currentPage, totalSize);
	  //Print_Students_InPg(page, currentPage, currentSize);
  }
  //__disable_irq();
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		switch (state) {
		case NextPg:
			__disable_irq();
			if (totalPage == 1) {
				state = ScanID;
				__enable_irq();
				break;
			}
			Npage++;
			if (Npage == currentPage) {
				state = ScanID;
				UI_Init(Npage, totalSize);
				Print_Students_InPg(page, Npage, currentSize);
			} else {
				if (Npage > currentPage) {
					Npage = 1;
				}
				UI_Init(Npage, totalSize);
				Print_Students_InPg(page, Npage, 6);
				state = None;
			}
			Ppage = Npage;
			__enable_irq();
			break;
		case PrevPg:
			__disable_irq();
			if (totalPage == 1) {
				state = ScanID;
				__enable_irq();
				break;
			}
			Ppage--;
			if (Ppage <= 0) {
				Ppage = currentPage;
			}
			if (Ppage == currentPage) {
				state = ScanID;
				UI_Init(Ppage, totalSize);
				Print_Students_InPg(page, Ppage, currentSize);
			} else {
				UI_Init(Ppage, totalSize);
				Print_Students_InPg(page, Ppage, 6);
				state = None;
			}
			Npage = Ppage;
			__enable_irq();
			break;
		case ScanID:
			MFRC522_Request(PICC_REQIDL, str);
			status = MFRC522_Anticoll(str);
			if (status == MI_OK)
			{
				sprintf(buffer, "%X%X%X%X", str[0], str[1], str[2], str[3]);
				if (isDuplicateID(page, totalPage, currentSize, buffer) == 1) {
					break;
				}
				//__disable_irq();
				if (currentSize == 6) {
					currentPage++;
					totalPage++;
					Npage = currentPage;
					Ppage = currentPage;
					currentSize = 0;
					UI_Init(currentPage, totalSize);
				}
				//page[currentPage].student[currentSize].order = totalSize + 1;
				strcpy(page[currentPage].student[currentSize].ID, buffer);
				Flash_Write_CharArr(buffer, page[currentPage].student[currentSize].addr);

				Get_Time(buffer);
				strcpy(page[currentPage].student[currentSize].time, buffer);
				Flash_Write_CharArr(buffer, page[currentPage].student[currentSize].addr + 0x30);
				printStudent(page, currentPage, currentSize);
				currentSize++;
				totalSize++;
				New_SS(totalSize);
				HAL_Delay(30000);
				//__enable_irq();
				//HAL_Delay(15000);
			}
			break;
		case Reset:

			HAL_Delay(5000);
			Flash_Erase_Sector11();
			HAL_Delay(5000);
			Fill_Black(0, LCD_ACTIVE_WIDTH, 0, LCD_ACTIVE_HEIGHT);
			currentPage = 1, currentSize = 0, totalSize = 0, totalPage = 1;
			UI_Init(currentPage, totalSize);
			state = ScanID;

			break;
		case End:

			break;
		default:
			break;
		}
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
