#ifndef A_STAR_ALGO_STATES_H
#define A_STAR_ALGO_STATES_H

#include <tuple>
#include <list>

typedef int PathState;

struct PathStates {
    static const int Shortest = 0;
    static const int Longest = 1;
};

typedef std::tuple<int, int, int> snakeTp; /* steps, totalCost, curPos */
typedef std::tuple<int, int, int, int, std::list<std::pair<int, int>>> tp; /* steps, totalCost, curPos, prevPos, prevSnake */

template <class T>
struct PqShortestComp {
    constexpr bool operator()(
        const T &a,
        const T &b)
        const noexcept
    {
        if (std::get<1>(a) == std::get<1>(b)) {
            return std::get<0>(a) > std::get<0>(b);
        }

        return std::get<1>(a) > std::get<1>(b);
    }
};

template <class T>
struct PqLongestComp {
    constexpr bool operator()(
        const T &a,
        const T &b)
        const noexcept
    {
        if (std::get<1>(a) == std::get<1>(b)) {
            return std::get<0>(a) < std::get<0>(b);
        }

        return std::get<1>(a) < std::get<1>(b);
    }
};

#endif // A_STAR_ALGO_STATES_H
