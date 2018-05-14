#pragma once

#include <stdarg.h>
#include "stdafx.h"


class CNumpyArray
{
private:
	void reset();
	void reset(int* _size, int _dimension);

public:
	double* _src;
	int *_size;
	int _dimension;

	int totalSize();

	CNumpyArray();
	CNumpyArray(CNumpyArray* arr);
	CNumpyArray(double* _src, int *_size, int _dimension);
	CNumpyArray* reshape(int count, ...);
	~CNumpyArray();
};

