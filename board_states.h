#ifndef BOARD_STATES_H
#define BOARD_STATES_H

struct BoardStates {
    static const int Unset = 0;
    static const int SnakeHead = 1;
    static const int SnakeBody = 2;
    static const int SnakeTail = 3;
    static const int Food = 4;
};

#endif // BOARD_STATES_H
