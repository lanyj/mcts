#pragma once

#include "stdafx.h"
#include "CNode.h"

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
	double best = -1e8, tmp = 0;
	int index = -1;
	for (int i = children->size() - 1; i >= 0; i--) {
		CNode* c = children->get(i);
		tmp = c->score / (0.000001 + c->visits) + sqrt(2 * log(0.000001 + c->parent->visits) / (0.000001 + c->visits));
		//tmp = c->value();
		if (tmp > best) {
			best = tmp;
			index = i;
		}
	}
	if (index == -1) {
		index = rand() % children->size();
	} else if (best == 0) {
		do {
			index = rand() % children->size();
			CNode* c = children->get(index);
			tmp = c->score / (0.000001 + c->visits) + sqrt(2 * log(0.000001 + c->parent->visits) / (0.000001 + c->visits));
			//tmp = c->value();
		} while (tmp != sqrt(2 * log(0.000001) / (0.000001)));
	}
//	CUtils::QuickSort(children, getCNode, children->size(), exchangeCNode, compareToCNode);
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
	double ret = score / (0.000001 + visits) + sqrt(2 * log(0.000001 + parent->visits) / (0.000001 + visits));
	//smt.unlock();
	return ret;
}

CNode::~CNode() {
	delete children;
}
