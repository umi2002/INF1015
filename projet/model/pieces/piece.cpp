/**
 * Programme qui implémente la classe de base des pièces d'échecs.
 * \file piece.cpp
 * \author Hoang et Ibarissen
 * \date 5 mai 2023
 * Créé le 12 avril 2023
 */

#include "piece.hpp"

#include "../board.hpp"
#include "king.hpp"

using std::pair, std::vector, std::shared_ptr, std::dynamic_pointer_cast;

Piece::Piece(const pair< int, int > coordinates, const bool player) :
    coordinates_(coordinates),
    player_(player)
{ }

pair< int, int > Piece::getCoordinates() const
{
    return coordinates_;
}

bool Piece::getPlayer() const
{
    return player_;
}

void Piece::move(const pair< int, int > coordinates)
{
    this->coordinates_ = coordinates;
}

bool Piece::threatensKing(const Board& board) const
{
    const vector< pair< int, int > > validMoves = getValidMoves(board);
    for (const pair< int, int >& move : validMoves)
    {
        const shared_ptr< King > piece =
            dynamic_pointer_cast< King >(board.getPiece(move));
        if (piece != nullptr)
        {
            return true;
        }
    }
    return false;
}

void Piece::removeSuicideMoves(const Board&                board,
                               vector< pair< int, int > >& validMoves) const
{
    vector< pair< int, int > > validMovesCopy(validMoves);

    for (const pair< int, int >& move : validMoves)
    {
        Board               boardCopy(board);
        shared_ptr< Piece > pieceCopy = clone();
        boardCopy.movePiece(pieceCopy, move);
        if (boardCopy.isCheck(player_))
        {
            auto validMoveIterator =
                find(validMovesCopy.begin(), validMovesCopy.end(), move);
            validMovesCopy.erase(validMoveIterator);
        }
    }
    validMoves = validMovesCopy;
}
