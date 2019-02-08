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
		{ //���� ��Ʈ
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
			life--; //�������
			Item.createItem();
		}

		else if (position.size() == 1)
		{//�� ������ �̵���
			statrtime = clock();
			back = startp_d; now = startp_d;
			start = { y, x };
			finish = { -1, -1 };
			position.clear();
			while (!s.empty()) s.pop();
			s.push(start);
		}
		else 
		{//���� ����
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
		life--; //�������
	}
}
double CheckCondition::mapPercent() {
	return (mapcounting / 3861) * 100;
}
void CheckCondition::failOrWin() {
	if ( life <= 0 || buffer[0] == '`' ){
		//������ �¸��� ���� ������ ���) 
		buf.clear();
		if (life <= 0)
		{
			ending[0] = '~';
			send(Connection1, ending, sizeof(ending), NULL);// ���濡 �¸�ȭ�� ǥ��
		}
		allfin = true; // ���� ������ ������
	    buf.failmonitor();

	}
	else if (CC.mapPercent() >= 50 || buffer[0] == '~') {
		buf.clear();
		if (CC.mapPercent() >= 50)
		{
			ending[0] = '`';
			send(Connection1, ending, sizeof(ending), NULL); //���濡 ����ȭ�� ǥ��
		}
		allfin = true;
		buf.winmonitor();
	}
}

