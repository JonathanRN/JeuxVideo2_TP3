#include "SceneCombat.h"

using namespace tp3;

SceneCombat::SceneCombat():fond(LARGEUR_ECRAN, HAUTEUR_ECRAN, 5), thrust(0), mouvementJoueur(0, 0)
{
	for (int i = 0; i < NBR_PROJ; i++)
	{
		projectiles[i] = nullptr;
	}
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
	for (int i = 0; i < NBR_PROJ; i++)
	{
		if (projectiles[i] != nullptr)
		{
			delete projectiles[i];
		}
	}
	
	return transitionVersScene;
}

bool SceneCombat::init(RenderWindow * const window)
{
	if (!fond.setTexture("Ressources\\spaceBackground.jpg"))
	{
		return false;
	}
	if (!projectileT[0].loadFromFile("Ressources\\Projectile_normal.png"))
	{
		return false;
	}
	if (!player.loadFromFile("Ressources\\Player.png"))
	{
		return false;
	}

	vaisseauJoueur.setTexture(player);
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
	else if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		vaisseauJoueur.pivoter();
	}
	else if (Keyboard::isKeyPressed(Keyboard::X))
	{
		ajouterProjectile(vaisseauJoueur.getPosition());
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
	for (size_t i = 0; i < NBR_PROJ; i++)
	{
		if (projectiles[i] != nullptr)
		{
			projectiles[i]->anim();
			projectiles[i]->move(projectiles[i]->vitesse, 0);
		}
		
	}
}

void SceneCombat::draw()
{
	mainWin->clear();
	fond.draw(mainWin);
	for (int i = 0; i < NBR_PROJ; i++)
	{
		if (projectiles[i] != nullptr)
		{
			mainWin->draw(*projectiles[i]);
		}
	}
	mainWin->draw(vaisseauJoueur);
	mainWin->draw(testText);
	mainWin->display();
}

void tp3::SceneCombat::ajouterProjectile(Vector2f position)
{
	for (int i = 0; i < NBR_PROJ; i++)
	{
		if (projectiles[i] == nullptr)
		{
			projectiles[i] = new Projectile_normal(Vector2f(position.x, position.y), 5, projectileT[0]);
			projectiles[i]->initGraphiques();
			projectiles[i]->activer();
			return;
		}
	}
}
