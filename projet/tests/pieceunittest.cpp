/**
 * Programme qui permet de tester la classe Piece et ses classes dérivées.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "testpiece.hpp"

using std::pair, std::string, std::shared_ptr;

TEST_F(PieceTest, getCoordinates)
{
    EXPECT_EQ(piece->getCoordinates(), coordinates::WHITE_ROOK[0]);
}

TEST_F(PieceTest, getPlayer)
{
    EXPECT_EQ(piece->getPlayer(), true);
}

TEST_F(PieceTest, move)
{
    pair< int, int > coordinates = {5, 5};
    piece->move(coordinates);
    EXPECT_EQ(piece->getCoordinates(), coordinates);
}

TEST_F(PieceTest, getNameWhiteKing)
{
    const shared_ptr< Piece >& king = board.getPiece(coordinates::WHITE_KING[0]);
    EXPECT_EQ(king->getName(), piece::WHITE_KING);
}

TEST_F(PieceTest, getNameBlackKing)
{
    const shared_ptr< Piece >& king = board.getPiece(coordinates::BLACK_KING[0]);
    EXPECT_EQ(king->getName(), piece::BLACK_KING);
}

TEST_F(PieceTest, getNameWhiteQueen)
{
    const shared_ptr< Piece >& queen = board.getPiece(coordinates::WHITE_QUEEN[0]);
    EXPECT_EQ(queen->getName(), piece::WHITE_QUEEN);
}

TEST_F(PieceTest, getNameBlackQueen)
{
    const shared_ptr< Piece >& queen = board.getPiece(coordinates::BLACK_QUEEN[0]);
    EXPECT_EQ(queen->getName(), piece::BLACK_QUEEN);
}

TEST_F(PieceTest, getNameWhiteRook)
{
    const shared_ptr< Piece >& rook = board.getPiece(coordinates::WHITE_ROOK[0]);
    EXPECT_EQ(rook->getName(), piece::WHITE_ROOK);
}

TEST_F(PieceTest, getNameBlackRook)
{
    const shared_ptr< Piece >& rook = board.getPiece(coordinates::BLACK_ROOK[0]);
    EXPECT_EQ(rook->getName(), piece::BLACK_ROOK);
}

TEST_F(PieceTest, getNameWhiteBishop)
{
    const shared_ptr< Piece >& bishop = board.getPiece(coordinates::WHITE_BISHOP[0]);
    EXPECT_EQ(bishop->getName(), piece::WHITE_BISHOP);
}

TEST_F(PieceTest, getNameBlackBishop)
{
    const shared_ptr< Piece >& bishop = board.getPiece(coordinates::BLACK_BISHOP[0]);
    EXPECT_EQ(bishop->getName(), piece::BLACK_BISHOP);
}

TEST_F(PieceTest, getNameWhiteKnight)
{
    const shared_ptr< Piece >& knight = board.getPiece(coordinates::WHITE_KNIGHT[0]);
    EXPECT_EQ(knight->getName(), piece::WHITE_KNIGHT);
}

TEST_F(PieceTest, getNameBlackKnight)
{
    const shared_ptr< Piece >& knight = board.getPiece(coordinates::BLACK_KNIGHT[0]);
    EXPECT_EQ(knight->getName(), piece::BLACK_KNIGHT);
}

TEST_F(PieceTest, getNameWhitePawn)
{
    const shared_ptr< Piece >& pawn = board.getPiece(coordinates::WHITE_PAWN[0]);
    EXPECT_EQ(pawn->getName(), piece::WHITE_PAWN);
}

TEST_F(PieceTest, getNameBlackPawn)
{
    const shared_ptr< Piece >& pawn = board.getPiece(coordinates::BLACK_PAWN[0]);
    EXPECT_EQ(pawn->getName(), piece::BLACK_PAWN);
}
