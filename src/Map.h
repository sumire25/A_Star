//
// Created by ERIK RAMOS on 24/05/2025.
//

#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include "conventions.hpp"


class Map {

public:
    std::vector<std::vector<bool>> grid;
    int rows, cols;
    float cellSize;

    Map(int rows, int cols, float cellSize);
    void draw(sf::RenderWindow& window);
    Point getCellPos(int x, int y) const;
};



#endif //MAP_H
