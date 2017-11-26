#include "SceneCombat.h"

using namespace tp3;

SceneCombat::SceneCombat():fond(LARGEUR_ECRAN, HAUTEUR_ECRAN, 5), thrust(1), mouvementJoueur(0, 0)
{
	for (int i = 0; i < NBR_PROJ; i++)
	{
		projectiles[i] = nullptr;
	}
	for (int i = 0; i < NBR_PROJ; i++)
	{
		projectilesEnemy[i] = nullptr;
	}
	for (int i = 0; i < NBR_BONUS; i++)
	{
		bonus[i] = nullptr;
	}
	for (int i = 0; i < NBR_ENEMY; i++)
	{
		ennemis[i] = nullptr;
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
		if (projectilesEnemy[i] != nullptr)
		{
			delete projectilesEnemy[i];
		}
	}
	for (int i = 0; i < NBR_BONUS; i++)
	{
		if (bonus[i] != nullptr)
		{
			delete bonus[i];
		}
	}
	for (int i = 0; i < NBR_ENEMY; i++)
	{
		if (ennemis[i] != nullptr)
		{
			delete ennemis[i];
		}
	}
	for (int i = 0; i < shields.size(); i++)
	{
		delete shields[i];
	}	
	return transitionVersScene;
}

bool SceneCombat::init(RenderWindow * const window)
{
	srand(time(NULL));
	if (!fond.setTexture("Ressources\\background.jpg"))
	{
		return false;
	}
	if (!projectileT[0].loadFromFile("Ressources\\Projectile_normal.png"))
	{
		return false;
	}
	if (!projectileEnemy.loadFromFile("Ressources\\Projectile_enemy2.png"))
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
	if (!ennemisT[1].loadFromFile("Ressources\\enemy2.png"))
	{
		return false;
	}
	if (!ennemisT[2].loadFromFile("Ressources\\enemy3.png"))
	{
		return false;
	}
	
	vaisseauJoueur.setTexture(player);
	vaisseauJoueur.setPosition(100, 100);
	vaisseauJoueur.initGraphiques();

	ennemis[0] = new Enemy1({ LARGEUR_ECRAN + 100, 100 }, ennemisT[0], choixCouleur());
	ennemis[1] = new Enemy2({ LARGEUR_ECRAN - 100, 300 }, ennemisT[1], choixCouleur());
	ennemis[2] = new Enemy2({ 100, 300 }, ennemisT[1], choixCouleur());
	ennemis[3] = new Enemy3({ 237, 600 }, ennemisT[2], choixCouleur());

	bonus[0] = new BonusShield(Vector2f(200,200), bonusT[0]);

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
	collisionProjectilesEnnemis();
	collisionVaisseauEnnemis();
	gererBonus();
	gererBoucliers();
	gererEnnemis();
	gererProjectiles();
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
		if (projectilesEnemy[i] != nullptr)
		{
			mainWin->draw(*projectilesEnemy[i]);
		}
	}
	for (int i = 0; i < NBR_ENEMY; i++)
	{
		if (ennemis[i] != nullptr)
		{
			mainWin->draw(*ennemis[i]);
		}
	}

	for (int i = 0; i < NBR_BONUS; i++)
	{
		if (bonus[i] != nullptr)
		{
			mainWin->draw(*bonus[i]);
		}
	}
	for (int i = 0; i < shields.size(); i++)
	{
		mainWin->draw(*shields[i]);
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
			projectiles[i] = new Projectile_normal(Vector2f(position.x, position.y), 20 * vaisseauJoueur.direction, projectileT[0]);
			projectiles[i]->initGraphiques();
			projectiles[i]->activer();
			return;
		}
	}
}

void SceneCombat::ajouterProjectileEnnemis(Vector2f position, Color color)
{
	for (int j = 0; j < NBR_PROJ; j++)
	{
		if (projectilesEnemy[j] == nullptr)
		{
			if (clock_tire_enemy2.getElapsedTime().asMilliseconds() >= 200)
			{
				projectilesEnemy[j] = new Projectile_Enemy(Vector2f(position.x, position.y), 5, projectileEnemy, color);
				projectilesEnemy[j]->activer();
				return;
			}
		}
	}
}

Color SceneCombat::choixCouleur()
{
	Color couleur;
	static int choix;
	choix = rand() % 3;

	switch (choix)
	{
	case 0:
		couleur = Color::Red;
		break;
	case 1:
		couleur = Color::Magenta;
		break;
	case 2:
		couleur = Color::Yellow;
		break;
	}
	return couleur;
}

void tp3::SceneCombat::collisionProjectilesEnnemis()
{
	for (int i = 0; i < NBR_ENEMY; i++)
	{
		if (ennemis[i] != nullptr)
		{
			for (int j = 0; j < NBR_PROJ; j++)
			{
				if (projectiles[j] != nullptr)
				{
					if (ennemis[i]->getGlobalBounds().intersects(projectiles[j]->getGlobalBounds()))
					{
						ennemis[i]->ptsVie--;
						delete projectiles[j];
						projectiles[j] = nullptr;
					}
				}
			}
		}
	}
}

void tp3::SceneCombat::collisionVaisseauEnnemis()
{
	for (int i = 0; i < NBR_ENEMY; i++)
	{
		if (ennemis[i] != nullptr)
		{
			if (vaisseauJoueur.getGlobalBounds().intersects(ennemis[i]->getGlobalBounds()))
			{
				vaisseauJoueur.ptsVie -= ennemis[i]->dommageCollision;
				delete ennemis[i];
				ennemis[i] = nullptr;
			}
		}
	}
}

void tp3::SceneCombat::gererBoucliers()
{
	if (shields.size() > 0)
	{
		shields[0]->setPosition(vaisseauJoueur.getPosition());
	}
}

void tp3::SceneCombat::gererProjectiles()
{
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
		if (projectilesEnemy[i] != nullptr)
		{
			projectilesEnemy[i]->move(projectilesEnemy[i]->vitesse, 0);
			if (projectilesEnemy[i]->getPosition().x > LARGEUR_ECRAN || projectilesEnemy[i]->getPosition().x < 0)
			{
				delete projectilesEnemy[i];
				projectilesEnemy[i] = nullptr;
			}
		}
	}
}

void tp3::SceneCombat::gererEnnemis()
{
	for (int i = 0; i < NBR_ENEMY; i++)
	{
		if (ennemis[i] != nullptr)
		{
			ennemis[i]->action(vaisseauJoueur);
			if (typeid(*ennemis[i]) == typeid(Enemy2))
			{
				if (clock_tire_enemy2.getElapsedTime().asMilliseconds() >= 300)
				{
					ajouterProjectileEnnemis(ennemis[i]->getPosition(), ennemis[i]->getColor());
					clock_tire_enemy2.restart();
				}
			}
			
			//Si la vie est a 0, detruit l'ennemi
			if (ennemis[i]->ptsVie <= 0)
			{
				delete ennemis[i];
				ennemis[i] = nullptr;
			}
		}
	}
}

void tp3::SceneCombat::gererBonus()
{
	for (int i = 0; i < NBR_BONUS; i++)
	{
		if (bonus[i] != nullptr)
		{
			if (vaisseauJoueur.getGlobalBounds().intersects(bonus[i]->getGlobalBounds()))
			{
				delete bonus[i];
				bonus[i] = nullptr;
				//Cree un bouclier
				shields.push_back(new Shield(vaisseauJoueur.getPosition(), shield));

			}
		}
	}
}
