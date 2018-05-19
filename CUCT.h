#pragma once

#include <shared_mutex>

#include <time.h>
#include "stdafx.h"
#include "CList.h"
#include "CException.h"
#include "CMove.h"
#include "CBoard.h"
#include "CUtils.h"
#include "CNode.h"

using namespace std;

#define MIN(x, y) x > y ? y : x

class CUCT {
private:
	
	static void* getCNode(const void *list, int index);
	static void exchangeCNode(const void *list, int i, int j);
	static int compareToCNode(const void* l, const void* r);
	static int random(int bounds);
	static CNode* randomChoiceCNode(CList<CNode*> *list);
	static CMove* randomChoiceCMove(CList<CMove*> *list);

	static void threadUCTMoveMethod(CNode* root, CBoard* _board, int itermax, int index, bool* arr);

	static CMove* uctMove(CBoard* _board, int itermax);

	static void auxClearUp(CNode* node);

	static void threadClearUp(CNode* node, int begin, int end, int index, bool* arr);

	static void clearUp(CNode* root);

	static CNode* select(CNode* root, CBoard* board);

	static CNode* expansion(CNode* root, CBoard* board);

	static double simulation(CNode* root, CBoard* board);

	static void backTrace(CNode* node, double res);

public:

	static void uctPlayGame();

};
