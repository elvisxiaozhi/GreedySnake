#ifndef A_STAR_ALGO_H
#define A_STAR_ALGO_H

#include "a_star_algo_states.h"

#include <vector>
#include <stack>
#include <list>
#include <unordered_map>
#include <set>

class AStarAlgo
{
public:
    static AStarAlgo &instance();

    AStarAlgo(AStarAlgo const&) = delete;
    AStarAlgo(AStarAlgo&&) = delete;
    AStarAlgo& operator=(AStarAlgo const&) = delete;
    AStarAlgo& operator=(AStarAlgo &&) = delete;

    std::stack<std::pair<int, int>> calculateShortestPath(const std::vector<std::vector<int>> &board, const std::list<std::pair<int, int>> &snakePos, const std::pair<int, int> &end);

protected:
    AStarAlgo() = default;
    ~AStarAlgo() = default;

    int calculateDistance(const std::pair<int, int> &start, const std::pair<int, int> &end);
    inline bool isValidPos(int row, int col, int rows, int cols);
    std::vector<std::pair<int, int>> findSurroundings(const std::set<int> &visitedPos, const std::pair<int, int> &pos, int rows, int cols);
    std::stack<std::pair<int, int>> calculateShortestPath(std::stack<std::pair<int, int>> &visitedSt, int cols);
    void calculatePath(PathState pathState, const std::vector<std::vector<int>> &board, const std::list<std::pair<int, int>> &snakePos, const std::pair<int, int> &end);
    bool canFind(const std::vector<std::vector<int>> &board, const std::list<std::pair<int, int>> &snakePos, const std::pair<int, int> &end,
                 std::stack<std::pair<int, int>> *path = nullptr, std::list<std::pair<int, int>> *virtualSnakePos = nullptr);
    bool canFindSnakeTail(const std::vector<std::vector<int>> &board, const std::list<std::pair<int, int>> &snakePos);
    std::stack<std::pair<int, int>> calculateLongestPath(const std::vector<std::vector<int>> &board, const std::list<std::pair<int, int>> &snakePos, const std::pair<int, int> &end);
};

#endif // A_STAR_ALGO_H
