#include "gt9147.h"
#include "touch.h"
#include "ctiic.h"
#include "..\lcd\lcd.h"
#include <xgpio.h>
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

//GT9147ÅäÖÃ²ÎÊý±í
//µÚÒ»¸ö×Ö½ÚÎª°æ±¾ºÅ(0X60),±ØÐë±£Ö¤ÐÂµÄ°æ±¾ºÅ´óÓÚµÈÓÚGT9147ÄÚ²¿
//flashÔ­ÓÐ°æ±¾ºÅ,²Å»á¸üÐÂÅäÖÃ.
void delay_ms(int ms);
const u8 GT9147_CFG_TBL[]=
{
	0X60,0XE0,0X01,0X20,0X03,0X05,0X35,0X00,0X02,0X08,
	0X1E,0X08,0X50,0X3C,0X0F,0X05,0X00,0X00,0XFF,0X67,
	0X50,0X00,0X00,0X18,0X1A,0X1E,0X14,0X89,0X28,0X0A,
	0X30,0X2E,0XBB,0X0A,0X03,0X00,0X00,0X02,0X33,0X1D,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X32,0X00,0X00,
	0X2A,0X1C,0X5A,0X94,0XC5,0X02,0X07,0X00,0X00,0X00,
	0XB5,0X1F,0X00,0X90,0X28,0X00,0X77,0X32,0X00,0X62,
	0X3F,0X00,0X52,0X50,0X00,0X52,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
	0X0F,0X03,0X06,0X10,0X42,0XF8,0X0F,0X14,0X00,0X00,
	0X00,0X00,0X1A,0X18,0X16,0X14,0X12,0X10,0X0E,0X0C,
	0X0A,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X29,0X28,0X24,0X22,0X20,0X1F,0X1E,0X1D,
	0X0E,0X0C,0X0A,0X08,0X06,0X05,0X04,0X02,0X00,0XFF,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
	0XFF,0XFF,0XFF,0XFF,
};

extern XGpio gpio1;
void GT_RST(u8 x)
{
	if(x == 1)
		XGpio_DiscreteSet(&gpio1, 1, (u8)2);
	else
		XGpio_DiscreteClear(&gpio1, 1, (u8)2);
}

//·¢ËÍGT9147ÅäÖÃ²ÎÊý
//mode:0,²ÎÊý²»±£´æµ½flash
//     1,²ÎÊý±£´æµ½flash
u8 GT9147_Send_Cfg(u8 mode)
{
	u8 buf[2];
	u8 i=0;
	buf[0]=0;
	buf[1]=mode;	//ÊÇ·ñÐ´Èëµ½GT9147 FLASH?  ¼´ÊÇ·ñµôµç±£´æ
	for(i=0;i<sizeof(GT9147_CFG_TBL);i++)buf[0]+=GT9147_CFG_TBL[i];//¼ÆËãÐ£ÑéºÍ
    buf[0]=(~buf[0])+1;
	GT9147_WR_Reg(GT_CFGS_REG,(u8*)GT9147_CFG_TBL,sizeof(GT9147_CFG_TBL));//·¢ËÍ¼Ä´æÆ÷ÅäÖÃ
	GT9147_WR_Reg(GT_CHECK_REG,buf,2);//Ð´ÈëÐ£ÑéºÍ,ºÍÅäÖÃ¸üÐÂ±ê¼Ç
	return 0;
}
//ÏòGT9147Ð´ÈëÒ»´ÎÊý¾Ý
//reg:ÆðÊ¼¼Ä´æÆ÷µØÖ·
//buf:Êý¾Ý»º»º´æÇø
//len:Ð´Êý¾Ý³¤¶È
//·µ»ØÖµ:0,³É¹¦;1,Ê§°Ü.
u8 GT9147_WR_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i;
	u8 ret=0;
	CT_IIC_Start();
 	CT_IIC_Send_Byte(GT_CMD_WR);   	//·¢ËÍÐ´ÃüÁî
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8);   	//·¢ËÍ¸ß8Î»µØÖ·
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg&0XFF);   	//·¢ËÍµÍ8Î»µØÖ·
	CT_IIC_Wait_Ack();
	for(i=0;i<len;i++)
	{
    	CT_IIC_Send_Byte(buf[i]);  	//·¢Êý¾Ý
		ret=CT_IIC_Wait_Ack();
		if(ret)break;
	}
    CT_IIC_Stop();					//²úÉúÒ»¸öÍ£Ö¹Ìõ¼þ
	return ret;
}
//´ÓGT9147¶Á³öÒ»´ÎÊý¾Ý
//reg:ÆðÊ¼¼Ä´æÆ÷µØÖ·
//buf:Êý¾Ý»º»º´æÇø
//len:¶ÁÊý¾Ý³¤¶È
void GT9147_RD_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i;
//	while(1)
//	{
		CT_IIC_Start();
		CT_IIC_Send_Byte(GT_CMD_WR);   //·¢ËÍÐ´ÃüÁî
		CT_IIC_Wait_Ack();
		CT_IIC_Send_Byte(reg>>8);   	//·¢ËÍ¸ß8Î»µØÖ·
		CT_IIC_Wait_Ack();
		CT_IIC_Send_Byte(reg&0XFF);   	//·¢ËÍµÍ8Î»µØÖ·
		CT_IIC_Wait_Ack();
		CT_IIC_Start();
		CT_IIC_Send_Byte(GT_CMD_RD);   //·¢ËÍ¶ÁÃüÁî
		CT_IIC_Wait_Ack();
//	}
	for(i=0;i<len;i++)
	{
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //·¢Êý¾Ý
	}
    CT_IIC_Stop();//²úÉúÒ»¸öÍ£Ö¹Ìõ¼þ
}
//³õÊ¼»¯GT9147´¥ÃþÆÁ
//·µ»ØÖµ:0,³õÊ¼»¯³É¹¦;1,³õÊ¼»¯Ê§°Ü
u8 GT9147_Init(void)
{
	u8 temp[5];
//	GPIO_Set(GPIOB,PIN1,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);	//int引脚
//	XGpio_SetDataDirection(&gpio0, 1,0x04);
//	GPIO_Set(GPIOC,PIN13,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); //rst
	int ConfigNum = 0;
	CT_IIC_Init();
	GT_RST(0);				//¸´Î»
	delay_ms(10);
	XGpio_DiscreteSet(&gpio1, 1, (u8)4);
	delay_ms(10);
	GT_RST(1);				//ÊÍ·Å¸´Î»
	delay_ms(10);
//	GPIO_Set(GPIOB,PIN1,GPIO_MODE_IN,0,0,GPIO_PUPD_NONE);//int引脚
	XGpio_SetDataDirection(&gpio1, 1,0x04);
	delay_ms(100);
	GT9147_RD_Reg(GT_PID_REG,temp,4);//¶ÁÈ¡²úÆ·ID
	temp[4]=0;
	printf("CTP ID:%s\r\n",temp);	//´òÓ¡ID
//	delay_ms(1000);
	if(strcmp((char*)temp,"9147")==0)//ID==9147
	{
		temp[0]=0X02;
		GT9147_WR_Reg(GT_CTRL_REG,temp,1);//Èí¸´Î»GT9147
		GT9147_RD_Reg(GT_CFGS_REG,temp,1);//¶ÁÈ¡GT_CFGS_REG¼Ä´æÆ÷
		if(temp[0]<0X60)//Ä¬ÈÏ°æ±¾±È½ÏµÍ,ÐèÒª¸üÐÂflashÅäÖÃ
		{
			printf("Default Ver:%d\r\n",temp[0]);
			GT9147_Send_Cfg(1);//¸üÐÂ²¢±£´æÅäÖÃ
		}
		delay_ms(10);
		temp[0]=0X00;
		GT9147_WR_Reg(GT_CTRL_REG,temp,1);//½áÊø¸´Î»
		return 0;
	}
	else
	{
		POINT_COLOR = RED;
		LCD_ShowString(100,100,200,24,24,"Error !!!");
		POINT_COLOR = BLACK;
		return 1;
	}

	return 1;
}
const u16 GT9147_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};
//É¨Ãè´¥ÃþÆÁ(²ÉÓÃ²éÑ¯·½Ê½)
//mode:0,Õý³£É¨Ãè.
//·µ»ØÖµ:µ±Ç°´¥ÆÁ×´Ì¬.
//0,´¥ÆÁÎÞ´¥Ãþ;1,´¥ÆÁÓÐ´¥Ãþ
u8 GT9147_Scan(u8 mode)
{
	u8 buf[4];
	u8 i=0;
	u8 res=0;
	u8 temp;
	u8 tempsta;
 	static u8 t=0;//¿ØÖÆ²éÑ¯¼ä¸ô,´Ó¶ø½µµÍCPUÕ¼ÓÃÂÊ
	t++;
	if((t%10)==0||t<10)//¿ÕÏÐÊ±,Ã¿½øÈë10´ÎCTP_Scanº¯Êý²Å¼ì²â1´Î,´Ó¶ø½ÚÊ¡CPUÊ¹ÓÃÂÊ
	{
		GT9147_RD_Reg(GT_GSTID_REG,&mode,1);	//¶ÁÈ¡´¥ÃþµãµÄ×´Ì¬
 		if(mode&0X80&&((mode&0XF)<6))
		{
			temp=0;
			GT9147_WR_Reg(GT_GSTID_REG,&temp,1);//Çå±êÖ¾
		}
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFF<<(mode&0XF);		//½«µãµÄ¸öÊý×ª»»Îª1µÄÎ»Êý,Æ¥Åätp_dev.sta¶¨Òå
			tempsta=tp_dev.sta;			//±£´æµ±Ç°µÄtp_dev.staÖµ
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES;
			tp_dev.x[4]=tp_dev.x[0];	//±£´æ´¥µã0µÄÊý¾Ý
			tp_dev.y[4]=tp_dev.y[0];
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))	//´¥ÃþÓÐÐ§?
				{
					GT9147_RD_Reg(GT9147_TPX_TBL[i],buf,4);	//¶ÁÈ¡XY×ø±êÖµ
					if(tp_dev.touchtype&0X01)//ºáÆÁ
					{
						tp_dev.y[i]=((u16)buf[1]<<8)+buf[0];
						tp_dev.x[i]=800-(((u16)buf[3]<<8)+buf[2]);
					}else
					{
						tp_dev.x[i]=((u16)buf[1]<<8)+buf[0];
						tp_dev.y[i]=((u16)buf[3]<<8)+buf[2];
					}
					//printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
				}
			}
			res=1;
			if(tp_dev.x[0]>lcddev.width||tp_dev.y[0]>lcddev.height)//·Ç·¨Êý¾Ý(×ø±ê³¬³öÁË)
			{
				if((mode&0XF)>1)		//ÓÐÆäËûµãÓÐÊý¾Ý,Ôò¸´µÚ¶þ¸ö´¥µãµÄÊý¾Ýµ½µÚÒ»¸ö´¥µã.
				{
					tp_dev.x[0]=tp_dev.x[1];
					tp_dev.y[0]=tp_dev.y[1];
					t=0;				//´¥·¢Ò»´Î,Ôò»á×îÉÙÁ¬Ðø¼à²â10´Î,´Ó¶øÌá¸ßÃüÖÐÂÊ
				}else					//·Ç·¨Êý¾Ý,ÔòºöÂÔ´Ë´ÎÊý¾Ý(»¹Ô­Ô­À´µÄ)
				{
					tp_dev.x[0]=tp_dev.x[4];
					tp_dev.y[0]=tp_dev.y[4];
					mode=0X80;
					tp_dev.sta=tempsta;	//»Ö¸´tp_dev.sta
				}
			}else t=0;					//´¥·¢Ò»´Î,Ôò»á×îÉÙÁ¬Ðø¼à²â10´Î,´Ó¶øÌá¸ßÃüÖÐÂÊ
		}
	}
	if((mode&0X8F)==0X80)//ÎÞ´¥Ãþµã°´ÏÂ
	{
		if(tp_dev.sta&TP_PRES_DOWN)	//Ö®Ç°ÊÇ±»°´ÏÂµÄ
		{
			tp_dev.sta&=~(1<<7);	//±ê¼Ç°´¼üËÉ¿ª
		}else						//Ö®Ç°¾ÍÃ»ÓÐ±»°´ÏÂ
		{
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//Çå³ýµãÓÐÐ§±ê¼Ç
		}
	}
	if(t>240)t=10;//ÖØÐÂ´Ó10¿ªÊ¼¼ÆÊý
	return res;
}




























