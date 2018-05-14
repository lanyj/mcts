#pragma once

#include "stdafx.h"
#include "CException.h"


CException::CException(const char* msg) {
	this->name = "CException";
	this->msg = msg;
}

void CException::printMsg() {
	printf("%s:\n\t%s\n", name, msg);
	exit(-1);
}

CIndexOutOfBoundsException::CIndexOutOfBoundsException(int index, int bounds, const char* msg) : CException(msg) {
	this->index = index;
	this->bounds = bounds;
	this->name = "CIndexOutOfBoundsException";
}

void CIndexOutOfBoundsException::printMsg() {
	printf("%s: Index: %d, Size: %d\n\t%s\n", name, index, bounds, msg);
	exit(-1);
}

CKeyNotFoundException::CKeyNotFoundException(const char* msg) : CException(msg) {
	this->name = "CKeyNotFoundException";
}

CEmptyStackException::CEmptyStackException(const char* msg) : CException(msg) {
	this->name = "CEmptyStackException";
}

CEmptyQueueException::CEmptyQueueException(const char* msg) : CException(msg) {
	this->name = "CEmptyQueueException";
}

CRootOfTreeException::CRootOfTreeException(const char* msg) : CException(msg) {
	this->name = "CRootOfTreeException";
}
		
CNoSuchChildException::CNoSuchChildException(const char* msg) : CException(msg) {
	this->name = "CNoSuchChildException";
}

CBoundsOfChildException::CBoundsOfChildException(const char* msg) : CException(msg) {
	this->name = "CBoundsOfChildException";
}
CIllegalStateException::CIllegalStateException(const char* msg) : CException(msg) {
	this->name = "CIllegalStateException";
};