#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>


class Game {
public:

	//Constructor
	Game();

	//Destructor
	~Game();

	void run();

private:

	/*Variables*/
		//Window
	sf::RenderWindow window;
	sf::Vector2i dimensions; // Window Dimensions

		//Objects
	sf::RectangleShape player1; //Red and will be controlled
	sf::RectangleShape player2; //Blue and will be ai
	sf::RectangleShape ball; // Ball

		//Objects
	int speedPlayers; // speed of Players

		//Ball
	int speedBall; // speed of Ball
	bool directionXBall; // true = right, false = left.
	bool directionYBall; // true = up, false = down.
	float movingX;
	float movingY;
	int score;

	//Initialize Vars

	void initVariables();

	void initWindow();
	void initComponents();
	void initPlayers();
	void initBall();

	//UPDATE vars
	void update();

	//Score
	void updateScore();

	// Objects
	void updatePlayer1(); // Will be controlled. Returns Vector2f for position
	void updatePlayer2(); // Will be ai
	void updateBall();

	//Collisions
	bool checkWindowYCol(float yPos);
	bool checkWindowXCol(float xPos);
	bool checkObjCol();

	//Render Vars

	void render();

	void pollWindow();
	void renderPlayers();
	void renderBall();


	//Window


	void endGame();


};
