#include "conio.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "CHUOT.h"
#define UP Skull.y+1==RAN[Length-2].y
#define DOWN Skull.y-1==RAN[Length-2].y
#define LEFT Skull.x+1==RAN[Length-2].x
#define RIGHT Skull.x-1==RAN[Length-2].x
typedef struct
{
	int x; int y;
} Point;
int HP, MP, SP, LEVEL, HP_PC, MP_PC, SP_PC, LEVEL_PC, Length, Length_PC, MUC_DO, so_block, so_dan, SCORE, SCORE_PC;
char* NAME;
Point RAN[1000], RAN_PC[1000], THUC_AN[10], HUONG[1000], DAN[1000], THUC_AN_TRUE, Skull, Skull_PC, BLOCK[1000];
unsigned long int time_100(void)
{
	static struct time ti;
	unsigned long int t;
	gettime(&ti);
	t = ((ti.ti_hour * 60 + ti.ti_min) * 60 + ti.ti_sec) * 100 + ti.ti_hund;
	return t;
}
void Ve1ChucNang(char* name, int x, int y, int nhap_nhay)
{
	textcolor(LIGHTRED + nhap_nhay);
	gotoxy(x, y);
	switch (strlen(name))
	{
	case 10: cprintf("%c %s %c\n", 3, name, 3);
		break;
	case 8:  cprintf("%c  %s  %c\n", 3, name, 3);
		break;
	case 6:  cprintf("%c   %s   %c\n", 3, name, 3);
		break;
	case 4:  cprintf("%c    %s    %c\n", 3, name, 3);

	}
}
void VeNhieuChucNang(int x, int y, int soluong, char(*name)[12])
{
	int i;
	for (i = 0; i < soluong; ++i)
		Ve1ChucNang(name[i], x, y + i * 2, 0);
}
void XoaChucNang(int x, int y)
{
	textbackground(BLACK);
	gotoxy(x, y); printf("              ");
}
void VeLOGO(void)
{
	gotoxy(51, 2); textcolor(LIGHTRED); cprintf("/");
	gotoxy(30, 3); cprintf("%c%c%c                %c%c%c", 192, 196, 217, 192, 196, 217);
	gotoxy(23, 4); cprintf("ÛßßßÛ ÛßßßÛ ÛÜ  Û  ÛßßßÛ ÛßßßÛ ÛÜ  Û");
	gotoxy(23, 5); cprintf("ÈÍÍÍ» ÌÍÍÍ¹ º Û º  ÌÍÍÜ¼ ÌÍÍÍ¹ º Û º");
	gotoxy(23, 6); cprintf("ÛÜÜÜÛ Û   Û Û  ßÛ  Û   Û Û   Û Û  ßÛ");
}
void HieuUngLOGO(void)
{
	int mau[] = { 2,9,14,5,3,4,1,12,10,15,6,13,7,11 };
	static int i;
	gotoxy(23, 5); textcolor(mau[i++]);
	cprintf("ÈÍÍÍ» ÌÍÍÍ¹ º Û º  ÌÍÍÜ¼ ÌÍÍÍ¹ º Û º");
}
void Ve2Cot(void)
{
	int i, cot[1][19];
	gotoxy(17, 14); textcolor(LIGHTRED); cprintf("%c", 219);
	gotoxy(17, 34); cprintf("%c", 219);
	gotoxy(64, 14); cprintf("%c", 219);
	gotoxy(64, 34); cprintf("%c", 219);
	gotoxy(17, 15); textcolor(LIGHTCYAN);
	for (i = 0; i < 19; ++i)
		cprintf("%c\n\b", 186);
	gettext(17, 15, 17, 33, cot); puttext(64, 15, 64, 33, cot);
	textcolor(LIGHTRED);
	gotoxy(18, 14); cprintf("%c", 223);
	gotoxy(63, 14); cprintf("%c", 223);
	gotoxy(18, 34); cprintf("%c", 220);
	gotoxy(63, 34); cprintf("%c", 220);
}
int ClickChucNang(int x, int soluong, int* Y, char(*name)[12])
{
	int i = soluong;
	NHAY_CHUOT(&chuot_trai, &chuot_phai, &xchuot, &ychuot);
	if (xchuot >= x && xchuot <= x + 13)
		for (i = 0; i < soluong; ++i)
			if (ychuot == Y[i]) break;
	if (i == soluong) return 0;
	textbackground(LIGHTGREEN);
	Ve1ChucNang(name[i], x, ychuot, 0);
	if (chuot_trai)
	{
		Ve1ChucNang(name[i], x, ychuot, 128);
		delay(50);
		return i + 1;
	}
	delay(10);
	textbackground(BLACK);
	Ve1ChucNang(name[i], x, ychuot, 0);
	return 0;
}
void HieuUngClickChucNang(int chuc_nang_ra, int chuc_nang_vao, int soluong, char(*name)[12])
{
	int so_lan = 0, T, HET, stop, xtrai, xphai, ytrai, yphai;
	if (chuc_nang_ra)
	{
		xtrai = 34; ytrai = 17; xphai = 34; yphai = 19; HET = 3;
	}
	else if (chuc_nang_vao)
	{
		xtrai = 63; ytrai = 17; xphai = 5; yphai = 19; HET = 34;

	}
	while (xtrai > HET)
	{
		if (!so_lan) /* CHUC NANG DI SANG TRAI */
		{
			stop = (soluong % 2 == 0) ? soluong / 2 : (soluong + 1) / 2;
			for (T = 0; stop--; T += 4)
			{
				XoaChucNang(xtrai, ytrai + T);
				if (xtrai != 4)
					Ve1ChucNang(name[T / 2], xtrai - 1, ytrai + T, 0);
			}
			++so_lan;
		}
		else if (so_lan == 1) /* CHUC NANG DI SANG PHAI */
		{
			stop = (soluong % 2 == 0) ? soluong / 2 : (soluong + 1) / 2 - 1;
			for (T = 0; stop--; T += 4)
			{
				XoaChucNang(xphai, yphai + T);
				if (xtrai != 4)
					Ve1ChucNang(name[T / 2 + 1], xphai + 1, yphai + T, 0);
			}
			++so_lan;
		}
		else
		{
			if (xtrai <= 17 || xphai <= 17)
				if (chuc_nang_ra)
					XoaDuThua(soluong, 0);
				else  XoaDuThua(soluong, 1);
			so_lan = 0; xtrai -= 1; xphai += 1;
			delay(7);
		}
	}
}
int XoaDuThua(int soluong, int vao)
{
	int T, xtrai = 5, xphai = 64, ytrai = 17, yphai = 19, so_lan = 0;
	char* xoa = "            ";
	if (vao)
	{
		xtrai = 64; xphai = 5;
	}
	textcolor(LIGHTCYAN);
	for (T = 0; so_lan < soluong; T += 4)
	{
		gotoxy(xtrai, ytrai + T);
		if (!vao)
			cprintf("%s%c", xoa, 186);
		else  cprintf("%c%s", 186, xoa);
		so_lan += 2;
		if (so_lan <= soluong)
		{
			gotoxy(xphai, yphai + T);
			if (!vao)
				cprintf("%c%s", 186, xoa);
			else   cprintf("%s%c", xoa, 186);
		}
	}
	return 0;
}
/*---------------------------------------------------------------------------------------------------*/
			  /* CAC HAM VE GIAO DIEN GAME CHINH */

void VE_GIAO_DIEN_GAME_CHINH(void)
{
	int TRAI = 9, PHAI = 69, TREN = 15, DUOI = 45, i;
	clrscr(); VeLOGO();  HieuUngLOGO(); AN_CHUOT();
	/* VE BAN DO */
	textcolor(LIGHTRED);
	for (i = TRAI + 1; i < PHAI; ++i)
	{
		gotoxy(i, TREN); cprintf("%c", 205);
		gotoxy(i, DUOI); cprintf("%c", 205);
	}
	for (i = TREN + 1; i < DUOI; ++i)
	{
		gotoxy(TRAI, i); cprintf("%c", 186);
		gotoxy(PHAI, i); cprintf("%c", 186);
	}
	gotoxy(TRAI, TREN); cprintf("%c", 219);
	gotoxy(PHAI, TREN); cprintf("%c", 219);
	gotoxy(TRAI, DUOI); cprintf("%c", 219);
	gotoxy(PHAI, DUOI); cprintf("%c", 219);

	/* VE THONG BAO NHAN ITEMS */
	textcolor(LIGHTBLUE);
	for (i = 2; i < 8; ++i)
	{
		gotoxy(i, 19); cprintf("%c", 205);
		gotoxy(i, 24); cprintf("%c", 205);
	}
	gotoxy(1, 19); cprintf("%c", 219);
	gotoxy(1, 24); cprintf("%c", 219);
	gotoxy(8, 19); cprintf("%c", 219);
	gotoxy(8, 24); cprintf("%c", 219);

	/* VE THONG TIN CON RAN */
		 /* ve RAN */
	textcolor(LIGHTGREEN);
	VE_TEN_LEVEL(LEVEL, 12, 12, NAME);
	VE_HP_MP_SP(1, HP, 21, 12);
	VE_HP_MP_SP(2, MP, 21, 13);
	VE_HP_MP_SP(3, SP, 21, 14);
	/* ve RAN_PC */
	textcolor(LIGHTMAGENTA);
	VE_TEN_LEVEL(LEVEL_PC, 45, 12, "OSAKA");
	VE_HP_MP_SP(1, HP_PC, 54, 12);
	VE_HP_MP_SP(2, MP_PC, 54, 13);
	VE_HP_MP_SP(3, SP_PC, 54, 14);
	/* VE SCORE */
	textcolor(LIGHTMAGENTA); gotoxy(6, 13); cprintf("%c%c%c", 205, 205, 205);
	gotoxy(5, 13); cprintf("%c\n\b%c", 219, 31);
	textcolor(LIGHTGREEN); gotoxy(70, 13); cprintf("%c%c%c", 205, 205, 205);
	gotoxy(73, 13); cprintf("%c\n\b%c", 219, 31);
	textcolor(YELLOW); gotoxy(4, 15); cprintf("%3d", SCORE);
	gotoxy(72, 15); cprintf("%3d", SCORE_PC);

	gotoxy(31, 49); textcolor(RED);
	cprintf("Nhan F1 de vao MENU");
}
int VE_TEN_LEVEL(int level, int x, int y, char* name)
{
	gotoxy(x, y); cprintf("%c%c%c", 1, 1, 1);
	gotoxy(x - 1, y + 1); cprintf("%s", name);
	gotoxy(x - 2, y + 2); cprintf("LEVEL %d", level);
	return 1;
}
int VE_HP_MP_SP(int ve, int var, int x, int y)
{
	int P, mau[3] = { 12,1,7 }, i, j;
	char* ten[3] = { "HP","MP","SP" };
	P = var; i = ve - 1;
	textcolor(LIGHTBLUE); gotoxy(x, y);
	cprintf("%s ", ten[i]);
	textcolor(WHITE);
	if (P < 7) cprintf("0  %c ", 29);
	else cprintf("%-3d%c ", P - 7, 29);
	textcolor(mau[i]);
	if (P < 7)
	{
		for (j = 0; j < P; ++j)
			cprintf("%c", 3);
		printf("       ");
	}
	else cprintf("%c%c%c%c%c%c%c", 3, 3, 3, 3, 3, 3, 3);
	return 1;
}
void Loading(void)
{

	int x = 38;
	clrscr(); VeLOGO(); HieuUngLOGO();
	textcolor(LIGHTGREEN);
	gotoxy(36, 22); cprintf("Loading....");
	textcolor(LIGHTRED);
	gotoxy(37, 26); cprintf("%c%c%c%c%c%c%c", 3, 3, 3, 3, 3, 3, 3);
	while (x < 44)
	{
		textcolor(12);
		gotoxy(x, 25); cprintf("%c\n\b ", 3);
		gotoxy(44, 22); printf("   ");
		delay(150);
		gotoxy(x, 24); cprintf("%c\n\b ", 3);
		textcolor(10); gotoxy(44, 22); cprintf(".");
		delay(150);
		textcolor(12); gotoxy(x, 24); cprintf(" \n\b%c", 3);
		textcolor(10); gotoxy(45, 22); cprintf(".");
		delay(150);
		textcolor(12); gotoxy(x, 25); cprintf(" \n\b%c", 3);
		textcolor(10); gotoxy(46, 22); cprintf(".");
		++x; delay(50);
	}
}

/*----------------------------------------------------------------------------------*/
				  /* CAC HAM XU LI RAN */

int bat_phim(void)
{
	/* -1: BAM PHIM MUI TEN
		1: ( PHIM F1 ) MENU
	   9: ( PHIM TAB ) TANG TOC
	   13: ( ENTER ) BAN DAN  */

	int ch1, ch2;
tt:
	if (!kbhit())
	{
		if (UP) --RAN[Length - 1].y;
		else if (DOWN) ++RAN[Length - 1].y;
		else if (LEFT) --RAN[Length - 1].x;
		else if (RIGHT) ++RAN[Length - 1].x;
		return -1;
	}
	ch1 = getch();
	if (ch1 == 0) ch2 = getch();
	if (ch1 == 0)
	{
		if (ch2 == 72)  /* LEN */
		{
			if (DOWN) ++RAN[Length - 1].y;
			else --RAN[Length - 1].y;
		}
		else if (ch2 == 80)  /* XUONG */
		{
			if (UP) --RAN[Length - 1].y;
			else ++RAN[Length - 1].y;
		}
		else if (ch2 == 75)  /* TRAI */
		{
			if (RIGHT) ++RAN[Length - 1].x;
			else --RAN[Length - 1].x;
		}
		else if (ch2 == 77)  /* PHAI */
		{
			if (LEFT) --RAN[Length - 1].x;
			else ++RAN[Length - 1].x;
		}
		else if (ch2 == 59)  /* PHIM F1 */
			return 1;
		else goto tt;
		return -1;
	}
	else if (ch1 == 13) return 13;
	else if (ch1 == 9) return 9;
	else goto tt;
}

/*----------------------------------------------------------------------------------------------------*/
			   /* CAC HAM XU LI RAN_PC */

void SMART_SNAKE_PC(int T)
{
	int duong_di, huong;
	if (RAN_PC[Length_PC - 1].x < THUC_AN[T].x)
	{
		duong_di = random(2);
		if (!duong_di)
			if (RAN_PC[Length_PC - 1].y != THUC_AN[T].y)
				Xet_ToaDo_y(T, &huong, 0);
			else goto tt;
		else
			tt:
		if (RAN_PC[Length_PC - 1].x + 1 == RAN_PC[Length_PC - 2].x &&
			RAN_PC[Length_PC - 1].y == RAN_PC[Length_PC - 2].y)
			Xet_ToaDo_y(T, &huong, 0);
		else
		{
			++RAN_PC[Length_PC - 1].x; huong = 4; PC_CAN_DUOI(&RAN_PC[Length_PC - 1], &huong);
		}

	}
	else if (RAN_PC[Length_PC - 1].x > THUC_AN[T].x)
	{
		duong_di = random(2);
		if (!duong_di)
			if (RAN_PC[Length_PC - 1].y != THUC_AN[T].y)
				Xet_ToaDo_y(T, &huong, 1);
			else goto tt1;
		else
			tt1:
		if (RAN_PC[Length_PC - 1].x - 1 == RAN_PC[Length_PC - 2].x &&
			RAN_PC[Length_PC - 1].y == RAN_PC[Length_PC - 2].y)
			Xet_ToaDo_y(T, &huong, 1);
		else
		{
			--RAN_PC[Length_PC - 1].x; huong = 3; PC_CAN_DUOI(&RAN_PC[Length_PC - 1], &huong);
		}
	}
	else Xet_ToaDo_y(T, &huong, -1);
}
int Xet_ToaDo_y(int T, int* huong, int chi_dan)
{
	if (RAN_PC[Length_PC - 1].y > THUC_AN[T].y)
		if (RAN_PC[Length_PC - 1].y - 1 == RAN_PC[Length_PC - 2].y &&
			RAN_PC[Length_PC - 1].x == RAN_PC[Length_PC - 2].x)
			if (chi_dan)  /* TRAI */
			{
				--RAN_PC[Length_PC - 1].x; *huong = 3; PC_CAN_DUOI(&RAN_PC[Length_PC - 1], &huong);
			}
			else
			{
				++RAN_PC[Length_PC - 1].x; *huong = 4; PC_CAN_DUOI(&RAN_PC[Length_PC - 1], &huong);
			}
		else
		{
			--RAN_PC[Length_PC - 1].y; *huong = 1; PC_CAN_DUOI(&RAN_PC[Length_PC - 1], &huong);
		}

	else if (RAN_PC[Length_PC - 1].y < THUC_AN[T].y)
		if (RAN_PC[Length_PC - 1].y + 1 == RAN_PC[Length_PC - 2].y &&
			RAN_PC[Length_PC - 1].x == RAN_PC[Length_PC - 2].x)
			if (chi_dan)  /* TRAI */
			{
				--RAN_PC[Length_PC - 1].x; *huong = 3; PC_CAN_DUOI(&RAN_PC[Length_PC - 1], &huong);
			}
			else
			{
				++RAN_PC[Length_PC - 1].x; *huong = 4; PC_CAN_DUOI(&RAN_PC[Length_PC - 1], &huong);
			}
		else
		{
			++RAN_PC[Length_PC - 1].y; *huong = 2; PC_CAN_DUOI(&RAN_PC[Length_PC - 1], &huong);
		}
	else
		if (random(2))  /* dung thi di len */
		{
			--RAN_PC[Length_PC - 1].y; *huong = 1; PC_CAN_DUOI(&RAN_PC[Length_PC - 1], &huong);
		}
		else
		{
			++RAN_PC[Length_PC - 1].y; *huong = 2; PC_CAN_DUOI(&RAN_PC[Length_PC - 1], &huong);
		}
	return 1;
}
int PC_CAN_DUOI(Point* ran, int* huong)
{
	Point kt;
	int d = 0, d1 = 0;
	if (KT_THUOC_RAN(ran, 0, 1) < -1)
		switch (*huong)
		{
		case 1:  /* LEN */
			kt.y = ran->y + 1;
		kt1:
			for (kt.x = ran->x + 1; kt.x < 69; ++kt.x)
				if (KT_THUOC_RAN(kt, 0, 1))
					break;
				else ++d;
			for (kt.x = ran->x - 1; kt.x > 9; --kt.x)
				if (KT_THUOC_RAN(kt, 0, 1))
					break;
				else ++d1;
			if (*huong == 2) goto huong2;
			if (d < 6 && d1 < 6) return 0;
			else if (d > d1)
			{
				++ran->x; ++ran->y; *huong = 4;
			}
			else
			{
				--ran->x; ++ran->y; *huong = 3;
			}
			break;
		case 2:  /* XUONG */
			kt.y = ran->y - 1;
			goto kt1;
		huong2:
			if (d < 6 && d1 < 6) return 0;
			else if (d > d1)
			{
				++ran->x; --ran->y; *huong = 4;
			}
			else
			{
				--ran->x; --ran->y; *huong = 3;
			}
			break;
		case 3:  /*  TRAI  */
			kt.x = ran->x + 1;
		kt2:
			for (kt.y = ran->y + 1; kt.y < 45; ++kt.y)
				if (KT_THUOC_RAN(kt, 0, 1))
					break;
				else ++d;
			for (kt.y = ran->y - 1; kt.y > 15; --kt.y)
				if (KT_THUOC_RAN(kt, 0, 1))
					break;
				else ++d1;
			if (*huong == 4) goto huong4;
			if (d < 6 && d1 < 6) return 0;
			else if (d > d1)
			{
				++ran->x; ++ran->y; *huong = 2;
			}
			else
			{
				++ran->x; --ran->y; *huong = 1;
			}
			break;
		case 4:  /* PHAI */
			kt.x = ran->x - 1;
			goto kt2;
		huong4:
			if (d < 6 && d1 < 6) return 0;
			else if (d > d1)
			{
				--ran->x; ++ran->y; *huong = 2;
			}
			else
			{
				--ran->x; --ran->y; *huong = 1;
			}
			break;
		}
	else return 0;
	return 1;
}

/*----------------------------------------------------------------------------------------------------*/
			   /* CAC HAM XU LI CHUNG */

void GAN_TOA_DO(int ran)
{
	int i;
	Point t;
	if (ran)
	{
		for (i = 0; i < Length - 2; ++i)
		{
			t = RAN[i]; RAN[i] = RAN[i + 1]; RAN[i + 1] = t;
		}
		RAN[Length - 2] = Skull;
	}
	else
	{
		for (i = 0; i < Length_PC - 2; ++i)
		{
			t = RAN_PC[i]; RAN_PC[i] = RAN_PC[i + 1]; RAN_PC[i + 1] = t;
		}
		RAN_PC[Length_PC - 2] = Skull_PC;
	}
}

void SNAKE_GO(Point* ran, Point skull, int mau_than, int mau_skull, int length)
{
	if (length == 1)
	{
		gotoxy(skull.x, skull.y); printf(" ");
	}
	else
	{
		gotoxy(ran[0].x, ran[0].y); printf(" ");
		gotoxy(skull.x, skull.y); textcolor(mau_than); cprintf("%c", 1);
	}
	gotoxy(ran[length - 1].x, ran[length - 1].y); textcolor(mau_skull); cprintf("%c", 2);
}
void TOADOBANDAU_VERAN(void)
{
	int x, x_pc, i;
	for (x = 10, x_pc = 68, i = 0; i < 7; ++x, ++i, --x_pc)
	{
		RAN[i].x = x; RAN[i].y = 16;
		RAN_PC[i].x = x_pc; RAN_PC[i].y = 44;
	}
	/* VE RAN*/
	textcolor(LIGHTGREEN); gotoxy(10, 16); cprintf("%c%c%c%c%c%c", 1, 1, 1, 1, 1, 1);
	textcolor(LIGHTMAGENTA); cprintf("%c", 2);
	/* VE RAN_PC */
	gotoxy(63, 44); cprintf("%c%c%c%c%c%c", 1, 1, 1, 1, 1, 1);
	gotoxy(62, 44); textcolor(LIGHTGREEN); cprintf("%c", 2);

}
int KT_THUOC_RAN(Point diem, int ran, int ran_pc)
{
	int i;
	if (ran)
		for (i = 0; i < Length; ++i)
			if (diem.x == RAN[i].x && diem.y == RAN[i].y)
				return i + 1;
	if (ran_pc)
		for (i = 0; i < Length_PC; ++i)
			if (diem.x == RAN_PC[i].x && diem.y == RAN_PC[i].y)
				return -(i + 1);
	return 0;
}
int RAN_AN_THUC_AN(Point* ran, Point skull, int* length, int mau_than, int mau_skull, int* score, int* thuc_an_pc)
{
	int an, i;
	for (an = 0; an < MUC_DO; ++an)
		if (ran[*length - 1].x == THUC_AN[an].x && ran[*length - 1].y == THUC_AN[an].y)
		{
			if (THUC_AN[an].x == THUC_AN_TRUE.x && THUC_AN[an].y == THUC_AN_TRUE.y)
			{
				if (mau_than == 10)
					if (THUC_AN[an].x == THUC_AN[*thuc_an_pc].x && THUC_AN[an].y == THUC_AN[*thuc_an_pc].y)
						*thuc_an_pc = -1;
				VE_TRUE();
				gotoxy((mau_than == 10) ? 4 : 72, 15);
				textcolor(YELLOW); cprintf("%3d", -- * score);
				for (i = 0; i < MUC_DO; ++i)
				{
					if (!(i == an))
					{
						gotoxy(THUC_AN[i].x, THUC_AN[i].y); printf(" ");
						THUC_AN[i].x = 0;
					}
				}
			}
			else
			{
				if (mau_than == 10)
					if (THUC_AN[an].x == THUC_AN[*thuc_an_pc].x && THUC_AN[an].y == THUC_AN[*thuc_an_pc].y)
						*thuc_an_pc = -1;
				VE_FALSE();
				VE_BLOCK();
			}
			textcolor(mau_than); gotoxy(skull.x, skull.y); cprintf("%c", 1);
			textcolor(mau_skull); gotoxy(THUC_AN[an].x, THUC_AN[an].y); cprintf("%c", 2);
			++* length; ran[*length - 2] = skull; ran[*length - 1] = THUC_AN[an];
			THUC_AN[an].x = 0;
			return 1;
		}

	return 0;
}
int KT_RAN_THUOC_MAP_BLOCK(Point* ran, Point skull, int length, int mau_than, int mau_skull)
{
	int i;
	if (!KT_THUOC_BLOCK(ran[length - 1]) &&
		!(ran[length - 1].x == 9 || ran[length - 1].x == 69 || ran[length - 1].y == 15 || ran[length - 1].y == 45)) return 0;
	ran[length - 1] = skull;
	(mau_than == 10) ? --HP : --HP_PC;
	VE_HP_MP_SP(1, (mau_than == 10) ? HP : HP_PC, (mau_than == 10) ? 21 : 54, 12);
	textcolor(LIGHTRED);
	for (i = 0; i < length; ++i)
	{
		gotoxy(ran[i].x, ran[i].y); cprintf("%c", 1); delay(30);
	}
	for (; i--; )
	{
		gotoxy(ran[i].x, ran[i].y);
		if (i == length - 1)
		{
			textcolor(mau_skull); cprintf("%c", 2); textcolor(mau_than);
		}
		else cprintf("%c", 1);
		delay(30);
	}
	return 1;
}
int RAN_CAN_DAU_DUOI(int snake)
{
	int i;
	if (RAN[Length - 1].x == RAN_PC[Length_PC - 1].x && RAN[Length - 1].y == RAN_PC[Length_PC - 1].y)
	{
		if (snake) RAN[Length - 1] = Skull;
		else RAN_PC[Length_PC - 1] = Skull_PC;
		DAO_NGUOC_DAU_DUOI(1, 1);
		textcolor(LIGHTGREEN); gotoxy(RAN[0].x, RAN[0].y); cprintf("%c", 1);
		gotoxy(RAN_PC[Length_PC - 1].x, RAN_PC[Length_PC - 1].y); cprintf("%c", 2);
		textcolor(LIGHTMAGENTA); gotoxy(RAN[Length - 1].x, RAN[Length - 1].y); cprintf("%c", 2);
		gotoxy(RAN_PC[0].x, RAN_PC[0].y); cprintf("%c", 1);
	}
	else if (RAN[Length - 1].x == RAN_PC[0].x && RAN[Length - 1].y == RAN_PC[0].y)
	{
		RAN[Length - 1] = Skull;
		DAO_NGUOC_DAU_DUOI(1, 0);
		textcolor(LIGHTGREEN); gotoxy(RAN[0].x, RAN[0].y); cprintf("%c", 1);
		textcolor(LIGHTMAGENTA); gotoxy(RAN[Length - 1].x, RAN[Length - 1].y);
		cprintf("%c", 2);
	}
	else if (RAN_PC[Length_PC - 1].x == RAN[0].x && RAN_PC[Length_PC - 1].y == RAN[0].y)
	{
		RAN_PC[Length_PC - 1] = Skull_PC;
		DAO_NGUOC_DAU_DUOI(0, 1);
		textcolor(LIGHTGREEN); gotoxy(RAN_PC[Length_PC - 1].x, RAN_PC[Length_PC - 1].y);
		cprintf("%c", 2); textcolor(LIGHTMAGENTA); gotoxy(RAN_PC[0].x, RAN_PC[0].y);
		cprintf("%c", 1);
	}
	else return 0;
	delay(100);
	return 1;

}
int DAO_NGUOC_DAU_DUOI(int ran, int ran_pc)
{
	int i, j;
	Point t;
	if (ran)
		for (i = 0, j = Length - 1; i < j; ++i, --j)
		{
			t = RAN[i]; RAN[i] = RAN[j]; RAN[j] = t;
		}
	if (ran_pc)
		for (i = 0, j = Length_PC - 1; i < j; ++i, --j)
		{
			t = RAN_PC[i]; RAN_PC[i] = RAN_PC[j]; RAN_PC[j] = t;
		}
	return 1;
}
void RAN_CAN_THAN(Point* ran, Point skull, int* length, int* score, int* HP, int snake, int snake_pc)
{
	int can_duoi;
	can_duoi = KT_THUOC_RAN(skull, snake, snake_pc);
	if (can_duoi && abs(can_duoi) != *length)
	{
		NGAN_DUOI(ran, length, abs(can_duoi));
		--* HP;
		VE_HP_MP_SP(1, *HP, (snake == 2) ? 21 : 54, 12);
		*score += abs(can_duoi / 2);
		gotoxy((snake == 2) ? 4 : 72, 15);
		textcolor(YELLOW); cprintf("%3d", *score);
	}
}
int NGAN_DUOI(Point* ran, int* length, int X)
{
	int i, j;
	for (i = 0; i < X; ++i)
	{
		gotoxy(ran[i].x, ran[i].y); printf(" ");
	}
	for (i = 0; i < X; ++i)
	{
		for (j = 0; j < *length; ++j)
			ran[j] = ran[j + 1];
		--* length;
	}
	return 1;
}


/*--------------------------------------------------------------------------------------------------------*/
			 /* CAC HAM TAO VA VE THUC AN */

void TAO_THUC_AN(void)
{
	int i;
	for (i = 0; i < MUC_DO; ++i)
	{
	tt:
		THUC_AN[i].x = random(59) + 10;
		THUC_AN[i].y = random(29) + 16;
		if (KT_THUC_AN(THUC_AN[i], i))
			goto tt;
	}
	THUC_AN_TRUE = THUC_AN[random(MUC_DO)];
}
int KT_THUC_AN(Point thuc_an, int thu_tu)
{
	int i;
	if (KT_THUOC_RAN(thuc_an, 1, 1)) return 1;
	if (KT_THUOC_BLOCK(thuc_an)) return 1;
	for (i = 0; i < thu_tu; ++i)
		if (thuc_an.x == THUC_AN[i].x && thuc_an.y == THUC_AN[i].y)
			return 1;
	return 0;
}
void VE_THUC_AN(void)
{
	int i;
	textcolor(LIGHTRED);
	for (i = 0; i < MUC_DO; ++i)
	{
		gotoxy(THUC_AN[i].x, THUC_AN[i].y);
		cprintf("%c", 3);
	}
}
int VE_TRUE(void)
{
	textcolor(LIGHTGREEN);
	gotoxy(72, 21); cprintf("ÛßÛßÛ");
	gotoxy(72, 22); cprintf("  º");
	gotoxy(72, 23); cprintf("  Û");

	gotoxy(72, 25); cprintf("ÛßßßÛ");
	gotoxy(72, 26); cprintf("ÌÍÍÜ¼");
	gotoxy(72, 27); cprintf("Û   Û");

	gotoxy(72, 29); cprintf("Û   Û");
	gotoxy(72, 30); cprintf("º   º");
	gotoxy(72, 31); cprintf("ÛÜÜÜÛ");

	gotoxy(72, 33); cprintf("Ûßßßß");
	gotoxy(72, 34); cprintf("ÌÍÍ¹");
	gotoxy(72, 35); cprintf("ÛÜÜÜÜ");
	return 0;
}
int VE_FALSE(void)
{
	textcolor(BROWN);
	gotoxy(72, 21); cprintf("Ûßßßß");
	gotoxy(72, 22); cprintf("ÌÍÍ¹");
	gotoxy(72, 23); cprintf("Û");

	gotoxy(72, 25); cprintf("ÛßßßÛ");
	gotoxy(72, 26); cprintf("ÌÍÍÍ¹");
	gotoxy(72, 27); cprintf("Û   Û");

	gotoxy(72, 29); cprintf("Û");
	gotoxy(72, 30); cprintf("º");
	gotoxy(72, 31); cprintf("ÛÜÜÜ");

	gotoxy(72, 33); cprintf("ÛßßßÛ");
	gotoxy(72, 34); cprintf("ÈÍÍÍ»");
	gotoxy(72, 35); cprintf("ÛÜÜÜÛ");

	gotoxy(72, 37); cprintf("Ûßßßß");
	gotoxy(72, 38); cprintf("ÌÍÍ¹");
	gotoxy(72, 39); cprintf("ÛÜÜÜÜ");
	return 0;
}


/*-------------------------------------------------------------------------------------------------------------*/
				   /* CAC HAM XU LI BLOCK */
int VE_BLOCK(void)
{
	int i;
tt:
	BLOCK[so_block].x = random(59) + 10;
	BLOCK[so_block].y = random(29) + 16;
	if (KT_THUOC_RAN(BLOCK[so_block], 1, 1)) goto tt;
	/* KT THUOC THUC AN */
	for (i = 0; i < MUC_DO; ++i)
		if (BLOCK[so_block].x == THUC_AN[i].x &&
			BLOCK[so_block].y == THUC_AN[i].y)
			goto tt;
	/* KT THUOC BLOCK KHAC */
	for (i = 0; i < so_block; ++i)
		if (BLOCK[so_block].x == BLOCK[i].x &&
			BLOCK[so_block].y == BLOCK[i].y)
			goto tt;
	textcolor(BROWN); gotoxy(BLOCK[so_block].x, BLOCK[so_block].y);
	cprintf("%c", 178);
	++so_block;
	return 0;
}
int KT_THUOC_BLOCK(Point diem)
{
	int i;
	for (i = 0; i < so_block; ++i)
		if (diem.x == BLOCK[i].x && diem.y == BLOCK[i].y)
			return i + 1;
	return 0;
}
int LOAI_BO_DAN_BLOCK(Point* dan_block, int vi_tri, int* soluong, int dan)
{
	int i;
	for (i = vi_tri; i < *soluong - 1; ++i)
	{
		dan_block[i] = dan_block[i + 1];
		if (dan) HUONG[i] = HUONG[i + 1];
	}
	dan_block[*soluong - 1].x = 0;
	dan_block[*soluong - 1].y = 0;
	if (dan)
	{
		HUONG[*soluong - 1].x = 0;
		HUONG[*soluong - 1].y = 0;
	}
	--* soluong;
	return 1;
}

/*-------------------------------------------------------------------------------------------------------------*/
					  /* CAC HAM XU LI DAN*/

void KT_DUONG_DI_DAN(int i)
{
	HUONG[i].y = 1;
	if (UP)
	{
		DAN[i].x = Skull.x; DAN[i].y = Skull.y - 2; HUONG[i].x = 1;
	}
	else if (DOWN)
	{
		DAN[i].x = Skull.x; DAN[i].y = Skull.y + 2; HUONG[i].x = 2;
	}
	else if (LEFT)
	{
		DAN[i].x = Skull.x - 2; DAN[i].y = Skull.y; HUONG[i].x = 3;
	}
	else if (RIGHT)
	{
		DAN[i].x = Skull.x + 2; DAN[i].y = Skull.y; HUONG[i].x = 4;
	}
	gotoxy(DAN[i].x, DAN[i].y); textcolor(WHITE); cprintf("%c", 15);
}
int RAN_PC_BAN_DAN(int huong)
{

	/* Ham kiem tra xem toa do RAN_PC co trung voi toa do BLOCK de ban DAN, muc dich la lay toa do DAN */

	int i, da;
	for (da = 0; da < so_block; ++da)
		if ((RAN_PC[Length_PC - 1].x == BLOCK[da].x && (huong == 1 || huong == 2))
			|| (RAN_PC[Length_PC - 1].y == BLOCK[da].y) && (huong == 3 || huong == 4))
			break;
	if (da == so_block) return 0;
	--MP_PC; VE_HP_MP_SP(2, MP_PC, 54, 13);
	HUONG[so_dan].x = huong; HUONG[so_dan].y = 0;
	switch (huong)
	{
	case 1: /* LEN */
		DAN[so_dan].x = RAN_PC[Length_PC - 1].x;
		DAN[so_dan].y = RAN_PC[Length_PC - 1].y - 2;
		break;
	case 2: /* XUONG */
		DAN[so_dan].x = RAN_PC[Length_PC - 1].x;
		DAN[so_dan].y = RAN_PC[Length_PC - 1].y + 2;
		break;
	case 3: /* TRAI */
		DAN[so_dan].x = RAN_PC[Length_PC - 1].x - 2;
		DAN[so_dan].y = RAN_PC[Length_PC - 1].y;
		break;
	case 4: /* PHAI */
		DAN[so_dan].x = RAN_PC[Length_PC - 1].x + 2;
		DAN[so_dan].y = RAN_PC[Length_PC - 1].y;
	}
	++so_dan;
	gotoxy(DAN[i].x, DAN[i].y); textcolor(WHITE); cprintf("%c", 15);
	return 1;
}
void XOA_VE_DAN(int i, int New)
{
	textcolor(WHITE);
	if (HUONG[i].x == 1)
	{
		gotoxy(DAN[i].x, DAN[i].y + 1); printf(" ");
		if (New)
		{
			gotoxy(DAN[i].x, DAN[i].y); cprintf("%c", 15);
		}
	}
	else if (HUONG[i].x == 2)
	{
		gotoxy(DAN[i].x, DAN[i].y - 1); printf(" ");
		if (New)
		{
			gotoxy(DAN[i].x, DAN[i].y); cprintf("%c", 15);
		}
	}
	else if (HUONG[i].x == 3)
	{
		gotoxy(DAN[i].x + 1, DAN[i].y); printf(" ");
		if (New)
		{
			gotoxy(DAN[i].x, DAN[i].y); cprintf("%c", 15);
		}
	}
	else if (HUONG[i].x == 4)
	{
		gotoxy(DAN[i].x, DAN[i].y - 1); printf(" ");
		if (New)
		{
			gotoxy(DAN[i].x, DAN[i].y); cprintf("%c", 15);
		}
	}

}
void HIEU_UNG_DAN(void)
{
	int i, j, new, da, ran;
	for (i = 0; i < so_dan; ++i)
	{
		/* KT BAN TRUNG RAN KHONG? */

		ran = KT_THUOC_RAN(DAN[i], 1, 1);
		if (ran > 0)
		{
			--HP; XOA_VE_DAN(i, 0);
			VE_HP_MP_SP(1, HP, 21, 12);
			LOAI_BO_DAN_BLOCK(DAN, i, &so_dan, 1);
			continue;
		}
		else if (ran < 0)
		{
			--HP_PC; XOA_VE_DAN(i, 0);
			VE_HP_MP_SP(1, HP_PC, 54, 12);
			LOAI_BO_DAN_BLOCK(DAN, i, &so_dan, 1);
			continue;
		}
		/* KT BAN TRUNG BLOCK */
		da = KT_THUOC_BLOCK(DAN[i]);
		if (da)
		{
			if (HUONG[i].y)
				THONG_BAO_PHA_DA(1);
			else THONG_BAO_PHA_DA(0);
			XOA_VE_DAN(i, 0);
			gotoxy(BLOCK[da - 1].x, BLOCK[da - 1].y);
			printf(" ");
			LOAI_BO_DAN_BLOCK(BLOCK, i, &so_block, 0);
			continue;
		}
		/* KT DAN TRUNG THUC_AN VA MAP */
		for (j = 0; j < MUC_DO; ++j)
			if (DAN[i].x == THUC_AN[j].x && DAN[i].y == THUC_AN[j].y)
			{
				XOA_VE_DAN(i, 0); LOAI_BO_DAN_BLOCK(DAN, i, &so_dan, 1); continue;
			}
		if ((DAN[i].x >= 10 && DAN[i].x <= 68) ||
			(DAN[i].y >= 16 && DAN[i].y <= 44))
			new = 1;
		else
		{
			new = 0; LOAI_BO_DAN_BLOCK(DAN, i, &so_dan, 1);
		}
		XOA_VE_DAN(i, new);

	}
}

/*-------------------------------------------------------------------------------------------------------------*/
				  /* CAC HAM THONG BAO */

int THONG_BAO_PHA_DA(int ran)
{
	int t, X;
	t = random(6) + 1; X = random(6) + 1;
	switch (t)
	{
	case 1: if (ran)
	{
		HP += X; VE_HP_MP_SP(1, HP, 21, 12);
	}
		  else
	{
		HP_PC += X; VE_HP_MP_SP(1, HP_PC, 54, 12);
	}
		  VIET_THONG_BAO(X, "HP", 1, ran); break;
	case 2: if (ran)
	{
		MP += X; VE_HP_MP_SP(2, MP, 21, 13);
	}
		  else
	{
		MP_PC += X; VE_HP_MP_SP(2, MP_PC, 54, 13);
	}
		  VIET_THONG_BAO(X, "MP", 1, ran); break;
	case 3: if (ran)
	{
		SP += X; VE_HP_MP_SP(3, SP, 21, 14);
	}
		  else
	{
		SP_PC += X; VE_HP_MP_SP(3, SP_PC, 54, 14);
	}
		  VIET_THONG_BAO(X, "SP", 1, ran); break;
	case 4: if (ran)
	{
		SCORE += X; gotoxy(4, 15); textcolor(YELLOW); cprintf("%3d", SCORE);
	}
		  else
	{
		SCORE_PC += X; gotoxy(72, 15); textcolor(YELLOW); cprintf("%3d", SCORE_PC);
	}
		  VIET_THONG_BAO(X, "SCORE", 1, ran); break;
	case 5: if (ran)
	{
		SCORE -= X; gotoxy(4, 15); textcolor(YELLOW); cprintf("%3d", SCORE);
	}
		  else
	{
		SCORE_PC -= X; gotoxy(72, 15); textcolor(YELLOW); cprintf("%3d", SCORE_PC);
	}
		  VIET_THONG_BAO(X, "SCORE", -1, ran); break;

	}
	return 1;
}
int VIET_THONG_BAO(int X, char* ten, int dau, int ran)
{
	if (ran) textcolor(GREEN); else textcolor(LIGHTMAGENTA);
	gotoxy(4, 21); cprintf("%c%d", (dau == 1) ? '+' : '-', X);
	switch (strlen(ten))
	{
	case 2: gotoxy(4, 22); cprintf(" %s ", ten); break;
	case 5: gotoxy(3, 22); cprintf("%s", ten); break;
	}
	return 1;
}

/*-------------------------------------------------------------------------------------------------------------*/
int Menu_Chinh()
{
	int i, Y[8], c;
	unsigned long int t_ht, t_bd;
	char name[8][12] = { "THACH  DAU","LUYEN  TAP","VAT PHAM","SHOP","CAI  DAT","HUONG  DAN","THONG  TIN","THOAT GAME" };
	char name1[8][12] = { "THACH  DAU","LUYEN  TAP","VAT PHAM" };
	_setcursortype(0);
	HP = 10; MP = 20; SP = 10; HP_PC = 7; MP_PC = 345; SP_PC = 99; LEVEL = 34; LEVEL_PC = 30;
	NAME = "LUCCC";
	VeNhieuChucNang(34, 17, 8, name);
	Ve2Cot();
	for (Y[0] = 17, i = 1; i < 8; ++i)
		Y[i] = Y[i - 1] + 2;
	t_bd = time_100();
	do
	{
		t_ht = time_100();
		if (t_ht - t_bd > 30)
		{
			t_bd = t_ht;
			HieuUngLOGO();
		}
		c = ClickChucNang(34, 8, Y, name);

	} while (!c);
	HieuUngClickChucNang(1, 0, 8, name); delay(30); HieuUngClickChucNang(0, 1, 3, name1); getch();
	switch (c)
	{
	case 1:printf("%s", name[c - 1]); Loading(); VE_GIAO_DIEN_GAME_CHINH(); return 1;
	case 2: printf("%s", name[c - 1]); break;
	case 3: printf("%s", name[c - 1]); break;
	case 4: printf("%s", name[c - 1]); break;
	case 5: printf("%s", name[c - 1]); break;
	case 6: printf("%s", name[c - 1]); break;
	case 7: printf("%s", name[c - 1]); break;
	case 8: printf("%s", name[c - 1]);
	}
	return 0;
}
void main()
{
	int TANG_TOC = 0, TANG_TOC_PC = 0, speed = 70, speed_PC = 70, thuc_an_PC = -1, snake_eat = 0, TRUE_FALSE, phim, i;
	unsigned long int t_ht, t_sp, t_sp_PC, t_bd, t_bd_PC, t_true_false, t_random_sp, t_DAN;
	Length = Length_PC = 7; MUC_DO = 3; SCORE = SCORE_PC = 7;
	clrscr();
	textmode(C4350);
	_setcursortype(0);
	TAO_CHUOT(); HIEN_CHUOT();
	VeLOGO();
	if (Menu_Chinh())
	{
		TOADOBANDAU_VERAN(); randomize();
		while (kbhit()) getch();
		t_bd = t_bd_PC = t_random_sp = t_DAN = time_100();
		do
		{
			for (i = 0; i < MUC_DO; ++i)
				if (THUC_AN[i].x)
					break;
			if (i == MUC_DO)
			{
				TAO_THUC_AN();
				VE_THUC_AN();
			}
			while (1)
			{
				Skull = RAN[Length - 1]; Skull_PC = RAN_PC[Length_PC - 1];
				if (thuc_an_PC < 0)
				{
				tt:
					thuc_an_PC = random(MUC_DO);
					if (!THUC_AN[thuc_an_PC].x)
						goto tt;
				}
				/* XU LI RAN */

				t_ht = time_100();
				if (TANG_TOC)
					if (t_ht - t_sp > 1000)
					{
						TANG_TOC = 0; speed = 100;
					}
				if (t_ht - t_bd > speed)
				{
					t_bd = t_ht;
					phim = bat_phim();
					if (phim == 1)
					{
						clrscr(); cprintf("F1"); break;
					}
					else if (phim == 13)
					{
						if (MP)
						{
							--MP; VE_HP_MP_SP(2, MP, 21, 13);
							++so_dan; KT_DUONG_DI_DAN(so_dan - 1);
							t_bd = 0; goto ran_pc;
						}
						t_bd = 0; goto ran_pc;
					}
					else if (phim == 9)
					{
						if (SP)
						{
							t_sp = time_100();
							TANG_TOC = 1;  --SP;
							VE_HP_MP_SP(3, SP, 21, 14);
							speed = 10;
							t_bd = 0; goto ran_pc;
						}
						t_bd = 0; goto ran_pc;
					}
					if (RAN_AN_THUC_AN(RAN, Skull, &Length, 10, 13, &SCORE, &thuc_an_PC))
					{
						snake_eat = 1;
						TRUE_FALSE = 1;
						t_true_false = time_100();
						goto ran_pc;
					}
					if (KT_RAN_THUOC_MAP_BLOCK(RAN, Skull, Length, 10, 13)) goto ran_pc;
					if (RAN_CAN_DAU_DUOI(1)) goto ran_pc;
					else RAN_CAN_THAN(RAN_PC, RAN[Length - 1], &Length_PC, &SCORE_PC, &HP_PC, 0, 1);
					RAN_CAN_THAN(RAN, RAN[Length - 1], &Length, &SCORE, &HP, 2, 0);
					SNAKE_GO(RAN, Skull, 10, 13, Length);
					GAN_TOA_DO(1);
				}

				/* XU LI RAN_PC */

			ran_pc:
				t_ht = time_100();
				if (TANG_TOC_PC)
					if (t_ht - t_sp_PC > 1000)
					{
						TANG_TOC_PC = 0; speed_PC = 70;
					}
				if (t_ht - t_bd_PC > speed_PC)
				{
					t_bd_PC = t_ht;
					if (thuc_an_PC == -1) goto eat;
					SMART_SNAKE_PC(thuc_an_PC);
					if (RAN_AN_THUC_AN(RAN_PC, Skull_PC, &Length_PC, 13, 10, &SCORE_PC, &thuc_an_PC))
					{
						snake_eat = 1;
						thuc_an_PC = -1;
						TRUE_FALSE = 1; t_true_false = time_100();
						goto eat;
					}
					if (KT_RAN_THUOC_MAP_BLOCK(RAN_PC, Skull_PC, Length_PC, 13, 10))
					{
						RAN_PC[Length_PC - 1] = Skull_PC;
						DAO_NGUOC_DAU_DUOI(0, 1);
						textcolor(LIGHTGREEN); gotoxy(RAN_PC[Length_PC - 1].x, RAN_PC[Length_PC - 1].y);
						cprintf("%c", 2); textcolor(LIGHTMAGENTA); gotoxy(RAN_PC[0].x, RAN_PC[0].y);
						cprintf("%c", 1);
						goto eat;
					}
					if (RAN_CAN_DAU_DUOI(0)) goto eat;
					else RAN_CAN_THAN(RAN, RAN_PC[Length_PC - 1], &Length, &SCORE, &HP, 2, 0);
					RAN_CAN_THAN(RAN_PC, RAN_PC[Length_PC - 1], &Length_PC, &SCORE_PC, &HP_PC, 0, 1);
					SNAKE_GO(RAN_PC, Skull_PC, 13, 10, Length_PC);
					/* Ngau nhien Tang toc cho Ran PC */
					if (t_ht - t_random_sp > 2000)
						if (SP_PC)
						{
							t_random_sp = t_ht;
							speed_PC = 10;
							t_sp_PC = time_100();
							TANG_TOC_PC = 1;
							--SP_PC; VE_HP_MP_SP(3, SP_PC, 54, 14);
						}

					GAN_TOA_DO(0);
				}
			eat:
				if (snake_eat) break;
				t_ht = time_100();
				if (t_ht - t_DAN > 5)
				{
					t_DAN = t_ht;
					HIEU_UNG_DAN();
				}
				if (TRUE_FALSE)
					if (t_ht - t_true_false > 70)
					{
						int i;
						TRUE_FALSE = 0;
						for (i = 21; i < 40; ++i)
						{
							gotoxy(72, i); printf("     ");
						}
					}
			}
			snake_eat = 0;
		} while (1);

	}
	getch();
}