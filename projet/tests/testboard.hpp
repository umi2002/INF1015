#pragma once

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

class BoardTest : public ::testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;

    Board board_;
};

#endif
