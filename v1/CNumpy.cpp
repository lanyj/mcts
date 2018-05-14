#include "CNumpy.h"

CNumpyArray* CNumpy::narange(int bound) {
	double *tmp = new double[bound];
	for (int i = 0; i < bound; i++) {
		tmp[i] = i;
	}
	int s[1];
	s[0] = bound;
	CNumpyArray* arr = new CNumpyArray(tmp, s, 1);
	delete tmp;
	return arr;
}

CNumpyArray* CNumpy::narange(int start, int bound) {
	bound -= start;
	double *tmp = new double[bound];
	for (int i = 0; i < bound; i++) {
		tmp[i] = start + i;
	}
	int s[1];
	s[0] = bound;
	CNumpyArray* arr = new CNumpyArray(tmp, s, 1);
	delete tmp;
	return arr;
}

double CNumpy::nmax(CNumpyArray* arr) {
	double max = arr->_src[0];
	for (int i = arr->totalSize() - 1; i > 0; i--) {
		if (max < arr->_src[i]) {
			max = arr->_src[i];
		}
	}
	return max;
}

double CNumpy::nsum(CNumpyArray* arr) {
	double sum = 0;
	for (int i = arr->totalSize() - 1; i >= 0; i--) {
		sum += arr->_src[i];
	}
	return sum;
}

CNumpyArray* CNumpy::nexp(CNumpyArray* arr, bool na) {
	CNumpyArray* tmp = arr;
	if (na) {
		tmp = new CNumpyArray(arr);
	}
	for (int i = arr->totalSize() - 1; i >= 0; i--) {
		tmp->_src[i] = exp(arr->_src[i]);
	}
	return tmp;
}

CNumpyArray* CNumpy::nmaximum(CNumpyArray* arr, double min, bool na) {
	CNumpyArray* tmp = arr;
	if (na) {
		tmp = new CNumpyArray(arr);
	}
	for (int i = arr->totalSize() - 1; i >= 0; i--) {
		if (tmp->_src[i] < min) {
			tmp->_src[i] = min;
		}
	}
	return tmp;
}

CNumpyArray* CNumpy::ndot(CNumpyArray* x, CNumpyArray* y) {
	return x;
}

CNumpy::CNumpy()
{
}


CNumpy::~CNumpy()
{
}
