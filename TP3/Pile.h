#pragma once
#include <vector>
template<class T>
class Pile
{
public:
	void Pile<T>::push(const T& valeur);
	T Pile<T>::pop();
	bool Pile<T>::empty();
	size_t Pile<T>::size();
	T Pile<T>::top();


	Pile<T>::Pile();
	Pile<T>::~Pile();
private:
	std::vector<T> pile;
	Pile<T>(const Pile&) = delete;
};
	template<class T>
	Pile<T>::Pile()
	{
	}
	template<class T>
	void Pile<T>::push(const T& valeur)
	{
		pile.push_back(valeur);
	}
	template<class T>
	T Pile<T>::pop()
	{
		T temp = pile.back();
		pile.pop_back();
		return temp;
	}
	template<class T>
	bool Pile<T>::empty()
	{
		return pile.empty();
	}
	template<class T>
	size_t Pile<T>::size()
	{
		return pile.size();
	}
	template<class T>
	T Pile<T>::top()
	{
		return pile.back();
	}
	template<class T>
	Pile<T>::~Pile()
	{
		for (size_t i = 0; i < pile.size(); i++)
		{
			delete pile[i];
		}
	}




