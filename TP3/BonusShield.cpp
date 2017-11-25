#include "BonusShield.h"
using namespace tp3;


BonusShield::BonusShield(Vector2f position,Texture& texture):Bonus(position,texture)
{
	setScale(getScale().x * 0.2, getScale().y * 0.2);
}


BonusShield::~BonusShield()
{
}
