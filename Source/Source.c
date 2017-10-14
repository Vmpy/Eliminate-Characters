#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <conio.h>
#include <time.h>
#include <stdbool.h> 

#define NUM 7
#define TYPE 5

/*****************************控制台颜色函数宏定义*****************************/
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED)
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN)
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE)
#define GREENPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define REDPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY)
#define BLUEPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define YELLO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY)
#define INDIG SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define MagentaPlus SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define White SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define Other SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED&FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)

char Map[NUM][NUM];

void Init(void);
void Display(int,int,int,int,int,int); 
char RandCh(void);
void Master(void);
int CheckLegal(int*,int*);
int Eliminate(int*,int*);
int RemoveCh(void);
int ShiftAndRand(void);

int main(void)
{
	srand((unsigned)(time(NULL)));
	Init();
	Master();
	return 0;
}

void Init(void)
{
	int index,index2;
	for(index = 0;index < NUM;index++)
	{
		for(index2 = 0;index2 < NUM;index2++)
		{
			Map[index][index2] = RandCh();
		}
	}
}

void Master(void)
{
	char ch;
	int KeyNum = 0;
	int DisplayPosx[2] = {-1,-1};
	int DisplayPosy[2] = {-1,-1};
	int Posx,Posy;
	Posx = Posy = 0;
	Display(-1,-1,-1,-1,Posx,Posy);
	while(1)
	{
		ch = getch();
		switch(ch)
		{
			case 'A':
			case 'a':
			{
				if(Posx)
				{
					Posx--;
				}
				Display(-1,-1,-1,-1,Posx,Posy);
				break;
			}
			case 'D':
			case 'd':
			{
				if(Posx != NUM)
				{
					Posx++;
				}
				Display(-1,-1,-1,-1,Posx,Posy);
				break;
			}
			case 'W':
			case 'w':
			{
				if(Posy)
				{
					Posy--;
				}
				Display(-1,-1,-1,-1,Posx,Posy);
				break;
			}
			case 'S':
			case 's':
			{
				if(Posy != NUM)
				{
					Posy++;
				}
				Display(-1,-1,-1,-1,Posx,Posy);
				break;
			}
			case 'I':
			case 'i':
			{
				DisplayPosx[KeyNum%2] = Posx;
				DisplayPosy[KeyNum%2] = Posy;
				KeyNum++;
				if(CheckLegal(DisplayPosx,DisplayPosy))
				{
					Display(DisplayPosx[0],DisplayPosx[1],DisplayPosy[0],DisplayPosy[1],Posx,Posy);
				}
				else
				{
					Display(-1,-1,-1,-1,Posx,Posy);
				}
				break;
			}
			case 'O':
			case 'o':
			{
				if(CheckLegal(DisplayPosx,DisplayPosy))
				{
					Eliminate(DisplayPosx,DisplayPosy);
					Display(DisplayPosx[0],DisplayPosx[1],DisplayPosy[0],DisplayPosy[1],Posx,Posy);
				}
			} 
		}
	}
}

int Eliminate(int* X,int*Y)
{
	char Tmp;
	Map[X[0]][Y[0]] = Tmp;
	Map[X[0]][Y[0]] = Map[X[1]][Y[1]];
	Map[X[1]][Y[1]] = Tmp;
	RemoveCh();
}

int RemoveCh(void)
{
	int x,y;
	bool MapList[NUM][NUM] = {{false}};
	
	for(x = 0;x < NUM;x++)
	{
		for(y = 0;y < NUM;y++)
		{
			if(Map[x][y] == Map[x][y+1] && Map[x][y+1] == Map[x][y+2])
			{
				int Tmp = 2;
				int Each;
				while(Map[x][y+Tmp] == Map[x][y+Tmp+1])
				{
					Tmp++;
				}
				for(Each = 0;Each <= Tmp;Each++)
				{
					MapList[x][y+Each] = true;
				}
			}
			if(Map[x][y] == Map[x+1][y] && Map[x+1][y] == Map[x+2][y])
			{
				int Tmp = 2;
				int Each;
				while(Map[x+Tmp][y] == Map[x+Tmp+1][y])
				{
					Tmp++;
				}
				for(Each = 0;Each <= Tmp;Each++)
				{
					MapList[x+Each][y] = true;
				}
			} 
		} 
	}
	
	for(x = 0;x < NUM;x++)
	{
		for(y = 0;y < NUM;y++)
		{
			if(MapList[x][y])
			{
				Map[x][y] = 0;
			}
		}
	}
	
	ShiftAndRand();
	
}

int ShiftAndRand(void)
{
	int index,index2;
	int Tmp;
	for(index = NUM-1;index >= 0;index--)
	{
		for(index2 = NUM-1;index2 >= 0;index2--)
		{
			if(Map[index][index2] == 0)
			{
				while(Map[index][index2] == 0)
				{
					for(Tmp = index2;Tmp > 0; Tmp--)
					{
						Map[index][Tmp] = Map[index][Tmp-1]; 
					}
				}
			}
		}
	}
	
	for(index = 0;index < NUM;index++)
	{
		for(index2 = 0;index2 < NUM;index2++)
		{
			if(Map[index][index2] == 0)
			{
				Map[index][index2] = RandCh();
			}
		}
	}
	return 0;
}

int CheckLegal(int * N1,int * N2)
{
	if(N1[0] != -1 && N1[1] != -1)
	{
		if(N2[0] != -1 && N2[1] != -1)
		{
			return 1;
		}
	}
	return 0;
}

void Display(int x1,int x2,int y1,int y2,int Fingerx,int Fingery)
{
	int x,y;
	char Finger[NUM][NUM] = {{0}};
	
	if(x1 != -1)
	{
		Finger[x1][y1] = '.';
		Finger[x2][y2] = '.';
	}
	
	system("cls");
	
	for(y = 0;y < NUM;y++)
	{
		for(x = 0;x < NUM;x++)
		{
			if(x == Fingerx && y == Fingery)
			{
				GREENPLUS;
			}
			else
			{
				White;
			} 
			printf("%c%c",Map[x][y],Finger[x][y]);
		}
		printf("\n");
	}
}

char RandCh(void)
{
	switch(rand()%TYPE)
	{
		case 0:return '@';
		case 1:return '#';
		case 2:return '$';
		case 3:return '&';
		case 4:return '%'; 
	}
} 
