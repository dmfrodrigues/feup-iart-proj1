#pragma once

#include <queue>
#include <stack>
#include <set>
#include <map>
#include "model/GameboardModel.h"
#include "algorithm/SearchStrategy.h"

/**
 * @brief Breadth-first Search
 * 
 * Keep track of visited nodes (nodes added to the path so far) so as to avoid cycles
 * 
 */
class BreadthFirstSearch : public SearchStrategy {
private:
    std::stack<GameboardModel::Move> solution;
    GameboardModel initialState;
    GameboardModel finalState;
    std::map<GameboardModel, GameboardModel::Move> prev;
    bool bfs(const GameboardModel& GameboardModel);
public:
    void initialize(const GameboardModel &gameboard) override;
    GameboardModel::Move next() override;
};
