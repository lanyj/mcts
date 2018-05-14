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
	double best = -1000, tmp = 0;
	int index = -1;
	for (int i = children->size() - 1; i >= 0; i--) {
		tmp = children->get(i)->value();
		if (tmp > best) {
			best = tmp;
			index = i;
		}
	}
	if (best == 0) {
		do {
			index = rand() % children->size();
		} while (children->get(index)->value() != 0);
	}
//	CUtils::QuickSort(children, getCNode, children->size(), exchangeCNode, compareToCNode);
	return children->get(index);
}

CNode* CNode::addNode(CMove* m, CBoard* board) {
	CNode *n = new CNode(m, this, board);
	this->children->add(n);
//	this->unvisited->remove(m, compareToCMove);
	return n;
}
		
void CNode::update(double result) {
	this->visits++;
	this->score += result;
}
		
double CNode::value() {
//	printf("[%f, %f, %f] = %f\n", score, visits, parent->visits, score / (0.000001 + visits) + sqrt(2 * log(parent->visits) / (0.000001 + visits)));
	return score / (0.000001 + visits) + sqrt(2 * log(parent->visits) / (0.000001 + visits));
}
				
CNode::~CNode() {
	delete children;
//	while (!unvisited->isEmpty()) {
//		delete unvisited->removeLast();
//	}
//	delete unvisited;
}
