#pragma once
#include <ftxui/component/component.hpp>
#include <vector>
#include <utility>

using Pos = std::pair<int, int>;

struct SnakeGame {
    std::vector<Pos> snakeBody;
    Pos food;
    int dirX = 1;
    int dirY = 0;
    int score = 0;

    const int mapWidth = 20;
    const int mapHeight = 15;

    //函数声明
    void GameInit();
    void SnakeMove();
    void CreateFood();
    bool IsGameOver();
};