// Copyright (C) 2021 Diogo Rodrigues, Rafael Ribeiro, Bernardo Ferreira
// Distributed under the terms of the GNU General Public License, version 3

#include "model/GameboardModel.h"

#include <stdexcept>
#include <algorithm>

using namespace std;
using Move = GameboardModel::Move;

GameboardModel::Move::Move(size_t f, size_t t):from(f), to(t) {
}

bool GameboardModel::Move::operator==(const Move &m) const { return from == m.from && to == m.to; }
bool GameboardModel::Move::operator!=(const Move &m) const { return !(*this == m); }
bool GameboardModel::Move::operator< (const GameboardModel::Move &m) const {
    if(from != m.from) return (from < m.from);
    return (to < m.to);
}
bool GameboardModel::Move::operator> (const GameboardModel::Move &m) const { return (m < *this); }
bool GameboardModel::Move::operator<=(const GameboardModel::Move &m) const { return !(m > *this); }
bool GameboardModel::Move::operator>=(const GameboardModel::Move &m) const { return !(m < *this); }

GameboardModel::GameboardModel():
        nTubes(0),
        tubeH(0),
        nColors(0)
{
}

GameboardModel::GameboardModel(const GameboardModel& original) = default;

GameboardModel &GameboardModel::operator=(const GameboardModel &gameboard) = default;

GameboardModel::GameboardModel(size_t num_tubes, size_t tube_height):
        nTubes(num_tubes),
        tubeH(tube_height),
        tubes(num_tubes)
{
}

const Tube &GameboardModel::operator[](size_t i) const { return tubes[i]; }
Tube &GameboardModel::operator[](size_t i) { return tubes[i]; }

const Tube &GameboardModel::at(size_t i) const { return tubes.at(i); }
Tube &GameboardModel::at(size_t i) { return tubes.at(i); }

size_t GameboardModel::size() const { return tubes.size(); }

vector<Tube>::iterator       GameboardModel::begin()       noexcept { return tubes.begin(); }
vector<Tube>::const_iterator GameboardModel::begin() const noexcept { return tubes.begin(); }
vector<Tube>::iterator       GameboardModel::end  ()       noexcept { return tubes.end(); }
vector<Tube>::const_iterator GameboardModel::end  () const noexcept { return tubes.end(); }

size_t GameboardModel::tubeHeight() const{ return tubeH; }

void GameboardModel::clear(){
    for(size_t i = 0; i < nTubes; ++i){
        (*this)[i] = deque<color_t>();
    }
}

void GameboardModel::fillRandom(size_t num_colors, unsigned sd){
    this->seed = sd;
    srand(sd);
    size_t num_pieces = num_colors * tubeH;
    // There must be at least as many tubes as there are colors, since each
    // color will be in a separate tube.
    if(num_colors > nTubes) throw invalid_argument("more colors (" + to_string(num_colors) + ") than tubes (" + to_string(nTubes) + ")");

    // There must be enough tubes to contain all pieces.
    if(num_pieces > nTubes * tubeH) throw invalid_argument("too many pieces");

    // There must be at least one piece of each color, otherwise one of the
    // colors would have 0 pieces, in which case it should be included as a
    // color.
    if(num_pieces < num_colors) throw invalid_argument("num_pieces < num_colors");
    vector<size_t> num_pieces_per_color(num_colors, 1);
    num_pieces -= num_colors;

    // Distribute remaining pieces to the colors.
    for(size_t i = 0; i < num_pieces; ++i){
        color_t color;
        do {
            // Select random color.
            color = color_t(static_cast<unsigned long>(rand()) % num_colors);

            // Keep trying until a color is found that has not yet been
            // allocated the maximum number of pieces per color.
        } while(num_pieces_per_color[color] >= tubeH);

        ++num_pieces_per_color[color];
    }

    clear();
    // Distribute colored pieces through the tubes.
    for(size_t i = 0; i < num_colors; ++i){
        while(num_pieces_per_color[i] > 0){
            // Search for tube that is not yet on maximum capacity.
            size_t tube;
            do {
                tube = static_cast<unsigned long>(rand()) % nTubes;
            } while((*this)[tube].size() >= tubeH);
            (*this)[tube].push_back(color_t(i));
            --num_pieces_per_color[i];
        }
    }

    nColors = num_colors;
}

size_t GameboardModel::getNumberOfColors() const {
    return nColors;
}

bool GameboardModel::canMove(const Move &move) const {
    if (move.from == move.to) return false;
    if (move.from >= this->nTubes || move.to >= this->nTubes ) return false;

    const Tube &tube_origin      = this->at(move.from);
    const Tube &tube_destination = this->at(move.to  );

    return (
        // Origin is not empty
        !tube_origin.empty() &&
        // Destination is not full
        tube_destination.size() < tubeH &&
        (
            // Destination is empty; or
            tube_destination.empty() ||
            // Destination top is same color as origin top
            tube_origin.back() == tube_destination.back()
        )
    );
}

bool GameboardModel::canReverseMove(const Move &move) const {
    const Tube &tube_destination = this->at(move.to  );

    return (
        // Destination only has a piece; or
        tube_destination.size() == 1 ||
        // The two pieces at the top have the same color
        *tube_destination.rbegin() == *(tube_destination.rbegin()+1)
    );
}

void GameboardModel::move(const Move &move) {
//    if(!canMove(move)) throw invalid_argument("");

    Tube &tube_origin      = this->at(move.from);
    Tube &tube_destination = this->at(move.to  );

    color_t c = tube_origin.back();
    tube_origin.pop_back();
    tube_destination.push_back(c);
}

void GameboardModel::reverseMove(const Move &move) {
//    if(!canReverseMove(move)) throw invalid_argument("");

    Tube &tube_origin      = this->at(move.from);
    Tube &tube_destination = this->at(move.to  );

    color_t c = tube_destination.back();
    tube_destination.pop_back();
    tube_origin.push_back(c);
}

vector<Move> GameboardModel::getAllMoves() const {
    vector<Move> result;

    if (this->size() < 2) return result;

    for (size_t i = 0 ; i < this->size() ; i++){
        for (size_t j = 0 ; j < this->size() ; j++){
            if(i == j) continue;
            Move m(i, j);
            if (canMove(m)) result.push_back(m);
        }
    }

    return result;
}

vector<GameboardModel> GameboardModel::getAdjacentStates() const {
    vector<GameboardModel> result;

    vector<Move> moves = getAllMoves();
    for (const Move &move : moves){
        GameboardModel newGameboard = GameboardModel(*this);
        if (newGameboard.canMove(move)) newGameboard.move(move);
        result.push_back(newGameboard);
    }

    return result;
}
/**
 * Checks if all elements of a vector are equal to each other.
 *
 * Returns true if all adjacent elements are equal to each other, or if the vector has less than 2 elements.
 *
 * Returns false if there is at least one adjacent pair of different elements.
 *
 * @tparam T
 * @param v Vector
 * @return  False if at least one pair of adjacent elements are different, true otherwise
 */
template<class T>
bool checkAllEqual(const deque<T> &v){
    return adjacent_find(v.begin(), v.end(), not_equal_to<>()) == v.end();
}

bool GameboardModel::isGameOver() const {
    for(size_t i = 0; i < size(); ++i){
        size_t s = this->at(i).size();
        if(!(s == 0 || s == tubeHeight())) return false;
        if(!checkAllEqual(this->at(i))) return false;
    }
    return true;
}

bool GameboardModel::operator==(const GameboardModel &model) const {
    /*
    GameboardModel this_sorted = *this;
    sort(this_sorted.begin(), this_sorted.end());
    GameboardModel model_sorted = model;
    sort(model_sorted.begin(), model_sorted.end());
    return static_cast<vector<Tube>>(this_sorted) == static_cast<vector<Tube>>(model_sorted);
     */
    return tubes == model.tubes;
}
bool GameboardModel::operator!=(const GameboardModel &model) const { return !(*this == model); }

bool GameboardModel::operator<(const GameboardModel &model) const {
    /*
    GameboardModel this_sorted = *this;
    sort(this_sorted.begin(), this_sorted.end());
    GameboardModel model_sorted = model;
    sort(model_sorted.begin(), model_sorted.end());
    return static_cast<vector<Tube>>(this_sorted) < static_cast<vector<Tube>>(model_sorted);
     */
    return tubes < model.tubes;
}

bool GameboardModel::operator> (const GameboardModel &model) const { return model < *this; }
bool GameboardModel::operator<=(const GameboardModel &model) const { return !(*this > model); }
bool GameboardModel::operator>=(const GameboardModel &model) const { return !(*this < model); }

unsigned GameboardModel::getSeed() const {
    return seed;
}

size_t std::hash<Tube>::operator()(const Tube &vec) const {
    size_t seed = vec.size();
    for (auto &i : vec) {
        seed ^= hash<color_t>()(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

// TODO
size_t hash<GameboardModel>::operator()(const GameboardModel& model) const {
    GameboardModel model_sorted = model;
    /*
    std::sort(model_sorted.begin(), model_sorted.end());
     */
    size_t seed = model_sorted.size();
    for(const Tube &t: model_sorted){
        seed = (seed << 1) ^ hash<Tube>()(t);
    }
    return seed;
}
