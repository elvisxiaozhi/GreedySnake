#ifndef BOARD_COLORS_H
#define BOARD_COLORS_H

#include <string>

struct BoardColors {
    static const std::string Unset;
    static const std::string SnakeHead;
    static const std::string SnakeBody;
    static const std::string SnakeTail;
    static const std::string Food;
};

const std::string BoardColors::Unset = "grey";
const std::string BoardColors::SnakeHead = "red";
const std::string BoardColors::SnakeBody = "green";
const std::string BoardColors::SnakeTail = "black";
const std::string BoardColors::Food = "yellow";

#endif // BOARD_COLORS_H
