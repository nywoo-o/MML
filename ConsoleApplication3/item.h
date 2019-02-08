#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <time.h>
#include <stdlib.h>
class item
{
public:
	item();
	~item();
	void createItem();
	void extraTime();
	void MyMapClear();
	void NotYourTurn();
	void extraLife();
	void eT_monitor();
	void eL_monitor();
	void NYT_monitor();
	void MMC_monitor();
};
extern class item Item;
extern int selectitem;

extern clock_t boStartTime, boEndTime;
extern int blackout;
#endif