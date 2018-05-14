#pragma once

#include "CMove.h"
#include "CList.h"


class OthelloCMove : public CMove {
public:
	int x;
	int y;

	OthelloCMove(int x, int y);

	bool equals(CMove* m);

	bool equals(OthelloCMove* l, OthelloCMove* r);

	void toString();

	OthelloCMove* clone();
};
