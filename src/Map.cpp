//
// Created by ERIK RAMOS on 24/05/2025.
//

#include "Map.h"
Map::Map(int rows, int cols, float cellSize)
    : rows(rows), cols(cols), cellSize(cellSize) {
    grid.resize(rows, std::vector<bool>(cols, false));
    if (!texture.loadFromFile("C:/Users/ERIK RAMOS/CLionProjects/A_Star/img/obstacle.png")) {
        std::cout << "No se puede abrir la imagen";
    }
}

void Map::draw(sf::RenderWindow& window) {
    sf::Color gridColor(100, 100, 100);
    sf::Color obstacleColor(150, 150, 150);

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
                sf::Sprite sprite(texture);
                sprite.setPosition({j * cellSize, i * cellSize});
                window.draw(sprite);
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

void Map::setObstacle(int row, int col, bool value) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        grid[row][col] = value;
    }
}

void Map::setObstacleRect(Point start, Point end, bool value) {
    int r1 = std::min(start.first, end.first);
    int r2 = std::max(start.first, end.first);
    int c1 = std::min(start.second, end.second);
    int c2 = std::max(start.second, end.second);
    for (int i = r1; i <= r2; ++i) {
        for (int j = c1; j <= c2; ++j) {
            setObstacle(i, j, value);
        }
    }
}


