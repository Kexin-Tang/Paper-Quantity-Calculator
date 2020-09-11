#include "ctiic.h"
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
XGpio gpio1;
void CT_SDA_OUT(void)
{
	XGpio_SetDataDirection(&gpio1, 1,(u8)0x0);
}

void CT_SDA_IN(void)
{
	XGpio_SetDataDirection(&gpio1, 1,(u8)0x8);
}

void CT_IIC_SDA(int x)
{
	if(x == 1)
		XGpio_DiscreteSet(&gpio1, 1, (u8)8);
	else
		XGpio_DiscreteClear(&gpio1, 1, (u8)8);

}
u8 CT_READ_SDA(void)
{
	u8 temp = XGpio_DiscreteRead(&gpio1, 1);
	return (temp & 8)>>3;
}


void CT_IIC_SCL(int x)
{
	if(x == 1)
		XGpio_DiscreteSet(&gpio1, 1, (u8)1);
	else
		XGpio_DiscreteClear(&gpio1, 1, (u8)1);
}
void CT_Delay(void)
{
	delay_us(2);
//	delay_ms(1);
}
//µçÈÝ´¥ÃþÐ¾Æ¬IIC½Ó¿Ú³õÊ¼»¯

void CT_IIC_Init(void)
{
	XGpio_Initialize(&gpio1, XPAR_GPIO_3_DEVICE_ID);
	XGpio_SetDataDirection(&gpio1, 1,0x04);
	XGpio_DiscreteSet(&gpio1, 1, 0xf6);
	//XGpio_SetDataDirection(&gpio0, 1,0x00);
	//XGpio_DiscreteSet(&gpio0, 1, (u8)2);
//	XGpio_DiscreteSet(&gpio0, 1, (u8)2);
//	XGpio_DiscreteSet(&gpio0, 1, (u8)1);
}
//²úÉúIICÆðÊ¼ÐÅºÅ
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     //sdaÏßÊä³ö
	CT_IIC_SDA(1);
	CT_IIC_SCL(1);
	delay_us(30);
//	delay_ms(1);
 	CT_IIC_SDA(0);//START:when CLK is high,DATA change form high to low
	CT_Delay();
	CT_IIC_SCL(0);//Ç¯×¡I2C×ÜÏß£¬×¼±¸·¢ËÍ»ò½ÓÊÕÊý¾Ý
}
//²úÉúIICÍ£Ö¹ÐÅºÅ
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//sdaÏßÊä³ö
	CT_IIC_SCL(1);
	delay_us(30);
//	delay_ms(1);
	CT_IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
	CT_Delay();
	CT_IIC_SDA(1);//·¢ËÍI2C×ÜÏß½áÊøÐÅºÅ

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
u8 CT_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	CT_SDA_IN();      //SDAÉèÖÃÎªÊäÈë
	CT_IIC_SDA(1);
	CT_IIC_SCL(1);
	CT_Delay();
	while(CT_READ_SDA())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		}
		CT_Delay();
	}
	CT_IIC_SCL(0);//Ê±ÖÓÊä³ö0
	return 0;
}
//²úÉúACKÓ¦´ð
void CT_IIC_Ack(void)
{
	CT_IIC_SCL(0);
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA(0);
	CT_Delay();
	CT_IIC_SCL(1);
	CT_Delay();
	CT_IIC_SCL(0);
}
//²»²úÉúACKÓ¦´ð
void CT_IIC_NAck(void)
{
	CT_IIC_SCL(0);
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA(1);
	CT_Delay();
	CT_IIC_SCL(1);
	CT_Delay();
	CT_IIC_SCL(0);
}
//IIC·¢ËÍÒ»¸ö×Ö½Ú
//·µ»Ø´Ó»úÓÐÎÞÓ¦´ð
//1£¬ÓÐÓ¦´ð
//0£¬ÎÞÓ¦´ð
void CT_IIC_Send_Byte(u8 txd)
{
    u8 t;
	CT_SDA_OUT();
    CT_IIC_SCL(0);//À­µÍÊ±ÖÓ¿ªÊ¼Êý¾Ý´«Êä
	CT_Delay();
	for(t=0;t<8;t++)
    {
        CT_IIC_SDA((txd&0x80)>>7);
        txd<<=1;
		CT_IIC_SCL(1);
		CT_Delay();
		CT_IIC_SCL(0);
		CT_Delay();
    }
}
//¶Á1¸ö×Ö½Ú£¬ack=1Ê±£¬·¢ËÍACK£¬ack=0£¬·¢ËÍnACK
u8 CT_IIC_Read_Byte(unsigned char ack)
{
	u8 i,receive=0;
 	CT_SDA_IN();//SDAÉèÖÃÎªÊäÈë
	delay_us(30);
// 	delay_ms(1);
	for(i=0;i<8;i++ )
	{
		CT_IIC_SCL(0);
		CT_Delay();
		CT_IIC_SCL(1);
		receive<<=1;
		if(CT_READ_SDA())receive++;
	}
	if (!ack)CT_IIC_NAck();//·¢ËÍnACK
	else CT_IIC_Ack(); //·¢ËÍACK
 	return receive;
}




























