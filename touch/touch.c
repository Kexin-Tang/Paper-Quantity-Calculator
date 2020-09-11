#include "touch.h"
#include "..\lcd\lcd.h"
#include "gt9147.h"

_m_tp_dev tp_dev =
{
	TP_Init,
	GT9147_Scan,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};

u8 TP_Init(void)  //≥ı ºªØ
{
	if(GT9147_Init()==0)
	{
		tp_dev.scan=GT9147_Scan;
	}
	tp_dev.touchtype|=0X80;
	tp_dev.touchtype|=lcddev.dir&0X01;
	return 0;
}
