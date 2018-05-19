
#include <thread>
#include <process.h>

#include <Python.h>

#include "stdafx.h"
#include "CUCT.h"
#include "CList.h"
using namespace std;

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

CList<char*> *list;

void f() {
	
	int sum = 10;
	while (sum-- >= 0) {
		char* tmp = new char[3];
		tmp[0] = list->size() / 10;
		tmp[1] = list->size() % 10;
		tmp[2] = 0;
		list->add(tmp);
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 100));
	}
}

int main(int argc, char* argv[]) {
//	wchar_t* tmp = argv[0];
//	Py_SetProgramName(tmp);
	Py_Initialize();
//	PyRun_SimpleString("print('hello world!\\n')");
	Py_Finalize();

	srand(time(NULL));
//	CUCT::uctPlayGame();
	int tmp = 0;
	while (tmp != -1) {
		tmp = scanf("%d\n", &tmp);
		_sleep(5000);
	}
	return 0;

	/*
	
	list = new CList<char*>();

	std::thread* thread0 = new std::thread(f);
	std::thread* thread1 = new std::thread(f);
	std::thread* thread2 = new std::thread(f);
	std::thread* thread3 = new std::thread(f);

	printf("All thread inited.\n");
	thread0->detach();
	thread1->detach();
	thread2->detach();
	thread3->detach();

	printf("All thread joined.\n");
	printf("Final len: %d, %d\n", list->size(), thread0->joinable());
	
	_sleep(20000);
	printf("Final len: %d, %d\n", list->size(), thread0->joinable());

	tmp = 0;
	while (tmp != -1) {
		tmp = scanf("%d\n", &tmp);
		_sleep(5000);
	}
	return 0;
	*/
}
