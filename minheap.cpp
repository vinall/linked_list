#include "minheap.h"
#include <iostream>

MinHeap::MinHeap() : heapLen(0) {
}

MinHeap::~MinHeap() {
	//std::cout << "Heap destroyed" << std::endl;
}

void
MinHeap::create(std::initializer_list<int> inVal) {
	int i = 0;
	for(auto &val : inVal)
		heap[i++] = val;
	heapLen = inVal.size();
	int size = inVal.size() /2  - 1;
	std::cout << "Heap Length = " << heapLen << " size = " << size << std::endl;
	for( ; size>=0 ; --size) {
		std::cout << "sending size = " << size << std::endl;
		heapify(size);
	}
}

void
MinHeap::add(int in) {
	int temp = heap[heapLen-1];
	heap[0] = in;
	heap[heapLen-1] = temp;
	heapify(0);
}

int
MinHeap::top() {
	return heap[0];
}

int leftchild(int idx) {
	return (2*idx)+1;
}

int rightchild(int idx) {
	return (2*idx)+2;
}

void
swap(int &a,int &b) {
	auto temp = a;
	a = b;
	b = temp; 
}

void
MinHeap::heapify(int idx) {
	auto leftchild_ = ::leftchild(idx);
	auto rightchild_ = ::rightchild(idx);
	int min = idx;
	if( leftchild_ < heapLen && heap[leftchild_] < heap[min])
		min = leftchild_;
	if( rightchild_  < heapLen && heap[rightchild_] < heap[min])
		min = rightchild_;
	if(min!=idx) {
		std::cout << "left " << leftchild_ << " right " << rightchild_ << std::endl;
		std::cout << "swap " << heap[min] << " " << heap[idx] << std::endl;
		::swap(heap[min],heap[idx]);
		heapify(min);
	}
}

void
MinHeap::delete_heap_element() {
	heap[0] = heap[heapLen-1];
	heapLen--;
	heapify(0);
}

int
MinHeap::heapSize() {
	return heapLen;
}
