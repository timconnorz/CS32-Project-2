// PROJ 2
// Set.h
//
// Created by Tim Connors April 2016
//
//


#include "Set.h"

Set::Set() {							// DEFAULT CONSTRUCTOR	 ------------------------------------------------------			
	head = tail = nullptr;
	s_size = 0;
}

Set::~Set() {							// DESTRUCTOR ------------------------------------------------------
	if (s_size == 0)
		return;
	if (s_size == 1) {
		delete head;
		return;
	}
	Node* p = head;
	while (p->next != nullptr)
	{
		p = p->next;
	 	delete p->prev;
	}
	delete tail;
}

Set::Set(const Set& other) {			// COPY CONSTRUCTOR ------------------------------------------------------
	int it = 0;
	Node* t = head;
	for (Node* p = other.head; p != nullptr; p = p->next)
	{

		if (it == 0)		// assigns head
		{
			head = new Node;
			head->data = other.head->data;
			head->prev = nullptr;
			head->next = nullptr;
			it++;
			t = head;
			if (other.s_size == 1)		//assigns tail if size is 1
				tail = t;
			s_size++;
		}
		else
		{	
			Node* newNode = new Node;		 // allocates neww space
			newNode->data = p->data;
			t->next = newNode;
			newNode->prev = t;
			t = t->next;
			it++;
			s_size++;			// increments size
		}
	}
	if (it == other.s_size)		//assigns tail
	{
		t->next = nullptr;
		tail = t;
	}
	if (other.size() == 0)
	{
		head = tail = nullptr;
		s_size = 0;
	}
}

Set& Set::operator=(const Set& rhs) {			// ASSIGNMENT OPERATOR ------------------------------------------------------
	if (this != &rhs)
	{
		int original_size = s_size;
		for (int i = 0; i < original_size; i++)		// deletes the left hand side
		{
			ItemType temp;
			get(0, temp);
			erase(temp);
		}
		
		for (Node* p = rhs.head; p != nullptr; p = p->next)
			insert(p->data);						// inserts data
	}
	return *this;
}

bool Set::empty() const {						//  EMPTY() ------------------------------------------------------
	if (head == nullptr && tail == nullptr)
		return 1;
	if (s_size == 0)
		return 1;							// returns TRUE if set is empty
	else
		return 0;
}

int Set::size() const {							// SIZE() ------------------------------------------------------
	return s_size;								// returns the number of items in a set
}

bool Set::insert(const ItemType& value) {			// INSERT(value) ------------------------------------------------------
	if (contains(value))							// Inserts a value at the tail end of the list 
		return 0;									// if value is not yet present
	if (s_size == 0)
	{
		Node* newNode = new Node;
		head = newNode;					// is size = 1, assigns head and tail as the same
		tail = newNode;
		newNode->data = value;
		head->next = nullptr;
		head->prev = nullptr;
		s_size++;
		return 1;						// returns true if successful
	}
	Node* newNode = new Node;
	newNode->data = value;
	tail->next = newNode;
	newNode->prev = tail;
	tail = newNode;
	tail->next = nullptr;
	s_size++;						// increments size
	return 1;
}

bool Set::erase(const ItemType& value) {			// ERASE(value) ------------------------------------------------------
	bool erased = 0;								// finds value and erases it from the list if present
	for (Node* p = head; p != nullptr; p = p->next)
	{
		if (p->data == value) {
			erased = true;
			if (p == head)							// reassigns head if necessary 
			{
				if (s_size == 1) {
					delete p;
					s_size--;
					head = nullptr;
					tail = nullptr;
					return erased;
				}
				head = p->next;
				head->prev = nullptr;
			}
			else if (p == tail)						// reassigns tail if necessary
			{
				tail = p->prev;
				tail->next = nullptr;
			}
			else {									// else it is an element in the middle
				p->prev->next = p->next;
				p->next->prev = p->prev;
			}
			delete p;
			s_size--;
			break;
		}
	}// end of for loop

	return erased;									// returns TRUE if an element is erased
}

bool Set::contains(const ItemType& value) const {			// CONTAINS(value) ------------------------------------------------------
	for (Node* p = head; p != nullptr; p = p->next)			// checks if a list contains the value
	{
		if (p->data == value)
			return 1;									// returns true if it does
	}
	return 0;
}

bool Set::get(int pos, ItemType& value) const {				// GET(pos, value) ------------------------------------------------------
	if (pos >= s_size)										// copies data from that position in the list into value
		return 0;
	int it = 0;
	for (Node* p = head; p != nullptr; p = p->next)
	{	
		if (it >= pos) {					// stops to copy in data if at the right position
			value = p->data;
			break;
		}
		it++;
	}
	return 1;								// returns TRUE if successful
}

void Set::swap(Set& other) {			// SWAP (set) ---------------------------------------------------------
	int tmp = s_size;
	s_size = other.s_size;
	other.s_size = tmp;					// changes the sizes

	Node* temp;
	temp = head;
	head = other.head;
	other.head = temp;					// swaps the head pointers
	temp = tail;
	tail = other.tail;
	other.tail = temp;					// swaps the tail pointers
}


//--------------------------------------------------------------------------------------------------//
//-------------------------------NON MEMBER FUNCTIONS----------------------------------------------//
//------------------------------------------------------------------------------------------------//


void unite(const Set& s1, const Set& s2, Set& result)		// UNITE (set,set,set) -----------------------------------------------------
{
	if (&s1 == &result)
		return;
	int original_size = result.size();
	for (int i = 0; i < original_size; i++)		// deletes result
	{
		ItemType temp;
		result.get(0, temp);
		result.erase(temp);
	}
	for (int i = 0; i < s1.size(); i++)		// adds in s1
	{
		ItemType temp;
		s1.get(i, temp);
		result.insert(temp);
	}
	for (int i = 0; i < s2.size(); i++)		// adds in s2
	{
		ItemType temp;
		s2.get(i, temp);
		result.insert(temp);
	}
}

void subtract(const Set& s1, const Set& s2, Set& result)		// SUBTRACT (set, set, set) ------------------------------------------------
{
	if (&s1 == &result){							// checks for aliasing
		int original_size = result.size();
		for (int i = 0; i < original_size; i++)		// deletes result items which are present in s2
		{
			ItemType temp;
			result.get(i, temp);
			if (s2.contains(temp)){
				result.erase(temp);
				i--;
			}
		}
		return;
	}
	int original_size = result.size();
	for (int i = 0; i < original_size; i++)		// deletes result
	{
		ItemType temp;
		result.get(0, temp);
		result.erase(temp);
	}
	
	if (&s1 == &s2)						// checks for aliasing, does nothing if s1 and s2 are the same
		return;

	for (int i = 0; i < s1.size(); i++)		// adds in s1 only if it is not in s2
	{
		ItemType temp;
		s1.get(i, temp);
		if (!s2.contains(temp)) {
			result.insert(temp);
		}
	}
}

//
//
// Last updated April 19th 2016
//
// END OF FILE
//
//