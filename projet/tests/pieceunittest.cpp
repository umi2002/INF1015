/**
 * Programme qui permet de tester la classe Piece et ses classes dérivées.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "testpiece.hpp"
#include "../model/pieces/king.hpp"
#include "../model/pieces/queen.hpp"
#include "../model/pieces/pawn.hpp"
#include "../model/pieces/rook.hpp"
#include "../model/pieces/bishop.hpp"
#include "../model/pieces/knight.hpp"

TEST_F(PieceTest, getCoordinates)
{
    std::pair< int, int > testCoordinates{5, 5};
    board.makePiece< Bishop >(testCoordinates, true);
    EXPECT_EQ(board.getPiece(testCoordinates)->getCoordinates(),
              testCoordinates);
}

TEST_F(PieceTest, extraKings)
{
    Board board;

    testing::internal::CaptureStdout();
    board.makePiece< King >({5, 5}, true);
    board.makePiece< King >({5, 5}, true);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Too many kings\nToo many kings\n");
    EXPECT_EQ(King::getCount(), 2);
}
