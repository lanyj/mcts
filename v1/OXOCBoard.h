#pragma once

#include "CBoard.h"
#include "CList.h"
#include "OXOCMove.h"

class OXOCBoard : public CBoard {
public:
	int _board[9] = { 0 };
	int player = 2;

	OXOCBoard();

	CList<CMove*>* getMoves();

	bool isGameOver();

	double getResult(int player);

	OXOCBoard* clone();

	void applyMove(CMove* move);

	int getCurrentPlayer();

	void printCBoard();
};
