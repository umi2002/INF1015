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

    pair< int, int > whiteKingCoords = WHITE_KING;
    makePiece< King >(whiteKingCoords, true);

    pair< int, int > blackKingCoords = BLACK_KING;
    makePiece< King >(blackKingCoords, false);

    vector< pair< int, int > > whitePawnCoords = WHITE_PAWN;
    for (const pair< int, int >& coordinates : whitePawnCoords)
    {
        makePiece< Pawn >(coordinates, true);
    }

    vector< pair< int, int > > blackPawnCoords = BLACK_PAWN;
    for (const pair< int, int >& coordinates : blackPawnCoords)
    {
        makePiece< Pawn >(coordinates, false);
    }

    vector< pair< int, int > > whiteRookCoords = WHITE_ROOK;
    for (const pair< int, int >& coordinates : whiteRookCoords)
    {
        makePiece< Rook >(coordinates, true);
    }

    vector< pair< int, int > > blackRookCoords = BLACK_ROOK;
    for (const pair< int, int >& coordinates : blackRookCoords)
    {
        makePiece< Rook >(coordinates, false);
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

void Board::removePiece(const std::shared_ptr< Piece >& piece)
{
    auto activePiecesIterator =
        find(activePieces_.begin(), activePieces_.end(), piece);

    if (activePiecesIterator != activePieces_.end())
    {
        activePieces_.erase(activePiecesIterator);
    }

    pair< int, int > coordinates                  = piece->getCoordinates();
    board_[coordinates.first][coordinates.second] = nullptr;
}

void Board::movePiece(shared_ptr< Piece >&   piece,
                      const pair< int, int > coordinates)
{
    const shared_ptr< Piece >& targetPiece =
        board_[coordinates.first][coordinates.second];
    if (targetPiece != nullptr)
    {
        removePiece(targetPiece);
    }

    board_[coordinates.first][coordinates.second] = piece;
    pair< int, int > oldCoords                    = piece->getCoordinates();
    board_[oldCoords.first][oldCoords.second]     = nullptr;
    piece->move(coordinates);
    turn_ = !turn_;
}

const vector< shared_ptr< Piece > >& Board::getActivePieces() const
{
    return activePieces_;
}
