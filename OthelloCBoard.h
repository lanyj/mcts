#pragma once

#include "CBoard.h"
#include "CList.h"
#include "OthelloCMove.h"

#include "CList.cpp"


class OthelloCBoard : public CBoard {
public:
	int player;
	int* _board;
	int size;

	OthelloCBoard(int size);

	OthelloCBoard* clone();

	void applyMove(CMove* _move);

	bool isOnBorder(int x, int y);

	bool isGameOver();

	CMove* randomMove();

	CList<CMove*>* getMoves();

	bool adjacentToEnemy(int x, int y);

	CList<OthelloCMove*>* adjacentEnemyDirections(int x, int y);

	bool existsSandwichedCounter(int x, int y);

	CList<OthelloCMove*>* getAllSandwichedCounters(int x, int y);

	CList<OthelloCMove*>* sandwichedCounters(int x, int y, int dx, int dy);

	double getResult(int player);

	int getCurrentPlayer();

	void printCBoard();

	~OthelloCBoard();
};
