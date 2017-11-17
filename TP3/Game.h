#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

class Game
{
public:
	Game();
	int run();
	int testTest();

private:
	const int LARGEUR = 1280;
	const int HAUTEUR = 720;

	bool init();
	void getInputs();
	void update();
	void draw();

	static const int NOMBRE_DE_RETARDS_QUI_TRAVAILLENT_SUR_LE_PROJET = 2; //kev et jo

	RenderWindow mainWin;
	View view;
	Event event;
};