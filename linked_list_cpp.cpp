#include <iostream>
#include <memory>
#include <initializer_list>
#include <stack>
using namespace std;

struct 
Node{
	Node() {
		data = 0;
		next = nullptr;
	}
	~Node() {
		std::cout << "\nNode getting deleted = " << data << std::endl;
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
std::shared_ptr<Node> merge(shared_ptr<Node> node1, shared_ptr<Node> node2) {
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

	std::cout << "Here finished\n" << std::endl;
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

	std::cout << "Here\n";
	while(head->next != nullptr) {
		std::cout << head->data << "\t ";
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
		std::cout << head_t->data << "\t";
		head_t = head_t->next;
	}
	std::cout << std::endl;
}
int
delete_last() {
	LinkedList my_list;
	my_list.insert(11);
	my_list.insert(2);
	my_list.insert(3);
	my_list.insert(8);
	my_list.insert(3);
	my_list.insert(1);
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
	LinkedList my_list;
	my_list.insert(1);
	my_list.insert(4);
	my_list.insert(7);
	my_list.insert(3);
	my_list.insert(6);
	my_list.insert(5);
	my_list.insert(2);
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
				std::cout << "head = " << head->data << std::endl;
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
		std::cout << temp->data << "\t";
		if(temp->next == start_node) {
			if(flag)
				break;
			else 
				flag = true;
		}
		temp = temp->next;
	}
	std::cout << "\n";
	temp = head;
	int count = 1;
	while(st.size()>0) {
		if(st.top() != temp->data) {
			std::cout << "temp = " << temp->data << std::endl;
			break;
		}
		st.pop();
		temp = temp->next;
	}

	return st.size() > 0 ? false : true;
}

void 
find_loop_list_palindrome() {
	LinkedList myList({1,2,3,2,8,1});
	auto head = myList.getHead();
	head->next->next->next->next->next->next = head->next->next; 
	auto loopy_node = find_loop(head);
	std::cout << "loop_node = " << loopy_node->data << std::endl;
	auto start_node = find_loop_start_node(head,loopy_node);
	std::cout << "start node = " << start_node->data << std::endl;
	bool val =_find_loopy_list_palindrome(head,start_node);
	if (val)
		std::cout << "palindrome \n";
	else
		std::cout << "not palindrome\n";
}

int 
main() {
	std::cout << "fnd_loop_list_palindrome \n";
	find_loop_list_palindrome();
	char ch;
	std::cin >> ch;
	std::cout << "Min Max Arrange\n";
	min_max_arrange();
	std::cout << "Last deleted\n";
	delete_last();
	LinkedList my_list;
	my_list.insert(89);
	my_list.insert(12);
	my_list.insert(67);
	my_list.insert(30);
	my_list.insert(53);
	my_list.insert(40);
	my_list.insert(10);
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
