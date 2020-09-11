#ifndef SRC_LCD_GRAPH_H_
#define SRC_LCD_GRAPH_H_

#include "..\lcd\lcd.h"

void Draw_Graph_Num(u16 x, u16 y, u16 width, u16 height);	//画出数字0~9及小数点部分
void Draw_Start(void);	//画出功能按键（起始界面）
void touch_Adjust(u16 x, u16 y, u16 weight, u16 height);			//画出校准界面
void Graw_Short_Detect(void);								//画出短路检测功能界面
double Get_Data(int n);										//计算出多次的平均值
double IIR(void);
void Recover_Rectangle(int x, int y, int x2, int y2, int x_word, int y_word, u8 *p);

#endif /* SRC_LCD_GRAPH_H_ */

