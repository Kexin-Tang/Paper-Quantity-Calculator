#include "graph.h"
#include "..\lcd\lcd.h"
#include "..\touch\touch.h"
#include "math.h"
#include "cal.h"
#include "xil_printf.h"
#include "..\fdc2214\fdc2214.h"

#define M 30	//ʹ�ò�ͬ���ߵ�ת�۵�

int func,cnt;
double short_num=0.0;	//���ڴ洢��·��ֵ
extern u32 ch0,ch1,ch2,ch3;
double cap = 0.0;
float a,b,c,d;			//a,b��1~30��ֽ��Ӧ�����߲�����	c,d��30~40�Ŷ�Ӧ�����߲���
float e,f,g,h;			//e,f��40~50�Ŷ�Ӧ�����߲�����	g,h��50~60�Ŷ�Ӧ�����߲���
double change_30,change_40,change_50;			//�洢�������߽����Ӧ�ĵ���ֵ���˴���Ϊ��M��ֽ����Ӧ

double e_sum_new = 0.0;

double CAP_INIT=53.5;

CP cp;
Cal cal;

int x[N];
double y[N];

//
//	����Ļ�ϻ������ְ���
//
//		x 	-> 	���Ͻ���ʼ������
//		y 	-> 	���Ͻ���ʼ������
//	weight 	->	�����Ŀ��
//	height 	->	�����ĸ߶�
//
void Draw_Graph_Num(u16 x,u16 y,u16 weight,u16 height)
{
	POINT_COLOR = YELLOW;
	//���߿�
	int i = 0;
	for( ; i<5 ; i++)
		LCD_Draw_Line(x,y+i*height,x+weight*3,y+i*height,WHITE);

	for(i=0; i<4 ; i++)
		LCD_Draw_Line(x+i*weight,y,x+i*weight,y+height*4,WHITE);

	//�����ֺ�С����,ע���������size
	//!!!!!!!!!!!!!!!!!!!!!!!!!��һ������û�л�����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	LCD_ShowNum(x+weight/2,y+height/2,7,1,24);
	LCD_ShowNum(x+weight/2+weight,y+height/2,8,1,24);
	LCD_ShowNum(x+weight/2+weight*2,y+height/2,9,1,24);

	LCD_ShowNum(x+weight/2,y+height/2+height,4,1,24);
	LCD_ShowNum(x+weight/2+weight,y+height/2+height,5,1,24);
	LCD_ShowNum(x+weight/2+weight*2,y+height/2+height,6,1,24);

	LCD_ShowNum(x+weight/2,y+height/2+height*2,1,1,24);
	LCD_ShowNum(x+weight/2+weight,y+height/2+height*2,2,1,24);
	LCD_ShowNum(x+weight/2+weight*2,y+height/2+height*2,3,1,24);

	LCD_Fill_Circle(x+weight/2,y+height/2+height*3,2,WHITE);
	LCD_ShowNum(x+weight/2+weight,y+height/2+height*3,0,1,24);
	LCD_ShowString(x+weight/2+weight*2,y+height/2+height*3,200,24,24,"Del");
}

//
//	����Ļ����ʾ��ʼ����
//
//�Ƽ���СDraw_Start(90,200,300,150,50);
//
void Draw_Start(void)
{
	int flag = 0;

	int i;
	for(i=0; i<N; i++)
	{
		x[i] = 0;
		y[i] = 0.0;
	}

	cp_init(&cp,&cal);

	//д�����
	POINT_COLOR = YELLOW;
	LCD_ShowString(100,100,200,24,24,"NUEDC F");

	//������У׼�����ܰ���
	LCD_Draw_Rectangle(90,200,390,300,WHITE);
	LCD_ShowString(200,250,200,24,24,"Adjust");

	//��������·��⡱����
	LCD_Draw_Rectangle(90,350,390,450,WHITE);
	LCD_ShowString(170,400,200,24,24,"Short Setting");

	//��������ʼ����������
	LCD_Draw_Rectangle(90,500,390,600,WHITE);
	LCD_ShowString(200,550,200,24,24,"Start");

	//��������ʼ����������
	LCD_Draw_Rectangle(90,650,390,750,WHITE);
	LCD_ShowString(200,700,200,24,24,"Game");

	while(1)
	{
		while(1)
		{
			tp_dev.scan(0);
			if(tp_dev.sta &(1<<0))
			{
				int x = tp_dev.x[0];
				int y = tp_dev.y[0];

				if(x>=90 & x<=390)
				{
					if(y>=200& y<=300)
					{
						LCD_Draw_Rectangle(90,200,390,300,RED);
						flag = 1;
						while(tp_dev.sta &(1<<0))
						{
							tp_dev.scan(0);
						}
						LCD_Draw_Rectangle(90,200,390,300,WHITE);
						break;
					}

					else if(y>=350 & y<=450)
					{
						LCD_Draw_Rectangle(90,350,390,450,RED);
						flag = 2;
						while(tp_dev.sta &(1<<0))
						{
							tp_dev.scan(0);
						}
						LCD_Draw_Rectangle(90,350,390,450,WHITE);
						break;
					}


					else if(y>=500 & y<= 600)
					{
						LCD_Draw_Rectangle(90,500,390,600,RED);
						flag = 3;
						while(tp_dev.sta &(1<<0))
						{
							tp_dev.scan(0);
						}
						LCD_Draw_Rectangle(90,500,390,600,WHITE);
						break;
					}

					else if(y>=650 & y<= 750)
					{
						LCD_Draw_Rectangle(90,650,390,750,RED);
						flag = 4;
						while(tp_dev.sta &(1<<0))
						{
							tp_dev.scan(0);
						}
						LCD_Draw_Rectangle(90,650,390,750,WHITE);
						break;
					}

					else
						;
				}
				else
					;
			}
		}

		switch(flag)
		{
			case 1:{LCD_Clear(BLACK);	Draw_Adjust(); flag=0;	break;}
			case 2:{LCD_Clear(BLACK);	Graw_Short_Detect(); 	flag=0;	break;}
			case 3:{LCD_Clear(BLACK);	Start(); 	flag=0;break;}
			case 4:{LCD_Clear(BLACK);	Game(); 	flag=0;break;}
			default: break;
		}
	}
}


//	������У׼���Ĺ��ܽ���
void Draw_Adjust(void)
{
	int sum = 0;	//��¼�����ֽ������

	//��������
	Draw_Graph_Num(1,400,158,100);

	//������ȷ����������"����"����
	LCD_Draw_Rectangle(240,300,476,400,WHITE);
	LCD_ShowString(90,330,200,24,24,"Store");
	LCD_Draw_Rectangle(1,300,240,400,WHITE);
	LCD_ShowString(90+240,330,200,24,24,"OK");

	POINT_COLOR = GREEN;
	LCD_ShowString(50,0,200,24,24,"Capcity(pF):");
	LCD_ShowString(400,0,200,24,24," pF");
	LCD_ShowString(50,200,400,24,24,"You have entered       data");
	LCD_ShowString(50,100,400,24,24,"You have put           paper");

	while(func!=12)
	{
		touch_Adjust(0,400,160,100);

		//�����������
		if(0<=func & func<=9)
		{
			LED(1);
			POINT_COLOR = RED;
			sum = func;
			LCD_ShowNum(220,100,sum,3,24);
			while(tp_dev.sta&(1<<0))
					tp_dev.scan(0);
			LED(0);
			//ֱ������OK���˳�������һֱ��¼����
			while(1)
			{
				touch_Adjust(0,400,160,100);
				//�������ok���˳�
				if(func == 13)
				{
					LED(1);
					cnt++;
					POINT_COLOR=BLACK;
					LCD_ShowNum(220,100,888,3,24);		//���Ĺ����ֵ
					POINT_COLOR = RED;
					LCD_ShowNum(250,200,cnt,3,24);

					cap = IIR();				//��ȡ���ݵ�ƽ��ֵ
					y[sum] = cap;		//�洢��Ӧ����ֵ
					x[sum] = sum;		//�洢��Ӧֽ����

					if(sum == 0)
					{
						CAP_INIT = cap;
						printf("Cap_Init: %f\n",cap);
					}
					else if(sum == 30)				//���õ�30��ֽ�ı亯��
					{
						change_30 = cap;
						printf("change_30: %f\n",cap);
					}
					else if(sum == 40)
					{
						change_40 = cap;
						printf("change_40: %f\n",cap);
					}
					else if(sum == 50)
					{
						change_50 = cap;
						printf("change_50: %f\n",cap);
					}
					else
						;

					POINT_COLOR = BLACK;
					LCD_ShowNum(200,0,888888888888,12,24);

					POINT_COLOR = RED;
					LCD_ShowString(240,0,400,24,24,".");
					LCD_ShowNum(200,0,(int)cap,3,24);
					LCD_ShowNum(250,0,(cap - (int)cap)*1000,3,24);
					LED(0);
					sum = 0;
				}
				else if(0<=func && func <=9)
				{
					LED(1);
					sum*=10;
					sum+=func;
					LCD_ShowNum(220,100,sum,3,24);
					while(tp_dev.sta&(1<<0))
					    tp_dev.scan(0);
					LED(0);
				}
				else if(func == 11)
				{
					LED(1);
					sum=0;
					POINT_COLOR=BLACK;
					LCD_ShowNum(220,100,888,3,24);		//���Ĺ����ֵ
					POINT_COLOR = RED;
					LED(0);
				}
				else if(func == 12)
					break;
				else
					;
			}
		}
		else
			;
	}

	func = 0;
	LED(1);
	jiao_zhun(&cp, &cal,x,y,1,30,&a,&b);
	jiao_zhun(&cp, &cal,x,y,30,40,&c,&d);
	jiao_zhun(&cp, &cal,x,y,40,50,&e,&f);
	jiao_zhun(&cp, &cal,x,y,50,60,&g,&h);
	LED(0);

	printf("a=%f,	b=%f\n",a,b);
	printf("c=%f,	d=%f\n",c,d);

	//���س�ʼ����
	cnt = 0;
	LCD_Clear(BLACK);
	//д�����
		POINT_COLOR = YELLOW;
		LCD_ShowString(100,100,200,24,24,"NUEDC F");

		//������У׼�����ܰ���
		LCD_Draw_Rectangle(90,200,390,300,WHITE);
		LCD_ShowString(200,250,200,24,24,"Adjust");

		//��������·��⡱����
		LCD_Draw_Rectangle(90,350,390,450,WHITE);
		LCD_ShowString(170,400,200,24,24,"Short Setting");

		//��������ʼ����������
		LCD_Draw_Rectangle(90,500,390,600,WHITE);
		LCD_ShowString(200,550,200,24,24,"Start");

		//��������ʼ����������
		LCD_Draw_Rectangle(90,650,390,750,WHITE);
		LCD_ShowString(200,700,200,24,24,"Game");
}



//
//	������
//
//	����ڷ�Χ�ڣ�����Ϊ���µ���0~9��С����
//	����ڷ�Χ�⣬���������������
//
void touch_Adjust(u16 x, u16 y, u16 weight, u16 height)
{
	tp_dev.scan(0);
	if(tp_dev.sta &(1<<0))
	{
		int x_place = tp_dev.x[0];
		int y_place = tp_dev.y[0];

		while(tp_dev.sta&(1<<0))
			tp_dev.scan(0);

		//��������ּ��̷�Χ��
		if((x<=x_place & x_place<=x+weight*3) & (y<=y_place & y_place<=y+height*5))
		{
			if((x<=x_place&x_place<=x+weight)&(y<=y_place&y_place<=y+height))
				func = 7;

			else if((x+weight<=x_place&x_place<=x+weight*2)&(y<=y_place&y_place<=y+height))
				func = 8;

			else if((x+weight*2<=x_place&x_place<=x+weight*3)&(y<=y_place&y_place<=y+height))
				func = 9;

			else if((x<=x_place&x_place<=x+weight)&(y+height<=y_place&y_place<=y+height*2))
				func = 4;

			else if((x+weight<=x_place&x_place<=x+weight*2)&(y+height<=y_place&y_place<=y+height*2))
				func = 5;

			else if((x+weight*2<=x_place&x_place<=x+weight*3)&(y+height<=y_place&y_place<=y+height*2))
				func = 6;

			else if((x<=x_place&x_place<=x+weight)&(y+height*2<=y_place&y_place<=y+height*3))
				func = 1;

			else if((x+weight<=x_place&x_place<=x+weight*2)&(y+height*2<=y_place&y_place<=y+height*3))
				func = 2;

			else if((x+weight*2<=x_place&x_place<=x+weight*3)&(y+height*2<=y_place&y_place<=y+height*3))
				func = 3;

			else if((x+weight<=x_place&x_place<=x+weight*2)&(y+height*3<=y_place&y_place<=y+height*4))
				func = 0;

			else if((x<=x_place&x_place<=x+weight)&(y+height*3<=y_place&y_place<=y+height*4))
				func = 10;		//�����ص���С����"."

			else if((x+weight*2<=x_place&x_place<=x+weight*3)&(y+height*3<=y_place&y_place<=y+height*4))
				func = 11;		//�����ص���"Del"
		}

		//�������ּ��̷�Χ��
		else if(y_place<=400 & y_place >= 300)
		{
			if((0<=x_place&x_place<240))
			{
				func = 12;	//�����˳��ý���
			}
			else if((240<x_place&x_place<480))
			{
				POINT_COLOR = RED;
				func = 13;
			}
			else
				;
		}
	}
	else
		func = -1;
}


//
//
//
void Graw_Short_Detect(void)
{
	POINT_COLOR = YELLOW;
	//��������·��⡱����
	LCD_Draw_Rectangle(90,400,390,550,WHITE);
	LCD_ShowString(170,475,200,24,24,"Setting");

	//��������ʼ����������
	LCD_Draw_Rectangle(90,600,390,750,WHITE);
	LCD_ShowString(200,675,200,24,24,"Back");

	while(1)
	{
		tp_dev.scan(0);
		if(tp_dev.sta&(1<<0))
		{
			int x = tp_dev.x[0];
			int y = tp_dev.y[0];
			if(90<=x & x<=390)
			{
				if(400<=y & y<=550)
				{
					LCD_Draw_Rectangle(90,400,390,550,RED);
					while(tp_dev.sta&(1<<0))
						tp_dev.scan(0);
					LCD_Draw_Rectangle(90,400,390,550,WHITE);

					LED(1);
					short_num =IIR();
					POINT_COLOR = RED;
					LCD_ShowString(100,100,200,24,24,"Setting OK !");
					POINT_COLOR = WHITE;
					delay_ms(1000);
					LED(0);
					break;
				}
				else if(600<=y & y<=750)
				{
					LCD_Draw_Rectangle(90,600,390,750,RED);
					while(tp_dev.sta&(1<<0))
						tp_dev.scan(0);
					LCD_Draw_Rectangle(90,600,390,750,WHITE);
					break;
				}
				else
					;
			}
			else
				;
		}
	}

	//���س�ʼ����
		cnt = 0;
		LCD_Clear(BLACK);
		//д�����
			POINT_COLOR = YELLOW;
			LCD_ShowString(100,100,200,24,24,"NUEDC F");

			//������У׼�����ܰ���
			LCD_Draw_Rectangle(90,200,390,300,WHITE);
			LCD_ShowString(200,250,200,24,24,"Adjust");

			//��������·��⡱����
			LCD_Draw_Rectangle(90,350,390,450,WHITE);
			LCD_ShowString(170,400,200,24,24,"Short Setting");

			//��������ʼ����������
			LCD_Draw_Rectangle(90,500,390,600,WHITE);
			LCD_ShowString(200,550,200,24,24,"Start");

			//��������ʼ����������
			LCD_Draw_Rectangle(90,650,390,750,WHITE);
			LCD_ShowString(200,700,200,24,24,"Game");
}



double IIR(void)
{
	const double lambda = 0.1;
	double out = 0.f;
	int i=0;
	double freq = 0.0;
	double in = 0.0;
	while(i<300)
	{
		FDC2214_GetData();
		freq = FDC2214_CalculateFrequency(FDC2214_Channel_2,ch2);
		in = FDC2214_CalculateCapacitance(freq, 0.000018,33);
		out = out * (1.f - lambda) +  in*lambda;
		i++;
		delay_ms(5);
	}
	return out;
}

void FDC2214_GetData(void)
{
    FDC2214_GetChannelData(FDC2214_Channel_0, &ch0);
    FDC2214_GetChannelData(FDC2214_Channel_1, &ch1);
    FDC2214_GetChannelData(FDC2214_Channel_2, &ch2);
    FDC2214_GetChannelData(FDC2214_Channel_3, &ch3);
}

void Start(void)
{

	double num=0.0;
	double distance =0.0;
	double paper = 0.0;
	int paper_number=0;
	int back = 0;

	POINT_COLOR = YELLOW;
	//��������·��⡱����
	LCD_Draw_Rectangle(90,400,390,550,WHITE);
	LCD_ShowString(170,475,200,24,24,"Start");

	//��������ʼ����������
	LCD_Draw_Rectangle(90,600,390,750,WHITE);
	LCD_ShowString(200,675,200,24,24,"Back");

	POINT_COLOR = YELLOW;
	LCD_ShowString(100,100,200,24,24,"Paper number: ");

	while(!back)
	{
		tp_dev.scan(0);
		if(tp_dev.sta&(1<<0))
		{
			int x = tp_dev.x[0];
			int y = tp_dev.y[0];

			if(90<=x & x<=390)
			{
				if(400<=y & y<=550)
				{
					LCD_Draw_Rectangle(90,400,390,550,RED);
					while(tp_dev.sta&(1<<0))
						tp_dev.scan(0);
					LCD_Draw_Rectangle(90,400,390,550,WHITE);

					LED(1);
					num = IIR();

					//�ж��Ƿ��·
					if(num<=short_num+1 && num>=short_num-1)
					{
						POINT_COLOR = RED;
						LCD_ShowString(100,200,200,24,24,"Short !!");
						delay_ms(2000);
						POINT_COLOR = BLACK;
						LCD_ShowString(100,200,200,24,24,"          ");
						LCD_ShowNum(100,200,88888888,8,24);
					}
					else
					{
						if(num>=change_30)		//���С��ת�۵㣬ʹ��a,b
						{
							distance= cal.e * cal.S / (num - cal.cap_bias);
							paper = ((distance - a)/b);
						}
						else if(num >= change_40)
						{
							distance= cal.e * cal.S / (num - cal.cap_bias);
							paper = ((distance - c)/d);
						}
						else if(num >= change_50)
						{
							distance= cal.e * cal.S / (num - cal.cap_bias);
							paper = ((distance - e)/f);
						}
						else
						{
							distance= cal.e * cal.S / (num - cal.cap_bias);
							paper = ((distance - g)/h);
						}

						//����������ֽ����
						paper_number = round(paper);

						POINT_COLOR = RED;
						LCD_ShowNum(300,100,paper_number,3,24);
					}
					LED(0);
					Beep();
					paper = 0.0;
				}
				else if(600<=y & y<=750)
				{
					LCD_Draw_Rectangle(90,600,390,750,RED);
					while(tp_dev.sta&(1<<0))
						tp_dev.scan(0);
					LCD_Draw_Rectangle(90,600,390,750,WHITE);
					back = 1;
				}
				else
					;
			}
			else
				;
		}
	}
	back = 0;
		//���س�ʼ����
		cnt = 0;
		LCD_Clear(BLACK);
		//д�����
			POINT_COLOR = YELLOW;
			LCD_ShowString(100,100,200,24,24,"NUEDC F");

			//������У׼�����ܰ���
			LCD_Draw_Rectangle(90,200,390,300,WHITE);
			LCD_ShowString(200,250,200,24,24,"Adjust");

			//��������·��⡱����
			LCD_Draw_Rectangle(90,350,390,450,WHITE);
			LCD_ShowString(170,400,200,24,24,"Short Setting");

			//��������ʼ����������
			LCD_Draw_Rectangle(90,500,390,600,WHITE);
			LCD_ShowString(200,550,200,24,24,"Start");

			//��������ʼ����������
			LCD_Draw_Rectangle(90,650,390,750,WHITE);
			LCD_ShowString(200,700,200,24,24,"Game");
}



void Game(void)
{

	int back = 0;
	int cnt = 3;
	double num=0.0;
	double distance =0.0;
	double paper = 0.0;
	int paper_number=0;
	int paper_rand = 0;
	int finish = 0;

	//��UI����

	POINT_COLOR = GREEN;
	LCD_ShowString(100,50,200,24,24,"Chance:	");
	LCD_ShowString(100,100,200,24,24,"You got: ");
	LCD_ShowString(100,150,200,24,24,"Consequence: ");

	POINT_COLOR = RED;
	LCD_ShowNum(200,50,cnt,1,24);

	POINT_COLOR = YELLOW;
	//������Restart������
	LCD_Draw_Rectangle(90,200,390,350,WHITE);
	LCD_ShowString(170,275,200,24,24,"Restart");

	//������OK������
	LCD_Draw_Rectangle(90,400,390,550,WHITE);
	LCD_ShowString(170,475,200,24,24,"OK");

	//������Back������
	LCD_Draw_Rectangle(90,600,390,750,WHITE);
	LCD_ShowString(200,675,200,24,24,"Back");

	while(!back)
	{
		tp_dev.scan(0);
		if(tp_dev.sta&(1<<0))
		{
			int x = tp_dev.x[0];
			int y = tp_dev.y[0];
			if(90<=x & x<=390)
			{
				if(!finish & 400<=y & y<=550)
				{
					LCD_Draw_Rectangle(90,400,390,550,RED);
					while(tp_dev.sta&(1<<0))
						tp_dev.scan(0);
					LCD_Draw_Rectangle(90,400,390,550,WHITE);

					LED(1);
					num = IIR();
					distance= cal.e * cal.S / (num - cal.cap_bias);
					paper = ((distance - a)/b);


					//����������ֽ����
					paper_number = round(paper);

					POINT_COLOR = RED;
					LCD_ShowNum(300,100,paper_number,3,24);

					cnt--;
					//�ж���Ϸ�Ƿ����
					if(!finish & cnt == 0)
					{
						POINT_COLOR = BLACK;
						LCD_ShowString(200,150,200,24,24,"              ");
						LCD_ShowNum(300,100,888,3,24);
						POINT_COLOR = RED;
						LCD_ShowString(200,150,200,24,24,"Failed");
						LCD_ShowNum(300,100,paper_number,3,24);

						POINT_COLOR = BLACK;
						LCD_ShowNum(200,50,8,1,24);
						POINT_COLOR = RED;
						LCD_ShowNum(200,50,cnt,1,24);
						finish = 1;
					}
					else if(!finish & cnt !=0)
					{
						POINT_COLOR = BLACK;
						LCD_ShowNum(200,50,8,1,24);
						POINT_COLOR = RED;
						LCD_ShowNum(200,50,cnt,1,24);
					}
					else
						;

					//����
					if(!finish && paper_rand>paper_number)
					{
						POINT_COLOR = BLACK;
						LCD_ShowString(200,150,200,24,24,"       ");
						LCD_ShowNum(300,100,888,3,24);
						POINT_COLOR = RED;
						LCD_ShowString(200,150,200,24,24,"too little");
						LCD_ShowNum(300,100,paper_number,3,24);
					}

					else if(!finish && paper_rand<paper_number)
					{
						POINT_COLOR = BLACK;
						LCD_ShowString(200,150,200,24,24,"       ");
						LCD_ShowNum(300,100,888,3,24);
						POINT_COLOR = RED;
						LCD_ShowString(200,150,200,24,24,"too much");
						LCD_ShowNum(300,100,paper_number,3,24);
					}
					else if(!finish && paper_rand==paper_number)
					{
						POINT_COLOR = BLACK;
						LCD_ShowString(200,150,200,24,24,"       ");
						LCD_ShowNum(300,100,888,3,24);
						POINT_COLOR = RED;
						LCD_ShowString(200,150,200,24,24,"Bingo !!");
						LCD_ShowNum(300,100,paper_number,3,24);
						finish = 1;
					}
					else
						;
					LED(0);
				}

				else if(200<=y & y<=350)
				{
					LCD_Draw_Rectangle(90,200,390,350,RED);
					while(tp_dev.sta&(1<<0))
						tp_dev.scan(0);
					LCD_Draw_Rectangle(90,200,390,350,WHITE);

					LED(1);

					paper_rand = rand()%30+1;	//����1~30�����ֽ��

					LCD_Fill_Rectangle(0,0,480,190,BLACK);
					POINT_COLOR = GREEN;
					LCD_ShowString(100,50,200,24,24,"Chance:	");
					LCD_ShowString(100,100,200,24,24,"You got: ");
					LCD_ShowString(100,150,200,24,24,"Conseq: ");
					cnt = 3;
					POINT_COLOR = RED;
					LCD_ShowNum(200,50,cnt,1,24);
					LCD_ShowNum(100,0,paper_rand,3,24);
					finish = 0;

					LED(0);
				}

				else if(600<=y & y<=750)
				{
					LED(1);

					LCD_Draw_Rectangle(90,600,390,750,RED);
					while(tp_dev.sta&(1<<0))
						tp_dev.scan(0);
					LCD_Draw_Rectangle(90,600,390,750,WHITE);
					back = 1;
					finish = 0;

					LED(0);
				}
				else
					;
			}
			else
				;
		}
	}
	back = 0;
	//���س�ʼ����
	cnt = 0;
	LCD_Clear(BLACK);
	//д�����
	POINT_COLOR = YELLOW;
	LCD_ShowString(100,100,200,24,24,"NUEDC F");

	//������У׼�����ܰ���
	LCD_Draw_Rectangle(90,200,390,300,WHITE);
	LCD_ShowString(200,250,200,24,24,"Adjust");

	//��������·��⡱����
	LCD_Draw_Rectangle(90,350,390,450,WHITE);
	LCD_ShowString(170,400,200,24,24,"Short Setting");

	//��������ʼ����������
	LCD_Draw_Rectangle(90,500,390,600,WHITE);
	LCD_ShowString(200,550,200,24,24,"Start");

	//��������ʼ����������
	LCD_Draw_Rectangle(90,650,390,750,WHITE);
	LCD_ShowString(200,700,200,24,24,"Game");
}

