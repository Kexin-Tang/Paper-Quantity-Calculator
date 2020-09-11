#ifndef __TOUCH_H__
#define __TOUCH_H__

#include <stdio.h>
//#include "platform.h"
#include "xil_printf.h"
#include"xparameters.h"

#define TP_PRES_DOWN 0x80
#define TP_CATH_PRES 0x40
#define CT_MAX_TOUCH  5

typedef struct
{
	u8 (*init)(void);
	u8 (*scan)(u8);

	u16 x[CT_MAX_TOUCH];
	u16 y[CT_MAX_TOUCH];

	u8  sta;
	float xfac;
	float yfac;
	short xoff;
	short yoff;
	u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;

//u8 TP_Scan(u8 tp);								//脡篓脙猫
u8 TP_Init(void);								//鲁玫脢录禄炉

#endif

