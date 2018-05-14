#pragma once

#include "stdafx.h"
#include "CException.h"

template <class T>
class CList {
private:
	int maxBufferSize;
	T* elementData;
	int _size;

	void increaseCapacity(int capacity);
	void checkForIncreaseCapacity();
public:
	CList();
	CList(int initSize);
	int size();
	T getLast();
	T get(int index);
	int indexOf(T t, bool equals(const T l, const T t));
	bool contains(T t, bool equals(const T l, const T t));
	T set(int index, T t);
	void add(T t);
	void add(int index, T t);
	T remove(int index);
	T removeLast();
	bool remove(T t);
	bool remove(T t, bool equals(T l, T r));
	bool clear();
	void passList(void pass(const int i, const T t));
	bool isEmpty();
	~CList();
};
