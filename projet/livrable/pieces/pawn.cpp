#include "pawn.hpp"

#include "../board.hpp"

using std::pair, std::vector, std::shared_ptr, std::make_shared;

Pawn::Pawn(const pair< int, int >& coordinates, const bool& player) :
    Piece(coordinates, player)
{ }

shared_ptr< Piece > Pawn::clone() const
{
    return make_shared< Pawn >(*this);
}

bool Pawn::isStartingPosition() const
{
    return getPlayer()
             ? getCoordinates().first == coordinates::WHITE_PAWN[0].first
             : getCoordinates().first == coordinates::BLACK_PAWN[0].first;
}

vector< pair< int, int > > Pawn::getValidMoves(const Board& board) const
{
    vector< pair< int, int > > validMoves;
    pair< int, int >           coordinates = getCoordinates();

    bool player    = getPlayer();
    int  direction = player ? -1 : 1;

    if (isStartingPosition())
    {
        pair< int, int > destination  = {coordinates.first + 2 * direction,
                                         coordinates.second};
        pair< int, int > intermediate = {coordinates.first + direction,
                                         coordinates.second};
        if (!board.isOccupied(destination) && !board.isOccupied(intermediate))
        {
            validMoves.push_back(destination);
        }
    }

    for (int i : iter::range(-1, 2))
    {
        pair< int, int > destination = {coordinates.first + direction,
                                        coordinates.second + i};
        if (board.isOutOfBounds(destination))
        {
            continue;
        }

        if (destination.second == coordinates.second)
        {
            if (!board.isOccupied(destination))
            {
                validMoves.push_back(destination);
            }
        }
        else
        {
            if (board.isOccupied(destination)
                && board.isEnemy(destination, player))
            {
                validMoves.push_back(destination);
            }
        }
    }

    return validMoves;
}

const QString Pawn::getName() const
{
    return getPlayer() ? piece::WHITE_PAWN : piece::BLACK_PAWN;
}
