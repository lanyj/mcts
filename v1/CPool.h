#pragma once

#include "stdafx.h"
#include "CList.h"


template <class T>
class CPool
{
private:
	CList<T> * _pool;
//	CList<T> * _using;
	T (*newInstance)();
	int poolSize;
public:
	CPool(int initSize, T newInstance());
	T obtain();
	void free(T* t);
	~CPool();
};

