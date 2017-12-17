#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
namespace tp3
{
	class Projectile : public Sprite
	{
	public:
		Projectile(const Vector2f& position, const Color& couleur, const int animationMaximale);
		~Projectile();
		float vitesse;
		float angle;
		virtual void initGraphiques() = 0;
		virtual void anim(int direction) = 0;
		bool animTermine = false;
		bool hasBeenShot = false;
		void activer();
	protected:
		static const int RHYTME_ANIM = 4;
		int animation;
		const int ANIMATION_MAXIMALE;
		bool actif;
		int image;
		IntRect rectangleAnimation;
	};
}

