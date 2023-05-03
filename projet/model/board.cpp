/**
 * Programme qui implémente le modèle d'un jeu d'échecs.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "board.hpp"

#include "pieces/bishop.hpp"
#include "pieces/king.hpp"
#include "pieces/knight.hpp"
#include "pieces/pawn.hpp"
#include "pieces/queen.hpp"
#include "pieces/rook.hpp"

using namespace coordinates;
using namespace nDirections;
using namespace nPieces;

using std::shared_ptr, std::vector, std::array, std::pair;

Board::Board()
{
    for (array< shared_ptr< Piece >, board::SIZE >& row : board_)
    {
        for (shared_ptr< Piece >& piece : row)
        {
            piece = nullptr;
        }
    }
}

void Board::addKings()
{
    const array< pair< int, int >, KING >& whiteKingCoords = WHITE_KING;
    for (const pair< int, int >& coordinates : whiteKingCoords)
    {
        makePiece< King >(coordinates, true);
    }

    const array< pair< int, int >, KING >& blackKingCoords = BLACK_KING;
    for (const pair< int, int >& coordinates : blackKingCoords)
    {
        makePiece< King >(coordinates, false);
    }
}

void Board::addQueens()
{
    const array< pair< int, int >, QUEEN >& whiteQueenCoords = WHITE_QUEEN;
    for (const pair< int, int >& coordinates : whiteQueenCoords)
    {
        makePiece< Queen >(coordinates, true);
    }

    const array< pair< int, int >, QUEEN >& blackQueenCoords = BLACK_QUEEN;
    for (const pair< int, int >& coordinates : blackQueenCoords)
    {
        makePiece< Queen >(coordinates, false);
    }
}

void Board::addRooks()
{
    const array< pair< int, int >, ROOK >& whiteRookCoords = WHITE_ROOK;
    for (const pair< int, int >& coordinates : whiteRookCoords)
    {
        makePiece< Rook >(coordinates, true);
    }

    const array< pair< int, int >, ROOK >& blackRookCoords = BLACK_ROOK;
    for (const pair< int, int >& coordinates : blackRookCoords)
    {
        makePiece< Rook >(coordinates, false);
    }
}

void Board::addBishops()
{
    const array< pair< int, int >, BISHOP >& whiteBishopCoords = WHITE_BISHOP;
    for (const pair< int, int >& coordinates : whiteBishopCoords)
    {
        makePiece< Bishop >(coordinates, true);
    }

    const array< pair< int, int >, BISHOP >& blackBishopCoords = BLACK_BISHOP;
    for (const pair< int, int >& coordinates : blackBishopCoords)
    {
        makePiece< Bishop >(coordinates, false);
    }
}

void Board::addKnights()
{
    const array< pair< int, int >, KNIGHT >& whiteKnightCoords = WHITE_KNIGHT;
    for (const pair< int, int >& coordinates : whiteKnightCoords)
    {
        makePiece< Knight >(coordinates, true);
    }

    const array< pair< int, int >, KNIGHT >& blackKnightCoords = BLACK_KNIGHT;
    for (const pair< int, int >& coordinates : blackKnightCoords)
    {
        makePiece< Knight >(coordinates, false);
    }
}

void Board::addPawns()
{
    const array< pair< int, int >, PAWN >& whitePawnCoords = WHITE_PAWN;
    for (const pair< int, int >& coordinates : whitePawnCoords)
    {
        makePiece< Pawn >(coordinates, true);
    }

    const array< pair< int, int >, PAWN >& blackPawnCoords = BLACK_PAWN;
    for (const pair< int, int >& coordinates : blackPawnCoords)
    {
        makePiece< Pawn >(coordinates, false);
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
