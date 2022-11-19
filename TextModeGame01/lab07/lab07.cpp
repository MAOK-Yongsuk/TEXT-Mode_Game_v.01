#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
//#include <thread>

void gotoxy(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y) {
	gotoxy(x, y);
	printf(" <-0-> ");
}

void setcursor(bool visible) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void erase_ship(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	setcolor(0, 0);
	printf("        "); // 7spacebar
}

void erase_bullet(int x, int y)
{
	COORD a = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), a);
	setcolor(0, 0);
	printf(" ");
}

void erase_star(int x, int y)
{
	COORD b = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), b);
	setcolor(0, 0);
	printf(" ");
}

char cursor(int x, int y)
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}


int main()
{
	srand(time(NULL));
	char ch = '.';
	int x = 38, y = 20, xbull[100], ybull[100], num = 1, points = 0, yrand, xrand;
	setcolor(2, 4);
	setcursor(0);
	draw_ship(x, y);
	
	

	int position = 0, shoot[100], bullet = 0, ammo = 5;

	do {		
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { position = 1; }
			else if (ch == 'd') { position = 2; }
			else if (ch == 's') { position = 0; }
			
			

			if (ch == ' ') {
				if (bullet < ammo) {				
					bullet += 1;
					ybull[bullet] = 19;
					xbull[bullet] = x + 3;
					shoot[bullet] = 1;
					Beep(1000, 400);
					//std::thread q(Beep, 1000, 400);
					//q.detach();
				}
			}
			fflush(stdin);
		}

		// Movement
		if (position == 1 && x != 0) {
			erase_ship(x, y);
			setcolor(2, 4);
			draw_ship(--x, y);
		}
		else if (position == 2 && x != 73) {
			erase_ship(x, y);
			setcolor(2, 4);
			draw_ship(++x, y);
		}

		// Star
		if (num <= 20) {
			yrand = (rand() % 4) + 1;
			xrand = (rand() % 61) + 10;
			setcolor(6, 0);
			gotoxy(xrand, yrand);
			printf("*");
			num += 1;
		}

	
		// Shoot
		for (int i = 1; i <= bullet; i++)
		{
			if (shoot[i] == 1) {
				erase_bullet(xbull[i], ybull[i]);
				if (ybull[i] > 0) {					
					if (cursor(xbull[i], ybull[i] - 1) == '*') {
						Beep(700, 400);
						//std::thread p(Beep, 700, 400);
						//p.detach();

						num = num - 1;
						erase_bullet(xbull[i], ybull[i]);
						erase_star(xbull[i], ybull[i] - 1);
						shoot[i] = 0;						
						points += 1;
					}
					else {
						gotoxy(xbull[i], --ybull[i]);
						setcolor(7, 8);
						printf("|");
					}					
				}
				else {
					shoot[i] = 0;
				}
			}
		}
		setcolor(7, 0);
		gotoxy(68, 0);
		printf("Points : %d", points);
		Sleep(100);
		

	} while (ch != 'x');
	return 0;
}
