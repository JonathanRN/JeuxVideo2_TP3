#pragma once
#include <vector>
#include <iostream>

template <class T>
class File
{
private:
	T* tab;
	File<T>(const File&) = delete;
	size_t cap;
	size_t size;
	size_t head;
	
public:
	File();
	File(const File<T>& other);
	~File();

	bool empty();
	size_t size();
	size_t capacity();
	void reserve(size_t new_cap);

	T front();
	T back();

	void clear();
	void push_back(const T& value);
	T pop_back();
	void push_front(const T& value);
	T pop_front();
	void resize(size_t new_size);

	T operator[](const size_t index);
};

template <class T>
File<T>::File() : tab(nullptr), size(0), cap(0), head(0)
{

}

template <class T>
File<T>::~File()
{
	clear();
}

template <class T>
size_t File<T>::size()
{
	return size;
}

template <class T>
size_t File<T>::capacity()
{
	return cap;
}

template <class T>
bool File<T>::empty()
{
	return size == 0;
}

template <class T>
T File<T>::front()
{
	return tab[0];
}

template <class T>
bool File<T>::back()
{
	return tab[size - 1];
}

template <class T>
File<T>::clear()
{
	size = 0;
	cap = 0;
	delete[] tab;
	tab = nullptr;
}

template <class T>
void File<T>::push_back(const T& value)
{
	if (size != cap)
	{
		tab[(head + size) % cap] = value;
		size++;
	}
}

template<class T>
T File<T>::pop_back()
{
	T temp = tab[(size + head) % cap];
	tab[(size+head)%cap] = NULL;
	size--;
	return temp;
}

template <class T>
void File<T>::push_front(const T& value)
{
	// A REVOIR
	if (size != cap)
	{
		if (head == 0)
		{
			tab[abs((head - size) % cap)] = value;
		}
		else
		{
			head--;
			tab[head] = value;
		}
	}
}

template <class T>
T File<T>::pop_front()
{
	T temp = tab[head];
	tab[head] = NULL;
	head = (head + 1) % cap;
	size--;
	return temp;
}

template<class T>
void File<T>::reserve(size_t new_cap)
{
	if (cap < new_cap)
	{
		auto tmp = tab;
		tab = new int[new_cap];

		size_t i = 0;

		for (; i < size; ++i)
			tab[i] = tmp[i];
		
		for (; i < new_cap; ++i)
			tab[i] = int();

		cap = new_cap;
	}
}

template<class T>
void File<T>::resize(size_t new_size)
{
	reserve(new_size);

	for (size_t i = new_size - 1; i < size; ++i)
		tab[i] = int();

	size = new_size;
}

template<class T>
File<T>::File(const File<T>& other)
{
	*this = other;
}

template<class T>
T File<T>::operator[](const size_t index)
{
	return tab[(head + index) % cap];
}

