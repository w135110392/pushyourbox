#include<graphics.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;

#define PIC_SIZE 61
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_Q  'q'
#define COLS  12
#define LINES 9
#define SCREEN_WIDTH 960
#define SCREEN_HIGHT 768
#define isValid(pos)  pos.X >= 0 && pos.X<LINES&&pos.Y >= 0 && pos.Y<COLS
void gameControl(enum DIRCTION dirct);

IMAGE pic[6];
//ǽ:0  �ذ�: 1  ����Ŀ�ĵ�: 2  С��:3  ����: 4  ��������Ŀ�� :5
int map[LINES][COLS] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	{ 0, 1, 4, 1, 0, 2, 1, 0, 2, 1, 0, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0 },
	{ 0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0 },
	{ 0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0 },
	{ 0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0 },
	{ 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
enum unit{
	wall,
	flor,
	des,
	man,
	box,
	hit
};

bool isGameover(){
	
	for (int i = 0; i < LINES; i++){
		for (int j = 0; j < COLS; j++){

			if (map[i][j] == des)return false;

		}
	}
	return true;
}
void gamemsg(IMAGE *bg){
	putimage(0, 0, bg);
	settextcolor(WHITE);
	RECT re = { 0, 0, SCREEN_WIDTH, SCREEN_HIGHT };
	settextstyle(40, 0, "����");
	drawtext("^_^��ϲ!!!!YOU WINNING!!!!", &re, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	
}


enum DIRCTION{
	UP,
	DOWN,
	LEFT,
	RIGHT

};
struct pos{   //��ʾ�˵�λ��
	int X;
	int Y;

};
struct pos men;



void changePic(struct pos *man, enum unit u){
	map[man->X][man->Y] = u;
	putimage(110 + man->Y*PIC_SIZE, 130 + man->X*PIC_SIZE, &pic[u]);

}


void gameControl(enum DIRCTION dirct){
	
	struct pos nextPos = men;  //ȡ��men.x men.y ��ֵ���µĽṹ�� ����������һ��λ�õ��� ����
	struct pos next_nextPos = men; //ȡ��men.x men.y ��ֵ���µĽṹ�� ��������������λ�õ��� ����
	switch (dirct){
	case UP:
		nextPos.X--;
		next_nextPos.X-= 2;
		
		break;
	case DOWN:
		nextPos.X++;
		next_nextPos.X += 2;
		
		break;
	case LEFT:
		nextPos.Y--;
		next_nextPos.Y -= 2;
		
		break;
	case RIGHT:
		nextPos.Y++;
		next_nextPos.Y += 2;
		
		break;
	}


	//��չ��  nextPos.X >= 0 && nextPos.X<LINES&&nextPos.Y >= 0 && nextPos.Y<COLS
	if (isValid(nextPos)&& map[nextPos.X][nextPos.Y] == flor){  //���ж�С�˵���һ��λ���ǲ��ǵذ� ����ķ�Χ �� �ǲ��Ǵ���0С��������  ���ǲ��Ǵ���0�ǲ���С���еķ�Χ
			changePic(&nextPos, man); //С��ǰ��λ�� ��ΪС��
			changePic(&men, flor);
			men = nextPos;
	}
	else if (isValid(next_nextPos) && map[nextPos.X][nextPos.Y] == box){
			
		if ( map[next_nextPos.X][next_nextPos.Y] == flor){
			changePic(&next_nextPos, box);
			changePic(&nextPos, man); //С��ǰ��λ�� ��ΪС��
			changePic(&men, flor);
			men = nextPos;
		}
		else if (isValid(nextPos) && map[next_nextPos.X][next_nextPos.Y] == des){
			changePic(&next_nextPos, hit);
			changePic(&nextPos, man); //С��ǰ��λ�� ��ΪС��
			changePic(&men, flor);
			men = nextPos;
		}
	
			
	 }
	
	}


int main(){
	IMAGE bg_img;
	char picName[6][32];

	initgraph(SCREEN_WIDTH, SCREEN_HIGHT);

	loadimage(&bg_img, _T("blackground.bmp"), 960, 768, true); //����ͼƬ
	putimage(0, 0, &bg_img); //ʹ��ͼƬ
	settextstyle(20, 0, "����");
	char explain[5][32];
	sprintf_s(explain[0],"%s","w ��");
	sprintf_s(explain[1], "%s", "s ��");
	sprintf_s(explain[2], "%s", "a ��");
	sprintf_s(explain[3], "%s", "d ��");
	sprintf_s(explain[4], "%s", "����ȫ���Ƶ�Ŀ�ĵ�,�ɹ�����!");
	int a = 110; //�������X������ʼλ��
	int b = 50; //�������Y������ʼλ��
	int n = 50; //�����������ƫ��
	for (int i = 0; i < sizeof(explain)/sizeof(string);i++){
		outtextxy(a, b, explain[i]);
		a += n;
		
	}
	

	sprintf_s(picName[wall], "%s", "wall_right.bmp");
	sprintf_s(picName[flor], "%s", "floor.bmp");
	sprintf_s(picName[des], "%s", "des.bmp");
	sprintf_s(picName[man], "%s", "man.bmp");
	sprintf_s(picName[box], "%s", "box.bmp");
	sprintf_s(picName[hit], "%s", "box.bmp");

	for (int i = 0; i < 6; i++){
		loadimage(&pic[i], picName[i], PIC_SIZE, PIC_SIZE, true); //����Ԫ��ͼƬ

	}

	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 12; j++){
			if (map[i][j]==3){
				men.X = i;
				men.Y = j;
			}
			putimage(110 + j*PIC_SIZE, 130 + i*PIC_SIZE, &pic[map[i][j]]); //����������еľ���ֵ ��Ӧ��ʾͼƬ���±�  ��Ϊ�����ֵ�Ǽ� ��Ӧ�ľ����±�Ϊ����ͼƬ

		}
	}
	//��Ϸ����
	bool quit = false;
	do{
		if (_kbhit()){
			char ch = _getch();
			if (ch == KEY_UP){
				gameControl(UP);
			}
			else if (ch == KEY_DOWN){
				gameControl(DOWN);
			}
			else if (ch == KEY_LEFT){
				gameControl(LEFT);
			}
			else if (ch == KEY_RIGHT){
				gameControl(RIGHT);
			}
			else if (ch == KEY_Q){
				quit = true;
			}
			if (isGameover()==true){
				Sleep(1000);
				gamemsg(&bg_img);
				system("pause");
				quit = true;
			}
		}
		Sleep(50);
	} while (quit == false);
	

	closegraph();

    return  0;
}