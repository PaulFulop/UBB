#include "Set.h"
#include "SetITerator.h"

/*
BC: theta(1)
WC: theta(1)
TC: theta(1)
*/
Set::Set() : length(0), capacity(1), data(new TElem[1])
{}

/*
BC: theta(1) -> we found the element on the first position and false is returned
WC: theta(n) -> 2 * length iterations if we didn't find the element and we need to reallocate space for the array
TC: theta(n)
*/
bool Set::add(TElem elem) {
	if (search(elem))
		return false;

	if (length == capacity)
	{
		capacity *= 2;
		TElem* new_data = new TElem[capacity];
		
		for (int i = 0; i < length; ++i)
			new_data[i] = data[i];

		delete[] data;
		data = new_data;
	}

	++length;
	data[length-1] = elem;
	return true;
}

/*
BC: theta(n) -> if elem = data[0] => shifting elements will take n - 1 iterations
			 -> if elem = data[length] => we don't even go through the second loop, but we find the position of elem after n - 1 iterations
WC: theta(n)
TC: theta(n)
*/
bool Set::remove(TElem elem) {

	int pos = -1;
	for(int i = 0; i < length; ++i)
		if (data[i] == elem)
		{
			pos = i;
			break;
		}

	if (pos == -1) return false;
	

	for (int i = pos; i < length - 1; ++i)
		data[i] = data[i + 1];
	--length;

	return true;
}

/*
BC: theta(1) -> elem = data[0]
WC: theta(n) -> elem is the last element / we dont find the element 
TC: O(n)
*/
bool Set::search(TElem elem) const {
	for (int i = 0; i < length; ++i)
		if (data[i] == elem)
			return true;

	return false;
}

/*
BC: theta(n * (n + 1)/2) -> the sets are equivalent so we find the elements at position 0, 1, 2, ... n - 1 => 1 + 2 + 3 + ... + n => n * (n + 1)/2
WC: theta(n^2) -> there are no elements which appear in s so the search function will always do n operations
TC: theta(n^2)
*/
void Set::intersection(const Set& s)
{
	for (int i = length - 1; i >= 0; --i)
		if (!s.search(data[i]))
			this->remove(data[i]);
}

/*
BC: theta(1)
WC: theta(1)
TC: theta(1)
*/
int Set::size() const {
	return length;
}

/*
BC: theta(1)
WC: theta(1)
TC: theta(1)
*/
bool Set::isEmpty() const {
	return length == 0;
}

/*
BC: theta(1)
WC: theta(1)
TC: theta(1)
*/
Set::~Set() {
	delete[] data;
}

/*
BC: theta(1)
WC: theta(1)
TC: theta(1)
*/
SetIterator Set::iterator() const {
	return SetIterator(*this);
}


