#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

	class IObservateur;

	using std::vector;

	class Sujet 
	{
	public:
		void ajouterObservateur(IObservateur* observateur);
		void retirerObservateur(IObservateur* observateur);
		/// <summary>
		/// Virtuel seulement pour que Sujet fonctionne avec typeid
		/// </summary>
		virtual void notifierTousLesObservateurs();

	protected:
		vector<IObservateur*> observateurs;
	};
