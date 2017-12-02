#include "SceneTitre.h"

using namespace tp3;

SceneTitre::SceneTitre():fond(LARGEUR_ECRAN, HAUTEUR_ECRAN, 5)
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
	if (!fond.setTexture("Ressources\\background.jpg"))
	{
		return false;
	}
	if (!font.loadFromFile("Ressources\\Font\\font.ttf"))
	{
		return false;
	}
	if (!vaisseauT.loadFromFile("Ressources\\Player_titre.png"))
	{
		return false;
	}

	vaisseau.setTexture(vaisseauT);
	vaisseau.setPosition(-400, 160);
	vaisseau.setOrigin(vaisseau.getTexture()->getSize().x / 2, vaisseau.getTexture()->getSize().y / 2);

	//Text du titre a l'ecran
	titre.setFont(font);
	titre.setPosition(220, 110);
	titre.setCharacterSize(120);
	titre.setFillColor(Color::White);
	text.str("");

	//Bouton jouer
	jouer.setFont(font);
	jouer.setPosition(200, 200);
	jouer.setCharacterSize(50);
	jouer.setFillColor(Color::White);
	jouer.setString("");
	//Bouton quitter
	quitter.setFont(font);
	quitter.setOrigin(quitter.getGlobalBounds().width / 2, quitter.getGlobalBounds().width / 2);
	quitter.setPosition(200, 300);
	quitter.setCharacterSize(50);
	quitter.setFillColor(Color::White);
	quitter.setString("");

	//Fait par:
	description1.setFont(font);
	description1.setPosition(LARGEUR_ECRAN-400, 200);
	description1.setCharacterSize(40);
	description1.setFillColor(Color::Yellow);
	description1.setString("");
	//Jonathan Roy-Noel et Kevin R. Leclaire
	description2.setFont(font);
	description2.setPosition(LARGEUR_ECRAN-400, 250);
	description2.setCharacterSize(40);
	description2.setFillColor(Color::Yellow);
	description2.setString("");

	description3.setFont(font);
	description3.setPosition(LARGEUR_ECRAN - 400, 300);
	description3.setCharacterSize(40);
	description3.setFillColor(Color::Yellow);
	description3.setString("");
	

	this->mainWin = window;
	isRunning = true;
	return true;
}

void SceneTitre::getInputs()
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
}

void SceneTitre::update()
{
	static int posX = 0; //Position precedente du vaisseau
	static int cpt = 0; //Compteur de caracteres

	// récupération de la position de la souris dans la fenêtre
	pixelPos = Mouse::getPosition(*mainWin);

	// conversion en coordonnées "monde"
	worldPos = mainWin->mapPixelToCoords(pixelPos);
	

	//Si l'animation du vaisseau n'est pas finie
	if (!animVaisseauFinie)
	{
		//Si le vaisseau depasse l'ecran, cest fini
		if (vaisseau.getPosition().x > LARGEUR_ECRAN+vaisseau.getTexture()->getSize().x)
		{
			animVaisseauFinie = true;
		}
		else
		{
			vaisseau.move(11.5, 0); //Sinon il bouge
		}

		//Affiche les lettres une par une selon la position du vaisseau
		if (vaisseau.getPosition().x > posX + 62 && cpt < 14)
		{
			text << titreText[cpt];
			cpt++;
			posX = vaisseau.getPosition().x;
		}
	}
	else
	{
		//Petite animation du titre
		if (titre.getScale().x >= 0.6 && titre.getScale().y >= 0.6)
		{
			titre.setScale(titre.getScale().x * 0.95, titre.getScale().y * 0.95);
			titre.setColor(Color::Yellow);
			titre.setPosition(titre.getPosition().x * 0.95, titre.getPosition().y * 0.95);
		}
		else
		{
			animTitreFinie = true;
		}
		//Appartition des boutons
		if (animTitreFinie)
		{
			jouer.setString("Jouer");
			quitter.setString("Quitter");
			description1.setString("Fait par:");
			description2.setString("Jonathan Roy-Noel");
			description3.setString("& Kevin R. Leclaire");
			//Change la couleur du text selon la position de la souris
			//Jouer
			if (worldPos.x >= jouer.getPosition().x && worldPos.x <= jouer.getPosition().x + jouer.getGlobalBounds().width
				&& worldPos.y - 28 >= jouer.getPosition().y && worldPos.y - 28 <= jouer.getPosition().y + jouer.getGlobalBounds().height)
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					isRunning = false;
					transitionVersScene = Scene::scenes::COMBAT;
				}
				jouer.setColor(Color::Yellow);
			}
			else
			{
				jouer.setColor(Color::White);
			}
			//Quitter
			if (worldPos.x >= quitter.getPosition().x && worldPos.x <= quitter.getPosition().x + quitter.getGlobalBounds().width
				&& worldPos.y - 28 >= quitter.getPosition().y && worldPos.y - 28 <= quitter.getPosition().y + quitter.getGlobalBounds().height)
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					exit(0);
				}
				quitter.setColor(Color::Yellow);
			}
			else
			{
				quitter.setColor(Color::White);
			}
		}
	}
	fond.move(1);
	titre.setString(text.str());
}

void SceneTitre::draw()
{
	mainWin->clear();
	fond.draw(mainWin);
	mainWin->draw(vaisseau);
	mainWin->draw(titre);
	mainWin->draw(description1);
	mainWin->draw(description2);
	mainWin->draw(description3);
	mainWin->draw(jouer);
	mainWin->draw(quitter);
	mainWin->display();
}
