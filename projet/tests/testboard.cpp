/**
 * Programme qui permet de tester la classe Board.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "../board.hpp"
#include "../pieces/king.hpp"
#include "../pieces/pawn.hpp"
#include "../pieces/rook.hpp"

#if __has_include("gtest/gtest.h")
#    include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(Board, constructor)
{
    using std::shared_ptr, std::pair, std::dynamic_pointer_cast;
    Board board;

    pair< int, int >         whiteKingCoords = coordinates::WHITE_KING_COORDS;
    const shared_ptr< King > whiteKing =
        dynamic_pointer_cast< King >(board.getPiece(whiteKingCoords));
    EXPECT_NE(whiteKing, nullptr);

    pair< int, int >         blackKingCoords = coordinates::BLACK_KING_COORDS;
    const shared_ptr< King > blackKing =
        dynamic_pointer_cast< King >(board.getPiece(blackKingCoords));
    EXPECT_NE(blackKing, nullptr);

    for (const pair< int, int >& coord : coordinates::WHITE_PAWN_COORDS)
    {
        const shared_ptr< Pawn > pawn =
            dynamic_pointer_cast< Pawn >(board.getPiece(coord));
        EXPECT_NE(pawn, nullptr);
    }

    for (const pair< int, int >& coord : coordinates::BLACK_PAWN_COORDS)
    {
        const shared_ptr< Pawn > pawn =
            dynamic_pointer_cast< Pawn >(board.getPiece(coord));
        EXPECT_NE(pawn, nullptr);
    }

    for (const pair< int, int >& coord : coordinates::WHITE_ROOK_COORDS)
    {
        const shared_ptr< Rook > rook =
            dynamic_pointer_cast< Rook >(board.getPiece(coord));
        EXPECT_NE(rook, nullptr);
    }

    for (const pair< int, int >& coord : coordinates::BLACK_ROOK_COORDS)
    {
        const shared_ptr< Rook > rook =
            dynamic_pointer_cast< Rook >(board.getPiece(coord));
        EXPECT_NE(rook, nullptr);
    }

    int emptySquaresCount = 0;
    for (int i = 0; i < board::SIZE; ++i)
    {
        for (int j = 0; j < board::SIZE; ++j)
        {
            if (board.getPiece({i, j}) == nullptr)
            {
                ++emptySquaresCount;
            }
        }
    }
    EXPECT_EQ(emptySquaresCount, 42);
}

#endif
