/**
 * Programme qui impl�mente la base pour tester les pi�ces d'un jeu d'�checs.
 * \file testpiece.cpp
 * \author Hoang et Ibarissen
 * \date 5 mai 2023
 * Cr�� le 12 avril 2023
 */

#include "testpiece.hpp"

void PieceTest::SetUp()
{
    piece = board.getPiece(coordinates::WHITE_ROOK[0]);
}

void PieceTest::TearDown() { }
