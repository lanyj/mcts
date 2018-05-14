#pragma once

#include "CMove.h"
#include "CList.h"

class OXOCMove : public CMove {
public:
	int move;

	OXOCMove(int move);

	bool equals(CMove *m);

	bool equals(OXOCMove *l, OXOCMove *r);

	void toString();

	OXOCMove* clone();
};
