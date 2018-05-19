#include "stdafx.h"
#include "GobangCBoard.h"


GobangCBoard::GobangCBoard(){
	width = 8;
	height = 8;
	n_in_row = 4;
	player = 2;
	_board = (int **) malloc(sizeof(int *) * width);
	for (int i = 0; i < width; i++) {
		_board[i] = (int *) malloc(sizeof(int) * height);
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			_board[i][j] = 0;
		}
	}
}
CList<CMove*>* GobangCBoard::getMoves() {
	CList<CMove*> *moves = new CList<CMove*>();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (_board[i][j] == 0) {
				moves->add(new GobangCMove(i, j));
			}
		}
	}
	return moves;
}
CMove* GobangCBoard::randomMove() {
	int sum = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (_board[i][j] == 0) {
				sum++;
			}
		}
	}
	if (sum == 0) {
		return NULL;
	}
	else {
		sum = rand() % sum;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (_board[i][j] == 0) {
					if (sum-- == 0) {
						return new GobangCMove(i, j);
					}
				}
			}
		}
	}
	return NULL;
}
bool GobangCBoard::isGameOver() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (_board[i][j] != 0) {
				if (testForWin(i, j, _board[i][j])) {
					return true;
				}
			}
		}
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (_board[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

bool GobangCBoard::testForWin(int i, int j, int player) {
	int n, x, y;
	// hor
	x = i;
	y = j;
	n = 0;
	while (true) {
		if (x >= 0 && _board[x][y] == player) {
			n++;
		}
		else {
			break;
		}
		x--;
	}
	x = i + 1;
	while (true) {
		if (x < width && _board[x][y] == player) {
			n++;
		}
		else {
			break;
		}
		x++;
	}
	if (n >= n_in_row) {
		return true;
	}
	// ver
	x = i;
	y = j;
	n = 0;
	while (true) {
		if (y >= 0 && _board[x][y] == player) {
			n++;
		}
		else {
			break;
		}
		y--;
	}
	y = j + 1;
	while (true) {
		if (y < height && _board[x][y] == player) {
			n++;
		}
		else {
			break;
		}
		y++;
	}
	if (n >= n_in_row) {
		return true;
	}
	// /
	x = i;
	y = j;
	n = 0;
	while (true) {
		if (x >= 0 && y >= 0 && _board[x][y] == player) {
			n++;
		}
		else {
			break;
		}
		x--;
		y--;
	}
	x = i + 1;
	y = j + 1;
	while (true) {
		if (x < width && y < height && _board[x][y] == player) {
			n++;
		}
		else {
			break;
		}
		x++;
		y++;
	}
	if (n >= n_in_row) {
		return true;
	}
	// \-

	x = i;
	y = j;
	n = 0;
	while (true) {
		if (isOnBoard(x, y) && _board[x][y] == player) {
			n++;
		}
		else {
			break;
		}
		x--;
		y++;
	}
	x = i + 1;
	y = j - 1;
	while (true) {
		if (isOnBoard(x, y) && _board[x][y] == player) {
			n++;
		}
		else {
			break;
		}
		x++;
		y--;
	}
	if (n >= n_in_row) {
		return true;
	}
	return false;
}

double GobangCBoard::getResult(int player) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (_board[i][j] != 0) {
				if (testForWin(i, j, _board[i][j])) {
					return _board[i][j] == player ? _PLAYER_WIN_ : _PLAYER_LOSE_;
				}
			}
		}
	}
	return _NO_PLAYER_WIN_;
}
GobangCBoard* GobangCBoard::clone() {
	GobangCBoard* b = new GobangCBoard();
	b->player = this->player;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			b->_board[i][j] = this->_board[i][j];
		}
	}
	return b;
}
void GobangCBoard::applyMove(CMove* move) {
	GobangCMove* m = (GobangCMove *)move;
	if (isOnBoard(m->x, m->y) && _board[m->x][m->y] == 0) {
		_board[m->x][m->y] = player; 
		player = 3 - player;
		return;
	}
	CIllegalStateException* e = new CIllegalStateException("IllegalStateException on OXOCBoard::applyMove(OXOCMove* move)");
	e->printMsg();
}

bool GobangCBoard::isOnBoard(int x,int y) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return true;
	}
	return false;
}

int GobangCBoard::getCurrentPlayer() {
	return player;
}
void GobangCBoard::printCBoard() {
	char c[3] = { '.', 'X', 'O' };
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			printf("%c ", c[_board[i][j]]);
		}
		printf("\n");
	}
}
GobangCBoard::~GobangCBoard(){
	for (int i = 0; i < width; i++) {
		free(_board[i]);
	}
	free(_board);
}
