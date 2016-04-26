// main()
//
// Project 4 TEST CASES
//
// Created by Tim Connors
//
// 

#include "Set.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {

	Set a;
	Set b;				// Check copy constructor
	Set c;
	c = b;					// Check assignment operator

	assert(a.size() == 0);				// Check that initial size is zero
	assert(a.size() == b.size());
	assert(b.size() == c.size());
	assert(a.empty() && b.empty() && c.empty());	// Check that EMPTY works

	a.insert("first");
	a.insert("second");
	a.insert("third");
	a.insert("third");

	assert(a.size() == 3); // Check that insert only works if value  is not already present

	b.insert("first");
	b.insert("second");
	b.insert("third");
	b.insert("fourth");

	c.insert("zero");

	Set d(c);	// Check the copy constructor with only one node
	assert(d.size() == 1);

	Set e(b);	// Check that the copy contructor works with multiple nodes
	assert(e.size() == b.size());

	assert(c.size() == 1); // Check that INSERT increases the size
	assert(!c.empty());

	unite(a, b, c);
	
	assert(c.contains("first") && c.contains("second") && c.contains("third") && c.contains("fourth"));	// Check that UNITE works properly

	unite(a, a, c);

	assert(c.contains("first") && c.contains("second") && c.contains("third") && c.size() == 3);	// Check aliasing case

	unite(a, b, a);

	assert(c.contains("first") && c.contains("second") && c.contains("third") && c.size() == 3);	// Check alternate aliasing case

	unite(a, a, a);

	assert(c.contains("first") && c.contains("second") && c.contains("third") && c.size() == 3);	// Check last aliasing case

	subtract(a, b, c);

	assert(c.size() == 0);	// Check that SUBTRACT works properly

	a.insert("fourth");
	a.insert("fifth");

	subtract(a, b, c);

	assert(c.size() == 1 && c.contains("fifth"));	// Check that SUBTRACT works properly


	subtract(a, a, c);

	assert(c.size() == 0);	// Check aliasing case

	subtract(a, b, a);

	assert(a.size() == 1 && a.contains("fifth"));	// Check alternate aliasing case

	subtract(b, b, b);

	assert(b.size() == 0);	// Check last aliasing case

	assert(!a.erase("not"));	// Check that erasing something that is not present returns false

	assert(a.erase("fifth"));	// Check that erasing something that is present returns true

	assert(a.size() == 0);	// Check that ERASE decreases size
	assert(b.size() == 0);
	assert(c.size() == 0);

	a.insert("first");
	a.insert("second");
	a.insert("third");

	b.insert("first");

	a.swap(b);			// Check that two reciprocal swaps cancel out
	b.swap(a);

	assert(a.contains("first") && a.contains("third") && a.contains("second"));	// Check that CONTAINS works properly
	assert(!c.contains("first"));	
	
	ItemType item;
	a.get(0, item);

	assert(item == "first");	// Check that GET works properly

	a.get(1, item);

	assert(item == "second");

	a.get(2, item);

	assert(item == "third");
	
	a.swap(b);					// Check that SWAP works properly

	assert(a.size() == 1 && a.contains("first") && b.size() == 3 && b.contains("first") && b.contains("second") && b.contains("third"));

	b.get(0, item);

	assert(item == "first");	// Check that SWAP works properly

	b.get(1, item);

	assert(item == "second");

	b.get(2, item);

	assert(item == "third");

	Set empty;
	Set not_empty(a);

	assert(empty.empty());
	assert(!not_empty.empty());

	empty.swap(not_empty);		// Check SWAP when swapping an empty set

	assert(!empty.empty());
	assert(not_empty.empty());
	
	cout << "Passed All Tests!" << endl << endl;
}
	
	