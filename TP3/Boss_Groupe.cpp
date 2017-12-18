#include "Boss_Groupe.h"

using namespace tp3;

Boss_Groupe::Boss_Groupe()
{
}

Boss_Groupe::~Boss_Groupe()
{
	vider();
}

/// <summary>
/// Appelle la fonction bouger de toutes les ennemis dans le composite
/// </summary>
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

/// <summary>
/// Appelle la fonction arreter de toutes les ennemis dans le composite
/// </summary>
void tp3::Boss_Groupe::arreter()
{
	for (int i = 0; i < groupe.size(); i++)
	{
		groupe[i]->arreter();
	}
}

/// <summary>
/// Ajoute un vaisseau dans la liste du composite
/// </summary>
/// <param name="vaisseau">The vaisseau.</param>
void tp3::Boss_Groupe::ajouter(IComponant * vaisseau)
{
	groupe.push_back(vaisseau);
}

/// <summary>
/// Retirer le vaisseau de la liste selon un index
/// </summary>
/// <param name="i">The i.</param>
void tp3::Boss_Groupe::retirer(int i)
{
	groupe.erase(groupe.begin() + i);
}

/// <summary>
/// Vide le vector
/// </summary>
void tp3::Boss_Groupe::vider()
{
	groupe.clear();
}
