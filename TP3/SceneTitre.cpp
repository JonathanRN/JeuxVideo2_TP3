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
	vaisseau.setPosition(-400, 180);
	vaisseau.setOrigin(vaisseau.getTexture()->getSize().x / 2, vaisseau.getTexture()->getSize().y / 2);

	//Text de niveau a l'ecran
	titre.setFont(font);
	titre.setPosition(LARGEUR_ECRAN / 2 - 300, 150);
	titre.setCharacterSize(150);
	titre.setFillColor(Color::White);
	text.str("");

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
	static int posX = 0;
	static int cpt = 0;

	if (!animVaisseauFinie)
	{
		if (vaisseau.getPosition().x > LARGEUR_ECRAN+vaisseau.getTexture()->getSize().x)
		{
			animVaisseauFinie = true;
		}
		else
		{
			vaisseau.move(12, 0);
		}

		if (vaisseau.getPosition().x > posX + 110 && cpt < 6)
		{
			text << titreText[cpt];
			cpt++;
			posX = vaisseau.getPosition().x;
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
	mainWin->display();
}
