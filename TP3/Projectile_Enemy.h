#pragma once
#include "Projectile.h"
namespace tp3
{
	class Projectile_Enemy : public Projectile
	{
	public:
		Projectile_Enemy(Vector2f position, float vitesse, Texture& texture,Color color);
		void anim(int direction);
		void initGraphiques();
		~Projectile_Enemy();
	};
}

