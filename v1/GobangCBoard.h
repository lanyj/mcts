#pragma once
#include "CBoard.h"
#include "GobangCMove.h"

class GobangCBoard : public CBoard
{
private:
	int width;
	int height;
	int n_in_row;
	int player;
	int **_board;
public:
	GobangCBoard();
	CList<CMove*>* getMoves();
	bool isGameOver();
	bool testForWin(int i, int j, int player);
	double getResult(int player);
	GobangCBoard* clone();
	void applyMove(CMove* move);
	bool isOnBoard(int x, int y);
	int getCurrentPlayer();
	void printCBoard();
	~GobangCBoard();
};

