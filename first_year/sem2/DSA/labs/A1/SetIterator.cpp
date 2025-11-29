#include "SetIterator.h"
#include "Set.h"
#include <exception>

/*
BC: theta(1)
WC: theta(1)
TC: theta(1)
*/
SetIterator::SetIterator(const Set& m) : set(m), position(0)
{}

/*
BC: theta(1)
WC: theta(1)
TC: theta(1)
*/
void SetIterator::first() {
	position = 0;
}

/*
BC: theta(1)
WC: theta(1)
TC: theta(1)
*/
void SetIterator::next() {
	if (!valid())
		throw std::exception("Out of bounds!");
	++position;
}

/*
BC: theta(1)
WC: theta(1)
TC: theta(1)
*/
TElem SetIterator::getCurrent()
{
	if (!valid())
		throw std::exception("Out of bounds!");
		
	return set.data[position];
}

/*
BC: theta(1)
WC: theta(1)
TC: theta(1)
*/
bool SetIterator::valid() const {
	return position < set.length;
}