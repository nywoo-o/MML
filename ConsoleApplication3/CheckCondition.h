#pragma once
#ifndef CHECKCONDITION_H
#define CHECKCONDITION_H
#include <ctime>

class CheckCondition
{
public:
	CheckCondition();
	~CheckCondition();

	void saveVec();
	void IFArriveFinish();
	void TimeoverAndEdgeover();
	void failOrWin();
	double mapPercent();
};
extern class CheckCondition CC;
extern clock_t statrtime;
extern clock_t checktime;
extern double mapcounting;
#endif