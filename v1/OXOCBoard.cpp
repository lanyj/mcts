#include "stdafx.h"
#include "OXOCBoard.h"

OXOCBoard::OXOCBoard() {
	memset(_board, 0, sizeof(_board));
	player = 2;
}

CList<CMove*>* OXOCBoard::getMoves() {
	CList<CMove*> *list = new CList<CMove*>();
	for (int i = 0; i < 9; i++) {
		if (_board[i] == 0) {
			list->add(new OXOCMove(i));
		}
	}
	return list;
}

bool OXOCBoard::isGameOver() {
	if (getResult(player) != _NO_PLAYER_WIN_) {
		return true;
	}
	for (int i = 0; i < 9; i++) {
		if (_board[i] == 0) {
			return false;
		}
	}
	return true;
}

double OXOCBoard::getResult(int player) {
	int TEST[8][3] = { { 0, 1, 2 },{ 3, 4, 5 },{ 6, 7, 8 },{ 0, 3, 6 },{ 1, 4, 7 },{ 2, 5, 8 },
	{ 0, 4, 8 },{ 2, 4, 6 } };
	for (int i = 0; i < 8; i++) {
		int* p = TEST[i];
		if (_board[p[0]] == _board[p[1]] && _board[p[1]] == _board[p[2]]) {
			if (_board[p[0]] == player) {
				return _PLAYER_WIN_;
			}
			else if (_board[p[0]] == 3 - player) {
				return _PLAYER_LOSE_;
			}
		}
	}
	return _NO_PLAYER_WIN_;
}

OXOCBoard* OXOCBoard::clone() {
	OXOCBoard* b = new OXOCBoard();
	b->player = this->player;
	memcpy(b->_board, this->_board, sizeof(this->_board));
	return b;
}

void OXOCBoard::applyMove(CMove* _move) {
	OXOCMove* move = (OXOCMove*) _move;
	if (move->move >= 0 && move->move < 9 && _board[move->move] == 0) {
		_board[move->move] = player;
		player = 3 - player;
		return;
	}
	CIllegalStateException* e = new CIllegalStateException("IllegalStateException on OXOCBoard::applyMove(OXOCMove* move)");
	e->printMsg();
}

int OXOCBoard::getCurrentPlayer() {
	return player;
}

void OXOCBoard::printCBoard() {
	char c[3] = { '.', 'X', 'O' };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%c ", c[_board[i * 3 + j]]);
		}
		printf("\n");
	}
}