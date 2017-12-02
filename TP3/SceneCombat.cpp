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
	for (int i = 0; i < ennemis.size(); i++)
	{
		if (ennemis[i] != nullptr)
		{
			delete ennemis[i];
		}
	}
	for (int i = 0; i < ennemisSuivants.size(); i++)
	{
		if (ennemisSuivants[i] != nullptr)
		{
			delete ennemisSuivants[i];
		}
	}
	delete fabriqueEnemy1;
	delete fabriqueEnemy2;
	delete fabriqueEnemy3;
	delete fabriqueEnemy4;
	delete fabriqueEnemy5;
	delete fabriqueEnemy6;

	for (int i = 0; i < NBR_PORTAIL; i++)
	{
		delete portail[i];
	}
	return transitionVersScene;
}

bool SceneCombat::init(RenderWindow * const window)
{
	srand(time(NULL));
	if (!font.loadFromFile("Ressources\\Font\\font.ttf"))
	{
		return false;
	}
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
	if (!bonusT[1].loadFromFile("Ressources\\Bombe_electro.png"))
	{
		return false;
	}
	if (!player.loadFromFile("Ressources\\Player.png"))
	{
		return false;
	}
	if (!vaisseauJoueur.shield.loadFromFile("Ressources\\Shield.png"))
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
	if (!portailT.loadFromFile("Ressources\\portail.png"))
	{
		return false;
	}
	explo.setOutlineThickness(1);
	explo.setFillColor(Color::Transparent);
	explo.setOrigin(explo.getGlobalBounds().width / 2, explo.getGlobalBounds().height / 2);
	vaisseauJoueur.setTexture(player);
	vaisseauJoueur.setPosition(100, 100);
	vaisseauJoueur.initGraphiques();

	ennemisSuivants.reserve(NBR_ENEMY);
	niveauActif = 0;

	//Positions des fabriques
	fabriqueEnemy1->setPosition(100, 144);
	fabriqueEnemy2->setPosition(100, 432);
	fabriqueEnemy3->setPosition(100, 576);
	fabriqueEnemy4->setPosition(LARGEUR_ECRAN - 100, 144);
	fabriqueEnemy5->setPosition(LARGEUR_ECRAN - 100, 432);
	fabriqueEnemy6->setPosition(LARGEUR_ECRAN - 100, 576);

	//Portails
	portail[0] = new Portail(fabriqueEnemy1->getPosition(), portailT);
	portail[1] = new Portail(fabriqueEnemy2->getPosition(), portailT);
	portail[2] = new Portail(fabriqueEnemy3->getPosition(), portailT);
	portail[3] = new Portail(fabriqueEnemy4->getPosition(), portailT);
	portail[4] = new Portail(fabriqueEnemy5->getPosition(), portailT);
	portail[5] = new Portail(fabriqueEnemy6->getPosition(), portailT);
	for (int i = 0; i < NBR_PORTAIL; i++)
	{
		portail[i]->initGraphiques();
	}
	//Text de niveau a l'ecran
	textNiveau.setFont(font);
	textNiveau.setPosition(LARGEUR_ECRAN / 2 - 300, HAUTEUR_ECRAN / 2 - 150);
	textNiveau.setCharacterSize(150);
	textNiveau.setFillColor(Color::White);
	textNiveau.setScale(0, textNiveau.getScale().y);

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
		if (clock_tirer.getElapsedTime().asMilliseconds() >= 100 && vaisseauJoueur.canShoot == true)
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
	animText();
	gererEnnemis();
	gererProjectiles();
	gererExplo();
	if (tempsBombeElectro.getElapsedTime().asSeconds() > 2)
	{
		vaisseauJoueur.canShoot = true;
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
		if (projectilesEnemy[i] != nullptr)
		{
			mainWin->draw(*projectilesEnemy[i]);
		}
	}
	for (int i = 0; i < ennemis.size(); i++)
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
	if (vaisseauJoueur.shields.size() > 0)
	{
		mainWin->draw(*vaisseauJoueur.shields.top());
	}
	
	for (int i = 0; i < NBR_PORTAIL; i++)
	{
		mainWin->draw(*portail[i]);
	}
	mainWin->draw(explo);
	mainWin->draw(vaisseauJoueur);
	mainWin->draw(textNiveau);
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

void SceneCombat::ajouterBonus(Vector2f position)
{
	for (int i = 0; i < NBR_BONUS; i++)
	{
		if (bonus[i] == nullptr)
		{
			int choixBonus = rand() % 3;
			if (choixBonus == 0)
			{
				bonus[i] = new BonusShield(position, bonusT[0]);
				bonus[i]->ajouterObservateur(&vaisseauJoueur);
				return;
			}
			if (choixBonus == 1)
			{
				bonus[i] = new Bombe(position, ennemisT[2]);
				bonus[i]->ajouterObservateur(&vaisseauJoueur);
				return;
			}
			if (choixBonus == 2)
			{
				bonus[i] = new BombeElectro(position, bonusT[1]);
				bonus[i]->ajouterObservateur(&vaisseauJoueur);
				bonus[i]->initGraphiques();
				return;
			}
		}
	}
}

void SceneCombat::ajouterProjectileEnnemis(Vector2f position, Color color ,int direction)
{
	for (int j = 0; j < NBR_PROJ; j++)
	{
		if (projectilesEnemy[j] == nullptr)
		{
			projectilesEnemy[j] = new Projectile_Enemy(Vector2f(position.x, position.y), 20 * -direction, projectileEnemy, color,direction);
			projectilesEnemy[j]->activer();
			return;
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

void tp3::SceneCombat::retObservateur(Enemy* observateur)
{
	for (size_t i = 0; i < NBR_BONUS; i++)
	{
		if (bonus[i] != nullptr)
		{
			bonus[i]->retirerObservateur(observateur);
		}
	}
}

void tp3::SceneCombat::addObserver()
{
	bool peutAjouter = true;
	for (size_t i = 0; i < NBR_BONUS; i++)
	{
		if (bonus[i] != nullptr)
		{
			for (size_t j = 0; j < ennemis.size(); j++)
			{
				if (ennemis[j] != nullptr)
				{
					bonus[i]->ajouterObservateur(ennemis[j]);
				}
			}
		}
	}
}

void tp3::SceneCombat::gererExplo()
{
	if (readyExplo == true)
	{
		explo.setRadius(explo.getRadius() + 40);
		explo.setPosition(explo.getPosition().x - 40, explo.getPosition().y - 40);
	}
	if (explo.getRadius() >= 2000)
	{
		explo.setRadius(0);
		readyExplo = false;
	}
}

void tp3::SceneCombat::collisionProjectilesEnnemis()
{
	for (int i = 0; i < ennemis.size(); i++)
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
	for (int i = 0; i < NBR_PROJ; i++)
	{
		if (projectilesEnemy[i] != nullptr)
		{
			if (projectilesEnemy[i]->getGlobalBounds().intersects(vaisseauJoueur.getGlobalBounds()))
			{
				if (vaisseauJoueur.shields.size() > 0)
				{
					if (vaisseauJoueur.shields.top()->getColor() != projectilesEnemy[i]->getColor())
					{
						vaisseauJoueur.shields.top()->ptsShield--;
					}
				}
				delete projectilesEnemy[i];
				projectilesEnemy[i] = nullptr;
			}
		}
	}
}

void tp3::SceneCombat::collisionVaisseauEnnemis()
{
	for (int i = 0; i < ennemis.size(); i++)
	{
		if (ennemis[i] != nullptr)
		{
			if (vaisseauJoueur.getGlobalBounds().intersects(ennemis[i]->getGlobalBounds()))
			{
				vaisseauJoueur.ptsVie -= ennemis[i]->dommageCollision;
				retObservateur(ennemis[i]);
				delete ennemis[i];
				ennemis[i] = nullptr;
			}
		}
	}
}

void tp3::SceneCombat::gererBoucliers()
{
	if (vaisseauJoueur.shields.size() > 0)
	{
		if (vaisseauJoueur.shields.top()->ptsShield <= 0)
		{
			vaisseauJoueur.shields.pop();
			cout << "shield miel" << endl;
		}
		if (vaisseauJoueur.shields.size() > 0)
		{
			vaisseauJoueur.shields.top()->setPosition(vaisseauJoueur.getPosition());
		}
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
	int nbEnemy = nbEnemy1 + nbEnemy2 + nbEnemy3;
	// Fais spawn les ennemis
	if (ennemisSuivants.empty() && nbEnemy <= 0 && textAfficheTerminer)
	{
		niveauActif++;
		chargerNiveau(niveauActif);
		textAfficheTerminer = false;
	}
	else if (spawnEnemy.getElapsedTime().asSeconds() > 2)
	{
		if (ennemisSuivants.size() > 0)
		{
			Enemy *temp = ennemisSuivants.pop_front();
			ennemis.push_back(temp);
			portail[temp->numeroFabrique]->animTermine = false;
			std::cout << temp->numeroFabrique << std::endl;
			addObserver();
				spawnEnemy.restart();
			
		}
	}
	for (size_t i = 0; i < NBR_PORTAIL; i++)
	{
		if (!portail[i]->animTermine)
		{
			portail[i]->anim();
		}
	}
	////////////////////////


	nbEnnemis();
	int counterEnemy2 = 0;
	for (int i = 0; i < ennemis.size(); i++)
	{
		if (ennemis[i] != nullptr)
		{
			ennemis[i]->action(vaisseauJoueur);
			
			if (typeid(*ennemis[i]) == typeid(Enemy2))
			{
				counterEnemy2++;
				if (clock_tire_enemy2.getElapsedTime().asMilliseconds() >= 400 && ennemis[i]->isReady && ennemis[i]->canShoot == true)
				{
					cout << ennemis[i]->canShoot << endl;
					ajouterProjectileEnnemis(ennemis[i]->getPosition(), ennemis[i]->getColor(), ennemis[i]->direction);
					if (nbEnemy2 == counterEnemy2 ||  nbEnemy2 == 1)
					{
						clock_tire_enemy2.restart();
					}
				}

			}
			if (tempsBombeElectroEnnemis.getElapsedTime().asSeconds() > 2)
			{
				ennemis[i]->canShoot = true;
			}
			//Si la vie est a 0, detruit l'ennemi
			if (ennemis[i]->ptsVie <= 0)
			{
				//Spawn bonus quand il meurt
				int spwnBonus = rand() % 100;
				if (spwnBonus <= 90)
				{
					ajouterBonus(ennemis[i]->getPosition());
				}
				retObservateur(ennemis[i]);
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
			if (typeid(*bonus[i]) == typeid(BombeElectro))
			{
				bonus[i]->anim();
			}
			if (vaisseauJoueur.getGlobalBounds().intersects(bonus[i]->getGlobalBounds()))
			{
				
				if (typeid(*bonus[i]) == typeid(BombeElectro))
				{
					tempsBombeElectroEnnemis.restart();
					explo.setPosition(bonus[i]->getPosition());
					explo.setOutlineColor(bonus[i]->getColor());
					readyExplo = true;
				}
				bonus[i]->notifierTousLesObservateurs();
				delete bonus[i];
				bonus[i] = nullptr;

			}
			else if (typeid(*bonus[i]) == typeid(BombeElectro))
			{
				for (size_t j = 0; j < ennemis.size(); j++)
				{
					if (ennemis[j] != nullptr)
					{
						if (bonus[i] != nullptr)
						{
							if (ennemis[j]->getGlobalBounds().intersects(bonus[i]->getGlobalBounds()))
							{
								explo.setPosition(bonus[i]->getPosition());
								explo.setOutlineColor(bonus[i]->getColor());
								readyExplo = true;
								tempsBombeElectro.restart();
								bonus[i]->notifierTousLesObservateurs();
								delete bonus[i];
								bonus[i] = nullptr;
							}
						}
					}
				}
			}
		}
		
	}
}

void SceneCombat::nbEnnemis()
{
	int temp1=0, temp2=0, temp3=0, temp4=0;
	for (int i = 0; i < ennemis.size(); i++)
	{
		if (ennemis[i] != nullptr)
		{
			if (typeid(*ennemis[i]) == typeid(Enemy1))
			{
				temp1++;
			}
			else if (typeid(*ennemis[i]) == typeid(Enemy2))
			{
				temp2++;
			}
			if (typeid(*ennemis[i]) == typeid(Enemy3))
			{
				temp3++;
			}
		}
	}
	nbEnemy1 = temp1;
	nbEnemy2 = temp2;
	nbEnemy3 = temp3;
}

void SceneCombat::chargerNiveau(const int niveau)
{
	text.str("");
	text << "NIVEAU " << niveau;
	textNiveau.setString(text.str());

	if (niveau == 1)
	{
		ennemisSuivants.push_back(new Enemy2({ 200, 200 }, ennemisT[1], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy2({ 200, 200 }, ennemisT[1], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy2({ 200, 200 }, ennemisT[1], choixCouleur(), 1));
		ennemisSuivants.push_back(fabriqueEnemy4->fabriquerEnemy(ennemisT[0], choixCouleur(), 3));
		ennemisSuivants.push_back(fabriqueEnemy6->fabriquerEnemy(ennemisT[0], choixCouleur(), 5));
		ennemisSuivants.push_back(fabriqueEnemy2->fabriquerEnemy(ennemisT[0], choixCouleur(), 1));
		ennemisSuivants.push_back(fabriqueEnemy3->fabriquerEnemy(ennemisT[0], choixCouleur(), 2));
		ennemisSuivants.push_back(fabriqueEnemy4->fabriquerEnemy(ennemisT[0], choixCouleur(), 3));
		ennemisSuivants.push_back(fabriqueEnemy5->fabriquerEnemy(ennemisT[0], choixCouleur(), 4));
	}
	else if (niveau == 2)
	{
		ennemisSuivants.push_back(fabriqueEnemy1->fabriquerEnemy(ennemisT[0], choixCouleur(), 0));
		ennemisSuivants.push_back(fabriqueEnemy3->fabriquerEnemy(ennemisT[0], choixCouleur(), 2));
		ennemisSuivants.push_back(fabriqueEnemy4->fabriquerEnemy(ennemisT[0], choixCouleur(), 3));
		ennemisSuivants.push_back(fabriqueEnemy6->fabriquerEnemy(ennemisT[0], choixCouleur(), 5));
		ennemisSuivants.push_back(fabriqueEnemy1->fabriquerEnemy(ennemisT[0], choixCouleur(), 0));
		ennemisSuivants.push_back(fabriqueEnemy2->fabriquerEnemy(ennemisT[0], choixCouleur(), 1));
		ennemisSuivants.push_back(fabriqueEnemy5->fabriquerEnemy(ennemisT[0], choixCouleur(), 4));
		ennemisSuivants.push_back(fabriqueEnemy3->fabriquerEnemy(ennemisT[0], choixCouleur(), 2));
	}
}

void SceneCombat::animText()
{
	static float compteur = 0;
	
	if (!textAfficheTerminer)
	{
		if (textNiveau.getScale().x < 1)
		{
			textNiveau.setScale(compteur, textNiveau.getScale().y);
			compteur += 0.05f;
			animationText.restart();
		}
		if (animationText.getElapsedTime().asMilliseconds() > 1500)
		{
			if (textNiveau.getScale().x >= 1 && textNiveau.getScale().y > 0)
			{
				textNiveau.setScale(textNiveau.getScale().x, compteur);
				compteur -= 0.05f;
			}
		}
		if (textNiveau.getScale().x >= 1 && textNiveau.getScale().y <= 0)
		{
			animationText.restart();
			textNiveau.setScale(0, 1);
			compteur = 0;
			textAfficheTerminer = true;
		}
	}
}

void tp3::SceneCombat::animPortail(Enemy* temp)
{
	switch (temp->numeroFabrique)
	{
	case 0:
		
		break;
	case 1:
		portail[1]->setPosition(fabriqueEnemy2->getPosition());
		break;
	case 2:
		portail[2]->setPosition(fabriqueEnemy3->getPosition());
		break;
	case 3:
		portail[3]->setPosition(fabriqueEnemy4->getPosition());
		break;
	case 4:
		portail[4]->setPosition(fabriqueEnemy5->getPosition());
		break;
	case 5:
		portail[5]->setPosition(fabriqueEnemy6->getPosition());
		break;
	}
}
