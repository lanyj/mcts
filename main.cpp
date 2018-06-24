#include <thread>
#include <process.h>

#include "stdafx.h"
#include "CUCT.h"
#include "CList.h"
using namespace std;

int main(int argc, char* argv[]) {
	srand(time(NULL));
	CUCT::uctPlayGame();
	int tmp = 0;
	while (tmp != -1) {
		tmp = scanf("%d\n", &tmp);
		_sleep(5000);
	}
	return 0;
}
