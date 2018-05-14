#include "stdafx.h"
#include "OthelloCBoard.h"


OthelloCBoard::OthelloCBoard(int size) {
	this->size = size;
	player = 2;
	_board = (int *)calloc(size * size, sizeof(int));
	_board[size / 2 * size + size / 2] = _board[(size / 2 - 1) * size + size / 2 - 1] = 1;
	_board[size / 2 * size + size / 2 - 1] = _board[(size / 2 - 1) * size + size / 2] = 2;
}

OthelloCBoard* OthelloCBoard::clone() {
	OthelloCBoard* b = new OthelloCBoard(size);
	memcpy(b->_board, this->_board, sizeof(int) * size * size);
	b->player = this->player;
	return b;
}

void OthelloCBoard::applyMove(CMove* _move) {
	OthelloCMove *move = (OthelloCMove*)_move;
	if (isOnBorder(move->x, move->y) && _board[move->x * size + move->y] == 0) {
		CList<OthelloCMove*>* list = this->getAllSandwichedCounters(move->x, move->y);
		player = 3 - player;
		_board[move->x * size + move->y] = player;
		while (!list->isEmpty()) {
			OthelloCMove* m = list->removeLast();
			_board[m->x * size + m->y] = player;
			delete m;
		}
		delete list;
		return;
	}
	CIllegalStateException* e = new CIllegalStateException("IllegalStateException on OXOCBorder::applyMove(OXOCMove* move)");
	e->printMsg();
}

bool OthelloCBoard::isOnBorder(int x, int y) {
	return x >= 0 && y >= 0 && x < size && y < size;
}

bool OthelloCBoard::isGameOver() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (_board[i * size + j] == 0 && existsSandwichedCounter(i, j)) {
				return false;
			}
		}
	}
	return true;
}

CList<CMove*>* OthelloCBoard::getMoves() {
	CList<CMove*> *list = new CList<CMove*>();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (_board[i * size + j] == 0 && existsSandwichedCounter(i, j)) {
				list->add(new OthelloCMove(i, j));
			}
		}
	}
	return list;
}

bool OthelloCBoard::adjacentToEnemy(int x, int y) {
	int D[8][2] = { { 0, 1 },{ 1, 1 },{ 1, 0 },{ 1, -1 },{ 0, -1 },{ -1, -1 },{ -1, 0 },{ -1, 1 } };
	for (int i = 0; i < 8; i++) {
		int* p = D[i];
		if (isOnBorder(x + p[0], y + p[1]) && _board[(x + p[0]) * size + y + p[1]] == player) {
			return true;
		}
	}
	return false;
}

CList<OthelloCMove*>* OthelloCBoard::adjacentEnemyDirections(int x, int y) {
	CList<OthelloCMove*>* list = new CList<OthelloCMove*>();
	int D[8][2] = { { 0, 1 },{ 1, 1 },{ 1, 0 },{ 1, -1 },{ 0, -1 },{ -1, -1 },{ -1, 0 },{ -1, 1 } };
	for (int i = 0; i < 8; i++) {
		int* p = D[i];
		if (isOnBorder(x + p[0], y + p[1]) && _board[(x + p[0]) * size + y + p[1]] == player) {
			list->add(new OthelloCMove(p[0], p[1]));
		}
	}
	return list;
}

bool OthelloCBoard::existsSandwichedCounter(int x, int y) {
	CList<OthelloCMove*> *moves = this->adjacentEnemyDirections(x, y);
	while (!moves->isEmpty()) {
		OthelloCMove* m = moves->removeLast();
		int dx = m->x;
		int dy = m->y;
		delete m;
		CList<OthelloCMove*> *tmp = sandwichedCounters(x, y, dx, dy);
		int s = tmp->size();
		while (!tmp->isEmpty()) {
			delete tmp->removeLast();
		}
		delete tmp;
		if (s > 0) {
			while (!moves->isEmpty()) {
				delete moves->removeLast();
			}
			delete moves;
			return true;
		}
	}
	delete moves;
	return false;
}

CList<OthelloCMove*>* OthelloCBoard::getAllSandwichedCounters(int x, int y) {
	CList<OthelloCMove*>* list = new CList<OthelloCMove*>();
	CList<OthelloCMove*> *moves = this->adjacentEnemyDirections(x, y);
	while (!moves->isEmpty()) {
		OthelloCMove* m = moves->removeLast();
		int dx = m->x;
		int dy = m->y;
		delete m;
		CList<OthelloCMove*> *tmp = sandwichedCounters(x, y, dx, dy);
		while (!tmp->isEmpty()) {
			list->add(tmp->removeLast());
		}
		delete tmp;
	}
	delete moves;
	return list;
}

CList<OthelloCMove*>* OthelloCBoard::sandwichedCounters(int x, int y, int dx, int dy) {
	CList<OthelloCMove*>* list = new CList<OthelloCMove*>();
	x += dx;
	y += dy;
	while (this->isOnBorder(x, y) && _board[x * size + y] == player) {
		list->add(new OthelloCMove(x, y));
		x += dx;
		y += dy;
	}
	if (this->isOnBorder(x, y) && _board[x * size + y] == 3 - player) {
		return list;
	}
	else {
		while (!list->isEmpty()) {
			delete list->removeLast();
		}
	}
	return list;
}

double OthelloCBoard::getResult(int player) {
	if (!isGameOver()) {
		return 0;
	}
	int pc = 0, npc = 0;
	for (int i = 0; i < size * size; i++) {
		if (_board[i] == player) {
			pc++;
		}
		else if (_board[i] == 3 - player) {
			npc++;
		}
	}
	if (pc > npc) {
		return _PLAYER_WIN_;
	}
	else if (pc < npc) {
		return _PLAYER_LOSE_;
	}
	else {
		return _NO_PLAYER_WIN_;
	}
}
int OthelloCBoard::getCurrentPlayer() {
	return player;
}
void OthelloCBoard::printCBoard() {
	char c[3] = { '.', 'X', 'O' };
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%c ", c[_board[i * size + j]]);
		}
		printf("\n");
	}
}
OthelloCBoard::~OthelloCBoard() {
	free(_board);
}

