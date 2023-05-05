/**
 * Programme qui permet de tester la classe Piece et ses classes dérivées.
 * \file pieceunittest.cpp
 * \author Hoang et Ibarissen
 * \date 5 mai 2023
 * Créé le 12 avril 2023
 */

#include "testpiece.hpp"

using std::dynamic_pointer_cast, std::pair, std::string, std::shared_ptr,
    std::vector;

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
    const shared_ptr< Piece >& king =
        board.getPiece(coordinates::WHITE_KING[0]);
    EXPECT_EQ(king->getName(), piece::WHITE_KING);
}

TEST_F(PieceTest, getNameBlackKing)
{
    const shared_ptr< Piece >& king =
        board.getPiece(coordinates::BLACK_KING[0]);
    EXPECT_EQ(king->getName(), piece::BLACK_KING);
}

TEST_F(PieceTest, getNameWhiteQueen)
{
    const shared_ptr< Piece >& queen =
        board.getPiece(coordinates::WHITE_QUEEN[0]);
    EXPECT_EQ(queen->getName(), piece::WHITE_QUEEN);
}

TEST_F(PieceTest, getNameBlackQueen)
{
    const shared_ptr< Piece >& queen =
        board.getPiece(coordinates::BLACK_QUEEN[0]);
    EXPECT_EQ(queen->getName(), piece::BLACK_QUEEN);
}

TEST_F(PieceTest, getNameWhiteRook)
{
    const shared_ptr< Piece >& rook =
        board.getPiece(coordinates::WHITE_ROOK[0]);
    EXPECT_EQ(rook->getName(), piece::WHITE_ROOK);
}

TEST_F(PieceTest, getNameBlackRook)
{
    const shared_ptr< Piece >& rook =
        board.getPiece(coordinates::BLACK_ROOK[0]);
    EXPECT_EQ(rook->getName(), piece::BLACK_ROOK);
}

TEST_F(PieceTest, getNameWhiteBishop)
{
    const shared_ptr< Piece >& bishop =
        board.getPiece(coordinates::WHITE_BISHOP[0]);
    EXPECT_EQ(bishop->getName(), piece::WHITE_BISHOP);
}

TEST_F(PieceTest, getNameBlackBishop)
{
    const shared_ptr< Piece >& bishop =
        board.getPiece(coordinates::BLACK_BISHOP[0]);
    EXPECT_EQ(bishop->getName(), piece::BLACK_BISHOP);
}

TEST_F(PieceTest, getNameWhiteKnight)
{
    const shared_ptr< Piece >& knight =
        board.getPiece(coordinates::WHITE_KNIGHT[0]);
    EXPECT_EQ(knight->getName(), piece::WHITE_KNIGHT);
}

TEST_F(PieceTest, getNameBlackKnight)
{
    const shared_ptr< Piece >& knight =
        board.getPiece(coordinates::BLACK_KNIGHT[0]);
    EXPECT_EQ(knight->getName(), piece::BLACK_KNIGHT);
}

TEST_F(PieceTest, getNameWhitePawn)
{
    const shared_ptr< Piece >& pawn =
        board.getPiece(coordinates::WHITE_PAWN[0]);
    EXPECT_EQ(pawn->getName(), piece::WHITE_PAWN);
}

TEST_F(PieceTest, getNameBlackPawn)
{
    const shared_ptr< Piece >& pawn =
        board.getPiece(coordinates::BLACK_PAWN[0]);
    EXPECT_EQ(pawn->getName(), piece::BLACK_PAWN);
}

TEST_F(PieceTest, pawnPromotion)
{
    Board                     promotionBoard("kP6/8/8/8/8/8/8/Kp6 w");
    const shared_ptr< Pawn >& whitePawn =
        dynamic_pointer_cast< Pawn >(promotionBoard.getPiece({0, 1}));
    const shared_ptr< Pawn >& blackPawn =
        dynamic_pointer_cast< Pawn >(promotionBoard.getPiece({7, 1}));
    EXPECT_TRUE(whitePawn->canBePromoted());
    EXPECT_TRUE(blackPawn->canBePromoted());
}

TEST_F(PieceTest, noPromotion)
{
    const shared_ptr< Pawn >& whitePawn =
        dynamic_pointer_cast< Pawn >(board.getPiece({1, 0}));
    const shared_ptr< Pawn >& blackPawn =
        dynamic_pointer_cast< Pawn >(board.getPiece({6, 0}));
    EXPECT_FALSE(whitePawn->canBePromoted());
    EXPECT_FALSE(blackPawn->canBePromoted());
}

TEST_F(PieceTest, filteredKingMoves)
{
    Board                      boardCheck("k6Q/8/8/8/8/8/8/8 b");
    pair< int, int >           coordinates = {0, 0};
    const shared_ptr< Piece >& king        = boardCheck.getPiece(coordinates);
    vector< pair< int, int > > moves       = king->getValidMoves(boardCheck);
    king->removeSuicideMoves(boardCheck, moves);
    const int expectedMovesCount = 2;
    EXPECT_EQ(moves.size(), expectedMovesCount);
}

TEST_F(PieceTest, filteredQueenMoves)
{
    Board                      boardPin("kq5Q/8/8/8/8/8/8/8 b");
    pair< int, int >           coordinates = {0, 1};
    const shared_ptr< Piece >& queen       = boardPin.getPiece(coordinates);
    vector< pair< int, int > > moves       = queen->getValidMoves(boardPin);
    queen->removeSuicideMoves(boardPin, moves);
    const int expectedMovesCount = 6;
    EXPECT_EQ(moves.size(), expectedMovesCount);
}

TEST_F(PieceTest, filteredPawnMoves)
{
    Board                      boardPin("kp5Q/8/8/8/8/8/8/8 b");
    pair< int, int >           coordinates = {0, 1};
    const shared_ptr< Piece >& pawn        = boardPin.getPiece(coordinates);
    vector< pair< int, int > > moves       = pawn->getValidMoves(boardPin);
    pawn->removeSuicideMoves(boardPin, moves);
    const int expectedMovesCount = 0;
    EXPECT_EQ(moves.size(), expectedMovesCount);
}

TEST_F(PieceTest, filteredRookMoves)
{
    Board                      boardPin("kr5R/8/8/8/8/8/8/8 b");
    pair< int, int >           coordinates = {0, 1};
    const shared_ptr< Piece >& rook        = boardPin.getPiece(coordinates);
    vector< pair< int, int > > moves       = rook->getValidMoves(boardPin);
    rook->removeSuicideMoves(boardPin, moves);
    const int expectedMovesCount = 6;
    EXPECT_EQ(moves.size(), expectedMovesCount);
}

TEST_F(PieceTest, filteredKnightMoves)
{
    Board                      boardPin("kn5R/8/8/8/8/8/8/8 b");
    pair< int, int >           coordinates = {0, 1};
    const shared_ptr< Piece >& knight      = boardPin.getPiece(coordinates);
    vector< pair< int, int > > moves       = knight->getValidMoves(boardPin);
    knight->removeSuicideMoves(boardPin, moves);
    const int expectedMovesCount = 0;
    EXPECT_EQ(moves.size(), expectedMovesCount);
}

TEST_F(PieceTest, filteredBishopMoves)
{
    Board                      boardPin("kb5R/8/8/8/8/8/8/8 b");
    pair< int, int >           coordinates = {0, 1};
    const shared_ptr< Piece >& bishop      = boardPin.getPiece(coordinates);
    vector< pair< int, int > > moves       = bishop->getValidMoves(boardPin);
    bishop->removeSuicideMoves(boardPin, moves);
    const int expectedMovesCount = 0;
    EXPECT_EQ(moves.size(), expectedMovesCount);
}
