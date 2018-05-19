#include "stdafx.h"
#include "CPool.h"


template <class T>
CPool<T>::CPool(int initSize, T newInstance())
{
	this->poolSize = initSize;
	_pool = new CList<T>(initSize);
//	_using = new CList<T>(initSize);
	this->newInstance = newInstance;
	for (int i = 0; i < initSize; i++) {
		_pool->add(newInstance());
	}
}

template <class T>
T CPool<T>::obtain() {
	if (_pool->isEmpty()) {
		for (int i = poolSize - 1; i >= 0; i--) {
			_pool->add(this->newInstance());
		}
	}
	T p = _pool->removeLast();
//	_using->add(p);
	return p;
}

template <class T>
void CPool<T>::free(T* t) {
//	bool p = _using->remove(t);
//	if (p) {
	_pool->add(t);
//	}
}

template <class T>
CPool<T>::~CPool() {
	_pool->~CList();
}
