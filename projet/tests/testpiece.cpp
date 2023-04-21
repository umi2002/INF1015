/**
 * Programme qui permet de tester la classe Piece et ses classes dérivées.
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

TEST(Piece, king)
{
    Board board;

    testing::internal::CaptureStdout();
    board.makePiece< King >({5, 5}, true);
    board.makePiece< King >({5, 5}, true);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Too many kings\nToo many kings\n");
    EXPECT_EQ(King::getCount(), 2);
}

#endif