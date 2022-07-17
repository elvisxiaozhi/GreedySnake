#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <list>
#include "board_states.h"

class Snake : public QObject
{
    Q_OBJECT
public:
    explicit Snake(QObject *parent = nullptr);
    void initSnake();
    const std::list<std::pair<int, int>> &getSnakePos();
    void moveSnake(const std::pair<int, int> &headPos);
    void growSnake(const std::pair<int, int> &headPos);

signals:
    void snakePosChanged(int row, int col, int snakeHead = BoardStates::SnakeBody);

private:
    std::list<std::pair<int, int>> m_snakePos;
};

#endif // SNAKE_H
