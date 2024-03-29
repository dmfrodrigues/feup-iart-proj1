// Copyright (C) 2021 Diogo Rodrigues, Rafael Ribeiro, Bernardo Ferreira
// Distributed under the terms of the GNU General Public License, version 3

#pragma once

#include <vector>
#include <deque>

/**
 * @brief Color of a piece in the gameboard.
 */
typedef unsigned int color_t;

/**
 * @brief Tube of a gameboard.
 */
typedef std::deque<color_t> Tube;

/**
 * @brief Gameboard model.
 *
 * Represents a gameboard configuration, also known as a state.
 *
 * All comparison operators compare the literal gameboards (i.e., they don't check if the two gameboards are different
 * permutations, or if they have the same configurations and only differ in colors).
 */
class GameboardModel {
public:
    /**
     * @brief Move.
     *
     * Describes a possible move.
     * Behaves just as a pair with convenient names, no checks are performed.
     *
     * Comparison operators behave as in a std::pair<size_t, size_t>, where `from` is `first` and `to` is `second`.
     */
    struct Move {
        size_t from;    ///< @brief Tube the piece will be removed from.
        size_t to;      ///< @brief Tube the piece will be placed on.
        /**
         * @brief Construct move.
         *
         * @param fr    From
         * @param to    To
         */
        Move(size_t fr, size_t to);

        bool operator==(const Move &m) const;
        bool operator!=(const Move &m) const;
        bool operator< (const Move &m) const;
        bool operator> (const Move &m) const;
        bool operator<=(const Move &m) const;
        bool operator>=(const Move &m) const;
    };
private:
    size_t nTubes = 0;          ///< @brief Number of tubes.
    size_t tubeH = 0;           ///< @brief Tubes' height.
    std::vector<Tube> tubes;    ///< @brief Tubes.
    size_t nColors = 0;         ///< @brief Number of colors.
    unsigned seed = 0;
public:
    /**
     * @brief Default constructor.
     */
    GameboardModel();

    /**
     * @brief Copy constructor.
     */
    GameboardModel(const GameboardModel& original);

    /**
     * @brief Assign a gameboard to another (copy properties of a gameboard to another).
     * 
     * @param gameboard         Gameboard to copy from
     * @return GameboardModel&  Reference to destination gameboard
     */
    GameboardModel& operator=(const GameboardModel &gameboard);

    /**
     * @brief Construct a new GameboardModel.
     * 
     * @param num_tubes     Number of tubes
     * @param tube_height   Tube height
     */
    GameboardModel(size_t num_tubes, size_t tube_height);

    const Tube& operator[](size_t i) const;                     ///< @see std::vector::operator[] const
    Tube& operator[](size_t i);                                 ///< @see std::vector::operator[]

    const Tube& at(size_t i) const;                             ///< @see std::vector::at(size_t) const
    Tube& at(size_t i);                                         ///< @see std::vector::at(size_t)

    size_t size() const;                                        ///< @see std::vector::size() const

    std::vector<Tube>::iterator begin() noexcept;               ///< @see std::vector::begin()
    std::vector<Tube>::const_iterator begin() const noexcept;   ///< @see std::vector::begin() const
    std::vector<Tube>::iterator end() noexcept;                 ///< @see std::vector::end()
    std::vector<Tube>::const_iterator end() const noexcept;     ///< @see std::vector::end() const

    /**
     * @brief Get tubes' height.
     * 
     * @return size_t Tube height
     */
    size_t tubeHeight() const;

    /**
     * @brief Clear GameboardModel.
     */
    void clear();

    /**
     * @brief Fill a GameboardModel with random pieces.
     * 
     * @param num_colors    Number of colors of pieces to place
     */
    void fillRandom(size_t num_colors, unsigned seed = 0);

    /**
     * @brief Get number of colors of the pieces currently in this gameboard.
     *
     * @return  Number of colors of the pieces in the gameboard
     */
    size_t getNumberOfColors() const;

    /**
     * @brief Check if the top piece of a tube can be moved to the top of
     * another tube.
     * 
     * @param move          Move to be checked
     * @return true         If movement is valid
     * @return false        otherwise
     */
    bool canMove(const Move &move) const;

    /**
     * @brief Check if move can be reversed in this gameboard.
     *
     * @param move          Move to be checked
     * @return true         If move can be reversed
     * @return false        otherwise
     */
    bool canReverseMove(const Move &move) const;

    /**
     * @brief Move piece from one tube to another.
     * 
     * @param move      Move to be executed
     */
    void move(const Move &move);

    /**
     * @brief Reverse a move.
     *
     * @param move      Move to be reversed
     */
    void reverseMove(const Move &move);

    /**
     * @brief Get all possible legal moves from current state
     * 
     * @return std::vector<Move> 
     */
    std::vector<Move> getAllMoves() const;

    /**
     * @brief Get all boards reachable by one move from the current one
     * 
     * @return std::vector<GameboardModel> 
     */
    std::vector<GameboardModel> getAdjacentStates() const;

    /**
     * @brief Check if game is over.
     * 
     * The game is over when each tube is empty, or it is full to its top with
     * pieces of the same color.
     * 
     * @return True if the game is over, false otherwise. 
     */
    bool isGameOver() const;

    bool operator==(const GameboardModel &model) const;
    bool operator!=(const GameboardModel &model) const;
    bool operator< (const GameboardModel &model) const;
    bool operator> (const GameboardModel &model) const;
    bool operator<=(const GameboardModel &model) const;
    bool operator>=(const GameboardModel &model) const;

    unsigned getSeed() const;
};

namespace std {
    /**
     * @brief Hash a tube.
     *
     * Currently implemented as a strong hash (https://stackoverflow.com/a/27216842).
     */
    template <> struct hash<Tube> {
        size_t operator()(const Tube &vec) const;
    };

    /**
     * @brief Hash a gameboard model.
     *
     * Using a possibly quite weak hash.
     */
    template <> struct hash<GameboardModel>{
        size_t operator()(const GameboardModel& model) const;
    };
}
