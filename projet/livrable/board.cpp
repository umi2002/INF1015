#include "board.hpp"

#include "pieces/king.hpp"
#include "pieces/pawn.hpp"
#include "pieces/rook.hpp"

using std::shared_ptr, std::vector, std::array, std::pair, std::make_shared;

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

    shared_ptr< Piece > piece;

    pair< int, int > whiteKingCoords = WHITE_KING_COORDS;
    piece = make_shared< King >(whiteKingCoords, true);
    board_[whiteKingCoords.first][whiteKingCoords.second] = piece;
    activePieces_.push_back(piece);

    pair< int, int > blackKingCoords = BLACK_KING_COORDS;
    piece = make_shared< King >(blackKingCoords, false);
    board_[blackKingCoords.first][blackKingCoords.second] = piece;
    activePieces_.push_back(piece);

    vector< pair< int, int > > whitePawnCoords = WHITE_PAWN_COORDS;
    for (pair< int, int >& coord : whitePawnCoords)
    {
        piece                             = make_shared< Pawn >(coord, true);
        board_[coord.first][coord.second] = piece;
        activePieces_.push_back(piece);
    }

    vector< pair< int, int > > blackPawnCoords = BLACK_PAWN_COORDS;
    for (pair< int, int >& coord : blackPawnCoords)
    {
        piece                             = make_shared< Pawn >(coord, false);
        board_[coord.first][coord.second] = piece;
        activePieces_.push_back(piece);
    }

    vector< pair< int, int > > whiteRookCoords = WHITE_ROOK_COORDS;
    for (pair< int, int >& coord : whiteRookCoords)
    {
        piece                             = make_shared< Rook >(coord, true);
        board_[coord.first][coord.second] = piece;
        activePieces_.push_back(piece);
    }

    vector< pair< int, int > > blackRookCoords = BLACK_ROOK_COORDS;
    for (pair< int, int >& coord : blackRookCoords)
    {
        piece                             = make_shared< Rook >(coord, false);
        board_[coord.first][coord.second] = piece;
        activePieces_.push_back(piece);
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
