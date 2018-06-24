#pragma once
#include "CBoard.h"
#include "CNode.h"
#include "CList.h"


class CBoardPolicyValue
{
private:
	CBoardPolicyValue();
	~CBoardPolicyValue();
	
public:
	static void step(CBoard* board, CNode* node, CList<double>* values, double* gate);
};