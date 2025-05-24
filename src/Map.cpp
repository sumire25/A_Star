//
// Created by ERIK RAMOS on 24/05/2025.
//

#include "Map.h"
Map::Map(int rows, int cols, float cellSize)
    : rows(rows), cols(cols), cellSize(cellSize) {
    grid.resize(rows, std::vector<bool>(cols, false)); // Inicializa todo como libre
}

void Map::draw(sf::RenderWindow& window) {
    sf::Color gridColor(100, 100, 100);
    sf::Color obstacleColor(200, 50, 50);

    // Líneas horizontales
    for (int i = 0; i <= rows; ++i) {
        sf::Vertex line[] = {
            {sf::Vector2f{0.f, i * cellSize}, gridColor},
            {sf::Vector2f{cols * cellSize, i * cellSize}, gridColor}
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Líneas verticales
    for (int j = 0; j <= cols; ++j) {
        sf::Vertex line[] = {
            {sf::Vector2f{j * cellSize, 0.f}, gridColor},
            {sf::Vector2f{j * cellSize, rows * cellSize}, gridColor}
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Obstáculos
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j]) {
                sf::RectangleShape obstacle({cellSize, cellSize});
                obstacle.setPosition(sf::Vector2f{j * cellSize, i * cellSize});
                obstacle.setFillColor(obstacleColor);
                window.draw(obstacle);
            }
        }
    }
}

Point Map::getCellPos(int x, int y) const {
    int col = x / cellSize;
    int row = y / cellSize;
    if (row >= 0 && row < rows && col >= 0 && col < cols)
        return {row, col};
    return {-1, -1}; // fuera del mapa
}


