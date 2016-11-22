#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

#define MAXSIZE 100
typedef enum state {DEAD,ALIVE1,ALIVE2};
typedef enum state Grid[MAXSIZE + 2][MAXSIZE + 2];
void CopyMap(Grid map, Grid newmap, int n);
void Initialize_random(Grid map, int n);
void Initialize_manul(Grid map, int n,static int add1,static int add2);
int NeighborCount(Grid map, int row, int col);
void WriteMap(Grid map, int n);
int P1Count(Grid map, int n);
void Fix(Grid map, int n,int a,int b,static int add1,static int add2);
static int ad1 = 0, ad2 = 0,g=1;

void main(){
	int row, col, n;
	char ch;
	printf("<<<<<<<<<<<<<<<<<<<< �� �� �� Ϸ >>>>>>>>>>>>>>>>>>>>>>>>\n\n");
	printf("����������ռ��С���߳�����");
	scanf_s("%d", &n);
	Grid map;
	Grid newmap;
	
	int v = 1000;
	printf("��������ʱ�䣨��λ�����룩��");
	scanf_s("%d", &v);

	COORD loc;
	loc.X = 0;
	loc.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);//return
	for (int i = 1; i <= n; i++)
		printf("                                                                    \n");

	WriteMap(map, n);
	/*
	printf("��ѡ���ʼ����ʽ��1.�ֶ��������ꣻ2.�Զ����ɣ���");
	int choose = 2;
	scanf_s("%d", &choose);
	if (choose == 1)
		Initialize_manul(map, n,ad1,ad2);
	else Initialize_random( map, n);
	*/
	
	Initialize_manul(map, n, ad1, ad2);

	loc.X = 0;
	loc.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);//return
	for (int i=1; i <= n*n;i++)
		printf("                                                                    \n");

	loc.X = 0;
	loc.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);//return
	printf("<<<<<<<<<<<<<<<<<<<< �� �� �� Ϸ >>>>>>>>>>>>>>>>>>>>>>>>\n\n");

	WriteMap(map, n);
	printf("���ĳ�ʼ��������ͼ��ʾ\n�� 0 ��\n�밴<Enter>����ʼ�۲�\n");
	getchar();
	getchar();
	
	while ( 0/*getchar() != '\n' */);
	
	do {
		for (row = 0; row <= n + 1; row++)
			map[row][0] = map[row][n + 1] = DEAD;
		for (col = 1; col <= n; col++)
			map[0][col] = map[n + 1][col]=DEAD;
		
		for (row = 1; row <= n;row++)
		for (col = 1; col <= n; col++)
			switch (NeighborCount(map, row, col)){
			case 0:
			case 1:
				newmap[row][col] = DEAD; break;
			case 2:
				newmap[row][col] = map[row][col]; break;
			case 3:
				switch (P1Count(map, row, col)){
				case 0:
					newmap[row][col] = ALIVE2; break;
				case 3:
					newmap[row][col] = ALIVE1; break;
				case 1:
					if (map[row][col] != ALIVE1)
						newmap[row][col] = ALIVE2; 
					else newmap[row][col] = map[row][col];
					break;
				case 2:
					if(map[row][col]!=ALIVE2)
						newmap[row][col] = ALIVE1; 
					else newmap[row][col] = map[row][col]; 
					break;
				}break;
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				newmap[row][col] = DEAD; break;
		}
		CopyMap(map, newmap, n);
		WriteMap(map, n);
		printf("                                  \n�� ");
		printf("%d ��                            \n", g++);
		printf("���һ���������״̬��Ŀ��%d\n��Ҷ����������״̬��Ŀ��%d\n", ad1, ad2);
		printf("���ո����ͣ���������״̬\n");
		//printf("�����۲���һ��YES or NO\n");
		Sleep(v);//auto

		int flag = 1;
		char unch;
		while (flag==1){
			if (_kbhit() && (unch = _getch()) == ' ')
			{
				int a=0,b=0;
				Fix(map, n,a,b,ad1,ad2);
				WriteMap(map, n);
				getchar();
				break;

			}
			else break;
		}
		
	}
	while ( 1 /*ch = getchar() != 'n'*/);
	
}

void Initialize_manul(Grid map, int n,static int add1,static int add2){
	
	
	int row, col;
	for (row = 0; row <= n + 1;row++)
	for (col = 0; col < n + 1; col++)
		map[row][col] = DEAD;

	printf("�����1�����ʼ��������״̬������0,0��������,��ʹ��Ӣ�Ķ��ţ�\n");
	scanf_s("%d,%d", &row, &col);
	while (row != 0 | col != 0){//random
		if (row >= 1 && row <= n&&col >= 1 && col <= n)
		{
			map[row][col] = ALIVE1;
			WriteMap(map, n);
			printf("\n     \b\b\b\b\b");
			add1++;
	}
		else
			printf("���󣡲��Ϸ������꣡\n");
		scanf_s("%d,%d", &row, &col);
	}

	printf("�����2�����ʼ��������״̬������0,0��������,��ʹ��Ӣ�Ķ��ţ�\n");
	scanf_s("%d,%d", &row, &col);
	while (row != 0 | col != 0){//random
		if (row >= 1 && row <= n&&col >= 1 && col <= n&&map[row][col] != ALIVE1)
		{
			map[row][col] = ALIVE2;
			WriteMap(map, n);
			printf("\n\n\n     \b\b\b\b\b");
			add2++;
		}
		else
			printf("���󣡲��Ϸ������꣡\n");
		scanf_s("%d,%d", &row, &col);
	}
	ad1 = add1;
	ad2 = add2;
}

void Fix(Grid map, int n,int a,int b,int add1,int add2){

	int row, col;

	printf("�����1�����������״̬������0,0��������,��ʹ��Ӣ�Ķ��ţ�\n");
	scanf_s("%d,%d", &row, &col);
	while (row != 0 | col != 0){//random
		if (row >= 1 && row <= n&&col >= 1 && col <= n&&map[row][col]!=ALIVE2)
		{		
			map[row][col] = ALIVE1;
			a++; add1++;
			WriteMap(map, n);
			for (int i = 1; i <= 6; i++)
				printf("\n");
			printf("     \b\b\b\b\b");
		}
		else
		{
			printf("���󣡲��Ϸ������꣡\n");
			a++; a++;
		}
		scanf_s("%d,%d", &row, &col);
	}

	printf("�����2�����������״̬������0,0��������,��ʹ��Ӣ�Ķ��ţ�\n");
	scanf_s("%d,%d", &row, &col);
	while (row != 0 | col != 0){//random
		if (row >= 1 && row <= n&&col >= 1 && col <= n&&map[row][col] != ALIVE1){
			map[row][col] = ALIVE2;
			b++; add2++;
			WriteMap(map, n);
			for (int i = 1; i <=  8; i++)
				printf("\n");
			printf("     \b\b\b\b\b");
		}
		else{
			printf("���󣡲��Ϸ������꣡\n");
			b++; b++;
		}
		scanf_s("%d,%d", &row, &col);
	}

	COORD loc;
	loc.X = 0;
	loc.Y = n+7;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);//return
	for (int i = 1; i <= 6; i++)
		printf("                                                           \n");

	ad1 = add1;
	ad2 = add2;

	WriteMap(map, n);
	printf("                                  \n�� ");
	printf("%d ��                            \n", g++);
	printf("���һ���������״̬��Ŀ��%d\n��Ҷ����������״̬��Ŀ��%d\n", ad1, ad2);
	printf("��<Enter>������                    ");
	getchar();

}


void Initialize_random(Grid map, int n){

	int c;
	srand(time(NULL));
	c = rand() % (n*n);//random



	int row, col;
	for (row = 0; row <= n + 1; row++)
	for (col = 0; col < n + 1; col++)
		map[row][col] = DEAD;

	while (c){//random
		
		row = rand() % (n-1);
		col = rand() % (n-1);
		row++; col++;//random
		
		if(row<n/2)
			map[row][col] = ALIVE1;
		else if(row>n/2)
			map[row][col] = ALIVE2;
		else map[row][col] = DEAD;

		c--;//random
	}
}


int NeighborCount(Grid map, int row, int col){
	int i;
	int j;
	int count = 0;
	for (i = row - 1; i <= row + 1;i++)
	for (j = col - 1; j <= col + 1;j++)
	if (map[i][j] != DEAD)
		count++;
	if (map[row][col] != DEAD)
		count--;
	return count;
}

int P1Count(Grid map, int row, int col){
	int i;
	int j;
	int count = 0;
	for (i = row - 1; i <= row + 1; i++)
	for (j = col - 1; j <= col + 1; j++)
	if (map[i][j] == ALIVE1)
		count++;
	if (map[row][col] == ALIVE1 )
		count--;
	return count;
}


void WriteMap(Grid map, int n){
	
	COORD loc;
	loc.X = 0;
	loc.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);//return
	
	int row, col;
	putchar('\n');
	putchar('\n');
	for (row = 1; row <= n; row++){
	for (col = 1; col <= n; col++)
	if (map[row][col] == ALIVE1)
		putchar('O');
	else if (map[row][col] == ALIVE2)
		putchar('*');
	else
		putchar(' ');
	putchar('\n');
	}
}

void CopyMap(Grid map, Grid newmap, int n){
	int row, col;
	for (row = 0; row <= n + 1;row++)
	for (col = 0; col <= n + 1; col++)
		map[row][col] = newmap[row][col];
}
