/*
made by K.Y.S

오류 수정
//-우주정거장에서 돈 지불
-우주정거장 지워지면 재출력
-파산하거나 돈 지불하면 가끔씩 위에 뜨는 돈표
//-우주정거장에서 갔을 때 월급, 황금열쇠 등
//-반액대매출시 들어오는 돈

 인공지능 넣기
 자기 땅 걸리면 추가 기능
 2012/11/25

*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <string.h>

#define LIGHT_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x02a) // 연두
#define SKY SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x002b) //하늘색
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x002c) //빨간색
#define FLUORE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x002d) //형광
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x002e) //노란색
#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x002f) // 흰색 

#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0029) //파란색 
#define GOLD SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0026) //금색
#define BLACK SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0020) //검은색 
//0: 검정 1: 파랑 2: 초록 3:옥색 4: 빨강 5: 자주 6: 노랑 7: 흰색 8:회색 9:연한 파랑 

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

#define VILLA '^'     //별장
#define BUILDING '@'  //빌딩
#define HOTEL '&'     //호텔
#define PS playershape[0] //플레이어 출력할려고 만든거  

#define NM 1   //normal
#define GK 2   //golden key
#define SP 3   //special
#define CNR 4  //corner

#define garosize 10  //한 칸 가로 사이즈
#define serosize 4   //한 칸 세로 사이즈
#define leftend 1    //보드판의 왼쪽 끝
#define upend 1      //보드판의 오른쪽 끝
#define dicesize 18  //주사위 사이즈
#define gkboxgarosize 40  //황금열쇠 출력 박스 가로 사이즈
#define gkboxserosize 10  //황금열쇠 출력 박스 세로 사이즈


void gotoxy(int x, int y);
void cursorview(char show); //show가 0이면 안 보이게, 1이면 보이게 
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
	int fee; //통행료
	int price; //가격
	int vprice, bprice, hprice; //별장, 빌딩, 호텔 가격
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
			if(price>0)	printf("%d만", price/10);

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
			if(price>0)	printf("%d만", price/10);

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
			if(price>0)	printf("%d만", price/10);

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
			if(price>0)	printf("%d만", price/10);

			gotoxy(garosize*10+leftend+6, upend+3+serosize*pos2);
			for(i=1; i<=v; i++)	printf("%c", VILLA);
			for(i=1; i<=b; i++) printf("%c", BUILDING);
			for(i=1; i<=h; i++) printf("%c", HOTEL);
		}
		if(pos==21) //사회 복지기금
		{
			gotoxy(leftend+6+garosize*pos2, upend+2);
			if(fund>0)	printf("%d만", fund/10);
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
				gotoxy(garosize*(10-pos2)+leftend, serosize*10+i+upend+1); printf("｜");
				gotoxy(garosize*(10-pos2)+leftend+garosize, serosize*10+i+upend+1); printf("｜");
			}
			for(i=0; i<=4; i++)
			{
				gotoxy(garosize*(10-pos2)+2*i+leftend+1, serosize*10+upend); printf("―");
				gotoxy(garosize*(10-pos2)+2*i+leftend+1, serosize*11+upend); printf("―");
			}
		}
		if(pos1==3)
		{
			for(i=0; i<=2; i++)
			{
				gotoxy(garosize*pos2+leftend, i+upend+1); printf("｜");
				gotoxy(garosize*pos2+leftend+garosize, i+upend+1); printf("｜");
			}
			for(i=0; i<=4; i++)
			{
				gotoxy(garosize*pos2+2*i+leftend+1, upend); printf("―");
				gotoxy(garosize*pos2+2*i+leftend+1, upend+serosize); printf("―");
			}
		}
		if(pos1==2)
		{
			for(i=0; i<=2; i++)
			{
				gotoxy(leftend, serosize*(10-pos2)+i+upend+1); printf("｜");
				gotoxy(leftend+garosize, serosize*(10-pos2)+i+upend+1); printf("｜");
			}
			for(i=0; i<=4; i++)
			{
				gotoxy(leftend+1+2*i, serosize*(10-pos2)+upend); printf("―");
				gotoxy(leftend+1+2*i, serosize*(10-pos2)+upend+serosize); printf("―");
			}
		}
		if(pos1==4)
		{
			for(i=0; i<=2; i++)
			{
				gotoxy(garosize*10+leftend, serosize*pos2+i+upend+1); printf("｜");
				gotoxy(garosize*11+leftend, serosize*pos2+i+upend+1); printf("｜");
			}
			for(i=0; i<=4; i++)
			{
				gotoxy(garosize*10+2*i+leftend+1, serosize*pos2+upend); printf("―");
				gotoxy(garosize*10+2*i+leftend+1, serosize*pos2+upend+serosize); printf("―");
			}
		}
	}
};

land LAND[41];
char *playershape[]={"●"};

class player  //1: 빨강 2: 파랑 3:초록 4:노랑
{
public:
	int owner;
	int money[8];  //{50만, 10만, 5만, 2만, 1만, 5천, 1천} 
	int total; 
	int ter[41];
	int ude; //우대권 0~2
	int mujeon; //무전기 0~1
	int pos;  //1~40
	int pos1, pos2;   //pos1: 1~4, pos2: 0~9
	int muin; //무인도에서 남은 턴수 (1~3) 
	int pasan; //파산했을 시 1
	int i, j;
	
	void posinit()
	{
		if(pos==0)	//우주정거장
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
		if(pos==0) gotoxy(9*garosize+leftend+2*((owner-1)%2)-1, upend+(owner-1)/2+serosize+4);	//우주 정거장
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
                printf("50만원 : ");
                break;
            case 2:
                printf("10만원 : ");
                break;
            case 3:
                printf("5만원  : ");
                break;
            case 4:
                printf("2만원  : ");
                break;
            case 5:
                printf("만원   : ");
                break;
            case 6:
                printf("5천원  : ");
                break;
            case 7:
                printf("천원   : ");
                break;
			case 8:
				printf("합계   : ");
				break;
			case 9:
				if(ude!=0)
				{
					printf("우대권 %d개", ude);
				}
				for(j=1; j<=mujeon; j++)
				{
					if(ude!=0)
					{
						printf(", ");
					}
					printf("무전기");
				}
				break;
            }
			if(i<=7)	printf("%d개", money[i]);
			if(i==8)
			{
				printf("%d만 %d천원     ", total/10, total-10*(total/10));
			}
         } 
    }
	void playererase()
    {
		if(pos1==1) gotoxy(10*garosize+leftend+2-10*pos2+2*((owner-1)%2), 10*serosize+leftend+2+(owner-1)/2);
		if(pos1==3) gotoxy(leftend+2+10*pos2+2*((owner-1)%2), leftend+2+(owner-1)/2);
		if(pos1==2) gotoxy(leftend+2+2*((owner-1)%2), 10*serosize+leftend+2-4*pos2+(owner-1)/2);
		if(pos1==4) gotoxy(10*garosize+leftend+2+2*((owner-1)%2), leftend+2+4*pos2+(owner-1)/2); 
		if(pos==0) gotoxy(9*garosize+leftend+2*((owner-1)%2)-1, upend+(owner-1)/2+serosize+4);	//우주 정거장
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
            printf("―");
            gotoxy(11*garosize/2+leftend+(2*th-3)*2*i, upend+5*serosize+6+dicesize/2-1);
            printf("―");
        }
        for(i=1; i<=dicesize/2-2; i++)
        {      
            gotoxy(11*garosize/2+leftend+(2*th-3)*(dicesize+1), upend+5*serosize+6+i);
            printf("｜");
            gotoxy(11*garosize/2+leftend+(2*th-3)*3, upend+5*serosize+6+i);
            printf("｜");
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

void boardset(void);  //보드 세팅
void landset(void);   //땅 세팅
void GKset(void);     //황금열쇠 랜덤 배열 세팅
int fee(land x);      //각 땅의 통행료를 계산하는 함수
void Start();         //시작할 때 초기화
void turn(int P);     //player P의 턴을 시작하는 함수
void choose(int P, int landatt);  //player P가 땅에 걸렸을 때 뭘 할지 선택하게 하는 함수
int pay(int P, int price, int escapable);  //player P가 price인 돈을 내는 함수 
int f(int a); //f(1)=500, f(2)=100, f(3)=50, f(4)=20, f(5)=10, f(6)=5, f(7)=1
void receive(int P, int remain);  //player P가 remain인 돈을 받는 함수
void sell(int P);  //player P가 땅을 파는 함수
void gkget(int P, int num);   //황금열쇠를 얻었을 때 함수
void gkboxshow(void);  //황금열쇠 박스 보여주는 함수
void gkerase(void);    //황금열쇠 박스 지우는 함수
int spacetrip(int P);  //콜럼비아호 우주여행 함수

int pnum;
int t;
int gk[31];
int currentcard; //현재 바닥에 놓여 있지 않는 황금열쇠 수

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
			if(i!=t%pnum+1 && PLAYER[i].pasan==0) //자신이 아니면서 파산이 아닌 사람이 한 명이라도 있으면
			{
				win=0;
			}
		}
		if(win)
		{
			if(t%pnum+1==1)	 RED;    if(t%pnum+1==2)	 BLUE;
			if(t%pnum+1==3)	 BLACK;  if(t%pnum+1==4)	 YELLOW;
			gotoxy(leftend+5*garosize-15, upend+5*serosize+3);
			printf("모두가 파산하여 player%d가 승리하였습니다!!\n", t%pnum+1);
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
					gotoxy(garosize*i+leftend, serosize*j+k+upend+1); printf("｜");
				}
				if((!(1<=j && j<=9 && 2<=i && i<=9)) || (i==3 && (j==9 || j==8)))
				{
					gotoxy(garosize*j+2*k+leftend+1, serosize*i+upend); printf("―");
				}
			}
		}
	}
	gotoxy(8*garosize+leftend, serosize+upend+4); printf("｜");
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
	LAND[1].price=0; strcpy(LAND[1].name, " 출  발"); LAND[1].att=CNR;
	LAND[2].price=50; LAND[2].vprice=50; LAND[2].bprice=150; LAND[2].hprice=250; strcpy(LAND[2].name, "타이페이");
	LAND[3].price=0; strcpy(LAND[3].name, "황금열쇠"); LAND[3].att=GK;
	LAND[4].price=80; LAND[4].vprice=50; LAND[4].bprice=150; LAND[4].hprice=250; strcpy(LAND[4].name, "홍 콩");
	LAND[5].price=80; LAND[5].vprice=50; LAND[5].bprice=150; LAND[5].hprice=250; strcpy(LAND[5].name, "마닐라");
	LAND[6].price=200; strcpy(LAND[6].name, "제주도"); LAND[6].att=SP;
	LAND[7].price=100; LAND[7].vprice=50; LAND[7].bprice=150; LAND[7].hprice=250; strcpy(LAND[7].name, "싱가폴");
	LAND[8].price=0; strcpy(LAND[8].name, "황금열쇠"); LAND[8].att=GK;
	LAND[9].price=100; LAND[9].vprice=50; LAND[9].bprice=150; LAND[9].hprice=250; strcpy(LAND[9].name, "카이로");
	LAND[10].price=120; LAND[10].vprice=50; LAND[10].bprice=150; LAND[10].hprice=250; strcpy(LAND[10].name, "이스탄불");

	LAND[11].price=0; strcpy(LAND[11].name, "무인도"); LAND[11].att=CNR;
	LAND[12].price=140; LAND[12].vprice=100; LAND[12].bprice=300; LAND[12].hprice=500; strcpy(LAND[12].name, "아테네");
	LAND[13].price=0; strcpy(LAND[13].name, "황금열쇠"); LAND[13].att=GK;
	LAND[14].price=160; LAND[14].vprice=100; LAND[14].bprice=300; LAND[14].hprice=500; strcpy(LAND[14].name, "코펜하겐");
	LAND[15].price=160; LAND[15].vprice=100; LAND[15].bprice=300; LAND[15].hprice=500; strcpy(LAND[15].name, "스톡홀름");
	LAND[16].price=200; strcpy(LAND[16].name, "콩고드"); LAND[16].att=SP;
	LAND[17].price=180; LAND[17].vprice=100; LAND[17].bprice=300; LAND[17].hprice=500; strcpy(LAND[17].name, "취리히");
	LAND[18].price=0; strcpy(LAND[18].name, "황금열쇠"); LAND[18].att=GK;
	LAND[19].price=180; LAND[19].vprice=100; LAND[19].bprice=300; LAND[19].hprice=500; strcpy(LAND[19].name, "베를린");
	LAND[20].price=200; LAND[20].vprice=100; LAND[20].bprice=300; LAND[20].hprice=500; strcpy(LAND[20].name, "몬트리올");

	LAND[21].price=0; strcpy(LAND[21].name, "사회복지"); LAND[21].att=CNR;
	LAND[22].price=220; LAND[22].vprice=150; LAND[22].bprice=450; LAND[22].hprice=750; strcpy(LAND[22].name, "부에노스");
	LAND[23].price=0; strcpy(LAND[23].name, "황금열쇠"); LAND[23].att=GK;
	LAND[24].price=240; LAND[24].vprice=150; LAND[24].bprice=450; LAND[24].hprice=750; strcpy(LAND[24].name, "상파울로");
	LAND[25].price=240; LAND[25].vprice=150; LAND[25].bprice=450; LAND[25].hprice=750; strcpy(LAND[25].name, "시드니");
	LAND[26].price=500; strcpy(LAND[26].name, "부  산"); LAND[26].att=SP;
	LAND[27].price=260; LAND[27].vprice=150; LAND[27].bprice=450; LAND[27].hprice=750; strcpy(LAND[27].name, "하와이");
	LAND[28].price=260; LAND[28].vprice=150; LAND[28].bprice=450; LAND[28].hprice=750; strcpy(LAND[28].name, "리스본");
	LAND[29].price=300; strcpy(LAND[29].name, "엘리자호"); LAND[29].att=SP;
	LAND[30].price=280; LAND[30].vprice=150; LAND[30].bprice=450; LAND[30].hprice=750; strcpy(LAND[30].name, "마드리드");

	LAND[31].price=0; strcpy(LAND[31].name, "우주여행"); LAND[31].att=CNR;
	LAND[32].price=300; LAND[32].vprice=200; LAND[32].bprice=600; LAND[32].hprice=1000; strcpy(LAND[32].name, "도  쿄");
	LAND[33].price=450; strcpy(LAND[33].name, "콜럼비아호"); LAND[33].att=SP;
	LAND[34].price=320; LAND[34].vprice=200; LAND[34].bprice=600; LAND[34].hprice=1000; strcpy(LAND[34].name, "파  리");
	LAND[35].price=320; LAND[35].vprice=200; LAND[35].bprice=600; LAND[35].hprice=1000; strcpy(LAND[35].name, "로  마");
	LAND[36].price=0; strcpy(LAND[36].name, "황금열쇠"); LAND[36].att=GK;
	LAND[37].price=350; LAND[37].vprice=200; LAND[37].bprice=600; LAND[37].hprice=1000; strcpy(LAND[37].name, "런  던");
	LAND[38].price=350; LAND[38].vprice=200; LAND[38].bprice=600; LAND[38].hprice=1000; strcpy(LAND[38].name, "뉴  욕");
	LAND[39].price=150; strcpy(LAND[39].name, "사회복지"); LAND[39].att=CNR;
	LAND[40].price=1000; LAND[40].vprice=200; LAND[40].bprice=600; LAND[40].hprice=1000; strcpy(LAND[40].name, "서  울");

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
	case 1: //타이페이
		if((x.v)==0 && x.b==0 && x.h==0)	f=2;
		else
		{
			f=5*(x.v)*(x.v)+5*(x.v)+90*x.b+250*x.h;
		}
		break;
	case 3: //홍콩 
		if((x.v)==0 && x.b==0 && x.h==0)	f=4;
		else
		{
			f=10*(x.v)*(x.v)+10*(x.v)+180*x.b+450*x.h;
		}
		break;
	case 4: //마닐라
		if((x.v)==0 && x.b==0 && x.h==0)	f=4;
		else
		{
			f=10*(x.v)*(x.v)+10*(x.v)+180*x.b+450*x.h;
		}
		break;
	case 5:  //제주도
		f=300;
		break;
	case 6:  //싱가폴
		if((x.v)==0 && x.b==0 && x.h==0)	f=6;
		else
		{
			f=15*(x.v)*(x.v)+15*(x.v)+270*x.b+550*x.h;
		}
		break;
	case 8:  //카이로
		if((x.v)==0 && x.b==0 && x.h==0)	f=6;
		else
		{
			f=15*(x.v)*(x.v)+15*(x.v)+270*x.b+550*x.h;
		}
		break;
	case 9:  //이스탄불
		if((x.v)==0 && x.b==0 && x.h==0)	f=8;
		else
		{
			f=10*(x.v)*(x.v)+30*(x.v)+300*x.b+600*x.h;
		}
		break;
	case 11:  //아테네 
		if((x.v)==0 && x.b==0 && x.h==0)	f=10;
		else
		{
			f=25*(x.v)*(x.v)+25*(x.v)+450*x.b+750*x.h;
		}
		break;
	case 13:  //코펜하겐
		if((x.v)==0 && x.b==0 && x.h==0)	f=12;
		else
		{
			f=30*(x.v)*(x.v)+30*(x.v)+500*x.b+900*x.h;
		}
		break;
	case 14:  //스톡홀름
		if((x.v)==0 && x.b==0 && x.h==0)	f=12;
		else
		{
			f=30*(x.v)*(x.v)+30*(x.v)+500*x.b+900*x.h;
		}
		break;
	case 15:  //콩고드여객기
		f=300;
		break;
	case 16:  //취리히
		if((x.v)==0 && x.b==0 && x.h==0)	f=14;
		else
		{
			f=30*(x.v)*(x.v)+40*(x.v)+550*x.b+950*x.h;
		}
		break;
	case 18:  //베를린
		if((x.v)==0 && x.b==0 && x.h==0)	f=14;
		else
		{
			f=30*(x.v)*(x.v)+40*(x.v)+550*x.b+950*x.h;
		}
		break;
	case 19:  //몬트리올
		if((x.v)==0 && x.b==0 && x.h==0)	f=16;
		else
		{
			f=30*(x.v)*(x.v)+50*(x.v)+600*x.b+1000*x.h;
		}
		break;
	case 21:  //부에노스 아이레스
		if((x.v)==0 && x.b==0 && x.h==0)	f=18;
		else
		{
			f=35*(x.v)*(x.v)+55*(x.v)+700*x.b+1050*x.h;
		}
		break;
	case 23:  //상파울로
		if((x.v)==0 && x.b==0 && x.h==0)	f=20;
		else
		{
			f=50*(x.v)*(x.v)+50*(x.v)+750*x.b+1100*x.h;
		}
		break;
	case 24:  //시드니
		if((x.v)==0 && x.b==0 && x.h==0)	f=20;
		else
		{
			f=50*(x.v)*(x.v)+50*(x.v)+750*x.b+1100*x.h;
		}
		break;
	case 25:  //부산
		f=600;
		break;
	case 26:  //하와이
		if((x.v)==0 && x.b==0 && x.h==0)	f=22;
		else
		{
			f=55*(x.v)*(x.v)+55*(x.v)+800*x.b+1150*x.h;
		}
		break;
	case 27:  //리스본
		if((x.v)==0 && x.b==0 && x.h==0)	f=22;
		else
		{
			f=55*(x.v)*(x.v)+55*(x.v)+800*x.b+1150*x.h;
		}
		break;
	case 28:  //퀸 엘리자베스 호 
		f=250;
		break;
	case 29:  //마드리드
		if((x.v)==0 && x.b==0 && x.h==0)	f=24;
		else
		{
			f=60*(x.v)*(x.v)+60*(x.v)+850*x.b+1200*x.h;
		}
		break;
	case 31:  //도쿄
		if((x.v)==0 && x.b==0 && x.h==0)	f=26;
		else
		{
			f=65*(x.v)*(x.v)+65*(x.v)+900*x.b+1270*x.h;
		}
		break;
	case 32:  //콜럼비아호
		f=400;
		break;
	case 33:  //파리
		if((x.v)==0 && x.b==0 && x.h==0)	f=28;
		else
		{
			f=75*(x.v)*(x.v)+75*(x.v)+1000*x.b+1400*x.h;
		}
		break;
	case 34:  //로마
		if((x.v)==0 && x.b==0 && x.h==0)	f=28;
		else
		{
			f=75*(x.v)*(x.v)+75*(x.v)+1000*x.b+1400*x.h;
		}
		break;
	case 36:  //런던
		if((x.v)==0 && x.b==0 && x.h==0)	f=35;
		else
		{
			f=80*(x.v)*(x.v)+90*(x.v)+1100*x.b+1500*x.h;
		}
		break;
	case 37:  //뉴욕
		if((x.v)==0 && x.b==0 && x.h==0)	f=35;
		else
		{
			f=80*(x.v)*(x.v)+90*(x.v)+1100*x.b+1500*x.h;
		}
		break;
	case 38:  //사회복지기금
		f=150;
		break;
	case 39:  //서울
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
	printf("부  루  마  블  게임");
	gotoxy(leftend+11*garosize/2-10, upend+5*serosize+2);
	printf("      made by K.Y.S");
	boardset();
	landset();
	GKset();
	for(i=1; i<=40; i++)
	{
		LAND[i].landshow();
	}
	gotoxy(8*garosize+leftend+4, serosize+upend+1); printf("우 주 정 거 장");

    gotoxy(leftend+5*garosize-3, upend+5*serosize+4);
	printf("2p     3p     4p");
    while(1)
    {
        gotoxy(7*cursor+leftend+5*garosize-10, upend+5*serosize+5);
        printf("↑"); 
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
	if(PLAYER[P].pasan==1)	return;		//더블나왔는데 파산했을 경우
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
			printf("무인도에서 남은 일 수: %d", PLAYER[P].muin);
			if(PLAYER[P].mujeon==0)
			{
				while(getch()!=ENTER) i=1;
			}
			else
			{
				YELLOW;
				gotoxy(leftend+5*garosize-8, upend+5*serosize+4); printf("무전기 사용 Y or N", P);
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
						gotoxy(leftend+5*garosize-13, upend+5*serosize+3); printf("player%d가 무인도에서 탈출했습니다.", P);
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
			gotoxy(leftend+5*garosize-13, upend+5*serosize+3); printf("player%d가 무인도에서 탈출했습니다.", P);
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
			printf("월급 20만원을 받았습니다.", P);
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
	int pos; //우주여행 시 갈 목적지
    int i;
    if(landatt==NM && LAND[PLAYER[P].pos].owner==0)
    {
        WHITE;
        gotoxy(11*garosize/2+leftend-4, upend+serosize+7);
        printf("1. 구매");
        gotoxy(11*garosize/2+leftend-4, upend+serosize+9); 
        printf("2. 패스"); 
        while(1)
        {
            gotoxy(11*garosize/2+leftend-7, upend+serosize+2*cursor+5);
            printf("→");
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
            printf("건설할 건물을 선택하세요."); 
            gotoxy(11*garosize/2+leftend-25, upend+serosize+5);
            printf("선택=space bar 취소=delete 지불=enter 나가기=esc");
            while(1)
            {
                gotoxy(11*garosize/2+leftend-12, upend+serosize+7);
                printf("별장(%d만원) : %d개", LAND[PLAYER[P].pos].vprice/10, v);
                gotoxy(11*garosize/2+leftend-12, upend+serosize+9);
                printf("빌딩(%d만원) : %d개", LAND[PLAYER[P].pos].bprice/10, b);
                gotoxy(11*garosize/2+leftend-12, upend+serosize+11);
                printf("호텔(%d만원) : %d개", LAND[PLAYER[P].pos].hprice/10, h);
				gotoxy(11*garosize/2+leftend-12, upend+serosize+13);
				printf("총 가격: %d만원", (LAND[PLAYER[P].pos].price+v*LAND[PLAYER[P].pos].vprice+b*LAND[PLAYER[P].pos].bprice+h*LAND[PLAYER[P].pos].hprice)/10);
                gotoxy(11*garosize/2+leftend-15, upend+serosize+2*cursor+5);
                printf("→");
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
        printf("1. 구매");
        gotoxy(11*garosize/2+leftend-3, upend+serosize+9); 
        printf("2. 패스"); 
        while(1)
        {
            gotoxy(11*garosize/2+leftend-7, upend+serosize+2*cursor+5);
            printf("→");
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
        gotoxy(11*garosize/2+leftend-16, upend+serosize+2); printf("player%d : ㅎㅇ", LAND[PLAYER[P].pos].owner);
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
    else if(PLAYER[P].pos==11) //무인도
    {
        if(PLAYER[P].muin==0)  PLAYER[P].muin=3;
    }
	else if(PLAYER[P].pos==39) //사회복지기금 접수처
	{
		WHITE;
		gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("사회복지기금 15만원을 내세요");
		pay(P, 150, 0);
		gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("                                  ");
		fund+=150;
		LAND[21].landshow();
	}
	else if(PLAYER[P].pos==21 && fund!=0) //사회복지기금
	{
		WHITE;
		gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
		printf("사회복지기금 %d만원을 받았습니다", fund/10);
		fund=0;
		receive(P, fund);
		getch();
		gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
		printf("                               ", fund/10);
	}
	else if(PLAYER[P].pos==31) //콜럼비아호
	{
		WHITE;
		gotoxy(leftend+5*garosize-8, upend+5*serosize+4); printf("우주선 탑승 Y or N(비용 20만원)");
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
				gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("우주정거장으로 갑니다");
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
		if(pos==21 && fund!=0) //사회복지기금
		{
			WHITE;
			gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
			printf("사회복지기금 %d만원을 받았습니다", fund/10);
			fund=0;
			receive(P, fund);
			getch();
			gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
			printf("                               ", fund/10);
		}
		 if(PLAYER[P].pos==11) //무인도
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
		printf("   지불할 화폐를 선택하세요.   "); 
		gotoxy(11*garosize/2+leftend-12, upend+serosize+4);
		if(price%10==0)
		{
			printf("지불해야할 돈 : %d만원", price/10);
		}
		else
		{
			printf("지불해야할 돈 : %d만 %d천원", price/10, price-10*(price/10));
		} 
		if(PLAYER[P].total<price)
		{
			gotoxy(11*garosize/2+leftend-17, upend+serosize+3);
			printf("                                                  ");
			gotoxy(11*garosize/2+leftend-6, upend+serosize+5);
			printf("돈이 모자랍니다.");
			gotoxy(11*garosize/2+leftend-1, upend+serosize+7);
			printf("1. 팔기");
			gotoxy(11*garosize/2+leftend-1, upend+serosize+9);
			printf("2. 파산");
			if(escapable==1)
			{
				gotoxy(11*garosize/2+leftend-1, upend+serosize+11);
				printf("3. 나가기");
			}

			while(1)
			{
				WHITE;
				gotoxy(11*garosize/2+leftend-4, upend+serosize+2*cursor+5);
				printf("→");
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
						printf("player%d가 파산했습니다.", P);
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
    printf("선택=spacebar 취소=delete 지불=enter ");
	if(escapable==1)	printf("나가기=esc"); 
	if(escapable==0 && PLAYER[P].ude>0)
	{
		gotoxy(11*garosize/2+leftend-6, upend+serosize+11); YELLOW; printf("우대권 사용");
		WHITE;
	}
    for(i=1; i<=7; i++)
    {
        gotoxy(11*garosize/2+leftend-11, i+11);
		if(i<=2) printf("%d만원  0개 / %d개", f(i)/10, PLAYER[P].money[i]);
        else if(i<=5) printf("%d만원   0개 / %d개", f(i)/10, PLAYER[P].money[i]);
        if(i>=6) printf("%d천원   0개 / %d개", f(i), PLAYER[P].money[i]);
	}
	gotoxy(11*garosize/2+leftend-11, upend+serosize+15); printf("합계 : 0만 0천원");
    while(1)
    {
        WHITE;
        gotoxy(11*garosize/2+leftend-14, upend+serosize+cursor+6);  printf("→");
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
				if(cursor<=2) printf("%d만원  %d개 / %d개", f(cursor)/10, bill[cursor], PLAYER[P].money[cursor]);
                else if(cursor<=5) printf("%d만원   %d개 / %d개", f(cursor)/10, bill[cursor], PLAYER[P].money[cursor]);
                if(cursor>=6) printf("%d천원   %d개 / %d개", f(cursor), bill[cursor], PLAYER[P].money[cursor]);
				gotoxy(11*garosize/2+leftend-11, upend+serosize+15); printf("합계 : %d만 %d천원", charge/10, charge-10*(charge/10));
            }
            else
            {
                gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("지불할 화폐가 부족합니다.");
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
				if(cursor<=2) printf("%d만원  %d개 / %d개", f(cursor)/10, bill[cursor], PLAYER[P].money[cursor]);
                else if(cursor<=5) printf("%d만원   %d개 / %d개", f(cursor)/10, bill[cursor], PLAYER[P].money[cursor]);
                if(cursor>=6) printf("%d천원   %d개 / %d개", f(cursor), bill[cursor], PLAYER[P].money[cursor]); 
				gotoxy(11*garosize/2+leftend-11, upend+serosize+15); printf("합계 : %d만 %d천원", charge/10, charge-10*(charge/10));
            }
            else
            {
                gotoxy(11*garosize/2+leftend-12, upend+serosize+2); printf("취소할 화폐가 없습니다.");
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
					printf("돈이 모자랍니다.");
					getch();
					gotoxy(11*garosize/2+leftend-12, upend+serosize+2);
					printf("                ");
				}
				else
				{
					remain=charge-price;

					gotoxy(11*garosize/2+leftend+11, upend+serosize+11);
					if(price%10==0) printf("원가 : %d만원", price/10);
					else printf("원가 : %d만 %d천원", price/10, price-10*(price/10)); 

					gotoxy(11*garosize/2+leftend+11, upend+serosize+12);
					if(price%10==0) printf("지불액 : %d만원", charge/10);
					else printf("지불액 : %d만 %d천원", charge/10, charge-10*(charge/10));
                
					gotoxy(11*garosize/2+leftend+11, upend+serosize+13);
					if(price%10==0)  printf("잔돈 : %d만원", remain/10);
					else printf("잔돈 : %d만 %d천원", remain/10, remain-10*(remain/10));

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
				printf("우대권을 사용하셨습니다.");
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
			printf(" : %d만원", landprice[landnum]/10);
			th[landnum]=i;
			
		}
	}
	WHITE;
	gotoxy(11*garosize/2+leftend+14, upend+serosize+5+landnum);
	printf("팔기=enter  나가기=esc");
	while(1)
	{
		WHITE;
		gotoxy(11*garosize/2+leftend+11, upend+serosize+4+cursor);
		printf("→");
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
	int v=0, b=0, h=0;  //건물수리비 지불 등등
	int fee=0;          //건물수리비 지불 등등
	int landprice=0;    //반액대매출
	int landpricemax=0, maxland=0; //반액대매출
	YELLOW;
	gkboxshow();
	switch(num)
	{
	case 1:
        gkboxshow();
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("병원비 지불");
		gotoxy(11*garosize/2+leftend-14, upend+serosize+7); printf("병원에서 건강 진단을 받았습니다.");
		gotoxy(11*garosize/2+leftend-12, upend+serosize+9); printf("병원비 5만원을 은행에 내시오");
		while(getch()!=ENTER)	i=1;
		gkerase();
		pay(P, 50, 0);
		break;
	case 2:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("복권 당첨");
		gotoxy(11*garosize/2+leftend-9, upend+serosize+7); printf("복권에 당첨되셨습니다.");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("당첨금 20만원");
		while(getch()!=ENTER)	i=1;
		gkerase();
		receive(P, 200);
		break;
	case 3:
		gotoxy(11*garosize/2+leftend-11, upend+serosize+5); printf("무인도 탈출용 특수 무전기");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+7); printf("무인도에서 탈출할 수 있습니다.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		PLAYER[P].mujeon=1;
		PLAYER[P].moneyshow();
		break;
	case 4:
		gotoxy(11*garosize/2+leftend-6, upend+serosize+5); printf("무인도로 가시오");
		gotoxy(11*garosize/2+leftend-7, upend+serosize+7); printf("폭풍을 만났습니다.");
		gotoxy(11*garosize/2+leftend-17, upend+serosize+9); printf("출발지를 거쳐가도 월급을 못 받습니다.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		PLAYER[P].pos=11;
		PLAYER[P].muin=3;
		PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
		break;
	case 5:
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("파티 초대권");
		gotoxy(11*garosize/2+leftend-7, upend+serosize+7); printf("장기자랑을 하시오.");
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("적당량의 상금을 받습니다.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		break;
	case 6:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("관광 여행");
		gotoxy(11*garosize/2+leftend-7, upend+serosize+7); printf("제주도로 가십시오");
		gotoxy(11*garosize/2+leftend-12, upend+serosize+9); printf("제주도에 통행료 지불 -30만원");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+11); printf("출발지를 거쳐갈 시 월급 +20만원");
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
		gotoxy(11*garosize/2+leftend-5, upend+serosize+5); printf("과속 운전 벌금");
		gotoxy(11*garosize/2+leftend-9, upend+serosize+7); printf("과속운전을 하였습니다.");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("5만원을 내시오");
		while(getch()!=ENTER)	i=1;
		gkerase();
		pay(P, 50, 0);
		break;
	case 8:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("해외 유학");
		gotoxy(11*garosize/2+leftend-8, upend+serosize+7); printf("학교 등록금을 내시오.");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("등록금 10만원");
		while(getch()!=ENTER)	i=1;
		gkerase();
		pay(P, 100, 0);
		break;
	case 9:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("연금 혜택");
		gotoxy(11*garosize/2+leftend-11, upend+serosize+7); printf("노후연금 5만원을 받으시오.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		receive(P, 50);
		break;
	case 10://?
	case 11:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("고속 도로");
		gotoxy(11*garosize/2+leftend-9, upend+serosize+7); printf("출발지까지 바로 가시오.");
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
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("우    승");
		gotoxy(11*garosize/2+leftend-16, upend+serosize+7); printf("자동차 경주에서 챔피온이 되었습니다.");
		gotoxy(11*garosize/2+leftend-4, upend+serosize+9); printf("상금 10만원");
		while(getch()!=ENTER)	i=1;
		gkerase();
		receive(P, 100);
		break;
	case 13:
	case 26:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("우 대 권");
		gotoxy(11*garosize/2+leftend-16, upend+serosize+7); printf("통행료를 한 번 면제받을 수 있습니다.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		PLAYER[P].ude+=1; PLAYER[P].moneyshow();
		break;
	case 14:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("항공 여행");
		gotoxy(11*garosize/2+leftend-17, upend+serosize+7); printf("콩고드여객기를 타고 타이페이로 가시오");
		gotoxy(11*garosize/2+leftend-12, upend+serosize+9); printf("콩고드에 객실료 지불 -30만원");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+11); printf("출발지를 거쳐갈 시 월급 +20만원");
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
		gotoxy(11*garosize/2+leftend-6, upend+serosize+5); printf("건물 수리비 지불");
		gotoxy(11*garosize/2+leftend-12, upend+serosize+7); printf("모든 건물을 수리하여야 합니다.");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("호텔 : 10만원");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+10); printf("빌딩 : 6만원");
        gotoxy(11*garosize/2+leftend-5, upend+serosize+11); printf("별장 : 3만원");
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
			gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("건물이 없습니다.");
		}
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("                     ");
		break;
	case 16:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("방 범 비");
		gotoxy(11*garosize/2+leftend-10, upend+serosize+7); printf("방범비를 은행에 지불하세요");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("호텔 : 5만원");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+10); printf("빌딩 : 3만원");
        gotoxy(11*garosize/2+leftend-5, upend+serosize+11); printf("별장 : 1만원");
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
			gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("건물이 없습니다.");
		}
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("                     ");
		break;
	case 17:
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("유람선 여행");
		gotoxy(11*garosize/2+leftend-18, upend+serosize+7); printf("퀸 엘리자베스호를 타고 홍콩으로 가시오");
		gotoxy(11*garosize/2+leftend-17, upend+serosize+9); printf("퀸 엘리자베스호에 객실료 지불 -25만원");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+11); printf("출발지를 거쳐갈 시 월급 +20만원");
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
		gotoxy(11*garosize/2+leftend-7, upend+serosize+5); printf("생일을 축하합니다");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+7); printf("모두에게 생일 축하금을 받으세요");
		gotoxy(11*garosize/2+leftend+6, upend+serosize+9); printf("축하금 1천원");
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
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("장학금 혜택");
		gotoxy(11*garosize/2+leftend-10, upend+serosize+7); printf("장학금 10만원을 받으시오.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		receive(P, 100);
		break;
	case 21:
		gotoxy(11*garosize/2+leftend-7, upend+serosize+5); printf("정기 종합 소득세");
		gotoxy(11*garosize/2+leftend-10, upend+serosize+7); printf("종합소득세를 지불하시오.");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+9); printf("호텔 : 15만원");
		gotoxy(11*garosize/2+leftend-5, upend+serosize+10); printf("빌딩 : 10만원");
        gotoxy(11*garosize/2+leftend-5, upend+serosize+11); printf("별장 : 3만원");
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
			gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("건물이 없습니다.");
		}
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("                     ");
		break;
	case 22:
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("노벨 평화상 수상");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+7); printf("당신은 세계평화를 위해 공헌하여");
		gotoxy(11*garosize/2+leftend-11, upend+serosize+9); printf("상금 30만원을 배당 받습니다.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		receive(P, 300);
		break;
	case 23:
		gotoxy(11*garosize/2+leftend-3, upend+serosize+5); printf("관광 여행");
		gotoxy(11*garosize/2+leftend-6, upend+serosize+7); printf("서울로 가십시오");
		gotoxy(11*garosize/2+leftend-12, upend+serosize+9); printf("서울에 통행료 지불 -200만원");
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
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("반액 대매출");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+7); printf("당신의 땅 중에서 가장 비싼 곳을");
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("은행에 반액으로 파십시오.");
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
			gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("%s이(가) %d만원에 팔렸습니다.", LAND[maxland].name, landprice/20);
			LAND[maxland].landerase();
			LAND[maxland].landshow();
			receive(P, landprice/2);
		}
		else
		{
			gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("팔 땅이 없습니다.");
		}
		while(getch()!=ENTER) i=1;
		gotoxy(11*garosize/2+leftend-10, upend+serosize+9); printf("                                      ");
		break;
	case 25:
		gotoxy(11*garosize/2+leftend-6, upend+serosize+5); printf("우주 여행 초청장");
		gotoxy(11*garosize/2+leftend-14, upend+serosize+7); printf("우주항공국에서 초청장이 왔습니다.");
		gotoxy(11*garosize/2+leftend-11, upend+serosize+9); printf("무료이므로 탑승료는 없습니다.");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+11); printf("출발지를 거쳐갈 시 월급 +20만원");
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
		gotoxy(11*garosize/2+leftend-6, upend+serosize+5); printf("세계 일주 초대권");
		gotoxy(11*garosize/2+leftend-9, upend+serosize+7); printf("한 바퀴 돌아 오십시오.");
		gotoxy(11*garosize/2+leftend-15, upend+serosize+9); printf("출발지를 지나면서 월급을 받으세요.");
		gotoxy(11*garosize/2+leftend-16, upend+serosize+11); printf("복지기금을 지나면서 기금을 받으세요");
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
		gotoxy(11*garosize/2+leftend-4, upend+serosize+5); printf("이사 가시오");
		gotoxy(11*garosize/2+leftend-8, upend+serosize+7); printf("뒤로 두칸 옮기시오.");
		while(getch()!=ENTER)	i=1;
		gkerase();
		PLAYER[P].pos-=2; //황금열쇠의 pos는 어차피 3 이상이기 때문에 음수가 될 리 없음
		PLAYER[P].playererase(); PLAYER[P].posinit(); PLAYER[P].playershow();
		break;
	case 29:
		gotoxy(11*garosize/2+leftend-7, upend+serosize+5); printf("사회복지 기금배당");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+7); printf("사회 복지 기금 접수처로 가시오.");
		gotoxy(11*garosize/2+leftend-13, upend+serosize+9); printf("출발지를 거쳐갈 시 월급 +20만원");
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
        printf("―");
        gotoxy(11*garosize/2+leftend-gkboxgarosize/2+2*i-1, upend+serosize+gkboxserosize+4);
        printf("―");
    }
    for(i=1; i<=gkboxserosize; i++)
    {      
        gotoxy(11*garosize/2+leftend-gkboxgarosize/2, upend+serosize+3+i);
        printf("｜");
        gotoxy(11*garosize/2+leftend+gkboxgarosize/2, upend+serosize+3+i);
        printf("｜");
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
	gotoxy(11*garosize/2+leftend-10, upend+serosize+6); printf("갈 곳을 선택해 주세요");
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