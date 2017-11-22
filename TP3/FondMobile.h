#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>

using namespace sf;
namespace tp3
{
	class FondMobile
	{
	public:
		FondMobile(const int largeur, const int hauteur, const int vitesse);
		

		bool setTexture(const char * path);
		void move(const int thrust);
		void draw(RenderWindow* rw);

	private:
		const int LARGEUR_ECRAN;
		const int HAUTEUR_ECRAN;

		Sprite fondEcran;
		Texture fondEcranT;

		Vector2f positions[2];
		int vitesse;
	};
}

//VERSION AVEC DES RECTANGLES TAILLÉES, UN  PEU PLUS COMPLEXE

//class FondMobile
//{
//public:
//	FondMobile(const int largeur, const int hauteur, const int vitesse);
//
//	bool setTexture(const char * path);
//	void move(const int thrust);
//	void draw(RenderWindow* rw);
//
//private:
//	Sprite fondEcran;
//	Texture fondEcranT;
//	
//	IntRect rectPrincipal;
//	IntRect rectAppoint;
//
//	int vitesse;
//
//	const int LARGEUR_ECRAN;
//	const int HAUTEUR_ECRAN;
//};

