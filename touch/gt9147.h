#ifndef __GT9147_H
#define __GT9147_H
//////////////////////////////////////////////////////////////////////////////////
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEK STM32¿ª·¢°å
//4.3´çµçÈÝ´¥ÃþÆÁ-GT9147 Çý¶¯´úÂë
//ÕýµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//´´½¨ÈÕÆÚ:2015/1/15
//°æ±¾£ºV1.1
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾ 2014-2024
//All rights reserved
//*******************************************************************************
//ÐÞ¸ÄÐÅÏ¢
//V1.1 20150320
//ÐÞ¸ÄGT9147_Scanº¯Êý,Ìí¼Ó¶Ô·Ç·¨Êý¾ÝµÄ´¦Àí,·ÀÖ¹·Ç·¨Êý¾Ý¸ÉÈÅ
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
//#include "platform.h"
#include "xil_printf.h"
#include"lcd_controller.h"
#include"xparameters.h"
//IO²Ù×÷º¯Êý
#define GT_INT    		PBin(1)		//GT9147ÖÐ¶ÏÒý½Å


//I2C¶ÁÐ´ÃüÁî
#define GT_CMD_WR 		0X28     	//Ð´ÃüÁî
#define GT_CMD_RD 		0X29		//¶ÁÃüÁî

//GT9147 ²¿·Ö¼Ä´æÆ÷¶¨Òå
#define GT_CTRL_REG 	0X8040   	//GT9147¿ØÖÆ¼Ä´æÆ÷
#define GT_CFGS_REG 	0X8047   	//GT9147ÅäÖÃÆðÊ¼µØÖ·¼Ä´æÆ÷
#define GT_CHECK_REG 	0X80FF   	//GT9147Ð£ÑéºÍ¼Ä´æÆ÷
#define GT_PID_REG 		0X8140   	//GT9147²úÆ·ID¼Ä´æÆ÷

#define GT_GSTID_REG 	0X814E   	//GT9147µ±Ç°¼ì²âµ½µÄ´¥ÃþÇé¿ö
#define GT_TP1_REG 		0X8150  	//µÚÒ»¸ö´¥ÃþµãÊý¾ÝµØÖ·
#define GT_TP2_REG 		0X8158		//µÚ¶þ¸ö´¥ÃþµãÊý¾ÝµØÖ·
#define GT_TP3_REG 		0X8160		//µÚÈý¸ö´¥ÃþµãÊý¾ÝµØÖ·
#define GT_TP4_REG 		0X8168		//µÚËÄ¸ö´¥ÃþµãÊý¾ÝµØÖ·
#define GT_TP5_REG 		0X8170		//µÚÎå¸ö´¥ÃþµãÊý¾ÝµØÖ·


u8 GT9147_Send_Cfg(u8 mode);
u8 GT9147_WR_Reg(u16 reg,u8 *buf,u8 len);
void GT9147_RD_Reg(u16 reg,u8 *buf,u8 len);
u8 GT9147_Init(void);
u8 GT9147_Scan(u8 mode);
#endif













