/**
 * Programme qui implémente le modèle d'un jeu d'échecs.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "board.hpp"

#include "pieces/king.hpp"
#include "pieces/pawn.hpp"
#include "pieces/rook.hpp"

using std::shared_ptr, std::vector, std::array, std::pair;

Board::Board()
{
    using namespace coordinates;

    for (array< shared_ptr< Piece >, board::SIZE >& row : board_)
    {
        for (shared_ptr< Piece >& piece : row)
        {
            piece = nullptr;
        }
    }

    pair< int, int > whiteKingCoords = WHITE_KING_COORDS;
    makePiece< King >(whiteKingCoords, true);

    pair< int, int > blackKingCoords = BLACK_KING_COORDS;
    makePiece< King >(blackKingCoords, false);

    vector< pair< int, int > > whitePawnCoords = WHITE_PAWN_COORDS;
    for (const pair< int, int >& coord : whitePawnCoords)
    {
        makePiece< Pawn >(coord, true);
    }

    vector< pair< int, int > > blackPawnCoords = BLACK_PAWN_COORDS;
    for (const pair< int, int >& coord : blackPawnCoords)
    {
        makePiece< Pawn >(coord, false);
    }

    vector< pair< int, int > > whiteRookCoords = WHITE_ROOK_COORDS;
    for (const pair< int, int >& coord : whiteRookCoords)
    {
        makePiece< Rook >(coord, true);
    }

    vector< pair< int, int > > blackRookCoords = BLACK_ROOK_COORDS;
    for (const pair< int, int >& coord : blackRookCoords)
    {
        makePiece< Rook >(coord, false);
    }
}

Board::~Board() { }

bool Board::isTurn(bool player) const
{
    return turn_ == player;
}

bool Board::isOutOfBounds(const pair< int, int > coordinates) const
{
    return coordinates.first < 0 || coordinates.first >= board::SIZE
        || coordinates.second < 0 || coordinates.second >= board::SIZE;
}

bool Board::isOccupied(const pair< int, int > coordinates) const
{
    return board_[coordinates.first][coordinates.second] != nullptr;
}

bool Board::isEnemy(const pair< int, int > coordinates, bool player) const
{
    return board_[coordinates.first][coordinates.second]->getPlayer() != player;
}

bool Board::isValidMove(const pair< int, int > coordinates, bool player) const
{
    if (isOutOfBounds(coordinates))
    {
        return false;
    }
    if (isOccupied(coordinates))
    {
        return isEnemy(coordinates, player);
    }
    return true;
}

bool Board::isCheck(bool player) const
{
    for (const shared_ptr< Piece >& piece : activePieces_)
    {

        if (piece->getPlayer() == player)
        {
            continue;
        }

        if (piece->threatensKing(*this))
        {
            return true;
        }
    }

    return false;
}

const shared_ptr< Piece >&
Board::getPiece(const pair< int, int > coordinates) const
{
    return board_[coordinates.first][coordinates.second];
}

void Board::movePiece(shared_ptr< Piece >&   piece,
                      const pair< int, int > coordinates)
{
    const shared_ptr< Piece >& targetPiece =
        board_[coordinates.first][coordinates.second];
    auto activePiecesIterator =
        find(activePieces_.begin(), activePieces_.end(), targetPiece);

    if (activePiecesIterator != activePieces_.end())
    {
        activePieces_.erase(activePiecesIterator);
    }

    board_[coordinates.first][coordinates.second] = piece;
    pair< int, int > oldCoords                    = piece->getCoordinates();
    board_[oldCoords.first][oldCoords.second]     = nullptr;
    piece->move(coordinates);
    turn_ = !turn_;
}
