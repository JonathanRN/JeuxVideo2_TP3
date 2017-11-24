#pragma once
#include "Projectile.h"
namespace tp3
{
	class Projectile_normal : public Projectile
	{
	public:
		Projectile_normal(Vector2f position, float vitesse,Texture& texture);
		void anim();
	    void initGraphiques();
		~Projectile_normal();
	private:
		static const int NOMBRES_ANIM = 10;
	};
}

