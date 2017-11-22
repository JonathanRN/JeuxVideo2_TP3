#include "SceneTitre.h"

using namespace tp3;

SceneTitre::SceneTitre()
{
}


SceneTitre::~SceneTitre()
{
}

Scene::scenes SceneTitre::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneTitre::init(RenderWindow * const window)
{
	this->mainWin = window;
	isRunning = true;
	return true;
}

void SceneTitre::getInputs()
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

void SceneTitre::update()
{
}

void SceneTitre::draw()
{
	mainWin->clear();
	mainWin->draw(testText);
	mainWin->display();
}
