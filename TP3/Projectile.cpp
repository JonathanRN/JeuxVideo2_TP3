#include "Projectile.h"
using namespace tp3;

tp3::Projectile::Projectile(const Vector2f& position, const Color& couleur, const int animationMaximale)
	: ANIMATION_MAXIMALE(animationMaximale),
	animation(0), actif(false)
{
	setPosition(position);
	setColor(couleur);
}

Projectile::~Projectile()
{
}

void tp3::Projectile::initGraphiques()
{
	
}

void tp3::Projectile::activer()
{
	actif = true;
}
