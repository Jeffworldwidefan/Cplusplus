#pragma once
#include "main.h"

class RPG {
public:
	int roll(int min, int max)
	{
		random_device rd;
		int x;
		int y;
		if (min > 0)
		{
			x = min + 1;
			y = min;


		}
		else if(min == 0) {
			y = 0;
			x = max + 1;
		}
		return rd() % x + y;
	}
};