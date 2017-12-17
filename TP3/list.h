#ifndef _LIST_H_
#define _LIST_H_

/**********************************************************
Description de la representation

Chaine double de boites
Une boite supplementaire a la fin,
nommee apres en memoire automatique (non dynamique)
Une boite supplementaire au debut nommee avant 
en memoire automatique (non dynamique) dont le suivant 
pointe sur la premiere boite
size contient le nombre d'elements dans la liste


iterator: pointeur sur la boite concernee,
la fin est un pointeur sur la boite de queue (apres)

reverse_iterator: pointeur sur la boite qui concernee
(rbegin: celle pointe par le precedent de apres, rend: avant)

RESTRICTION par rapport a la SL
pas de const_iterator, donc pas d'iteration possible
sur une list const.

**********************************************************/

template <class TYPE>
class list {

private:
	struct boite {
		TYPE valeur;
		boite *suiv, *prec;
		boite(const TYPE C, boite*S = nullptr, boite*P = nullptr)
		{
			valeur = C;
		    suiv = S;
		    prec = P;
		}//a implanter
		boite()
		{
			suiv = nullptr;
			prec = nullptr;
		}
		~boite() { prec = suiv = nullptr; } //je vous le donne en cadeau
	};
	boite avant;
	boite apres;
	size_t nbElem;
	
	//fonctions generatrices privees
	boite* insert(boite*, const TYPE&); //inserer avant cette boite 
	boite* erase(boite*); //enlever cette boite

public:
	class iterator;
	iterator iterateur;
	//class const_iterator; //Optionnel
	//class reverse_iterator; //Optionnel
	//class const_reverse_iterator; //Optionnel

	list(); //constructeur
	~list(); //destructeur
	list(const list&); //copie constructeur
	list(std::initializer_list<TYPE>);
	list& operator=(const list& other);  //affectateur. copie les elements de other dans la file courante. O(n) 
	void swap(list& other); //echange les element des files courante et other O(1);

	iterator insert(iterator pos, const TYPE value) //ajoute un element AVANT la boite en position pos. retourne un iterateur sur la nouvelle boite. O(1)
	{
		boite* temp = pos->prec;
		pos->prec = new boite(value, pos, temp);
		temp->suiv = pos->prec;
		nbElem++;
	    return pos->prec;
	}
	iterator erase(iterator pos); //enleve l'element a la position pos. retourne un iterateur sur l'element suivant celui qui est retire. O(1)
	//reverse_iterator insert(reverse_iterator, const TYPE&); //Optionnel, comme les methodes precedentes mais avec un reverse iterator
	//reverse_iterator erase(reverse_iterator);  //Optionnel, comme les methodes precedentes mais avec un reverse iterator

	void push_back(const TYPE valeur);  //Ajoute un element a la fin de la liste. O(1)
	void pop_back();			  //Enleve un element a la fin de la liste. O(1)
	void push_front(const TYPE valeur); //Ajoute un element au debut de la liste. O(1)
	void pop_front();			  //Enleve un element au debut de la liste. O(1)
	TYPE& back(); //Retourne une reference sur le dernier element de la liste. O(1)
	TYPE& front(); //Retourne une reference sur le premier element de la liste. O(1)
	//const TYPE& back()const;	//Optionnel version const de la precedente
	//const TYPE& front()const; //Optionnel version const de la precedente

	void clear();
	size_t size()const;
	bool empty()const;

	iterator begin(); //Retourne un iterateur sur la boite suivant avant.
	iterator end()
	{
		return apres.prec;
	}//Retourne un iterateur sur la boite apres.
	//reverse_iterator rbegin(); //Optionnel version inverse des methodes precedentes
	//reverse_iterator rend(); //Optionnel version inverse des methodes precedentes

							 //algorithmes
	void reverse(); //Inverse l'ordre des elements de la liste. O(n)
	void splice(iterator pos, list& other); //Transfere les elements contenu dans other vers la liste courante. les element sont ajouter avant la boite en position pos. O(1)
	//void resize(size_t newSize, const TYPE& valeur= TYPE()); //Optionnel permet d'ajuster le nombre d'element de la liste. initialise les nouveaux element a valeur. Potentiellement O(n)
};

template <typename TYPE>
list<TYPE>::list() 
{
	avant.suiv = &apres;
	apres.prec = &avant;
	nbElem = 0;
	
}
template <typename TYPE>
list<TYPE>::~list()
{
	while(!empty())
	{
		pop_back();
	}
	avant.suiv = &apres;
	apres.prec = &avant;
	nbElem = 0;
	iterateur = end();
}
template <typename TYPE>
void list<TYPE>::clear()
{
	~list();
}
template <typename TYPE>
size_t list<TYPE>::size()const
{
	return nbElem;
}
template <typename TYPE>
bool list<TYPE>::empty()const
{
	if (nbElem == 0)
	{
		return true;
	}
	return false;
}
template <typename TYPE>
void list<TYPE>::push_back(const TYPE valeur)
{
	boite* temp = apres.prec;
	temp->suiv = new boite(valeur, &apres, temp);
	apres.prec = temp->suiv;
	iterateur.POINTEUR = temp->suiv;
	nbElem++;
}
template <typename TYPE>
void list<TYPE>::pop_front()
{
	boite* temp = avant.suiv;
	avant.suiv = temp->suiv;
	avant.suiv->prec = &avant;
	nbElem--;
	delete temp;
}
template <typename TYPE>
void list<TYPE>::pop_back()
{
	boite* temp = apres.prec;
	apres.prec = temp->prec;
	apres.prec->suiv = &apres;
	nbElem--;
	delete temp;
}
template <typename TYPE>
void list<TYPE>::push_front(const TYPE valeur)
{
	boite* temp = avant.suiv;
	temp->prec = new boite(valeur, &avant, temp);
	avant->suiv = temp->prec;
	iterateur.POINTEUR = temp->prec;
	nbElem++;
}
template <typename TYPE>
TYPE& list<TYPE>::back()
{
	return apres->prec;
}
template <typename TYPE>
TYPE& list<TYPE>::front()
{
	return avant.suiv;
}
//template <typename TYPE>
//iterator list<TYPE>::begin()
//{
//	return avant->next;
//}
//template <typename TYPE>
//iterator list<TYPE>::end()
//{
//
//}
//template <typename TYPE>
//iterator list<TYPE>::insert(iterator pos, const TYPE value)
//{
//	boite* temp = pos->prec;
//	pos->prec = new boite(value, pos, temp);
//	temp->suiv = pos->prec;
//	size++;
//	return pos->prec;
//}
//template <typename TYPE>
//iterator list<TYPE>::erase(iterator pos)
//{
//	pos->prec->suiv = pos->suiv;
//	pos->suiv->prec = pos->prec;
//	size--;
//	return pos->suiv;
//}


///////////////////////////////////////////////////////////
//la classe iterator
///////////////////////////////////////////////////////////

template <typename TYPE>
class list<TYPE>::iterator {
	friend class list<TYPE>;
private:
	
public:
    boite* POINTEUR;
	
	iterator(boite*c = nullptr) :POINTEUR(c) {} // cadeau
	TYPE operator*()const //Dereference l'iterateur
	{
		//TODO a faire...
		if (POINTEUR != nullptr)
		{
			return POINTEUR->valeur;
		}
	}

	TYPE* operator->()const { return &(POINTEUR->CONTENU); } //Autre dereference en cadeau.
	
	iterator& operator++() //++i
	{
		POINTEUR = POINTEUR->suiv;
		return *this;
	}

	iterator& operator++(int) {   //i++
		if (POINTEUR != nullptr)
		{
			POINTEUR = POINTEUR->suiv;
		}
		return *this;
	}

	iterator& operator--() //--i
	{
		POINTEUR = POINTEUR->prec;
		return *this;
	}
	iterator& operator--(int) {   //i--
		if (POINTEUR != nullptr)
		{
			POINTEUR = POINTEUR->prec;
		}

		return *this;
	}
	bool operator==(const iterator&droite)const { //Cadeau! comparaison d'iterateur
		return POINTEUR == droite.POINTEUR;
	}
	bool operator!=(const iterator&droite)const { //Cadeau! comparaison d'iterateur
		return POINTEUR != droite.POINTEUR;
	}
};
#endif //_LIST_H