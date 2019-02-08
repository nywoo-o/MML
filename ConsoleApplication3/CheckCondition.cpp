#include "network.h"
#include "console.h"
#include "CheckCondition.h"

clock_t statrtime;
clock_t checktime;
double mapcounting = 0;

CheckCondition::CheckCondition()
{
}
CheckCondition::~CheckCondition()
{
}

void CheckCondition::saveVec() {
	if (back != now && abs(back - now) != 1) {
		if (!position.empty() && position.back() != post) {
			position.push_back(make_pair(post.first, post.second));
		}
		else if (position.empty())
			position.push_back(make_pair(post.first, post.second));
	}
}
void CheckCondition::IFArriveFinish() {
	if (finish.first != -1 && finish.second != -1)
	{
		if (position.size() == 2) 
		{ //직선 루트
			statrtime = clock();
			back = startp_d; now = startp_d;
			newmap[y][x] = map[y][x];
			y = start.first; x = start.second;
			finish = { -1, -1 };
			while (!s.empty()) {
				newmap[s.top().first][s.top().second] = ' ';
				s.pop();
			}
			newmap[start.first][start.second] = mych;
			position.clear(); s.push(start);
			life--; //목숨깎임
			Item.createItem();
		}

		else if (position.size() == 1)
		{//땅 내에서 이동중
			statrtime = clock();
			back = startp_d; now = startp_d;
			start = { y, x };
			finish = { -1, -1 };
			position.clear();
			while (!s.empty()) s.pop();
			s.push(start);
		}
		else 
		{//벽에 도달
			statrtime = clock();
			back = startp_d; now = startp_d;
			start = finish;
			finish = { -1, -1 };
			position.clear();
			while (!s.empty()) s.pop();
			s.push(start);
			ending[0] = '!';
		}
	}
}
void CheckCondition::TimeoverAndEdgeover() {
	if (!position.empty() &&
		(position.size() >= 4 || (checktime - statrtime) / CLOCKS_PER_SEC >= 10)) {
		statrtime = clock();
		back = startp_d; now = startp_d;
		newmap[y][x] = ' ';
		y = start.first; x = start.second;
		while (!s.empty()) {
			newmap[s.top().first][s.top().second] = ' ';
			s.pop();
		}
		newmap[start.first][start.second] = mych;
		s.push(start);
		position.clear();
		life--; //목숨깎임
	}
}
double CheckCondition::mapPercent() {
	return (mapcounting / 3861) * 100;
}
void CheckCondition::failOrWin() {
	if ( life <= 0 || buffer[0] == '`' ){
		//상대방이 승리라 내가 페일인 경우) 
		buf.clear();
		if (life <= 0)
		{
			ending[0] = '~';
			send(Connection1, ending, sizeof(ending), NULL);// 상대방에 승리화면 표시
		}
		allfin = true; // 완전 끝났다 게임이
	    buf.failmonitor();

	}
	else if (CC.mapPercent() >= 50 || buffer[0] == '~') {
		buf.clear();
		if (CC.mapPercent() >= 50)
		{
			ending[0] = '`';
			send(Connection1, ending, sizeof(ending), NULL); //상대방에 페일화면 표시
		}
		allfin = true;
		buf.winmonitor();
	}
}

