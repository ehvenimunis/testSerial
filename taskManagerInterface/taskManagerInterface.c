/*
 * taskManagerInterface.c
 *
 *  Created on: Feb 25, 2021
 *      Author: neset
 */

#include "taskManagerInterface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "motorDriverInterface.h"
#include "analogValuesController.h"
#include "buttonController.h"
#include "lcdDriverInterface.h"
#include "ComputerInterface.h"



void sendDataUart1Task(void *params);
void sendDataUart2Task(void *params);
void getDataUart1Task(void *params);
void getDataUart2Task(void *params);
void adcReadTask(void *params);
void lcdTask(void *params);
void buttonControlTask(void *params);

void sendDataUartComputerTask(void *params);
void getDataUartComputerTask(void *params);

xSemaphoreHandle uart1SemphrHandle=NULL;
xSemaphoreHandle uart2SemphrHandle=NULL;
xSemaphoreHandle uart3SemphrHandle=NULL;
void tasks_init(void){
	/* xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask)
	 * @param pxTaskCode-> function name
	 * @param pcName-> task name (string)
	 * @param usStackDepth-> stack size
	 * @param pvParameters-> function parameters
	 * @param uxPriority -> Priority
	 * @param pxCreatedTask -> handle so id
	 * */
	vSemaphoreCreateBinary(uart1SemphrHandle);
	vSemaphoreCreateBinary(uart2SemphrHandle);
	vSemaphoreCreateBinary(uart3SemphrHandle);


	if(uart1SemphrHandle!=NULL && uart2SemphrHandle!=NULL && uart3SemphrHandle!=NULL){

		xTaskCreate(sendDataUartComputerTask, "send Uart C", configMINIMAL_STACK_SIZE*2, NULL,  55 , NULL);
		xTaskCreate(getDataUartComputerTask, "get Uart C", configMINIMAL_STACK_SIZE*2, NULL,  55 , NULL);
		xTaskCreate(sendDataUart1Task, "send Uart 1", configMINIMAL_STACK_SIZE, NULL,  55 , NULL);
		xTaskCreate(sendDataUart2Task, "send Uart 2", configMINIMAL_STACK_SIZE, NULL,  55 , NULL);
		xTaskCreate(getDataUart1Task, "get Uart 1", configMINIMAL_STACK_SIZE, NULL,  55, NULL);
		xTaskCreate(getDataUart2Task, "get Uart 2", configMINIMAL_STACK_SIZE, NULL,  55 , NULL);
		xTaskCreate(adcReadTask, "adc read", configMINIMAL_STACK_SIZE, NULL,   55, NULL);
		xTaskCreate(lcdTask, "lcd controller", configMINIMAL_STACK_SIZE*2, NULL,  55 , NULL);
		xTaskCreate(buttonControlTask, "button controller", configMINIMAL_STACK_SIZE*2, NULL,  55 , NULL);



		vTaskStartScheduler();
	}
}


void sendDataUartComputerTask(void *params){
	//uint8_t batt;
	while(1){
		testCIsend();
		//batt=rand()%1;
		//CI_sendDataChannel(0x11,1,1,1,90);

		}
}
void getDataUartComputerTask(void *params){
	while(1){
		xSemaphoreTake(uart3SemphrHandle, portMAX_DELAY);
		CI_enableGetDataChannel();
		xSemaphoreGive(uart3SemphrHandle);

	}
}
void sendDataUart1Task(void *params){

	while(1){
			transmissionDriver1();

	}
}
void sendDataUart2Task(void *params){
	while(1){
			transmissionDriver2();
	}
}
void getDataUart1Task(void *params){
	while(1){
		xSemaphoreTake(uart1SemphrHandle, portMAX_DELAY);
		MDI_enableGetDataChannel1();
		xSemaphoreGive(uart1SemphrHandle);

	}
}
void getDataUart2Task(void *params){
	while(1){
		xSemaphoreTake(uart2SemphrHandle, portMAX_DELAY);
		MDI_enableGetDataChannel2();
		xSemaphoreGive(uart2SemphrHandle);
	}
}
void adcReadTask(void *params){
	uint16_t val1,val2;
	while(1){
		readAnalog2Values(&ADCREADCH1,&ADCREADCH2);
			val1=valuesMap(getAnalogValue1(),0,4095,140,860);
			setDriver1AngleValue(val1);
			vTaskDelay(10);
			val2=valuesMap(getAnalogValue2(),0,4095,140,860);
			setDriver2AngleValue(val2);
			vTaskDelay(10);
	}
}
void lcdTask(void *params){
	lcd_Init();
	while(1){
	  	lcdController();
	  	vTaskDelay(200);
	  	cleanTheLcd();
	  	vTaskDelay(5);
	}

}
void buttonControlTask(void *params){
	btnParameterInit();
	while(1){
		buttonController();
		vTaskDelay(50);
	}
}

