#include "knight.hpp"

#include "../board.hpp"

using std::pair, std::vector, std::shared_ptr, std::make_shared, std::array;

Knight::Knight(const pair< int, int >& coordinates, const bool& player) :
    Piece(coordinates, player)
{ }

shared_ptr< Piece > Knight::clone() const
{
    return make_shared< Knight >(*this);
}

vector< pair< int, int > > Knight::getValidMoves(const Board& board) const
{
    using nDirections::TOTAL, board::SIZE, iter::range;

    vector< pair< int, int > > validMoves;
    pair< int, int >           coordinates = getCoordinates();

    array< pair< int, int >, TOTAL > directions = {{{1, 2},
                                                    {1, -2},
                                                    {-1, 2},
                                                    {-1, -2},
                                                    {2, 1},
                                                    {2, -1},
                                                    {-2, 1},
                                                    {-2, -1}}};

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
