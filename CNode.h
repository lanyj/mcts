#pragma once

#include <shared_mutex>

#include "stdafx.h"
#include "CList.h"
#include "CBoard.h"
#include "CMove.h"
#include "CException.h"
#include "CUtils.h"
#include "CList.cpp"


class CNode {
private:
	static void* getCNode(const void *list, int index);
	static void exchangeCNode(const void *list, int i, int j);
	static int compareToCNode(const void* l, const void* r);
	static bool compareToCMove(CMove* l, CMove* r);
public:
	CNode * parent;
	CList<CNode*>* children;
	CList<double>* policy;
	double score;
	double visits;
	CMove* move;
	int player;

	CNode(CMove* move, CNode* parent, CBoard* board);

	CNode* uctSelectChild(CBoard* board);

	CNode* addNode(CMove* m, CBoard* board);

	void update(double result);

	void lock();

	void unlock();

	double value();

	~CNode();
};
