#include "dos.h"
union REGS regs;
unsigned char chuot_trai, chuot_phai;
int xchuot, ychuot;
int CO_CHUOT, show_mouse;
void TAO_CHUOT(void)
{
	regs.x.ax = 0;
	int86(0x33, &regs, &regs);
	if (regs.x.ax != 0) CO_CHUOT = 1;
}
void HIEN_CHUOT(void)
{
	if (CO_CHUOT)
	{
		regs.x.ax = 1;
		int86(0x33, &regs, &regs);
		show_mouse = 1;
	}
}
void AN_CHUOT(void)
{
	if (CO_CHUOT && show_mouse)
	{
		regs.x.ax = 2;
		int86(0x33, &regs, &regs);
		show_mouse = 0;
	}
}
void NHAY_CHUOT(unsigned char* CHUOT_TRAI, unsigned char* CHUOT_PHAI, int* x_chuot, int* y_chuot)
{
	if (CO_CHUOT)
	{
		regs.x.ax = 3;
		int86(0x33, &regs, &regs);
		*CHUOT_TRAI = (regs.x.bx == 1) ? 1 : 0;
		*CHUOT_PHAI = (regs.x.bx == 2) ? 1 : 0;
		if (regs.x.bx == 3)
			*CHUOT_TRAI = *CHUOT_PHAI = 1;
		*x_chuot = (regs.x.cx) / 8 + 1;
		*y_chuot = (regs.x.dx) / 8 + 1;
	}
}
void Pham_vi_ngang(int x1, int x2)
{
	if (CO_CHUOT)
	{
		regs.x.ax = 7;
		regs.x.cx = x1;
		regs.x.dx = x2;
		int86(0x33, &regs, &regs);
	}
}
void Pham_vi_doc(int y1, int y2)
{
	if (CO_CHUOT)
	{
		regs.x.ax = 8;
		regs.x.cx = y1;
		regs.x.dx = y2;
		int86(0x33, &regs, &regs);
	}
}