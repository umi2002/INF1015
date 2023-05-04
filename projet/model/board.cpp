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

using std::shared_ptr, std::vector, std::pair, std::istringstream;

Board::Board(std::string simplifiedFEN)
{
    using std::isdigit, iter::range, board::SIZE;

    istringstream fenStream(simplifiedFEN);
    int           row = 0;
    int           col = 0;
    char          c;

    while (fenStream.get(c) && c != ' ')
    {
        if (isdigit(c))
        {
            int nEmptySquares = c - '0';
            for (int i : range(col, col + nEmptySquares))
            {
                board_[row][i] = nullptr;
            }
            col += nEmptySquares;
        }
        else if (c == '/')
        {
            row++;
            col = 0;
        }
        else
        {
            pair< int, int > coordinates = {row, col++};
            bool             player      = isupper(c);
            c                            = tolower(c);

            switch (c)
            {
                case 'p' :
                    makePiece< Pawn >(coordinates, player);
                    break;
                case 'n' :
                    makePiece< Knight >(coordinates, player);
                    break;
                case 'b' :
                    makePiece< Bishop >(coordinates, player);
                    break;
                case 'r' :
                    makePiece< Rook >(coordinates, player);
                    break;
                case 'q' :
                    makePiece< Queen >(coordinates, player);
                    break;
                case 'k' :
                    makePiece< King >(coordinates, player);
                    break;
                default :
                    break;
            }
        }
    }

    char turn;
    fenStream >> turn;
    turn_ = turn == 'w';
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
