/**
 * Programme qui permet de tester la classe Board.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "../model/board.hpp"
#include "../model/pieces/king.hpp"
#include "../model/pieces/pawn.hpp"
#include "../model/pieces/rook.hpp"

#if __has_include("gtest/gtest.h")
#    include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(Board, constructor)
{
    using std::shared_ptr, std::pair, std::dynamic_pointer_cast, iter::range;
    Board board;
    EXPECT_EQ(board.getActivePieces().size(), 22);

    pair< int, int >         whiteKingCoords = coordinates::WHITE_KING;
    const shared_ptr< King > whiteKing =
        dynamic_pointer_cast< King >(board.getPiece(whiteKingCoords));
    EXPECT_NE(whiteKing, nullptr);

    pair< int, int >         blackKingCoords = coordinates::BLACK_KING;
    const shared_ptr< King > blackKing =
        dynamic_pointer_cast< King >(board.getPiece(blackKingCoords));
    EXPECT_NE(blackKing, nullptr);

    for (const pair< int, int >& coord : coordinates::WHITE_PAWN)
    {
        const shared_ptr< Pawn > pawn =
            dynamic_pointer_cast< Pawn >(board.getPiece(coord));
        EXPECT_NE(pawn, nullptr);
    }

    for (const pair< int, int >& coord : coordinates::BLACK_PAWN)
    {
        const shared_ptr< Pawn > pawn =
            dynamic_pointer_cast< Pawn >(board.getPiece(coord));
        EXPECT_NE(pawn, nullptr);
    }

    for (const pair< int, int >& coord : coordinates::WHITE_ROOK)
    {
        const shared_ptr< Rook > rook =
            dynamic_pointer_cast< Rook >(board.getPiece(coord));
        EXPECT_NE(rook, nullptr);
    }

    for (const pair< int, int >& coord : coordinates::BLACK_ROOK)
    {
        const shared_ptr< Rook > rook =
            dynamic_pointer_cast< Rook >(board.getPiece(coord));
        EXPECT_NE(rook, nullptr);
    }
}

TEST(Board, whiteStarts)
{
    Board board;
    EXPECT_TRUE(board.isTurn(true));
    EXPECT_FALSE(board.isTurn(false));
}

TEST(board, isValidMove)
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

    EXPECT_TRUE(board.isValidMove(coordinates::WHITE_KING, false));
    EXPECT_FALSE(board.isValidMove(coordinates::WHITE_KING, true));
    EXPECT_TRUE(board.isValidMove(coordinates::BLACK_KING, true));
    EXPECT_FALSE(board.isValidMove(coordinates::BLACK_KING, false));

    for (const std::pair< int, int >& coord : coordinates::WHITE_PAWN)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }

    for (const std::pair< int, int >& coord : coordinates::BLACK_PAWN)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }

    for (const std::pair< int, int >& coord : coordinates::WHITE_ROOK)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }

    for (const std::pair< int, int >& coord : coordinates::BLACK_ROOK)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }
}

TEST(Board, isCheck)
{
    using iter::range, std::shared_ptr, std::pair;

    Board board;
    int   activePiecesCount = board.getActivePieces().size();

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
    EXPECT_EQ(board.getActivePieces().size(), 0);

    const pair< int, int > whiteKingCoords = coordinates::WHITE_ROOK[0];
    const pair< int, int > blackKingCoords = coordinates::BLACK_ROOK[0];

    board.makePiece< King >(whiteKingCoords, true);
    EXPECT_EQ(board.getActivePieces().size(), 1);
    board.makePiece< King >(blackKingCoords, false);
    EXPECT_EQ(board.getActivePieces().size(), 2);

    EXPECT_FALSE(board.isCheck(true));
    EXPECT_FALSE(board.isCheck(false));

    board.makePiece< Rook >(coordinates::WHITE_ROOK[1], false);
    EXPECT_TRUE(board.isCheck(true));
    EXPECT_EQ(board.getActivePieces().size(), 3);
    board.makePiece< Pawn >(coordinates::WHITE_KING, true);
    EXPECT_FALSE(board.isCheck(true));
    EXPECT_EQ(board.getActivePieces().size(), 4);

    board.makePiece< Rook >(coordinates::BLACK_ROOK[1], true);
    EXPECT_TRUE(board.isCheck(false));
    EXPECT_EQ(board.getActivePieces().size(), 5);
    board.makePiece< Pawn >(coordinates::BLACK_KING, false);
    EXPECT_FALSE(board.isCheck(false));
    EXPECT_EQ(board.getActivePieces().size(), 6);

    board.makePiece< Pawn >(
        {whiteKingCoords.first - 1, whiteKingCoords.second + 1}, false);
    EXPECT_TRUE(board.isCheck(true));
    EXPECT_EQ(board.getActivePieces().size(), 7);

    board.makePiece< Pawn >(
        {blackKingCoords.first + 1, blackKingCoords.second - 1}, true);
    EXPECT_TRUE(board.isCheck(false));
    EXPECT_EQ(board.getActivePieces().size(), 8);
}

TEST(Board, movePiece)
{
    using std::shared_ptr;

    Board board;

    shared_ptr< Piece > piece = board.getPiece(coordinates::WHITE_KING);
    board.movePiece(piece, coordinates::BLACK_ROOK[0]);
    board.movePiece(piece, coordinates::BLACK_ROOK[1]);
    EXPECT_EQ(board.getActivePieces().size(), 20);

    piece = board.getPiece(coordinates::BLACK_KING);
    board.movePiece(piece, coordinates::WHITE_ROOK[0]);
    board.movePiece(piece, coordinates::WHITE_ROOK[1]);
    EXPECT_EQ(board.getActivePieces().size(), 18);
}

#endif
