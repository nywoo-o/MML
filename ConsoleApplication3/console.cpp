#include "network.h"
#include "console.h"
vector<pair<int, int>> position;
enum direction; //{startp_d, space1_d, up_d, down_d, space2_d, right_d, left_d};
enum direction now = startp_d; enum direction back = startp_d;
stack <pair<int, int>> s;
pair <int, int> start;
pair <int, int> finish = { -1,-1 };
pair <int, int> post;
int x, y; char mych; int life = 15;
bool allfin = 0;
char newmap[35][121]=
{
	{ "*---------------------------------------------------------------------------------------------------------------------*" },
	{ "|A                                                                                                                   B|" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },                                                                                                 
    { "|                                                                                                                     |" },                                                                                               
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "*---------------------------------------------------------------------------------------------------------------------*" }
};
char map[35][121] =
{
	{ "*---------------------------------------------------------------------------------------------------------------------*" },
	{ "|A                                                                                                                   B|" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "*---------------------------------------------------------------------------------------------------------------------*" }
};
char defaultmap[35][121] = {
	{ "*---------------------------------------------------------------------------------------------------------------------*" },
	{ "|A                                                                                                                   B|" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "|                                                                                                                     |" },
	{ "*---------------------------------------------------------------------------------------------------------------------*" }
};

//체크맵으로 최대 최소 범위 내의 칸은 다 찍게
//그렇지만 한 번 찍은 곳을 또 가지는 않도록 찍은 칸은 1로 바꿔서 제한시킴
bool checkmap[35][121] = { 0 };

console::console()
{
}
console::~console()
{
}

void console::Movefinish(char ch) {
	finish = make_pair(y, x);
	position.push_back(finish);

	if (finish.first != -1 && finish.second != -1 && position.size() > 1) {
		xmax = 0; xmin = 0; ymax = 0; ymin = 0;
		findingMinMax(position, position.size());

		int xcmx = (int)((xmax + xmin) / 2);
		int ycmy = (int)((ymax + ymin) / 2);

		if (newmap[ycmy][xcmx] != ch) {
			if (ch == 'A') {
				fill(ycmy, xcmx, '+');
			}
			else if (ch == 'B') {
				fill(ycmy, xcmx, '#');
			}
		}
		memset(checkmap, false, 35 * 121);
	}
}
void console::Move(int v, int h, char ch)
{
	int x2 = x + h;
	int y2 = y + v;
	//move 확인을 위한
	
	//A면 B땅을 먹을 수 있도록 설정하기 위해
	if (ch == 'A' && (newmap[y][x2] == '|' || newmap[y2][x] == '-' || newmap[y2][x2] == '+'))
	{//테두리에 도달하면 finish에 좌표값 입력
		Console.Movefinish(ch);
	}
	else if (ch == 'B' && (newmap[y][x2] == '|' || newmap[y2][x] == '-' || newmap[y2][x2] == '#')) 
	{
		Console.Movefinish(ch);
	}

	if (newmap[y2][x2] == '$') {
		selectitem = rand() % 4;
		switch (selectitem) {
		case 0:	Item.eT_monitor(); Item.extraTime(); break;
		case 1: Item.MMC_monitor(); Item.MyMapClear(); newmap[y2][x2] = ' '; return; break;
		case 2: Item.NYT_monitor(); Item.NotYourTurn(); break;
		case 3: Item.eL_monitor(); Item.extraLife(); break;
		default: break;
		}
	}

	if (newmap[y][x2] == ' ' || newmap[y][x2] == '+' || newmap[y][x2] =='#' ||newmap[y][x2] == '$') { //A가 이동하는 루트 표시
		if (ch == 'A') {
			newmap[y][x] = '+';
		}
		else if (ch == 'B') {
			newmap[y][x] = '#';
		}
		x += h; 
		newmap[y][x] = ch;		
	}

	if (newmap[y2][x] == ' ' || newmap[y2][x] == '+' || newmap[y2][x] =='#' || newmap[y2][x] == '$') {
		if (ch == 'A') {
			newmap[y][x] = '+';			
		}
		else if (ch == 'B') {
			newmap[y][x] = '#';		
		}		y += v;
		newmap[y][x] = ch;
	}

}
void console::fill(int y, int x, char ch) {
	if(checkmap[y][x] != 1 && newmap[y][x] != '|' && newmap[y][x] != '-' 
		&& newmap[y][x] != 'A' && newmap[y][x] != 'B') {
		newmap[y][x] = ch; checkmap[y][x] = 1;
	}
	if(checkmap[y-1][x] != 1 && y - 1 >= ymin && x >= xmin && x <= xmax 
		&& newmap[y-1][x] != 'A' && newmap[y-1][x] != 'B'){
		fill(y - 1, x ,ch); 
	}
	if(checkmap[y+1][x] != 1 && y + 1 <= ymax && x >= xmin && x <= xmax 
		&& newmap[y+1][x] != 'A' && newmap[y+1][x] != 'B'){
		fill(y + 1, x, ch);
	}
	if(checkmap[y][x-1] != 1 && y >= ymin && y <= ymax && x - 1 >= xmin 
		&& newmap[y][x-1] != 'A' && newmap[y][x-1] != 'B'){
		fill(y, x - 1, ch);
	}
	if(checkmap[y][x+1] != 1 && y >= ymin && y <= ymax && x + 1 <= xmax 
		&& newmap[y][x+1] != 'A' && newmap[y][x+1] != 'B'){
		fill(y, x + 1, ch);
	}
}
void console::findingMinMax(vector<pair<int, int>> vec, int size) {

	if (position.size() == 4) {
		ymax = vec[1].first; ymin = vec[1].first;
		xmax = vec[1].second; xmin = vec[1].second;
		for (int i = 1; i < size; i++) {
			if (ymax < vec[i].first) ymax = vec[i].first;
			if (ymin > vec[i].first) ymin = vec[i].first;
			if (xmax < vec[i].second) xmax = vec[i].second;
			if (xmin > vec[i].second) xmin = vec[i].second;
		}
	}
	else {
		ymax = vec[0].first; ymin = vec[0].first;
		xmax = vec[0].second; xmin = vec[0].second;
		for (int i = 0; i < size; i++) {
			if (ymax < vec[i].first) ymax = vec[i].first;
			if (ymin > vec[i].first) ymin = vec[i].first;
			if (xmax < vec[i].second) xmax = vec[i].second;
			if (xmin > vec[i].second) xmin = vec[i].second;
		}
	}
}
void console::gotoxy(int vy, int hx) {
	COORD pos;
	pos.X = hx;
	pos.Y = vy;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void console::GetTheKEY() {
	if (GetAsyncKeyState(VK_UP)) {
		if (abs(back - now) != 1) back = now; //지가 온길로 바로 못가게 ㅇㅇㅋ
		now = up_d;
		if (abs(back - now) != 1) Console.Move(-1, 0, mych);
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
		if (abs(back - now) != 1) back = now;
		now = down_d;
		if (abs(back - now) != 1) Console.Move(1, 0, mych);
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		if (abs(back - now) != 1) back = now;
		now = left_d;
		if (abs(back - now) != 1) Console.Move(0, -1, mych);
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		if (abs(back - now) != 1) back = now;
		now = right_d;
		if (abs(back - now) != 1) Console.Move(0, 1, mych);
	}
}