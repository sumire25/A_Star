//
// Created by msumi on 24/05/2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "conventions.hpp"

using namespace std;

class Game {
public:
	vector<vector<bool>> grid;
	int rows, cols;
	Point character, target;

	sf::RenderWindow window;

	//A_Star variables;
	int speedOfSteps = 100;

	Game(int rows, int cols);
	void run();
	void handleInput();
	void drawGrid();
	void drawAlgorithm();
	void drawCharacterAndTarget();
};



#endif //GAME_HPP
