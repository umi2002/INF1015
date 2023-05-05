/**
 * Programme qui implémente la reine d'un jeu d'échecs.
 * \file queen.cpp
 * \author Hoang et Ibarissen
 * \date 5 mai 2023
 * Créé le 12 avril 2023
 */

#include "queen.hpp"

#include "../board.hpp"

using std::pair, std::vector, std::shared_ptr, std::make_shared, std::array;

Queen::Queen(const pair< int, int >& coordinates, const bool& player) :
    Piece(coordinates, player)
{ }

shared_ptr< Piece > Queen::clone() const
{
    return make_shared< Queen >(*this);
}

vector< pair< int, int > > Queen::getValidMoves(const Board& board) const
{
    using nDirections::TOTAL, directions::QUEEN, board::SIZE, iter::range;

    vector< pair< int, int > > validMoves;
    pair< int, int >           coordinates = getCoordinates();

    const array< pair< int, int >, TOTAL >& directions = QUEEN;

    for (const pair< int, int >& direction : directions)
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

const QString Queen::getName() const
{
    using namespace piece;

    return getPlayer() ? WHITE_QUEEN : BLACK_QUEEN;
}
