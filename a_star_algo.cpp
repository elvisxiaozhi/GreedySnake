#include "a_star_algo.h"
#include "board_states.h"
#include "board_directions.h"
#include <cmath>
#include <queue>
#include <set>

AStarAlgo &AStarAlgo::instance()
{
    static AStarAlgo instance;

    return instance;
}

std::stack<std::pair<int, int>> AStarAlgo::calculateShortestPath(const std::vector<std::vector<int>> &board, const std::list<std::pair<int, int>> &snakePos, const std::pair<int, int> &end)
{
    std::stack<std::pair<int, int>> path;
    std::list<std::pair<int, int>> virtualSnakePos;
    // check if a shortest path to eat food can be found
    if (canFind(board, snakePos, end, &path, &virtualSnakePos)) {
        /* if a shortest path to eat food is found
         * check if snake tail can be found after eating its food */

        /* if snake tail can still be found
         *  go eat food */
        if (!canFindSnakeTail(board, virtualSnakePos)) {
            path = std::stack<std::pair<int, int>>();
            path.push(calculateLongestPath(board, snakePos, end).top());
        }
    }
    else {
        path.push(calculateLongestPath(board, snakePos, end).top());
    }

    return path;
}

int AStarAlgo::calculateDistance(const std::pair<int, int> &start, const std::pair<int, int> &end)
{
    int x = std::abs(start.first - end.first);
    int y = std::abs(start.second - end.second);
    double distance = std::hypot(x, y);

    return std::round(distance);
}

bool AStarAlgo::isValidPos(int row, int col, int rows, int cols)
{
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

std::vector<std::pair<int, int>> AStarAlgo::findSurroundings(const std::set<int> &visitedPos, const std::pair<int, int> &pos, int rows, int cols)
{
    std::vector<std::pair<int, int>> surroundings;

    std::map<int, std::pair<int, int>>::const_iterator it;
    if (pos.first % BoardDirections::Divisor == BoardDirections::Odd) {
        it = BoardDirections::Directions.find(BoardDirections::OddRow);
    }
    else {
        it = BoardDirections::Directions.find(BoardDirections::EvenRow);
    }

    int row = pos.first + it->second.first;
    int col = pos.second + it->second.second;

    if (isValidPos(row, col, rows, cols) && !visitedPos.count(row * cols + col)) {
        surroundings.emplace_back(std::make_pair(row, col));
    }

    if (pos.second % BoardDirections::Divisor == BoardDirections::Odd) {
        it = BoardDirections::Directions.find(BoardDirections::OddCol);
    }
    else {
        it = BoardDirections::Directions.find(BoardDirections::EvenCol);
    }

    row = pos.first + it->second.first;
    col = pos.second + it->second.second;

    if (isValidPos(row, col, rows, cols) && !visitedPos.count(row * cols + col)) {
        surroundings.emplace_back(std::make_pair(row, col));
    }

    return surroundings;
}

std::stack<std::pair<int, int>> AStarAlgo::calculateShortestPath(std::stack<std::pair<int, int>> &visitedSt, int cols)
{
    std::stack<std::pair<int, int>> shortestPath;
    int prevPos = visitedSt.top().first;

    while (!visitedSt.empty()) {
        if (prevPos == visitedSt.top().first) {
            prevPos = visitedSt.top().second;
            int row = visitedSt.top().first / cols;
            int col = visitedSt.top().first % cols;
            shortestPath.push({ row, col });
        }

        visitedSt.pop();
    }

    return shortestPath;
}

bool AStarAlgo::canFind(const std::vector<std::vector<int> > &board, const std::list<std::pair<int, int> > &snakePos, const std::pair<int, int> &end,
                        std::stack<std::pair<int, int> > *path, std::list<std::pair<int, int>> *virtualSnakePos)
{
    std::stack<std::pair<int, int>> visitedSt;
    std::set<int> visitedPos;
    std::priority_queue<tp, std::vector<tp>, PqShortestComp<tp>> pq;

    int startPos = snakePos.front().first * board[0].size() + snakePos.front().second;
    int endPos = end.first * board[0].size() + end.second;
    for (const auto &it : snakePos)
        visitedPos.insert(it.first * board[0].size() + it.second);
    visitedPos.erase(startPos);
    pq.push({ 0, calculateDistance(snakePos.front(), end), startPos, -1, snakePos });

    while (!pq.empty()) {
        int prevSteps = std::get<0>(pq.top());
        int curPos = std::get<2>(pq.top());
        int prevPos = std::get<3>(pq.top());
        std::list<std::pair<int, int>> prevSnake = std::get<4>(pq.top());
        pq.pop();

        if (curPos == endPos) {
            visitedSt.push({ curPos, prevPos });

            *path = calculateShortestPath(visitedSt, board[0].size());
            *virtualSnakePos = prevSnake;
            virtualSnakePos->emplace_front(std::make_pair(curPos / board[0].size(), curPos % board[0].size()));

            return true;
        }

        if (visitedPos.count(curPos))
            continue;

        std::pair<int, int> snakeHead = { curPos / board[0].size(), curPos % board[0].size() };
        if (curPos != startPos && curPos != endPos) {
            prevSnake.emplace_front(snakeHead);
            visitedPos.erase(prevSnake.back().first * board[0].size() + prevSnake.back().second);
            prevSnake.pop_back();
            visitedSt.push({ curPos, prevPos });
        }

        const std::vector<std::pair<int, int> > &surroundings = findSurroundings(visitedPos, snakeHead, board.size(), board[0].size());
        for (const auto &surrounding : surroundings) {
            int steps = prevSteps + 1;
            int newCurPos = surrounding.first * board[0].size() + surrounding.second;
            tp element = { steps, steps + calculateDistance(surrounding, end), newCurPos, curPos, prevSnake };
            pq.push(element);
        }

        visitedPos.insert(curPos);
    }

    return false;
}

bool AStarAlgo::canFindSnakeTail(const std::vector<std::vector<int> > &board, const std::list<std::pair<int, int> > &snakePos)
{
    std::set<int> visitedPos;
    std::priority_queue<snakeTp, std::vector<snakeTp>, PqShortestComp<snakeTp>> pq;

    int startPos = snakePos.front().first * board[0].size() + snakePos.front().second;
    int endPos = snakePos.back().first * board[0].size() + snakePos.back().second;
    for (const auto &it : snakePos)
        visitedPos.insert(it.first * board[0].size() + it.second);
    visitedPos.erase(startPos);
    visitedPos.erase(endPos);
    pq.push({ 0, calculateDistance(snakePos.front(), snakePos.back()), startPos });

    while (!pq.empty()) {
        int prevSteps = std::get<0>(pq.top());
        int curPos = std::get<2>(pq.top());
        pq.pop();

        if (curPos == endPos) {
            return true;
        }

        if (visitedPos.count(curPos))
            continue;

        std::pair<int, int> snakeHead = { curPos / board[0].size(), curPos % board[0].size() };

        const std::vector<std::pair<int, int> > &surroundings = findSurroundings(visitedPos, snakeHead, board.size(), board[0].size());
        for (const auto &surrounding : surroundings) {
            int steps = prevSteps + 1;
            int newCurPos = surrounding.first * board[0].size() + surrounding.second;
            snakeTp element = { steps, steps + calculateDistance(surrounding, snakePos.back()), newCurPos };
            pq.push(element);
        }

        visitedPos.insert(curPos);
    }

    return false;
}

std::stack<std::pair<int, int>> AStarAlgo::calculateLongestPath(const std::vector<std::vector<int> > &board, const std::list<std::pair<int, int> > &snakePos, const std::pair<int, int> &end)
{
    std::set<int> visitedPos;

    int startPos = snakePos.front().first * board[0].size() + snakePos.front().second;
    for (const auto &it : snakePos)
        visitedPos.insert(it.first * board[0].size() + it.second);
    visitedPos.erase(startPos);

    std::tuple<int, int, int> tp = { std::numeric_limits<int>::min(), 0, 0 };
    const std::vector<std::pair<int, int>> &surroundings = findSurroundings(visitedPos, snakePos.front(), board.size(), board[0].size());
    for (const auto &surrounding : surroundings) {
        int distance = calculateDistance(surrounding, end);
        if (std::get<0>(tp) < distance) {
            tp = { distance, surrounding.first, surrounding.second };
        }
    }

    std::stack<std::pair<int, int>> path;
    path.emplace(std::get<1>(tp), std::get<2>(tp));

    return path;
}
