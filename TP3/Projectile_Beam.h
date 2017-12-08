#pragma once
#include "Projectile.h"
namespace tp3
{
	class Projectile_Beam : public Projectile
	{
	public:
		Projectile_Beam(Vector2f position, float vitesse, Texture& texture, float angle);
		void anim(int direction);
		void initGraphiques();
		~Projectile_Beam();
	private:
		static const int NOMBRES_ANIM = 12;
	};
}

