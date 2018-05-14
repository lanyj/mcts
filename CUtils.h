#pragma once

#include "stdafx.h"

class CUtils {
private:
	static int partition(void* collection, void* get(const void* collection, const int index), int length, void exchange(const void* collection, int i, int j), int compareTo(const void* l, const void* r), int p, int r);
	static void quickSort(void* collection, void* get(const void* collection, const int index), int length, void exchange(const void* collection, const int i, const int j), int compareTo(const void* l, const void* r), int p, int r);
public:
	static void QuickSort(void* collection, void* get(const void* collection, const int index), int length, void exchange(const void* collection, const int i, const int j), int compareTo(const void* l, const void* r));
};
