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
	
	//Projectiles
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

	//Bonus
	for (int i = 0; i < NBR_BONUS; i++)
	{
		if (bonus[i] != nullptr)
		{
			delete bonus[i];
		}
	}

	//Enemis
	for (int i = 0; i < ennemis.size(); i++)
	{
		if (ennemis[i] != nullptr)
		{
			delete ennemis[i];
		}
	}
	ennemis.clear();

	//Explosions
	for (int i = 0; i < explosions.size(); i++)
	{
		if (explosions[i] != nullptr)
		{
			delete explosions[i];
		}
	}
	explosions.clear();

	//Ennemissuivants
	for (int i = 0; i < ennemisSuivants.size(); i++)
	{
		if (ennemisSuivants[i] != nullptr)
		{
			delete ennemisSuivants[i];
		}
	}
	ennemisSuivants.clear();

	//Portails
	for (int i = 0; i < NBR_PORTAIL; i++)
	{
		delete portail[i];
	}

	//Barres dans le HUD
	for (int i = 0; i < NB_BARRES_VIES; i++)
	{
		delete barresVie[i];
	}
	for (int i = 0; i < NB_BARRES_VIES_BOSS; i++)
	{
		delete barresViesBoss[i];
	}
	for (int i = 0; i < NB_BARRES_ARMES; i++)
	{
		delete barresArmes[i];
	}
	for (int i = 0; i < barresEnnemis.size(); i++)
	{
		if (barresEnnemis[i] != nullptr)
		{
			delete barresEnnemis[i];
		}
	}
	barresEnnemis.clear();
	for (int i = 0; i < barresBouclier.size(); i++)
	{
		if (barresBouclier[i] != nullptr)
		{
			delete barresBouclier[i];
		}
	}
	barresBouclier.clear();
	//////////////////

	//Fabriques
	delete fabriqueEnemy1;
	delete fabriqueEnemy2;
	delete fabriqueEnemy3;
	delete fabriqueEnemy4;
	delete fabriqueEnemy5;
	delete fabriqueEnemy6;

	delete cercleCollision;

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
	if (!projectileT[1].loadFromFile("Ressources\\beam.png"))
	{
		return false;
	}
	if (!projectileT[2].loadFromFile("Ressources\\missile.png"))
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
	if (!bonusT[2].loadFromFile("Ressources\\Bonus_laser.png"))
	{
		return false;
	}
	if (!bonusT[3].loadFromFile("Ressources\\Bonus_scatter.png"))
	{
		return false;
	}
	if (!bonusT[4].loadFromFile("Ressources\\Bonus_score.png"))
	{
		return false;
	}
	if (!bonusT[5].loadFromFile("Ressources\\Bonus_missile.png"))
	{
		return false;
	}
	if (!bonusT[6].loadFromFile("Ressources\\bombe.png"))
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
	if (!ennemisT[3].loadFromFile("Ressources\\enemy4.png"))
	{
		return false;
	}
	if (!iconArmes[0].loadFromFile("Ressources\\icon_base.png"))
	{
		return false;
	}
	if (!iconArmes[1].loadFromFile("Ressources\\icon_scatter.png"))
	{
		return false;
	}
	if (!iconArmes[2].loadFromFile("Ressources\\icon_missile.png"))
	{
		return false;
	}
	if (!iconArmes[3].loadFromFile("Ressources\\icon_laser.png"))
	{
		return false;
	}
	if (!bossT.loadFromFile("Ressources\\boss.png"))
	{
		return false;
	}
	if (!enemyListeT[0].loadFromFile("Ressources\\enemy1_liste.png"))
	{
		return false;
	}
	if (!enemyListeT[1].loadFromFile("Ressources\\enemy2_liste.png"))
	{
		return false;
	}
	if (!enemyListeT[2].loadFromFile("Ressources\\enemy3_liste.png"))
	{
		return false;
	}
	if (!enemyListeT[3].loadFromFile("Ressources\\enemy4_liste.png"))
	{
		return false;
	}
	if (!portailT.loadFromFile("Ressources\\portail.png"))
	{
		return false;
	}
	if (!explosionT.loadFromFile("Ressources\\explosion.png"))
	{
		return false;
	}
	if (!iconBouclier.loadFromFile("Ressources\\shield_liste.png"))
	{
		return false;
	}

	//Explosion joueur
	explosions.push_back(new Explosion({ 100,100 }, explosionT));
	explosions.front()->initGraphiques();
	explo.setOutlineThickness(1);
	explo.setFillColor(Color::Transparent);
	explo.setOrigin(explo.getGlobalBounds().width / 2, explo.getGlobalBounds().height / 2);

	//HUD
	if (!hudT.loadFromFile("Ressources\\hud.png"))
	{
		return false;
	}
	hud.setTexture(hudT);
	hud.setOrigin(LARGEUR_ECRAN / 2, HAUTEUR_ECRAN / 2);
	hud.setPosition(hud.getOrigin());

	//Joueur
	vaisseauJoueur.setTexture(player);
	vaisseauJoueur.setPosition(LARGEUR_ECRAN/2, HAUTEUR_ECRAN/2);
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

	//Boss
	cercleCollision = new CircleShape(180);
	cercleCollision->setFillColor(Color::Transparent);
	cercleCollision->setOrigin(cercleCollision->getGlobalBounds().width / 2, cercleCollision->getGlobalBounds().height / 2);
	cercleCollision->setPosition(-1000, 0);

	//Text de niveau a l'ecran
	textNiveau.setFont(font);
	textNiveau.setPosition(LARGEUR_ECRAN / 2 - 300, HAUTEUR_ECRAN / 2 - 150);
	textNiveau.setCharacterSize(150);
	textNiveau.setFillColor(Color::White);
	textNiveau.setScale(0, textNiveau.getScale().y);

	//Text WARNING
	warning.setFont(font);
	warning.setPosition(LARGEUR_ECRAN / 2 - 300, HAUTEUR_ECRAN / 2 - 150);
	warning.setCharacterSize(150);
	warning.setFillColor(Color::Transparent);
	warning.setString("WARNING");

	//Text boss
	textBoss.setFont(font);
	textBoss.setPosition(LARGEUR_ECRAN / 2 - 65, 95);
	textBoss.setCharacterSize(45);
	textBoss.setFillColor(Color::Red);
	textBoss.setString("BOSS");

	//Section HUD
	//Texte Niveau
	niveauTextHUD.setFont(font);
	niveauTextHUD.setFillColor(Color::White);
	niveauTextHUD.setCharacterSize(35);
	niveauTextHUD.setString("Niveau");
	niveauTextHUD.setOrigin(niveauTextHUD.getGlobalBounds().width / 2, niveauTextHUD.getGlobalBounds().height / 2);
	niveauTextHUD.setPosition(LARGEUR_ECRAN / 2 - 20, 0);
	//Nombre niveau
	niveauHUD.setFont(font);
	niveauHUD.setFillColor(Color::White);
	niveauHUD.setCharacterSize(35);
	niveauHUD.setPosition(LARGEUR_ECRAN / 2 + 95, 0);
	//Nombre score joueur
	scoreHUD.setFont(font);
	scoreHUD.setFillColor(Color::White);
	scoreHUD.setCharacterSize(90);
	scoreHUD.setPosition(LARGEUR_ECRAN / 2 - 50, 0);
	//Munitions du joueur
	munitionsHUD.setFont(font);
	munitionsHUD.setFillColor(Color::White);
	munitionsHUD.setCharacterSize(45);
	munitionsHUD.setPosition(LARGEUR_ECRAN - 130, -15);
	munitionsHUD.setString("");

	//Barres de vie
	static int espace = 0;
	for (int i = 0; i < NB_BARRES_VIES; i++)
	{
		barresVie[i] = new RectangleShape({ 20, 25 });
		barresVie[i]->setFillColor(Color::Green);
		barresVie[i]->setOrigin(barresVie[i]->getSize().x / 2, barresVie[i]->getSize().y / 2);
		barresVie[i]->setPosition(165 + espace, 20);
		espace += 25;
	}

	//Barres de vies du boss
	static int espaceBoss = 0;
	for (int i = 0; i < NB_BARRES_VIES_BOSS; i++)
	{
		barresViesBoss[i] = new RectangleShape({ 30, 20 });
		barresViesBoss[i]->setFillColor(Color::Green);
		barresViesBoss[i]->setOrigin(barresViesBoss[i]->getSize().x / 2, barresViesBoss[i]->getSize().y / 2);
		barresViesBoss[i]->setPosition(LARGEUR_ECRAN/2 - 195 + espaceBoss, 160);
		espaceBoss += 35;
	}

	//Barres des armes
	static int espaceArmes = 0;
	for (int i = 0; i < NB_BARRES_ARMES; i++)
	{
		barresArmes[i] = new RectangleShape({ 50, 40 });
		barresArmes[i]->setOrigin(barresArmes[i]->getSize().x / 2, barresArmes[i]->getSize().y / 2);
		barresArmes[i]->setPosition(LARGEUR_ECRAN -165 - espaceArmes, 23);
		barresArmes[i]->setTexture(&iconArmes[i]);
		barresArmes[i]->setOutlineThickness(2);
		espaceArmes += 60;
	}
	barresArmes[0]->setFillColor(Color::Cyan);

	//Texte affichant la vie
	ptsVieText.setFont(font);
	ptsVieText.setCharacterSize(55);
	ptsVieText.setOrigin(niveauTextHUD.getGlobalBounds().width / 2, niveauTextHUD.getGlobalBounds().height / 2);
	ptsVieText.setPosition(120, -15);
	
	//Texte vie du bouclier
	ptsBouclier.setFont(font);
	ptsBouclier.setCharacterSize(55);
	ptsBouclier.setOrigin(niveauTextHUD.getGlobalBounds().width / 2, niveauTextHUD.getGlobalBounds().height / 2);
	ptsBouclier.setPosition(120, 30);
	ptsBouclier.setString("");

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
		if (vaisseauJoueur.weapon == Base || vaisseauJoueur.weapon == Scatter)
		{
			if (clock_tirer.getElapsedTime().asMilliseconds() >= 100 && vaisseauJoueur.canShoot == true)
			{
				ajouterProjectile(vaisseauJoueur.getPosition());
				clock_tirer.restart();
			}
		}
		else if(vaisseauJoueur.weapon == FatLaser)
		{
			if (clock_tirer.getElapsedTime().asMilliseconds() >= 2000 && vaisseauJoueur.canShoot == true)
			{
				ajouterProjectile(vaisseauJoueur.getPosition());
				clock_tirer.restart();
			}
		}
		else if (vaisseauJoueur.weapon == Missile)
		{
			if (clock_tirer.getElapsedTime().asMilliseconds() >= 200 && vaisseauJoueur.canShoot == true)
			{
				ajouterProjectile(vaisseauJoueur.getPosition());
				clock_tirer.restart();
			}
		}
	}
	//Changer d'arme vers la gauche
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		if (peutSwitchWeapon)
		{
			vaisseauJoueur.positionWeapon++;
			if (vaisseauJoueur.positionWeapon > vaisseauJoueur.weapons.size() - 1)
			{
				vaisseauJoueur.positionWeapon = 0;
			}
			tempsSwitchWeapon.restart();
			peutSwitchWeapon = false;
		}
	}
	//Changer d'arme vers la droite
	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		if (peutSwitchWeapon)
		{
			vaisseauJoueur.positionWeapon--;
			if (vaisseauJoueur.positionWeapon < 0)
			{
				vaisseauJoueur.positionWeapon = vaisseauJoueur.weapons.size() - 1;
			}
			tempsSwitchWeapon.restart();
			peutSwitchWeapon = false;

		}
		
	}

	//Mode debug, pour ne pas mourir
	if (Keyboard::isKeyPressed(Keyboard::F))
	{
		debugMode = true;
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
	gererExplo();
	gererBonus();
	gererScoreJoueur();
	gererBoucliers();
	animText();
	gererEnnemis();
	gererProjectiles();
	gererWeapons();
	gererFinJeu();

	//Update des explosions
	for (int i = 0; i < explosions.size(); i++)
	{
		if (explosions[i] != nullptr)
		{
			if (explosions[i]->isReady)
			{
				explosions[i]->anim();
			}
			if (explosions[i]->animTermine == true)
			{
				explosions.erase(explosions.begin() + i);
			}
		}
	}

	//Pivotement du joueur
	if (vaisseauJoueur.isPivoting == true)
	{
		vaisseauJoueur.pivoter();
	}

	//Bombe électro
	if (tempsBombeElectro.getElapsedTime().asSeconds() > 2)
	{
		vaisseauJoueur.canShoot = true;
	}

	//Clock switch weapon
	if (tempsSwitchWeapon.getElapsedTime().asMilliseconds() > 200)
	{
		peutSwitchWeapon = true;
	}

	//Clock bonus score
	if (tempsBonusScore.getElapsedTime().asSeconds() > 22)
	{
		bonusScoreActif = false;
	}

	//Couleur du texte de la vie du joueur
	if (vaisseauJoueur.shields.size() > 0)
	{
		ptsVieText.setFillColor(vaisseauJoueur.shields.top()->getColor());
	}
	else
	{
		ptsVieText.setFillColor(Color::Cyan);
	}
	if (vaisseauJoueur.ptsVie < 0)
	{
		ptsVieText.setString("0");
	}
	else
	{
		ptsVieText.setString(std::to_string(vaisseauJoueur.ptsVie));
	}
}

void SceneCombat::draw()
{
	mainWin->clear();
	fond.draw(mainWin);
	
	//Ennemis
	for (int i = 0; i < ennemis.size(); i++)
	{
		if (ennemis[i] != nullptr)
		{
			mainWin->draw(*ennemis[i]);
		}
	}

	//Explosions
	for (int i = 0; i < explosions.size(); i++)
	{
		if (explosions[i] != nullptr)
		{
			if (explosions[i]->isReady == true)
			{
				mainWin->draw(*explosions[i]);
			}
		}
	}
	mainWin->draw(*cercleCollision);

	//Bonus
	for (int i = 0; i < NBR_BONUS; i++)
	{
		if (bonus[i] != nullptr)
		{
			mainWin->draw(*bonus[i]);
		}
	}	

	//Bouclier du joueur
	if (vaisseauJoueur.shields.size() > 0)
	{
		mainWin->draw(*vaisseauJoueur.shields.top());
	}
	
	//Les 6 portails
	for (int i = 0; i < NBR_PORTAIL; i++)
	{
		mainWin->draw(*portail[i]);
	}

	//Ajuste le texte et les barres de vies
	for (int i = 0; i < vaisseauJoueur.ptsVie; i++)
	{
		if (vaisseauJoueur.shields.size() > 0)
		{
			barresVie[i]->setFillColor(vaisseauJoueur.shields.top()->getColor());
			ptsVieText.setFillColor(vaisseauJoueur.shields.top()->getColor());
		}
		else
		{
			barresVie[i]->setFillColor(Color::Cyan);
			ptsVieText.setFillColor(Color::Cyan);
		}
		mainWin->draw(*barresVie[i]);
	}

	//Barres de vies du boss
	if (dernierNiveau)
	{
		if (ennemis.size() > 0 && ennemis[0]->isReady)
		{
			for (int i = 0; i < ennemis[0]->ptsVie / 50; i++)
			{
				if (ennemis[0]->phase == 2)
				{
					barresViesBoss[i]->setFillColor(Color::Yellow);
				}
				else if (ennemis[0]->phase == 3)
				{
					barresViesBoss[i]->setFillColor(Color::Red);
				}
				else
				{
					barresViesBoss[i]->setFillColor(Color::Green);
				}
				mainWin->draw(*barresViesBoss[i]);
			}
			mainWin->draw(textBoss);
		}
	}
	
	//Barres d'armes
	for (int i = 0; i < NB_BARRES_ARMES; i++)
	{
		mainWin->draw(*barresArmes[i]);
	}

	//Liste des ennemis
	int cptEnnemis = 1;
	for (int i = 0; i < barresEnnemis.size(); i++)
	{
		if (cptEnnemis == NB_BARRES_ENNEMIS+1)
		{
			break;
		}
		barresEnnemis[i]->setPosition(LARGEUR_ECRAN - 55 - (50 * cptEnnemis), 55);
		mainWin->draw(*barresEnnemis[i]);
		cptEnnemis++;
	}

	//Liste des boucliers
	int cptBoubou = 1;
	for (int i = barresBouclier.size() - 1; i >= 0; i--)
	{
		if (cptBoubou == NB_BARRES_BOUCLIERS+1)
		{
			break;
		}
		barresBouclier[i]->setPosition(100 + (50 * cptBoubou), 55);
		mainWin->draw(*barresBouclier[i]);
		cptBoubou++;
	}	

	mainWin->draw(explo);
	mainWin->draw(vaisseauJoueur);
	//Projectiles
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
	//HUD et reste
	mainWin->draw(textNiveau);
	mainWin->draw(warning);
	mainWin->draw(scoreHUD);
	mainWin->draw(ptsBouclier);
	mainWin->draw(niveauTextHUD);
	mainWin->draw(niveauHUD);
	mainWin->draw(munitionsHUD);
	mainWin->draw(ptsVieText);
	mainWin->draw(hud);
	mainWin->display();
}

void tp3::SceneCombat::ajouterProjectile(Vector2f position)
{
	//Base
	if (vaisseauJoueur.weapon == Base)
	{
		for (int i = 0; i < NBR_PROJ; i++)
		{
			if (projectiles[i] == nullptr)
			{
				projectiles[i] = new Projectile_normal(Vector2f(position.x, position.y), 20 * vaisseauJoueur.direction, projectileT[0],0);
				projectiles[i]->setRotation(((projectiles[i]->angle) * 180) / M_PI);
				projectiles[i]->initGraphiques();
				projectiles[i]->activer();
				return;
			}
		}
	}

	//Scatter
	if (vaisseauJoueur.weapon == Scatter)
	{
		for (size_t j = 0; j < 3; j++)
		{
			for (int i = 0; i < NBR_PROJ; i++)
			{
				if (projectiles[i] == nullptr)
				{
					projectiles[i] = new Projectile_normal(Vector2f(position.x, position.y), 20 * vaisseauJoueur.direction, projectileT[0],0);
					if (j == 0)
						projectiles[i]->angle = 0.2f;
					if (j == 1)
						projectiles[i]->angle = -0.2f;
					projectiles[i]->setRotation(((projectiles[i]->angle) * 180) / M_PI);
					projectiles[i]->initGraphiques();
					projectiles[i]->activer();
					vaisseauJoueur.munitionScatter--;
					break;
				}
			}
		}
	}

	//Missile
	if (vaisseauJoueur.weapon == Missile)
	{
		for (int i = 0; i < NBR_PROJ; i++)
		{
			if (projectiles[i] == nullptr)
			{
				projectiles[i] = new Projectile_Missile(Vector2f(position.x, position.y), 15 * vaisseauJoueur.direction, projectileT[2], 0);
				projectiles[i]->setRotation(((projectiles[i]->angle) * 180) / M_PI);
				projectiles[i]->initGraphiques();
				projectiles[i]->activer();
				vaisseauJoueur.munitionMissile--;
				return;
			}
		}
	}

	//Laser
	if (vaisseauJoueur.weapon == FatLaser)
	{
		for (int i = 0; i < NBR_PROJ; i++)
		{
			if (projectiles[i] == nullptr)
			{
				projectiles[i] = new Projectile_Beam(Vector2f(position.x, position.y), 20 * vaisseauJoueur.direction, projectileT[1], 0);
				projectiles[i]->initGraphiques();
				projectiles[i]->activer();
				vaisseauJoueur.munitionLaserbeam--;
				return;
			}
		}
	}
}


void SceneCombat::ajouterBonus(Vector2f position)
{
	for (int i = 0; i < NBR_BONUS; i++)
	{
		if (bonus[i] == nullptr)
		{
			int choixBonus =  rand() % 1000;
			//Les boucliers ont 2fois plus de chance
			if (choixBonus >= 0 && choixBonus < 60)
			{
				bonus[i] = new BonusShield(position, bonusT[0]);
				bonus[i]->ajouterObservateur(&vaisseauJoueur);
				return;
			}
			if (choixBonus >= 60 && choixBonus < 90)
			{
				bonus[i] = new Bombe(position, bonusT[6]);
				bonus[i]->ajouterObservateur(&vaisseauJoueur);
				bonus[i]->initGraphiques();
				return;
			}
			if (choixBonus >= 90 && choixBonus < 120)
			{
				bonus[i] = new BombeElectro(position, bonusT[1]);
				bonus[i]->ajouterObservateur(&vaisseauJoueur);
				bonus[i]->initGraphiques();
				return;
			}
			if (choixBonus >= 120 && choixBonus < 150)
			{
				bonus[i] = new BonusScatter(position, bonusT[3]);
				bonus[i]->ajouterObservateur(&vaisseauJoueur);
				bonus[i]->initGraphiques();
				return;
			}
			if (choixBonus >= 150 && choixBonus < 180)
			{
				bonus[i] = new BonusMissile(position, bonusT[5]);
				bonus[i]->ajouterObservateur(&vaisseauJoueur);
				bonus[i]->initGraphiques();
				return;
			}
			if (choixBonus >= 180 && choixBonus < 210)
			{
				bonus[i] = new BonusScore(position, bonusT[4]);
				bonus[i]->ajouterObservateur(&vaisseauJoueur);
				bonus[i]->initGraphiques();
				return;
			}
		}
	}
}

void SceneCombat::ajouterProjectileEnnemis(Vector2f position, Color color ,int direction, float scale, float angle)
{
	for (int j = 0; j < NBR_PROJ; j++)
	{
		if (projectilesEnemy[j] == nullptr)
		{
			projectilesEnemy[j] = new Projectile_Enemy(Vector2f(position.x, position.y), 20 * -direction, projectileEnemy, color,direction, scale, angle);
			projectilesEnemy[j]->setRotation(((projectilesEnemy[j]->angle) * 180) / M_PI);
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
	//Boucle des ennemis
	for (int i = 0; i < ennemis.size(); i++)
	{
		if (ennemis[i] != nullptr)
		{
			//Boucle des projectiles
			for (int j = 0; j < NBR_PROJ; j++)
			{
				if (projectiles[j] != nullptr)
				{
					if (typeid(*projectiles[j]) != typeid(Projectile_Beam))
					{
						if (typeid(*ennemis[i]) != typeid(Boss)) //Si ce n'est pas le boss, applique la collision normale
						{
							if (ennemis[i]->getGlobalBounds().intersects(projectiles[j]->getGlobalBounds())) //S'il y a collision
							{
								ennemis[i]->ptsVie--; //Enleve la vie a l'ennemi
								if (typeid(*projectiles[j]) == typeid(Projectile_Missile))
								{
									//Parcourt tous les ennemis pour les missiles
									for (size_t k = 0; k < ennemis.size(); k++)
									{
										if (ennemis[k] != nullptr)
										{
											int distance = sqrt(pow(ennemis[k]->getPosition().x - projectiles[j]->getPosition().x, 2) + pow(ennemis[k]->getPosition().y - projectiles[j]->getPosition().y, 2));
											if (distance < 200)
											{
												ennemis[k]->ptsVie -= 2;
											}
										}
									}
								}
								delete projectiles[j];
								projectiles[j] = nullptr;
							}
						}
						else
						{
							//Cercle de collision du boss
							if (cercleCollision->getGlobalBounds().intersects(projectiles[j]->getGlobalBounds()))
							{
								ennemis[i]->ptsVie--;
								if (typeid(*projectiles[j]) == typeid(Projectile_Missile))
								{
									for (size_t k = 0; k < ennemis.size(); k++)
									{
										if (ennemis[k] != nullptr)
										{
											int distance = sqrt(pow(ennemis[k]->getPosition().x - projectiles[j]->getPosition().x, 2) + pow(ennemis[k]->getPosition().y - projectiles[j]->getPosition().y, 2));
											if (distance < 200)
											{
												ennemis[k]->ptsVie -= 2;
											}
										}
									}
								}
								delete projectiles[j];
								projectiles[j] = nullptr;
							}
						}
					}
				}
			}
		}
	}
	//Gestion des collision boucliers/projectiles
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
				else
				{
					vaisseauJoueur.ptsVie -= 1;
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
			if (typeid(*ennemis[i]) != typeid(Boss)) //Si ce n'est pas le boss, applique la collision normale
			{
				if (vaisseauJoueur.getGlobalBounds().intersects(ennemis[i]->getGlobalBounds()))
				{
					vaisseauJoueur.ptsVie -= ennemis[i]->dommageCollision;
					retObservateur(ennemis[i]);

					//Ajoute le score au joueur
					ajouterScore(i);

					if (typeid(*ennemis[i]) != typeid(Boss)) //Ne supprime pas le boss si le joueur lui rentre dedans
					{
						ennemis[i]->ptsVie -= 100;
					}
				}
			}
			else
			{
				if (cercleCollision->getGlobalBounds().intersects(vaisseauJoueur.getGlobalBounds()))
				{
					vaisseauJoueur.ptsVie -= ennemis[i]->dommageCollision;
					retObservateur(ennemis[i]);

					//Ajoute le score au joueur
					ajouterScore(i);

					if (typeid(*ennemis[i]) != typeid(Boss)) //Ne supprime pas le boss si le joueur lui rentre dedans
					{
						ennemis.erase(ennemis.begin() + i);
					}
				}
			}
		}
	}
}

void tp3::SceneCombat::gererBoucliers()
{
	if (vaisseauJoueur.shields.size() > 0)
	{
		//Texte de pts de vies des boucliers
		ptsBouclier.setString(std::to_string(vaisseauJoueur.shields.top()->ptsShield));
		ptsBouclier.setColor(vaisseauJoueur.shields.top()->getColor());

		if (vaisseauJoueur.shields.top()->ptsShield <= 0)
		{
			vaisseauJoueur.shields.pop();

			//Enleve dans la liste des boucliers du HUD
			barresBouclier.pop_back();
		}
		if (vaisseauJoueur.shields.size() > 0)
		{
			vaisseauJoueur.shields.top()->setPosition(vaisseauJoueur.getPosition());
		}
	}
}

void tp3::SceneCombat::gererWeapons()
{
	static Color couleurHover = Color::White;
	static Color couleurHave = Color::Cyan;
	static Color couleurNoHave = Color::White;

	if (vaisseauJoueur.weapons.size() > 0)
	{
		vaisseauJoueur.weapon = *vaisseauJoueur.weapons[vaisseauJoueur.positionWeapon];
	}

	//FATLASER
	if (vaisseauJoueur.weapon == FatLaser)
	{
		barresArmes[3]->setOutlineColor(couleurHover);
		munitionsHUD.setString(std::to_string(vaisseauJoueur.munitionLaserbeam));
		if (vaisseauJoueur.munitionLaserbeam <= 0)
		{
			vaisseauJoueur.weapon = Base;
			munitionsHUD.setString("");
			vaisseauJoueur.haveLaser = false;
			vaisseauJoueur.weapons.erase(vaisseauJoueur.weapons.begin() + vaisseauJoueur.positionWeapon);
			vaisseauJoueur.positionWeapon = 0;
		}
	}
	else
	{
		barresArmes[3]->setOutlineColor(Color::Transparent);
	}

	//SCATTER
	if (vaisseauJoueur.weapon == Scatter)
	{
		barresArmes[1]->setOutlineColor(couleurHover);
		munitionsHUD.setString(std::to_string(vaisseauJoueur.munitionScatter));
		if (vaisseauJoueur.munitionScatter <= 0)
		{
			vaisseauJoueur.weapon = Base;
			munitionsHUD.setString("");
			vaisseauJoueur.haveScatter = false;
			vaisseauJoueur.weapons.erase(vaisseauJoueur.weapons.begin() + vaisseauJoueur.positionWeapon);
			vaisseauJoueur.positionWeapon = 0;

		}
	}
	else
	{
		barresArmes[1]->setOutlineColor(Color::Transparent);
	}

	//MISSILE
	if (vaisseauJoueur.weapon == Missile)
	{
		barresArmes[2]->setOutlineColor(couleurHover);
		munitionsHUD.setString(std::to_string(vaisseauJoueur.munitionMissile));
		if (vaisseauJoueur.munitionMissile <= 0)
		{
			vaisseauJoueur.weapon = Base;
			munitionsHUD.setString("");
			vaisseauJoueur.haveMissile = false;
			vaisseauJoueur.weapons.erase(vaisseauJoueur.weapons.begin() + vaisseauJoueur.positionWeapon);
			vaisseauJoueur.positionWeapon = 0;

		}
	}
	else
	{
		barresArmes[2]->setOutlineColor(Color::Transparent);
	}

	//BASE
	if (vaisseauJoueur.weapon == Base)
	{
		barresArmes[0]->setOutlineColor(couleurHover);
	}
	else
	{
		barresArmes[0]->setOutlineColor(Color::Transparent);
	}
	
	//Barres d'armes
	if (vaisseauJoueur.haveLaser)
	{
		barresArmes[3]->setFillColor(couleurHave);
	}
	else
	{
		barresArmes[3]->setFillColor(couleurNoHave);
	}

	if (vaisseauJoueur.haveMissile)
	{
		barresArmes[2]->setFillColor(couleurHave);
	}
	else
	{
		barresArmes[2]->setFillColor(couleurNoHave);
	}

	if (vaisseauJoueur.haveScatter)
	{
		barresArmes[1]->setFillColor(couleurHave);
	}
	else
	{
		barresArmes[1]->setFillColor(couleurNoHave);
	}

	//Change l'emplacement des armes selon les emplacements par defaut
	if (vaisseauJoueur.weapons.size() >= 3)
	{
		for (int i = 1; i < vaisseauJoueur.weapons.size()-1; i++)
		{
			if (*vaisseauJoueur.weapons[i] > *vaisseauJoueur.weapons[i+1])
			{
				Weapon* temp = vaisseauJoueur.weapons[i];
				vaisseauJoueur.weapons[i] = vaisseauJoueur.weapons[i + 1];
				vaisseauJoueur.weapons[i + 1] = temp;
			}
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
			
			if (typeid(*projectiles[i]) != typeid(Projectile_Beam))
			{
				projectiles[i]->move(projectiles[i]->vitesse *cos(projectiles[i]->angle), projectiles[i]->vitesse*sin(projectiles[i]->angle));
			}
			if (projectiles[i]->getPosition().x > LARGEUR_ECRAN || projectiles[i]->getPosition().x < 0)
			{
				if (typeid(*projectiles[i]) != typeid(Projectile_Beam))
				{
					delete projectiles[i];
					projectiles[i] = nullptr;
				}
			}
			if (projectiles[i] != nullptr)
			{
				if (typeid(*projectiles[i]) == typeid(Projectile_Beam))
				{
					if (projectiles[i]->animTermine)
					{
						delete projectiles[i];
						projectiles[i] = nullptr;
						
					}
					//Ajoute le score
					
					if (projectiles[i] != nullptr)
					{
						for (int j = 0; j < ennemis.size(); j++)
						{
							if (ennemis[j] != nullptr && projectiles[i]->hasBeenShot == false)
							{
								//Ajoute le score au joueur
								ajouterScore(j);
							}
						}
						if (!projectiles[i]->hasBeenShot)
						{
							for (size_t j = 0; j < ennemis.size(); j++)
							{
								if (ennemis[j] != nullptr)
								{
									ennemis[j]->ptsVie -= 100;
								}
							}
							projectiles[i]->hasBeenShot = true;
						}
					}
					
				}
			}
			
		}
		if (projectilesEnemy[i] != nullptr)
		{
			projectilesEnemy[i]->move(projectilesEnemy[i]->vitesse *cos(projectilesEnemy[i]->angle), projectilesEnemy[i]->vitesse*sin(projectilesEnemy[i]->angle));
			if (projectilesEnemy[i]->getPosition().x > LARGEUR_ECRAN || projectilesEnemy[i]->getPosition().x < 0)
			{
				delete projectilesEnemy[i];
				projectilesEnemy[i] = nullptr;
			}
		}
	}
}

void tp3::SceneCombat::gererListeEnnemisHUD()
{
	for (int i = 0; i < ennemisSuivants.size(); i++)
	{
		barresEnnemis.push_back(new RectangleShape({ 40, 25 }));
		if (typeid(*ennemisSuivants[i]) == typeid(Enemy1))
		{
			barresEnnemis[barresEnnemis.size()-1]->setTexture(&enemyListeT[0]);
		}
		else if (typeid(*ennemisSuivants[i]) == typeid(Enemy2))
		{
			barresEnnemis[barresEnnemis.size() - 1]->setTexture(&enemyListeT[1]);
		}
		else if (typeid(*ennemisSuivants[i]) == typeid(Enemy3))
		{
			barresEnnemis[barresEnnemis.size() - 1]->setTexture(&enemyListeT[2]);
		}
		else
		{
			barresEnnemis[barresEnnemis.size() - 1]->setTexture(&enemyListeT[3]);
		}
		barresEnnemis[barresEnnemis.size() - 1]->setFillColor(Color::White);
	}
}

void tp3::SceneCombat::gererEnnemis()
{
	int nbEnemy = nbEnemy1 + nbEnemy2 + nbEnemy3;
	// Fais spawn les ennemis
	gererNiveauBoss();
	if (ennemis.empty() && ennemisSuivants.empty() && nbEnemy <= 0 && textAfficheTerminer && !dernierNiveau) //Verifie que le prochain niveau ne joue pas lorsque rendu au boss
	{
		niveauActif++;
		chargerNiveau(niveauActif);
		textAfficheTerminer = false;
	}
	else if (spawnEnemy.getElapsedTime().asSeconds() > 2)
	{
		peutCreerEnnemi = true;
		if (ennemisSuivants.size() > 0)
		{
			Enemy *temp = ennemisSuivants.pop_front();
			ennemis.push_back(temp);
			explosions.push_back(new Explosion(temp->getPosition(), explosionT));
			explosions[explosions.size() - 1]->initGraphiques();
			grp.ajouter(temp);

			if (!dernierNiveau)
			{
				barresEnnemis.erase(barresEnnemis.begin()); //Enleve l'ennemi suivant dans la liste d'ennemis
			}

			if (typeid(*temp) == typeid(Enemy1))
			{
				portail[temp->numeroFabrique]->animTermine = false;
			}
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
	int counterEnemy3 = 0;
	int counterEnemy4 = 0;
	int counterEnemyBoss = 0;

	for (int i = 0; i < ennemis.size(); i++)
	{
		if (ennemis[i] != nullptr)
		{
			ennemis[i]->action(vaisseauJoueur);
			
			//Enemy2 tire
			if (typeid(*ennemis[i]) == typeid(Enemy2))
			{
				counterEnemy2++;
				if (clock_tire_enemy2.getElapsedTime().asMilliseconds() >= 400 && ennemis[i]->isReady && ennemis[i]->canShoot == true)
				{
					ajouterProjectileEnnemis(ennemis[i]->getPosition(), ennemis[i]->getColor(), ennemis[i]->direction, 0.05f, 0);
					if (nbEnemy2 == counterEnemy2 ||  nbEnemy2 == 1)
					{
						clock_tire_enemy2.restart();
					}
				}

			}
			//Enemy3 tire
			if (typeid(*ennemis[i]) == typeid(Enemy3))
			{
				counterEnemy3++;
				if (clock_tire_enemy3.getElapsedTime().asMilliseconds() >= 800 && ennemis[i]->isReady && ennemis[i]->canShoot == true)
				{
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x +10, ennemis[i]->getPosition().y + 35 }, ennemis[i]->getColor(), ennemis[i]->direction, 0.20f, 0);
					if (nbEnemy3 == counterEnemy3 || nbEnemy3 == 1)
					{
						clock_tire_enemy3.restart();
					}
				}
			}
			//Enemy4 tire
			if (typeid(*ennemis[i]) == typeid(Enemy4))
			{
				counterEnemy4++;
				if (clock_tire_enemy4.getElapsedTime().asMilliseconds() >= 800 && ennemis[i]->isReady && ennemis[i]->canShoot == true)
				{
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction, 0.05f, 0.5f);
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction, 0.05f, -0.5f);
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction*-1, 0.05f, 0.5f);
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction*-1, 0.05f, -0.5f);

					if (nbEnemy4 == counterEnemy4 || nbEnemy4 == 1)
					{
						clock_tire_enemy4.restart();
					}
				}
			}
			//Boss tire
			if (typeid(*ennemis[i]) == typeid(Boss))
			{
				if (clock_tire_boss.getElapsedTime().asMilliseconds() >= 700 && ennemis[i]->isReady && ennemis[i]->canShoot == true)
				{
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction, 0.05f, 0.2f);
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction, 0.05f, -0.2f);
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction, 0.05f, 0.8f);
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction, 0.05f, -0.8f);
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction*-1, 0.05f, 0.2f);
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction*-1, 0.05f, -0.2f);
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction*-1, 0.05f, 0.8f);
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction*-1, 0.05f, -0.8f);

					clock_tire_boss.restart();
				}
			}
			//Enemy_boss tire
			if (typeid(*ennemis[i]) == typeid(Enemy_Boss))
			{
				counterEnemyBoss++;
				if (clock_tire_enemyBoss.getElapsedTime().asMilliseconds() >= 800 && ennemis[i]->isReady && ennemis[i]->canShoot == true)
				{
					ajouterProjectileEnnemis({ ennemis[i]->getPosition().x, ennemis[i]->getPosition().y }, ennemis[i]->getColor(), ennemis[i]->direction, 0.05f, 0);
					if (nbEnemyBoss == counterEnemyBoss || nbEnemyBoss == 1)
					{
						clock_tire_enemyBoss.restart();
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

				//Ajoute le score au joueur
				ajouterScore(i);
				explosions.front()->setPosition(ennemis[i]->getPosition());
				explosions.front()->setScale(explosions.front()->getScale().x * ennemis[i]->grosseur, explosions.front()->getScale().x * ennemis[i]->grosseur);
				ennemis.erase(ennemis.begin() + i);
				
				explosions.front()->isReady = true;
			}
		}
	}
}

void tp3::SceneCombat::gererNiveauBoss()
{
	if (dernierNiveau)
	{
		if (ennemis.size() > 0)
		{
			if (ennemis[0] != nullptr)
			{
				cercleCollision->setPosition(ennemis[0]->getPosition());
				if (ennemis[0]->phase == 3)
				{
					//Ajoute les ennemis dans le composite
					if (peutCreerEnnemi)
					{
						ennemisSuivants.push_back(new Enemy_Boss(ennemis[0]->getPosition(), ennemisT[0], Color::Green, 1));

						peutCreerEnnemi = false;
					}
					grp.bouger();
				}
				else if (ennemis[0]->phase == 2)
				{
					if (peutCreerEnnemi2)
					{
						ennemisSuivants.push_back(new Enemy2({ -100, 100 }, ennemisT[1], choixCouleur(), 1));
						ennemisSuivants.push_back(new Enemy2({ -100, 200 }, ennemisT[1], choixCouleur(), 1));
						ennemisSuivants.push_back(new Enemy2({ -100, 300 }, ennemisT[1], choixCouleur(), 1));

						peutCreerEnnemi2 = false;
					}
					grp.bouger();
				}
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
			if (typeid(*bonus[i]) == typeid(Bombe) && bonus[i]->readyAnim)
			{
				bonus[i]->anim();
			}
			
			if (vaisseauJoueur.getGlobalBounds().intersects(bonus[i]->getGlobalBounds()))
			{
				if (typeid(*bonus[i]) != typeid(Bombe))
				{
					bonus[i]->notifierTousLesObservateurs();
				}
				if (typeid(*bonus[i]) == typeid(BombeElectro))
				{
					tempsBombeElectroEnnemis.restart();
					explo.setPosition(bonus[i]->getPosition());
					explo.setOutlineColor(bonus[i]->getColor());
					readyExplo = true;
				}
				if (typeid(*bonus[i]) == typeid(Bombe))
				{
					bonus[i]->readyAnim = true;
				}
				if ((typeid(*bonus[i]) == typeid(BonusScore)))
				{
					tempsBonusScore.restart();
					bonusScoreActif = true;
				}

				//Affiche la liste des boucliers
				if (typeid(*bonus[i]) == typeid(BonusShield))
				{
					static int espaceBoucliers = 50;
					static int precedent = 100;

					if (barresBouclier.size() < NB_BARRES_BOUCLIERS)
					{
						precedent = precedent + espaceBoucliers;
					}
					barresBouclier.push_back(new RectangleShape({ 40, 25 }));
					barresBouclier[barresBouclier.size() - 1]->setTexture(&iconBouclier);
					barresBouclier[barresBouclier.size() - 1]->setFillColor(vaisseauJoueur.shields.top()->getColor());
					
				}
				if (typeid(*bonus[i]) != typeid(Bombe))
				{
					delete bonus[i];
					bonus[i] = nullptr;
				}
				

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
			if (bonus[i] != nullptr)
			{
				if (bonus[i]->animTermine == true)
				{
					bonus[i]->notifierTousLesObservateurs();
					delete bonus[i];
					bonus[i] = nullptr;
				}
			}
		}
		
	}
}

void tp3::SceneCombat::gererScoreJoueur()
{
	
    if (bonusScoreActif)
	{
		scoreHUD.setFillColor(Color::Yellow);
		if (tempsBonusScore.getElapsedTime().asSeconds() > 17)
		{
			scoreHUD.setFillColor(Color::Red);
		}
	}
	else
	{
		scoreHUD.setFillColor(Color::White);
	}
	scoreHUD.setString(std::to_string(scoreJoueur));
	
}

void tp3::SceneCombat::ajouterScore(int indexEnnemis)
{
	if (typeid(*ennemis[indexEnnemis]) == typeid(Enemy1))
	{
		if (bonusScoreActif != true)
		{
			scoreJoueur += 1;
		}
		else
		{
			scoreJoueur += 1 * 2;
		}
	}
	else if (typeid(*ennemis[indexEnnemis]) == typeid(Enemy2))
	{
		if (bonusScoreActif != true)
		{
			scoreJoueur += 3;
		}
		else
		{
			scoreJoueur += 3 * 2;
		}
	}
	else if (typeid(*ennemis[indexEnnemis]) == typeid(Enemy3))
	{
		if (bonusScoreActif != true)
		{
			scoreJoueur += 6;
		}
		else
		{
			scoreJoueur += 6 * 2;
		}
	}
	else
	{
		if (bonusScoreActif != true)
		{
			scoreJoueur += 8;
		}
		else
		{
			scoreJoueur += 8 * 2;
		}
	}
}

void SceneCombat::nbEnnemis()
{
	int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0, temp5 = 0;
	for (int i = 0; i < ennemis.size(); i++)
	{
		if (ennemis[i] != nullptr)
		{
			if (ennemis[i]->isReady)
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
				if (typeid(*ennemis[i]) == typeid(Enemy4))
				{
					temp4++;
				}
				if (typeid(*ennemis[i]) == typeid(Enemy_Boss))
				{
					temp5++;
				}
			}
		}
	}
	nbEnemy1 = temp1;
	nbEnemy2 = temp2;
	nbEnemy3 = temp3;
	nbEnemy4 = temp4;
	nbEnemyBoss = temp5;
}

void SceneCombat::chargerNiveau(int niveau)
{
	//Si ce n'est pas le dernier niveau
	if (niveau != 11)
	{
		text.str("");
		text << "NIVEAU " << niveau;
		textNiveau.setString(text.str());
		niveauHUD.setString(std::to_string(niveau));
		niveauHUD.setOrigin(niveauTextHUD.getGlobalBounds().width / 2, niveauTextHUD.getGlobalBounds().height / 2);
	}

	if (niveau == 1)
	{
		ennemisSuivants.push_back(fabriqueEnemy1->fabriquerEnemy(ennemisT[0], choixCouleur(), 0));
		ennemisSuivants.push_back(fabriqueEnemy3->fabriquerEnemy(ennemisT[0], choixCouleur(), 2));
		ennemisSuivants.push_back(fabriqueEnemy4->fabriquerEnemy(ennemisT[0], choixCouleur(), 3));
		ennemisSuivants.push_back(fabriqueEnemy6->fabriquerEnemy(ennemisT[0], choixCouleur(), 5));
	}
	else if (niveau == 2)
	{
		ennemisSuivants.push_back(fabriqueEnemy1->fabriquerEnemy(ennemisT[0], choixCouleur(), 0));
		ennemisSuivants.push_back(fabriqueEnemy2->fabriquerEnemy(ennemisT[0], choixCouleur(), 1));
		ennemisSuivants.push_back(fabriqueEnemy3->fabriquerEnemy(ennemisT[0], choixCouleur(), 2));
		ennemisSuivants.push_back(fabriqueEnemy4->fabriquerEnemy(ennemisT[0], choixCouleur(), 3));
		ennemisSuivants.push_back(fabriqueEnemy5->fabriquerEnemy(ennemisT[0], choixCouleur(), 4));
		ennemisSuivants.push_back(fabriqueEnemy6->fabriquerEnemy(ennemisT[0], choixCouleur(), 5));
	}
	else if (niveau == 3)
	{
		ennemisSuivants.push_back(fabriqueEnemy1->fabriquerEnemy(ennemisT[0], choixCouleur(), 0));
		ennemisSuivants.push_back(fabriqueEnemy3->fabriquerEnemy(ennemisT[0], choixCouleur(), 2));
		ennemisSuivants.push_back(fabriqueEnemy2->fabriquerEnemy(ennemisT[0], choixCouleur(), 1));
		ennemisSuivants.push_back(fabriqueEnemy6->fabriquerEnemy(ennemisT[0], choixCouleur(), 5));
		ennemisSuivants.push_back(fabriqueEnemy4->fabriquerEnemy(ennemisT[0], choixCouleur(), 3));
		ennemisSuivants.push_back(new Enemy2({ -100, 180 }, ennemisT[1], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy2({ LARGEUR_ECRAN + 100, 180 }, ennemisT[1], choixCouleur(), 1));
	}
	else if (niveau == 4)
	{
		ennemisSuivants.push_back(new Enemy2({ LARGEUR_ECRAN + 100, 180 }, ennemisT[1], choixCouleur(), 1));
		ennemisSuivants.push_back(fabriqueEnemy3->fabriquerEnemy(ennemisT[0], choixCouleur(), 2));
		ennemisSuivants.push_back(new Enemy2({ LARGEUR_ECRAN + 100, 360 }, ennemisT[1], choixCouleur(), 1));
		ennemisSuivants.push_back(fabriqueEnemy5->fabriquerEnemy(ennemisT[0], choixCouleur(), 4));
		ennemisSuivants.push_back(new Enemy2({ -100, 360 }, ennemisT[1], choixCouleur(), 1));
	}
	else if (niveau == 5)
	{
		ennemisSuivants.push_back(new Enemy3({ LARGEUR_ECRAN + 100, 180 }, ennemisT[2], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy3({ -100, 360 }, ennemisT[2], choixCouleur(), 1));
	}
	else if (niveau == 6)
	{
		ennemisSuivants.push_back(new Enemy3({ LARGEUR_ECRAN + 100, 180 }, ennemisT[2], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy3({ -100, 180 }, ennemisT[2], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy3({ LARGEUR_ECRAN + 100, 360 }, ennemisT[2], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy3({ -100, 360 }, ennemisT[2], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy3({ LARGEUR_ECRAN + 100, 540 }, ennemisT[2], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy3({ -100, 540 }, ennemisT[2], choixCouleur(), 1));

		//Bonus laser ;)
		for (int i = 0; i < NBR_BONUS; i++)
		{
			if (bonus[i] == nullptr)
			{
				bonus[i] = new BonusLaserBeam({ LARGEUR_ECRAN/2, HAUTEUR_ECRAN/2 }, bonusT[2]);
				bonus[i]->ajouterObservateur(&vaisseauJoueur);
				bonus[i]->initGraphiques();
				break;
			}
		}
	}
	else if (niveau == 7)
	{
		ennemisSuivants.push_back(fabriqueEnemy2->fabriquerEnemy(ennemisT[0], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy2({ -100, 360 }, ennemisT[1], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy3({ LARGEUR_ECRAN + 100, 180 }, ennemisT[2], choixCouleur(), 1));
		ennemisSuivants.push_back(fabriqueEnemy6->fabriquerEnemy(ennemisT[0], choixCouleur(), 5));
		ennemisSuivants.push_back(fabriqueEnemy1->fabriquerEnemy(ennemisT[0], choixCouleur(), 0));
		ennemisSuivants.push_back(new Enemy2({ LARGEUR_ECRAN + 100, 360 }, ennemisT[1], choixCouleur(), 1));
	}
	else if (niveau == 8)
	{
		ennemisSuivants.push_back(new Enemy4({ -100, 180 }, ennemisT[3], choixCouleur(), 1));
		ennemisSuivants.push_back(fabriqueEnemy1->fabriquerEnemy(ennemisT[0], choixCouleur(), 0));
		ennemisSuivants.push_back(fabriqueEnemy2->fabriquerEnemy(ennemisT[0], choixCouleur(), 1));		
		ennemisSuivants.push_back(fabriqueEnemy5->fabriquerEnemy(ennemisT[0], choixCouleur(), 4));
		ennemisSuivants.push_back(fabriqueEnemy6->fabriquerEnemy(ennemisT[0], choixCouleur(), 5));
		ennemisSuivants.push_back(fabriqueEnemy3->fabriquerEnemy(ennemisT[0], choixCouleur(), 2));
		ennemisSuivants.push_back(fabriqueEnemy4->fabriquerEnemy(ennemisT[0], choixCouleur(), 3));
		ennemisSuivants.push_back(new Enemy4({ -100, 180 }, ennemisT[3], choixCouleur(), 1));
	}
	else if (niveau == 9)
	{
		ennemisSuivants.push_back(new Enemy4({ -100, 180 }, ennemisT[3], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy4({ -100, 360 }, ennemisT[3], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy4({ -100, 540 }, ennemisT[3], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy4({ -100, 360 }, ennemisT[3], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy4({ -100, 180 }, ennemisT[3], choixCouleur(), 1));
	}
	else if (niveau == 10)
	{
		ennemisSuivants.push_back(new Enemy2({ LARGEUR_ECRAN + 100, 180 }, ennemisT[1], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy2({ -100, 360 }, ennemisT[1], choixCouleur(), 1));
		ennemisSuivants.push_back(fabriqueEnemy1->fabriquerEnemy(ennemisT[0], choixCouleur(), 0));
		ennemisSuivants.push_back(fabriqueEnemy4->fabriquerEnemy(ennemisT[0], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy3({ -100, 540 }, ennemisT[2], choixCouleur(), 1));
		ennemisSuivants.push_back(new Enemy4({ -100, 540 }, ennemisT[3], choixCouleur(), 1));
	}
    else if (niveau == 11)
	{
		ennemisSuivants.push_back(new Boss({ LARGEUR_ECRAN + 230, HAUTEUR_ECRAN / 2 }, bossT, Color::White, 1));
		dernierNiveau = true;
	}
	gererListeEnnemisHUD();
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

	//Text warning
	static int cpt = 0;
	if (dernierNiveau && cpt <= 6)
	{
		if (animationWarning.getElapsedTime().asMilliseconds() < 800)
		{
			warning.setFillColor(Color::Red);
		}
		if (animationWarning.getElapsedTime().asMilliseconds() > 800)
		{
			warning.setFillColor(Color::Transparent);
		}
		if (animationWarning.getElapsedTime().asMilliseconds() > 1600)
		{
			animationWarning.restart();
			cpt++;
		}
	}
}

void tp3::SceneCombat::gererFinJeu()
{
	if (!debugMode)
	{
		if (vaisseauJoueur.ptsVie <= 0 || dernierNiveau && ennemis.empty()) //Si la fin du jeu survient
		{
			if (vaisseauJoueur.shields.size() > 0)
			{
				vaisseauJoueur.shields.top()->setColor(Color::Transparent);
			}
			if (!jeuTermine)
			{
				explosions.front()->setPosition(vaisseauJoueur.getPosition());
				explosions.front()->isReady = true;
				vaisseauJoueur.setColor(Color::Transparent);
				clock_finDeJeu.restart();
				jeuTermine = true;
			}
			if (clock_finDeJeu.getElapsedTime().asSeconds() > 3) //On attend un peu
			{
				isRunning = false;
				transitionVersScene = scenes::FIN; //Puis on change de scene
			}
		}
	}
}
