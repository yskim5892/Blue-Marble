/*
made by K.Y.S

���� ����
//-���������忡�� �� ����
-���������� �������� �����
-�Ļ��ϰų� �� �����ϸ� ������ ���� �ߴ� ��ǥ
//-���������忡�� ���� �� ����, Ȳ�ݿ��� ��
//-�ݾ״����� ������ ��

 �ΰ����� �ֱ�
 �ڱ� �� �ɸ��� �߰� ���
 2012/11/25

*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <string.h>

#define LIGHT_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x02a) // ����
#define SKY SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x002b) //�ϴû�
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x002c) //������
#define FLUORE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x002d) //����
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x002e) //�����
#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x002f) // ��� 

#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0029) //�Ķ��� 
#define GOLD SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0026) //�ݻ�
#define BLACK SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0020) //������ 
//0: ���� 1: �Ķ� 2: �ʷ� 3:���� 4: ���� 5: ���� 6: ��� 7: ��� 8:ȸ�� 9:���� �Ķ� 

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13
#define SPACE_BAR 32
#define BACKSPACE 8
#define TAB 9
#define PAUSE 112
#define PLUS 43
#define MINUS 45
#define DEL 83

#define VILLA '^'     //����
#define BUILDING '@'  //����
#define HOTEL '&'     //ȣ��
#define PS playershape[0] //�÷��̾� ����ҷ��� �����  

#define NM 1   //normal
#define GK 2   //golden key
#define SP 3   //special
#define CNR 4  //corner

#define garosize 10  //�� ĭ ���� ������
#define serosize 4   //�� ĭ ���� ������
#define leftend 1    //�������� ���� ��
#define upend 1      //�������� ������ ��
#define dicesize 18  //�ֻ��� ������
#define gkboxgarosize 40  //Ȳ�ݿ��� ��� �ڽ� ���� ������
#define gkboxserosize 10  //Ȳ�ݿ��� ��� �ڽ� ���� ������


void gotoxy(int x, int y);
void cursorview(char show); //show�� 0�̸� �� ���̰�, 1�̸� ���̰� 
void setConSize (int row,int col );  
int wherex(void);
int wherey(void);

int fund;

class land
{
public:
	int owner;
	int v;	//villa		0, 1, 2
	int b;	//building  0, 1
	int h;  //hotel		0, 1
	int fee; //�����
	int price; //����
	int vprice, bprice, hprice; //����, ����, ȣ�� ����
	int pos; //1~40
	int pos1, pos2; //pos1:1~4, pos2: 0~9
	char name[10];
	int att;
	int i;
	
	void landshow()
	{
		if(owner==0)	WHITE;
		if(owner==1)	RED;
		if(owner==2)	BLUE;
		if(owner==3)	BLACK;
		if(owner==4)	YELLOW;

		if(pos1==1)
		{
			gotoxy(10*garosize+2+leftend-garosize*pos2, serosize*10+upend+1);
			printf("%s", name);

			gotoxy(10*garosize+6+leftend-garosize*pos2, serosize*10+upend+2);
			if(price>0)	printf("%d��", price/10);

			gotoxy(10*garosize+6+leftend-garosize*pos2, serosize*10+upend+3);
			for(i=1; i<=v; i++)	printf("%c", VILLA);
			for(i=1; i<=b; i++) printf("%c", BUILDING);
			for(i=1; i<=h; i++) printf("%c", HOTEL);
		}
		if(pos1==3)
		{
			gotoxy(leftend+2+garosize*pos2, upend+1);
			printf("%s", name);

			gotoxy(leftend+6+garosize*pos2, upend+2);
			if(price>0)	printf("%d��", price/10);

			gotoxy(leftend+6+garosize*pos2, upend+3);
			for(i=1; i<=v; i++)	printf("%c", VILLA);
			for(i=1; i<=b; i++) printf("%c", BUILDING);
			for(i=1; i<=h; i++) printf("%c", HOTEL);
		}
		if(pos1==2)
		{
			gotoxy(leftend+2, serosize*10+upend+1-serosize*pos2);
			printf("%s", name);

			gotoxy(leftend+6, serosize*10+upend+2-serosize*pos2);
			if(price>0)	printf("%d��", price/10);

			gotoxy(leftend+6, serosize*10+upend+3-serosize*pos2);
			for(i=1; i<=v; i++)	printf("%c", VILLA);
			for(i=1; i<=b; i++) printf("%c", BUILDING);
			for(i=1; i<=h; i++) printf("%c", HOTEL);
		}
		if(pos1==4)
		{
			gotoxy(garosize*10+leftend+2, upend+1+serosize*pos2);
			printf("%s", name);

			gotoxy(garosize*10+leftend+6, upend+2+serosize*pos2);
			if(price>0)	printf("%d��", price/10);

			gotoxy(garosize*10+leftend+6, upend+3+serosize*pos2);
			for(i=1; i<=v; i++)	printf("%c", VILLA);
			for(i=1; i<=b; i++) printf("%c", BUILDING);
			for(i=1; i<=h; i++) printf("%c", HOTEL);
		}
		if(pos==21) //��ȸ �������
		{
			gotoxy(leftend+6+garosize*pos2, upend+2);
			if(fund>0)	printf("%d��", fund/10);
			else printf("   ");
		}
	}
	void landerase()
    {
    	if(pos1==1)
		{
			gotoxy(10*garosize+6+leftend-garosize*pos2, serosize*10+upend+3);
			for(i=1; i<=v; i++)	printf("  ");
			for(i=1; i<=b; i++) printf("  ");
			for(i=1; i<=h; i++) printf("  ");
		}
		if(pos1==3)
		{
			gotoxy(leftend+6+garosize*pos2, upend+3);
			for(i=1; i<=v; i++)	printf("  ");
			for(i=1; i<=b; i++) printf("  ");
			for(i=1; i<=h; i++) printf("  ");
		}
		if(pos1==2)
		{
			gotoxy(leftend+6, serosize*10+upend+3-serosize*pos2);
			for(i=1; i<=v; i++)	printf("  ");
			for(i=1; i<=b; i++) printf("  ");
			for(i=1; i<=h; i++) printf("  ");
		}
		if(pos1==4)
		{
			gotoxy(garosize*10+leftend+6, upend+3+serosize*pos2);
			for(i=1; i<=v; i++)	printf("  ");
			for(i=1; i<=b; i++) printf("  ");
			for(i=1; i<=h; i++) printf("  ");
		}
		v=0; b=0; h=0; fee=0; owner=0;
    }
	void landboxshow(int P)
	{
		int i;
		if(P==0)	WHITE; if(P==1)	RED; if(P==2)	BLUE;
		if(P==3)	BLACK; if(P==4)	YELLOW;
		if(pos1==1)
		{
			for(i=0; i<=2; i++)
			{
				gotoxy(garosize*(10-pos2)+leftend, serosize*10+i+upend+1); printf("��");
				gotoxy(garosize*(10-pos2)+leftend+garosize, serosize*10+i+upend+1); printf("��");
			}
			for(i=0; i<=4; i++)
			{
				gotoxy(garosize*(10-pos2)+2*i+leftend+1, serosize*10+upend); printf("��");
				gotoxy(garosize*(10-pos2)+2*i+leftend+1, serosize*11+upend); printf("��");
			}
		}
		if(pos1==3)
		{
			for(i=0; i<=2; i++)
			{
				gotoxy(garosize*pos2+leftend, i+upend+1); printf("��");
				gotoxy(garosize*pos2+leftend+garosize, i+upend+1); printf("��");
			}
			for(i=0; i<=4; i++)
			{
				gotoxy(garosize*pos2+2*i+leftend+1, upend); printf("��");
				gotoxy(garosize*pos2+2*i+leftend+1, upend+serosize); printf("��");
			}
		}
		if(pos1==2)
		{
			for(i=0; i<=2; i++)
			{
				gotoxy(leftend, serosize*(10-pos2)+i+upend+1); printf("��");
				gotoxy(leftend+garosize, serosize*(10-pos2)+i+upend+1); printf("��");
			}
			for(i=0; i<=4; i++)
			{
				gotoxy(leftend+1+2*i, serosize*(10-pos2)+upend); printf("��");
				gotoxy(leftend+1+2*i, serosize*(10-pos2)+upend+serosize); printf("��");
			}
		}
		if(pos1==4)
		{
			for(i=0; i<=2; i++)
			{
				gotoxy(garosize*10+leftend, serosize*pos2+i+upend+1); printf("��");
				gotoxy(garosize*11+leftend, serosize*pos2+i+upend+1); printf("��");
			}
			for(i=0; i<=4; i++)
			{
				gotoxy(garosize*10+2*i+leftend+1, serosize*pos2+upend); printf("��");
				gotoxy(garosize*10+2*i+leftend+1, serosize*pos2+upend+serosize); printf("��");
			}
		}
	}
};

land LAND[41];
char *playershape[]={"��"};

class player  //1: ���� 2: �Ķ� 3:�ʷ� 4:���
{
public:
	int owner;
	int money[8];  //{50��, 10��, 5��, 2��, 1��, 5õ, 1õ} 
	int total; 
	int ter[41];
	int ude; //���� 0~2
	int mujeon; //������ 0~1
	int pos;  //1~40
	int pos1, pos2;   //pos1: 1~4, pos2: 0~9
	int muin; //���ε����� ���� �ϼ� (1~3) 
	int pasan; //�Ļ����� �� 1
	int i, j;
	
	void posinit()
	{
		if(pos==0)	//����������
		{
			pos1=0; pos2=0;
		}
		else
		{
			pos1=(pos-1)/10+1; pos2=(pos-1)%10;
		}
	}
	void moneyinit()
	{
        total=500*money[1]+100*money[2]+50*money[3]+20*money[4]+10*money[5]+5*money[6]+money[7];
    }
	void playershow()
	{
		if(owner==1)	RED;
		if(owner==2)	BLUE;
		if(owner==3)	BLACK;
		if(owner==4)	YELLOW;

		if(pos1==1) gotoxy(10*garosize+leftend+2-garosize*pos2+2*((owner-1)%2), 10*serosize+upend+2+(owner-1)/2);
		if(pos1==3) gotoxy(leftend+2+garosize*pos2+2*((owner-1)%2), upend+2+(owner-1)/2);
		if(pos1==2) gotoxy(leftend+2+2*((owner-1)%2), 10*serosize+upend+2-serosize*pos2+(owner-1)/2);
		if(pos1==4) gotoxy(10*garosize+leftend+2+2*((owner-1)%2), upend+2+serosize*pos2+(owner-1)/2);
		if(pos==0) gotoxy(9*garosize+leftend+2*((owner-1)%2)-1, upend+(owner-1)/2+serosize+4);	//���� ������
		printf("%s", PS);		
    }
    void moneyshow()
    {
        if(owner==0)	WHITE;
		if(owner==1)	RED;
		if(owner==2)	BLUE;
		if(owner==3)	BLACK;
		if(owner==4)	YELLOW;
		
		for(i=1; i<=9; i++)
		{
            gotoxy(10*garosize+leftend+24, 2+i+9*owner);
            switch(i)
            {
            case 1:
                printf("50���� : ");
                break;
            case 2:
                printf("10���� : ");
                break;
            case 3:
                printf("5����  : ");
                break;
            case 4:
                printf("2����  : ");
                break;
            case 5:
                printf("����   : ");
                break;
            case 6:
                printf("5õ��  : ");
                break;
            case 7:
                printf("õ��   : ");
                break;
			case 8:
				printf("�հ�   : ");
				break;
			case 9:
				if(ude!=0)
				{
					printf("���� %d��", ude);
				}
				for(j=1; j<=mujeon; j++)
				{
					if(ude!=0)
					{
						printf(", ");
					}
					printf("������");
				}
				break;
            }
			if(i<=7)	printf("%d��", money[i]);
			if(i==8)
			{
				printf("%d�� %dõ��     ", total/10, total-10*(total/10));
			}
         } 
    }
	void playererase()
    {
		if(pos1==1) gotoxy(10*garosize+leftend+2-10*pos2+2*((owner-1)%2), 10*serosize+leftend+2+(owner-1)/2);
		if(pos1==3) gotoxy(leftend+2+10*pos2+2*((owner-1)%2), leftend+2+(owner-1)/2);
		if(pos1==2) gotoxy(leftend+2+2*((owner-1)%2), 10*serosize+leftend+2-4*pos2+(owner-1)/2);
		if(pos1==4) gotoxy(10*garosize+leftend+2+2*((owner-1)%2), leftend+2+4*pos2+(owner-1)/2); 
		if(pos==0) gotoxy(9*garosize+leftend+2*((owner-1)%2)-1, upend+(owner-1)/2+serosize+4);	//���� ������
		printf("  "); 
    }
};
class dice
{
public:
    int th;
    int num;
    int owner;
    int i;
    void boxshow()
    {
        if(owner==0)	WHITE;
 	    if(owner==1)	RED;
     	if(owner==2)	BLUE;
		if(owner==3)	BLACK;
		if(owner==4)	YELLOW;
        for(i=2; i<=dicesize/2; i++)
        {
            gotoxy(11*garosize/2+leftend+(2*th-3)*2*i, upend+5*serosize+6);
            printf("��");
            gotoxy(11*garosize/2+leftend+(2*th-3)*2*i, upend+5*serosize+6+dicesize/2-1);
            printf("��");
        }
        for(i=1; i<=dicesize/2-2; i++)
        {      
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize+1), upend+5*serosize+6+i);
            printf("��");
            gotoxy(11*garosize/2+leftend+(2*th-3)*3, upend+5*serosize+6+i);
            printf("��");
        }
    }
    void diceshow(int number)
    {
        if(owner==0)	WHITE;
 	    if(owner==1)	RED;
     	if(owner==2)	BLUE;
		if(owner==3)	BLACK;
		if(owner==4)	YELLOW;
        switch(number)
        {
        case 1:
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/2+3), upend+5*serosize+6+dicesize/4);
            printf("%s", PS);
            break;         
        case 2:
            gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+dicesize/4);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+dicesize/4);
            printf("%s", PS);
            break;
        case 3:    
            gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/2+3), upend+5*serosize+6+dicesize/4);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+3*dicesize/8);
            printf("%s", PS);
            break;
        case 4:
            gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+3*dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+3*dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+dicesize/8);
            printf("%s", PS);
            break;
        case 5:
            gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+3*dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+3*dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/2+3), upend+5*serosize+6+dicesize/4);
            printf("%s", PS);
            break;
        case 6:
            gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+3*dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+3*dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+dicesize/8);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+dicesize/4);
            printf("%s", PS);
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+dicesize/4);
            printf("%s", PS);
            break;
        }
    }
    void diceerase(void)
    {
        gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+dicesize/8);
        printf("  ");
        gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+3*dicesize/8);
        printf("  ");
        gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+3*dicesize/8);
        printf("  ");
        gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+dicesize/8);
        printf("  ");
        gotoxy(11*garosize/2+leftend+(2*th-3)*(3*dicesize/4+3), upend+5*serosize+6+dicesize/4);
        printf("  ");
        gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/4+3), upend+5*serosize+6+dicesize/4);
        printf("  ");
        gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize/2+3), upend+5*serosize+6+dicesize/4);
        printf("  ");
    }
};

player PLAYER[5];
dice DICE[3];

void boardset(void);  //���� ����
void landset(void);   //�� ����
void GKset(void);     //Ȳ�ݿ��� ���� �迭 ����
int fee(land x);      //�� ���� ����Ḧ ����ϴ� �Լ�
void Start();         //������ �� �ʱ�ȭ
void turn(int P);     //player P�� ���� �����ϴ� �Լ�
void choose(int P, int landatt);  //player P�� ���� �ɷ��� �� �� ���� �����ϰ� �ϴ� �Լ�
int pay(int P, int price, int escapable);  //player P�� price�� ���� ���� �Լ� 
int f(int a); //f(1)=500, f(2)=100, f(3)=50, f(4)=20, f(5)=10, f(6)=5, f(7)=1
void receive(int P, int remain);  //player P�� remain�� ���� �޴� �Լ�
void sell(int P);  //player P�� ���� �Ĵ� �Լ�
void gkget(int P, int num);   //Ȳ�ݿ��踦 ����� �� �Լ�
void gkboxshow(void);  //Ȳ�ݿ��� �ڽ� �����ִ� �Լ�
void gkerase(void);    //Ȳ�ݿ��� �ڽ� ����� �Լ�
int spacetrip(int P);  //�ݷ����ȣ ���ֿ��� �Լ�

int pnum;
int t;
int gk[31];
int currentcard; //���� �ٴڿ� ���� ���� �ʴ� Ȳ�ݿ��� ��

int main()
{
	int i;
	int win=0;
	setConSize(70, 150);
	cursorview(0);
	system("color 27");
	
	Start();
	
	while(1)
	{
		win=1;
		for(i=1; i<=pnum; i++)
		{
			if(i!=t%pnum+1 && PLAYER[i].pasan==0) //�ڽ��� �ƴϸ鼭 �Ļ��� �ƴ� ����� �� ���̶� ������
			{
				win=0;
			}
		}
		if(win)
		{
			if(t%pnum+1==1)	 RED;    if(t%pnum+1==2)	 BLUE;
			if(t%pnum+1==3)	 BLACK;  if(t%pnum+1==4)	 YELLOW;
			gotoxy(leftend+5*garosize-15, upend+5*serosize+3);
			printf("��ΰ� �Ļ��Ͽ� player%d�� �¸��Ͽ����ϴ�!!\n", t%pnum+1);
			break;
		}
		if(PLAYER[t%pnum+1].pasan==0)
		{
			turn(t%pnum+1);
		}
        t++;
    }
	getch();
	return 0;
}

void boardset(void)
{
	int i, j, k;
	for(i=0; i<=11; i++)
	{
		for(j=0; j<=10; j++)
		{
			for(k=0; k<=4; k++)
			{
				if((!(1<=j && j<=9 && 2<=i && i<=9) || (i==8 && (j==1 || j==2))) && k<=2)
				{
					gotoxy(garosize*i+leftend, serosize*j+k+upend+1); printf("��");
				}
				if((!(1<=j && j<=9 && 2<=i && i<=9)) || (i==3 && (j==9 || j==8)))
				{
					gotoxy(garosize*j+2*k+leftend+1, serosize*i+upend); printf("��");
				}
			}
		}
	}
	gotoxy(8*garosize+leftend, serosize+upend+4); printf("��");
}	
void landset(void)
{
	int i;
	for(i=1; i<=40; i++)
	{
		LAND[i].owner=0;
		LAND[i].v=0; LAND[i].b=0; LAND[i].h=0; LAND[i].fee=0;
        LAND[i].pos=i; 
		LAND[i].pos1=(i-1)/10+1; LAND[i].pos2=(i-1)%10;
		LAND[i].att=NM;
	}
	LAND[1].price=0; strcpy(LAND[1].name, " ��  ��"); LAND[1].att=CNR;
	LAND[2].price=50; LAND[2].vprice=50; LAND[2].bprice=150; LAND[2].hprice=250; strcpy(LAND[2].name, "Ÿ������");
	LAND[3].price=0; strcpy(LAND[3].name, "Ȳ�ݿ���"); LAND[3].att=GK;
	LAND[4].price=80; LAND[4].vprice=50; LAND[4].bprice=150; LAND[4].hprice=250; strcpy(LAND[4].name, "ȫ ��");
	LAND[5].price=80; LAND[5].vprice=50; LAND[5].bprice=150; LAND[5].hprice=250; strcpy(LAND[5].name, "���Ҷ�");
	LAND[6].price=200; strcpy(LAND[6].name, "���ֵ�"); LAND[6].att=SP;
	LAND[7].price=100; LAND[7].vprice=50; LAND[7].bprice=150; LAND[7].hprice=250; strcpy(LAND[7].name, "�̰���");
	LAND[8].price=0; strcpy(LAND[8].name, "Ȳ�ݿ���"); LAND[8].att=GK;
	LAND[9].price=100; LAND[9].vprice=50; LAND[9].bprice=150; LAND[9].hprice=250; strcpy(LAND[9].name, "ī�̷�");
	LAND[10].price=120; LAND[10].vprice=50; LAND[10].bprice=150; LAND[10].hprice=250; strcpy(LAND[10].name, "�̽�ź��");

	LAND[11].price=0; strcpy(LAND[11].name, "���ε�"); LAND[11].att=CNR;
	LAND[12].price=140; LAND[12].vprice=100; LAND[12].bprice=300; LAND[12].hprice=500; strcpy(LAND[12].name, "���׳�");
	LAND[13].price=0; strcpy(LAND[13].name, "Ȳ�ݿ���"); LAND[13].att=GK;
	LAND[14].price=160; LAND[14].vprice=100; LAND[14].bprice=300; LAND[14].hprice=500; strcpy(LAND[14].name, "�����ϰ�");
	LAND[15].price=160; LAND[15].vprice=100; LAND[15].bprice=300; LAND[15].hprice=500; strcpy(LAND[15].name, "����Ȧ��");
	LAND[16].price=200; strcpy(LAND[16].name, "����"); LAND[16].att=SP;
	LAND[17].price=180; LAND[17].vprice=100; LAND[17].bprice=300; LAND[17].hprice=500; strcpy(LAND[17].name, "�븮��");
	LAND[18].price=0; strcpy(LAND[18].name, "Ȳ�ݿ���"); LAND[18].att=GK;
	LAND[19].price=180; LAND[19].vprice=100; LAND[19].bprice=300; LAND[19].hprice=500; strcpy(LAND[19].name, "������");
	LAND[20].price=200; LAND[20].vprice=100; LAND[20].bprice=300; LAND[20].hprice=500; strcpy(LAND[20].name, "��Ʈ����");

	LAND[21].price=0; strcpy(LAND[21].name, "��ȸ����"); LAND[21].att=CNR;
	LAND[22].price=220; LAND[22].vprice=150; LAND[22].bprice=450; LAND[22].hprice=750; strcpy(LAND[22].name, "�ο��뽺");
	LAND[23].price=0; strcpy(LAND[23].name, "Ȳ�ݿ���"); LAND[23].att=GK;
	LAND[24].price=240; LAND[24].vprice=150; LAND[24].bprice=450; LAND[24].hprice=750; strcpy(LAND[24].name, "���Ŀ��");
	LAND[25].price=240; LAND[25].vprice=150; LAND[25].bprice=450; LAND[25].hprice=750; strcpy(LAND[25].name, "�õ��");
	LAND[26].price=500; strcpy(LAND[26].name, "��  ��"); LAND[26].att=SP;
	LAND[27].price=260; LAND[27].vprice=150; LAND[27].bprice=450; LAND[27].hprice=750; strcpy(LAND[27].name, "�Ͽ���");
	LAND[28].price=260; LAND[28].vprice=150; LAND[28].bprice=450; LAND[28].hprice=750; strcpy(LAND[28].name, "������");
	LAND[29].price=300; strcpy(LAND[29].name, "������ȣ"); LAND[29].att=SP;
	LAND[30].price=280; LAND[30].vprice=150; LAND[30].bprice=450; LAND[30].hprice=750; strcpy(LAND[30].name, "���帮��");

	LAND[31].price=0; strcpy(LAND[31].name, "���ֿ���"); LAND[31].att=CNR;
	LAND[32].price=300; LAND[32].vprice=200; LAND[32].bprice=600; LAND[32].hprice=1000; strcpy(LAND[32].name, "��  ��");
	LAND[33].price=450; strcpy(LAND[33].name, "�ݷ����ȣ"); LAND[33].att=SP;
	LAND[34].price=320; LAND[34].vprice=200; LAND[34].bprice=600; LAND[34].hprice=1000; strcpy(LAND[34].name, "��  ��");
	LAND[35].price=320; LAND[35].vprice=200; LAND[35].bprice=600; LAND[35].hprice=1000; strcpy(LAND[35].name, "��  ��");
	LAND[36].price=0; strcpy(LAND[36].name, "Ȳ�ݿ���"); LAND[36].att=GK;
	LAND[37].price=350; LAND[37].vprice=200; LAND[37].bprice=600; LAND[37].hprice=1000; strcpy(LAND[37].name, "��  ��");
	LAND[38].price=350; LAND[38].vprice=200; LAND[38].bprice=600; LAND[38].hprice=1000; strcpy(LAND[38].name, "��  ��");
	LAND[39].price=150; strcpy(LAND[39].name, "��ȸ����"); LAND[39].att=CNR;
	LAND[40].price=1000; LAND[40].vprice=200; LAND[40].bprice=600; LAND[40].hprice=1000; strcpy(LAND[40].name, "��  ��");

}
void GKset(void)
{
	int i;
	int tmp;
	int a;
	srand(time(NULL));
	for(i=1; i<=30; i++)
	{
		gk[i]=i;
	}
	for(i=30; i>=2; i--)
	{
		a=rand()%i+1;
		tmp=gk[i];
		gk[i]=gk[a];
		gk[a]=tmp;
	}
}
int fee(land x)
{
	int f=0;
	switch(x.pos-1)
	{
	case 1: //Ÿ������
		if((x.v)==0 && x.b==0 && x.h==0)	f=2;
		else
		{
			f=5*(x.v)*(x.v)+5*(x.v)+90*x.b+250*x.h;
		}
		break;
	case 3: //ȫ�� 
		if((x.v)==0 && x.b==0 && x.h==0)	f=4;
		else
		{
			f=10*(x.v)*(x.v)+10*(x.v)+180*x.b+450*x.h;
		}
		break;
	case 4: //���Ҷ�
		if((x.v)==0 && x.b==0 && x.h==0)	f=4;
		else
		{
			f=10*(x.v)*(x.v)+10*(x.v)+180*x.b+450*x.h;
		}
		break;
	case 5:  //���ֵ�
		f=300;
		break;
	case 6:  //�̰���
		if((x.v)==0 && x.b==0 && x.h==0)	f=6;
		else
		{
			f=15*(x.v)*(x.v)+15*(x.v)+270*x.b+550*x.h;
		}
		break;
	case 8:  //ī�̷�
		if((x.v)==0 && x.b==0 && x.h==0)	f=6;
		else
		{
			f=15*(x.v)*(x.v)+15*(x.v)+270*x.b+550*x.h;
		}
		break;
	case 9:  //�̽�ź��
		if((x.v)==0 && x.b==0 && x.h==0)	f=8;
		else
		{
			f=10*(x.v)*(x.v)+30*(x.v)+300*x.b+600*x.h;
		}
		break;
	case 11:  //���׳� 
		if((x.v)==0 && x.b==0 && x.h==0)	f=10;
		else
		{
			f=25*(x.v)*(x.v)+25*(x.v)+450*x.b+750*x.h;
		}
		break;
	case 13:  //�����ϰ�
		if((x.v)==0 && x.b==0 && x.h==0)	f=12;
		else
		{
			f=30*(x.v)*(x.v)+30*(x.v)+500*x.b+900*x.h;
		}
		break;
	case 14:  //����Ȧ��
		if((x.v)==0 && x.b==0 && x.h==0)	f=12;
		else
		{
			f=30*(x.v)*(x.v)+30*(x.v)+500*x.b+900*x.h;
		}
		break;
	case 15:  //���忩����
		f=300;
		break;
	case 16:  //�븮��
		if((x.v)==0 && x.b==0 && x.h==0)	f=14;
		else
		{
			f=30*(x.v)*(x.v)+40*(x.v)+550*x.b+950*x.h;
		}
		break;
	case 18:  //������
		if((x.v)==0 && x.b==0 && x.h==0)	f=14;
		else
		{
			f=30*(x.v)*(x.v)+40*(x.v)+550*x.b+950*x.h;
		}
		break;
	case 19:  //��Ʈ����
		if((x.v)==0 && x.b==0 && x.h==0)	f=16;
		else
		{
			f=30*(x.v)*(x.v)+50*(x.v)+600*x.b+1000*x.h;
		}
		break;
	case 21:  //�ο��뽺 ���̷���
		if((x.v)==0 && x.b==0 && x.h==0)	f=18;
		else
		{
			f=35*(x.v)*(x.v)+55*(x.v)+700*x.b+1050*x.h;
		}
		break;
	case 23:  //���Ŀ��
		if((x.v)==0 && x.b==0 && x.h==0)	f=20;
		else
		{
			f=50*(x.v)*(x.v)+50*(x.v)+750*x.b+1100*x.h;
		}
		break;
	case 24:  //�õ��
		if((x.v)==0 && x.b==0 && x.h==0)	f=20;
		else
		{
			f=50*(x.v)*(x.v)+50*(x.v)+750*x.b+1100*x.h;
		}
		break;
	case 25:  //�λ�
		f=600;
		break;
	case 26:  //�Ͽ���
		if((x.v)==0 && x.b==0 && x.h==0)	f=22;
		else
		{
			f=55*(x.v)*(x.v)+55*(x.v)+800*x.b+1150*x.h;
		}
		break;
	case 27:  //������
		if((x.v)==0 && x.b==0 && x.h==0)	f=22;
		else
		{
			f=55*(x.v)*(x.v)+55*(x.v)+800*x.b+1150*x.h;
		}
		break;
	case 28:  //�� �����ں��� ȣ 
		f=250;
		break;
	case 29:  //���帮��
		if((x.v)==0 && x.b==0 && x.h==0)	f=24;
		else
		{
			f=60*(x.v)*(x.v)+60*(x.v)+850*x.b+1200*x.h;
		}
		break;
	case 31:  //����
		if((x.v)==0 && x.b==0 && x.h==0)	f=26;
		else
		{
			f=65*(x.v)*(x.v)+65*(x.v)+900*x.b+1270*x.h;
		}
		break;
	case 32:  //�ݷ����ȣ
		f=400;
		break;
	case 33:  //�ĸ�
		if((x.v)==0 && x.b==0 && x.h==0)	f=28;
		else
		{
			f=75*(x.v)*(x.v)+75*(x.v)+1000*x.b+1400*x.h;
		}
		break;
	case 34:  //�θ�
		if((x.v)==0 && x.b==0 && x.h==0)	f=28;
		else
		{
			f=75*(x.v)*(x.v)+75*(x.v)+1000*x.b+1400*x.h;
		}
		break;
	case 36:  //����
		if((x.v)==0 && x.b==0 && x.h==0)	f=35;
		else
		{
			f=80*(x.v)*(x.v)+90*(x.v)+1100*x.b+1500*x.h;
		}
		break;
	case 37:  //����
		if((x.v)==0 && x.b==0 && x.h==0)	f=35;
		else
		{
			f=80*(x.v)*(x.v)+90*(x.v)+1100*x.b+1500*x.h;
		}
		break;
	case 38:  //��ȸ�������
		f=150;
		break;
	case 39:  //����
		f=2000;
		break;
	}
	return f;
}	
void Start()
{
    int cursor=1;
    int input;
    int a=0;
	int i, j;
	gotoxy(leftend+11*garosize/2-10, upend+5*serosize+1);
	printf("��  ��  ��  ��  ����");
	gotoxy(leftend+11*garosize/2-10, upend+5*serosize+2);
	printf("      made by K.Y.S");
	boardset();
	landset();
	GKset();
	for(i=1; i<=40; i++)
	{
		LAND[i].landshow();
	}
	gotoxy(8*garosize+leftend+4, serosize+upend+1); printf("�� �� �� �� ��");

    gotoxy(leftend+5*garosize-3, upend+5*serosize+4);
	printf("2p     3p     4p");
    while(1)
    {
        gotoxy(7*cursor+leftend+5*garosize-10, upend+5*serosize+5);
        printf("��"); 
        input=getch();
        switch(input)
        {
        case ENTER:
            a=1;
            break;
        case LEFT:            
            if(cursor!=1)
            {
                gotoxy(7*cursor+leftend+5*garosize-10, upend+5*serosize+5); printf("  ");
                cursor-=1;
            }
            break;
        case RIGHT:
            if(cursor!=3)
            {
                gotoxy(7*cursor+leftend+5*garosize-10, upend+5*serosize+5); printf("  ");            
                cursor+=1;
            }
            break;
        }
        if(a==1)   break;
    }
    gotoxy(leftend+5*garosize-3, upend+5*serosize+4); printf("                 ");
    gotoxy(7*cursor+leftend+5*garosize-10, upend+5*serosize+5);  printf("  ");
    pnum=cursor+1;

	for(i=1; i<=pnum; i++)
	{
        PLAYER[i].owner=i;
        PLAYER[i].money[1]=2;
        for(j=2; j<=7; j++)
        {
              PLAYER[i].money[j]=5;
        }
		PLAYER[i].pasan=0;
		PLAYER[i].mujeon=0;
		PLAYER[i].muin=0;
		PLAYER[i].ude=0;
        PLAYER[i].pos=1;
        PLAYER[i].posinit();
        PLAYER[i].moneyinit();
        PLAYER[i].playershow();
        gotoxy(10*garosize+leftend+13, 3+9*i); printf("player%d", PLAYER[i].owner);
        PLAYER[i].moneyshow();
    }
	
    getch();
}   
void turn(int P)
{
    int i;
    int Double=0;
	int a=0;
	int input;
    srand(time(NULL));
Again:
	if(PLAYER[P].pasan==1)	return;		//�����Դµ� �Ļ����� ���
	if(PLAYER[P].pos>0)
	{
		PLAYER[P].posinit(); PLAYER[P].playershow();
		if(P==1)	RED;    if(P==2)	BLUE;
		if(P==3)	BLACK;  if(P==4)	YELLOW;
		gotoxy(leftend+5*garosize-13, upend+5*serosize+3);
		printf("                                    ");
		if(PLAYER[P].muin>0)
		{
			gotoxy(leftend+5*garosize-9, upend+5*serosize+3);
			printf("���ε����� ���� �� ��: %d", PLAYER[P].muin);
			if(PLAYER[P].mujeon==0)
			{
				while(getch()!=ENTER) i=1;
			}
			else
			{
				YELLOW;
				gotoxy(leftend+5*garosize-8, upend+5*serosize+4); printf("������ ��� Y or N", P);
				input=getch();
				gotoxy(leftend+5*garosize-8, upend+5*serosize+4); printf("                     ");
				while(1)
				{
					switch(input)
					{
					case 'y':
					case 'Y':
						a=1;
						PLAYER[P].mujeon=0;
						PLAYER[P].muin=0;
						gk[currentcard]=3;
						currentcard--;
						if(P==1)	RED;    if(P==2)	BLUE;
						if(P==3)	BLACK;  if(P==4)	YELLOW;
						gotoxy(leftend+5*garosize-13, upend+5*serosize+3); printf("player%d�� ���ε����� Ż���߽��ϴ�.", P);
						while(getch()!=ENTER) i=1;
						return;
					case 'n':
					case 'N':
						a=1;
						break;
					}
					if(a==1)	break;
				}
			}
		}
		gotoxy(leftend+5*garosize-3, upend+5*serosize+4); printf("player %d's turn", P);
		if(Double) printf("(again)");
		else printf("       ");
		Double=0;

		DICE[1].num=rand()%6+1;
		DICE[1].owner=P; DICE[2].owner=P;
		DICE[1].th=1; DICE[2].th=2;
		DICE[2].num=rand()%6+1;
		DICE[1].boxshow();
		for(i=1; i<=8; i++)
		{
			DICE[1].diceshow(rand()%6+1);
			Sleep(60);
			DICE[1].diceerase();
		}
		DICE[1].diceshow(DICE[1].num);
		DICE[2].boxshow();
		for(i=1; i<=8; i++)
		{
			DICE[2].diceshow(rand()%6+1);
			Sleep(60);
			DICE[2].diceerase();
		}
		DICE[2].diceshow(DICE[2].num);

		getch();

		
		if(PLAYER[P].muin==0) PLAYER[P].pos+=DICE[1].num+DICE[2].num;
		if(DICE[1].num==DICE[2].num) Double=1;
		
		if(Double==1 && PLAYER[P].muin!=0)
		{
			gotoxy(leftend+5*garosize-13, upend+5*serosize+3); printf("player%d�� ���ε����� Ż���߽��ϴ�.", P);
			while(getch()!=ENTER) i=1;
			PLAYER[P].muin=0;
			return;
		} 
		if(PLAYER[P].muin!=0)
		{
			PLAYER[P].muin-=1;
           
			return;
		}
		
		if(PLAYER[P].pos>40)
		{
			gotoxy(leftend+5*garosize-7, upend+5*serosize+3);
			printf("���� 20������ �޾ҽ��ϴ�.", P);
			PLAYER[P].pos%=40;
			getch();
			receive(P, 200);
			gotoxy(leftend+5*garosize-7, upend+5*serosize+3);
			printf("                                    ");
		}
		PLAYER[P].playererase();
		PLAYER[P].posinit();
		PLAYER[P].playershow();
    
		getch();
	}
     
    choose(P, LAND[PLAYER[P].pos].att);
    if(Double) goto Again;
}
void choose(int P, int landatt)
{
    int cursor=1;
    int input;
    int a=0; 
    int v=0, b=0, h=0;
    int cost;
	int pos; //���ֿ��� �� �� ������
    int i;
    if(landatt==NM && LAND[PLAYER[P].pos].owner==0)
    {
        WHITE;
        gotoxy(11*garosize/2+leftend-4, upend+serosize+7);
        printf("1. ����");
        gotoxy(11*garosize/2+leftend-4, upend+serosize+9); 
        printf("2. �н�"); 
        while(1)
        {
            gotoxy(11*garosize/2+leftend-7, upend+serosize+2*cursor+5);
            printf("��");
            input=getch();
            switch(input)
            {
            case ENTER:
                a=1;
                break;
            case UP:            
                if(cursor!=1)
                {
                    gotoxy(11*garosize/2+leftend-7, upend+serosize+2*cursor+5); printf("  ");
                    cursor-=1;
                }
                break;
            case DOWN:
                if(cursor!=2)
                {
                    gotoxy(11*garosize/2+leftend-7, upend+serosize+2*cursor+5); printf("  ");          
                    cursor+=1;
                }
                break;
            }
            if(a==1)   break;
        }
        a=0;
        gotoxy(11*garosize/2+leftend-4, upend+serosize+7); printf("       ");
        gotoxy(11*garosize/2+leftend-4, upend+serosize+9); printf("       ");
        gotoxy(11*garosize/2+leftend-7, upend+serosize+2*cursor+5); printf("  ");
        if(cursor==1)
        {
            WHITE;
            cost=LAND[PLAYER[P].pos].price;
            gotoxy(11*garosize/2+leftend-12, upend+serosize+3);
            printf("�Ǽ��� �ǹ��� �����ϼ���."); 
            gotoxy(11*garosize/2+leftend-25, upend+serosize+5);
            printf("����=space bar ���=delete ����=enter ������=esc");
            while(1)
            {
                gotoxy(11*garosize/2+leftend-12, upend+serosize+7);
                printf("����(%d����) : %d��", LAND[PLAYER[P].pos].vprice/10, v);
                gotoxy(11*garosize/2+leftend-12, upend+serosize+9);
                printf("����(%d����) : %d��", LAND[PLAYER[P].pos].bprice/10, b);
                gotoxy(11*garosize/2+leftend-12, upend+serosize+11);
                printf("ȣ��(%d����) : %d��", LAND[PLAYER[P].pos].hprice/10, h);
				gotoxy(11*garosize/2+leftend-12, upend+serosize+13);
				printf("�� ����: %d����", (LAND[PLAYER[P].pos].price+v*LAND[PLAYER[P].pos].vprice+b*LAND[PLAYER[P].pos].bprice+h*LAND[PLAYER[P].pos].hprice)/10);
                gotoxy(11*garosize/2+leftend-15, upend+serosize+2*cursor+5);
                printf("��");
                input=getch();
                switch(input)
                {
                case SPACE_BAR:
                    if(cursor==1 && v!=2)      v+=1;
                    if(cursor==2 && b!=1)      b+=1;
                    if(cursor==3 && h!=1)      h+=1;
                    break;
                case DEL:
                    if(cursor==1 && v!=0)      v-=1;
                    if(cursor==2 && b!=0)      b-=1;
                    if(cursor==3 && h!=0)      h-=1;
                    break;
                case ENTER:
					gotoxy(11*garosize/2+leftend-15, upend+serosize+2*cursor+5); printf("  ");
                    cost+=v*LAND[PLAYER[P].pos].vprice+b*LAND[PLAYER[P].pos].bprice+h*LAND[PLAYER[P].pos].hprice;
                    a=1;
                    break;
                case ESC:
                    v=0; b=0; h=0; cost=0; LAND[PLAYER[P].pos].landerase();
                    a=1;
                    gotoxy(11*garosize/2+leftend-15, upend+serosize+2*cursor+5); printf("  ");
                    gotoxy(11*garosize/2+leftend-17, upend+serosize+3); printf("                                  ");
                    gotoxy(11*garosize/2+leftend-12, upend+serosize+4); printf("                              "); 
                    gotoxy(11*garosize/2+leftend-25, upend+serosize+5); printf("                                                       ");
                    for(i=1; i<=7; i++)
                    {
                        gotoxy(11*garosize/2+leftend-11, i+11);
                        printf("            ");
                    }
                    gotoxy(11*garosize/2+leftend+11, upend+serosize+11); printf("                  ");
                    gotoxy(11*garosize/2+leftend+11, upend+serosize+12); printf("                  ");
                    gotoxy(11*garosize/2+leftend+11, upend+serosize+13); printf("                              ");
                    break;
                case UP:
                    if(cursor!=1)
                    {
                    gotoxy(11*garosize/2+leftend-15, upend+serosize+2*cursor+5); printf("  ");
                    cursor-=1;
                    }
                    break;
                case DOWN:
                    if(cursor!=3)
                    {
                        gotoxy(11*garosize/2+leftend-15, upend+serosize+2*cursor+5); printf("  ");          
                        cursor+=1;
                    }
                    break;  
                } 
                if(a==1)
                break;             
            }
            gotoxy(11*garosize/2+leftend-12, upend+serosize+7); printf("                     ");
            gotoxy(11*garosize/2+leftend-12, upend+serosize+9); printf("                     ");
            gotoxy(11*garosize/2+leftend-12, upend+serosize+11); printf("                     ");
			gotoxy(11*garosize/2+leftend-12, upend+serosize+13); printf("                         ");
			if(cost==0) return;
            if(pay(P, cost, 1))
			{
				LAND[PLAYER[P].pos].v=v; LAND[PLAYER[P].pos].b=b; LAND[PLAYER[P].pos].h=h; LAND[PLAYER[P].pos].owner=P;
				LAND[PLAYER[P].pos].fee=fee(LAND[PLAYER[P].pos]);
				LAND[PLAYER[P].pos].landshow();
			}
        }                   
    }
	else if(landatt==SP && LAND[PLAYER[P].pos].owner==0)
    {
        WHITE;
        gotoxy(11*garosize/2+leftend-3, upend+serosize+7);
        printf("1. ����");
        gotoxy(11*garosize/2+leftend-3, upend+serosize+9); 
        printf("2. �н�"); 
        while(1)
        {
            gotoxy(11*garosize/2+leftend-7, upend+serosize+2*cursor+5);
            printf("��");
            input=getch();
            switch(input)
            {
            case ENTER:
				gotoxy(11*garosize/2+leftend-7, upend+serosize+2*cursor+5); printf("  ");
				LAND[PLAYER[P].pos].fee=fee(LAND[PLAYER[P].pos]);
                a=1;
                break;
            case UP:            
                if(cursor!=1)
                {
                    gotoxy(11*garosize/2+leftend-7, upend+serosize+2*cursor+5); printf("  ");
                    cursor-=1;
                }
                break;
            case DOWN:
                if(cursor!=2)
                {
                    gotoxy(11*garosize/2+leftend-7, upend+serosize+2*cursor+5); printf("  ");          
                    cursor+=1;
                }
                break;
            }
            if(a==1)   break;
        }
        a=0;
        gotoxy(11*garosize/2+leftend-4, upend+serosize+7); printf("       ");
        gotoxy(11*garosize/2+leftend-4, upend+serosize+9); printf("       ");
        gotoxy(11*garosize/2+leftend-7, upend+serosize+2*cursor+5); printf("  ");
        if(cursor==1)
        {
            cost=LAND[PLAYER[P].pos].price;
            pay(P, cost, 1);
            LAND[PLAYER[P].pos].owner=P;
			LAND[PLAYER[P].pos].landshow();
        }
	}
    else if((landatt==NM || landatt==SP) && LAND[PLAYER[P].pos].owner!=P && LAND[PLAYER[P].pos].owner!=0)
    {
		if(LAND[PLAYER[P].pos].owner==1)	RED; if(LAND[PLAYER[P].pos].owner==2)	BLUE;   
        if(LAND[PLAYER[P].pos].owner==3)	BLACK;   if(LAND[PLAYER[P].pos].owner==4)	YELLOW;
        gotoxy(11*garosize/2+leftend-16, upend+serosize+2); printf("player%d : ����", LAND[PLAYER[P].pos].owner);
        pay(P, LAND[PLAYER[P].pos].fee, 0);
        receive(LAND[PLAYER[P].pos].owner, LAND[PLAYER[P].pos].fee);
		gotoxy(11*garosize/2+leftend-16, upend+serosize+2); printf("                                    ");
    } 
	else if(landatt==GK)
	{
		gkget(P, gk[30]);
		if(gk[30]!=3 && gk[30]!=13 && gk[30]!=26)
		{
			gk[currentcard]=gk[30];
		}
		for(i=30; i>=1; i--)
		{
			gk[i]=gk[i-1];
		}
		gk[currentcard]=0;
	}
    else if(PLAYER[P].pos==11) //���ε�
    {
        if(PLAYER[P].muin==0)  PLAYER[P].muin=3;
    }
	else if(PLAYER[P].pos==39) //��ȸ������� ����ó
	{
		WHITE;
		gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("��ȸ������� 15������ ������");
		pay(P, 150, 0);
		gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("                                  ");
		fund+=150;
		LAND[21].landshow();
	}
	else if(PLAYER[P].pos==21 && fund!=0) //��ȸ�������
	{
		WHITE;
		gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
		printf("��ȸ������� %d������ �޾ҽ��ϴ�", fund/10);
		fund=0;
		receive(P, fund);
		getch();
		gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
		printf("                               ", fund/10);
	}
	else if(PLAYER[P].pos==31) //�ݷ����ȣ
	{
		WHITE;
		gotoxy(leftend+5*garosize-8, upend+5*serosize+4); printf("���ּ� ž�� Y or N(��� 20����)");
		input=getch();
		gotoxy(leftend+5*garosize-8, upend+5*serosize+4); printf("                                  ");
		while(1)
		{
			switch(input)
			{
			case 'y':
			case 'Y':
				a=1;
				break;
			case 'n':
			case 'N':
				a=2;
				break;
			}
			if(a==1 || a==2)	break;
		}
		if(a==1)
		{
			if(pay(P, 200, 1))
			{
				gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("�������������� ���ϴ�");
				while(getch()!=ENTER)	i=1;
				gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("                     ");
				PLAYER[P].playererase();
				PLAYER[P].pos=0;
				PLAYER[P].posinit(); PLAYER[P].playershow();
			}
		}
	}
	else if(PLAYER[P].pos==0)
	{
		pos=spacetrip(P);
		PLAYER[P].playererase();
		PLAYER[P].pos=pos;
		PLAYER[P].posinit(); PLAYER[P].playershow();
		if(pos==1)	receive(P, 200);
		if(LAND[pos].att==GK)	
		{
			gkget(P, gk[30]);
			if(gk[30]!=3 && gk[30]!=13 && gk[30]!=26)
			{
				gk[currentcard]=gk[30];
			}
			for(i=30; i>=1; i--)
			{
				gk[i]=gk[i-1];
			}
			gk[currentcard]=0;
		}
		if(pos==21 && fund!=0) //��ȸ�������
		{
			WHITE;
			gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
			printf("��ȸ������� %d������ �޾ҽ��ϴ�", fund/10);
			fund=0;
			receive(P, fund);
			getch();
			gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
			printf("                               ", fund/10);
		}
		 if(PLAYER[P].pos==11) //���ε�
		{
			if(PLAYER[P].muin==0)  PLAYER[P].muin=3;
		}
	}
}              
int pay(int P, int price, int escapable)
{
    int cursor=1;
    int a=0;
    int input;
    int charge=0;
    int remain=0;
    int bill[8]={0};
    int i;
	bool payagain=false;

	do{
		cursor=1;
		a=0;
		WHITE;
		gotoxy(11*garosize/2+leftend-25, upend+serosize+5);
		printf("                                                        ");
		gotoxy(11*garosize/2+leftend-17, upend+serosize+3);
		printf("   ������ ȭ�� �����ϼ���.   "); 
		gotoxy(11*garosize/2+leftend-12, upend+serosize+4);
		if(price%10==0)
		{
			printf("�����ؾ��� �� : %d����", price/10);
		}
		else
		{
			printf("�����ؾ��� �� : %d�� %dõ��", price/10, price-10*(price/10));
		} 
		if(PLAYER[P].total<price)
		{
			gotoxy(11*garosize/2+leftend-17, upend+serosize+3);
			printf("                                                  ");
			gotoxy(11*garosize/2+leftend-6, upend+serosize+5);
			printf("���� ���ڶ��ϴ�.");
			gotoxy(11*garosize/2+leftend-1, upend+serosize+7);
			printf("1. �ȱ�");
			gotoxy(11*garosize/2+leftend-1, upend+serosize+9);
			printf("2. �Ļ�");
			if(escapable==1)
			{
				gotoxy(11*garosize/2+leftend-1, upend+serosize+11);
				printf("3. ������");
			}

			while(1)
			{
				WHITE;
				gotoxy(11*garosize/2+leftend-4, upend+serosize+2*cursor+5);
				printf("��");
				input=getch();
				switch(input)
				{
				case UP:
					if(cursor!=1)
					{
						gotoxy(11*garosize/2+leftend-4, upend+serosize+2*cursor+5); printf("  ");
						cursor-=1;
					}
					break;
				case DOWN:
					if(cursor!=2+escapable)
					{
						gotoxy(11*garosize/2+leftend-4, upend+serosize+2*cursor+5); printf("  ");          
						cursor+=1;
					}
					break;
				case ENTER:
					a=1;
					gotoxy(11*garosize/2+leftend-4, upend+serosize+2*cursor+5); printf("  ");
					if(cursor==2)
					{
						gotoxy(leftend+5*garosize-5, upend+5*serosize+3);
						if(P==1)	RED;     if(P==2)	BLUE;   
						if(P==3)	BLACK;   if(P==4)	YELLOW;
						printf("player%d�� �Ļ��߽��ϴ�.", P);
						getch();
						gotoxy(leftend+5*garosize-5, upend+5*serosize+3);  printf("                                      ");
						gotoxy(11*garosize/2+leftend-17, upend+serosize+3); printf("                                          ");
						gotoxy(11*garosize/2+leftend-12, upend+serosize+4); printf("                                   "); 
						gotoxy(11*garosize/2+leftend-25, upend+serosize+5); printf("                                   ");
						gotoxy(11*garosize/2+leftend-1, upend+serosize+7);  printf("            ");
						gotoxy(11*garosize/2+leftend-1, upend+serosize+9);  printf("            ");
						gotoxy(11*garosize/2+leftend-1, upend+serosize+11); printf("            ");
						for(i=1; i<=7; i++)
						{
							PLAYER[P].money[i]=0;
						}
						PLAYER[P].moneyinit();
						PLAYER[P].moneyshow();
						PLAYER[P].playererase();
						PLAYER[P].pos=0;
						PLAYER[P].posinit();
						PLAYER[P].pasan=1;
						for(i=1; i<=41; i++)
						{
							PLAYER[P].ter[i]=0;
							if(LAND[i].owner==P)
							{
								LAND[i].owner=0;
								LAND[i].landerase();
								LAND[i].landshow();
							}
						}
						gotoxy(10*garosize+leftend+13, 3+9*P); printf("             ");
						for(i=1; i<=9; i++)
						{
							gotoxy(10*garosize+leftend+24, 2+i+9*P);
							printf("                    ");
						}
						return 0;
					}
					else if(cursor==3)	
					{
						gotoxy(11*garosize/2+leftend-17, upend+serosize+3); printf("                                        ");
						gotoxy(11*garosize/2+leftend-12, upend+serosize+4); printf("                                   "); 
						gotoxy(11*garosize/2+leftend-25, upend+serosize+5); printf("                                   ");
						gotoxy(11*garosize/2+leftend-1, upend+serosize+7);  printf("            ");
						gotoxy(11*garosize/2+leftend-1, upend+serosize+9);  printf("            ");
						gotoxy(11*garosize/2+leftend-1, upend+serosize+11); printf("            ");
						return 0;
					}
					break;
				}
				if(a==1)
					break;
			}
			if(cursor==1)
			{
				gotoxy(11*garosize/2+leftend-17, upend+serosize+3); printf("                                        ");
				gotoxy(11*garosize/2+leftend-12, upend+serosize+4); printf("                                   "); 
				gotoxy(11*garosize/2+leftend-25, upend+serosize+5); printf("                                   ");
				gotoxy(11*garosize/2+leftend-1, upend+serosize+7);  printf("            ");
				gotoxy(11*garosize/2+leftend-1, upend+serosize+9);  printf("            ");
				gotoxy(11*garosize/2+leftend-1, upend+serosize+11); printf("            ");
				sell(P);
			}
			payagain=true;
		}
		else payagain=false;
	}while(payagain);
      
    gotoxy(11*garosize/2+leftend-25, upend+serosize+5);
    printf("����=spacebar ���=delete ����=enter ");
	if(escapable==1)	printf("������=esc"); 
	if(escapable==0 && PLAYER[P].ude>0)
	{
		gotoxy(11*garosize/2+leftend-6, upend+serosize+11); YELLOW; printf("���� ���");
		WHITE;
	}
    for(i=1; i<=7; i++)
    {
        gotoxy(11*garosize/2+leftend-11, i+11);
		if(i<=2) printf("%d����  0�� / %d��", f(i)/10, PLAYER[P].money[i]);
        else if(i<=5) printf("%d����   0�� / %d��", f(i)/10, PLAYER[P].money[i]);
        if(i>=6) printf("%dõ��   0�� / %d��", f(i), PLAYER[P].money[i]);
	}
	gotoxy(11*garosize/2+leftend-11, upend+serosize+15); printf("�հ� : 0�� 0õ��");
    while(1)
    {
        WHITE;
        gotoxy(11*garosize/2+leftend-14, upend+serosize+cursor+6);  printf("��");
        input=getch();
        switch(input)
        {
        case SPACE_BAR:
            if(PLAYER[P].money[cursor]>0)
            {
                charge+=f(cursor);
                bill[cursor]+=1;
                PLAYER[P].money[cursor]-=1;
                PLAYER[P].moneyshow();
                WHITE;
                gotoxy(11*garosize/2+leftend-11, upend+serosize+cursor+6);
				if(cursor<=2) printf("%d����  %d�� / %d��", f(cursor)/10, bill[cursor], PLAYER[P].money[cursor]);
                else if(cursor<=5) printf("%d����   %d�� / %d��", f(cursor)/10, bill[cursor], PLAYER[P].money[cursor]);
                if(cursor>=6) printf("%dõ��   %d�� / %d��", f(cursor), bill[cursor], PLAYER[P].money[cursor]);
				gotoxy(11*garosize/2+leftend-11, upend+serosize+15); printf("�հ� : %d�� %dõ��", charge/10, charge-10*(charge/10));
            }
            else
            {
                gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("������ ȭ�� �����մϴ�.");
                getch();
                gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("                         ");
            }
            break;
        case DEL:
            if(bill[cursor]>0)
            {
                charge-=f(cursor);
                bill[cursor]-=1;
                PLAYER[P].money[cursor]+=1;
                PLAYER[P].moneyshow();
                WHITE;
                gotoxy(11*garosize/2+leftend-11, upend+serosize+cursor+6);
				if(cursor<=2) printf("%d����  %d�� / %d��", f(cursor)/10, bill[cursor], PLAYER[P].money[cursor]);
                else if(cursor<=5) printf("%d����   %d�� / %d��", f(cursor)/10, bill[cursor], PLAYER[P].money[cursor]);
                if(cursor>=6) printf("%dõ��   %d�� / %d��", f(cursor), bill[cursor], PLAYER[P].money[cursor]); 
				gotoxy(11*garosize/2+leftend-11, upend+serosize+15); printf("�հ� : %d�� %dõ��", charge/10, charge-10*(charge/10));
            }
            else
            {
                gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("����� ȭ�� �����ϴ�.");
                while(getch()!=ENTER) i=1;
                gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("                         ");
            }
            break;     
        case ENTER:
			if(cursor>0)
			{
				if(charge<price)
				{
					gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
					printf("���� ���ڶ��ϴ�.");
					getch();
					gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
					printf("                ");
				}
				else
				{
					remain=charge-price;

					gotoxy(11*garosize/2+leftend+11, upend+serosize+11);
					if(price%10==0) printf("���� : %d����", price/10);
					else printf("���� : %d�� %dõ��", price/10, price-10*(price/10)); 

					gotoxy(11*garosize/2+leftend+11, upend+serosize+12);
					if(price%10==0) printf("���Ҿ� : %d����", charge/10);
					else printf("���Ҿ� : %d�� %dõ��", charge/10, charge-10*(charge/10));
                
					gotoxy(11*garosize/2+leftend+11, upend+serosize+13);
					if(price%10==0)  printf("�ܵ� : %d����", remain/10);
					else printf("�ܵ� : %d�� %dõ��", remain/10, remain-10*(remain/10));

					gotoxy(11*garosize/2+leftend-14, upend+serosize+cursor+6); printf("  ");
					while(getch()!=ENTER)   i=1;  
					receive(P, remain);
					PLAYER[P].moneyinit();
					PLAYER[P].ter[PLAYER[P].pos]=1;
					a=1;
				} 
			}
			else
			{
				PLAYER[P].ude-=1;
				gotoxy(11*garosize/2+leftend-17, upend+serosize+3); printf("                                          ");
				gotoxy(11*garosize/2+leftend-12, upend+serosize+4); printf("                                    "); 
				gotoxy(11*garosize/2+leftend-25, upend+serosize+5); printf("                                                       ");
				for(i=1; i<=9; i++)
				{
					gotoxy(11*garosize/2+leftend-11, upend+serosize+i+6);
					printf("                      ");
				}
				gotoxy(11*garosize/2+leftend+11, upend+serosize+11);
				printf("                   ");
				gotoxy(11*garosize/2+leftend+11, upend+serosize+12);
				printf("                   ");
				gotoxy(11*garosize/2+leftend+11, upend+serosize+13);
				printf("                   "); 
				gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
				printf("������ ����ϼ̽��ϴ�.");
				getch();
				gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
				printf("                        ");
				gk[currentcard]=13;
				currentcard-=1;
			}
            break;
        case ESC:
			if(escapable==1)
			{
				a=2;
				gotoxy(11*garosize/2+leftend-14, upend+serosize+cursor+6); printf("  ");
				for(i=1; i<=7; i++)
				{
						PLAYER[P].money[i]+=bill[i];
				}
				PLAYER[P].moneyinit(); PLAYER[P].moneyshow(); 
			}
            break;
        case UP:            
            if(cursor!=1-((PLAYER[P].ude>0) && escapable==0))
            {
                gotoxy(11*garosize/2+leftend-14, cursor+11); printf("  ");
                cursor-=1;
            }
            break;
        case DOWN:
            if(cursor!=7)
            {
                gotoxy(11*garosize/2+leftend-14, cursor+11); printf("  ");          
                cursor+=1;
            }
            break;
        }
        if(a==1 || a==2)   break;
                      
    }
    gotoxy(11*garosize/2+leftend-17, upend+serosize+3); printf("                                          ");
    gotoxy(11*garosize/2+leftend-12, upend+serosize+4); printf("                                    "); 
    gotoxy(11*garosize/2+leftend-25, upend+serosize+5); printf("                                                       ");
    for(i=1; i<=9; i++)
    {
        gotoxy(11*garosize/2+leftend-11, upend+serosize+i+6);
        printf("                      ");
    }
    gotoxy(11*garosize/2+leftend+11, upend+serosize+11);
    printf("                   ");
    gotoxy(11*garosize/2+leftend+11, upend+serosize+12);
    printf("                   ");
    gotoxy(11*garosize/2+leftend+11, upend+serosize+13);
    printf("                   "); 
	if(a==1) return 1;
	else return 0;
}      
int f(int a)
{
    switch(a)
    {
    case 1:
         return 500;
    case 2:
         return 100;
    case 3: 
         return 50;
    case 4:
         return 20;
    case 5:
         return 10;
    case 6:
         return 5;
    case 7:
         return 1;
    }
}
void receive(int P, int remain)
{
    PLAYER[P].money[1]+=remain/500;
    remain-=500*(remain/500);
    PLAYER[P].money[2]+=remain/100;
    remain-=100*(remain/100);
    PLAYER[P].money[3]+=remain/50;
    remain-=50*(remain/50);
    PLAYER[P].money[4]+=remain/20;
    remain-=20*(remain/20);
    PLAYER[P].money[5]+=remain/10;
    remain-=10*(remain/10);
    PLAYER[P].money[6]+=remain/5;
    remain-=5*(remain/5);
    PLAYER[P].money[7]+=remain;
    PLAYER[P].moneyinit();
    PLAYER[P].moneyshow();
}
void sell(int P)
{
	int i, j;
	int a=0;
	int input;
	int cursor=1;
	int landnum=0;
	int landprice[41]={0};
	int th[41]={0};

	if(P==1)	RED;    if(P==2)	BLUE;
    if(P==3)	BLACK;  if(P==4)	YELLOW;
	for(i=1; i<=40; i++)
	{
		if(LAND[i].owner==P)
		{
			gotoxy(11*garosize/2+leftend+13, upend+serosize+5+landnum);
			printf("%s", LAND[i].name);
			landnum+=1;

			landprice[landnum]=LAND[i].price + LAND[i].v*LAND[i].vprice + LAND[i].b*LAND[i].bprice + LAND[i].h*LAND[i].hprice;
			printf(" : %d����", landprice[landnum]/10);
			th[landnum]=i;
			
		}
	}
	WHITE;
	gotoxy(11*garosize/2+leftend+14, upend+serosize+5+landnum);
	printf("�ȱ�=enter  ������=esc");
	while(1)
	{
		WHITE;
		gotoxy(11*garosize/2+leftend+11, upend+serosize+4+cursor);
		printf("��");
		input=getch();
		switch(input)
		{
		case UP:            
			if(cursor!=1)
			{
				gotoxy(11*garosize/2+leftend+11, upend+serosize+4+cursor); printf("  ");
				cursor-=1;
			}
			break;
		case DOWN:
			if(cursor!=landnum)
			{
				gotoxy(11*garosize/2+leftend+11, upend+serosize+4+cursor); printf("  ");          
				cursor+=1;
			}
			break;
		case ENTER:
			LAND[th[cursor]].landerase();
			LAND[th[cursor]].landshow();
			receive(P, landprice[cursor]);
			gotoxy(11*garosize/2+leftend+13, upend+serosize+4+cursor);
			printf("                   ");
			landprice[cursor]=0;
			break;
		case ESC:
			a=1;
			gotoxy(11*garosize/2+leftend+11, upend+serosize+4+cursor); printf("  ");
			for(i=0; i<=landnum; i++)
			{
				gotoxy(11*garosize/2+leftend+11, upend+serosize+5+i);
				printf("                          ");
			}
			break;
		}
		if(a==1) break;
	}

} 
void gkget(int P, int num)
{
	int i;
	int v=0, b=0, h=0;  //�ǹ������� ���� ���
	int fee=0;          //�ǹ������� ���� ���
	int landprice=0;    //�ݾ״����
	int landpricemax=0, maxland=0; //�ݾ״����
	YELLOW;
	gkboxshow();
	switch(num)
	{
	case 1:
        gkboxshow();
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("������ ����");
		gotoxy(11*garosize/2+leftend-14, upend+serosize+7); printf("�������� �ǰ� ������ �޾ҽ��ϴ�.");
		gotoxy(11*garosize/2+leftend-12, upend+serosize+9); printf("������ 5������ ���࿡ ���ÿ�");
		while(getch()!=ENTER)	i=1;
		gkerase();
		pay(P, 50, 0);
		break;
	case 2:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("���� ��÷");
		gotoxy(11*garosize/2+leftend-9, upend+serosize+7); printf("���ǿ� ��÷�Ǽ̽��ϴ�.");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("��÷�� 20����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		receive(P, 200);
		break;
	case 3:
		gotoxy(11*garosize/2+leftend-11, upend+serosize+5); printf("���ε� Ż��� Ư�� ������");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+7); printf("���ε����� Ż���� �� �ֽ��ϴ�.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		PLAYER[P].mujeon=1;
		PLAYER[P].moneyshow();
		break;
	case 4:
		gotoxy(11*garosize/2+leftend-6, upend+serosize+5); printf("���ε��� ���ÿ�");
		gotoxy(11*garosize/2+leftend-7, upend+serosize+7); printf("��ǳ�� �������ϴ�.");
		gotoxy(11*garosize/2+leftend-17, upend+serosize+9); printf("������� ���İ��� ������ �� �޽��ϴ�.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		PLAYER[P].pos=11;
		PLAYER[P].muin=3;
		PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
		break;
	case 5:
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("��Ƽ �ʴ��");
		gotoxy(11*garosize/2+leftend-7, upend+serosize+7); printf("����ڶ��� �Ͻÿ�.");
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("���緮�� ����� �޽��ϴ�.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		break;
	case 6:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("���� ����");
		gotoxy(11*garosize/2+leftend-7, upend+serosize+7); printf("���ֵ��� ���ʽÿ�");
		gotoxy(11*garosize/2+leftend-12, upend+serosize+9); printf("���ֵ��� ����� ���� -30����");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+11); printf("������� ���İ� �� ���� +20����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		while(PLAYER[P].pos!=6)
		{
			PLAYER[P].pos+=1;
			PLAYER[P].pos%=41;
			if(PLAYER[P].pos==0)
			{
				PLAYER[P].pos+=1;
				receive(P, 200);
			}
			PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
			Sleep(50);
		}
		if(LAND[6].owner!=P)
		{
			pay(P, 300, 0);
			if(LAND[6].owner!=0)
			{
				receive(LAND[6].owner, 300);
			}
		}
		break;
	case 7:
		gotoxy(11*garosize/2+leftend-5, upend+serosize+5); printf("���� ���� ����");
		gotoxy(11*garosize/2+leftend-9, upend+serosize+7); printf("���ӿ����� �Ͽ����ϴ�.");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("5������ ���ÿ�");
		while(getch()!=ENTER)	i=1;
		gkerase();
		pay(P, 50, 0);
		break;
	case 8:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("�ؿ� ����");
		gotoxy(11*garosize/2+leftend-8, upend+serosize+7); printf("�б� ��ϱ��� ���ÿ�.");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("��ϱ� 10����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		pay(P, 100, 0);
		break;
	case 9:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("���� ����");
		gotoxy(11*garosize/2+leftend-11, upend+serosize+7); printf("���Ŀ��� 5������ �����ÿ�.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		receive(P, 50);
		break;
	case 10://?
	case 11:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("��� ����");
		gotoxy(11*garosize/2+leftend-9, upend+serosize+7); printf("��������� �ٷ� ���ÿ�.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		while(PLAYER[P].pos!=1)
		{
			PLAYER[P].pos+=1;
			PLAYER[P].pos%=41;
			if(PLAYER[P].pos==0)
			{
				PLAYER[P].pos+=1;
				receive(P, 200);
			}
			PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
			Sleep(50);
		}
		break;
	case 12:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("��    ��");
		gotoxy(11*garosize/2+leftend-16, upend+serosize+7); printf("�ڵ��� ���ֿ��� è�ǿ��� �Ǿ����ϴ�.");
		gotoxy(11*garosize/2+leftend-4, upend+serosize+9); printf("��� 10����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		receive(P, 100);
		break;
	case 13:
	case 26:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("�� �� ��");
		gotoxy(11*garosize/2+leftend-16, upend+serosize+7); printf("����Ḧ �� �� �������� �� �ֽ��ϴ�.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		PLAYER[P].ude+=1; PLAYER[P].moneyshow();
		break;
	case 14:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("�װ� ����");
		gotoxy(11*garosize/2+leftend-17, upend+serosize+7); printf("���忩���⸦ Ÿ�� Ÿ�����̷� ���ÿ�");
		gotoxy(11*garosize/2+leftend-12, upend+serosize+9); printf("���忡 ���Ƿ� ���� -30����");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+11); printf("������� ���İ� �� ���� +20����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		while(PLAYER[P].pos!=16)
		{
			PLAYER[P].pos+=1;
			PLAYER[P].pos%=41;
			if(PLAYER[P].pos==0)
			{
				PLAYER[P].pos+=1;
				receive(P, 200);
			}
			PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
			Sleep(50);
		}
		if(LAND[16].owner!=P)
		{
			pay(P, 300, 0);
			if(LAND[16].owner!=0)
			{
				receive(LAND[16].owner, 300);
			}
		}
		while(PLAYER[P].pos!=2)
		{
			PLAYER[P].pos+=1;
			PLAYER[P].pos%=41;
			if(PLAYER[P].pos==0)
			{
				PLAYER[P].pos+=1;
				receive(P, 200);
			}
			PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
			Sleep(50);
		}
		choose(P, NM);
		break;
	case 15:
		gotoxy(11*garosize/2+leftend-6, upend+serosize+5); printf("�ǹ� ������ ����");
		gotoxy(11*garosize/2+leftend-12, upend+serosize+7); printf("��� �ǹ��� �����Ͽ��� �մϴ�.");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("ȣ�� : 10����");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+10); printf("���� : 6����");
        gotoxy(11*garosize/2+leftend-5, upend+serosize+11); printf("���� : 3����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		for(i=1; i<=40; i++)
		{
			if(LAND[i].owner==P)
			{
				v+=LAND[i].v; b+=LAND[i].b; h+=LAND[i].h;
			}
		}
		fee=100*h + 60*b + 30*v;
		if(fee!=0)	pay(P,fee, 0);
		else
		{
			gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("�ǹ��� �����ϴ�.");
		}
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("                     ");
		break;
	case 16:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("�� �� ��");
		gotoxy(11*garosize/2+leftend-10, upend+serosize+7); printf("����� ���࿡ �����ϼ���");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("ȣ�� : 5����");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+10); printf("���� : 3����");
        gotoxy(11*garosize/2+leftend-5, upend+serosize+11); printf("���� : 1����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		for(i=1; i<=40; i++)
		{
			if(LAND[i].owner==P)
			{
				v+=LAND[i].v; b+=LAND[i].b; h+=LAND[i].h;
			}
		}
		fee=50*h + 30*b + 10*v;
		if(fee!=0)	pay(P,fee, 0);
		else
		{
			gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("�ǹ��� �����ϴ�.");
		}
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("                     ");
		break;
	case 17:
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("������ ����");
		gotoxy(11*garosize/2+leftend-18, upend+serosize+7); printf("�� �����ں���ȣ�� Ÿ�� ȫ������ ���ÿ�");
		gotoxy(11*garosize/2+leftend-17, upend+serosize+9); printf("�� �����ں���ȣ�� ���Ƿ� ���� -25����");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+11); printf("������� ���İ� �� ���� +20����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		while(PLAYER[P].pos!=29)
		{
			PLAYER[P].pos+=1;
			PLAYER[P].pos%=41;
			if(PLAYER[P].pos==0)
			{
				PLAYER[P].pos+=1;
				receive(P, 200);
			}
			PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
			Sleep(50);
		}
		if(LAND[29].owner!=P)
		{
			pay(P, 250, 0);
			if(LAND[29].owner!=0)
			{
				receive(LAND[29].owner, 250);
			}
		}
		while(PLAYER[P].pos!=6)
		{
			PLAYER[P].pos+=1;
			PLAYER[P].pos%=41;
			if(PLAYER[P].pos==0)
			{
				PLAYER[P].pos+=1;
				receive(P, 200);
			}
			PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
			Sleep(50);
		}
		choose(P, NM);
		break;
	case 18: 
	case 19:
		gotoxy(11*garosize/2+leftend-7, upend+serosize+5); printf("������ �����մϴ�");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+7); printf("��ο��� ���� ���ϱ��� ��������");
		gotoxy(11*garosize/2+leftend+6, upend+serosize+9); printf("���ϱ� 1õ��");
		while(getch()!=ENTER)	i=1;
		gkerase();
		for(i=1; i<=pnum; i++)
		{
			if(PLAYER[i].pasan==0 && i!=P && PLAYER[i].money[7]>0)
			{
				PLAYER[i].money[7]-=1;
				PLAYER[P].money[7]+=1;
				PLAYER[i].moneyinit(); PLAYER[i].moneyshow();
			}
		}
		PLAYER[P].moneyinit(); PLAYER[P].moneyshow();
		break;
	case 20:
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("���б� ����");
		gotoxy(11*garosize/2+leftend-10, upend+serosize+7); printf("���б� 10������ �����ÿ�.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		receive(P, 100);
		break;
	case 21:
		gotoxy(11*garosize/2+leftend-7, upend+serosize+5); printf("���� ���� �ҵ漼");
		gotoxy(11*garosize/2+leftend-10, upend+serosize+7); printf("���ռҵ漼�� �����Ͻÿ�.");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("ȣ�� : 15����");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+10); printf("���� : 10����");
        gotoxy(11*garosize/2+leftend-5, upend+serosize+11); printf("���� : 3����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		for(i=1; i<=40; i++)
		{
			if(LAND[i].owner==P)
			{
				v+=LAND[i].v; b+=LAND[i].b; h+=LAND[i].h;
			}
		}
		fee=150*h + 100*b + 30*v;
		if(fee!=0)	pay(P,fee, 0);
		else
		{
			gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("�ǹ��� �����ϴ�.");
		}
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("                     ");
		break;
	case 22:
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("�뺧 ��ȭ�� ����");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+7); printf("����� ������ȭ�� ���� �����Ͽ�");
		gotoxy(11*garosize/2+leftend-11, upend+serosize+9); printf("��� 30������ ��� �޽��ϴ�.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		receive(P, 300);
		break;
	case 23:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("���� ����");
		gotoxy(11*garosize/2+leftend-6, upend+serosize+7); printf("����� ���ʽÿ�");
		gotoxy(11*garosize/2+leftend-12, upend+serosize+9); printf("���￡ ����� ���� -200����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		while(PLAYER[P].pos!=40)
		{
			PLAYER[P].pos+=1;
			PLAYER[P].pos%=41;
			if(PLAYER[P].pos==0)
			{
				PLAYER[P].pos+=1;
				receive(P, 200);
			}
			PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
			Sleep(50);
		}
		pay(P, 2000, 0);
		break;
	case 24:
	case 30:
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("�ݾ� �����");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+7); printf("����� �� �߿��� ���� ��� ����");
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("���࿡ �ݾ����� �Ľʽÿ�.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		for(i=1; i<=40; i++)
		{
			if(LAND[i].owner==P)
			{
				landprice=LAND[i].price + LAND[i].v*LAND[i].vprice + LAND[i].b*LAND[i].bprice + LAND[i].h*LAND[i].hprice;
				if(landprice>landpricemax)
				{
					landpricemax=landprice; maxland=i;
				}
			}
		}
		if(maxland!=0)
		{
			gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("%s��(��) %d������ �ȷȽ��ϴ�.", LAND[maxland].name, landprice/20);
			LAND[maxland].landerase();
			LAND[maxland].landshow();
			receive(P, landprice/2);
		}
		else
		{
			gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("�� ���� �����ϴ�.");
		}
		while(getch()!=ENTER) i=1;
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("                                      ");
		break;
	case 25:
		gotoxy(11*garosize/2+leftend-6, upend+serosize+5); printf("���� ���� ��û��");
		gotoxy(11*garosize/2+leftend-14, upend+serosize+7); printf("�����װ������� ��û���� �Խ��ϴ�.");
		gotoxy(11*garosize/2+leftend-11, upend+serosize+9); printf("�����̹Ƿ� ž�·�� �����ϴ�.");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+11); printf("������� ���İ� �� ���� +20����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		while(PLAYER[P].pos!=31)
		{
			PLAYER[P].pos+=1;
			PLAYER[P].pos%=41;
			if(PLAYER[P].pos==0)
			{
				PLAYER[P].pos+=1;
				receive(P, 200);
			}
			PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
			Sleep(50);
		}
		choose(P, CNR);
		break;
	case 27:
		gotoxy(11*garosize/2+leftend-6, upend+serosize+5); printf("���� ���� �ʴ��");
		gotoxy(11*garosize/2+leftend-9, upend+serosize+7); printf("�� ���� ���� ���ʽÿ�.");
		gotoxy(11*garosize/2+leftend-15, upend+serosize+9); printf("������� �����鼭 ������ ��������.");
		gotoxy(11*garosize/2+leftend-16, upend+serosize+11); printf("��������� �����鼭 ����� ��������");
		while(getch()!=ENTER)	i=1;
		gkerase();
		for(i=1; i<=39; i++)
		{
			PLAYER[P].pos+=1;
			PLAYER[P].pos%=40;
			if(PLAYER[P].pos==0)
			{
				PLAYER[P].pos+=1;
				receive(P, 200);
			}
			if(PLAYER[P].pos==21)
			{
				receive(P, fund);
				fund=0;
			}
			PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
			Sleep(50);
		}
		break;
	case 28:
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("�̻� ���ÿ�");
		gotoxy(11*garosize/2+leftend-8, upend+serosize+7); printf("�ڷ� ��ĭ �ű�ÿ�.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		PLAYER[P].pos-=2; //Ȳ�ݿ����� pos�� ������ 3 �̻��̱� ������ ������ �� �� ����
		PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
		break;
	case 29:
		gotoxy(11*garosize/2+leftend-7, upend+serosize+5); printf("��ȸ���� ��ݹ��");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+7); printf("��ȸ ���� ��� ����ó�� ���ÿ�.");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+9); printf("������� ���İ� �� ���� +20����");
		while(getch()!=ENTER)	i=1;
		gkerase();
		while(PLAYER[P].pos!=21)
		{
			PLAYER[P].pos+=1;
			PLAYER[P].pos%=41;
			if(PLAYER[P].pos==0)
			{
				PLAYER[P].pos+=1;
				receive(P, 200);
			}
			PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
			Sleep(50);
		}
		receive(P, fund);
		fund=0;
		break;
	}	
}
void gkboxshow(void)
{
	int i, j;
	YELLOW;
	for(i=1; i<=gkboxgarosize/2; i++)
    {
        gotoxy(11*garosize/2+leftend-gkboxgarosize/2+2*i-1, upend+serosize+3);
        printf("��");
        gotoxy(11*garosize/2+leftend-gkboxgarosize/2+2*i-1, upend+serosize+gkboxserosize+4);
        printf("��");
    }
    for(i=1; i<=gkboxserosize; i++)
    {      
        gotoxy(11*garosize/2+leftend-gkboxgarosize/2, upend+serosize+3+i);
        printf("��");
        gotoxy(11*garosize/2+leftend+gkboxgarosize/2, upend+serosize+3+i);
        printf("��");
    }
	gotoxy(11*garosize/2+leftend+gkboxgarosize/2-6, upend+serosize+gkboxserosize+3);
	printf("K.Y.S");
}
void gkerase(void)
{
	int i;
	for(i=1; i<=gkboxgarosize/2; i++)
    {
        gotoxy(11*garosize/2+leftend-gkboxgarosize/2+2*i-1, upend+serosize+3);
        printf("  ");
        gotoxy(11*garosize/2+leftend-gkboxgarosize/2+2*i-1, upend+serosize+gkboxserosize+4);
        printf("  ");
    }
    for(i=1; i<=gkboxserosize; i++)
    {      
        gotoxy(11*garosize/2+leftend-gkboxgarosize/2, upend+serosize+3+i);
        printf("  ");
        gotoxy(11*garosize/2+leftend+gkboxgarosize/2, upend+serosize+3+i);
        printf("  ");
    }
	gotoxy(11*garosize/2+leftend+gkboxgarosize/2-6, upend+serosize+gkboxserosize+3);
	printf("      ");
	gotoxy(11*garosize/2+leftend-gkboxgarosize/2, upend+serosize+5); printf("                                                        ");
	gotoxy(11*garosize/2+leftend-gkboxgarosize/2, upend+serosize+7); printf("                                                        ");
	gotoxy(11*garosize/2+leftend-gkboxgarosize/2, upend+serosize+9); printf("                                                        ");
	gotoxy(11*garosize/2+leftend-gkboxgarosize/2, upend+serosize+10); printf("                                                       ");
	gotoxy(11*garosize/2+leftend-gkboxgarosize/2, upend+serosize+11); printf("                                                       ");
}
int spacetrip(int P)
{
	int i;
	int input;
	int a=0;
	int pos=31;
	gotoxy(11*garosize/2+leftend-10, upend+serosize+6); printf("�� ���� ������ �ּ���");
	while(1)
	{
		LAND[pos].landboxshow(P);
		input=getch();
		LAND[pos].landboxshow(0);
		switch(input)
		{
		case DOWN:
			if((12<=pos && pos<=21) || (31<=pos && pos<=40))
			{
				if((pos-1)/10+1==2 || pos==21) pos-=1;
				if((pos-1)/10+1==4) pos+=1;
				if(pos>40) pos%=40;
			}
			break;
		case UP:
			if((11<=pos && pos<=20) || (32<=pos && pos<=40) || pos==1)
			{
				if((pos-1)/10+1==2) pos+=1;
				if((pos-1)/10+1==4 || pos==1) pos-=1;
				if(pos==0) pos=40;
			}
			break;
		case LEFT:
			if((1<=pos && pos<=10) || (22<=pos && pos<=31))
			{
				if((pos-1)/10+1==1) pos+=1;
				if((pos-1)/10+1==3 || pos==31) pos-=1;
			}
			break;
		case RIGHT:
			if((2<=pos && pos<=11) || (21<=pos && pos<=30))
			{
				if((pos-1)/10+1==1 || pos==11) pos-=1;
				if((pos-1)/10+1==3) pos+=1;
			}
			break;
		case ENTER:
			a=1;
			break;
		}
		if(a==1) break;
	}
	gotoxy(11*garosize/2+leftend-10, upend+serosize+6); printf("                         ");
	return pos;
}

void gotoxy(int x, int y)
{
	COORD KYS={x-1, y-1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), KYS);
}
void cursorview(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}
void setConSize ( int row, int col ) 
{
	char buf[256] = {0};
	sprintf ( buf, "mode con: lines=%d cols=%d", row, col );
	system ( buf );
}
int wherex(void)
{
     CONSOLE_SCREEN_BUFFER_INFO csb;
 
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csb);
     return (csb.dwCursorPosition.X)+1;
}
int wherey(void)
{
     CONSOLE_SCREEN_BUFFER_INFO csb;
 
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csb);
     return (csb.dwCursorPosition.Y)+1;
 }