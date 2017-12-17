#pragma once
#include "Projectile.h"
namespace tp3
{
	class Projectile_Missile : public Projectile
	{
	public:
		Projectile_Missile(Vector2f position, float vitesse, Texture& texture, float angle);
		void anim(int direction);
		void initGraphiques();
		~Projectile_Missile();
	private:
		static const int NOMBRES_ANIM = 8;
	};
}

