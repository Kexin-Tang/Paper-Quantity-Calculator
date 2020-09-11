#include "iic.h"
#include <xgpio.h>
//////////////////////////////////////////////////////////////////////////////////
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEK STM32F407¿ª·¢°å
//µçÈÝ´¥ÃþÆÁ-IIC Çý¶¯´úÂë
//ÕýµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//´´½¨ÈÕÆÚ:2014/5/7
//°æ±¾£ºV1.1
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾ 2014-2024
//All rights reserved
//********************************************************************************
//ÐÞ¸ÄËµÃ÷
//V1.1 20140721
//1,ÐÞ¸ÄCT_IIC_Read_Byteº¯Êý,¶ÁÊý¾Ý¸ü¿ì.
//2,ÐÞ¸ÄCT_IIC_Wait_Ackº¯Êý,ÒÔÖ§³ÖMDKµÄ-O2ÓÅ»¯.
//////////////////////////////////////////////////////////////////////////////////

//¿ØÖÆI2CËÙ¶ÈµÄÑÓÊ±
XGpio gpio0;
void SDA_OUT(void)
{
	XGpio_SetDataDirection(&gpio0, 1,(u8)0x0);
}

void SDA_IN(void)
{
	XGpio_SetDataDirection(&gpio0, 1,(u8)0x2);
}

void IIC_SDA(int x)
{
	if(x == 1)
		XGpio_DiscreteSet(&gpio0, 1, (u8)2);
	else
		XGpio_DiscreteClear(&gpio0, 1, (u8)2);

}
u8 READ_SDA(void)
{
	u8 temp = XGpio_DiscreteRead(&gpio0, 1);
	return (temp & 2)>>1;
}


void IIC_SCL(int x)
{
	if(x == 1)
		XGpio_DiscreteSet(&gpio0, 1, (u8)1);
	else
		XGpio_DiscreteClear(&gpio0, 1, (u8)1);
}
void Delay(void)
{
	delay_us(2);
//	delay_ms(1);
}
//µçÈÝ´¥ÃþÐ¾Æ¬IIC½Ó¿Ú³õÊ¼»¯

void IIC_Init(void)
{
	XGpio_Initialize(&gpio0, XPAR_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&gpio0, 1,0x00);
	XGpio_DiscreteSet(&gpio0, 1, 0x03);
	//XGpio_SetDataDirection(&gpio0, 1,0x00);
	//XGpio_DiscreteSet(&gpio0, 1, (u8)2);
//	XGpio_DiscreteSet(&gpio0, 1, (u8)2);
//	XGpio_DiscreteSet(&gpio0, 1, (u8)1);
}
//²úÉúIICÆðÊ¼ÐÅºÅ
void IIC_Start(void)
{
	SDA_OUT();     //sdaÏßÊä³ö
	IIC_SDA(1);
	IIC_SCL(1);
	delay_us(30);
//	delay_ms(1);
 	IIC_SDA(0);//START:when CLK is high,DATA change form high to low
	Delay();
	IIC_SCL(0);//Ç¯×¡I2C×ÜÏß£¬×¼±¸·¢ËÍ»ò½ÓÊÕÊý¾Ý
}
//²úÉúIICÍ£Ö¹ÐÅºÅ
void IIC_Stop(void)
{
	SDA_OUT();//sdaÏßÊä³ö
	IIC_SCL(1);
	delay_us(30);
//	delay_ms(1);
	IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
	Delay();
	IIC_SDA(1);//·¢ËÍI2C×ÜÏß½áÊøÐÅºÅ

//	CT_SDA_OUT();     //sdaÏßÊä³ö
//	CT_IIC_SDA(0);
//	CT_IIC_SCL(1);
//	delay_us(30);
////	delay_ms(1);
//	CT_IIC_SDA(1);//START:when CLK is high,DATA change form high to low
//	CT_Delay();
//	CT_IIC_SCL(0);//Ç¯×¡I2C×ÜÏß£¬×¼±¸·¢ËÍ»ò½ÓÊÕÊý¾Ý
}
//µÈ´ýÓ¦´ðÐÅºÅµ½À´
//·µ»ØÖµ£º1£¬½ÓÊÕÓ¦´ðÊ§°Ü
//        0£¬½ÓÊÕÓ¦´ð³É¹¦
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDAÉèÖÃÎªÊäÈë
	IIC_SDA(1);
	IIC_SCL(1);
	Delay();
	while(READ_SDA())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
		Delay();
	}
	IIC_SCL(0);//Ê±ÖÓÊä³ö0
	return 0;
}
//²úÉúACKÓ¦´ð
void IIC_Ack(void)
{
	IIC_SCL(0);
	SDA_OUT();
	Delay();
	IIC_SDA(0);
	Delay();
	IIC_SCL(1);
	Delay();
	IIC_SCL(0);
}
//²»²úÉúACKÓ¦´ð
void IIC_NAck(void)
{
	IIC_SCL(0);
	SDA_OUT();
	Delay();
	IIC_SDA(1);
	Delay();
	IIC_SCL(1);
	Delay();
	IIC_SCL(0);
}
//IIC·¢ËÍÒ»¸ö×Ö½Ú
//·µ»Ø´Ó»úÓÐÎÞÓ¦´ð
//1£¬ÓÐÓ¦´ð
//0£¬ÎÞÓ¦´ð
void IIC_Send_Byte(u8 txd)
{
    u8 t;
	SDA_OUT();
    IIC_SCL(0);//À­µÍÊ±ÖÓ¿ªÊ¼Êý¾Ý´«Êä
	Delay();
	for(t=0;t<8;t++)
    {
        IIC_SDA((txd&0x80)>>7);
        txd<<=1;
		IIC_SCL(1);
		Delay();
		IIC_SCL(0);
		Delay();
    }
}
//¶Á1¸ö×Ö½Ú£¬ack=1Ê±£¬·¢ËÍACK£¬ack=0£¬·¢ËÍnACK
u8 IIC_Read_Byte(unsigned char ack)
{
	u8 i,receive=0;
 	SDA_IN();//SDAÉèÖÃÎªÊäÈë
	delay_us(30);
// 	delay_ms(1);
	for(i=0;i<8;i++ )
	{
		IIC_SCL(0);
		Delay();
		IIC_SCL(1);
		receive<<=1;
		if(READ_SDA())receive++;
	}
	if (!ack)IIC_NAck();//·¢ËÍnACK
	else IIC_Ack(); //·¢ËÍACK
 	return receive;
}




























