#include "food.h"

Food::Food(QObject *parent) : QObject(parent),
    rd(), rng(rd())
{

}

bool Food::genFood(int rows, int cols, const std::list<std::pair<int, int>> &unavailPos)
{
    int total = rows * cols;
    std::unordered_set<int> m_availPos;
    m_availPos.reserve(total);
    for (int i = 0; i < total; ++i) {
        m_availPos.insert(i);
    }

    for (const auto &unavail : unavailPos) {
        int pos = unavail.first * cols + unavail.second;
        auto it = m_availPos.find(pos);
        if (it != m_availPos.end())
            m_availPos.erase(it);
    }

    int n = m_availPos.size() - 1;

    if (n == -1) {
        return false;
    }

    int pos = *std::next(m_availPos.begin(), 0);
    if (n > 1) {
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, n);
        int index = dist(rng);
        pos = *std::next(m_availPos.begin(), index);
    }

    int row = pos / cols;
    int col = pos % cols;
    m_food_pos = { row, col };

    emit foodPosChanged(row, col, BoardStates::Food);

    return true;
}

const std::pair<int, int> &Food::getFoodPos()
{
    return m_food_pos;
}
