#include "Boss_Groupe.h"

using namespace tp3;

Boss_Groupe::Boss_Groupe()
{
}

Boss_Groupe::~Boss_Groupe()
{
	vider();
}

void tp3::Boss_Groupe::bouger()
{
	for (int i = 0; i < groupe.size(); i++)
	{
		if (typeid(*groupe[i]) == typeid(Enemy_Boss) || typeid(*groupe[i]) == typeid(Boss))
		{
			groupe[i]->bouger();
		}
	}
}

void tp3::Boss_Groupe::arreter()
{
	for (int i = 0; i < groupe.size(); i++)
	{
		groupe[i]->arreter();
	}
}

void tp3::Boss_Groupe::ajouter(IComponant * vaisseau)
{
	groupe.push_back(vaisseau);
}

void tp3::Boss_Groupe::retirer(int i)
{
	groupe.erase(groupe.begin() + i);
}

void tp3::Boss_Groupe::vider()
{
	groupe.clear();
}
