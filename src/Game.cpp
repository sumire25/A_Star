//
// Created by msumi on 24/05/2025.
//

#include "Game.hpp"

Game::Game(int rows, int cols) {
	rows = rows;
	cols = cols;
	character = {rows/2, cols/2};
	target = {rand() % rows, rand() % cols};
	grid.resize(rows, vector<bool>(cols, false));
	//initialize sfml objects
	window.create(sf::VideoMode({1080,720}), "Game");
	window.setFramerateLimit(60);
}

void Game::run() {
	while(window.isOpen()) {
		while (auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		drawGrid();
		drawAlgorithm();
		drawCharacterAndTarget();
		window.display();
	}
}

void Game::drawGrid() {
}

void Game::drawAlgorithm() {
}

void Game::drawCharacterAndTarget() {
}
