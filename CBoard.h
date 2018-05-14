#pragma once

#include "CList.h"
#include "CMove.h"


#define _PLAYER_WIN_ 1
#define _PLAYER_LOSE_ -1
#define _NO_PLAYER_WIN_ 0

class CBoard {
public:

	virtual CMove* randomMove() = 0;

	virtual CList<CMove*>* getMoves() = 0;

	virtual bool isGameOver() = 0;

	virtual double getResult(int player) = 0;

	virtual CBoard* clone() = 0;

	virtual void applyMove(CMove* move) = 0;

	virtual int getCurrentPlayer() = 0;

	virtual void printCBoard() = 0;

	virtual ~CBoard();
};
