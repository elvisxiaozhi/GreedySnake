#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <unordered_set>
#include <random>
#include "board_states.h"

class Food : public QObject
{
    Q_OBJECT
public:
    explicit Food(QObject *parent = nullptr);
    void initFood(int rows, int cols, const std::list<std::pair<int, int>> &unavailPos);
    bool genFood(int rows, int cols, const std::list<std::pair<int, int>> &unavailPos);
    const std::pair<int, int> &getFoodPos();

signals:
    void foodPosChanged(int row, int col, int boardState = BoardStates::Food);

private:
    std::pair<int, int> m_food_pos;

    std::random_device rd;
    std::mt19937 rng;

    inline void erasePos(int pos);
};

#endif // FOOD_H
