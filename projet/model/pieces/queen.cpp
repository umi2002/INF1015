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
    using nDirections::TOTAL, board::SIZE, iter::range;

    vector< pair< int, int > > validMoves;
    pair< int, int >           coordinates = getCoordinates();

    array< pair< int, int >, TOTAL > directions = {
        {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}}};

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
