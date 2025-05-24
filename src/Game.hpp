//
// Created by msumi on 24/05/2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

typedef pair<int, int> Point;

class Game {
public:
	vector<vector<bool>> grid;
	int rows, cols;
	Point character, target;

	sf::RenderWindow window;

	Game(int rows, int cols);
	void run();
	void drawGrid();
	void drawAlgorithm();
	void drawCharacterAndTarget();
};



#endif //GAME_HPP
