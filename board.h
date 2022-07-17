#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <vector>
#include <QTimer>
#include <stack>
#include <string>
#include "board_states.h"
#include "snake.h"
#include "food.h"

class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rows MEMBER kRows CONSTANT)
    Q_PROPERTY(int cols MEMBER kCols CONSTANT)
public:
    explicit Board(QObject *parent = nullptr);
    Snake &getSnake();
    void initBoard();

signals:
    void boardStateChanged(int row, int col, QString color);
    void gameOver();

private slots:
    void onBoardStateChanged(int row, int col, int boardState);
    void onTimerTimeout();
    void onGameOver();

private:
    const int kRows = 10;
    const int kCols = 10;

    std::vector<std::vector<int>> m_board;
    Snake m_snake;
    Food m_food;
    QTimer m_timer;
    std::stack<std::pair<int, int>> m_shortestPath;
};

#endif // BOARD_H
