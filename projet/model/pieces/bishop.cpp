/**
 * Programme qui impl�mente le fou d'un jeu d'�chec.
 * \file bishop.cpp
 * \author Hoang et Ibarissen
 * \date 5 mai 2023
 * Cr�� le 12 avril 2023
 */

#include "bishop.hpp"

#include "../board.hpp"

using std::pair, std::vector, std::shared_ptr, std::make_shared, std::array;

Bishop::Bishop(const pair< int, int >& coordinates, const bool& player) :
    Piece(coordinates, player)
{ }

shared_ptr< Piece > Bishop::clone() const
{
    return make_shared< Bishop >(*this);
}

vector< pair< int, int > > Bishop::getValidMoves(const Board& board) const
{
    using nDirections::DIAGONAL, directions::BISHOP, board::SIZE, iter::range;

    vector< pair< int, int > > validMoves;
    pair< int, int >           coordinates = getCoordinates();

    const array< pair< int, int >, DIAGONAL >& directions = BISHOP;

    for (const pair< int, int >& direction : directions)
    {
        for (const int& i : range(1, SIZE))
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

const QString Bishop::getName() const
{
    using namespace piece;

    return getPlayer() ? WHITE_BISHOP : BLACK_BISHOP;
}
