#include <stdio.h>
#include <math.h>
#include "stdlib.h"
#include "xil_printf.h"
#include <xparameters.h>
#include <lcd_controller.h>
#include "lcd.h"
#include "font.h"
#include "sleep.h"

u16 POINT_COLOR=0x0000;	//»­±ÊÑÕÉ«
u16 BACK_COLOR=0xFFFF;  //±³¾°É«

_lcd_dev lcddev;

void delay_ms(int ms)
{
	usleep(ms*1000);
}

void delay_us(int us)
{
	usleep(us);
}

void LCD_WR_REG(u32 regval)
{
	u32 reg = (regval << 2) | (0x1);
	LCD_CONTROLLER_mWriteReg(XPAR_HIER_PERIPH_LCD_CONTROLLER_0_S00_AXI_BASEADDR, LCD_CONTROLLER_S00_AXI_SLV_REG0_OFFSET, reg);
}

void LCD_WR_DATA(u32 data)
{
	u32 reg = (data << 2) | (0x2);
	LCD_CONTROLLER_mWriteReg(XPAR_HIER_PERIPH_LCD_CONTROLLER_0_S00_AXI_BASEADDR, LCD_CONTROLLER_S00_AXI_SLV_REG0_OFFSET, reg);
}

void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{
	LCD_WR_REG(LCD_Reg);
	LCD_WR_DATA(LCD_RegValue);
}

void LCD_Reset(void)
{
	LCD_CONTROLLER_mWriteReg(XPAR_HIER_PERIPH_LCD_CONTROLLER_0_S00_AXI_BASEADDR, LCD_CONTROLLER_S00_AXI_SLV_REG2_OFFSET, 0);
	delay_ms(120);
	LCD_CONTROLLER_mWriteReg(XPAR_HIER_PERIPH_LCD_CONTROLLER_0_S00_AXI_BASEADDR, LCD_CONTROLLER_S00_AXI_SLV_REG2_OFFSET, 1);
}

void LCD_Init(u8 dir)
{
    LCD_Reset();
  	lcddev.id = 0x5510;
  	if(lcddev.id==0x5510)
	{
		LCD_WriteReg(0xF000,0x55);
		LCD_WriteReg(0xF001,0xAA);
		LCD_WriteReg(0xF002,0x52);
		LCD_WriteReg(0xF003,0x08);
		LCD_WriteReg(0xF004,0x01);
		//AVDD Set AVDD 5.2V
		LCD_WriteReg(0xB000,0x0D);
		LCD_WriteReg(0xB001,0x0D);
		LCD_WriteReg(0xB002,0x0D);
		//AVDD ratio
		LCD_WriteReg(0xB600,0x34);
		LCD_WriteReg(0xB601,0x34);
		LCD_WriteReg(0xB602,0x34);
		//AVEE -5.2V
		LCD_WriteReg(0xB100,0x0D);
		LCD_WriteReg(0xB101,0x0D);
		LCD_WriteReg(0xB102,0x0D);
		//AVEE ratio
		LCD_WriteReg(0xB700,0x34);
		LCD_WriteReg(0xB701,0x34);
		LCD_WriteReg(0xB702,0x34);
		//VCL -2.5V
		LCD_WriteReg(0xB200,0x00);
		LCD_WriteReg(0xB201,0x00);
		LCD_WriteReg(0xB202,0x00);
		//VCL ratio
		LCD_WriteReg(0xB800,0x24);
		LCD_WriteReg(0xB801,0x24);
		LCD_WriteReg(0xB802,0x24);
		//VGH 15V (Free pump)
		LCD_WriteReg(0xBF00,0x01);
		LCD_WriteReg(0xB300,0x0F);
		LCD_WriteReg(0xB301,0x0F);
		LCD_WriteReg(0xB302,0x0F);
		//VGH ratio
		LCD_WriteReg(0xB900,0x34);
		LCD_WriteReg(0xB901,0x34);
		LCD_WriteReg(0xB902,0x34);
		//VGL_REG -10V
		LCD_WriteReg(0xB500,0x08);
		LCD_WriteReg(0xB501,0x08);
		LCD_WriteReg(0xB502,0x08);
		LCD_WriteReg(0xC200,0x03);
		//VGLX ratio
		LCD_WriteReg(0xBA00,0x24);
		LCD_WriteReg(0xBA01,0x24);
		LCD_WriteReg(0xBA02,0x24);
		//VGMP/VGSP 4.5V/0V
		LCD_WriteReg(0xBC00,0x00);
		LCD_WriteReg(0xBC01,0x78);
		LCD_WriteReg(0xBC02,0x00);
		//VGMN/VGSN -4.5V/0V
		LCD_WriteReg(0xBD00,0x00);
		LCD_WriteReg(0xBD01,0x78);
		LCD_WriteReg(0xBD02,0x00);
		//VCOM
		LCD_WriteReg(0xBE00,0x00);
		LCD_WriteReg(0xBE01,0x64);
		//Gamma Setting
		LCD_WriteReg(0xD100,0x00);
		LCD_WriteReg(0xD101,0x33);
		LCD_WriteReg(0xD102,0x00);
		LCD_WriteReg(0xD103,0x34);
		LCD_WriteReg(0xD104,0x00);
		LCD_WriteReg(0xD105,0x3A);
		LCD_WriteReg(0xD106,0x00);
		LCD_WriteReg(0xD107,0x4A);
		LCD_WriteReg(0xD108,0x00);
		LCD_WriteReg(0xD109,0x5C);
		LCD_WriteReg(0xD10A,0x00);
		LCD_WriteReg(0xD10B,0x81);
		LCD_WriteReg(0xD10C,0x00);
		LCD_WriteReg(0xD10D,0xA6);
		LCD_WriteReg(0xD10E,0x00);
		LCD_WriteReg(0xD10F,0xE5);
		LCD_WriteReg(0xD110,0x01);
		LCD_WriteReg(0xD111,0x13);
		LCD_WriteReg(0xD112,0x01);
		LCD_WriteReg(0xD113,0x54);
		LCD_WriteReg(0xD114,0x01);
		LCD_WriteReg(0xD115,0x82);
		LCD_WriteReg(0xD116,0x01);
		LCD_WriteReg(0xD117,0xCA);
		LCD_WriteReg(0xD118,0x02);
		LCD_WriteReg(0xD119,0x00);
		LCD_WriteReg(0xD11A,0x02);
		LCD_WriteReg(0xD11B,0x01);
		LCD_WriteReg(0xD11C,0x02);
		LCD_WriteReg(0xD11D,0x34);
		LCD_WriteReg(0xD11E,0x02);
		LCD_WriteReg(0xD11F,0x67);
		LCD_WriteReg(0xD120,0x02);
		LCD_WriteReg(0xD121,0x84);
		LCD_WriteReg(0xD122,0x02);
		LCD_WriteReg(0xD123,0xA4);
		LCD_WriteReg(0xD124,0x02);
		LCD_WriteReg(0xD125,0xB7);
		LCD_WriteReg(0xD126,0x02);
		LCD_WriteReg(0xD127,0xCF);
		LCD_WriteReg(0xD128,0x02);
		LCD_WriteReg(0xD129,0xDE);
		LCD_WriteReg(0xD12A,0x02);
		LCD_WriteReg(0xD12B,0xF2);
		LCD_WriteReg(0xD12C,0x02);
		LCD_WriteReg(0xD12D,0xFE);
		LCD_WriteReg(0xD12E,0x03);
		LCD_WriteReg(0xD12F,0x10);
		LCD_WriteReg(0xD130,0x03);
		LCD_WriteReg(0xD131,0x33);
		LCD_WriteReg(0xD132,0x03);
		LCD_WriteReg(0xD133,0x6D);
		LCD_WriteReg(0xD200,0x00);
		LCD_WriteReg(0xD201,0x33);
		LCD_WriteReg(0xD202,0x00);
		LCD_WriteReg(0xD203,0x34);
		LCD_WriteReg(0xD204,0x00);
		LCD_WriteReg(0xD205,0x3A);
		LCD_WriteReg(0xD206,0x00);
		LCD_WriteReg(0xD207,0x4A);
		LCD_WriteReg(0xD208,0x00);
		LCD_WriteReg(0xD209,0x5C);
		LCD_WriteReg(0xD20A,0x00);

		LCD_WriteReg(0xD20B,0x81);
		LCD_WriteReg(0xD20C,0x00);
		LCD_WriteReg(0xD20D,0xA6);
		LCD_WriteReg(0xD20E,0x00);
		LCD_WriteReg(0xD20F,0xE5);
		LCD_WriteReg(0xD210,0x01);
		LCD_WriteReg(0xD211,0x13);
		LCD_WriteReg(0xD212,0x01);
		LCD_WriteReg(0xD213,0x54);
		LCD_WriteReg(0xD214,0x01);
		LCD_WriteReg(0xD215,0x82);
		LCD_WriteReg(0xD216,0x01);
		LCD_WriteReg(0xD217,0xCA);
		LCD_WriteReg(0xD218,0x02);
		LCD_WriteReg(0xD219,0x00);
		LCD_WriteReg(0xD21A,0x02);
		LCD_WriteReg(0xD21B,0x01);
		LCD_WriteReg(0xD21C,0x02);
		LCD_WriteReg(0xD21D,0x34);
		LCD_WriteReg(0xD21E,0x02);
		LCD_WriteReg(0xD21F,0x67);
		LCD_WriteReg(0xD220,0x02);
		LCD_WriteReg(0xD221,0x84);
		LCD_WriteReg(0xD222,0x02);
		LCD_WriteReg(0xD223,0xA4);
		LCD_WriteReg(0xD224,0x02);
		LCD_WriteReg(0xD225,0xB7);
		LCD_WriteReg(0xD226,0x02);
		LCD_WriteReg(0xD227,0xCF);
		LCD_WriteReg(0xD228,0x02);
		LCD_WriteReg(0xD229,0xDE);
		LCD_WriteReg(0xD22A,0x02);
		LCD_WriteReg(0xD22B,0xF2);
		LCD_WriteReg(0xD22C,0x02);
		LCD_WriteReg(0xD22D,0xFE);
		LCD_WriteReg(0xD22E,0x03);
		LCD_WriteReg(0xD22F,0x10);
		LCD_WriteReg(0xD230,0x03);
		LCD_WriteReg(0xD231,0x33);
		LCD_WriteReg(0xD232,0x03);
		LCD_WriteReg(0xD233,0x6D);
		LCD_WriteReg(0xD300,0x00);
		LCD_WriteReg(0xD301,0x33);
		LCD_WriteReg(0xD302,0x00);
		LCD_WriteReg(0xD303,0x34);
		LCD_WriteReg(0xD304,0x00);
		LCD_WriteReg(0xD305,0x3A);
		LCD_WriteReg(0xD306,0x00);
		LCD_WriteReg(0xD307,0x4A);
		LCD_WriteReg(0xD308,0x00);
		LCD_WriteReg(0xD309,0x5C);
		LCD_WriteReg(0xD30A,0x00);
		LCD_WriteReg(0xD30B,0x81);
		LCD_WriteReg(0xD30C,0x00);
		LCD_WriteReg(0xD30D,0xA6);
		LCD_WriteReg(0xD30E,0x00);
		LCD_WriteReg(0xD30F,0xE5);
		LCD_WriteReg(0xD310,0x01);
		LCD_WriteReg(0xD311,0x13);
		LCD_WriteReg(0xD312,0x01);
		LCD_WriteReg(0xD313,0x54);
		LCD_WriteReg(0xD314,0x01);
		LCD_WriteReg(0xD315,0x82);
		LCD_WriteReg(0xD316,0x01);
		LCD_WriteReg(0xD317,0xCA);
		LCD_WriteReg(0xD318,0x02);
		LCD_WriteReg(0xD319,0x00);
		LCD_WriteReg(0xD31A,0x02);
		LCD_WriteReg(0xD31B,0x01);
		LCD_WriteReg(0xD31C,0x02);
		LCD_WriteReg(0xD31D,0x34);
		LCD_WriteReg(0xD31E,0x02);
		LCD_WriteReg(0xD31F,0x67);
		LCD_WriteReg(0xD320,0x02);
		LCD_WriteReg(0xD321,0x84);
		LCD_WriteReg(0xD322,0x02);
		LCD_WriteReg(0xD323,0xA4);
		LCD_WriteReg(0xD324,0x02);
		LCD_WriteReg(0xD325,0xB7);
		LCD_WriteReg(0xD326,0x02);
		LCD_WriteReg(0xD327,0xCF);
		LCD_WriteReg(0xD328,0x02);
		LCD_WriteReg(0xD329,0xDE);
		LCD_WriteReg(0xD32A,0x02);
		LCD_WriteReg(0xD32B,0xF2);
		LCD_WriteReg(0xD32C,0x02);
		LCD_WriteReg(0xD32D,0xFE);
		LCD_WriteReg(0xD32E,0x03);
		LCD_WriteReg(0xD32F,0x10);
		LCD_WriteReg(0xD330,0x03);
		LCD_WriteReg(0xD331,0x33);
		LCD_WriteReg(0xD332,0x03);
		LCD_WriteReg(0xD333,0x6D);
		LCD_WriteReg(0xD400,0x00);
		LCD_WriteReg(0xD401,0x33);
		LCD_WriteReg(0xD402,0x00);
		LCD_WriteReg(0xD403,0x34);
		LCD_WriteReg(0xD404,0x00);
		LCD_WriteReg(0xD405,0x3A);
		LCD_WriteReg(0xD406,0x00);
		LCD_WriteReg(0xD407,0x4A);
		LCD_WriteReg(0xD408,0x00);
		LCD_WriteReg(0xD409,0x5C);
		LCD_WriteReg(0xD40A,0x00);
		LCD_WriteReg(0xD40B,0x81);
		LCD_WriteReg(0xD40C,0x00);
		LCD_WriteReg(0xD40D,0xA6);
		LCD_WriteReg(0xD40E,0x00);
		LCD_WriteReg(0xD40F,0xE5);
		LCD_WriteReg(0xD410,0x01);
		LCD_WriteReg(0xD411,0x13);
		LCD_WriteReg(0xD412,0x01);
		LCD_WriteReg(0xD413,0x54);
		LCD_WriteReg(0xD414,0x01);
		LCD_WriteReg(0xD415,0x82);
		LCD_WriteReg(0xD416,0x01);
		LCD_WriteReg(0xD417,0xCA);
		LCD_WriteReg(0xD418,0x02);
		LCD_WriteReg(0xD419,0x00);
		LCD_WriteReg(0xD41A,0x02);
		LCD_WriteReg(0xD41B,0x01);
		LCD_WriteReg(0xD41C,0x02);
		LCD_WriteReg(0xD41D,0x34);
		LCD_WriteReg(0xD41E,0x02);
		LCD_WriteReg(0xD41F,0x67);
		LCD_WriteReg(0xD420,0x02);
		LCD_WriteReg(0xD421,0x84);
		LCD_WriteReg(0xD422,0x02);
		LCD_WriteReg(0xD423,0xA4);
		LCD_WriteReg(0xD424,0x02);
		LCD_WriteReg(0xD425,0xB7);
		LCD_WriteReg(0xD426,0x02);
		LCD_WriteReg(0xD427,0xCF);
		LCD_WriteReg(0xD428,0x02);
		LCD_WriteReg(0xD429,0xDE);
		LCD_WriteReg(0xD42A,0x02);
		LCD_WriteReg(0xD42B,0xF2);
		LCD_WriteReg(0xD42C,0x02);
		LCD_WriteReg(0xD42D,0xFE);
		LCD_WriteReg(0xD42E,0x03);
		LCD_WriteReg(0xD42F,0x10);
		LCD_WriteReg(0xD430,0x03);
		LCD_WriteReg(0xD431,0x33);
		LCD_WriteReg(0xD432,0x03);
		LCD_WriteReg(0xD433,0x6D);
		LCD_WriteReg(0xD500,0x00);
		LCD_WriteReg(0xD501,0x33);
		LCD_WriteReg(0xD502,0x00);
		LCD_WriteReg(0xD503,0x34);
		LCD_WriteReg(0xD504,0x00);
		LCD_WriteReg(0xD505,0x3A);
		LCD_WriteReg(0xD506,0x00);
		LCD_WriteReg(0xD507,0x4A);
		LCD_WriteReg(0xD508,0x00);
		LCD_WriteReg(0xD509,0x5C);
		LCD_WriteReg(0xD50A,0x00);
		LCD_WriteReg(0xD50B,0x81);
		LCD_WriteReg(0xD50C,0x00);
		LCD_WriteReg(0xD50D,0xA6);
		LCD_WriteReg(0xD50E,0x00);
		LCD_WriteReg(0xD50F,0xE5);
		LCD_WriteReg(0xD510,0x01);
		LCD_WriteReg(0xD511,0x13);
		LCD_WriteReg(0xD512,0x01);
		LCD_WriteReg(0xD513,0x54);
		LCD_WriteReg(0xD514,0x01);
		LCD_WriteReg(0xD515,0x82);
		LCD_WriteReg(0xD516,0x01);
		LCD_WriteReg(0xD517,0xCA);
		LCD_WriteReg(0xD518,0x02);
		LCD_WriteReg(0xD519,0x00);
		LCD_WriteReg(0xD51A,0x02);
		LCD_WriteReg(0xD51B,0x01);
		LCD_WriteReg(0xD51C,0x02);
		LCD_WriteReg(0xD51D,0x34);
		LCD_WriteReg(0xD51E,0x02);
		LCD_WriteReg(0xD51F,0x67);
		LCD_WriteReg(0xD520,0x02);
		LCD_WriteReg(0xD521,0x84);
		LCD_WriteReg(0xD522,0x02);
		LCD_WriteReg(0xD523,0xA4);
		LCD_WriteReg(0xD524,0x02);
		LCD_WriteReg(0xD525,0xB7);
		LCD_WriteReg(0xD526,0x02);
		LCD_WriteReg(0xD527,0xCF);
		LCD_WriteReg(0xD528,0x02);
		LCD_WriteReg(0xD529,0xDE);
		LCD_WriteReg(0xD52A,0x02);
		LCD_WriteReg(0xD52B,0xF2);
		LCD_WriteReg(0xD52C,0x02);
		LCD_WriteReg(0xD52D,0xFE);
		LCD_WriteReg(0xD52E,0x03);
		LCD_WriteReg(0xD52F,0x10);
		LCD_WriteReg(0xD530,0x03);
		LCD_WriteReg(0xD531,0x33);
		LCD_WriteReg(0xD532,0x03);
		LCD_WriteReg(0xD533,0x6D);
		LCD_WriteReg(0xD600,0x00);
		LCD_WriteReg(0xD601,0x33);
		LCD_WriteReg(0xD602,0x00);
		LCD_WriteReg(0xD603,0x34);
		LCD_WriteReg(0xD604,0x00);
		LCD_WriteReg(0xD605,0x3A);
		LCD_WriteReg(0xD606,0x00);
		LCD_WriteReg(0xD607,0x4A);
		LCD_WriteReg(0xD608,0x00);
		LCD_WriteReg(0xD609,0x5C);
		LCD_WriteReg(0xD60A,0x00);
		LCD_WriteReg(0xD60B,0x81);
		LCD_WriteReg(0xD60C,0x00);
		LCD_WriteReg(0xD60D,0xA6);
		LCD_WriteReg(0xD60E,0x00);
		LCD_WriteReg(0xD60F,0xE5);
		LCD_WriteReg(0xD610,0x01);
		LCD_WriteReg(0xD611,0x13);
		LCD_WriteReg(0xD612,0x01);
		LCD_WriteReg(0xD613,0x54);
		LCD_WriteReg(0xD614,0x01);
		LCD_WriteReg(0xD615,0x82);
		LCD_WriteReg(0xD616,0x01);
		LCD_WriteReg(0xD617,0xCA);
		LCD_WriteReg(0xD618,0x02);
		LCD_WriteReg(0xD619,0x00);
		LCD_WriteReg(0xD61A,0x02);
		LCD_WriteReg(0xD61B,0x01);
		LCD_WriteReg(0xD61C,0x02);
		LCD_WriteReg(0xD61D,0x34);
		LCD_WriteReg(0xD61E,0x02);
		LCD_WriteReg(0xD61F,0x67);
		LCD_WriteReg(0xD620,0x02);
		LCD_WriteReg(0xD621,0x84);
		LCD_WriteReg(0xD622,0x02);
		LCD_WriteReg(0xD623,0xA4);
		LCD_WriteReg(0xD624,0x02);
		LCD_WriteReg(0xD625,0xB7);
		LCD_WriteReg(0xD626,0x02);
		LCD_WriteReg(0xD627,0xCF);
		LCD_WriteReg(0xD628,0x02);
		LCD_WriteReg(0xD629,0xDE);
		LCD_WriteReg(0xD62A,0x02);
		LCD_WriteReg(0xD62B,0xF2);
		LCD_WriteReg(0xD62C,0x02);
		LCD_WriteReg(0xD62D,0xFE);
		LCD_WriteReg(0xD62E,0x03);
		LCD_WriteReg(0xD62F,0x10);
		LCD_WriteReg(0xD630,0x03);
		LCD_WriteReg(0xD631,0x33);
		LCD_WriteReg(0xD632,0x03);
		LCD_WriteReg(0xD633,0x6D);
		//LV2 Page 0 enable
		LCD_WriteReg(0xF000,0x55);
		LCD_WriteReg(0xF001,0xAA);
		LCD_WriteReg(0xF002,0x52);
		LCD_WriteReg(0xF003,0x08);
		LCD_WriteReg(0xF004,0x00);
		//Display control
		LCD_WriteReg(0xB100, 0xCC);
		LCD_WriteReg(0xB101, 0x00);
		//Source hold time
		LCD_WriteReg(0xB600,0x05);
		//Gate EQ control
		LCD_WriteReg(0xB700,0x70);
		LCD_WriteReg(0xB701,0x70);
		//Source EQ control (Mode 2)
		LCD_WriteReg(0xB800,0x01);
		LCD_WriteReg(0xB801,0x03);
		LCD_WriteReg(0xB802,0x03);
		LCD_WriteReg(0xB803,0x03);
		//Inversion mode (2-dot)
		LCD_WriteReg(0xBC00,0x02);
		LCD_WriteReg(0xBC01,0x00);
		LCD_WriteReg(0xBC02,0x00);
		//Timing control 4H w/ 4-delay
		LCD_WriteReg(0xC900,0xD0);
		LCD_WriteReg(0xC901,0x02);
		LCD_WriteReg(0xC902,0x50);
		LCD_WriteReg(0xC903,0x50);
		LCD_WriteReg(0xC904,0x50);
		LCD_WriteReg(0x3500,0x00);
		LCD_WriteReg(0x3A00,0x55);  //16-bit/pixel
		LCD_WR_REG(0x1100);
		delay_us(120);
		LCD_WR_REG(0x2900);
	}
	LCD_Display_Dir(dir);		//Ä¬ÈÏÎªÊúÆÁ
	LCD_Clear(BLACK);
}

void LCD_Display_Dir(u8 dir)
{
	if(dir==0)			//ÊúÆÁ
	{
		lcddev.dir=0;	//ÊúÆÁ
		lcddev.width=480;
		lcddev.height=800;
	}else 				//ºáÆÁ
	{
		lcddev.dir=1;	//ºáÆÁ
		lcddev.width=800;
		lcddev.height=480;
	}
	lcddev.wramcmd=0X2C00;
	lcddev.setxcmd=0X2A00;
	lcddev.setycmd=0X2B00;

	LCD_Scan_Dir(DFT_SCAN_DIR);	//Ä¬ÈÏÉ¨Ãè·½Ïò
}

void LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u16 dirreg=0;
	u16 temp;
	if(lcddev.dir==1)
	{
		switch(dir)//·½Ïò×ª»»
		{
			case 0:dir=6;break;
			case 1:dir=7;break;
			case 2:dir=4;break;
			case 3:dir=5;break;
			case 4:dir=1;break;
			case 5:dir=0;break;
			case 6:dir=3;break;
			case 7:dir=2;break;
		}
	}
	if(lcddev.id==0X5510)
	{
		switch(dir)
		{
			case L2R_U2D://´Ó×óµ½ÓÒ,´ÓÉÏµ½ÏÂ
				regval|=(0<<7)|(0<<6)|(0<<5);
				break;
			case L2R_D2U://´Ó×óµ½ÓÒ,´ÓÏÂµ½ÉÏ
				regval|=(1<<7)|(0<<6)|(0<<5);
				break;
			case R2L_U2D://´ÓÓÒµ½×ó,´ÓÉÏµ½ÏÂ
				regval|=(0<<7)|(1<<6)|(0<<5);
				break;
			case R2L_D2U://´ÓÓÒµ½×ó,´ÓÏÂµ½ÉÏ
				regval|=(1<<7)|(1<<6)|(0<<5);
				break;
			case U2D_L2R://´ÓÉÏµ½ÏÂ,´Ó×óµ½ÓÒ
				regval|=(0<<7)|(0<<6)|(1<<5);
				break;
			case U2D_R2L://´ÓÉÏµ½ÏÂ,´ÓÓÒµ½×ó
				regval|=(0<<7)|(1<<6)|(1<<5);
				break;
			case D2U_L2R://´ÓÏÂµ½ÉÏ,´Ó×óµ½ÓÒ
				regval|=(1<<7)|(0<<6)|(1<<5);
				break;
			case D2U_R2L://´ÓÏÂµ½ÉÏ,´ÓÓÒµ½×ó
				regval|=(1<<7)|(1<<6)|(1<<5);
				break;
		}
		dirreg=0X3600;
		LCD_WriteReg(dirreg,regval);
		if(regval&0X20)
		{
			if(lcddev.width<lcddev.height)//½»»»X,Y
			{
				temp=lcddev.width;
				lcddev.width=lcddev.height;
				lcddev.height=temp;
			}
		}else
		{
			if(lcddev.width>lcddev.height)//½»»»X,Y
			{
				temp=lcddev.width;
				lcddev.width=lcddev.height;
				lcddev.height=temp;
			}
		}
		LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(0);
		LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(0);
		LCD_WR_REG(lcddev.setxcmd+2);LCD_WR_DATA((lcddev.width-1)>>8);
		LCD_WR_REG(lcddev.setxcmd+3);LCD_WR_DATA((lcddev.width-1)&0XFF);
		LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(0);
		LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(0);
		LCD_WR_REG(lcddev.setycmd+2);LCD_WR_DATA((lcddev.height-1)>>8);
		LCD_WR_REG(lcddev.setycmd+3);LCD_WR_DATA((lcddev.height-1)&0XFF);
	}
}

void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(Xpos>>8);
	LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(Xpos&0XFF);
	LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(Ypos>>8);
	LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(Ypos&0XFF);
}

void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}

void LCD_Clear(u16 color)
{
	int x, y, z;

	BACK_COLOR = color;
	printf("Clear the LCD now!\n");
	delay_ms(10);
	for(z=0; z<=240; z++)
	{
		for(y=z, x=y-1; x<lcddev.width-1-z; x++)
		{
			LCD_Fast_Draw_Point(x, y, color);
		}
		for(; y<lcddev.height-1-z; y++)
		{
			LCD_Fast_Draw_Point(x, y, color);
		}
		for(; x>z; x--)
		{
			LCD_Fast_Draw_Point(x, y, color);
		}
		for(; y>x+1; y--)
		{
			LCD_Fast_Draw_Point(x, y, color);
		}
	}
//	for(y=0; y<lcddev.height; y++)
//	{
//		for(x=0; x<lcddev.width; x++)
//		{
//			LCD_Fast_DrawPoint(x, y, color);
//		}
//	}
}

void LCD_Draw_Point(u16 x,u16 y)
{
	LCD_SetCursor(x,y);
	LCD_WriteRAM_Prepare();
	LCD_WR_DATA(POINT_COLOR);
}

void LCD_Fast_Draw_Point(u16 x,u16 y,u16 color)
{
	LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(x>>8);
	LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(x&0XFF);
	LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(y>>8);
	LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(y&0XFF);

	LCD_WR_REG(lcddev.wramcmd);
	LCD_WR_DATA(color);
}

void LCD_Init_PointList(Point *header)
{
	header->x = 0;
	header->y = 0;
	header->color = 0;
	header->next = NULL;
}

void LCD_DrawAndStore_Point(u16 x, u16 y, u16 color, Point *node)
{
	LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(x>>8);
	LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(x&0XFF);
	LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(y>>8);
	LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(y&0XFF);

	LCD_WR_REG(lcddev.wramcmd);
	LCD_WR_DATA(color);

	node->x = x;
	node->y = y;
	node->color = color;
	node->next = NULL;
}

void LCD_Draw_Line(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
	u16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //¼ÆËã×ø±êÔöÁ¿
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1; //ÉèÖÃµ¥²½·½Ïò
	else if(delta_x==0)incx=0;//´¹Ö±Ïß
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//Ë®Æ½Ïß
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x; //Ñ¡È¡»ù±¾ÔöÁ¿×ø±êÖá
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//»­ÏßÊä³ö
	{
		LCD_Fast_Draw_Point(uRow, uCol, color);
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

void LCD_Draw_Rectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
	LCD_Draw_Line(x1, y1, x1, y2, color);
	LCD_Draw_Line(x1, y2, x2, y2, color);
	LCD_Draw_Line(x2, y2, x2, y1, color);
	LCD_Draw_Line(x2, y1, x1, y1, color);
}

void LCD_Draw_Circle(u16 x0, u16 y0, u16 r, u16 color)
{
	int a,b;
	int di;

	a=0;
	b=r;
	di=3-(r<<1);

	while(a<=b)
	{
		LCD_Fast_Draw_Point(x0+a, y0-b, color);
		LCD_Fast_Draw_Point(x0+a, y0+b, color);
		LCD_Fast_Draw_Point(x0+b, y0-a, color);
		LCD_Fast_Draw_Point(x0+b, y0+a, color);
		LCD_Fast_Draw_Point(x0-a, y0-b, color);
		LCD_Fast_Draw_Point(x0-a, y0+b, color);
		LCD_Fast_Draw_Point(x0-b, y0-a, color);
		LCD_Fast_Draw_Point(x0-b, y0+a, color);
		a++;
		if(di<0)
			di += 4*a+6;
		else
		{
			di += 10+4*(a-b);
			b--;
		}
	}
}

void LCD_Draw_Ellipse(u16 x0, u16 y0, u16 xr, u16 yr, u16 color)
{
	int a,b;
	int di;
	float k;

	a = 0;
	di = 3-(xr<<1);             //ÅÐ¶ÏÏÂ¸öµãÎ»ÖÃµÄ±êÖ¾
	if(yr < xr)
	{
		b = xr;
		k = (float)yr/(float)xr;
	}
	else if(yr >= xr)
	{
		b = yr;
		k = (float)xr/(float)yr;
	}

	while(a<=b)
	{
		if(yr < xr)
		{
			LCD_Fast_Draw_Point(x0+a, y0-(int)(b*k), color);
			LCD_Fast_Draw_Point(x0+a, y0+(int)(b*k), color);
			LCD_Fast_Draw_Point(x0+b, y0-(int)(a*k), color);
			LCD_Fast_Draw_Point(x0+b, y0+(int)(a*k), color);
			LCD_Fast_Draw_Point(x0-a, y0-(int)(b*k), color);
			LCD_Fast_Draw_Point(x0-a, y0+(int)(b*k), color);
			LCD_Fast_Draw_Point(x0-b, y0-(int)(a*k), color);
			LCD_Fast_Draw_Point(x0-b, y0+(int)(a*k), color);
			a++;
			//Ê¹ÓÃBresenhamËã·¨»­Ô²
			if(di<0)
				di += 4*a+6;
			else
			{
				di += 10+4*(a-b);
				b--;
			}
		}
		else if(yr >= xr)
		{
			LCD_Fast_Draw_Point(x0+(int)(a*k), y0-b, color);
			LCD_Fast_Draw_Point(x0+(int)(a*k), y0+b, color);
			LCD_Fast_Draw_Point(x0+(int)(b*k), y0-a, color);
			LCD_Fast_Draw_Point(x0+(int)(b*k), y0+a, color);
			LCD_Fast_Draw_Point(x0-(int)(a*k), y0-b, color);
			LCD_Fast_Draw_Point(x0-(int)(a*k), y0+b, color);
			LCD_Fast_Draw_Point(x0-(int)(b*k), y0-a, color);
			LCD_Fast_Draw_Point(x0-(int)(b*k), y0+a, color);
			a++;
			//Ê¹ÓÃBresenhamËã·¨»­Ô²
			if(di<0)
				di += 4*a+6;
			else
			{
				di += 10+4*(a-b);
				b--;
			}
		}
	}
}

void LCD_Draw_Five_Pointed_Star1(u16 x0, u16 y0, u16 r, u16 color)
{
	u16 x[5], y[5];
	float sin18 = 0.309;
	float cos18 = 0.951;
	float sin54 = 0.809;
	float cos54 = 0.588;

	x[0] = x0;
	x[1] = x0 + (int)(r*cos18);
	x[2] = x0 + (int)(r*cos54);
	x[3] = x0 - (int)(r*cos54);
	x[4] = x0 - (int)(r*cos18);

	y[0] = y0 - r;
	y[1] = y0 - (int)(r*sin18);
	y[2] = y0 + (int)(r*sin54);
	y[3] = y0 + (int)(r*sin54);
	y[4] = y0 - (int)(r*sin18);

	LCD_Draw_Line(x[0], y[0], x[2], y[2], color);
	LCD_Draw_Line(x[2], y[2], x[4], y[4], color);
	LCD_Draw_Line(x[4], y[4], x[1], y[1], color);
	LCD_Draw_Line(x[1], y[1], x[3], y[3], color);
	LCD_Draw_Line(x[3], y[3], x[0], y[0], color);
}

void LCD_Draw_Five_Pointed_Star2(u16 x0, u16 y0, u16 r, u16 color)
{
	u16 x[10], y[10];
	float r2 = 0.382 * r;
	float sin18 = 0.309;
	float cos18 = 0.951;
	float sin54 = 0.809;
	float cos54 = 0.588;

	x[0] = x0;
	x[1] = x0 + (int)(r2*cos54);
	x[2] = x0 + (int)(r*cos18);
	x[3] = x0 + (int)(r2*cos18);
	x[4] = x0 + (int)(r*cos54);
	x[5] = x0;
	x[6] = x0 - (int)(r*cos54);
	x[7] = x0 - (int)(r2*cos18);
	x[8] = x0 - (int)(r*cos18);
	x[9] = x0 - (int)(r2*cos54);

	y[0] = y0 - r;
	y[1] = y0 - (int)(r2*sin54);
	y[2] = y0 - (int)(r*sin18);
	y[3] = y0 + (int)(r2*sin18);
	y[4] = y0 + (int)(r*sin54);
	y[5] = y0 + r2;
	y[6] = y0 + (int)(r*sin54);
	y[7] = y0 + (int)(r2*sin18);
	y[8] = y0 - (int)(r*sin18);
	y[9] = y0 - (int)(r2*sin54);

	LCD_Draw_Line(x[0], y[0], x[1], y[1], color);
	LCD_Draw_Line(x[1], y[1], x[2], y[2], color);
	LCD_Draw_Line(x[2], y[2], x[3], y[3], color);
	LCD_Draw_Line(x[3], y[3], x[4], y[4], color);
	LCD_Draw_Line(x[4], y[4], x[5], y[5], color);
	LCD_Draw_Line(x[5], y[5], x[6], y[6], color);
	LCD_Draw_Line(x[6], y[6], x[7], y[7], color);
	LCD_Draw_Line(x[7], y[7], x[8], y[8], color);
	LCD_Draw_Line(x[8], y[8], x[9], y[9], color);
	LCD_Draw_Line(x[9], y[9], x[0], y[0], color);
}

void LCD_Draw_Sin(u16 x_start, u16 x_end, u16 y, u16 cycle, u16 amp, u16 phase, u16 wid, u16 color)
{
	int i, j;
	double y_delta;
	u16 xpoint_old, ypoint_old;
	u16 xpoint_new, ypoint_new;

	for(i=0; i<=x_end-x_start; i++)
	{
		y_delta = amp * sin(2*M_PI*(i+phase)/cycle);
		xpoint_new = x_start + i;
		ypoint_new = y - (int)y_delta;
		LCD_Draw_Line(xpoint_new, ypoint_new-wid/2, xpoint_new, ypoint_new+(wid-1)/2, color);
		if(i)
		{
			for(j=-wid/2; j<=(wid-1)/2; j++)
				LCD_Draw_Line(xpoint_old, ypoint_old+j, xpoint_new, ypoint_new+j, RED);
		}
		xpoint_old = xpoint_new;
		ypoint_old = ypoint_new;
	}
}

void LCD_Fill_Rectangle(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{
	u16 i;
	for(i=sy;i<=ey;i++)
		LCD_Draw_Line(sx, i, ex, i, color);
}

void LCD_Fill_Circle(u16 x0, u16 y0, u16 r, u16 color)
{
	int a,b;
	int di;

	a=0;
	b=r;
	di=3-(r<<1);             //ÅÐ¶ÏÏÂ¸öµãÎ»ÖÃµÄ±êÖ¾

	while(a<=b)
	{
		LCD_Draw_Line(x0+a, y0-b, x0+a, y0+b, color);
		LCD_Draw_Line(x0+b, y0-a, x0+b, y0+a, color);
		LCD_Draw_Line(x0-a, y0-b, x0-a, y0+b, color);
		LCD_Draw_Line(x0-b, y0-a, x0-b, y0+a, color);

		a++;
		//Ê¹ÓÃBresenhamËã·¨»­Ô²
		if(di<0)
			di += 4*a+6;
		else
		{
			di += 10+4*(a-b);
			b--;
		}
	}
}

void LCD_Fill_Heart(u16 x0, u16 y0, u16 r, u16 color)
{
	int i;
	float k;
	double r_float;
	double big, small;
	int y_up, y_down;

	k = r / 2.0;

	for(i=-r; i<=r; i++)
	{
		r_float = i / k;
		big = sqrt(1-pow(fabs(r_float)-1,2));
		small = acos(1-fabs(r_float)) - M_PI;
		y_up = y0 - (int)(big*k);
		y_down = y0 - (int)(small*k);
		LCD_Draw_Line(x0+i, y_up, x0+i, y_down, color);
	}
}



void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//µÃµ½×ÖÌåÒ»¸ö×Ö·û¶ÔÓ¦µãÕó¼¯ËùÕ¼µÄ×Ö½ÚÊý
 	num=num-' ';//µÃµ½Æ«ÒÆºóµÄÖµ£¨ASCII×Ö¿âÊÇ´Ó¿Õ¸ñ¿ªÊ¼È¡Ä££¬ËùÒÔ-' '¾ÍÊÇ¶ÔÓ¦×Ö·ûµÄ×Ö¿â£©
	for(t=0;t<csize;t++)
	{
		if(size==12)temp=asc2_1206[num][t]; 	 	//µ÷ÓÃ1206×ÖÌå
		else if(size==16)temp=asc2_1608[num][t];	//µ÷ÓÃ1608×ÖÌå
		else if(size==24)temp=asc2_2412[num][t];	//µ÷ÓÃ2412×ÖÌå
		else return;								//Ã»ÓÐµÄ×Ö¿â
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Fast_Draw_Point(x,y,POINT_COLOR);//0x80=1000 0000
			else if(mode==0)LCD_Fast_Draw_Point(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=lcddev.height)return;		//³¬ÇøÓòÁË
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)return;	//³¬ÇøÓòÁË
				break;
			}
		}
	}
}

u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)result*=m;
	return result;
}

void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{
	u8 t,temp;
	u8 enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1;

		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0);
	}
}

void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{
	u8 t,temp;
	u8 enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);
 				continue;
			}else enshow=1;

		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01);
	}
}

void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//ÅÐ¶ÏÊÇ²»ÊÇ·Ç·¨×Ö·û!
    {
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//ÍË³ö
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }
}

//��һ������
//(x1,y1),(x2,y2):��������ʼ����
//size�������Ĵ�ϸ�̶�
//color����������ɫ
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	if(x1<size|| x2<size||y1<size|| y2<size)return;
	delta_x=x2-x1; //������������
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1; //���õ�������
	else if(delta_x==0)incx=0;//��ֱ��
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//ˮƽ��
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//�������
	{
		gui_fill_circle(uRow,uCol,size,color);//����
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}
