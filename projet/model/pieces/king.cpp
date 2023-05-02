/**
 * Programme qui implémente le roi d'un jeu d'échecs.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "king.hpp"

#include "../board.hpp"

using std::pair, std::vector, std::shared_ptr, std::make_shared;

King::King(const pair< int, int >& coordinates, const bool& player) :
    Piece(coordinates, player)
{
    if (count_ > 1)
    {
        throw std::runtime_error("Too many kings");
    }

    ++count_;
}

King::~King()
{
    --count_;
}

shared_ptr< Piece > King::clone() const
{
    return make_shared< King >(*this);
}

vector< std::pair< int, int > > King::getValidMoves(const Board& board) const
{
    vector< std::pair< int, int > > validMoves;
    const pair< int, int >          coordinates = getCoordinates();

    for (int i : iter::range(-1, 2))
    {
        for (int j : iter::range(-1, 2))
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            pair< int, int > destination = {coordinates.first + i,
                                            coordinates.second + j};
            if (board.isValidMove(destination, getPlayer()))
            {
                validMoves.push_back(destination);
            }
        }
    }

    return validMoves;
}

const QString King::getName() const
{
    using namespace piece;

    return getPlayer() ? WHITE_KING : BLACK_KING;
}

int King::getCount()
{
    return count_;
}

int King::count_ = 0;
