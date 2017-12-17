#pragma once

template <class T>
class File
{
public:
	File<T>::File();
	File<T>::~File();

	bool File<T>::empty();
	bool File<T>::full();
	size_t File<T>::size();
	size_t File<T>::capacity();
	void File<T>::reserve(const size_t new_cap);

	T File<T>::front();
	T File<T>::back();

	void File<T>::clear();
	void File<T>::push_back(const T& value);
	T File<T>::pop_back();
	void File<T>::push_front(const T& value);
	T File<T>::pop_front();
	void File<T>::resize(const size_t new_size);

	T File<T>::operator[](const size_t index);

private:
	T* tab;
	size_t cap;
	size_t nbElem;
	size_t head;
};

template <class T>
File<T>::File() : tab(nullptr), nbElem(0), cap(0), head(0)
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
	return nbElem;
}

template <class T>
size_t File<T>::capacity()
{
	return cap;
}

template <class T>
bool File<T>::empty()
{
	return nbElem == 0;
}

template <class T>
bool File<T>::full()
{
	return nbElem == cap;
}

template <class T>
T File<T>::front()
{
	return tab[0];
}

template <class T>
T File<T>::back()
{
	return tab[nbElem - 1];
}

template <class T>
void File<T>::clear()
{
	nbElem = 0;
	head = 0;
	cap = 0;
	delete[] tab;
	tab = nullptr;
}

template <class T>
void File<T>::push_back(const T& value)
{
	if (nbElem != cap)
	{
		tab[(head + nbElem) % cap] = value;
		nbElem++;
	}
}

template<class T>
T File<T>::pop_back()
{
	T temp = tab[(nbElem + head) % cap];
	tab[(nbElem +head)%cap] = nullptr;
	nbElem--;
	return temp;
}

template <class T>
void File<T>::push_front(const T& value)
{
	// A REVOIR
	if (nbElem != cap)
	{
		if (head == 0)
		{
			tab[abs((head - nbElem) % cap)] = value;
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
	tab[head] = nullptr;
	head = (head + 1) % cap;
	nbElem--;
	return temp;
}

template<class T>
void File<T>::reserve(size_t new_cap)
{
	if (cap < new_cap)
	{
		auto tmp = tab;
		tab = new T[new_cap];

		size_t i = 0;

		for (; i < nbElem; ++i)
			tab[i] = tmp[i];
		
		for (; i < new_cap; ++i)
			tab[i] = nullptr;

		cap = new_cap;
	}
}

template<class T>
void File<T>::resize(size_t new_size)
{
	reserve(new_size);

	for (size_t i = new_size - 1; i < nbElem; ++i)
		tab[i] = nullptr;

	nbElem = new_size;
}

template<class T>
T File<T>::operator[](const size_t index)
{
	return tab[(head + index) % cap];
}

