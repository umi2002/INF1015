#include "board.hpp"

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(Board, test1)
{
	Board board;
	const std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(board.getPiece({ 0, 0 }));
	bool isRook = rook != nullptr;
	EXPECT_EQ(isRook, true)
}

#endif