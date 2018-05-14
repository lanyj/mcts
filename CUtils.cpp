#pragma once

#include "stdafx.h"
#include "CUtils.h"

/*
public static <T extends Comparable<T>> void sort(Sortable<T> sortable) {
quickSort(sortable, 0, sortable.length() - 1);
}

private static <T extends Comparable<T>> void quickSort(Sortable<T> sortable, int p, int r) {
if (p < r) {
int q = partition(sortable, p, r);
quickSort(sortable, p, q - 1);
quickSort(sortable, q + 1, r);
}
}
*/

int CUtils::partition(void* collection, void* get(const void* collection, const int index), int length, void exchange(const void* collection, int i, int j), int compareTo(const void* l, const void* r), int p, int r) {
	void* x = get(collection, r);
	int i = p - 1;
	for(int j = p; j < r; j++) {
		if(compareTo(get(collection, j), x) <= 0) {
			i++;
			exchange(collection, i, j);
		}
	}
	exchange(collection, i + 1, r);
	return i + 1;
}
void CUtils::quickSort(void* collection, void* get(const void* collection, const int index), int length, void exchange(const void* collection, const int i, const int j), int compareTo(const void* l, const void* r), int p, int r) {
	if(p < r) {
		int q = partition(collection, get, length, exchange, compareTo, p, r);
		quickSort(collection, get, length, exchange, compareTo, p, q - 1);
		quickSort(collection, get, length, exchange, compareTo, q + 1, r);
	}
}
void CUtils::QuickSort(void* collection, void* get(const void* collection, const int index), int length, void exchange(const void* collection, const int i, const int j), int compareTo(const void* l, const void* r)) {
	quickSort(collection, get, length, exchange, compareTo, 0, length - 1);
}