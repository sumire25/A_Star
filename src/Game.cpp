//
// Created by msumi on 24/05/2025.
//

#include "Game.hpp"

void Game::startA_Star() {
	frontier = priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, CompareNode>(CompareNode(this)); // Re-initialize to clear
	reached.clear();

	shared_ptr<Node> startNode = make_shared<Node>();
	startNode->state = character;

	frontier.push(startNode);

	int startKey = startNode->state.first * cols + startNode->state.second;
	reached[startKey] = startNode;

	inProgress = true;
}

void Game::stepA_Star() {
	shared_ptr<Node> curr = frontier.top();
	frontier.pop();
	int key = curr->state.first * cols + curr->state.second;
	if (!reached[key]->bestPath) {
		reached[key]->bestPath = true;
	}
	else {
		return;
	}
	if (curr->state == target) {
		inProgress = false;
		cout << "best path cost: "<<curr->pathCost << endl;
		shared_ptr<Node> currNode = reached[key];
		while (currNode != nullptr) {
			path.push({currNode->state.first, currNode->state.second});
			currNode = currNode->parent;
		}
		return;
	}
	vector<shared_ptr<Node>> children = expandNode(curr);
	for (const auto& child : children) {
		int childKey = child->state.first * cols + child->state.second;
		if (reached.find(childKey) == reached.end() || child->pathCost < reached[childKey]->pathCost) {
			reached[childKey] = child;
			frontier.push(child);
		}
	}
}

vector<shared_ptr<Game::Node>> Game::expandNode(shared_ptr<Node> node) {
	vector<shared_ptr<Node>> children;
	for(int i = 0; i < 9; i++) {
		if (i == 4) continue;
		int dx = (i % 3) - 1;
		int dy = (i / 3) - 1;
		Point newState = {node->state.first + dy, node->state.second + dx};
		if (newState.first >= 0 && newState.first < rows && newState.second >= 0 && newState.second < cols) {
			if (!map.grid[newState.first][newState.second]) {
				if(i%2==0 && map.grid[node->state.first + dy][node->state.second] && map.grid[node->state.first][node->state.second + dx]) {
					continue;
				}
				auto childNode = make_shared<Node>();
				childNode->state = newState;
				childNode->parent = node;
				childNode->action = i;
				childNode->pathCost = node->pathCost + ((dx == 0 || dy == 0) ? CARDINALCOST : DIAGONALCOST);
				children.push_back(childNode);
			}
		}
	}
	return children;
}

Game::Game(int rows, int cols)
	: map(rows, cols, CELL_SIZE)
{
	if (!jerryCharacter.loadFromFile("C:/Users/ERIK RAMOS/CLionProjects/A_Star/img/character.png")) {
		std::cout << "No se puede abrir la imagen";
	}
	if (!cheese.loadFromFile("C:/Users/ERIK RAMOS/CLionProjects/A_Star/img/target.png")) {
		std::cout << "No se puede abrir la imagen";
	}
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
		handleInput();
		window.clear(sf::Color::Black);
		drawGrid();
		if (inProgress) {
			drawAlgorithm();
		}
		if (!path.empty()) {
			updatePosCharacter();
		}
		drawCharacter();

		if(inProgress || !path.empty()) {
			drawTarget();
			sf::sleep(sf::milliseconds(delayForSteps));
		}
		window.display();
	}
}

void Game::handleInput() {
	while (auto event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		if (event-> is<sf::Event::MouseButtonPressed>() && !inProgress) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			auto cell = map.getCellPos(mousePos.x, mousePos.y);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
				this -> target = cell;
				startA_Star();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				drawStart = cell;
				dragging = true;
			}
		}
		if (event -> is<sf::Event::MouseButtonReleased>() && !inProgress) {
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
		if (event -> is<sf::Event::MouseWheelScrolled>()) {
			const auto* wheelEvent = event->getIf<sf::Event::MouseWheelScrolled>();
			if (wheelEvent) {
				if (wheelEvent->delta > 0) {
					delayForSteps += 25;
				} else if (wheelEvent->delta < 0) {
					delayForSteps -= 25;
					if (delayForSteps < 0) {
						delayForSteps = 0;
					}
				}
				cout << "Delay for steps: " << delayForSteps << endl;

			}

		}

	}
}

void Game::drawGrid() {
	map.draw(window);
}

void Game::drawAlgorithm() {
	if(!frontier.empty()) {
		stepA_Star();
		// iterate reached nodes and draw them
		for (const auto& [key, node] : reached) {
			sf::RectangleShape nodeShape({CELL_SIZE, CELL_SIZE});
			nodeShape.setPosition(sf::Vector2f{static_cast<float>(node->state.second * CELL_SIZE), static_cast<float>(node->state.first * CELL_SIZE)});
			if (node->bestPath) {
				nodeShape.setFillColor(sf::Color::Yellow);
			} else {
				nodeShape.setFillColor(sf::Color::Blue);
			}
			window.draw(nodeShape);
		}
	}
	else {//solution not found
		inProgress = false;
	}
}

void Game::drawCharacter() {
	sf::Sprite charac(jerryCharacter);
	charac.setPosition({static_cast<float>(character.second * CELL_SIZE), static_cast<float>(character.first * CELL_SIZE)});
	window.draw(charac);

}

void Game::drawTarget() {
	if (target.first >= 0 && target.second >= 0) {
		sf::Sprite tar(cheese);
		tar.setPosition({static_cast<float>(target.second * CELL_SIZE), static_cast<float>(target.first * CELL_SIZE)});
		window.draw(tar);
	}
}
void Game::updatePosCharacter() {
	Point next = path.top();
	if (character != next) {
		character = next;
	} else {
		path.pop();
	}

}