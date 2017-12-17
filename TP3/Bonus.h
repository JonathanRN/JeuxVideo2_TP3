#pragma once
#include"Sujet.h"
#include <SFML/Graphics.hpp>
using namespace sf;
namespace tp3
{
	class Bonus : public Sprite , public Sujet
	{
	public:
		Bonus(Vector2f position,Texture& texture);
		virtual void anim();
		virtual void initGraphiques();
		bool readyAnim = false;
		bool animTermine = false;
		~Bonus();
	};
}

