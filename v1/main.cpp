#include "stdafx.h"
#include "CUCT.h"
#include "CList.h"


/*
void* getCNode(const void *list, int index) {
	return ((CList<char *>*) list)->get(index);
}
void exchangeCNode(const void *list, int i, int j) {
	char *m = (char *)((CList<char *>*) list)->get(i);
	char *n = (char *)((CList<char *>*) list)->get(j);
	((CList<char *>*) list)->set(i, n);
	((CList<char *>*) list)->set(j, m);
}
int compareToCNode(const void* l, const void* r) {
	return  -strcmp((char *) l, (char *) r);
}

void test() {
	CList<char *> *list = new CList<char *>();
	for (int i = 0; i < 10; i++) {
		char *p = new char[10];
		itoa(i, p, 10);
		list->add(p);
	}
	CUtils::QuickSort(list, getCNode, list->size(), exchangeCNode, compareToCNode);
	while (!list->isEmpty()) {
		printf("%d, %s\n", list->size(), list->getLast());
		delete list->removeLast();
	}
	delete list;
}
*/

int main(int argc, char** argv) {
	srand(time(NULL));
	CUCT::uctPlayGame();
	
	int tmp = 0;
	while (tmp != -1) {
		tmp = scanf("%d\n", &tmp);
		_sleep(5000);
	}
	return 0;
}
