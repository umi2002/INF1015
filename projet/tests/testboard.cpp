/**
 * Programme qui permet de tester la classe Board.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "../model/board.hpp"
#include "../model/pieces/bishop.hpp"
#include "../model/pieces/king.hpp"
#include "../model/pieces/knight.hpp"
#include "../model/pieces/pawn.hpp"
#include "../model/pieces/queen.hpp"
#include "../model/pieces/rook.hpp"

#if __has_include("gtest/gtest.h")
#    include "gtest/gtest.h"
#endif
#ifdef TEST

using nPieces::TOTAL, std::shared_ptr, std::pair, std::dynamic_pointer_cast,
    iter::range;

TEST(Board, ActivePieces)
{
    Board board;
    EXPECT_EQ(board.getActivePieces().size(), TOTAL);
}

TEST(Board, WhiteKingCoordinates)
{
    Board                    board;
    pair< int, int >         whiteKingCoords = coordinates::WHITE_KING;
    const shared_ptr< King > whiteKing =
        dynamic_pointer_cast< King >(board.getPiece(whiteKingCoords));
    EXPECT_NE(whiteKing, nullptr);
}

TEST(Board, BlackKingCoordinates)
{
    Board                    board;
    pair< int, int >         blackKingCoords = coordinates::BLACK_KING;
    const shared_ptr< King > blackKing =
        dynamic_pointer_cast< King >(board.getPiece(blackKingCoords));
    EXPECT_NE(blackKing, nullptr);
}

TEST(Board, WhiteQueenCoordinates)
{
    Board                     board;
    pair< int, int >          whiteQueenCoords = coordinates::WHITE_QUEEN;
    const shared_ptr< Queen > whiteQueen =
        dynamic_pointer_cast< Queen >(board.getPiece(whiteQueenCoords));
    EXPECT_NE(whiteQueen, nullptr);
}

TEST(Board, BlackQueenCoordinates)
{
    Board                     board;
    pair< int, int >          blackQueenCoords = coordinates::BLACK_QUEEN;
    const shared_ptr< Queen > blackQueen =
        dynamic_pointer_cast< Queen >(board.getPiece(blackQueenCoords));
    EXPECT_NE(blackQueen, nullptr);
}

TEST(Board, WhiteBishopCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : coordinates::WHITE_BISHOP)
    {
        const shared_ptr< Bishop > bishop =
            dynamic_pointer_cast< Bishop >(board.getPiece(coord));
        EXPECT_NE(bishop, nullptr);
    }
}

TEST(Board, BlackBishopCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : coordinates::BLACK_BISHOP)
    {
        const shared_ptr< Bishop > bishop =
            dynamic_pointer_cast< Bishop >(board.getPiece(coord));
        EXPECT_NE(bishop, nullptr);
    }
}

TEST(Board, WhiteKnightCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : coordinates::WHITE_KNIGHT)
    {
        const shared_ptr< Knight > knight =
            dynamic_pointer_cast< Knight >(board.getPiece(coord));
        EXPECT_NE(knight, nullptr);
    }
}

TEST(Board, BlackKnightCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : coordinates::BLACK_KNIGHT)
    {
        const shared_ptr< Knight > knight =
            dynamic_pointer_cast< Knight >(board.getPiece(coord));
        EXPECT_NE(knight, nullptr);
    }
}

TEST(Board, WhiteRookCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : coordinates::WHITE_ROOK)
    {
        const shared_ptr< Rook > rook =
            dynamic_pointer_cast< Rook >(board.getPiece(coord));
        EXPECT_NE(rook, nullptr);
    }
}

TEST(Board, BlackRookCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : coordinates::BLACK_ROOK)
    {
        const shared_ptr< Rook > rook =
            dynamic_pointer_cast< Rook >(board.getPiece(coord));
        EXPECT_NE(rook, nullptr);
    }
}

TEST(Board, WhitePawnCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : coordinates::WHITE_PAWN)
    {
        const shared_ptr< Pawn > pawn =
            dynamic_pointer_cast< Pawn >(board.getPiece(coord));
        EXPECT_NE(pawn, nullptr);
    }
}

TEST(Board, BlackPawnCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : coordinates::BLACK_PAWN)
    {
        const shared_ptr< Pawn > pawn =
            dynamic_pointer_cast< Pawn >(board.getPiece(coord));
        EXPECT_NE(pawn, nullptr);
    }
}

TEST(Board, whiteStarts)
{
    Board board;
    EXPECT_TRUE(board.isTurn(true));
    EXPECT_FALSE(board.isTurn(false));
}

TEST(Board, OutOfBounds)
{
    Board board;
    EXPECT_FALSE(board.isValidMove({-1, 0}, true));
    EXPECT_FALSE(board.isValidMove({-1, 0}, false));
    EXPECT_FALSE(board.isValidMove({0, -1}, true));
    EXPECT_FALSE(board.isValidMove({0, -1}, false));
    EXPECT_FALSE(board.isValidMove({board::SIZE, 0}, true));
    EXPECT_FALSE(board.isValidMove({board::SIZE, 0}, false));
    EXPECT_FALSE(board.isValidMove({0, board::SIZE}, true));
    EXPECT_FALSE(board.isValidMove({0, board::SIZE}, false));
}

TEST(Board, CanCaptureWhiteKing)
{
    Board board;
    EXPECT_TRUE(board.isValidMove(coordinates::WHITE_KING, false));
    EXPECT_FALSE(board.isValidMove(coordinates::WHITE_KING, true));
}

TEST(Board, CanCaptureBlackKing)
{
    Board board;
    EXPECT_TRUE(board.isValidMove(coordinates::BLACK_KING, true));
    EXPECT_FALSE(board.isValidMove(coordinates::BLACK_KING, false));
}

TEST(Board, CanCaptureWhitePawn)
{
    Board board;
    for (const std::pair< int, int >& coord : coordinates::WHITE_PAWN)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }
}

TEST(Board, CanCaptureBlackPawn)
{
    Board board;
    for (const std::pair< int, int >& coord : coordinates::BLACK_PAWN)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }
}

TEST(Board, CanCaptureWhiteRook)
{
    Board board;
    for (const std::pair< int, int >& coord : coordinates::WHITE_ROOK)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }
}

TEST(Board, CanCaptureBlackRook)
{
    Board board;
    for (const std::pair< int, int >& coord : coordinates::BLACK_ROOK)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }
}

TEST(Board, CanCaptureWhiteKnight)
{
    Board board;
    for (const std::pair< int, int >& coord : coordinates::WHITE_KNIGHT)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }
}

TEST(Board, CanCaptureBlackKnight)
{
    Board board;
    for (const std::pair< int, int >& coord : coordinates::BLACK_KNIGHT)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }
}

TEST(Board, CanCaptureWhiteBishop)
{
    Board board;
    for (const std::pair< int, int >& coord : coordinates::WHITE_BISHOP)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }
}

TEST(Board, CanCaptureBlackBishop)
{
    Board board;
    for (const std::pair< int, int >& coord : coordinates::BLACK_BISHOP)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }
}

TEST(Board, CanCaptureWhiteQueen)
{
    Board board;
    EXPECT_TRUE(board.isValidMove(coordinates::WHITE_QUEEN, false));
    EXPECT_FALSE(board.isValidMove(coordinates::WHITE_QUEEN, true));
}

TEST(Board, CanCaptureBlackQueen)
{
    Board board;
    EXPECT_TRUE(board.isValidMove(coordinates::BLACK_QUEEN, true));
    EXPECT_FALSE(board.isValidMove(coordinates::BLACK_QUEEN, false));
}

TEST(Board, isCheck)
{
    Board  board;
    size_t activePiecesCount = board.getActivePieces().size();

    for (int i : range(board::SIZE))
    {
        for (int j : range(board::SIZE))
        {
            const shared_ptr< Piece > piece = board.getPiece({i, j});
            if (piece != nullptr)
            {
                board.removePiece(piece);
                activePiecesCount--;
                EXPECT_EQ(board.getActivePieces().size(), activePiecesCount);
            }
        }
    }

    const pair< int, int > whiteKingCoords = coordinates::WHITE_ROOK[0];
    const pair< int, int > blackKingCoords = coordinates::BLACK_ROOK[0];

    board.makePiece< King >(whiteKingCoords, true);
    EXPECT_EQ(board.getActivePieces().size(), ++activePiecesCount);
    board.makePiece< King >(blackKingCoords, false);
    EXPECT_EQ(board.getActivePieces().size(), ++activePiecesCount);

    EXPECT_FALSE(board.isCheck(true));
    EXPECT_FALSE(board.isCheck(false));

    board.makePiece< Rook >(coordinates::WHITE_ROOK[1], false);
    EXPECT_TRUE(board.isCheck(true));
    EXPECT_EQ(board.getActivePieces().size(), ++activePiecesCount);
    board.makePiece< Pawn >(coordinates::WHITE_KING, true);
    EXPECT_FALSE(board.isCheck(true));
    EXPECT_EQ(board.getActivePieces().size(), ++activePiecesCount);

    board.makePiece< Rook >(coordinates::BLACK_ROOK[1], true);
    EXPECT_TRUE(board.isCheck(false));
    EXPECT_EQ(board.getActivePieces().size(), ++activePiecesCount);
    board.makePiece< Pawn >(coordinates::BLACK_KING, false);
    EXPECT_FALSE(board.isCheck(false));
    EXPECT_EQ(board.getActivePieces().size(), ++activePiecesCount);

    board.makePiece< Pawn >(
        {whiteKingCoords.first - 1, whiteKingCoords.second + 1}, false);
    EXPECT_TRUE(board.isCheck(true));
    EXPECT_EQ(board.getActivePieces().size(), ++activePiecesCount);

    board.makePiece< Pawn >(
        {blackKingCoords.first + 1, blackKingCoords.second + 1}, true);
    EXPECT_TRUE(board.isCheck(false));
    EXPECT_EQ(board.getActivePieces().size(), ++activePiecesCount);
}

TEST(Board, movePiece)
{
    using nPieces::ROOK, std::shared_ptr;

    Board  board;
    size_t activePiecesCount = board.getActivePieces().size();

    shared_ptr< Piece > piece = board.getPiece(coordinates::WHITE_KING);
    board.movePiece(piece, coordinates::BLACK_ROOK[0]);
    board.movePiece(piece, coordinates::BLACK_ROOK[1]);
    activePiecesCount -= ROOK;
    EXPECT_EQ(board.getActivePieces().size(), activePiecesCount);

    piece = board.getPiece(coordinates::BLACK_KING);
    board.movePiece(piece, coordinates::WHITE_ROOK[0]);
    board.movePiece(piece, coordinates::WHITE_ROOK[1]);
    activePiecesCount -= ROOK;
    EXPECT_EQ(board.getActivePieces().size(), activePiecesCount);
}

#endif
