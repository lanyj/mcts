#include "CNumpyArray.h"


void CNumpyArray::reset() {
	if (_src != NULL) {
		delete _src;
		_src = NULL;
	}
	if (_size != NULL) {
		delete _size;
		_size = NULL;
	}
	_dimension = 0;
}

void CNumpyArray::reset(int *_size, int _dimension) {
	if (this->_src != NULL) {
		delete this->_src;
	}
	if (this->_size != NULL) {
		delete this->_size;
	}
	int total = 1;
	for (int i = 0; i < _dimension; i++) {
		total *= _size[i];
	}
	this->_src = new double[total];
	this->_size = new int[_dimension];
	memcpy(this->_size, _size, sizeof(int) * _dimension);
	this->_dimension = _dimension;
}

CNumpyArray::CNumpyArray() {
	this->_src = NULL;
	this->_size = NULL;
	this->_dimension = 0;
}

CNumpyArray::CNumpyArray(CNumpyArray* arr) {
	int total = arr->totalSize();
	this->_src = new double[total];
	memcpy(this->_src, arr->_src, sizeof(double) * total);
	this->_size = new int[arr->_dimension];
	memcpy(this->_size, arr->_size, sizeof(int) * arr->_dimension);
	this->_dimension = arr->_dimension;
}

CNumpyArray::CNumpyArray(double* _src, int *_size, int _dimension)
{
	int total = 1;
	for (int i = 0; i < _dimension; i++) {
		total *= _size[i];
	}
	this->_src = new double[total];
	memcpy(this->_src, _src, sizeof(double) * total);
	this->_size = new int[_dimension];
	memcpy(this->_size, _size, sizeof(int) * _dimension);
	this->_dimension = _dimension;
}

int CNumpyArray::totalSize() {
	if (_dimension == 0) {
		return 0;
	}
	int total = 1;
	for (int i = 0; i < _dimension; i++) {
		total *= _size[i];
	}
	return total;
}

CNumpyArray* CNumpyArray::reshape(int count, ...) {
	va_list ap;
	int* tmp = new int[count];
	va_start(ap, count);
	for (int i = 0; i < count; i++) {
		tmp[i] = va_arg(ap, int);
	}
	va_end(ap);
	delete _size;
	_size = tmp;
	_dimension = count;
	return this;
}

CNumpyArray::~CNumpyArray()
{
	delete _src;
	delete _size;
}
