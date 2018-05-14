#include "stdafx.h"
#include "OXOCMove.h"

OXOCMove::OXOCMove(int move) {
	this->move = move;
}

bool OXOCMove::equals(CMove *m) {
	return move == ((OXOCMove*) m)->move;
}

bool OXOCMove::equals(OXOCMove *l, OXOCMove *r) {
	return l->move == r->move;
}

void OXOCMove::toString() {
	printf("(%d)", move);
}

OXOCMove* OXOCMove::clone() {
	OXOCMove* move = new OXOCMove(this->move);
	return move;
}
