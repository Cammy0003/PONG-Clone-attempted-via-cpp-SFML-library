#include "Game.hpp"

Game::Game() {
	initVariables();
}

Game::~Game()
{

	std::cout << "Endgame!" << std::endl;
}

void Game::run()
{
	while (window.isOpen()) 
	{
		pollWindow();

		//update();

		window.clear();

		update();
		render();

		window.display();
	}
}

void Game::initVariables()
{
	initWindow();

	initComponents();

	initPlayers();

	initBall();
}

void Game::initWindow()
{
	this->dimensions.x = 800;
	this->dimensions.y = 600;

	this->window.create(sf::VideoMode(dimensions.x, dimensions.y), "PONG", sf::Style::Default);
	window.setFramerateLimit(60);

}

void Game::initComponents()
{

	this->speedPlayers = { 4 };
	this->speedBall = { 2 };
	this->score = { 0 };
	this->directionXBall = false;
	this->directionYBall = false;


}

void Game::update()
{
	updatePlayer1();
	updateBall();
}

/*
	Player 1 is the controlled player
*/
void Game::updatePlayer1() 
{

	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ) {

		if (checkWindowYCol((player1.getPosition().y - 50) - speedPlayers) == true) {
			this->player1.setPosition(sf::Vector2f(player1.getPosition().x, player1.getPosition().y - speedPlayers));
		}

	}
	else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ){

		if (checkWindowYCol((player1.getPosition().y + 50) + speedPlayers) == true) {
			this->player1.setPosition(sf::Vector2f(player1.getPosition().x, player1.getPosition().y + speedPlayers));
		}

	}
	
}

void Game::updateBall()
{

	//float tempMove = ball.getPosition().x;


	
	if (checkWindowXCol(ball.getPosition().x - 15) == false) {
		directionXBall = true;
	}
	else if(checkWindowXCol(ball.getPosition().x + 15) == false) {
		directionXBall = false;
	}

	//std::cout << "direction of Ball: " << directionXBall << std::endl;
	// Now check Collisions
	if( directionXBall == true)
	{
		if(checkObjCol() == true)
		{
			directionXBall = false;
		}
	}
	else
	{
		if(checkObjCol() == true)
		{
			directionXBall = true;
		}
	}

	
	if (directionXBall == true) {
		//this->ball.setPosition(sf::Vector2f(ball.getPosition().x + speedBall, tempMove));
		this->movingX = ball.getPosition().x + speedBall;
	}
	else {
		//this->ball.setPosition(sf::Vector2f(ball.getPosition().x - speedBall, tempMove));
		this->movingX = ball.getPosition().x - speedBall;
	}
	

	if (checkWindowYCol(ball.getPosition().y + 15) == false) {
		directionYBall = true;
	}
	else if (checkWindowYCol(ball.getPosition().y - 15) == false) {
		directionYBall = false;
	}
	
	if (directionYBall == true) {
		this->movingY = ball.getPosition().y - speedBall;
	}
	else {
		this->movingY = ball.getPosition().y + speedBall;
	}

	this->ball.setPosition(sf::Vector2f(movingX, movingY));

}



void Game::initPlayers()
{
	//Set size of Object
	player1.setSize(sf::Vector2f(30, 100));	//Vector2f(width, height)
	player2.setSize(sf::Vector2f(30, 100));	//Vector2f(width, height)

	//Set Color of Object
	player1.setFillColor(sf::Color(255, 0, 0)); // P1 Red
	player2.setFillColor(sf::Color(0, 255, 0)); // P2 Blue

	//Set Origin of Object
	player1.setOrigin(30 / 2, 100 / 2); // P1 Setting origins to centre
	player2.setOrigin(30 / 2, 100 / 2); // P2 Setting origins to centre

	//Init Positions
	player1.setPosition(sf::Vector2f(30, dimensions.y / 2)); // Setting INITIAL pos!
	player2.setPosition(sf::Vector2f(dimensions.x - 30, dimensions.y / 2)); // Setting Initial Pos

}

void Game::initBall()
{
	this->ball.setSize(sf::Vector2f(30, 30)); //set dimensions

	this->ball.setFillColor(sf::Color(0, 0, 255)); // Blue

	this->ball.setOrigin(30 / 2, 30 / 2); // Origin is centre of square

	this->ball.setPosition(sf::Vector2f(dimensions.x / 2, dimensions.y / 2)); // Place in middle
}

/*
	check if Given Player hits the top. Return FALSE if the player hits the top or bottom of the window. 
*/
bool Game::checkWindowYCol(float yPos)
{
	if(yPos < dimensions.y && yPos > 0.0){
		return true;
	}
	return false;
}

/*
	return false if ball hits the side of the window
*/
bool Game::checkWindowXCol(float xPos) 
{	
	if (xPos < dimensions.x && xPos > 0.0) {
		return true;
	}
	return false;
}

bool Game::checkObjCol()
{
	if (this->directionXBall == false ) //going left
	{
		//Check Collisions with P1
		if(this->ball.getPosition().x < this->player1.getPosition().x + 15 && this->ball.getPosition().x > this->player1.getPosition().x - 15)
		{
			//Means we are within the x range of player and the border of the window
			if(this->ball.getPosition().y + 15 <= this->player1.getPosition().y + 15 && this->ball.getPosition().y + 15 >= this->player1.getPosition().y - 15)
			{
				//Then we are inside the player.
				return true;
			}
		}

		return false;

	}
	else //direction == true  // going right
	{
		if (this->ball.getPosition().x < this->player2.getPosition().x + 15 && this->ball.getPosition().x > this->player2.getPosition().x - 15)
		{
			//Means we are within the x range of player and the border of the window
			if (this->ball.getPosition().y + 15 <= this->player2.getPosition().y + 15 && this->ball.getPosition().y + 15 >= this->player2.getPosition().y - 15)
			{
				//Then we are inside the player.
				return true;
			}
		}

		return false;
	}
}


void Game::render()
{

	renderPlayers();
	renderBall();
	
}

void Game::pollWindow()
{

	sf::Event event;

	while (window.pollEvent(event)) {

		switch (event.type) {

			case sf::Event::Closed:
				endGame();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					endGame();
				}
				break;

			default:
				break;

		}
	}

}

void Game::renderPlayers()
{
	window.draw(player1);
	window.draw(player2);
}

void Game::renderBall()
{
	window.draw(ball);
}




//Destructor 

void Game::endGame()
{
	window.close();
	std::cout << "GoodBye" << std::endl;
}

