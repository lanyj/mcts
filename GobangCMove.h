#pragma once
#include "CMove.h"
class GobangCMove : public CMove
{
public:
	int x;
	int y;
	GobangCMove(int x, int y);
	GobangCMove* clone();
	bool equals(CMove* m);
	bool equals(GobangCMove* l, GobangCMove* r);
	void toString();
	~GobangCMove();
};

