
#ifndef SET_H
#define SET_H


#include <string>
using namespace std;
typedef string ItemType;


class Set
{
public:
	Set();
	~Set();
	Set(const Set& other);
	Set& Set::operator=(const Set& rhs);
	bool empty() const;
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int pos, ItemType& value) const;
	void swap(Set& other);
private:
	struct Node
	{
		ItemType data;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
	int s_size = 0;
};

void unite(const Set& s1, const Set& s2, Set& result);

void subtract(const Set& s1, const Set& s2, Set& result);

#endif