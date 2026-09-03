#include <initializer_list>
template<typename T>
class DoubleList
{
private:
	class Node
	{
	private:

	public:
		Node* next;
		Node* prev;
		T value;
		Node(T value)
		{
			this->next = nullptr;
			this->prev = nullptr;
			this->value = value;
		}
	};
	int size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;
public:
	DoubleList()
	{
		head = nullptr;
		tail = nullptr;
	}
	DoubleList(const DoubleList& other)
	{
		head = nullptr;
		size = 0;
		Node* current = other.head;
		while (current)
		{
			push_back(current->value);
			current = current->next;
		}
	}
	DoubleList(DoubleList&& other)
	{
		head = other.head;
		size = other.size;
		tail = other.tail;

		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}
	DoubleList(std::initializer_list<T> init)
	{
		head = tail = nullptr;
		for (const N& value : init)
		{
			push_back(value);
		}
	}
	DoubleList& operator=(std::initializer_list<T> init)
	{
		clear();
		for (const T& value : init)
		{
			push_back(value);
		}
		return *this;
	}
	DoubleList& operator=(const DoubleList& other)
	{
		if (this == &other)
			return *this;

		clear();
		Node* current = other.head;
		while (current)
		{
			push_back(current->value);
			current = current->next;
		}
		return *this;
	}
	DoubleList& operator=(DoubleList&& other)
	{
		if (this == &other)
		{
			return *this;
		}
		clear();
		head = other.head;
		tail = other.tail;
		size = other.size;

		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
		return*this;
	}
	T operator[](int index)
	{
		Node* current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->value;
	}
	const T& operator[](int index) const
	{
		Node* current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->value;;
	}
	class Iterator
	{
	public:
		Node* ptr;
		Iterator(Node* ptr)
		{
			this->ptr = ptr;
		}
		T& operator*()
		{
			return ptr->value;
		}
		Iterator& operator++()
		{
			ptr = ptr->next;
			return ptr;
		}
		bool operator !=(const Iterator& other)
		{
			return ptr != other.ptr;
		}
		bool operator ==(const Iterator& other)
		{
			return ptr == other.ptr;
		}
	};
	class ConstIterator
	{
	public:
		Node* ptr;
		ConstIterator(Node* ptr)
		{
			this->ptr = ptr;
		}
		const T& operator*() const
		{
			return ptr->value;
		}
		ConstIterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		bool operator!=(const ConstIterator& other) const
		{
			return ptr != other.ptr;
		}
		bool operator ==(const ConstIterator& other) const
		{
			return ptr == other.ptr;
		}
	};
	Iterator begin()
	{
		return Iterator(head);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}
	ConstIterator begin() const
	{
		return ConstIterator(head);
	}
	ConstIterator end() const
	{
		return ConstIterator(nullptr);
	}
	void push_back(T value)
	{
		Node* current = new Node(value);
		if (head == nullptr)
		{
			head = tail = current;
			size++;
			return;
		}
		else
		{
			tail->next = current;
			current->prev = tail;
			tail = current;
			size++;
		}
	}
	void push_by_index(int index, T value)
	{
		if (index == 0)
		{
			push_front(value);
			return;
		}

		Node* h = head;

		for (int i = 0; i < index - 1 && h; i++)
			h = h->next;

		if (!h || !h->next)
		{
			push_back(value);
			return;
		}

		Node* newNode = new Node(value);

		newNode->next = h->next;
		newNode->prev = h;

		h->next->prev = newNode;
		h->next = newNode;

		size++;
	}
	void push_front(T value)
	{
		Node* newNode = new Node(value);
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		size++;
	}
	void pop_front()
	{
		Node* temp = head;
		head = head->next;
		head->prev = nullptr;
		size--;
		delete temp;
	}
	void pop_back()
	{
		Node* temp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		size--;
		delete temp;
	}
	void erase_by_index(int index)
	{
		if (head == nullptr)
		{
			head = tail = nullptr;
			return;
		}
		if (index == 0)
		{
			pop_front();
			return;
		}
		Node* h = head;
		for (int i = 0; i < index - 1; i++)
		{
			h = h->next;
		}
		if (h->next == nullptr)
		{
			pop_back();
			return;
		}
		else
		{
			Node* current = h->next;

			h->next = current->next;
			current->next->prev = h;
			size--;

			delete current;
		}
	}
	int getsize()
	{
		return size;
	}
	void clear()
	{
		Node* h = head;
		while (h)
		{
			Node* current = h;
			h = h->next;
			delete current;
		}
		head = tail = nullptr;
		size = 0;
	}
	void swap(int index, int twoindex)
	{
		Node* n1 = head;
		Node* n2 = head;
		for (int i = 0; i < index; i++)
		{
			n1 = n1->next;
		}
		for (int i = 0; i < twoindex; i++)
		{
			n2 = n2->next;
		}
		T temp = n1->value;
		n1->value = n2->value;
		n2->value = temp;
	}
	int find_index(T value)
	{
		int index = 0;
		Node* current = head;
		while (current)
		{
			
			if (current->value == value)
			{
				return index;
			}
			current = current->next; 
			index++;
		}
		return -1;
	}
	Node* find(T value)
	{
		Node* current = head;
		while (current)
		{
			current = current->next;
			if (current->value == value)
			{
				return current;
			}
		}
		return nullptr;
	}
	void reverse()
	{
		Node* current = head;
		Node* temp = nullptr;

		while (current)
		{
			temp = current->prev;
			current->prev = current->next;
			current->next = temp;

			current = current->prev;
		}

		std::swap(head, tail);
	}
	Iterator insert(Iterator it, T value)
	{
		Node* pos = it.ptr;
		Node* newNode = new Node(value);
		if (pos == head)
		{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
			size++;
			return Iterator(head);
		}
		if (pos == nullptr)
		{
			push_back(value);
			return Iterator(tail);
		}
		else
		{
			Node* prePos = pos->prev;
			newNode->next = pos;
			newNode->prev = prePos;

			prePos->next = newNode;
			pos->prev = newNode;
			size++;
			return Iterator(newNode);
		}
	}
	Iterator erase(Iterator it)
	{
		Node* node = it.ptr;
		if (node == head)
		{
			Node* cur = head;
			head = head->next;
			head->prev = nullptr;
			delete cur;
		}
		
		if (node == tail)
		{
			tail = tail->prev;
			tail->next = nullptr;
		}
		else
		{
			node->next->prev = node->prev;
			node->prev->next = node->next;
			
		}
		delete node;
		size--;

	}
	void SwapNode(int index, int index2)
	{
		Node* n1 = head;
		Node* n2 = head;
		for (int i = 0; i < index; i++)
		{
			n1 = n1->next;
		}
		for (int i = 0; i < index2; i++)
		{
			n2 = n2->next;
		}
		Node* p1 = n1->prev;
		Node* nx1 = n1->next;

		Node* p2 = n2->prev;
		Node* nx2 = n2->next;

		if (nx1 == n2)
		{
			if (p1) p1->next = n2;
			if (nx2) nx2->prev = n1;

			n2->prev = p1;
			n2->next = n1;

			n1->prev = n2;
			n1->next = nx2;
		}
		else if (nx2 == n1)
		{
			if (p2) p2->next = n1;
			if (nx1) nx1->prev = n2;

			n1->prev = p2;
			n1->next = n2;

			n2->prev = n1;
			n2->next = nx1;
		}
		else
		{
			if (p1) p1->next = n2;
			if (nx1) nx1->prev = n2;

			if (p2) p2->next = n1;
			if (nx2) nx2->prev = n1;

			std::swap(n1->prev, n2->prev);
			std::swap(n1->next, n2->next);
		}

		if (n1 == head) head = n2;
		else if (n2 == head) head = n1;

		if (n1 == tail) tail = n2;
		else if (n2 == tail) tail = n1;
	}
	void DeletePeriod(int index, int index2)
	{
		Node* left = head;
		Node* right = head;

		for (int i = 0; i < index; i++)
			left = left->next;

		for (int i = 0; i < index2; i++)
			right = right->next;

		Node* before = left->prev;
		Node* after = right->next;

		Node* cur = left;

		while (cur != after)
		{
			Node* temp = cur;
			cur = cur->next;
			delete temp;
		}

		if (before)
			before->next = after;
		else
			head = after;

		if (after)
			after->prev = before;
		else
			tail = before;
	}
	Node* merge(Node* a, Node* b)
	{
		if (!a) return b;
		if (!b) return a;

		Node* head = nullptr;
		Node* tail = nullptr;

		if (a->value < b->value)
		{
			head = tail = a;
			a = a->next;
		}
		else
		{
			head = tail = b;
			b = b->next;
		}

		head->prev = nullptr;

		while (a && b)
		{
			if (a->value < b->value)
			{
				tail->next = a;
				a->prev = tail;
				tail = a;
				a = a->next;
			}
			else
			{
				tail->next = b;
				b->prev = tail;
				tail = b;
				b = b->next;
			}
		}

		if (a)
		{
			tail->next = a;
			a->prev = tail;
		}

		if (b)
		{
			tail->next = b;
			b->prev = tail;
		}

		return head;
	}
	void split(Node* head, Node*& left, Node*& right)
	{
		Node* first = head;
		Node* second = head->next;

		while (second->next)
		{
			first = first->next;
			second = second->next->next;
		}
		left = head;
		right = slow->next;
		slow->next = nullptr;
		right->prev = nullptr;
	}
	Node* mergeSort(Node* node)
	{
		if (!node || !node->next)
			return node;

		Node* left;
		Node* right;

		split(node, left, right);

		left = mergeSort(left);
		right = mergeSort(right);

		return merge(left, right);
	}
	~DoubleList()
	{
		clear();
	}


};
