#include "stdafx.h"
#include "OthelloCMove.h"


OthelloCMove::OthelloCMove(int x, int y) {
	this->x = x;
	this->y = y;
}

bool OthelloCMove::equals(CMove* m) {
	return x == ((OthelloCMove*) m)->x && y == ((OthelloCMove*) m)->y;
}

bool OthelloCMove::equals(OthelloCMove* l, OthelloCMove* r) {
	return l->x == r->x && l->y == r->y;
}

void OthelloCMove::toString() {
	printf("(%d, %d)", x, y);
}

OthelloCMove* OthelloCMove::clone() {
	OthelloCMove* move = new OthelloCMove(this->x, this->y);
	return move;
}
