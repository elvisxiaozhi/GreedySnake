#include "board.h"
#include "board_colors.h"
#include "a_star_algo.h"

Board::Board(QObject *parent) : QObject(parent), m_board(kRows, std::vector<int>(kCols))
{
    connect(&m_snake, &Snake::snakePosChanged, this, &Board::onBoardStateChanged);
    connect(&m_food, &Food::foodPosChanged, this, &Board::onBoardStateChanged);
    connect(&m_timer, &QTimer::timeout, this, &Board::onTimerTimeout);
    connect(this, &Board::gameOver, this, &Board::onGameOver);
}

Snake &Board::getSnake()
{
    return m_snake;
}

void Board::initBoard()
{
    m_snake.initSnake();
    m_food.genFood(kRows, kCols, m_snake.getSnakePos());
    m_timer.start(50);
}

void Board::onBoardStateChanged(int row, int col, int boardState)
{
    m_board[row][col] = boardState;

    switch (boardState) {
        case BoardStates::Unset:
            emit boardStateChanged(row, col, QString::fromStdString(BoardColors::Unset));
        break;
        case BoardStates::SnakeHead:
            emit boardStateChanged(row, col, QString::fromStdString(BoardColors::SnakeHead));
        break;
        case BoardStates::SnakeBody:
            emit boardStateChanged(row, col, QString::fromStdString(BoardColors::SnakeBody));
        break;
        case BoardStates::SnakeTail:
            emit boardStateChanged(row, col, QString::fromStdString(BoardColors::SnakeTail));
        break;
        case BoardStates::Food:
            emit boardStateChanged(row, col, QString::fromStdString(BoardColors::Food));
        break;
    default:
        break;
    }
}

void Board::onTimerTimeout()
{
    const std::list<std::pair<int, int> > &snakePos = m_snake.getSnakePos();
    if (m_shortestPath.empty()) {
        m_shortestPath = AStarAlgo::instance().calculateShortestPath(m_board, snakePos, m_food.getFoodPos());
    }
    else {
        int nextPos = m_shortestPath.top().first * kCols + m_shortestPath.top().second;
        int foodPos = m_food.getFoodPos().first * kCols + m_food.getFoodPos().second;
        if (nextPos == foodPos) {
            m_snake.growSnake(m_shortestPath.top());
            m_shortestPath.pop();
            if (!m_food.genFood(kRows, kCols, snakePos))
                emit gameOver();
        }
        else {
            m_snake.moveSnake(m_shortestPath.top());
            m_shortestPath.pop();
        }
    }
}

void Board::onGameOver()
{
    m_timer.stop();
}
