#pragma once

#include <time.h>
#include "stdafx.h"
#include "CUCT.h"
#include "OthelloCBoard.h"
#include "OXOCBoard.h"
#include "GobangCBoard.h"

#define THREAD_CHECK_TIME 500
#define THREAD_COUNT 8
static shared_mutex __cuct_smt;

void* CUCT::getCNode(const void *list, int index) {
	return ((CList<CNode*>*) list)->get(index);
}
void CUCT::exchangeCNode(const void *list, int i, int j) {
	CNode* m = (CNode*)((CList<CNode*>*) list)->get(i);
	CNode* n = (CNode*)((CList<CNode*>*) list)->get(j);
	((CList<CNode*>*) list)->set(i, n);
	((CList<CNode*>*) list)->set(j, m);
}
int CUCT::compareToCNode(const void* l, const void* r) {
	double v1 = ((CNode *)l)->value();
	double v2 = ((CNode *)r)->value();
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

void CUCT::threadUCTMoveMethod(CNode* root, CBoard* _board, int itermax, int index, bool* arr) {
	for (; itermax--;) {
		CNode* node = root;
		CBoard *board = _board->clone();

#if THREAD_COUNT > 1
		__cuct_smt.lock();
#endif // THREAD_COUNT > 1

		CNode* n = select(node, board);

#if THREAD_COUNT > 1
		__cuct_smt.unlock();
#endif // THREAD_COUNT > 1

		n = expansion(n, board);
		double res = simulation(n, board);

#if THREAD_COUNT > 1
		__cuct_smt.lock();
#endif // THREAD_COUNT > 1

		backTrace(n, res);

#if THREAD_COUNT > 1
		__cuct_smt.unlock();
#endif // THREAD_COUNT > 1

		delete board;
	}
	arr[index] = true;
	// printf("uct move thread %d returned.\n", index);
}

CMove* CUCT::uctMove(CBoard* _board, int itermax) {
	CNode* root = new CNode(NULL, NULL, _board);

	bool arr[THREAD_COUNT] = { false };
	for (int i = 0; i < THREAD_COUNT; i++) {
		std::thread t = std::thread(&CUCT::threadUCTMoveMethod, root, _board, itermax / THREAD_COUNT, i, arr);
		t.detach();
	}
CHECKA:
	while (true) {
		for (int i = 0; i < THREAD_COUNT; i++) {
			if (!arr[i]) {
				std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_CHECK_TIME));
				goto CHECKA;
			}
		}
		break;
	}
	CMove* move;
	double mostVist = -1e8;
	int index = -1;
	for (int i = root->children->size() - 1; i >= 0; i--) {
		CNode* tmp = root->children->get(i);
		if (tmp->visits > mostVist) {
			mostVist = tmp->visits;
			index = i;
		}
//		printf("Node on ");
//		tmp->move->toString();
//		printf(" visits = %f, socre = %f, pvisits = %f, value = %f\n", tmp->visits, tmp->score, tmp->parent->visits, tmp->value());
	}
	move = root->children->get(index)->move->clone();
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

#if THREAD_COUNT > 1
	__cuct_smt.lock();

	// 检查是不是仍然未被更改
	if (!root->children->isEmpty()) {
		__cuct_smt.unlock();
		CNode* node = randomChoiceCNode(root->children);
		board->applyMove(node->move);
		return node;
	}
#endif // THREAD_COUNT > 1
	
	CList<CMove*>* moves = board->getMoves();

	while (!moves->isEmpty()) {
		root->addNode(moves->removeLast(), board);
	}

#if THREAD_COUNT > 1
	__cuct_smt.unlock();
#endif // THREAD_COUNT > 1

	CNode* tmp = randomChoiceCNode(root->children);

	board->applyMove(tmp->move);

	delete moves;
	return tmp;
}

double CUCT::simulation(CNode* root, CBoard* board) {
	CBoard* tb = board;
	while (!tb->isGameOver()) {
		CMove* m = tb->randomMove();
		tb->applyMove(m);
		delete m;
	}
	return tb->getResult(root->player);
/*	
	@Deprecated

	double w = 0, l = 0, e = 0;
	int times = 100;
	int htimes = times / 1.5;
	while (times--) {
		CBoard* tb = board->clone();
		while (!tb->isGameOver()) {
			CMove* m = tb->randomMove();
			tb->applyMove(m);
			delete m;
		}
		double tmp = tb->getResult(root->player) > 0;
		if (tmp > 0) {
			w++;
		}
		else if (tmp < 0) {
			l++;
		}
		else {
			e++;
		}
		delete tb;
	}
	if (w >= l && w >= e) {
		return 1;
	}
	if (l >= w && l >= e) {
		return -1;
	}
	return 0;
	*/
}

void CUCT::backTrace(CNode* node, double res) {
	node->update(res);
	if (node->parent != NULL) {
		backTrace(node->parent, -res);
	}
}

void CUCT::auxClearUp(CNode* node) {
	delete node->move;
	while (!node->children->isEmpty()) {
		auxClearUp(node->children->removeLast());
	}
	delete node;
}

void CUCT::threadClearUp(CNode* node, int begin, int end, int index, bool* arr) {
	CList<CNode*> *children = node->children;
	for (int i = begin; i < end; i++) {
		auxClearUp(children->get(i));
	}
	arr[index] = true;
	// printf("clear up thread %d returned.(%d, %d)\n", index, begin, end);
}

void CUCT::clearUp(CNode* root) {
	bool arr[THREAD_COUNT] = { false };
	int total = root->children->size();
	int e = total / THREAD_COUNT + (total % THREAD_COUNT == 0 ? 0 : 1);
	for (int i = 0; i < THREAD_COUNT; i++) {
		// printf("(%d, %d) - (%d, %d)\n", total, e, i * e, MIN(i * e + e, total));
		std::thread t = std::thread(&CUCT::threadClearUp, root, i * e, MIN(i * e + e, total), i, arr);
		t.detach();
	}
CHECKB:
	while (true) {
		for (int i = 0; i < THREAD_COUNT; i++) {
			if (!arr[i]) {
				std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_CHECK_TIME));
				goto CHECKB;
			}
		}
		break;
	}
	delete root;
}

void CUCT::uctPlayGame() {
	char c[3] = { '.', 'X', 'O' };
	// OXOCBoard, GobangCBoard, OthelloCBoard
	CBoard *board = new GobangCBoard();
	board->printCBoard();
	printf("\n");

	CMove *move;
	while (!board->isGameOver()) {
		if (board->getCurrentPlayer() == 1) {
			move = uctMove(board, 100000);
		}
		else {
			move = uctMove(board, 100000);
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
