#pragma once

#include "stdafx.h"
#include "CList.h"


template <class T>
void CList<T>::increaseCapacity(int capacity) {
	while(maxBufferSize <= capacity) {
		maxBufferSize = maxBufferSize * 2;
	}
	T* p = (T*) malloc(sizeof(T) * maxBufferSize);
	memcpy(p, elementData, sizeof(T) * (_size));
	free(elementData);
	elementData = p;
}

template <class T>
inline void CList<T>::checkForIncreaseCapacity() {
	if(maxBufferSize <= _size) {
		increaseCapacity(_size);
	}
}

template <class T>
CList<T>::CList() {
	maxBufferSize = 64;
	elementData = (T*)malloc(sizeof(T) * (maxBufferSize));
	_size = 0;
}

template <class T>
CList<T>::CList(int initSize) {
	maxBufferSize = initSize;
	elementData = (T*)malloc(sizeof(T) * (maxBufferSize));
	_size = 0;
}

template <class T>
int CList<T>::size() {
	return _size;
}

template <class T>
T CList<T>::getLast() {
#ifdef DEBUG
	if (0 == _size) {
		CIndexOutOfBoundsException *exception = new CIndexOutOfBoundsException(-1, _size, "Index out of range on CList::get(int index)");
		exception->printMsg();
    }
#endif // DEBUG
	return elementData[_size - 1];
}

template <class T>
T CList<T>::get(int index) {
#ifdef DEBUG
	if (index >= _size) {
		CIndexOutOfBoundsException *exception = new CIndexOutOfBoundsException(index, _size, "Index out of range on CList::get(int index)");
		exception->printMsg();
    }
#endif // DEBUG

	return elementData[index];
}

template <class T>
int CList<T>::indexOf(T t, bool equals(const T l, const T t)) {
	for(int i = 0; i < _size; i++) {
		if(equals(elementData[i], t)) {
			return i;
		}
	}
	return -1;
}

template <class T>
bool CList<T>::contains(T t, bool equals(const T l, const T t)) {
	return indexOf(t, equals) >= 0;
}

template <class T>
T CList<T>::set(int index, T t) {
#ifdef DEBUG
	if (index >= _size) {
		CIndexOutOfBoundsException *exception = new CIndexOutOfBoundsException(index, _size, "Index out of range on CList::set(int index, T t)");
		exception->printMsg();
    }
#endif // DEBUG
	T p = elementData[index];
	elementData[index] = t;
	return p;
}

template <class T>
void CList<T>::add(T t) {
	checkForIncreaseCapacity();
	elementData[_size++] = t;
}

template <class T>
void CList<T>::add(int index, T t) {
#ifdef DEBUG
	if (index > _size) {
		CIndexOutOfBoundsException *exception = new CIndexOutOfBoundsException(index, _size, "Index out of range on CList::add(int index, T t)");
		exception->printMsg();
    }
#endif // DEBUG
	checkForIncreaseCapacity();
	for(int i = _size; i > index; i--) {
		elementData[i] = elementData[i - 1];
	}
	elementData[index] = t;
	_size++;
}

template <class T>
T CList<T>::remove(int index) {
#ifdef DEBUG
	if (index >= _size) {
		CIndexOutOfBoundsException *exception = new CIndexOutOfBoundsException(index, _size, "Index out of range on CList::remove(int index)");
		exception->printMsg();
}
#endif // DEBUG
	T tmp = elementData[index];
	for(int i = index; i < _size - 1; i++) {
		elementData[i] = elementData[i + 1];
	}
	_size--;
	return tmp;
}

template <class T>
T CList<T>::removeLast() {
#ifdef DEBUG
	if (_size == 0) {
		CIndexOutOfBoundsException *exception = new CIndexOutOfBoundsException(-1, _size, "Index out of range on CList::remove(int index)");
		exception->printMsg();
}
#endif // DEBUG
	return elementData[--_size];
}

template <class T>
bool CList<T>::remove(T t) {
	for(int i = 0; i < _size; i++) {
		if(t == elementData[i]) {
			remove(i);
			return true;
		}
	}
	return false;
}

template <class T>
bool CList<T>::remove(T t, bool equals(T l, T r)) {
	for (int i = 0; i < _size; i++) {
		if (equals(elementData[i], t)) {
			remove(i);
			return true;
		}
	}
	return false;
}

template <class T>
bool CList<T>::clear() {
	_size = 0;
}

template <class T>
void CList<T>::passList(void pass(const int i, const T t)) {
	for(int i = 0; i < _size; i++) {
		pass(i, elementData[i]);
	}
}

template <class T>
bool CList<T>::isEmpty() {
	return _size <= 0;
}

template <class T>
CList<T>::~CList() {
	free(elementData);
}
