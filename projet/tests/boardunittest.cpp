/**
 * Programme qui permet de tester les méthodes de la classe Board.
 * \file boardunittest.cpp
 * \author Hoang et Ibarissen
 * \date 5 mai 2023
 * Créé le 12 avril 2023
 */

#include "../model/board.hpp"
#include "../model/pieces/bishop.hpp"
#include "../model/pieces/king.hpp"
#include "../model/pieces/knight.hpp"
#include "../model/pieces/pawn.hpp"
#include "../model/pieces/queen.hpp"
#include "../model/pieces/rook.hpp"

#include "gtest/gtest.h"

using namespace coordinates;

using std::string, std::shared_ptr, std::pair, std::dynamic_pointer_cast;

TEST(BoardTest, activePieces)
{
    using nPieces::TOTAL;

    Board board;
    Board emptyBoard("8/8/8/8/8/8/8/8 w");
    EXPECT_EQ(emptyBoard.getActivePieces().size(), 0);
    EXPECT_EQ(board.getActivePieces().size(), TOTAL);
}

TEST(BoardTest, whiteKingCoordinates)
{
    Board board;
    for (const pair< int, int >& coordinates : WHITE_KING)
    {
        const shared_ptr< King > whiteKing =
            dynamic_pointer_cast< King >(board.getPiece(coordinates));
        EXPECT_NE(whiteKing, nullptr);
    }
}

TEST(BoardTest, blackKingCoordinates)
{
    Board board;
    for (const pair< int, int >& coordinates : BLACK_KING)
    {
        const shared_ptr< King > blackKing =
            dynamic_pointer_cast< King >(board.getPiece(coordinates));
        EXPECT_NE(blackKing, nullptr);
    }
}

TEST(BoardTest, whiteQueenCoordinates)
{
    Board board;
    for (const pair< int, int >& coordinates : WHITE_QUEEN)
    {
        const shared_ptr< Queen > whiteQueen =
            dynamic_pointer_cast< Queen >(board.getPiece(coordinates));
        EXPECT_NE(whiteQueen, nullptr);
    }
}

TEST(BoardTest, blackQueenCoordinates)
{
    Board board;
    for (const pair< int, int >& coordinates : BLACK_QUEEN)
    {
        const shared_ptr< Queen > blackQueen =
            dynamic_pointer_cast< Queen >(board.getPiece(coordinates));
        EXPECT_NE(blackQueen, nullptr);
    }
}

TEST(BoardTest, whiteBishopCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : WHITE_BISHOP)
    {
        const shared_ptr< Bishop > bishop =
            dynamic_pointer_cast< Bishop >(board.getPiece(coord));
        EXPECT_NE(bishop, nullptr);
    }
}

TEST(BoardTest, blackBishopCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : BLACK_BISHOP)
    {
        const shared_ptr< Bishop > bishop =
            dynamic_pointer_cast< Bishop >(board.getPiece(coord));
        EXPECT_NE(bishop, nullptr);
    }
}

TEST(BoardTest, whiteKnightCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : WHITE_KNIGHT)
    {
        const shared_ptr< Knight > knight =
            dynamic_pointer_cast< Knight >(board.getPiece(coord));
        EXPECT_NE(knight, nullptr);
    }
}

TEST(BoardTest, blackKnightCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : BLACK_KNIGHT)
    {
        const shared_ptr< Knight > knight =
            dynamic_pointer_cast< Knight >(board.getPiece(coord));
        EXPECT_NE(knight, nullptr);
    }
}

TEST(BoardTest, whiteRookCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : WHITE_ROOK)
    {
        const shared_ptr< Rook > rook =
            dynamic_pointer_cast< Rook >(board.getPiece(coord));
        EXPECT_NE(rook, nullptr);
    }
}

TEST(BoardTest, blackRookCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : BLACK_ROOK)
    {
        const shared_ptr< Rook > rook =
            dynamic_pointer_cast< Rook >(board.getPiece(coord));
        EXPECT_NE(rook, nullptr);
    }
}

TEST(BoardTest, whitePawnCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : WHITE_PAWN)
    {
        const shared_ptr< Pawn > pawn =
            dynamic_pointer_cast< Pawn >(board.getPiece(coord));
        EXPECT_NE(pawn, nullptr);
    }
}

TEST(BoardTest, blackPawnCoordinates)
{
    Board board;
    for (const pair< int, int >& coord : BLACK_PAWN)
    {
        const shared_ptr< Pawn > pawn =
            dynamic_pointer_cast< Pawn >(board.getPiece(coord));
        EXPECT_NE(pawn, nullptr);
    }
}

TEST(BoardTest, whiteStarts)
{
    Board board("8/8/8/8/8/8/8/8 w");
    EXPECT_TRUE(board.isTurn(true));
    EXPECT_FALSE(board.isTurn(false));
}

TEST(BoardTest, blackStarts)
{
    Board board("8/8/8/8/8/8/8/8 b");
    EXPECT_FALSE(board.isTurn(true));
    EXPECT_TRUE(board.isTurn(false));
}

TEST(BoardTest, outOfBoundsTopLeft)
{
    Board board;
    EXPECT_FALSE(board.isValidMove({-1, 0}, true));
    EXPECT_FALSE(board.isValidMove({-1, 0}, false));
}

TEST(BoardTest, outOfBoundsTopRight)
{
    Board board;
    EXPECT_FALSE(board.isValidMove({0, -1}, true));
    EXPECT_FALSE(board.isValidMove({0, -1}, false));
}

TEST(BoardTest, outOfBoundsBottomLeft)
{
    Board board;
    EXPECT_FALSE(board.isValidMove({board::SIZE, 0}, true));
    EXPECT_FALSE(board.isValidMove({board::SIZE, 0}, false));
}

TEST(BoardTest, outOfBoundsBottomRight)
{
    Board board;
    EXPECT_FALSE(board.isValidMove({0, board::SIZE}, true));
    EXPECT_FALSE(board.isValidMove({0, board::SIZE}, false));
}

TEST(BoardTest, canCaptureWhiteKing)
{
    Board board;
    for (const std::pair< int, int >& coord : WHITE_KING)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }
}

TEST(BoardTest, canCaptureBlackKing)
{
    Board board;
    for (const std::pair< int, int >& coord : BLACK_KING)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }
}

TEST(BoardTest, canCaptureWhitePawn)
{
    Board board;
    for (const std::pair< int, int >& coord : WHITE_PAWN)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }
}

TEST(BoardTest, canCaptureBlackPawn)
{
    Board board;
    for (const std::pair< int, int >& coord : BLACK_PAWN)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }
}

TEST(BoardTest, canCaptureWhiteRook)
{
    Board board;
    for (const std::pair< int, int >& coord : WHITE_ROOK)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }
}

TEST(BoardTest, canCaptureBlackRook)
{
    Board board;
    for (const std::pair< int, int >& coord : BLACK_ROOK)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }
}

TEST(BoardTest, canCaptureWhiteKnight)
{
    Board board;
    for (const std::pair< int, int >& coord : WHITE_KNIGHT)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }
}

TEST(BoardTest, canCaptureBlackKnight)
{
    Board board;
    for (const std::pair< int, int >& coord : BLACK_KNIGHT)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }
}

TEST(BoardTest, canCaptureWhiteBishop)
{
    Board board;
    for (const std::pair< int, int >& coord : WHITE_BISHOP)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }
}

TEST(BoardTest, canCaptureBlackBishop)
{
    Board board;
    for (const std::pair< int, int >& coord : BLACK_BISHOP)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }
}

TEST(BoardTest, canCaptureWhiteQueen)
{
    Board board;
    for (const std::pair< int, int >& coord : WHITE_QUEEN)
    {
        EXPECT_TRUE(board.isValidMove(coord, false));
        EXPECT_FALSE(board.isValidMove(coord, true));
    }
}

TEST(BoardTest, canCaptureBlackQueen)
{
    Board board;
    for (const std::pair< int, int >& coord : BLACK_QUEEN)
    {
        EXPECT_TRUE(board.isValidMove(coord, true));
        EXPECT_FALSE(board.isValidMove(coord, false));
    }
}

TEST(BoardTest, isCheck)
{
    Board board;
    EXPECT_FALSE(board.isCheck(true));
    EXPECT_FALSE(board.isCheck(false));
}

TEST(BoardTest, isCheckQueen)
{
    Board board("k7/1Q6/8/8/8/8/1q6/K7 w");
    EXPECT_TRUE(board.isCheck(true));
    EXPECT_TRUE(board.isCheck(false));
}

TEST(BoardTest, isCheckPawn)
{
    Board board("k7/1P6/8/8/8/8/1p6/K7 w");
    EXPECT_TRUE(board.isCheck(true));
    EXPECT_TRUE(board.isCheck(false));
}

TEST(BoardTest, isCheckRook)
{
    Board board("k6R/8/8/8/8/8/8/K6r w");
    EXPECT_TRUE(board.isCheck(true));
    EXPECT_TRUE(board.isCheck(false));
}

TEST(BoardTest, isCheckKnight)
{
    Board board("k7/8/1N6/8/8/1n6/8/K7 w");
    EXPECT_TRUE(board.isCheck(true));
    EXPECT_TRUE(board.isCheck(false));
}

TEST(BoardTest, isCheckBishop)
{
    Board board("k7/1B6/8/8/8/8/1b6/K7 w");
    EXPECT_TRUE(board.isCheck(true));
    EXPECT_TRUE(board.isCheck(false));
}

TEST(BoardTest, moveWhitePiece)
{
    using nPieces::ROOK;

    Board  board;
    size_t activePiecesCount = board.getActivePieces().size();

    shared_ptr< Piece > piece = board.getPiece(WHITE_KING[0]);
    board.movePiece(piece, BLACK_ROOK[0]);
    board.movePiece(piece, BLACK_ROOK[1]);
    activePiecesCount -= ROOK;
    EXPECT_EQ(board.getActivePieces().size(), activePiecesCount);
}

TEST(BoardTest, moveBlackPiece)
{
    using nPieces::ROOK;

    Board  board;
    size_t activePiecesCount = board.getActivePieces().size();

    shared_ptr< Piece > piece = board.getPiece(BLACK_KING[0]);
    piece                     = board.getPiece(BLACK_KING[0]);
    board.movePiece(piece, WHITE_ROOK[0]);
    board.movePiece(piece, WHITE_ROOK[1]);
    activePiecesCount -= ROOK;
    EXPECT_EQ(board.getActivePieces().size(), activePiecesCount);
}
