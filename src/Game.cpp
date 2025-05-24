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
	target = { -1, -1};
	drawStart = { -1, -1};
	drawEnd = { -1, -1};
	dragging = false;
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
		drawTarget();
		window.display();
	}
}

void Game::handleInput() {
	while (auto event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		if (event-> is<sf::Event::MouseButtonPressed>()) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			auto cell = map.getCellPos(mousePos.x, mousePos.y);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {

				this -> target = cell;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				drawStart = cell;
				dragging = true;
			}
		}
		if (event -> is<sf::Event::MouseButtonReleased>()) {
			const auto* mouseEvent = event->getIf<sf::Event::MouseButtonReleased>();
			if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left && dragging) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				drawEnd = map.getCellPos(mousePos.x, mousePos.y);
				if (drawStart == drawEnd && drawStart.first >= 0 && drawStart.second >= 0) {
					map.setObstacle(drawStart.first, drawStart.second, !map.grid[drawStart.first][drawStart.second]);
				} else if (drawStart.first >= 0 && drawStart.second >= 0 && drawEnd.first >= 0 && drawEnd.second >= 0) {
					map.setObstacleRect(drawStart, drawEnd, !map.grid[drawStart.first][drawStart.second]);
				}
				dragging = false;
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

void Game::drawTarget() {
	if (target.first >= 0 && target.second >= 0) {
		sf::RectangleShape targetShape({CELL_SIZE, CELL_SIZE});
		targetShape.setPosition(sf::Vector2f{static_cast<float>(target.second * CELL_SIZE), static_cast<float>(target.first * CELL_SIZE)});
		targetShape.setFillColor(sf::Color::Red);
		window.draw(targetShape);
	}
}