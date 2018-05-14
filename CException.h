#pragma once

#include "stdafx.h"


class CException {
protected:
	const char* name;
	const char* msg;
public:
	CException(const char* msg);
	void printMsg();
};
class CIndexOutOfBoundsException : public CException {
protected:
	int index;
	int bounds;
public:
	CIndexOutOfBoundsException(int index, int bounds, const char* msg);
	void printMsg();
};
class CKeyNotFoundException : public CException {
	CKeyNotFoundException(const char* msg);
};
class CEmptyStackException : public CException {
	CEmptyStackException(const char* msg);
};
class CEmptyQueueException : public CException {
	CEmptyQueueException(const char* msg);
};
class CRootOfTreeException : public CException {
	CRootOfTreeException(const char* msg);
};
class CNoSuchChildException : public CException {
	CNoSuchChildException(const char* msg);
};
class CBoundsOfChildException : public CException {
	CBoundsOfChildException(const char* msg);
};
class CIllegalStateException : public CException {
public:
	CIllegalStateException(const char* msg);
};