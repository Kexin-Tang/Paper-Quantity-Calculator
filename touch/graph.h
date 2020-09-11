#ifndef SRC_LCD_GRAPH_H_
#define SRC_LCD_GRAPH_H_

#include "..\lcd\lcd.h"

void Draw_Graph_Num(u16 x, u16 y, u16 width, u16 height);	//��������0~9��С���㲿��
void Draw_Start(void);	//�������ܰ�������ʼ���棩
void touch_Adjust(u16 x, u16 y, u16 weight, u16 height);			//����У׼����
void Graw_Short_Detect(void);								//������·��⹦�ܽ���
double Get_Data(int n);										//�������ε�ƽ��ֵ
double IIR(void);
void Recover_Rectangle(int x, int y, int x2, int y2, int x_word, int y_word, u8 *p);

#endif /* SRC_LCD_GRAPH_H_ */

