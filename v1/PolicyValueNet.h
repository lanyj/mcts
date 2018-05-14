#pragma once

#include "stdafx.h"


class PolicyValueNet
{
public:
	static double* softmax(double* x, int length);
	static double* relu(double* x, int length);

	PolicyValueNet();
	~PolicyValueNet();
};

