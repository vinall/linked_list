#include <iostream>
#include <memory>
#include <initializer_list>
#include <stack>
#include "minheap.h"
#include <vector>
using namespace std;

struct 
Node{
	Node() {
		data = 0;
		next = nullptr;
	}
	~Node() {
		//std::cout << "\nNode getting deleted = " << data << std::endl;
	}
	int data;
	shared_ptr<Node> next;
};

class 
LinkedList {
	public:
		LinkedList() {
			head = nullptr;
		}
		LinkedList(std::initializer_list<int> ilist)
		{
			for(auto &val : ilist)
				insert(val);
		}
		~LinkedList(){}
		void insert(int val) {
			auto newNode = std::make_shared<Node>();
			newNode->data = val;
			newNode->next = head;
			head = newNode;
		}
		void display() {
			auto temp = head;
			while(temp != nullptr)
			{
				std::cout << temp->data <<" ";
				temp = temp->next;
			}
			std::cout << std::endl;
		}
		shared_ptr<Node>  &getHead() { return head; }
		void setNewHead(shared_ptr<Node> newHead) { head = newHead; }
		void insert_sorted(shared_ptr<Node> &sorted, shared_ptr<Node> newNode)  {
			if(sorted == nullptr || sorted->data >= newNode->data) {
				newNode->next = sorted;
				sorted = newNode;
			}
			else {
				auto temp_sorted = sorted;
				while(temp_sorted->next != nullptr && temp_sorted->next->data <= newNode->data) {
					temp_sorted = temp_sorted->next;
				}
				newNode->next = temp_sorted->next;
				temp_sorted->next = newNode;
			}

		}
		void insertion_sort() {
			shared_ptr<Node> next = nullptr;
			shared_ptr<Node> sorted = nullptr;
			auto tempHead = head;
			while(tempHead!=NULL) {
				next = tempHead->next;
				insert_sorted(sorted,tempHead);
				tempHead = next;
			}
			head = sorted;
		}
	private:
		std::shared_ptr<Node> head;
};

shared_ptr<Node> 
reverse(shared_ptr<Node> node) {
	auto p = node;
	shared_ptr<Node> q , r;
	r = nullptr;
	while(p) {
		q = p;
		p = p->next;
		q->next = r;
		r = q;
	}
	return r;
}

void 
display(shared_ptr<Node> node) {
	auto temp = node;
	while(temp) {
		std :: cout << temp->data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}
std::shared_ptr<Node> 
merge(shared_ptr<Node> node1, shared_ptr<Node> node2) {
	if(node1 == nullptr && node2 == nullptr)
		return nullptr;
	if(node1 == nullptr or node2 == nullptr)
		return node1 == nullptr ? node2 : node1;
	shared_ptr<Node> result = nullptr;
	if(node1->data <= node2->data) {
		result = node1;
		result->next = merge(node1->next,node2); 
	} 
	else {
		result = node2;
		result->next = merge(node1,node2->next);
	}
	return result;
}

shared_ptr<Node> 
sort_not_normal_list(shared_ptr<Node> node) {
	if(node == nullptr or node->next == nullptr)
		return node;
	shared_ptr<Node> head1 = node;
	shared_ptr<Node> head2 = node->next;
	auto save_head1 = head1;
	auto save_head2 = head2;
	while (head1 != nullptr && head2 != nullptr && 
			(head1->next != nullptr && head2->next !=nullptr)) {
		auto temp = head1->next->next;
		head1->next = head1->next->next;
		head2->next = head2->next->next;
		head1 = head1->next;
		head2 = head2->next;
	}
	if(head1)
		head1->next = nullptr;
	if(head2)
		head2->next = nullptr;

	if (save_head1->data > save_head1->next->data) {
		auto temp = save_head1;
		save_head1 = save_head2;
		save_head2 = temp;
	}
	save_head2 = reverse(save_head2);
	return merge(save_head1,save_head2);
}

void 
sorted(shared_ptr<Node> &slist,shared_ptr<Node> &push_node) {
	if(slist==nullptr) {
		slist = push_node;
		slist->next = nullptr;
		return;
	}
	while(slist->next != nullptr)
		slist = slist->next;
	slist->next = push_node;
	push_node->next = nullptr;
}

void 
sort_abs_value_linked_list(LinkedList &my_list) {
	shared_ptr<Node> p_sorted = nullptr;
	shared_ptr<Node> n_sorted = nullptr;
	shared_ptr<Node> next;
	shared_ptr<Node> tempHead = my_list.getHead();
	while(tempHead != nullptr) {
		next = tempHead->next;
		if(tempHead->data >= 0) {
			sorted(p_sorted,tempHead);
		}
		else {
			sorted(n_sorted,tempHead);
		}
		tempHead = next;
	}
	auto temp = n_sorted;
	while(temp->next) {
		temp = temp->next;
	}
	temp->next = p_sorted;
	my_list.getHead() = n_sorted;
	my_list.display();
}

void 
call_to_sort_another_list() {
	LinkedList my_list;
	my_list.insert(-10);
	my_list.insert(1);
	sort_abs_value_linked_list(my_list);

	my_list.display();
}

void
_delete_last(shared_ptr<Node> head_t, int number) {
	shared_ptr<Node> prev = nullptr;
	shared_ptr<Node> cur = nullptr;
	shared_ptr<Node> head = head_t;
	if (head->data == number) {
		cur = head;
		head = head->next;
	}

	while(head->next != nullptr) {
		if(head->next->data == number) {
			prev = head;
			cur = head->next;
		}
		head = head->next;
	}
	
	if(prev != nullptr) {
		prev->next = cur->next;
	}
	while(head_t != nullptr) {
		head_t = head_t->next;
	}
	std::cout << std::endl;
}
int
delete_last() {
	LinkedList my_list({1,3,8,3,2,11});
	auto head = my_list.getHead();
	display(head);
	_delete_last(head,3);
	std::cout << "===========\n";
}


int
length(shared_ptr<Node> head) {
	int len = 1;
	while(head!=nullptr) {
		head = head->next;
		len++;
	}
	return len;
}
void
divide_list(shared_ptr<Node> &a, shared_ptr<Node> &b,shared_ptr<Node> head) {
	auto len = length(head);
	a = head;
	int i = 1;
	while(i < len/2) {
		head=head->next;
		i++;
	}
	b = head->next;
	head->next = nullptr;
}

void
min_max_arrange() {
	LinkedList my_list({2,5,6,3,7,4,1});
	my_list.display();
	my_list.insertion_sort();
	shared_ptr<Node> a = nullptr;
	shared_ptr<Node> b = nullptr;
	divide_list(a,b,my_list.getHead());
	display(a);
	display(b);
	my_list.display();
	std::cout << "+++++++++++\n";
}

shared_ptr<Node>
find_loop_start_node(shared_ptr<Node> head,shared_ptr<Node> loopy_node) {
	shared_ptr<Node> temp = nullptr;
	shared_ptr<Node> result = nullptr;
	while(head != nullptr && result == nullptr) {
		temp = loopy_node;
		while(temp->next != loopy_node) {
			if(temp->next == head) {
				result = head;
				break;
			}
			temp = temp->next;
		}
		head = head->next;
	}
	return result;
}

shared_ptr<Node>
find_loop(shared_ptr<Node> head) {
	shared_ptr<Node> result = nullptr;
	auto slow = head;
	auto fast = head;
	while(fast != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;
		if(slow == fast) {
			result = slow; 	
			break;
		}
	}
	return result;
}

bool
_find_loopy_list_palindrome(shared_ptr<Node> head, shared_ptr<Node> start_node) {
	auto temp = head;
	bool flag = false;
	std::stack<int> st;
	while(true) {
		st.push(temp->data);
		if(temp->next == start_node) {
			if(flag)
				break;
			else 
				flag = true;
		}
		temp = temp->next;
	}
	temp = head;
	int count = 1;
	while(st.size()>0) {
		if(st.top() != temp->data) {
			break;
		}
		st.pop();
		temp = temp->next;
	}
	return st.size() > 0 ? false : true;
}

void 
find_loop_list_palindrome() {
	LinkedList myList({1,2,3,2,8});
	auto head = myList.getHead();
	head->next->next->next->next->next = head->next->next; 
	auto loopy_node = find_loop(head);
	auto start_node = find_loop_start_node(head,loopy_node);
	bool val =_find_loopy_list_palindrome(head,start_node);
	if (val)
		std::cout << "palindrome \n";
	else
		std::cout << "not palindrome\n";
}


shared_ptr<Node>
_remove_all_duplicate_occurence(shared_ptr<Node> head) {
	shared_ptr<Node> tempHead = head;
	shared_ptr<Node> newHead = head;
	shared_ptr<Node> first = nullptr , second = nullptr , prev = nullptr;
	bool moveHeadToSecond = false;
	while(tempHead != nullptr && tempHead->next != nullptr) {
		first = tempHead;
		second = tempHead->next;
		while(second != nullptr && first->data == second->data){
			if(first == newHead)
				moveHeadToSecond = true;
			second = second->next;
		}
		if(moveHeadToSecond) {
			newHead = second;
			moveHeadToSecond = false;
		}
		if(prev != nullptr)
			prev->next = second;
		else
			prev = first;
		tempHead = second;
	}	
	return newHead;
}

void
remove_all_duplicate_occurence() {
	//LinkedList myList({23,28,28,28,39,39,40});
	LinkedList myList({40,39,39,39,28,28,23,23});
	auto head = myList.getHead();
	auto newHead = _remove_all_duplicate_occurence(head);
	myList.getHead() = newHead;
	std::cout << "remove_all_duplicate_occurence - " << std::endl;
	myList.display();
	std::cout << "=================================" << std::endl;
}

void 
_removeKthNode(shared_ptr<Node> head,int k) {
	auto tempHead = head ; 
	shared_ptr<Node> prev = nullptr;
	int i = 1;
	while(tempHead != nullptr) {
		while (tempHead != nullptr && i < k  ) {
			prev = tempHead;
			tempHead = tempHead->next;
			i++;
		}
		if(prev == nullptr) {
			tempHead = tempHead->next;
		} else if(tempHead != nullptr){
			prev->next = tempHead->next;
		}
		i = 0;
	}
}

void
RemoveKthNode() {
	LinkedList myList({8,7,6,5,4,3,2,1});
	auto head = myList.getHead();
	_removeKthNode(head,3);
	myList.display();
}

int 
sum_last_n_node(shared_ptr<Node> head,int &count , int n) {
	if(head->next == nullptr) {
		count += 1;
		return head->data;
	}
	auto res = sum_last_n_node(head->next,count,n);
	if(count + 1 <= n) {
		res = res + head->data;
		count++;
	}
	return res;
}
void
sum_last_n_node() {
	LinkedList myList({8,9,2,1,4});
	auto head = myList.getHead();
	std::cout << "sum_last_n_node - ";
	int count = 0;
	std::cout << sum_last_n_node(head,count,5) << std::endl;
}

shared_ptr<Node> 
_merge_linked_list(shared_ptr<Node> head1, shared_ptr<Node> head2) {
	auto newHead = head1;
	shared_ptr<Node> next1 = nullptr,next2 = nullptr;
	int i = 1;
	while(head1 != nullptr && head2 != nullptr) {
		next1 = head1->next;
		next2 = head2->next;
		head1->next = head2;
		head2->next = next1;
		head2 = next2;
		head1 = next1;
	}
	return newHead;
}

void
merge_linked_list() {
	LinkedList myList1({4,3,1,5,6});
	LinkedList myList2({8,9,7,2});
	auto head1 = myList1.getHead();
	auto head2 = myList2.getHead();
	myList1.display();
	myList2.display();
	auto newListHead = _merge_linked_list(head1,head2);
	myList1.display();
}

void
merge_three_linked_list() {
	MinHeap minheap;
	minheap.create({2,4,5});
	minheap.add(1);
	std::cout << "Min "<< minheap.top() << std::endl;
	LinkedList myList1({1,3,5,7});
	LinkedList myList2({2,4,6,8});
	LinkedList myList3({0,9,10,11});
	shared_ptr<Node> arr[3] ;
	arr[0] = myList1.getHead();
	arr[1] = myList2.getHead();
	arr[2] = myList3.getHead();
	MinHeap heap;
	std::vector<int> newList;
	heap.create({arr[0]->data,arr[1]->data,arr[2]->data});
	arr[0] = arr[0]->next;
	arr[1] = arr[1]->next;
	arr[2] = arr[2]->next;
	for(int i = 1; i < 4;i++) {
		for(int j = 0; j < 3 ; j++) {
			auto t = arr[j];
			std::cout <<j << " "<<heap.top() << " "<< t->data << " data to be inserted\n";
			if ( t->data > heap.top() )
			{
				auto top = heap.top();
				newList.push_back(top);
				heap.add(t->data);
			} else {
				newList.push_back(t->data);
			}
			arr[j] = t->next;
		}
	}
	while(heap.heapSize() > 0) {
		newList.push_back(heap.top());
		heap.delete_heap_element();
	}

	for(auto val : newList) { 
		std::cout << val << "\t";
	}
	std::cout << std::endl;
}

shared_ptr<Node>
union_list(shared_ptr<Node> head1,shared_ptr<Node> head2) {
	if(head1 == nullptr && head2 != nullptr)
		return head2;
	if(head2 == nullptr && head1 != nullptr)
		return head1;
	auto tempHead1 = head1;
	auto tempHead2 = head2;
	shared_ptr<Node> newHead = nullptr;

	if( tempHead1->data < tempHead2->data) { 
		newHead = tempHead1;
		newHead->next = union_list(tempHead1->next,tempHead2);
	} else if ( tempHead2->data < tempHead1->data) {
		newHead = tempHead2;
		newHead->next = union_list(tempHead1,tempHead2->next);
	} else {
		newHead = tempHead1;
		newHead->next = union_list(tempHead1->next,tempHead2->next);
	}	
	return newHead;
}

void
Union_Intersection() {
	LinkedList myList1({10,15,4,20});
	LinkedList myList2({8,4,2,10});
	myList1.insertion_sort();
	myList2.insertion_sort();
	auto head1 = myList1.getHead();
	auto head2 = myList2.getHead();
	auto newHead1 = union_list(head1,head2);
	//auto newHead2 = intersection_list(head1,head2);
	//display(newHead);
	display(newHead1);
}

int 
main() {
	merge_three_linked_list();
	getchar();
	std::cout << "merge linked list\n";
	merge_linked_list();
	getchar();
	std::cout << "==================\n";
	std::cout << "sum last n node\n";
	sum_last_n_node();
	std::cout << "================\n";
	std::cout << "RemoveKthNode - \n";
	RemoveKthNode();
	getchar();
	std::cout << "================\n";
	std::cout << "remove_all_duplicate_occurence\n";
	remove_all_duplicate_occurence();
	std::cout << "fnd_loop_list_palindrome \n";
	find_loop_list_palindrome();
	char ch;
	std::cin >> ch;
	std::cout << "Min Max Arrange\n";
	min_max_arrange();
	std::cout << "Last deleted\n";
	delete_last();
	LinkedList my_list({10,40,53,30,67,12,89});
	call_to_sort_another_list();
	auto result = sort_not_normal_list(my_list.getHead());
	std::cin >> ch;
	while(result!=nullptr) {
		std::cout << result->data << " ";
		result = result->next;
	}
	std::cout << std::endl;

	return 0;
}
