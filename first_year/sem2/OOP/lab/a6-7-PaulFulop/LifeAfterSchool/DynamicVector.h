#pragma once

template<typename T>
class DynamicVector {
public:
	int length, capacity;
	T* data;

	/**
		@brief DynamicVector object constructor
	**/
	DynamicVector();

	/**
		@brief DynamicVector copy constructor
		@param other - the DynamicVector object used for copying
	**/
	DynamicVector(const DynamicVector& other);

	/**
		@brief DynamicVector object destructor
	**/
	~DynamicVector();

	/**
		@brief  Adds an object at the end of the vector
		@param  new_object - the new object to be added
		@retval            - true if the object was added succsessfully, false otherwise
	**/
	bool Add(T new_object);

	/**
		@brief  Removes an object from the vector
		@param  object - the object to be removed
		@retval        - true if the object has been removed succsessfully, false otherwise
	**/
	bool Remove(T object);

	/**
		@brief  Updates an object from the vector
		@param  object     - the object that will be updated
		@param  new_object - the object that will replace the old one
		@retval            - true if the object has been updated succsessfully, false otherwise
	**/
	bool Update(T object, T new_object);

	/**
		@brief  Searches for an object through the vector
		@param  object - the object to search for
		@retval        - the position of the object in the array or -1 if no such object has been found
	**/
	int Search(T object);

	/**
		@brief Resizes the vector in case the length exceeds the capacity.
	**/
	void Resize();

	/**
		@brief  operator= Copy assignment operator
		@param  other - The DynamicVector object used for assignment
		@retval       - this object reference
	**/
	DynamicVector& operator=(const DynamicVector& other) noexcept;
};

template <typename T>
DynamicVector<T>::DynamicVector() : length{ 0 }, capacity{ 1 }, data{ new T[1] }
{}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector& other)
{
	length = other.length;
	capacity = other.capacity;

	data = new T[capacity];
	for (int i = 0; i < length; ++i)
		data[i] = other.data[i];
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] data;
}

template <typename T>
bool DynamicVector<T>::Add(T new_object)
{
	if (Search(new_object) != -1) return false;

	if (length == capacity)
		Resize();

	data[length++] = new_object;
	return true;
}

template <typename T>
bool DynamicVector<T>::Remove(T object)
{
	int pos = Search(object);
	if (pos == -1) return false;

	for (int i = pos; i < length - 1; ++i)
		data[i] = data[i + 1];

	--length;
	return true;
}

template <typename T>
bool DynamicVector<T>::Update(T object, T new_object)
{
	int pos = Search(object);
	if (pos == -1) return false;

	data[pos] = new_object;
	return true;
}

template <typename T>
int DynamicVector<T>::Search(T object)
{
	for (int i = 0; i < length; ++i)
		if (data[i] == object)
			return i;

	return -1;
}

template <typename T>
void DynamicVector<T>::Resize()
{
	capacity *= 2;
	T* new_data = new T[capacity];

	for (int i = 0; i < length; ++i)
		new_data[i] = data[i];

	delete[] data;
	data = new_data;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& other) noexcept
{
	delete[] data;

	length = other.length;
	capacity = other.capacity;

	data = new T[capacity];
	for (int i = 0; i < length; ++i)
		data[i] = other.data[i];

	return *this;
}