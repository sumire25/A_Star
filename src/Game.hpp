//
// Created by msumi on 24/05/2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "conventions.hpp"
#include "Map.h"

using namespace std;

class Game {
public:
	vector<vector<bool>> grid;
	int rows, cols;
	Point character;
	Map map;
	sf::RenderWindow window;

	//A_Star variables;
	bool inProgress = false;
	int speedOfSteps = 100;
	Point target;

	Game(int rows, int cols);
	void run();
	void handleInput();
	void drawGrid();
	void drawAlgorithm();
	void drawCharacter();
};



#endif //GAME_HPP
