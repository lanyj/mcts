#pragma once

#include "stdafx.h"
#include "CNode.h"

#define EPISLION 1E-6

void* CNode::getCNode(const void *list, int index) {
	return ((CList<CNode*>*) list)->get(index);
}
void CNode::exchangeCNode(const void *list, int i, int j) {
	CNode* m = (CNode*)((CList<CNode*>*) list)->get(i);
	CNode* n = (CNode*)((CList<CNode*>*) list)->get(j);
	((CList<CNode*>*) list)->set(i, n);
	((CList<CNode*>*) list)->set(j, m);
}
int CNode::compareToCNode(const void* l, const void* r) {
	double v1 = ((CNode *)l)->value();
	double v2 = ((CNode *)r)->value();
	return  v1 == v2 ? 0 : (v1 > v2 ? 1 : -1);
}

bool CNode::compareToCMove(CMove* l, CMove* r) {
	return l->equals(r);
}

CNode::CNode(CMove* move, CNode* parent, CBoard* board) {
	this->player = board->getCurrentPlayer();
	this->score = 0;
	this->visits = 0;
	this->move = move;
	this->parent = parent;
	this->children = new CList<CNode*>();
//	this->unvisited = board->getMoves();
}
		
CNode* CNode::uctSelectChild() {
	//smt.lock();
	int index = rand() % children->size();
	double best = children->get(index)->value(), tmp = 0;
	for (int i = children->size() - 1; i >= 0; i--) {
		CNode* c = children->get(i);
		tmp = c->value();
		if (tmp > best) {
			best = tmp;
			index = i;
		}
	}
	CNode* t = children->get(index);
	//smt.unlock();
	return t;
}

CNode* CNode::addNode(CMove* m, CBoard* board) {
	CNode *n = new CNode(m, this, board);
	//smt.lock();
	this->children->add(n);
	//smt.unlock();
//	this->unvisited->remove(m, compareToCMove);
	return n;
}
		
void CNode::update(double result) {
	//smt.lock();
	this->visits++;
	this->score += result;
	//smt.unlock();
}
		
double CNode::value() {
//	printf("[%f, %f, %f] = %f\n", score, visits, parent->visits, score / (0.000001 + visits) + sqrt(2 * log(parent->visits) / (0.000001 + visits)));
	//smt.lock();
	double ret = score / (EPISLION + visits) + sqrt(2 * log(EPISLION + parent->visits) / log(2.71828) / (EPISLION + visits));
	//smt.unlock();
	return ret;
}

CNode::~CNode() {
	delete children;
}
