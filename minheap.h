#ifndef __MIN_HEAP__
#define __MIN_HEAP__

#include <initializer_list>

class IHeap {
	public:
		virtual void create(std::initializer_list<int> inVal) = 0;
		virtual void add(int val) = 0;
		virtual int top() =0 ;
		virtual void heapify(int idx)=0;
		virtual void delete_heap_element() = 0;
		virtual int heapSize() = 0;
};

class MinHeap : public IHeap{
	public:
		MinHeap(); 
		~MinHeap(); 
		void create(std::initializer_list<int> inVal) override;
		void add(int val) override;
		int top() override;
		void heapify(int idx) override;
		void delete_heap_element() override;
		int heapSize() override;
	private:
		int heap[100];
		int heapLen;
};

#endif
