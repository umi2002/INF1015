#pragma once

#include "../model/board.hpp"

#include "gtest/gtest.h"

class PieceTest : public ::testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;

    Board board;
};
