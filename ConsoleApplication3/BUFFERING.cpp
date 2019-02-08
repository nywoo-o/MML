#include "BUFFERING.h"
#include "network.h"
#include "console.h"
#include <stdio.h>
#include <fstream>
#include <iomanip>

char turn_interface;

char rulemon[30][150] = {
	{"  "},
	{"  "},
	{"  "},
	{"  "},
	{"                       +-----------------------------------------------------------+"},
	{"                       |                     ��HOW TO PLAY��                       |"},
	{"                       |    rule 1. 3�� �̻� ���� ��� ��Ʈ �ʱ�ȭ, ��� -1        |"},
	{"                       |    rule 2. 5�� �̻� ������ ��� ��Ʈ �ʱ�ȭ, ��� -1      |"},
	{"                       |    rule 3. �������� �� ���� ��� ��Ʈ �ʱ�ȭ, ��� -1     |"},
	{"                       |    rule 4. 15�ʰ� ������ �ڵ����� ���� �Ѿ�ϴ�.        |"},
	{"                       |    rule 5. ��� �������� �����Դϴ�                       |"},
	{"                       |    rule 6. 50�ۼ�Ʈ �̻� ���� ���� �Դ� ��� �¸�!        |"},
	{"                       |    rule 7. ĳ���� A�� ���� �����̰� �˴ϴ�                |"},
	{"                       +-----------------------------------------------------------+"},
	{"                       |                         ��ITEM��                          |"},
	{"                       |       item�� �� 4���� �����ϸ� �������� �����˴ϴ�!       |"},
	{"                       |       �ڽ��� ���� �������� ���� �� ����غ����� :         |"},
	{"                       +-----------------------------------------------------------+"},
	{" "},{" "},{" "},{" "}
};
BUFFERING::BUFFERING()
{
	color = 14; //�⺻�÷� ���
}
BUFFERING::~BUFFERING()
{
}
void BUFFERING::QuitOrContinue(char ch) {
	int enter = 1; //���� ��� �����ΰ�
	Console.gotoxy(15, 50); cout << "+------------------+\n";
	Console.gotoxy(16, 50); cout << "|   1.CONTINUE     |\n";
	Console.gotoxy(17, 50); cout << "|   2.  QUIT       |\n";
	Console.gotoxy(18, 50); cout << "|   3. SETTING     |\n";
	Console.gotoxy(19, 50); cout << "+------------------+";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	Console.gotoxy(16, 54); cout << "1.CONTINUE";
	while (1) {
		Sleep(100);
		if (GetAsyncKeyState(VK_DOWN) && enter == 1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(16, 54); cout << "1.CONTINUE";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(17, 54); cout << "2.  QUIT";
			enter = 2;
		}
		else if (GetAsyncKeyState(VK_DOWN) && enter == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(17, 54); cout << "2.  QUIT";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(18, 54); cout << "3. SETTING";
			enter = 3;
		}
		else if (GetAsyncKeyState(VK_UP) && enter == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(17, 54); cout << "2.  QUIT";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(16, 54); cout << "1.CONTINUE";
			enter = 1;
		}
		else if (GetAsyncKeyState(VK_UP) && enter == 3) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(18, 54); cout << "3. SETTING";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(17, 54); cout << "2.  QUIT";
			enter = 2;
		}
		else if (GetAsyncKeyState(VK_RETURN) && enter == 1) { 
			buf.clear();//���� ������ ���ư���~~
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			for (int i = 0; i < 35; i++) {
				for (int j = 0; map[i][j] != '\0'; j++) {
					Console.gotoxy(i, j);
					if (map[i][j] == ch) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
						cout << map[i][j] << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					}
					else cout << map[i][j] << endl;
				}
				

			} 
			return;
		}
		else if (GetAsyncKeyState(VK_RETURN) && enter == 2) { 
			ending[0] = '?'; //������ ������ ����ƴٴ� �� �˸�
			send(Connection1, ending, sizeof(ending), NULL);
			buf.clear();
			Console.gotoxy(15, 50); cout << "������ ����Ǿ����ϴ�.";
			exit(1); }
		else if (GetAsyncKeyState(VK_RETURN) && enter == 3) { 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			buf.settingmon(); 
		 }
	}
}
void BUFFERING::settingmon() {
	int enter = 1; //���� ��� �����ΰ�
	Console.gotoxy(15, 50); cout << "+------------------+\n";
	Console.gotoxy(16, 50); cout << "|   1.MUSIC  -1-   |\n";
	Console.gotoxy(17, 50); cout << "|   2.MUSIC  -2-   |\n";
	Console.gotoxy(18, 50); cout << "|   3.  BACK       |\n";
	Console.gotoxy(19, 50); cout << "+------------------+";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	Console.gotoxy(16, 54); cout << "1.MUSIC  -1-";
	while (1) {
		Sleep(100);
		if (GetAsyncKeyState(VK_DOWN) && enter == 1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(16, 54); cout << "1.MUSIC  -1-";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(17, 54); cout << "2.MUSIC  -2-";
			enter = 2;
		}
		else if (GetAsyncKeyState(VK_DOWN) && enter == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(17, 54); cout << "2.MUSIC  -2-";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(18, 54); cout << "3.  BACK";
			enter = 3;
		}
		else if (GetAsyncKeyState(VK_UP) && enter == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(17, 54); cout << "2.MUSIC  -2-";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(16, 54); cout << "1.MUSIC  -1-";
			enter = 1;
		}
		else if (GetAsyncKeyState(VK_UP) && enter == 3) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(18, 54); cout << "3.  BACK";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(17, 54); cout << "2.MUSIC  -2-";
			enter = 2;
		}
		else if (GetAsyncKeyState(VK_RETURN) && enter == 1) {
			soundchoice = 1; buf.sound();
		}
		else if (GetAsyncKeyState(VK_RETURN) && enter == 2) {
			soundchoice = 2; buf.sound();
		}
		else if (GetAsyncKeyState(VK_RETURN) && enter == 3) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(15, 50); cout << "+------------------+\n";
			Console.gotoxy(16, 50); cout << "|   1.CONTINUE     |\n";
			Console.gotoxy(17, 50); cout << "|   2.  QUIT       |\n";
			Console.gotoxy(18, 50); cout << "|   3. SETTING     |\n";
			Console.gotoxy(19, 50); cout << "+------------------+";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			return;
		}
	}
}
void BUFFERING::clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}
void BUFFERING::comparAndChange(char mych) {

	for (int i = 1; i < 34; i++) {
		for (int j = 1; j < 120; j++) {
			if (newmap[i][j] == map[i][j]) continue;
			Console.gotoxy(i, j);
			if (newmap[i][j] == mych) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
				cout << newmap[i][j];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else
				cout << newmap[i][j];
		}
	}
	cout.flush(); //���� �����̴�?
	memcpy((char*)map, (char const*)newmap, 121 * 35);

}
void BUFFERING::main_menu() {
	int enter = 1; //���� ��� �����ΰ�
	Console.gotoxy(1, 0); cout << "                      ��       ��          ��                                           ����\n";
	Console.gotoxy(2, 0); cout << "              ��                      ��                                 �١�                 ��\n";
	Console.gotoxy(4, 0); cout << "                               ��  ��                    ����           ��             ��\n";
	Console.gotoxy(6, 0); 
	cout << "                         **********************************************************\n"
		<< "                         *      ssss     tttttt     aa       rrrr     tttttt      *\n"
		<< "                         *     s           tt      a  a     r    r      tt        *\n"
		<< "                         *      sss        tt     aaaaaa    rrrrr       tt        *\n"
		<< "                         *         s       tt    a      a   r   r       tt        *\n"
		<< "                         *     ssss        tt   a        a  r    r      tt        *\n"
		<< "                         **********************************************************\n";
	Console.gotoxy(13, 0);
	cout << "                         **********************************************************\n"
		 << "                         *      ssss eeeee tttttt tttttt iii  nn   n    gggg      *\n"
		 << "                         *     s     e       tt     tt    i   n n  n   g          *\n"
		 << "                         *      sss  eeeee   tt     tt    i   n  n n  g    ggg    *\n"
		 << "                         *         s e       tt     tt    i   n   nn   g    g     *\n"
		 << "                         *     ssss  eeeee   tt     tt   iii  n    n    gggg      *\n"
		 << "                         **********************************************************\n";
	Console.gotoxy(21, 0);
	cout << "                         **********************************************************\n"
		 << "                         *      qqqq        u    u       iiiii        tttttt      *\n"
		 << "                         *     q    q       u    u         i            tt        *\n"
		 << "                         *     q  q q       u    u         i            tt        *\n"
		 << "                         *     q   qq       u    u         i            tt        *\n"
		 << "                         *      qqqq q       uuuu        iiiii          tt        *\n"
		 << "                         **********************************************************\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	Console.gotoxy(6, 0);
	cout << "                         **********************************************************\n"
		<< "                         *      ssss     tttttt     aa       rrrr     tttttt      *\n"
		<< "                         *     s           tt      a  a     r    r      tt        *\n"
		<< "                         *      sss        tt     aaaaaa    rrrrr       tt        *\n"
		<< "                         *         s       tt    a      a   r   r       tt        *\n"
		<< "                         *     ssss        tt   a        a  r    r      tt        *\n"
		<< "                         **********************************************************\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	while (1) {
		Sleep(100);
		if (GetAsyncKeyState(VK_DOWN) && enter == 1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(6, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      ssss     tttttt     aa       rrrr     tttttt      *\n"
				<< "                         *     s           tt      a  a     r    r      tt        *\n"
				<< "                         *      sss        tt     aaaaaa    rrrrr       tt        *\n"
				<< "                         *         s       tt    a      a   r   r       tt        *\n"
				<< "                         *     ssss        tt   a        a  r    r      tt        *\n"
				<< "                         **********************************************************\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(13, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      ssss eeeee tttttt tttttt iii  nn   n    gggg      *\n"
				<< "                         *     s     e       tt     tt    i   n n  n   g          *\n"
				<< "                         *      sss  eeeee   tt     tt    i   n  n n  g    ggg    *\n"
				<< "                         *         s e       tt     tt    i   n   nn   g    g     *\n"
				<< "                         *     ssss  eeeee   tt     tt   iii  n    n    gggg      *\n"
				<< "                         **********************************************************\n";
			enter = 2;
		}
		else if (GetAsyncKeyState(VK_DOWN) && enter == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(13, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      ssss eeeee tttttt tttttt iii  nn   n    gggg      *\n"
				<< "                         *     s     e       tt     tt    i   n n  n   g          *\n"
				<< "                         *      sss  eeeee   tt     tt    i   n  n n  g    ggg    *\n"
				<< "                         *         s e       tt     tt    i   n   nn   g    g     *\n"
				<< "                         *     ssss  eeeee   tt     tt   iii  n    n    gggg      *\n"
				<< "                         **********************************************************\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(21, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      qqqq        u    u       iiiii        tttttt      *\n"
				<< "                         *     q    q       u    u         i            tt        *\n"
				<< "                         *     q  q q       u    u         i            tt        *\n"
				<< "                         *     q   qq       u    u         i            tt        *\n"
				<< "                         *      qqqq q       uuuu        iiiii          tt        *\n"
				<< "                         **********************************************************\n";
			enter = 3;
		}
		else if (GetAsyncKeyState(VK_UP) && enter == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(13, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      ssss eeeee tttttt tttttt iii  nn   n    gggg      *\n"
				<< "                         *     s     e       tt     tt    i   n n  n   g          *\n"
				<< "                         *      sss  eeeee   tt     tt    i   n  n n  g    ggg    *\n"
				<< "                         *         s e       tt     tt    i   n   nn   g    g     *\n"
				<< "                         *     ssss  eeeee   tt     tt   iii  n    n    gggg      *\n"
				<< "                         **********************************************************\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(6, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      ssss     tttttt     aa       rrrr     tttttt      *\n"
				<< "                         *     s           tt      a  a     r    r      tt        *\n"
				<< "                         *      sss        tt     aaaaaa    rrrrr       tt        *\n"
				<< "                         *         s       tt    a      a   r   r       tt        *\n"
				<< "                         *     ssss        tt   a        a  r    r      tt        *\n"
				<< "                         **********************************************************\n";
			enter = 1;
		}
		else if (GetAsyncKeyState(VK_UP) && enter == 3) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(21, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      qqqq        u    u       iiiii        tttttt      *\n"
				<< "                         *     q    q       u    u         i            tt        *\n"
				<< "                         *     q  q q       u    u         i            tt        *\n"
				<< "                         *     q   qq       u    u         i            tt        *\n"
				<< "                         *      qqqq q       uuuu        iiiii          tt        *\n"
				<< "                         **********************************************************\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(13, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      ssss eeeee tttttt tttttt iii  nn   n    gggg      *\n"
				<< "                         *     s     e       tt     tt    i   n n  n   g          *\n"
				<< "                         *      sss  eeeee   tt     tt    i   n  n n  g    ggg    *\n"
				<< "                         *         s e       tt     tt    i   n   nn   g    g     *\n"
				<< "                         *     ssss  eeeee   tt     tt   iii  n    n    gggg      *\n"
				<< "                         **********************************************************\n";
			enter = 2;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && enter == 1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			buf.clear();
			return;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && enter == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			buf.clear();
			buf.main_setting();
		}
		else if (GetAsyncKeyState(VK_RIGHT) && enter == 3) {
			ending[0] = '?'; //������ ������ ����ƴٴ� �� �˸�
			send(Connection1, ending, sizeof(ending), NULL);
			buf.clear();
			Console.gotoxy(15, 50); cout << "������ ����Ǿ����ϴ�.";
			exit(1);
		}
	}
}
void BUFFERING::main_setting() {
	int enter = 1; //���� ��� �����ΰ�
	Console.gotoxy(1, 0); cout << "                      ��       ��          ��                                           ����\n";
	Console.gotoxy(2, 0); cout << "              ��                      ��                                 �١�                 ��\n";
	Console.gotoxy(4, 0); cout << "                               ��  ��                    ����           ��             ��\n";
	Console.gotoxy(6, 0);
	cout << "                         **********************************************************\n"
	     << "                         *                  1. green   A++++ B####                *\n"
		 << "                         *                  2. pink    A++++ B####                *\n"
		 << "                         *                  3. red     A++++ B####                *\n"
	     << "                         *                  4. yellow(default)                    *\n"
	     << "                         *                       type :                           *\n"
	     << "                         **********************************************************\n";
	Console.gotoxy(13, 0);
	cout << "                         **********************************************************\n"
		<< "                         *         sssss      ooooo      nn   n       gggg         *\n"
		<< "                         *        s          o     o     n n  n      g             *\n"
		<< "                         *         ssss     o       o    n  n n     g    ggg       *\n"
		<< "                         *             s     o     o     n   nn      g    g        *\n"
		<< "                         *        sssss       ooooo      n    n       gggg         *\n"
		<< "                         **********************************************************\n";
	Console.gotoxy(21, 0);
	cout << "                         **********************************************************\n"
		<< "                         *      qqqq        u    u       iiiii        tttttt      *\n"
		<< "                         *     q    q       u    u         i            tt        *\n"
		<< "                         *     q  q q       u    u         i            tt        *\n"
		<< "                         *     q   qq       u    u         i            tt        *\n"
		<< "                         *      qqqq q       uuuu        iiiii          tt        *\n"
		<< "                         **********************************************************\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	Console.gotoxy(6, 0);
	cout << "                         **********************************************************\n"
		<< "                         *                  1. green   A++++ B####                *\n"
		<< "                         *                  2. pink    A++++ B####                *\n"
		<< "                         *                  3. red     A++++ B####                *\n"
		<< "                         *                  4. yellow(default)                    *\n"
		<< "                         *                       type :                           *\n"
		<< "                         **********************************************************\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	while (1) {
		Sleep(100);
		if (GetAsyncKeyState(VK_DOWN) && enter == 1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(6, 0);
			cout << "                         **********************************************************\n"
				<< "                         *                  1. green   A++++ B####                *\n"
				<< "                         *                  2. pink    A++++ B####                *\n"
				<< "                         *                  3. red     A++++ B####                *\n"
				<< "                         *                  4. yellow(default)                    *\n"
				<< "                         *                       type :                           *\n"
				<< "                         **********************************************************\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(13, 0);
			cout << "                         **********************************************************\n"
				<< "                         *         sssss      ooooo      nn   n       gggg         *\n"
				<< "                         *        s          o     o     n n  n      g             *\n"
				<< "                         *         ssss     o       o    n  n n     g    ggg       *\n"
				<< "                         *             s     o     o     n   nn      g    g        *\n"
				<< "                         *        sssss       ooooo      n    n       gggg         *\n"
				<< "                         **********************************************************\n";
			enter = 2;
		}
		else if (GetAsyncKeyState(VK_DOWN) && enter == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(13, 0);
			cout << "                         **********************************************************\n"
				<< "                         *         sssss      ooooo      nn   n       gggg         *\n"
				<< "                         *        s          o     o     n n  n      g             *\n"
				<< "                         *         ssss     o       o    n  n n     g    ggg       *\n"
				<< "                         *             s     o     o     n   nn      g    g        *\n"
				<< "                         *        sssss       ooooo      n    n       gggg         *\n"
				<< "                         **********************************************************\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(21, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      qqqq        u    u       iiiii        tttttt      *\n"
				<< "                         *     q    q       u    u         i            tt        *\n"
				<< "                         *     q  q q       u    u         i            tt        *\n"
				<< "                         *     q   qq       u    u         i            tt        *\n"
				<< "                         *      qqqq q       uuuu        iiiii          tt        *\n"
				<< "                         **********************************************************\n";
			enter = 3;
		}
		else if (GetAsyncKeyState(VK_UP) && enter == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(13, 0);
			cout << "                         **********************************************************\n"
				<< "                         *         sssss      ooooo      nn   n       gggg         *\n"
				<< "                         *        s          o     o     n n  n      g             *\n"
				<< "                         *         ssss     o       o    n  n n     g    ggg       *\n"
				<< "                         *             s     o     o     n   nn      g    g        *\n"
				<< "                         *        sssss       ooooo      n    n       gggg         *\n"
				<< "                         **********************************************************\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(6, 0);
			cout << "                         **********************************************************\n"
				<< "                         *                  1. green   A++++ B####                *\n"
				<< "                         *                  2. pink    A++++ B####                *\n"
				<< "                         *                  3. red     A++++ B####                *\n"
				<< "                         *                  4. yellow(default)                    *\n"
				<< "                         *                       type :                           *\n"
				<< "                         **********************************************************\n";
			enter = 1;
		}
		else if (GetAsyncKeyState(VK_UP) && enter == 3) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(21, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      qqqq        u    u       iiiii        tttttt      *\n"
				<< "                         *     q    q       u    u         i            tt        *\n"
				<< "                         *     q  q q       u    u         i            tt        *\n"
				<< "                         *     q   qq       u    u         i            tt        *\n"
				<< "                         *      qqqq q       uuuu        iiiii          tt        *\n"
				<< "                         **********************************************************\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(13, 0);
			cout << "                         **********************************************************\n"
				<< "                         *         sssss      ooooo      nn   n       gggg         *\n"
				<< "                         *        s          o     o     n n  n      g             *\n"
				<< "                         *         ssss     o       o    n  n n     g    ggg       *\n"
				<< "                         *             s     o     o     n   nn      g    g        *\n"
				<< "                         *        sssss       ooooo      n    n       gggg         *\n"
				<< "                         **********************************************************\n";
			enter = 2;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && enter == 1) {
			buf.main_set_color();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Console.gotoxy(6, 0);
			cout << "                         **********************************************************\n"
				<< "                         *                  1. green   A++++ B####                *\n"
				<< "                         *                  2. pink    A++++ B####                *\n"
				<< "                         *                  3. red     A++++ B####                *\n"
				<< "                         *                  4. yellow(default)                    *\n"
				<< "                         *                       type :                           *\n"
				<< "                         **********************************************************\n";
			
		}
		else if (GetAsyncKeyState(VK_RIGHT) && enter == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			buf.main_set_song();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(13, 0);
			cout << "                         **********************************************************\n"
				<< "                         *         sssss      ooooo      nn   n       gggg         *\n"
				<< "                         *        s          o     o     n n  n      g             *\n"
				<< "                         *         ssss     o       o    n  n n     g    ggg       *\n"
				<< "                         *             s     o     o     n   nn      g    g        *\n"
				<< "                         *        sssss       ooooo      n    n       gggg         *\n"
				<< "                         **********************************************************\n";
			
		}
		else if (GetAsyncKeyState(VK_RIGHT) && enter == 3) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Console.gotoxy(6, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      ssss     tttttt     aa       rrrr     tttttt      *\n"
				<< "                         *     s           tt      a  a     r    r      tt        *\n"
				<< "                         *      sss        tt     aaaaaa    rrrrr       tt        *\n"
				<< "                         *         s       tt    a      a   r   r       tt        *\n"
				<< "                         *     ssss        tt   a        a  r    r      tt        *\n"
				<< "                         **********************************************************\n";
			Console.gotoxy(13, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      ssss eeeee tttttt tttttt iii  nn   n    gggg      *\n"
				<< "                         *     s     e       tt     tt    i   n n  n   g          *\n"
				<< "                         *      sss  eeeee   tt     tt    i   n  n n  g    ggg    *\n"
				<< "                         *         s e       tt     tt    i   n   nn   g    g     *\n"
				<< "                         *     ssss  eeeee   tt     tt   iii  n    n    gggg      *\n"
				<< "                         **********************************************************\n";
			Console.gotoxy(21, 0);
			cout << "                         **********************************************************\n"
				<< "                         *      qqqq        u    u       iiiii        tttttt      *\n"
				<< "                         *     q    q       u    u         i            tt        *\n"
				<< "                         *     q  q q       u    u         i            tt        *\n"
				<< "                         *     q   qq       u    u         i            tt        *\n"
				<< "                         *      qqqq q       uuuu        iiiii          tt        *\n"
				<< "                         **********************************************************\n";
			return;
		}
	}
} //�������
void BUFFERING::main_set_color() {
	cin.clear();
	int n;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	Console.gotoxy(6, 0);
	cout << "                         **********************************************************\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "                         *                  1. green   A++++ B####                *\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	cout << "                         *                  2. pink    A++++ B####                *\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "                         *                  3. red     A++++ B####                *\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "                         *                  4. yellow(default)                    *\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "                         *                       type :                           *\n";
	cout << "                         **********************************************************\n";
	Console.gotoxy(11, 55); cin >> n;
	switch (n) {
	case 1: buf.setcolor(10); break;
	case 2: buf.setcolor(13); break;
	case 3: buf.setcolor(12); break;
	case 4: buf.setcolor(14); break;
	default: buf.setcolor(14); break;
	}
	cin.clear();
	return;
}
void BUFFERING::main_set_song() {
	cin.clear();
	int n;
	Console.gotoxy(13, 0);
	cout << "                         **********************************************************\n"
	   	 << "                         *                   ��  1.  Happy Day  ��                *\n"
		 << "                         *                  ��  2.  Beautiful   ��                *\n"
		 << "                         *                  ��   3.    Beat     ��                *\n"
		 << "                         *                  ��  4. Party Time  ��                 *\n"
		 << "                         *                       type :                           *\n"
		 << "                         **********************************************************\n";
	Console.gotoxy(18, 55); cin >> n;
	switch (n) {
	case 1: soundchoice = 1; buf.sound(); break;
	case 2: soundchoice = 2; buf.sound(); break;
	case 3: soundchoice = 3; buf.sound(); break;
	case 4: soundchoice = 4; buf.sound(); break;
	default: soundchoice = rand() % 4 + 1; break;
	}
}
void BUFFERING::readymonitor() {
	// ���� �б� �غ�
		ifstream in("beginnig.txt");
		string s;

		if (in.is_open()) {
			// ��ġ �����ڸ� ���� ������ �ű��.
			in.seekg(0, ios::end);
			// �׸��� �� ��ġ�� �д´�. (������ ũ��)
			int size = in.tellg();
			// �� ũ���� ���ڿ��� �Ҵ��Ѵ�.
			s.resize(size);
			// ��ġ �����ڸ� �ٽ� ���� �� ������ �ű��.
			in.seekg(0, ios::beg);
			// ���� ��ü ������ �о ���ڿ��� �����Ѵ�.
			in.read(&s[0], size);
			cout << s << endl;
		}
		else {
			cout << "������ ã�� �� �����ϴ�!" << endl;
		}
	
	system("pause");
	buf.clear();
}
void BUFFERING::infomonitor() {
	Console.gotoxy(0, 122); cout << "+-------------+";
	Console.gotoxy(1, 122); cout << "|  char : " << mych << "   |";
	Console.gotoxy(2, 122); cout << "|  life : " << setw(2) <<life << "  |";
	Console.gotoxy(3, 122); cout << "|  turn : " << turn_interface << "   |";
	Console.gotoxy(4, 122); cout.precision(1); cout << "|  per : " << setw(3) << CC.mapPercent() << " |";
	Console.gotoxy(5, 122); cout << "+-------------+";
}
void BUFFERING::Rulemonitor() {
	for (int i = 0; i <= 20; i++) {
		cout << rulemon[i] << '\n';
	}
	system("pause");
	buf.clear();
}
void BUFFERING::failmonitor() {
	ifstream in("fail.txt");
	string s;

	if (in.is_open()) {
		// ��ġ �����ڸ� ���� ������ �ű��.
		in.seekg(0, ios::end);
		// �׸��� �� ��ġ�� �д´�. (������ ũ��)
		int size = in.tellg();
		// �� ũ���� ���ڿ��� �Ҵ��Ѵ�.
		s.resize(size);
		// ��ġ �����ڸ� �ٽ� ���� �� ������ �ű��.
		in.seekg(0, ios::beg);
		// ���� ��ü ������ �о ���ڿ��� �����Ѵ�.
		in.read(&s[0], size);
		cout << s << endl;
	}
	else {
		cout << "������ ã�� �� �����ϴ�!" << endl;
	}

	system("pause");
	buf.clear();
}
void BUFFERING::winmonitor() {
	ifstream in("win.txt");
	string s;

	if (in.is_open()) {
		// ��ġ �����ڸ� ���� ������ �ű��.
		in.seekg(0, ios::end);
		// �׸��� �� ��ġ�� �д´�. (������ ũ��)
		int size = in.tellg();
		// �� ũ���� ���ڿ��� �Ҵ��Ѵ�.
		s.resize(size);
		// ��ġ �����ڸ� �ٽ� ���� �� ������ �ű��.
		in.seekg(0, ios::beg);
		// ���� ��ü ������ �о ���ڿ��� �����Ѵ�.
		in.read(&s[0], size);
		cout << s << endl;
	}
	else {
		cout << "������ ã�� �� �����ϴ�!" << endl;
	}

	system("pause");
	buf.clear();
}
void BUFFERING::sound() {
	if (soundchoice == 1)
		PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (soundchoice==2)
		PlaySound(TEXT(SOUND_FILE_NAME2), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (soundchoice == 3)
		PlaySound(TEXT(SOUND_FILE_NAME3), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if(soundchoice == 3)
		PlaySound(TEXT(SOUND_FILE_NAME4), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

}
