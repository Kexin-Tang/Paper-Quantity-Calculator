#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H
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
#include <stdio.h>
//#include "platform.h"
#include "xil_printf.h"
#include"lcd_controller.h"
#include"xparameters.h"
//IO·½ÏòÉèÖÃ
//IO²Ù×÷º¯Êý


//IICËùÓÐ²Ù×÷º¯Êý
void CT_IIC_Init(void);                	//³õÊ¼»¯IICµÄIO¿Ú
void CT_IIC_Start(void);				//·¢ËÍIIC¿ªÊ¼ÐÅºÅ
void CT_IIC_Stop(void);	  				//·¢ËÍIICÍ£Ö¹ÐÅºÅ
void CT_IIC_Send_Byte(u8 txd);			//IIC·¢ËÍÒ»¸ö×Ö½Ú
u8 CT_IIC_Read_Byte(unsigned char ack);	//IIC¶ÁÈ¡Ò»¸ö×Ö½Ú
u8 CT_IIC_Wait_Ack(void); 				//IICµÈ´ýACKÐÅºÅ
void CT_IIC_Ack(void);					//IIC·¢ËÍACKÐÅºÅ
void CT_IIC_NAck(void);					//IIC²»·¢ËÍACKÐÅºÅ

#endif







