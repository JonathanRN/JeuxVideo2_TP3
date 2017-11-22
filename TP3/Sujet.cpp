//Notez que tous les sujets peuvent réutiliser cette classe intégralement.  Ce sera toujours la forme du sujet
//Notez aussi que les pointeurs vont toujours pointer vers des objets qui existent déjà ailleurs, donc pas de new et de delete ici.

#include "Sujet.h"
#include "IObservateur.h"

void Sujet::ajouterObservateur(IObservateur* observateur)
{
	//Si l'observateur n'est pas déjà dans la liste...
	if (!(std::find(observateurs.begin(), observateurs.end(), observateur) != observateurs.end()))
	{
		observateurs.push_back(observateur);
	}
}

void Sujet::retirerObservateur(IObservateur* observateur)
{
	//Pour retirer un observateur de la liste.  Deux pointeurs qui pointent à la même adresse sont égaux.
	for (int i = 0; i < observateurs.size(); i++)
	{
		if (observateurs[i] == observateur)
		{
			observateurs.erase(observateurs.begin() + i);
			return;
		}
	}
}

//Suite à une action on fait toujours ça.
void Sujet::notifierTousLesObservateurs()
{
	for (int i = 0; i < observateurs.size(); i++)
	{
		observateurs[i]->notifier(this);
	}
}