#include "stdafx.h"
#include "GobangCMove.h"


GobangCMove::GobangCMove(int x, int y) : CMove() {
	this->x = x;
	this->y = y;
}

bool GobangCMove::equals(CMove* m) {
	return x == ((GobangCMove*)m)->x && y == ((GobangCMove*)m)->y;
}

bool GobangCMove::equals(GobangCMove* l, GobangCMove* r) {
	return l->x == r->x && l->y == r->y;
}


GobangCMove* GobangCMove::clone() {
	GobangCMove* m = new GobangCMove(x, y);
//	m->x = this->x;
//	m->y = this->y;
	return m;
}

void GobangCMove::toString() {
	printf("(%d, %d)", x, y);
}

GobangCMove::~GobangCMove() {
}
