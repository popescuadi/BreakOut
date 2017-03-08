#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define gri 8
#define maro 6
#define orange 192
#define alb 15
#define negru 0
#define left 'a'
#define right 'd'
#define LEFT 'A'
#define RIGHT 'D'
#pragma comment (lib , "winmm.lib")
struct bila//declararea tipului de data bila (aceasta contine coordonatele acesteia , directia si sensul deplasarii bilei)
{
	int lin, col, dir, sens;
};
struct bonus//declararea tipului de data bonus
{
	int lin, col, efect, exists;
};
void changecolor(int culoare)//se modifica culoarea caracterelor output
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, culoare);
}
/////////////////////
void gotoxy(int x, int y)//deplasarea cursorului la coordonatele (x,y) din consola
{
	COORD coord;
	coord.X = y + 5;
	coord.Y = x + 6;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
////////////////////////////
void clearcursor()//cursorul este facut invizibil in consola
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	BOOL result;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	result = SetConsoleCursorInfo(h, &CURSOR);
}
////////////////////
void fill(int M[][75])//umplerea matricii suport si a spatiului de joc
{
	int i, j;
	changecolor(gri);
	gotoxy(0, 0);
	printf("%c", (char)201);
	M[0][0] = 1;
	for (i = 0; i <= 22; i++)
	{
		for (j = 0; j <= 71; j++)
		{
			M[i][j] = 0;
		}
	}
	for (j = 1; j <= 70; j++)
	{
		gotoxy(0, j);
		M[0][j] = 1;
		printf("%c", (char)205);
	}
	gotoxy(0, 71);
	printf("%c", (char)187);
	M[0][71] = 1;
	for (i = 1; i <= 22; i++)
	{
		M[i][0] = 1;
		gotoxy(i, 0);
		printf("%c", (char)186);
		M[i][71] = 1;
		gotoxy(i, 71);
		printf("%c", (char)186);
	}
}
void loadmap(int M[][75], char filename[])
{
	int i, j;
	FILE *p;
	p = fopen(filename, "r");
	for (i = 1; i <= 6; i++)
	{
		for (j = 1; j <= 70; j++)
		{
			fscanf(p, "%d", &M[i][j]);
			gotoxy(i, j);
			if (M[i][j] == 1)
			{
				changecolor(112);
				if (j % 7 == 0) { changecolor(alb); printf(" "); }
				else printf("_");
			}
			else if (M[i][j] == 2)
			{
				changecolor(orange);
				if (j % 7 == 0) { changecolor(alb); printf(" "); }
				else printf("_");
			}
			else if (M[i][j] == 3)
			{
				changecolor(96);
				if (j % 7 == 0) { changecolor(alb); printf(" "); }
				else printf("_");
			}
			else if (M[i][j] == 4)
			{
				changecolor(160);
				if (j % 7 == 0) { changecolor(alb); printf(" "); }
				else if ((j + 3) % 7 == 0) { changecolor(172); printf("%c", 3); }
				else printf("_");
			}
			else if (M[i][j] == 5)
			{
				changecolor(160);
				if (j % 7 == 0) { changecolor(alb); printf(" "); }
				else if ((j + 3) % 7 == 0) { changecolor(169); printf("%c", 29); }
				else printf("_");
			}
			else if (M[i][j] == 6)
			{
				changecolor(160);
				if (j % 7 == 0) { changecolor(alb); printf(" "); }
				else if ((j + 3) % 7 == 0) { changecolor(174); printf("%c", 30); }
				else printf("_");
			}
		}
	}
	fclose(p);
}
void load(char filename[])
{
	int i, j, d;
	FILE *p;
	p = fopen(filename, "r");
	for (i = 1; i <= 21; i++)
	{
		for (j = 1; j <= 70; j++)
		{
			fscanf(p, "%d", &d);
			gotoxy(i, j);
			if (d == 1)
			{
				changecolor(orange);
				printf(" ");
			}
			else if (d == 2)
			{
				changecolor(224);
				printf(" ");
			}
			else if (d == 3)
			{
				changecolor(144);
				printf(" ");
			}
			else if (d == 4)
			{
				changecolor(160);
				printf(" ");
			}
		}
	}
	fclose(p);
}
void clearintro()
{
	int i, j;
	changecolor(alb);
	for (i = 1; i <= 22; i++)
	{
		for (j = 1; j <= 70; j++)
		{
			gotoxy(i, j);
			printf(" ");
		}
	}
}
////////////////////////
void fillbara(int M[][75], int jbarl, int jbarr)//umblerea barii controlate de jucator(bara se afla pe linia 21)
{
	int i;
	changecolor(alb);
	for (i = jbarl; i <= jbarr; i++)
	{
		M[21][i] = -1;
		gotoxy(21, i);
		printf("O");
	}
}
////////////////////
void clearbara(int M[][75], int jbarl, int jbarr)//stergerea barii
{
	int i;
	changecolor(alb);
	for (i = jbarl; i <= jbarr; i++)
	{
		M[21][i] = 0;
		gotoxy(21, i);
		printf(" ");
	}
}
///
void fillbila(int M[][75], bila &c)//umblerea initiala a bilei si setarea caracteristicilor acesteia(pozitie,directie,sens)
{
	c.lin = 12;
	c.col = 29;
	c.sens = 1;
	c.dir = 1;
	gotoxy(c.lin, c.col);
	changecolor(15);
	printf("O");
}
///////////////
void slidebarright(int M[][75], int &jbarl, int &jbarr)//alunecarea barii la dreapta
{
	changecolor(15);
	if (M[21][jbarr + 1] != 1)
	{
		gotoxy(21, jbarr + 1);
		printf("O");
		M[21][jbarr + 1] = -1;
		gotoxy(21, jbarl);
		printf(" ");
		M[21][jbarl] = 0;
		jbarl++;
		jbarr++;
	}
}
void slidebarleft(int M[][75], int &jbarl, int &jbarr)//alunecarea barii la stanga 
{
	changecolor(15);
	if (M[21][jbarl - 1] != 1)
	{
		gotoxy(21, jbarl - 1);
		printf("O");
		M[21][jbarl - 1] = -1;
		gotoxy(21, jbarr);
		printf(" ");
		M[21][jbarr] = 0;
		jbarr--;
		jbarl--;
	}
}
///////////////////
void printpause()
{
	changecolor(11);
	//P
	gotoxy(10, 26); printf("%c", 220);
	gotoxy(11, 26); printf("%c", 222);
	gotoxy(12, 26); printf("%c", 222);
	gotoxy(13, 26); printf("%c", 222);
	gotoxy(14, 26); printf("%c", 222);
	gotoxy(10, 27); printf("%c", 220);
	gotoxy(12, 27); printf("%c", 223);
	gotoxy(10, 28); printf("%c", 220);
	gotoxy(11, 28); printf("%c", 219);
	//A
	gotoxy(11, 30); printf("%c", 222);
	gotoxy(12, 30); printf("%c", 222);
	gotoxy(13, 30); printf("%c", 222);
	gotoxy(14, 30); printf("%c", 222);
	gotoxy(10, 31); printf("%c", 220);
	gotoxy(12, 31); printf("%c", 219);
	gotoxy(11, 32); printf("%c", 221);
	gotoxy(12, 32); printf("%c", 221);
	gotoxy(13, 32); printf("%c", 221);
	gotoxy(14, 32); printf("%c", 221);
	//U
	gotoxy(10, 34); printf("%c", 220);
	gotoxy(11, 34); printf("%c", 221);
	gotoxy(12, 34); printf("%c", 221);
	gotoxy(13, 34); printf("%c", 221);
	gotoxy(14, 34); printf("%c", 222);
	gotoxy(14, 35); printf("%c", 219);
	gotoxy(10, 36); printf("%c", 220);
	gotoxy(11, 36); printf("%c", 222);
	gotoxy(12, 36); printf("%c", 222);
	gotoxy(13, 36); printf("%c", 222);
	gotoxy(14, 36); printf("%c", 221);
	//S
	gotoxy(10, 38); printf("%c", 220);
	gotoxy(11, 38); printf("%c", 219);
	gotoxy(14, 38); printf("%c", 220);
	gotoxy(10, 39); printf("%c", 220);
	gotoxy(12, 39); printf("%c", 219);
	gotoxy(14, 39); printf("%c", 220);
	gotoxy(10, 40); printf("%c", 220);
	gotoxy(13, 40); printf("%c", 221);
	gotoxy(14, 40); printf("%c", 219);
	//E
	gotoxy(10, 42); printf("%c", 220);
	gotoxy(11, 42); printf("%c", 221);
	gotoxy(12, 42); printf("%c", 219);
	gotoxy(13, 42); printf("%c", 221);
	gotoxy(14, 42); printf("%c", 219);
	gotoxy(10, 43); printf("%c", 220);
	gotoxy(12, 43); printf("%c", 220);
	gotoxy(14, 43); printf("%c", 220);
	gotoxy(10, 44); printf("%c", 220);
	gotoxy(14, 44); printf("%c", 220);
}
void clearpause()
{
	changecolor(11);
	//P
	gotoxy(10, 26); printf(" ");
	gotoxy(11, 26); printf(" ");
	gotoxy(12, 26); printf(" ");
	gotoxy(13, 26); printf(" ");
	gotoxy(14, 26); printf(" ");
	gotoxy(10, 27); printf(" ");
	gotoxy(12, 27); printf(" ");
	gotoxy(10, 28); printf(" ");
	gotoxy(11, 28); printf(" ");
	//A
	gotoxy(11, 30); printf(" ");
	gotoxy(12, 30); printf(" ");
	gotoxy(13, 30); printf(" ");
	gotoxy(14, 30); printf(" ");
	gotoxy(10, 31); printf(" ");
	gotoxy(12, 31); printf(" ");
	gotoxy(11, 32); printf(" ");
	gotoxy(12, 32); printf(" ");
	gotoxy(13, 32); printf(" ");
	gotoxy(14, 32); printf(" ");
	//U
	gotoxy(10, 34); printf(" ");
	gotoxy(11, 34); printf(" ");
	gotoxy(12, 34); printf(" ");
	gotoxy(13, 34); printf(" ");
	gotoxy(14, 34); printf(" ");
	gotoxy(14, 35); printf(" ");
	gotoxy(10, 36); printf(" ");
	gotoxy(11, 36); printf(" ");
	gotoxy(12, 36); printf(" ");
	gotoxy(13, 36); printf(" ");
	gotoxy(14, 36); printf(" ");
	//S
	gotoxy(10, 38); printf(" ");
	gotoxy(11, 38); printf(" ");
	gotoxy(14, 38); printf(" ");
	gotoxy(10, 39); printf(" ");
	gotoxy(12, 39); printf(" ");
	gotoxy(14, 39); printf(" ");
	gotoxy(10, 40); printf(" ");
	gotoxy(13, 40); printf(" ");
	gotoxy(14, 40); printf(" ");
	//E
	gotoxy(10, 42); printf(" ");
	gotoxy(11, 42); printf(" ");
	gotoxy(12, 42); printf(" ");
	gotoxy(13, 42); printf(" ");
	gotoxy(14, 42); printf(" ");
	gotoxy(10, 43); printf(" ");
	gotoxy(12, 43); printf(" ");
	gotoxy(14, 43); printf(" ");
	gotoxy(10, 44); printf(" ");
	gotoxy(14, 44); printf(" ");
}
///////////////////////
void printbonus(bonus &c)//umblerea initiala a bilei si setarea caracteristicilor acesteia(pozitie,directie,sens)
{
	gotoxy(c.lin, c.col);
	switch (c.efect)
	{
	case 1:{changecolor(12); printf("%c", 3); break; }//extralife
	case 2:{changecolor(1); printf("%c", 29); break; }//expand
	case 3:{changecolor(14); printf("%c", 30); break; }//laser
	default:break;
	}
}
///////////////////////
void destroy(int M[][75], int x, int y, int cul, int &score, bonus &c1, bonus &c2, bonus &c3, bonus &c4)
{
	int i, nr;
	if (cul == 2)//caramizi portocalii
	{
		changecolor(alb);
		nr = y;
		while (nr % 7 != 0) nr++;
		M[x][nr] = 0;
		for (i = nr - 1; i >= nr - 6; i--)
		{
			gotoxy(x, i);
			printf(" ");
			M[x][i] = 0;
		}
		score++;
	}
	else if (cul == 3)//caramizi maro
	{
		changecolor(orange);
		nr = y;
		while (nr % 7 != 0) nr++;
		M[x][nr] = 2;
		for (i = nr - 6; i <= nr - 1; i++)
		{
			gotoxy(x, i);
			printf("_");
			M[x][i] = 2;
		}
		score++;
	}
	else if (cul == 4)//extra life
	{
		changecolor(alb);
		nr = y;
		while (nr % 7 != 0) nr++;
		M[x][nr] = 0;
		for (i = nr - 6; i <= nr - 1; i++)
		{
			gotoxy(x, i);
			printf(" ");
			M[x][i] = 0;
		}
		score++;
		c1.col = nr - 3;
		c1.lin = x;
		c1.exists = 1;
		c1.efect = 1;
		printbonus(c1);
	}
	else if (cul == 5)//enlarge bar
	{
		changecolor(alb);
		nr = y;
		while (nr % 7 != 0) nr++;
		M[x][nr] = 0;
		for (i = nr - 6; i <= nr - 1; i++)
		{
			gotoxy(x, i);
			printf(" ");
			M[x][i] = 0;
		}
		score++;
		c2.col = nr - 3;
		c2.lin = x;
		c2.exists = 1;
		c2.efect = 2;
		printbonus(c2);
	}
	else if (cul == 6)//laser
	{
		changecolor(alb);
		nr = y;
		while (nr % 7 != 0) nr++;
		M[x][nr] = 0;
		for (i = nr - 6; i <= nr - 1; i++)
		{
			gotoxy(x, i);
			printf(" ");
			M[x][i] = 0;
		}
		score++;
		c3.col = nr - 3;
		c3.lin = x;
		c3.exists = 1;
		c3.efect = 3;
		printbonus(c3);
	}
}
//////
void coldet11(int M[][75], bila &B)
{
	if (M[B.lin + 1][B.col] == -1)
	{
		B.sens = rand() % 2 + 1;
		B.dir = rand() % 3 + 2;
	}
}
void coldet1(int M[][75], bila &B, int &score, bonus &c1, bonus &c2, bonus &c3, bonus &c4)
{
	if (M[B.lin][B.col + 1] != 0 && M[B.lin - 1][B.col] != 0)
	{
		B.sens = 3;
		destroy(M, B.lin, B.col + 1, M[B.lin][B.col + 1], score, c1, c2, c3, c4);
		destroy(M, B.lin - 1, B.col, M[B.lin - 1][B.col], score, c1, c2, c3, c4);
	}
	else if (M[B.lin][B.col + 1] == 0 && M[B.lin - 1][B.col] == 0 && M[B.lin - 1][B.col + 1] != 0)
	{
		B.sens = 3;
		destroy(M, B.lin - 1, B.col + 1, M[B.lin - 1][B.col + 1], score, c1, c2, c3, c4);
	}
	else if (M[B.lin][B.col + 1] != 0 && M[B.lin - 1][B.col] == 0)
	{
		B.sens = 2;
		destroy(M, B.lin, B.col + 1, M[B.lin][B.col + 1], score, c1, c2, c3, c4);
	}
	else if (M[B.lin][B.col + 1] == 0 && M[B.lin - 1][B.col] != 0)
	{
		B.sens = 4;
		destroy(M, B.lin - 1, B.col, M[B.lin - 1][B.col], score, c1, c2, c3, c4);
	}
}
void coldet2(int M[][75], bila &B, int &score, bonus &c1, bonus &c2, bonus &c3, bonus &c4)
{
	if (M[B.lin][B.col - 1] != 0 && M[B.lin - 1][B.col] != 0)
	{
		B.sens = 4;
		destroy(M, B.lin, B.col - 1, M[B.lin][B.col - 1], score, c1, c2, c3, c4);
		destroy(M, B.lin - 1, B.col, M[B.lin - 1][B.col], score, c1, c2, c3, c4);
	}
	else if (M[B.lin][B.col - 1] == 0 && M[B.lin - 1][B.col] == 0 && M[B.lin - 1][B.col - 1] != 0)
	{
		B.sens = 4;
		destroy(M, B.lin - 1, B.col - 1, M[B.lin - 1][B.col - 1], score, c1, c2, c3, c4);
	}
	else if (M[B.lin][B.col - 1] != 0 && M[B.lin - 1][B.col] == 0)
	{
		B.sens = 1;
		destroy(M, B.lin, B.col - 1, M[B.lin][B.col - 1], score, c1, c2, c3, c4);
	}
	else if (M[B.lin][B.col - 1] == 0 && M[B.lin - 1][B.col] != 0)
	{
		B.sens = 3;
		destroy(M, B.lin - 1, B.col, M[B.lin - 1][B.col], score, c1, c2, c3, c4);
	}
}
void coldet3(int M[][75], bila &B, char c, int &score, bonus &d1, bonus &d2, bonus &d3, bonus &d4)
{
	if (M[B.lin][B.col - 1] != 0 && M[B.lin + 1][B.col] != 0 && M[B.lin + 1][B.col] != -1)
	{
		B.sens = 1;
		destroy(M, B.lin, B.col - 1, M[B.lin][B.col - 1], score, d1, d2, d3, d4);
		destroy(M, B.lin + 1, B.col, M[B.lin + 1][B.col], score, d1, d2, d3, d4);
	}
	else if (M[B.lin][B.col - 1] == 0 && M[B.lin + 1][B.col] == 0 && M[B.lin + 1][B.col - 1] != 0 && M[B.lin + 1][B.col - 1] != -1)
	{
		B.sens = 1;
		destroy(M, B.lin + 1, B.col - 1, M[B.lin + 1][B.col - 1], score, d1, d2, d3, d4);
	}
	else if (M[B.lin][B.col - 1] != 0 && M[B.lin + 1][B.col] == 0)
	{
		B.sens = 4;
		destroy(M, B.lin, B.col - 1, M[B.lin][B.col - 1], score, d1, d2, d3, d4);
	}
	else if (M[B.lin][B.col - 1] == 0 && M[B.lin + 1][B.col] != 0 && M[B.lin + 1][B.col] != -1)
	{
		B.sens = 2;
		destroy(M, B.lin + 1, B.col, M[B.lin + 1][B.col], score, d1, d2, d3, d4);
	}
	else if (M[B.lin][B.col - 1] != 0 && M[B.lin + 1][B.col] == -1)
	{
		B.sens = 1;
	}
	else if (M[B.lin][B.col - 1] == 0 && M[B.lin + 1][B.col] == 0 && M[B.lin + 1][B.col - 1] == -1)
	{
		if (c == 'D' || c == 'd')
		{
			B.sens = 1;
			B.dir = rand() % 3 + 2;
		}
		else if (c == 'A' || c == 'a')
		{
			B.sens = 2;
			B.dir = rand() % 3 + 2;
		}
	}
	else if (M[B.lin][B.col - 1] == 0 && M[B.lin + 1][B.col] == -1)
	{
		if (c == 'D' || c == 'd')
		{
			B.sens = 1;
			B.dir = rand() % 3 + 2;
		}
		else if (c == 'A' || c == 'a')
		{
			B.sens = 2;
			B.dir = rand() % 3 + 2;
		}
	}
}
void coldet4(int M[][75], bila &B, char c, int &score, bonus &d1, bonus &d2, bonus &d3, bonus &d4)
{
	if (M[B.lin][B.col + 1] != 0 && M[B.lin + 1][B.col] != 0 && M[B.lin + 1][B.col] != -1)
	{
		B.sens = 2;
		destroy(M, B.lin, B.col + 1, M[B.lin][B.col + 1], score, d1, d4, d3, d4);
		destroy(M, B.lin + 1, B.col, M[B.lin + 1][B.col], score, d1, d4, d3, d4);
	}
	else if (M[B.lin][B.col + 1] == 0 && M[B.lin + 1][B.col] == 0 && M[B.lin + 1][B.col + 1] != 0 && M[B.lin + 1][B.col + 1] != -1)
	{
		B.sens = 2;
		destroy(M, B.lin + 1, B.col + 1, M[B.lin + 1][B.col + 1], score, d1, d4, d3, d4);
	}
	else if (M[B.lin][B.col + 1] != 0 && M[B.lin + 1][B.col] == 0)
	{
		B.sens = 3;
		destroy(M, B.lin, B.col + 1, M[B.lin][B.col + 1], score, d1, d4, d3, d4);
	}
	else if (M[B.lin][B.col + 1] == 0 && M[B.lin + 1][B.col] != 0 && M[B.lin + 1][B.col] != -1)
	{
		B.sens = 1;
		destroy(M, B.lin + 1, B.col, M[B.lin + 1][B.col], score, d1, d4, d3, d4);
	}
	else if (M[B.lin][B.col + 1] != 0 && M[B.lin + 1][B.col] == -1)
	{
		B.sens = 2;
	}
	else if (M[B.lin][B.col + 1] == 0 && M[B.lin + 1][B.col] == 0 && M[B.lin + 1][B.col + 1] == -1)
	{
		if (c == 'D' || c == 'd')
		{
			B.sens = 1;
			B.dir = rand() % 3 + 2;
		}
		else if (c == 'A' || c == 'a')
		{
			B.sens = 2;
			B.dir = rand() % 3 + 2;
		}
	}
	else if (M[B.lin][B.col + 1] == 0 && M[B.lin + 1][B.col] == -1)
	{
		if (c == 'D' || c == 'd')
		{
			B.sens = 1;
			B.dir = rand() % 3 + 2;
		}
		else if (c == 'A' || c == 'a')
		{
			B.sens = 2;
			B.dir = rand() % 3 + 2;
		}
	}
}
void coldetlaser(int M[][75], bila &B, int &score, bonus &c1, bonus &c2, bonus &c3, bonus &c4, int &lasermove)
{
	if (M[B.lin - 1][B.col] != 0)
	{
		destroy(M, B.lin - 1, B.col, M[B.lin - 1][B.col], score, c1, c2, c3, c4);
		lasermove = 0;
		changecolor(alb);
		gotoxy(B.lin, B.col);
		printf(" ");
	}
}
///////////////////////
void move(int M[][75], bila &B, char c, int &score, bonus &d1, bonus &d2, bonus &d3, bonus &d4, int &lasermove)//miscarea bilei(starea permanenta a bilei este de miscare pe directia si sensul precizate in structura pana aceasta intalneste un obstacol si statusul ei se modifica)
{
	int sens;
	changecolor(15);
	if (B.dir == 1)
	{
		switch (B.sens)
		{
		case 1:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  gotoxy(B.lin + 1, B.col);
				  printf("O");
				  B.lin++;
				  coldet11(M, B);
				  break;
		}
			//laser shots
		case 2:
		{
				  changecolor(14);
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.lin--;
				  gotoxy(B.lin, B.col);
				  printf("|");
				  coldetlaser(M, B, score, d1, d2, d3, d4, lasermove);
				  break;
		}
		default:{break; }
		}
	}
	else if (B.dir == 2)
	{
		switch (B.sens)
		{
		case 1:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.lin--;
				  B.col++;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet1(M, B, score, d1, d2, d3, d4);
				  break;
		}
		case 2:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.lin--;
				  B.col--;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet2(M, B, score, d1, d2, d3, d4);
				  break;
		}
		case 3:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.lin++;
				  B.col--;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet3(M, B, c, score, d1, d2, d3, d4);
				  break;
		}
		case 4:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.lin++;
				  B.col++;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet4(M, B, c, score, d1, d2, d3, d4);
				  break;
		}
		default:{break; }
		}
	}
	else if (B.dir == 3)
	{
		sens = B.sens;
		switch (B.sens)
		{
		case 1:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.col++;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet1(M, B, score, d1, d2, d3, d4);

				  if (B.sens == sens)
				  {
					  gotoxy(B.lin, B.col);
					  printf(" ");
					  B.lin--;
					  B.col++;
					  gotoxy(B.lin, B.col);
					  printf("O");
					  coldet1(M, B, score, d1, d2, d3, d4);
				  }
				  break;
		}
		case 2:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.lin--;
				  B.col--;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet2(M, B, score, d1, d2, d3, d4);

				  if (B.sens == sens)
				  {
					  gotoxy(B.lin, B.col);
					  printf(" ");
					  B.col--;
					  gotoxy(B.lin, B.col);
					  printf("O");
					  coldet2(M, B, score, d1, d2, d3, d4);
				  }
				  break;
		}
		case 3:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.lin++;
				  B.col--;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet3(M, B, c, score, d1, d2, d3, d4);

				  if (B.sens == sens)
				  {
					  gotoxy(B.lin, B.col);
					  printf(" ");
					  B.col--;
					  gotoxy(B.lin, B.col);
					  printf("O");
					  coldet3(M, B, c, score, d1, d2, d3, d4);
				  }
				  break;
		}
		case 4:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.col++;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet4(M, B, c, score, d1, d2, d3, d4);

				  if (B.sens == sens)
				  {
					  gotoxy(B.lin, B.col);
					  printf(" ");
					  B.lin++;
					  B.col++;
					  gotoxy(B.lin, B.col);
					  printf("O");
					  coldet4(M, B, c, score, d1, d2, d3, d4);
				  }
				  break;
		}
		default:{break; }
		}
	}
	else if (B.dir == 4)
	{
		sens = B.sens;
		switch (B.sens)
		{
		case 1:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.lin--;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet1(M, B, score, d1, d2, d3, d4);

				  if (B.sens == sens)
				  {
					  gotoxy(B.lin, B.col);
					  printf(" ");
					  B.lin--;
					  B.col++;
					  gotoxy(B.lin, B.col);
					  printf("O");
					  coldet1(M, B, score, d1, d2, d3, d4);
				  }
				  break;
		}
		case 2:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.lin--;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet2(M, B, score, d1, d2, d3, d4);

				  if (B.sens == sens)
				  {
					  gotoxy(B.lin, B.col);
					  printf(" ");
					  B.lin--;
					  B.col--;
					  gotoxy(B.lin, B.col);
					  printf("O");
					  coldet2(M, B, score, d1, d2, d3, d4);
				  }
				  break;
		}
		case 3:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.lin++;
				  B.col--;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet3(M, B, c, score, d1, d2, d3, d4);

				  if (B.sens == sens)
				  {
					  gotoxy(B.lin, B.col);
					  printf(" ");
					  B.lin++;
					  gotoxy(B.lin, B.col);
					  printf("O");
					  coldet3(M, B, c, score, d1, d2, d3, d4);
				  }
				  break;
		}
		case 4:
		{
				  gotoxy(B.lin, B.col);
				  printf(" ");
				  B.lin++;
				  B.col++;
				  gotoxy(B.lin, B.col);
				  printf("O");
				  coldet4(M, B, c, score, d1, d2, d3, d4);

				  if (B.sens == sens)
				  {
					  gotoxy(B.lin, B.col);
					  printf(" ");
					  B.lin++;
					  gotoxy(B.lin, B.col);
					  printf("O");
					  coldet4(M, B, c, score, d1, d2, d3, d4);
				  }
				  break;
		}
		default:{break; }
		}
	}
}
///////////////////////
void printlifes(int i)
{
	changecolor(4);
	gotoxy(-1, 1);
	printf("%c", 3);
	changecolor(alb);
	gotoxy(-1, 2);
	printf("%d", i);
}
void updatelifes(int i)
{
	changecolor(alb);
	gotoxy(-1, 2);
	printf("%d", i);
}
////////////////////////
void printscore(int i)
{
	changecolor(9);
	gotoxy(-1, 4);
	printf("Score");
	changecolor(alb);
	gotoxy(-1, 9);
	printf(":%d", i);
}
void updatescore(int i)
{
	changecolor(alb);
	gotoxy(-1, 9);
	printf(":%d", i);
}
//////////////
void printlevel(int level)
{
	changecolor(5);
	gotoxy(-1, 60);
	printf("Level");
	changecolor(alb);
	gotoxy(-1, 66);
	printf(":%d", level);
}
void updatelevel(int level)
{
	changecolor(alb);
	gotoxy(-1, 66);
	printf(":%d", level);
}
//////
void moveb1(int M[][75], bonus &c1)
{
	if (M[c1.lin + 1][c1.col] == 1)
	{
		changecolor(124);
		gotoxy(c1.lin + 1, c1.col);
		printf("%c", 3);
	}
	else if (M[c1.lin + 1][c1.col] == 2)
	{
		changecolor(204);
		gotoxy(c1.lin + 1, c1.col);
		printf("%c", 3);
	}
	else if (M[c1.lin + 1][c1.col] == 3)
	{
		changecolor(108);
		gotoxy(c1.lin + 1, c1.col);
		printf("%c", 3);
	}
	else
	{
		changecolor(12);
		gotoxy(c1.lin + 1, c1.col);
		printf("%c", 3);
	}

	if (M[c1.lin][c1.col] == 1)
	{
		changecolor(112);
		gotoxy(c1.lin, c1.col);
		printf("_");
	}
	else if (M[c1.lin][c1.col] == 2)
	{
		changecolor(192);
		gotoxy(c1.lin, c1.col);
		printf("_");
	}
	else if (M[c1.lin][c1.col] == 3)
	{
		changecolor(96);
		gotoxy(c1.lin, c1.col);
		printf(" ");
	}
	else
	{
		changecolor(alb);
		gotoxy(c1.lin, c1.col);
		printf(" ");
	}
	c1.lin++;
}
void moveb2(int M[][75], bonus &c2)
{
	if (M[c2.lin + 1][c2.col] == 1)
	{
		changecolor(121);
		gotoxy(c2.lin + 1, c2.col);
		printf("%c", 29);
	}
	else if (M[c2.lin + 1][c2.col] == 2)
	{
		changecolor(201);
		gotoxy(c2.lin + 1, c2.col);
		printf("%c", 29);
	}
	else if (M[c2.lin + 1][c2.col] == 3)
	{
		changecolor(105);
		gotoxy(c2.lin + 1, c2.col);
		printf("%c", 29);
	}
	else
	{
		changecolor(9);
		gotoxy(c2.lin + 1, c2.col);
		printf("%c", 29);
	}

	if (M[c2.lin][c2.col] == 1)
	{
		changecolor(112);
		gotoxy(c2.lin, c2.col);
		printf("_");
	}
	else if (M[c2.lin][c2.col] == 2)
	{
		changecolor(192);
		gotoxy(c2.lin, c2.col);
		printf("_");
	}
	else if (M[c2.lin][c2.col] == 3)
	{
		changecolor(96);
		gotoxy(c2.lin, c2.col);
		printf(" ");
	}
	else
	{
		changecolor(alb);
		gotoxy(c2.lin, c2.col);
		printf(" ");
	}
	c2.lin++;
}
void moveb3(int M[][75], bonus &c3)
{
	if (M[c3.lin + 1][c3.col] == 1)
	{
		changecolor(126);
		gotoxy(c3.lin + 1, c3.col);
		printf("%c", 30);
	}
	else if (M[c3.lin + 1][c3.col] == 2)
	{
		changecolor(206);
		gotoxy(c3.lin + 1, c3.col);
		printf("%c", 30);
	}
	else if (M[c3.lin + 1][c3.col] == 3)
	{
		changecolor(110);
		gotoxy(c3.lin + 1, c3.col);
		printf("%c", 30);
	}
	else
	{
		changecolor(14);
		gotoxy(c3.lin + 1, c3.col);
		printf("%c", 30);
	}

	if (M[c3.lin][c3.col] == 1)
	{
		changecolor(112);
		gotoxy(c3.lin, c3.col);
		printf("_");
	}
	else if (M[c3.lin][c3.col] == 2)
	{
		changecolor(192);
		gotoxy(c3.lin, c3.col);
		printf("_");
	}
	else if (M[c3.lin][c3.col] == 3)
	{
		changecolor(96);
		gotoxy(c3.lin, c3.col);
		printf(" ");
	}
	else
	{
		changecolor(alb);
		gotoxy(c3.lin, c3.col);
		printf(" ");
	}
	c3.lin++;
}
int levelclear(int M[][75])
{
	int i, j;
	for (i = 1; i <= 6; i++)
	{
		for (j = 1; j <= 70; j++)
		{
			if (M[i][j] >= 2) return 0;
		}
	}
	return 1;
}
void printmainmenu()
{
	changecolor(12);
	gotoxy(11, 26);
	printf("%c", 1);
	changecolor(alb);
	printf(" PLAY");

	changecolor(12);
	gotoxy(12, 26);
	printf("%c", 1);
	changecolor(alb);
	printf(" Instructions");

	changecolor(12);
	gotoxy(13, 26);
	printf("%c", 1);
	changecolor(alb);
	printf(" Scores");
}
void introduscor(char name[], int score)
{
	FILE *p;
	p = fopen("top10.out", "a");
	fprintf(p, "%s %d\n", name, score);
	fclose(p);
}
void loadinstructions()
{
	int nr = 2;
	char s;
	FILE *p;
	p = fopen("instructions.in", "r");
	s = getc(p);
	gotoxy(nr, 2);
	while (s != EOF)
	{
		if (s == '\n')
		{
			nr++; gotoxy(nr, 2);
		}
		else printf("%c", s);
		s = getc(p);
	}
	fclose(p);
}
void loadtop10()
{
	int nr = 2;
	char s;
	FILE *p;
	p = fopen("top10.out", "r");
	s = getc(p);
	gotoxy(nr, 2);
	while (s != EOF)
	{
		if (s == '\n')
		{
			nr++; gotoxy(nr, 2);
		}
		else printf("%c", s);
		s = getc(p);
	}
	fclose(p);
}
int main()
{
	int M[25][75], lifes, win = 0, pause = 0, jbarl = 22, jbarr, score = 0, lasershots = 0, lasermove = 0, level, intro = 1, lin, instr = 0, top10 = 0;
	double t1, t2, k1, k2;
	bila B, L;
	bonus b1, b2, b3, b4;
	b1.exists = 0;
	b2.exists = 0;
	char movbar;
	SetConsoleTitle(TEXT("Break It!"));
	srand(time(NULL));
	t1 = GetTickCount();
	k1 = GetTickCount();
	jbarr = jbarl + 13;//coordonata coloana cea mai din dreapta a barii
	clearcursor();
	fill(M);
	PlaySound(TEXT("intro.wav"), 0, SND_FILENAME | SND_NODEFAULT | SND_ASYNC | SND_LOOP);
	load("gameintro.in"); Sleep(3000); clearintro();
	lin = 11;
	printmainmenu();
	gotoxy(lin, 26);
	changecolor(9);
	printf("%c", 1);
	while (intro)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 's':
			{
						if (lin == 11 && instr == 0)
						{
							gotoxy(11, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(12, 26);
							changecolor(9);
							printf("%c", 1);
						}
						if (lin == 12 && instr == 0)
						{
							gotoxy(12, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(13, 26);
							changecolor(9);
							printf("%c", 1);
						}
						if (lin == 13 && instr == 0)
						{
							gotoxy(13, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(11, 26);
							changecolor(9);
							printf("%c", 1);
							lin = 10;
						}
						lin++;
						break;
			}
			case 'S':
			{
						if (lin == 11 && instr == 0)
						{
							gotoxy(11, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(12, 26);
							changecolor(9);
							printf("%c", 1);
						}
						if (lin == 12 && instr == 0)
						{
							gotoxy(12, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(13, 26);
							changecolor(9);
							printf("%c", 1);
						}
						if (lin == 13 && instr == 0)
						{
							gotoxy(13, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(11, 26);
							changecolor(9);
							printf("%c", 1);
							lin = 10;
						}
						lin++;
						break;
			}
				////////
			case 'w':
			{
						if (lin == 11 && instr == 0)
						{
							gotoxy(11, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(13, 26);
							changecolor(9);
							printf("%c", 1);
							lin = 14;
						}
						if (lin == 12 && instr == 0)
						{
							gotoxy(12, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(11, 26);
							changecolor(9);
							printf("%c", 1);
						}
						if (lin == 13 && instr == 0)
						{
							gotoxy(13, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(12, 26);
							changecolor(9);
							printf("%c", 1);
						}
						lin--;
						break;
			}
			case 'W':
			{
						if (lin == 11 && instr == 0)
						{
							gotoxy(11, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(13, 26);
							changecolor(9);
							printf("%c", 1);
							lin = 14;
						}
						if (lin == 12 && instr == 0)
						{
							gotoxy(12, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(11, 26);
							changecolor(9);
							printf("%c", 1);
						}
						if (lin == 13 && instr == 0)
						{
							gotoxy(13, 26);
							changecolor(12);
							printf("%c", 1);
							gotoxy(12, 26);
							changecolor(9);
							printf("%c", 1);
						}
						lin--;
						break;
			}
			case ' ':
			{
						if (lin == 11 && instr == 0 && top10 == 0)
						{
							clearintro();
							PlaySound(NULL, 0, SND_ASYNC); PlaySound(TEXT("song1.wav"), 0, SND_FILENAME | SND_NODEFAULT | SND_ASYNC | SND_LOOP);
							Sleep(1000);
							intro = 0;
							lifes = 3;
							loadmap(M, "map1.in");
							level = 1;
							printlevel(level);
							printlifes(lifes);
							printscore(score);
							fillbara(M, jbarl, jbarr);
							fillbila(M, B);
						}
						if (lin == 12 && instr == 0 && top10 == 0)
						{
							clearintro();
							loadinstructions();
							instr = 1;
							char asd = _getch();
							while (asd != ' ')
							{
								asd = _getch();
							}
							instr = 0;
							clearintro();
							lin = 11;
							printmainmenu();
							gotoxy(lin, 26);
							changecolor(9);
							printf("%c", 1);
						}
						if (lin == 13 && instr == 0 && top10 == 0)
						{
							clearintro();
							loadtop10();
							top10 = 1;
							char asd = _getch();
							while (asd != ' ')
							{
								asd = _getch();
							}
							top10 = 0;
							clearintro();
							lin = 11;
							printmainmenu();
							gotoxy(lin, 26);
							changecolor(9);
							printf("%c", 1);
						}
						break;
			}
			}

		}
	}
	while (lifes && !win)//conditiile pentru care jocul nu se sfarseste (game loop)
	{
		t2 = GetTickCount() / 100;
		k2 = GetTickCount() / 200;
		if (B.lin == 21 || B.lin == 22)//conditia pentru care pierd o viata
		{
			changecolor(negru);
			gotoxy(21, B.col);
			printf(" ");
			gotoxy(22, B.col);
			printf(" ");
			lifes--;
			updatelifes(lifes);
			fillbila(M, B);
			clearbara(M, jbarl, jbarr);
			jbarl = 22;
			jbarr = jbarl + 13;
			fillbara(M, jbarl, jbarr);
			Sleep(1000);
		}
		if (_kbhit())
		{
			movbar = _getch();
			switch (movbar)
			{
			case left:{if (!pause){ slidebarleft(M, jbarl, jbarr); }break; }
			case LEFT:{if (!pause){ slidebarleft(M, jbarl, jbarr); }break; }
			case right:{if (!pause){ slidebarright(M, jbarl, jbarr); } break; }
			case RIGHT:{if (!pause){ slidebarright(M, jbarl, jbarr); break; } }//folosirea tastelor a/A si d/D pentru deplasarea barii
			case ' '://folosirea tastei "space" ca tasta de pauza/reluarea a jocului
			{
						 if (pause == 0)
						 {
							 pause = 1; printpause();
						 }
						 else
						 {
							 pause = 0; clearpause(); if (B.sens == 3) movbar = 'a'; else movbar = 'd';
						 }
						 break;
			}
			case 'w'://folosirea tastei w/W pentru a trage cu laserul
			{
						 if (lasershots && lasermove == 0)
						 {
							 L.dir = 1;
							 L.sens = 2;
							 L.lin = 20;
							 L.col = (jbarl + jbarr) / 2;
							 lasermove = 1;
							 lasershots--;
						 }
						 if (B.sens == 3) movbar = 'a'; else movbar = 'd';
						 break;
			}
			case 'W':
			{
						if (lasershots && lasermove == 0)
						{
							L.dir = 1;
							L.sens = 2;
							L.lin = 20;
							L.col = (jbarl + jbarr) / 2;
							lasermove = 1;
							lasershots--;
						}
						if (B.sens == 3) movbar = 'a'; else movbar = 'd';
						break;
			}
			default:{break; }
			}
		}
		if (t2 - t1 && lasermove && !pause)
		{
			move(M, L, movbar, score, b1, b2, b3, b4, lasermove);
		}
		/////////////////extra life
		if (k2 - k1 && b1.exists == 1 && !pause)
		{
			moveb1(M, b1);
		}
		if (b1.lin == 20 && b1.exists == 1)
		{
			if (M[b1.lin + 1][b1.col] == -1)
			{
				b1.exists = 0;
				lifes++;
				updatelifes(lifes);
				changecolor(alb);
				gotoxy(b1.lin, b1.col);
				printf(" ");
			}
			else
			{
				b1.exists = 0;
				changecolor(alb);
				gotoxy(b1.lin, b1.col);
				printf(" ");
			}
		}
		//////////////expand
		if (k2 - k1 && b2.exists == 1 && !pause)
		{
			moveb2(M, b2);
		}
		if (b2.lin == 20 && b2.exists == 1)
		{
			if (M[b2.lin + 1][b2.col] == -1)
			{
				fillbara(M, jbarl - 3, jbarr + 3);
				jbarl = jbarl - 3;
				jbarr = jbarr + 3;
				b2.exists = 0;
				changecolor(alb);
				gotoxy(b2.lin, b2.col);
				printf(" ");
			}
			else
			{
				b2.exists = 0;
				changecolor(alb);
				gotoxy(b2.lin, b2.col);
				printf(" ");
			}
		}
		//////////////laser
		if (k2 - k1 && b3.exists == 1 && !pause)
		{
			moveb3(M, b3);
		}
		if (b3.lin == 20 && b3.exists == 1)
		{
			if (M[b3.lin + 1][b3.col] == -1)
			{
				lasershots = 3;
				b3.exists = 0;
				changecolor(alb);
				gotoxy(b3.lin, b3.col);
				printf(" ");
			}
			else
			{
				b3.exists = 0;
				changecolor(alb);
				gotoxy(b3.lin, b3.col);
				printf(" ");
			}
		}
		//////////////
		if (t2 - t1 && !pause)//conditiile pentru care bila se misca
		{
			move(M, B, movbar, score, b1, b2, b3, b4, lasermove);
			updatescore(score);
			t1 = t2;
			k1 = k2;
		}

		///////////////LEVEL UNLOCKING
		if (levelclear(M))
		{
			level++;
			updatelevel(level);
			changecolor(alb);
			gotoxy(B.lin, B.col); printf(" ");
			fillbila(M, B);
			clearbara(M, jbarl, jbarr);
			jbarl = 22;
			jbarr = jbarl + 13;
			fillbara(M, jbarl, jbarr);
			lasershots = 0;
			switch (level)
			{
			case 2:{loadmap(M, "map2.in"); Sleep(1000); break; }
			case 3:{loadmap(M, "map3.in"); Sleep(1000); break; }
			case 4:{loadmap(M, "map4.in"); PlaySound(NULL, 0, SND_ASYNC); PlaySound(TEXT("song2.wav"), 0, SND_FILENAME | SND_NODEFAULT | SND_ASYNC | SND_LOOP); Sleep(1000); break; }
			case 5:{loadmap(M, "map5.in"); Sleep(1000); break; }
			case 6:{loadmap(M, "map6.in"); Sleep(1000); break; }
			case 7:{loadmap(M, "map7.in"); PlaySound(NULL, 0, SND_ASYNC); PlaySound(TEXT("song3.wav"), 0, SND_FILENAME | SND_NODEFAULT | SND_ASYNC | SND_LOOP); Sleep(1000); break; }
			case 8:{loadmap(M, "map8.in"); Sleep(1000); break; }
			case 9:{loadmap(M, "map9.in"); Sleep(1000); break; }
			case 10:{win = 1; lifes = 0; break; }
			default:break;
			}
		}
	}
	if (lifes == 0)
	{
		if (win == 1)
		{
			PlaySound(NULL, 0, SND_ASYNC);
			clearintro();
			Sleep(1000);
			load("youwon.in");
			Sleep(4000);
		}
		else
		{
			PlaySound(NULL, 0, SND_ASYNC);
			clearintro();
			Sleep(1000);
			load("youlost.in");
			Sleep(4000);
		}
	}
	clearintro();
	char nume[30];
	changecolor(10);
	gotoxy(10, 3);
	printf("Introduce your name:");
	scanf("%s", &nume);
	introduscor(nume, score);
}