//
// Created by msumi on 24/05/2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include <bits/stdc++.h>
#include <memory>
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
	Point drawStart;
	Point drawEnd;
	bool dragging;
	//A_Star variables;
	bool inProgress = false;
	int delayForSteps = 350;
	stack<Point> path;
	Point target;
	struct Node {
		Point state;
		shared_ptr<Node> parent = nullptr;
		int action;
		int pathCost = 0;
		bool bestPath = false;
		Node() = default;
	};
	int heuristic(Point a) {
		int dy = abs(a.first - target.first);
		int dx = abs(a.second - target.second);
		int maxDiagonal = min(dx, dy);
		return DIAGONALCOST * maxDiagonal + CARDINALCOST * (dx + dy - 2 * maxDiagonal);
	}
	struct CompareNode {
		Game* game;
		CompareNode(Game* g) : game(g) {}
		bool operator()(const shared_ptr<Node>& a, const shared_ptr<Node>& b) const {
			return a->pathCost + game->heuristic(a->state)>
									 b->pathCost + game->heuristic(b->state);
		}
	};
	priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, CompareNode> frontier{CompareNode(this)};
	unordered_map<int, shared_ptr<Node>> reached;
	void startA_Star();
	void stepA_Star();
	vector<shared_ptr<Node>> expandNode(shared_ptr<Node> node);
	// texturas
	sf::Texture jerryCharacter;
	sf::Texture cheese;
	Game(int rows, int cols);
	void run();
	void handleInput();
	void drawTarget();
	void drawGrid();
	void drawAlgorithm();
	void drawCharacter();
	void updatePosCharacter();
};



#endif //GAME_HPP
