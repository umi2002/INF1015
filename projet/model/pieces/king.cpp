/**
 * Programme qui implémente le roi d'un jeu d'échecs.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "king.hpp"

#include "../board.hpp"

using std::pair, std::vector, std::shared_ptr, std::make_shared, std::array;

King::King(const pair< int, int >& coordinates, const bool& player) :
    Piece(coordinates, player)
{ }

shared_ptr< Piece > King::clone() const
{
    return make_shared< King >(*this);
}

vector< pair< int, int > > King::getValidMoves(const Board& board) const
{
    using nDirections::TOTAL, directions::KING, iter::range;

    vector< pair< int, int > > validMoves;
    const pair< int, int >     coordinates = getCoordinates();

    const array< pair< int, int >, TOTAL >& directions = KING;

    for (const pair< int, int >& direction : directions)
    {
        const pair< int, int > destination = {
            coordinates.first + direction.first,
            coordinates.second + direction.second};
        if (board.isValidMove(destination, getPlayer()))
        {
            validMoves.push_back(destination);
        }
    }

    return validMoves;
}

const QString King::getName() const
{
    using namespace piece;

    return getPlayer() ? WHITE_KING : BLACK_KING;
}
