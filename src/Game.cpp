//
// Created by msumi on 24/05/2025.
//

#include "Game.hpp"

Game::Game(int rows, int cols)
	: map(rows, cols, CELL_SIZE)
{
	this->rows = WIN_HEIGHT / CELL_SIZE;
	this->cols = WIN_WIDTH / CELL_SIZE;
	map = Map(this->rows, this->cols, CELL_SIZE);
	character = {this->rows / 2, this->cols / 2};
	grid.resize(this->rows, vector<bool>(this->cols, false));
	window.create(sf::VideoMode({WIN_WIDTH, WIN_HEIGHT}), "Game");
	window.setFramerateLimit(60);
}

void Game::run() {
	while(window.isOpen()) {
		window.clear(sf::Color::Black);
		drawGrid();
		handleInput();
		if (inProgress) {
			drawAlgorithm();
		}
		drawCharacter();
		window.display();
	}
}

void Game::handleInput() {
	while (auto event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		if (event-> is<sf::Event::MouseButtonPressed>()) {

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
				sf::RectangleShape characterShape({CELL_SIZE, CELL_SIZE});
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				auto cell = map.getCellPos(mousePos.x, mousePos.y);
				this -> target = cell;
				cout << this -> target.first << " " << this -> target.second << endl;
			}
		}

	}
}

void Game::drawGrid() {
	map.draw(window);
}

void Game::drawAlgorithm() {
}

void Game::drawCharacter() {
	sf::RectangleShape characterShape({CELL_SIZE, CELL_SIZE});
	characterShape.setPosition(sf::Vector2f{static_cast<float>(character.second * CELL_SIZE), static_cast<float>(character.first * CELL_SIZE)});
	characterShape.setFillColor(sf::Color::Green);
	window.draw(characterShape);

}
