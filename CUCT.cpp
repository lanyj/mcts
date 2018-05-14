#pragma once

#include <time.h>
#include "stdafx.h"
#include "CUCT.h"
#include "OthelloCBoard.h"
#include "OXOCBoard.h"
#include "GobangCBoard.h"


void* CUCT::getCNode(const void *list, int index) {
	return ((CList<CNode*>*) list)->get(index);
}
void CUCT::exchangeCNode(const void *list, int i, int j) {
	CNode* m = (CNode*) ((CList<CNode*>*) list)->get(i);
	CNode* n = (CNode*) ((CList<CNode*>*) list)->get(j);
	((CList<CNode*>*) list)->set(i, n);
	((CList<CNode*>*) list)->set(j, m);
}
int CUCT::compareToCNode(const void* l, const void* r) {
	double v1 = ((CNode *) l)->value();
	double v2 = ((CNode *) r)->value();
	return  (v1 == v2 ? 0 : (v1 > v2 ? 1 : -1));
}

int CUCT::random(int bounds) {
	return rand() % bounds;
}

CNode* CUCT::randomChoiceCNode(CList<CNode*> *list) {
	if (list->isEmpty()) {
		return NULL;
	}
	return list->get(random(list->size()));
}

CMove* CUCT::randomChoiceCMove(CList<CMove*> *list) {
	if (list->isEmpty()) {
		return NULL;
	}
	return list->get(random(list->size()));
}

CMove* CUCT::uctMove(CBoard* _board, int itermax) {
	CNode* root = new CNode(NULL, NULL, _board);

	for(; itermax--;) {
		CNode* node = root;
		CBoard *board = _board->clone();

		CNode* n = select(node, board);
		n = expansion(n, board);
		double res = simulation(n, board);
		backUp(n, res);

		delete board;
	}	
//	printf("\nBEGIN...\n");
//	for (int i = root->children->size() - 1; i >= 0; i--) {
//		root->children->get(i)->move->toString();
//		printf(" -> %f, %f, %f\n", root->children->get(i)->visits, root->children->get(i)->score, root->children->get(i)->value());
//	}
	CMove* move;
	double mostVist = -100;
	int index = -1;
	for (int i = root->children->size() - 1; i >= 0; i--) {
		CNode* tmp = root->children->get(i);
		/*
		if ((tmp->score / tmp->visits) > mostVist) {
			mostVist = (tmp->score / tmp->visits);
			index = i;
		}
		*/
		if (tmp->visits > mostVist) {
			mostVist = tmp->visits;
			index = i;
		}
	}
	move = root->children->get(index)->move->clone();
//	printf("\nCHOSEN:->");
//	move->toString();
//	printf("\nEND...");
	clearUp(root);
	return move;
}

CNode* CUCT::select(CNode* root, CBoard* board) {
	if (root->children->isEmpty()) {
		return root;
	}
	CNode* next = root->uctSelectChild();
	board->applyMove(next->move);
	while (!next->children->isEmpty()) {
		next = next->uctSelectChild();
		board->applyMove(next->move);
	}
	return next;
}

CNode* CUCT::expansion(CNode* root, CBoard* board) {
	if (board->isGameOver()) {
		return root;
	}
	CNode* node = NULL;
	CList<CMove*>* moves = board->getMoves();
	while (!moves->isEmpty()) {
		root->addNode(moves->removeLast(), board);
	}
	delete moves;
	return randomChoiceCNode(root->children);
}

double CUCT::simulation(CNode* root, CBoard* board) {
	while (!board->isGameOver()) {
		//CList<CMove*>* moves = board->getMoves();
		//CMove* m = randomChoiceCMove(moves);
		CMove* m = board->randomMove();
		board->applyMove(m);
		//while (!moves->isEmpty()) {
		//	delete moves->removeLast();
		//}
		//delete moves;
	}
	double res = board->getResult(root->player);
	return res;
}

void CUCT::backUp(CNode* node, double res) {
	node->update(res);
	if (node->parent != NULL) {
		backUp(node->parent, -res);
	}
}

void CUCT::clearUp(CNode* node) {
	if (node->move != NULL) {
		delete node->move;
	}
	CList<CNode*> *children = node->children;
	while(!children->isEmpty()) {
		clearUp(children->removeLast());
	}
	delete node;
}

void CUCT::uctPlayGame() {
	char c[3] = { '.', 'X', 'O' };
	// OXOCBoard, GobangCBoard, OthelloCBoard
	CBoard *board = new OthelloCBoard(8);
	board->printCBoard();
	printf("\n");

	CMove *move;
	while(!board->isGameOver()) {
		if(board->getCurrentPlayer() == 1) {
			move = uctMove(board, 1000);
		} else {
			move = uctMove(board, 100);
		}
		printf("\nPlayer %c STEP: ", c[board->getCurrentPlayer()]);
		move->toString();
		printf("\n");
		board->applyMove(move);
		board->printCBoard();
		printf("\n");
		delete move;
	}
	printf("Player: %c -> %lf\n", c[board->getCurrentPlayer()], board->getResult(board->getCurrentPlayer()));
	printf("Player: %c -> %lf\n", c[3 - board->getCurrentPlayer()], board->getResult(3 - board->getCurrentPlayer()));
	delete board;	
}