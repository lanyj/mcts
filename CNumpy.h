#pragma once

#include "stdafx.h"
#include "CNumpyArray.h"


class CNumpy
{
public:
	CNumpy();
	double nmax(CNumpyArray* array);
	double nsum(CNumpyArray* array);
	CNumpyArray* narange(int bound);
	CNumpyArray* narange(int begin, int bound);
	CNumpyArray* nexp(CNumpyArray* arr, bool na);
	CNumpyArray* nmaximum(CNumpyArray* arr, double min, bool na);
	CNumpyArray* ndot(CNumpyArray* x, CNumpyArray* y);
	~CNumpy();
};

