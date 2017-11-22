#include "SceneCombat.h"

using namespace tp3;

SceneCombat::SceneCombat():fond(LARGEUR_ECRAN, HAUTEUR_ECRAN, 5), thrust(0), mouvementJoueur(0, 0)
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
	if (!Player_up_down.loadFromFile("Ressources\\Player_up_down.png"))
	{
		return false;
	}
	if (!Player_pivot.loadFromFile("Ressources\\Player_pivot.png"))
	{
		return false;
	}
	if (!death.loadFromFile("Ressources\\death.png"))
	{
		return false;
	}

	vaisseauJoueur.setTexture(Player_up_down);
	vaisseauJoueur.setPosition(100, 100);
	vaisseauJoueur.initGraphiques();

	this->mainWin = window;
	isRunning = true;
	return true;
}

void SceneCombat::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin à l'application
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		mouvementJoueur.x = -1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		mouvementJoueur.x = 1;
	}
	else
	{
		mouvementJoueur.x = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		mouvementJoueur.y = -1;
		vaisseauJoueur.monter();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		mouvementJoueur.y = 1;
		vaisseauJoueur.descendre();
	}
	else
	{
		mouvementJoueur.y = 0;
		vaisseauJoueur.centrer();
	}
}

void SceneCombat::update()
{
	fond.move(thrust);
	vaisseauJoueur.mouvementJoueur(mouvementJoueur);
}

void SceneCombat::draw()
{
	mainWin->clear();
	fond.draw(mainWin);
	mainWin->draw(vaisseauJoueur);
	mainWin->draw(testText);
	mainWin->display();
}
