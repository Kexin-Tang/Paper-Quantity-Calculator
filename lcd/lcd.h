#ifndef __LCD_H
#define __LCD_H
//#include "sys.h"
#include "xil_printf.h"
#include "stdlib.h"
//////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	u16 width;
	u16 height;
	u16 id;
	u8  dir;
	u16	wramcmd;
	u16  setxcmd;
	u16  setycmd;
}_lcd_dev;

typedef struct Point
{
	u16 x;
	u16 y;
	u16 color;
	struct Point *next;
}Point;

typedef struct Quadrant
{
	u16 xpoint;
	u16 ypoint;
	u16 l_len;
	u16 r_len;
	u16 u_len;
	u16 d_len;
	u16 axis_wid;
	u16 grid_size;
	u16 color_axis;
	u16 color_grid;

	u16 xl;
	u16 xr;
	u16 yu;
	u16 yd;
}Quadrant;

extern _lcd_dev lcddev;

extern u16  POINT_COLOR;
extern u16  BACK_COLOR;

//////////////////////////////////////////////////////////////////////////////////

#define L2R_U2D  0
#define L2R_D2U  1
#define R2L_U2D  2
#define R2L_D2U  3

#define U2D_L2R  4
#define U2D_R2L  5
#define D2U_L2R  6
#define D2U_R2L  7

#define DFT_SCAN_DIR  L2R_U2D

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //脳脴脡芦
#define BRRED 			 0XFC07 //脳脴潞矛脡芦
#define GRAY  			 0X8430 //禄脪脡芦

#define DARKBLUE      	 0X01CF	//脡卯脌露脡芦
#define LIGHTBLUE      	 0X7D7C	//脟鲁脌露脡芦
#define GRAYBLUE       	 0X5458 //禄脪脌露脡芦

#define LIGHTGREEN     	 0X841F //脟鲁脗脤脡芦
#define LIGHTGRAY        0XEF5B //脟鲁禄脪脡芦(PANNEL)
#define LGRAY 			 0XC618 //脟鲁禄脪脡芦(PANNEL),麓掳脤氓卤鲁戮掳脡芦

#define LGRAYBLUE        0XA651 //脟鲁禄脪脌露脡芦(脰脨录盲虏茫脩脮脡芦)
#define LBBLUE           0X2B12 //脟鲁脳脴脌露脡芦(脩隆脭帽脤玫脛驴碌脛路麓脡芦)

#define SSD_HOR_RESOLUTION		800		//LCD脣庐脝陆路脰卤忙脗脢
#define SSD_VER_RESOLUTION		480		//LCD麓鹿脰卤路脰卤忙脗脢

#define SSD_HOR_PULSE_WIDTH		1		//脣庐脝陆脗枚驴铆
#define SSD_HOR_BACK_PORCH		46		//脣庐脝陆脟掳脌脠
#define SSD_HOR_FRONT_PORCH		210		//脣庐脝陆潞贸脌脠

#define SSD_VER_PULSE_WIDTH		1		//麓鹿脰卤脗枚驴铆
#define SSD_VER_BACK_PORCH		23		//麓鹿脰卤脟掳脌脠
#define SSD_VER_FRONT_PORCH		22		//麓鹿脰卤脟掳脌脠

#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

/*鏃堕棿鍑芥暟*/
void delay_ms(int ms);
void delay_us(int us);

/*鍩烘湰搴曞眰鍑芥暟*/
void LCD_WR_REG(u32 regval);
void LCD_WR_DATA(u32 data);
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_WriteRAM_Prepare(void);

/*鍒濆鍖栦笌澶嶄綅鍑芥暟*/
void LCD_Reset(void);
void LCD_Init(u8 dir);
void LCD_Display_Dir(u8 dir);
void LCD_Scan_Dir(u8 dir);

/*娓呭睆*/
void LCD_Clear(u16 Color);

/*鐢荤偣*/
void LCD_Draw_Point(u16 x, u16 y);
void LCD_Fast_Draw_Point(u16 x, u16 y, u16 color);
void LCD_Init_PointList(Point *header);
void LCD_DrawAndStore_Point(u16 x, u16 y, u16 color, Point *node);

/*鐢荤嚎*/
void LCD_Draw_Line(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

/*鐢诲钩闈㈠舰鐘�*/
void LCD_Draw_Rectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void LCD_Draw_Circle(u16 x0, u16 y0, u16 r, u16 color);
void LCD_Draw_Ellipse(u16 x0, u16 y0, u16 xr, u16 yr, u16 color);
void LCD_Draw_Five_Pointed_Star1(u16 x0, u16 y0, u16 r, u16 color);
void LCD_Draw_Five_Pointed_Star2(u16 x0, u16 y0, u16 r, u16 color);
void LCD_Draw_Sin(u16 x_start, u16 x_end, u16 y, u16 cycle, u16 amp, u16 phase, u16 wid, u16 color);

/*濉钩闈㈠舰鐘�*/
void LCD_Fill_Rectangle(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void LCD_Fill_Circle(u16 x0, u16 y0, u16 r, u16 color);
void LCD_Fill_Heart(u16 x0, u16 y0, u16 r, u16 color);

/*鐢诲潗鏍囩郴*/
void LCD_Init_Quadrant(Quadrant *quad);
void LCD_Draw_Quadrant(Quadrant *quad);



/*鐢昏〃鏍�*/



void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color);


#endif
