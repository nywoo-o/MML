#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H
//____define the entry point____//

#pragma comment(lib, "winmm.lib")

#include "stdafx.h"
#include <Windows.h>
#include "BUFFERING.h"
#include "item.h"
#include "CheckCondition.h"
#include <stdlib.h>
#include <ctime>
#include <string>
#include <mmsystem.h>
#include <vector>
#include <iostream>
#include <stack>

#define SOUND_FILE_NAME ".\\HappyDay.wav"
#define SOUND_FILE_NAME2 ".\\Beautifu.wav"
#define SOUND_FILE_NAME3 ".\\Beat.wav"
#define SOUND_FILE_NAME4 ".\\PartyTim.wav"
using namespace std;

class console
{
private:
	int ymax, ymin, xmax, xmin;
public:
	console();
	~console();
	void Move(int v, int h, char ch);
	void fill(int ycm, int xcm, char ch);
	void findingMinMax(vector <pair<int,  int>> vec, int size);
	void gotoxy(int vy, int hx);
	void GetTheKEY();
	void Movefinish(char ch);
};


extern class console Console;
extern char map[35][121] ,newmap[35][121] ,defaultmap[35][121];
extern bool checkmap[35][121];
extern int x, y;
extern int life;
extern char mych;
extern bool allfin;
extern enum direction { startp_d, space1_d, up_d, down_d, space2_d, right_d, left_d };
extern direction now; extern direction back;
extern pair<int, int> start; extern pair<int, int> finish; extern vector<pair<int, int>> position;
extern pair <int, int> post; //Àü ÁÂÇ¥ ÀúÀå
extern stack <pair<int, int>> s;
//extern int startpy, startpx;
#endif
