// Copyright (C) 2021 Diogo Rodrigues, Rafael Ribeiro, Bernardo Ferreira
// Distributed under the terms of the GNU General Public License, version 3

#pragma once

#include "model/GameboardModel.h"
#include "algorithm/SearchStrategy.h"

#include <bits/stdc++.h>
#include <deque>
#include <unordered_set>

class IterativeDeepeningSearch : public SearchStrategy {
private:
    std::deque<GameboardModel::Move> solution;
    std::unordered_set<GameboardModel> visited;
    size_t currentDepth = 0;
public:
    bool dfs(const GameboardModel& gameBoard, size_t depth);

    void initialize(const GameboardModel &gameboardModel) override;
    GameboardModel::Move next() override;
};