#include "network.h"
#include "item.h"
#include "console.h"


int selectitem;

item::item()
{
}
item::~item()
{
}

void item::createItem() { //아이템 생성
	srand(rand() % 50 + 1);
	int howmany = rand() % 7 + 1;

	while (howmany--) {
		int xitem = rand() % 117 + 1;
		int yitem = rand() % 33 + 1;
		if (newmap[yitem][xitem] != mych && newmap[yitem][xitem] != '+' && newmap[yitem][xitem] != '#')
			newmap[yitem][xitem] = '$';
	}
}
void item::extraTime() {
	statrtime = clock();
}
void item::extraLife() {
	life += 10; //목숨을 10개 추가함
}
void item::MyMapClear() {
	for (int i = 1; i < 34; i++) { //맵 청소
		for (int j = 1; j < 119; j++) {
			if (mych == 'A'){
				if (newmap[i][j] == '+') newmap[i][j] = ' ';
			}
			else if (mych == 'B') {
				if (newmap[i][j] == '#') newmap[i][j] = ' ';
			}			
		}
	}
	newmap[y][x] = ' ';
	//위치초기화
	if (mych == 'A') {
		newmap[1][1] = mych; 
		y = 1; x = 1;
		start = { 1, 1 };
	}
	else if (mych == 'B') {
		newmap[1][117] = mych;
		y = 1; x = 117;
		start = { 1, 117 };
	}
	statrtime = clock();
	//방향 체크 및 모든 걸 처음상태로 초기화
	back = startp_d; now = startp_d;
	finish = { -1, -1 };
	position.clear();
	while (!s.empty()) s.pop();
	s.push(start);
}
void item::NotYourTurn() {
	ending[0] = '!';
}

void item::eT_monitor() {
	Console.gotoxy( 7, 122); cout << "588721522881";
	Console.gotoxy( 8, 122); cout << " 78      87";
	Console.gotoxy( 9, 122); cout << "  487  784";
	Console.gotoxy(10, 122); cout << "    5885";
	Console.gotoxy(11, 122); cout << "   207202";
	Console.gotoxy(12, 122); cout << "  87    78";
	Console.gotoxy(13, 122); cout << " 78      87";
	Console.gotoxy(14, 122); cout << "0884900048801";
	Sleep(1000);
	Console.gotoxy( 7, 121); cout << "             ";
	Console.gotoxy( 8, 122); cout << "             ";
	Console.gotoxy( 9, 121); cout << "             ";
	Console.gotoxy(10, 122); cout << "             ";
	Console.gotoxy(11, 121); cout << "             ";
	Console.gotoxy(12, 122); cout << "             ";
	Console.gotoxy(13, 121); cout << "             ";
	Console.gotoxy(14, 122); cout << "             ";
}
void item::MMC_monitor() {
	Console.gotoxy(7, 122); cout << "   *  §";
	Console.gotoxy(8, 122); cout << "             **";
	Console.gotoxy(9, 122); cout << " *        *";
	Console.gotoxy(10, 122); cout << "  ▶초기화◀  *";
	Console.gotoxy(11, 122); cout << "    **     §";
	Console.gotoxy(12, 122); cout << " §      *     *";
	Console.gotoxy(13, 122); cout << "      §";
	Sleep(1000);
	Console.gotoxy(7, 121); cout << "                ";
	Console.gotoxy(8, 122); cout << "                 ";
	Console.gotoxy(9, 121); cout << "                ";
	Console.gotoxy(10, 122); cout << "                ";
	Console.gotoxy(11, 121); cout << "                ";
	Console.gotoxy(12, 122); cout << "                 ";
	Console.gotoxy(13, 121); cout << "               ";
	Console.gotoxy(14, 122); cout << "               ";

}
void item::eL_monitor() {
	Console.gotoxy( 7, 122); cout << "      708889788";
	Console.gotoxy( 8, 122); cout << "    888888888888";
	Console.gotoxy( 9, 122); cout << "   78827788877288";
	Console.gotoxy(10, 122); cout << "  888     8     888";
	Console.gotoxy(11, 122); cout << "  888          7888";
	Console.gotoxy(12, 122); cout << "  88885       58888";
	Console.gotoxy(13, 122); cout << "   288887   788887";
	Console.gotoxy(14, 122); cout << "    788888 888887";
	Console.gotoxy(15, 122); cout << "      788888882";

	Sleep(1000);
	Console.gotoxy(7, 121); cout << "                     ";
	Console.gotoxy(8, 122); cout << "                     ";
	Console.gotoxy(9, 121); cout << "                     ";
	Console.gotoxy(10, 122); cout << "                    ";
	Console.gotoxy(11, 121); cout << "                    ";
	Console.gotoxy(12, 122); cout << "                    ";
	Console.gotoxy(13, 121); cout << "                    ";
	Console.gotoxy(14, 122); cout << "                    ";
	Console.gotoxy(15, 122); cout << "                    ";
}
void item::NYT_monitor() {
	Console.gotoxy(7, 122); cout << "   !   !!";
	Console.gotoxy(8, 122); cout << "  !           !";
	Console.gotoxy(9, 122); cout << "       !     !!!";
	Console.gotoxy(10, 122); cout << "  ▶턴강종◀";
	Console.gotoxy(11, 122); cout << "    !!     !";
	Console.gotoxy(12, 122); cout << " !      !     !";
	Console.gotoxy(13, 122); cout << "      !!!";

	Sleep(1000);
	Console.gotoxy(7, 121); cout << "               ";
	Console.gotoxy(8, 122); cout << "               ";
	Console.gotoxy(9, 121); cout << "               ";
	Console.gotoxy(10, 122); cout << "               ";
	Console.gotoxy(11, 121); cout << "               ";
	Console.gotoxy(12, 122); cout << "                ";
	Console.gotoxy(13, 121); cout << "               ";
	Console.gotoxy(14, 122); cout << "               ";
}