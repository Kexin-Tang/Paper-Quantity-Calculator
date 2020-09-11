#include <stdio.h>
#include <math.h>
#include <xparameters.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include <lcd_controller.h>
#include <xgpio.h>
#include ".\lcd\lcd.h"
#include ".\fdc2214\iic.h"
#include ".\fdc2214\fdc2214.h"
#include ".\touch\ctiic.h"
#include ".\touch\touch.h"
#include ".\touch\graph.h"
#include "preph.h"


u32 ch0,ch1,ch2,ch3;

extern double short_num;


int main()
{

	init_platform();

	double cap=0.0;
	double freq =0.0;

	CT_IIC_Init();
	IIC_Init();
	LCD_Init(0);
	tp_dev.init();
	Beep_Init();
	LED_Init();
	FDC2214_Init();

/*
	POINT_COLOR=BLUE;
	LCD_ShowString(30,10,200,16,16,"Capcity(pF):");
	LCD_ShowString(150,30,200,16,16," pF");
	POINT_COLOR=RED;
	printf("OK\n");
	while(1)
	{
		cap = IIR();

		delay_ms(500);
	}
*/


	Draw_Start();
	while(1)
		;

}


