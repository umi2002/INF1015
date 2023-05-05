/**
 * Programme qui implémente la base pour tester les pièces d'un jeu d'échecs.
 * \file testpiece.cpp
 * \author Hoang et Ibarissen
 * \date 5 mai 2023
 * Créé le 12 avril 2023
 */

#include "testpiece.hpp"

void PieceTest::SetUp()
{
    piece = board.getPiece(coordinates::WHITE_ROOK[0]);
}

void PieceTest::TearDown() { }
