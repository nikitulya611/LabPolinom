#pragma once

struct Monom
{
	int k;
	int pows;

	Monom() : k(0), pows(0) {};

	friend std::ostream& operator<<(std::ostream& out, const Monom& m)
	{
		int x = m.pows / 100;
		int y = (m.pows / 10) % 10;
		int z = m.pows % 10;

		out << m.k;
		if (x != 0)
			out << "x^" << x;
		if (y != 0)
			out << "y^" << y;
		if (z != 0)
			out << "z^" << z;
		return out;
	}

	bool operator==(Monom& m)
	{
		return k == m.k && pows == m.pows;
	}

	bool operator!=(Monom& m)
	{
		return !(*this == m);
	}
};


struct Node
{
	Monom data;
	Node* prev;
	Node* next;

	Node() : next(nullptr), prev(nullptr) {};

	bool operator==(Node& n)
	{
		return (data == n.data) && (prev == n.prev) && (next == n.next);
	}
	bool operator!=(Node& n)
	{
		return !(*this == n);
	}
};




class List
{
public:
	List(int size = 10);
	~List();

	Node* erase(Monom& value);
	Node* erase(Node* value);
	void push(Monom& value);

	bool isEmpty() const;
	int getSize() const;

	Node* begin() const;
	Node* end() const;


	friend std::ostream& operator<<(std::ostream& out, const List& m)
	{
		if (m.isEmpty())
		{
			out << 0;
			return out;
		}
		bool isFirst = true;
		for (Node* it = m.begin(); it != nullptr; it = it->next)
		{
			if (isFirst)
			{
				out << it->data << ' ';
				isFirst = false;
				continue;
			}
			if (it->data.k > 0)
				out << "+";
			out << it->data << ' ';
		}
		return out;
	}

private:
	int size;
	int max;

	Node* pFirst;
	Node* pLast;

};


List::List(int size)
{
	max = size;

	this->size = 0;
	pFirst = pLast = nullptr;
}

List::~List()
{
	delete pFirst, pLast;
}

inline Node* List::erase(Monom& value)
{
	if (isEmpty() || value.k == 0)
		return nullptr;
	Node* curr = pFirst;
	Node* temp;
	while (value != curr->data)
	{
		if (curr->next == nullptr)
			return nullptr;
		curr = curr->next;
	}
	if (getSize() == 1)
	{
		pFirst = pLast = temp = nullptr;
	}
	else if (curr == pFirst)
	{
		curr->next->prev = nullptr;
		pFirst = curr->next;
		temp = pFirst;
	}

	else if (curr == pLast)
	{
		curr->prev->next = nullptr;
		pLast = curr->prev;
		temp = pLast;
	}

	else {
		temp = curr->prev;
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
	}
	delete curr;
	size--;
	return temp;
}

inline Node* List::erase(Node* value)
{
	Node* curr = value;
	Node* temp;
	if (getSize() == 1)
	{
		pFirst = pLast = temp = nullptr;
	}
	else if (curr == pFirst)
	{
		curr->next->prev = nullptr;
		pFirst = curr->next;
		temp = pFirst;
	}

	else if (curr == pLast)
	{
		curr->prev->next = nullptr;
		pLast = curr->prev;
		temp = pLast;
	}

	else {
		temp = curr->prev;
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
	}
	delete curr;
	size--;
	return temp;
}

void List::push(Monom& value)
{
	if (value.k == 0)
		return;
	Node* n = new Node;
	n->data = value;
	if (isEmpty())
	{
		pFirst = pLast = n;
	}
	else {
		Node* curr = pFirst;
		while (value.pows < curr->data.pows)
		{
			curr = curr->next;
			if (curr == nullptr)
				break;
		}

		//if(value.pows < curr->data.pows)

		if (curr == pFirst)
		{
			n->next = pFirst;
			pFirst->prev = n;
			pFirst = n;
		}

		else if (curr == nullptr)
		{
			n->prev = pLast;
			pLast->next = n;
			pLast = n;
		}

		/*else if (curr == pLast)
		{
			n->prev = curr;
			curr->next = n;
			pLast = n;
		}*/

		else {

			n->prev = curr->prev;
			n->next = curr;
			curr->prev->next = n;
			curr->prev = n;
		}
	}
	size++;
}

bool List::isEmpty() const
{
	return pFirst == nullptr;
}

inline int List::getSize() const
{
	return size;
}

inline Node* List::begin() const
{
	return pFirst;
}

inline Node* List::end() const
{
	return pLast;
}
