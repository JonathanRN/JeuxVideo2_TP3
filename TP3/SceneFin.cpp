#include "SceneFin.h"

using namespace tp3;

SceneFin::SceneFin() :fond(LARGEUR_ECRAN, HAUTEUR_ECRAN, 5)
{
}


SceneFin::~SceneFin()
{
}

Scene::scenes SceneFin::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneFin::init(RenderWindow * const window)
{
	if (!fond.setTexture("Ressources\\background.jpg"))
	{
		return false;
	}
	if (!font.loadFromFile("Ressources\\Font\\font.ttf"))
	{
		return false;
	}

	//Text gameover
	gameOver.setFont(font);
	gameOver.setPosition(LARGEUR_ECRAN/2 - 300, 25);
	gameOver.setCharacterSize(100);
	gameOver.setFillColor(Color::Red);
	gameOver.setString("GAME OVER!");

	//Text score
	scoreText.setFont(font);
	scoreText.setPosition(LARGEUR_ECRAN / 2- 175, 200);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(Color::White);
	scoreText.setString("Votre score: ");

	//Score
	score.setFont(font);
	score.setPosition(LARGEUR_ECRAN / 2 - 150, 250);
	score.setCharacterSize(50);
	score.setFillColor(Color::White);
	score.setString(std::to_string(scoreJoueur));

	//Bouton revenir
	quitter.setFont(font);
	quitter.setPosition(LARGEUR_ECRAN/2 - 120, 500);
	quitter.setCharacterSize(50);
	quitter.setFillColor(Color::White);
	quitter.setString("Quitter");


	this->mainWin = window;
	isRunning = true;
	return true;
}

void SceneFin::getInputs()
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

void SceneFin::update()
{
	// récupération de la position de la souris dans la fenêtre
	pixelPos = Mouse::getPosition(*mainWin);

	// conversion en coordonnées "monde"
	worldPos = mainWin->mapPixelToCoords(pixelPos);

	//Change la couleur du text selon la position de la souris
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

	fond.move(1);
}

void SceneFin::draw()
{
	mainWin->clear();
	fond.draw(mainWin);
	mainWin->draw(scoreText);
	mainWin->draw(quitter);
	mainWin->draw(gameOver);
	mainWin->draw(score);
	mainWin->display();
}
