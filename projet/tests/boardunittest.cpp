/**
 * Programme qui permet de tester la classe BoardTest.
 * \file board_.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "testboard.hpp"

#if __has_include("gtest/gtest.h")
#    include "gtest/gtest.h"
#endif
#ifdef TEST_F

using namespace coordinates;

using nPieces::TOTAL, std::shared_ptr, std::pair, std::dynamic_pointer_cast;

TEST_F(BoardTest, activePieces)
{
    EXPECT_EQ(board_.getActivePieces().size(), 0);
    board_.addPieces();
    EXPECT_EQ(board_.getActivePieces().size(), TOTAL);
}

TEST_F(BoardTest, whiteKingCoordinates)
{
    board_.addKings();
    for (const pair< int, int >& coordinates : WHITE_KING)
    {
        const shared_ptr< King > whiteKing =
            dynamic_pointer_cast< King >(board_.getPiece(coordinates));
        EXPECT_NE(whiteKing, nullptr);
    }
}

TEST_F(BoardTest, blackKingCoordinates)
{
    board_.addKings();
    for (const pair< int, int >& coordinates : BLACK_KING)
    {
        const shared_ptr< King > blackKing =
            dynamic_pointer_cast< King >(board_.getPiece(coordinates));
        EXPECT_NE(blackKing, nullptr);
    }
}

TEST_F(BoardTest, whiteQueenCoordinates)
{
    board_.addQueens();
    for (const pair< int, int >& coordinates : WHITE_QUEEN)
    {
        const shared_ptr< Queen > whiteQueen =
            dynamic_pointer_cast< Queen >(board_.getPiece(coordinates));
        EXPECT_NE(whiteQueen, nullptr);
    }
}

TEST_F(BoardTest, blackQueenCoordinates)
{
    board_.addQueens();
    for (const pair< int, int >& coordinates : BLACK_QUEEN)
    {
        const shared_ptr< Queen > blackQueen =
            dynamic_pointer_cast< Queen >(board_.getPiece(coordinates));
        EXPECT_NE(blackQueen, nullptr);
    }
}

TEST_F(BoardTest, whiteBishopCoordinates)
{
    board_.addBishops();
    for (const pair< int, int >& coord : WHITE_BISHOP)
    {
        const shared_ptr< Bishop > bishop =
            dynamic_pointer_cast< Bishop >(board_.getPiece(coord));
        EXPECT_NE(bishop, nullptr);
    }
}

TEST_F(BoardTest, blackBishopCoordinates)
{
    board_.addBishops();
    for (const pair< int, int >& coord : BLACK_BISHOP)
    {
        const shared_ptr< Bishop > bishop =
            dynamic_pointer_cast< Bishop >(board_.getPiece(coord));
        EXPECT_NE(bishop, nullptr);
    }
}

TEST_F(BoardTest, whiteKnightCoordinates)
{
    board_.addKnights();
    for (const pair< int, int >& coord : WHITE_KNIGHT)
    {
        const shared_ptr< Knight > knight =
            dynamic_pointer_cast< Knight >(board_.getPiece(coord));
        EXPECT_NE(knight, nullptr);
    }
}

TEST_F(BoardTest, blackKnightCoordinates)
{
    board_.addKnights();
    for (const pair< int, int >& coord : BLACK_KNIGHT)
    {
        const shared_ptr< Knight > knight =
            dynamic_pointer_cast< Knight >(board_.getPiece(coord));
        EXPECT_NE(knight, nullptr);
    }
}

TEST_F(BoardTest, whiteRookCoordinates)
{
    board_.addRooks();
    for (const pair< int, int >& coord : WHITE_ROOK)
    {
        const shared_ptr< Rook > rook =
            dynamic_pointer_cast< Rook >(board_.getPiece(coord));
        EXPECT_NE(rook, nullptr);
    }
}

TEST_F(BoardTest, blackRookCoordinates)
{
    board_.addRooks();
    for (const pair< int, int >& coord : BLACK_ROOK)
    {
        const shared_ptr< Rook > rook =
            dynamic_pointer_cast< Rook >(board_.getPiece(coord));
        EXPECT_NE(rook, nullptr);
    }
}

TEST_F(BoardTest, whitePawnCoordinates)
{
    board_.addPawns();
    for (const pair< int, int >& coord : WHITE_PAWN)
    {
        const shared_ptr< Pawn > pawn =
            dynamic_pointer_cast< Pawn >(board_.getPiece(coord));
        EXPECT_NE(pawn, nullptr);
    }
}

TEST_F(BoardTest, blackPawnCoordinates)
{
    board_.addPawns();
    for (const pair< int, int >& coord : BLACK_PAWN)
    {
        const shared_ptr< Pawn > pawn =
            dynamic_pointer_cast< Pawn >(board_.getPiece(coord));
        EXPECT_NE(pawn, nullptr);
    }
}

TEST_F(BoardTest, whiteStarts)
{
    EXPECT_TRUE(board_.isTurn(true));
    EXPECT_FALSE(board_.isTurn(false));
}

TEST_F(BoardTest, outOfBoundsTopLeft)
{
    EXPECT_FALSE(board_.isValidMove({-1, 0}, true));
    EXPECT_FALSE(board_.isValidMove({-1, 0}, false));
}

TEST_F(BoardTest, outOfBoundsTopRight)
{
    EXPECT_FALSE(board_.isValidMove({0, -1}, true));
    EXPECT_FALSE(board_.isValidMove({0, -1}, false));
}

TEST_F(BoardTest, outOfBoundsBottomLeft)
{
    EXPECT_FALSE(board_.isValidMove({board::SIZE, 0}, true));
    EXPECT_FALSE(board_.isValidMove({board::SIZE, 0}, false));
}

TEST_F(BoardTest, outOfBoundsBottomRight)
{
    EXPECT_FALSE(board_.isValidMove({0, board::SIZE}, true));
    EXPECT_FALSE(board_.isValidMove({0, board::SIZE}, false));
}

TEST_F(BoardTest, canCaptureWhiteKing)
{
    board_.addKings();
    for (const std::pair< int, int >& coord : WHITE_KING)
    {
        EXPECT_TRUE(board_.isValidMove(coord, false));
        EXPECT_FALSE(board_.isValidMove(coord, true));
    }
}

TEST_F(BoardTest, canCaptureBlackKing)
{
    board_.addKings();
    for (const std::pair< int, int >& coord : BLACK_KING)
    {
        EXPECT_TRUE(board_.isValidMove(coord, true));
        EXPECT_FALSE(board_.isValidMove(coord, false));
    }
}

TEST_F(BoardTest, canCaptureWhitePawn)
{
    board_.addPawns();
    for (const std::pair< int, int >& coord : WHITE_PAWN)
    {
        EXPECT_TRUE(board_.isValidMove(coord, false));
        EXPECT_FALSE(board_.isValidMove(coord, true));
    }
}

TEST_F(BoardTest, canCaptureBlackPawn)
{
    board_.addPawns();
    for (const std::pair< int, int >& coord : BLACK_PAWN)
    {
        EXPECT_TRUE(board_.isValidMove(coord, true));
        EXPECT_FALSE(board_.isValidMove(coord, false));
    }
}

TEST_F(BoardTest, canCaptureWhiteRook)
{
    board_.addRooks();
    for (const std::pair< int, int >& coord : WHITE_ROOK)
    {
        EXPECT_TRUE(board_.isValidMove(coord, false));
        EXPECT_FALSE(board_.isValidMove(coord, true));
    }
}

TEST_F(BoardTest, canCaptureBlackRook)
{
    board_.addRooks();
    for (const std::pair< int, int >& coord : BLACK_ROOK)
    {
        EXPECT_TRUE(board_.isValidMove(coord, true));
        EXPECT_FALSE(board_.isValidMove(coord, false));
    }
}

TEST_F(BoardTest, canCaptureWhiteKnight)
{
    board_.addKnights();
    for (const std::pair< int, int >& coord : WHITE_KNIGHT)
    {
        EXPECT_TRUE(board_.isValidMove(coord, false));
        EXPECT_FALSE(board_.isValidMove(coord, true));
    }
}

TEST_F(BoardTest, canCaptureBlackKnight)
{
    board_.addKnights();
    for (const std::pair< int, int >& coord : BLACK_KNIGHT)
    {
        EXPECT_TRUE(board_.isValidMove(coord, true));
        EXPECT_FALSE(board_.isValidMove(coord, false));
    }
}

TEST_F(BoardTest, canCaptureWhiteBishop)
{
    board_.addBishops();
    for (const std::pair< int, int >& coord : WHITE_BISHOP)
    {
        EXPECT_TRUE(board_.isValidMove(coord, false));
        EXPECT_FALSE(board_.isValidMove(coord, true));
    }
}

TEST_F(BoardTest, canCaptureBlackBishop)
{
    board_.addBishops();
    for (const std::pair< int, int >& coord : BLACK_BISHOP)
    {
        EXPECT_TRUE(board_.isValidMove(coord, true));
        EXPECT_FALSE(board_.isValidMove(coord, false));
    }
}

TEST_F(BoardTest, canCaptureWhiteQueen)
{
    board_.addQueens();
    for (const std::pair< int, int >& coord : WHITE_QUEEN)
    {
        EXPECT_TRUE(board_.isValidMove(coord, false));
        EXPECT_FALSE(board_.isValidMove(coord, true));
    }
}

TEST_F(BoardTest, canCaptureBlackQueen)
{
    board_.addQueens();
    for (const std::pair< int, int >& coord : BLACK_QUEEN)
    {
        EXPECT_TRUE(board_.isValidMove(coord, true));
        EXPECT_FALSE(board_.isValidMove(coord, false));
    }
}

TEST_F(BoardTest, isCheckEmpty)
{
    board_.makePiece< King >(WHITE_KING[0], true);
    board_.makePiece< King >(BLACK_KING[0], false);
    EXPECT_FALSE(board_.isCheck(true));
    EXPECT_FALSE(board_.isCheck(false));
}

TEST_F(BoardTest, isCheckRook)
{
    board_.makePiece< King >(WHITE_KING[0], true);
    board_.makePiece< King >(BLACK_KING[0], false);

    board_.makePiece< Rook >(WHITE_ROOK[0], false);
    EXPECT_TRUE(board_.isCheck(true));
    board_.makePiece< Rook >(BLACK_ROOK[0], true);
    EXPECT_TRUE(board_.isCheck(false));
}

TEST_F(BoardTest, isCheckBlocked)
{
    board_.makePiece< King >(WHITE_ROOK[0], true);
    board_.makePiece< King >(BLACK_ROOK[0], false);

    board_.makePiece< Rook >(WHITE_ROOK[1], false);
    board_.makePiece< Rook >(BLACK_ROOK[1], true);

    board_.makePiece< Rook >(WHITE_KING[0], true);
    EXPECT_FALSE(board_.isCheck(true));
    board_.makePiece< Rook >(BLACK_KING[0], false);
    EXPECT_FALSE(board_.isCheck(false));
}

TEST_F(BoardTest, moveWhitePiece)
{
    using nPieces::ROOK, std::shared_ptr;

    board_.addPieces();

    size_t activePiecesCount = board_.getActivePieces().size();

    shared_ptr< Piece > piece = board_.getPiece(WHITE_KING[0]);
    board_.movePiece(piece, BLACK_ROOK[0]);
    board_.movePiece(piece, BLACK_ROOK[1]);
    activePiecesCount -= ROOK;
    EXPECT_EQ(board_.getActivePieces().size(), activePiecesCount);
}

TEST_F(BoardTest, moveBlackPiece)
{
    using nPieces::ROOK, std::shared_ptr;

    board_.addPieces();

    size_t activePiecesCount = board_.getActivePieces().size();

    shared_ptr< Piece > piece = board_.getPiece(BLACK_KING[0]);
    piece                     = board_.getPiece(BLACK_KING[0]);
    board_.movePiece(piece, WHITE_ROOK[0]);
    board_.movePiece(piece, WHITE_ROOK[1]);
    activePiecesCount -= ROOK;
    EXPECT_EQ(board_.getActivePieces().size(), activePiecesCount);
}

#endif
