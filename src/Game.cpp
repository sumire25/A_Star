//
// Created by msumi on 24/05/2025.
//

#include "Game.hpp"

Game::Game(int rows, int cols) {
	rows = rows;
	cols = cols;
	character = {rows/2, cols/2};
	grid.resize(rows, vector<bool>(cols, false));
	//initialize sfml objects
	window.create(sf::VideoMode({WIN_WIDTH,	WIN_HEIGHT}), "Game");
	window.setFramerateLimit(60);
}

void Game::run() {
	while(window.isOpen()) {
		handleInput();
		window.clear(sf::Color::Black);
		drawGrid();
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
	}
}

void Game::drawGrid() {
}

void Game::drawAlgorithm() {
}

void Game::drawCharacter() {
}
