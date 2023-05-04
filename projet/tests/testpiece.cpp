#include "testpiece.hpp"

void PieceTest::SetUp()
{
    piece = board.getPiece(coordinates::WHITE_ROOK[0]);
}

void PieceTest::TearDown()
{
}
