#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <exception>
#include <iostream>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

}

void testJumpForward()
{
	std::cout << "Test jump forward\n";
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	// 0 5 5 6 8 10
	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	
	it.jumpForward(3);
	assert(it.getCurrent() == 6);
	
	try {
		it.jumpForward(0);
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}

	try {
		it.jumpForward(-1);
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	
	it.jumpForward(10);
	assert(it.valid() == false);
}
