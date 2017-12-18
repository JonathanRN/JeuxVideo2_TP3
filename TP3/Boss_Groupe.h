#pragma once
#include <vector>
#include "Enemy.h"
#include "Enemy_Boss.h"
#include "Boss.h"

namespace tp3
{
	class Boss_Groupe : public Enemy
	{
	public:
		Boss_Groupe();
		~Boss_Groupe();
		virtual void bouger();
		virtual void arreter();

		//Permettent de gerer la collection de componants
		void ajouter(IComponant* vaisseau);
		void retirer(int i);
		void vider();

	private:
		std::vector<IComponant*> groupe; //Vector du composite
	};
}

