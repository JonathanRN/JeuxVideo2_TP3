#include "SceneCombat.h"

using namespace tp3;

SceneCombat::SceneCombat():fond(LARGEUR_ECRAN, HAUTEUR_ECRAN, 5), thrust(0)
{
}


SceneCombat::~SceneCombat()
{
}

Scene::scenes SceneCombat::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneCombat::init(RenderWindow * const window)
{
	if (!fond.setTexture("Ressources\\spaceBackground.jpg"))
	{
		return false;
	}
	this->mainWin = window;
	isRunning = true;
	return true;
}

void SceneCombat::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fen�tre ne mettrait pas n�cessairement 
			//fin � l'application
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}
	}
}

void SceneCombat::update()
{
	fond.move(thrust);
}

void SceneCombat::draw()
{
	mainWin->clear();
	fond.draw(mainWin);
	mainWin->draw(testText);
	mainWin->display();
}
