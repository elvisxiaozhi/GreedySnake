#ifndef BOARD_DIRECTIONS_H
#define BOARD_DIRECTIONS_H

#include <map>

struct BoardDirections {
    static constexpr std::pair<int, int> Up = { -1, 0 };
    static constexpr std::pair<int, int> Down = { 1, 0 };
    static constexpr std::pair<int, int> Left = { 0, -1 };
    static constexpr std::pair<int, int> Right = { 0, 1 };

    static const int Even = 0;
    static const int Odd = 1;
    static const int Divisor = 2;

    static const int OddRow;
    static const int EvenRow;
    static const int OddCol;
    static const int EvenCol;

    static const std::map<int, std::pair<int, int>> Directions;
};

const int BoardDirections::OddRow = 0;
const int BoardDirections::EvenRow = 1;
const int BoardDirections::OddCol = 2;
const int BoardDirections::EvenCol = 3;

const std::map<int, std::pair<int, int>> BoardDirections::Directions = {
    { BoardDirections::OddCol, Up },
    { BoardDirections::EvenCol, BoardDirections::Down },
    { BoardDirections::EvenRow, BoardDirections::Left },
    { BoardDirections::OddRow, BoardDirections::Right },
};

#endif // BOARD_DIRECTIONS_H
