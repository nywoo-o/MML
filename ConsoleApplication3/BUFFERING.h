#pragma once

#ifndef BUFFERING_H
#define BUFFERING_H
#include <Windows.h>
class BUFFERING
{
private:
	int color;
public:
	BUFFERING();
	~BUFFERING();

	void clear();
	void sound();
	void comparAndChange(char mych);
	void main_menu();
	void main_setting();
	void main_set_color();
	void main_set_song();
	void setcolor(int n) {
		color = n;
	};
	int getcolor() {
		return color;
	};
	void readymonitor();
	void infomonitor();
	void QuitOrContinue(char ch);
	void settingmon();
	void Rulemonitor();
	void failmonitor();
	void winmonitor();
};
extern class BUFFERING buf;
extern char turn_interface;
extern char rulemon[30][150];
extern int soundchoice;
#endif