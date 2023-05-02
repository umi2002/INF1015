/**
 * Programme qui implémente la tour d'un jeu d'échecs.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "rook.hpp"

#include "../board.hpp"

using std::pair, std::vector, std::shared_ptr, std::make_shared, std::array;

Rook::Rook(const pair< int, int >& coordinates, const bool& player) :
    Piece(coordinates, player)
{ }

shared_ptr< Piece > Rook::clone() const
{
    return make_shared< Rook >(*this);
}

vector< pair< int, int > > Rook::getValidMoves(const Board& board) const
{
    using nDirections::STRAIGHT, board::SIZE, iter::range;

    vector< pair< int, int > > validMoves;
    pair< int, int >           coordinates = getCoordinates();

    array< pair< int, int >, STRAIGHT > directions = {
        {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};

    for (pair< int, int > direction : directions)
    {
        for (int i : range(1, SIZE))
        {
            const pair< int, int > destination = {
                coordinates.first + i * direction.first,
                coordinates.second + i * direction.second};
            if (!board.isValidMove(destination, getPlayer()))
            {
                break;
            }

            validMoves.push_back(destination);

            if (board.isOccupied(destination))
            {
                break;
            }
        }
    }

    return validMoves;
}

const QString Rook::getName() const
{
    using namespace piece;

    return getPlayer() ? WHITE_ROOK : BLACK_ROOK;
}
