#pragma once

#include "../model/board.hpp"
#include "../model/pieces/bishop.hpp"
#include "../model/pieces/king.hpp"
#include "../model/pieces/knight.hpp"
#include "../model/pieces/pawn.hpp"
#include "../model/pieces/queen.hpp"
#include "../model/pieces/rook.hpp"

#include "gtest/gtest.h"

class PieceTest : public ::testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;

    Board                    board;
    std::shared_ptr< Piece > piece;
};
