#include "snake.hpp"
#include <random>

void SnakeGame::GameInit()
{
    snakeBody.clear();
    snakeBody.push_back({4, 4});
    dirX = 1;
    dirY = 0;
    score = 0;
    CreateFood();
}

void SnakeGame::CreateFood()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> w(1, mapWidth - 2);
    std::uniform_int_distribution<int> h(1, mapHeight - 2);

    food.first = w(rng);
    food.second = h(rng);
}

void SnakeGame::SnakeMove()
{
    Pos head = snakeBody.front();
    Pos newHead = {head.first + dirX, head.second + dirY};

    if (newHead == food)
    {
        score += 10;
        CreateFood();
    }
    else
    {
        snakeBody.pop_back();
    }
    snakeBody.insert(snakeBody.begin(), newHead);
}

bool SnakeGame::IsGameOver()
{
    Pos head = snakeBody.front();
    //撞击墙壁
    if (head.first <= 0 || head.first >= mapWidth - 1 || head.second <= 0 || head.second >= mapHeight - 1)
    {
        return true;
    }
    //撞击自身
    for (int i = 1; i < snakeBody.size(); i++)
    {
        if (snakeBody[i] == head)
            return true;
    }
    return false;
}