/*
 * main.c
 * Author: Huong Dang
 * Date: May 12nd, 2020
 * purpose: Learning using peripheral UART
 * Content: Send character over UART to MCU. MCU convert all lower case
 * into upper case and send it back to user
 *
 */

#include<string.h>
#include "stm32l1xx.h"
#include "main.h"

void SystemClockConfig(void);
void TIMER6_Init(void);
void Error_handler(void);
void GPIO_Init(void);

TIM_HandleTypeDef htimer6;



int main(void)
{
	HAL_Init();
	SystemClockConfig();
	GPIO_Init();

	TIMER6_Init();

	//let's start the timer
	HAL_TIM_Base_Start(&htimer6);




	while(1){
		//loop until the update event flag is set
		while(!(TIM6 -> SR & TIM_SR_UIF)); //when this expression is 0, then the collective result will be 1
		//when we come out of the while loop, that means hundred milliseconds elapsed
		//the required time delay has been elapsed
		TIM6 -> SR = 0;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	}

	while(1);



	return 0;
}


void SystemClockConfig(void)
{


}

void GPIO_Init(void){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &ledgpio);

}


void TIMER6_Init(void){
	htimer6.Instance = TIM6;
	htimer6.Init.Prescaler = 24;
	htimer6.Init.Period = 64000 - 1; //has to be minus 1 because it actually generates 1 more time gap after the requested is meet
	HAL_TIM_Base_Init(&htimer6);

	if(HAL_TIM_Base_Init(&htimer6) != HAL_OK){
		Error_handler();
	}

	//prescaler value is used to slow down the TIM_CLK for example, if TIM_CLK=500MHz and prescaler =1 then TIM_CNT_CLK = TIM_CLK/1+ prescaler =25MHz
}



void Error_handler(void)
{
	while(1);
}


