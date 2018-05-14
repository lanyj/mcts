#pragma once

#include <time.h>
#include "stdafx.h"
#include "CList.h"
#include "CException.h"
#include "CMove.h"
#include "CBoard.h"
#include "CUtils.h"
#include "CNode.h"


class CUCT {
private:
	static void* getCNode(const void *list, int index);
	static void exchangeCNode(const void *list, int i, int j);
	static int compareToCNode(const void* l, const void* r);

public:

	static int random(int bounds);

	static CNode* randomChoiceCNode(CList<CNode*> *list);

	static CMove* randomChoiceCMove(CList<CMove*> *list);

	static CMove* uctMove(CBoard* _board, int itermax);

	static void clearUp(CNode* root);

	static void uctPlayGame();

	static CNode* select(CNode* root, CBoard* board);

	static CNode* expansion(CNode* root, CBoard* board);

	static double simulation(CNode* root, CBoard* board);

	static void backUp(CNode* node, double res);
};
