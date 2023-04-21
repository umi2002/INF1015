#include "king.hpp"

#include "../board.hpp"

using std::pair, std::vector, std::shared_ptr, std::make_shared;

King::King(const pair< int, int >& coordinates, const bool& player) :
    Piece(coordinates, player)
{ }

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
    return getPlayer() ? piece::WHITE_KING : piece::BLACK_KING;
}
