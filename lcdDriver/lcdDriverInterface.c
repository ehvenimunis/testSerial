/*
 * lcdDriverInterface.c
 *
 *  Created on: Feb 23, 2021
 *      Author: neset
 */

#include "lcdDriverInterface.h"
#include "../buttonController/buttonController.h"
char lcdBuff[20];

/* @brief lcd module initalize
 * @param none
 * @return none
 * */
void lcd_Init(void){
	LCD_i2cDeviceCheck(LCD_I2C_CHANNEL1);
	LCD_Init(LCD_I2C_CHANNEL1);
	LCD_BackLight(LCD_I2C_CHANNEL1,LCD_BL_ON);
	LCD_SetCursor(LCD_I2C_CHANNEL1,0,0);

	LCD_Send_String(LCD_I2C_CHANNEL1,"TEST",STR_NOSLIDE);

	LCD_i2cDeviceCheck(LCD_I2C_CHANNEL2);
	LCD_Init(LCD_I2C_CHANNEL2);
	LCD_BackLight(LCD_I2C_CHANNEL2,LCD_BL_ON);
	LCD_SetCursor(LCD_I2C_CHANNEL2,0,0);

	LCD_Send_String(LCD_I2C_CHANNEL1,"TEST",STR_NOSLIDE);

}
void printToLcdDrv1Receive(mD_interface gets,bool isSelected){
	LCD_SetCursor(LCD_I2C_CHANNEL1,1,1);
	if(isSelected)	sprintf(lcdBuff,"-Gln1-a:%03d p:%02x",gets.angle,gets.pid_kp);
	else	sprintf(lcdBuff,"Gln1 a:%03d p:%02x",gets.angle,gets.pid_kp);
	LCD_Send_String(LCD_I2C_CHANNEL1,lcdBuff,STR_NOSLIDE);
	LCD_SetCursor(LCD_I2C_CHANNEL1,2,1);
	sprintf(lcdBuff,"i:%02x d:%02x f:%02x",gets.pid_ki,gets.pid_kd,gets.factor);
	LCD_Send_String(LCD_I2C_CHANNEL1,lcdBuff,STR_NOSLIDE);
}
void printToLcdDrv1Transmit(mD_interface sends,bool isSelected){
	LCD_SetCursor(LCD_I2C_CHANNEL1,1,1);
	if(isSelected)	sprintf(lcdBuff,"-Gdn1-a:%03d p:%02x",sends.angle,sends.pid_kp);
	else sprintf(lcdBuff,"Gdn1 a:%03d p:%02x",sends.angle,sends.pid_kp);
	LCD_Send_String(LCD_I2C_CHANNEL1,lcdBuff,STR_NOSLIDE);
	LCD_SetCursor(LCD_I2C_CHANNEL1,2,1);
	sprintf(lcdBuff,"i:%02x d:%02x f:%02x",sends.pid_ki,sends.pid_kd,sends.factor);
	LCD_Send_String(LCD_I2C_CHANNEL1,lcdBuff,STR_NOSLIDE);
}
void printToLcdDrv2Receive(mD_interface gets,bool isSelected){
	LCD_SetCursor(LCD_I2C_CHANNEL2,1,1);
	if(isSelected)	sprintf(lcdBuff,"-Gln2-a:%03d p:%02x",gets.angle,gets.pid_kp);
	else	sprintf(lcdBuff,"Gln2 a:%03d p:%02x",gets.angle,gets.pid_kp);
	LCD_Send_String(LCD_I2C_CHANNEL2,lcdBuff,STR_NOSLIDE);
	LCD_SetCursor(LCD_I2C_CHANNEL2,2,1);
	sprintf(lcdBuff,"i:%02x d:%02x f:%02x",gets.pid_ki,gets.pid_kd,gets.factor);
	LCD_Send_String(LCD_I2C_CHANNEL2,lcdBuff,STR_NOSLIDE);
}
void printToLcdDrv2Transmit(mD_interface sends,bool isSelected){
	LCD_SetCursor(LCD_I2C_CHANNEL2,1,1);
	if(isSelected)	sprintf(lcdBuff,"-Gdn2-a:%03d p:%02x",sends.angle,sends.pid_kp);
	else	sprintf(lcdBuff,"Gdn2 a:%03d p:%02x",sends.angle,sends.pid_kp);
	LCD_Send_String(LCD_I2C_CHANNEL2,lcdBuff,STR_NOSLIDE);
	LCD_SetCursor(LCD_I2C_CHANNEL2,2,1);
	sprintf(lcdBuff,"i:%02x d:%02x f:%02x",sends.pid_ki,sends.pid_kd,sends.factor);
	LCD_Send_String(LCD_I2C_CHANNEL2,lcdBuff,STR_NOSLIDE);
}
void cleanTheLcd(void){
	LCD_Clear(LCD_I2C_CHANNEL1);
	LCD_Clear(LCD_I2C_CHANNEL2);
}
void lcdController(void){
	static mD_interface temp;
	static uint8_t itemVal=0,statuVal=0;
	if(0==statuVal){
		if(0==itemVal){
			temp=getDriver1TransmitVal();
			printToLcdDrv1Transmit(temp,true);
			temp=getDriver2TransmitVal();
			printToLcdDrv2Transmit(temp,false);

		}else{
			temp=getDriver1ReceiveVal();
			printToLcdDrv1Receive(temp,true);
			temp=getDriver2ReceiveVal();
			printToLcdDrv2Receive(temp,false);
		}
	}
	else{
		if(0==itemVal){
			temp=getDriver2TransmitVal();
			printToLcdDrv2Transmit(temp,true);
			temp=getDriver1TransmitVal();
			printToLcdDrv1Transmit(temp,false);

		}else{
			temp=getDriver2ReceiveVal();
			printToLcdDrv2Receive(temp,true);
			temp=getDriver1ReceiveVal();
			printToLcdDrv1Receive(temp,false);
		}
	}
	statuVal=getSelectedLcdVal();
	itemVal=getSelectedLcdItemVal();
}
