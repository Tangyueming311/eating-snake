//test
//test2
//test3
//test4

#include<iostream>
#include<string>
#include<Windows.h>
#include <conio.h>
#include<iomanip>
#include<stdio.h>
#include<cstdlib>
using namespace std;
void game();
void menu();
void mapCreat();
void mapDraw();
void gotoxy(unsigned char x, unsigned char y);
void HideCursor();

int length = 50;
int height = 70;

 char map[50][70];
 int key;
 int tempKey;

 class food {
 private:
	 int num;
	 int point_x;
	 int point_y;
 public:
	 int get_x() { return point_x; }
	 int get_y() { return point_y; }
	 void makeFood() {
		 srand((unsigned)time(NULL));
		 point_x=  rand() %49 + 1;
		 point_y = rand() % 69 + 1;

		 map[get_x()][get_y()] = 4;
		 gotoxy(get_x(), get_y());
		
		 putchar('$');
	 }
 };



class snake {
private:
	int snakeHead_x ;
	int snakeHead_y ;

	int snakeBody_x[10000] = { 0 };
	int snakeBody_y[10000] = { 0 };

	int snakeBody ;
	int moveDirection;

public:
	friend void gotoxy(unsigned char x, unsigned char y);
	snake() ;

	int getHead_x();
	int getHead_y();
	void setHead_x(int x);
	void setHead_y(int y);
	void move(int x,int y);
	int getDirection();
	void setBody();

	int get_body() { return snakeBody; }
	int getbody_x(int x) { return snakeBody_x[x]; }
	int getbody_y(int y) { return snakeBody_y[y]; }
};

snake::snake() {
	snakeHead_x = 25;
	snakeHead_y = 35;
	snakeBody = 6;
	moveDirection = 119;
	snakeBody_x[0] = 25;
	snakeBody_y[0] = 36;
	snakeBody_x[1] = 25;
	snakeBody_y[1] = 37;
	snakeBody_x[2] = 25;
	snakeBody_y[2] = 38;
	snakeBody_x[3] = 25;
	snakeBody_y[3] = 39;
	snakeBody_x[4] = 25;
	snakeBody_y[4] = 40;
	snakeBody_x[5] = 25;
	snakeBody_y[5] = 41;
}

int snake::getHead_x() {
	return snakeHead_x;
}
int snake::getHead_y() {
	return snakeHead_y;
}
int snake::getDirection() {
	return moveDirection;
}

void snake::setHead_x(int x) {
	snakeHead_x = x;
}
void snake::setHead_y(int y) {
	snakeHead_y = y;
}
void snake::move(int x,int y) {
	
	if (x == 119) {
		snakeHead_y--;
	}
	else if (x == 100) {
		snakeHead_x++;
	}
	else if (x == 115) {
		snakeHead_y++;
	}
	else if (x == 97) {
		snakeHead_x--;
	}
	moveDirection = x;
	map[snakeHead_x][snakeHead_y] = '1';
}
void snake::setBody() {
	int i,j;
	
	for (i = snakeBody; i > 0; i--) {
		snakeBody_x[i] = snakeBody_x[i - 1];
	}
	for (i = snakeBody; i >0; i--) {
		snakeBody_y[i] = snakeBody_y[i - 1];
	}
	snakeBody_x[0] = snakeHead_x;
	snakeBody_y[0] = snakeHead_y;

	for (i = 0; i <snakeBody; i++) {
		
		map[snakeBody_x[i]][snakeBody_y[i]]='2';
		
	}
}

 snake S;


 void HideCursor()
 {
	 CONSOLE_CURSOR_INFO curInfo; //定义光标信息的结构体变量
	 curInfo.dwSize = 1; //如果没赋值的话，光标隐藏无效
	 curInfo.bVisible = FALSE; //将光标设置为不可见
	 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	 SetConsoleCursorInfo(handle, &curInfo); //设置光标信息
 }

 void gotoxy(unsigned char x, unsigned char y) {
	 //COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标
	 COORD cor;

	 //句柄 
	 HANDLE hout;

	 //设定我们要定位到的坐标 
	 cor.X = x;
	 cor.Y = y;

	 //GetStdHandle函数获取一个指向特定标准设备的句柄，包括标准输入，标准输出和标准错误。
	 //STD_OUTPUT_HANDLE正是代表标准输出（也就是显示屏）的宏 
	 hout = GetStdHandle(STD_OUTPUT_HANDLE);

	 //SetConsoleCursorPosition函数用于设置控制台光标的位置
	 SetConsoleCursorPosition(hout, cor);
 }

void menu() {

	cout << setfill(' ') << setw(35) << "贪吃蛇！" << endl;
	cout << setfill(' ') << setw(35) << "输入“1”以开始游戏!" << endl;
	cout << setfill(' ') << setw(35) << "输入“2”以退出游戏!" << endl;

	int a;
	cin >> a;
	if (a == 1) {
		mapCreat();
		while (1) {
			game();
		}

	}
	if (a == 2) {
		system("cls");

	}

}

void game() {
	//system("cls");
	S.setBody();
	if (_kbhit()) {
		tempKey = key;
		key = _getch();
		
		S.move(key,tempKey);
	}
	else S.move(S.getDirection(), S.getDirection());

	/*gotoxy(S.snakeBody_x[S.snakeBody - 1], S.snakeBody_y[S.snakeBody - 1]);
	putchar(' ');*/

	
	mapDraw();
	Sleep(100);
}







void mapCreat() {                                                  //"0"是空地，“1”是蛇头，“2”是蛇身，“3”是围墙,“4”是食物 
	system("cls");
	int i = 0, j = 0;
	for (j = 0; j < height; j++) {
		map[0][j] = '3';
	}
	for (j = 0; j < length; j++) {
		map[j][0] = '3';
	}
	for (i = 1; i < length-1; i++) {
		for (j = 1; j < height-1; j++) {
			map[i][j] = '0';
		}
	}
	for (j = 0; j < length; j++) {
		map[j][height-1] = '3';
	}
	for (j = 0; j < height; j++) {
		map[length-1][j] = '3';
	}
	map[S.getHead_x()][S.getHead_y()] = '2';
	map[S.getHead_x()][S.getHead_y()+1] = '2';
	map[S.getHead_x()][S.getHead_y()+2] = '2';
	//map[S.getHead_x()][S.getHead_y()] = '*';
	gotoxy(0, 0);
	for (i = 0; i < length; i++) {
		for (j = 0; j < height; j++) {
			gotoxy(i, j);
			if (map[i][j] == '0') {
				putchar(' ');
			}
			else if (map[i][j] == '3')
				putchar('#');
			else if (map[i][j] == '2') {
				putchar('*');
			}
		}
		
	}
	gotoxy(S.getHead_x(), S.getHead_y());
	putchar('*');
	gotoxy(S.getHead_x(), S.getHead_y() + 1);
	putchar('*');
	gotoxy(S.getHead_x(), S.getHead_y() + 2);
	putchar('*');


}

void mapDraw() {
	int j, i = 0;
	/*for (i = 0; i < 50; i++) {
		for (j = 0; j < 70; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}*/
	gotoxy(S.getHead_x(), S.getHead_y());
	putchar('*');

	gotoxy(S.getbody_x(S.get_body()), S.getbody_y(S.get_body()));
	putchar(' ');
	map[S.getbody_x(S.get_body())][S.getbody_y(S.get_body())] = '0';

}

int main() {
	HideCursor();
	menu();
}