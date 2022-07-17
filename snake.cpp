#include "snake.h"

Snake::Snake(QObject *parent) : QObject(parent),
    m_snakePos({ std::make_pair(0,2), std::make_pair(0,1), std::make_pair(0,0) })
{
}

void Snake::initSnake()
{
    for (auto it = m_snakePos.begin(); it != m_snakePos.end(); ++it){
        if (it == m_snakePos.begin())
            emit snakePosChanged(it->first, it->second, BoardStates::SnakeHead);
        else
            emit snakePosChanged(it->first, it->second, BoardStates::SnakeBody);
    }
}

const std::list<std::pair<int, int> > &Snake::getSnakePos()
{
    return m_snakePos;
}

void Snake::moveSnake(const std::pair<int, int> &headPos)
{
    growSnake(headPos);

    emit snakePosChanged(m_snakePos.back().first, m_snakePos.back().second, BoardStates::Unset);
    m_snakePos.pop_back();
    emit snakePosChanged(m_snakePos.back().first, m_snakePos.back().second, BoardStates::SnakeTail);
}

void Snake::growSnake(const std::pair<int, int> &headPos)
{
    emit snakePosChanged(m_snakePos.front().first, m_snakePos.front().second, BoardStates::SnakeBody);
    m_snakePos.emplace_front(headPos);
    emit snakePosChanged(m_snakePos.front().first, m_snakePos.front().second, BoardStates::SnakeHead);
    emit snakePosChanged(m_snakePos.back().first, m_snakePos.back().second, BoardStates::SnakeTail);
}
