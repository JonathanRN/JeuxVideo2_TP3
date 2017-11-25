#include "SceneCombat.h"

using namespace tp3;

SceneCombat::SceneCombat():fond(LARGEUR_ECRAN, HAUTEUR_ECRAN, 5), thrust(1), mouvementJoueur(0, 0)
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
	delete ennemis[0];
	
	return transitionVersScene;
}

bool SceneCombat::init(RenderWindow * const window)
{
	if (!fond.setTexture("Ressources\\background.jpg"))
	{
		return false;
	}
	if (!projectileT[0].loadFromFile("Ressources\\Projectile_normal.png"))
	{
		return false;
	}
	if (!bonusT[0].loadFromFile("Ressources\\Bonus_shield.png"))
	{
		return false;
	}
	if (!player.loadFromFile("Ressources\\Player.png"))
	{
		return false;
	}
	if (!shield.loadFromFile("Ressources\\Shield.png"))
	{
		return false;
	}
	if (!ennemisT[0].loadFromFile("Ressources\\enemy1.png"))
	{
		return false;
	}
	

	vaisseauJoueur.setTexture(player);
	vaisseauJoueur.setPosition(100, 100);
	vaisseauJoueur.initGraphiques();

	ennemis.push_back(new Enemy1({ LARGEUR_ECRAN + 100, 100 }, ennemisT[0]));

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

	//Tirer
	if (Keyboard::isKeyPressed(Keyboard::X))
	{
		if (clock_tirer.getElapsedTime().asMilliseconds() >= 100)
		{
			ajouterProjectile(vaisseauJoueur.getPosition());
			clock_tirer.restart();
		}
	}

	//Mouvements gauche et droite
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

	//Mouvement haut et bas
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

	//Pivoter
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (clock_pivoter.getElapsedTime().asSeconds() >= 1)
		{
			vaisseauJoueur.pivoter();
			clock_pivoter.restart();
		}
	}
		
}

void SceneCombat::update()
{
	fond.move(thrust);
	vaisseauJoueur.mouvementJoueur(mouvementJoueur);

	//Projectiles
	for (size_t i = 0; i < NBR_PROJ; i++)
	{
		if (projectiles[i] != nullptr)
		{
			projectiles[i]->anim(vaisseauJoueur.direction);
			projectiles[i]->move(projectiles[i]->vitesse, 0);
			if (projectiles[i]->getPosition().x > LARGEUR_ECRAN || projectiles[i]->getPosition().x < 0)
			{
				delete projectiles[i];
				projectiles[i] = nullptr;
			}
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
	mainWin->draw(*ennemis.at(0));
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
			projectiles[i] = new Projectile_normal(Vector2f(position.x, position.y), 20 * vaisseauJoueur.direction, projectileT[0]);
			projectiles[i]->initGraphiques();
			projectiles[i]->activer();
			return;
		}
	}
}
