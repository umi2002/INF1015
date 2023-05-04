#pragma once

#include "../libraries.hpp"

namespace board
{
    const int SIZE = 8;
}

namespace square
{
    const QFont   FONT            = QFont("Arial", 50);
    const QSize   SIZE            = QSize(100, 100);
    const QString DARK_BG         = "QPushButton { background-color: gray }";
    const QString LIGHT_BG        = "QPushButton { background-color: white }";
    const QString SELECTED_BG     = "QPushButton { background-color: blue }";
    const QString VALID_MOVE_BG   = "QPushButton { background-color: green }";
    const QString INVALID_MOVE_BG = "QPushButton { background-color: red }";
}  //namespace square

namespace piece
{
    const QString WHITE_PAWN   = "♙";
    const QString WHITE_KNIGHT = "♘";
    const QString WHITE_BISHOP = "♗";
    const QString WHITE_ROOK   = "♖";
    const QString WHITE_QUEEN  = "♕";
    const QString WHITE_KING   = "♔";

    const QString BLACK_PAWN   = "♟";
    const QString BLACK_KNIGHT = "♞";
    const QString BLACK_BISHOP = "♝";
    const QString BLACK_ROOK   = "♜";
    const QString BLACK_QUEEN  = "♛";
    const QString BLACK_KING   = "♚";
}  //namespace piece

namespace nPieces
{
    const int PAWN   = 8;
    const int KNIGHT = 2;
    const int BISHOP = 2;
    const int ROOK   = 2;
    const int QUEEN  = 1;
    const int KING   = 1;
    const int TOTAL  = 32;
}  //namespace nPieces

namespace coordinates
{
    const std::array< std::pair< int, int >, nPieces::PAWN > WHITE_PAWN = {
        {{6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 7}}};
    const std::array< std::pair< int, int >, nPieces::KNIGHT > WHITE_KNIGHT = {
        {{7, 1}, {7, 6}}};
    const std::array< std::pair< int, int >, nPieces::BISHOP > WHITE_BISHOP = {
        {{7, 2}, {7, 5}}};
    const std::array< std::pair< int, int >, nPieces::ROOK > WHITE_ROOK = {
        {{7, 0}, {7, 7}}};
    const std::array< std::pair< int, int >, nPieces::QUEEN > WHITE_QUEEN = {
        {{7, 3}}};
    const std::array< std::pair< int, int >, nPieces::KING > WHITE_KING = {
        {{7, 4}}};

    const std::array< std::pair< int, int >, nPieces::PAWN > BLACK_PAWN = {
        {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}}};
    const std::array< std::pair< int, int >, nPieces::KNIGHT > BLACK_KNIGHT = {
        {{0, 1}, {0, 6}}};
    const std::array< std::pair< int, int >, nPieces::BISHOP > BLACK_BISHOP = {
        {{0, 2}, {0, 5}}};
    const std::array< std::pair< int, int >, nPieces::ROOK > BLACK_ROOK = {
        {{0, 0}, {0, 7}}};
    const std::array< std::pair< int, int >, nPieces::QUEEN > BLACK_QUEEN = {
        {{0, 3}}};
    const std::array< std::pair< int, int >, nPieces::KING > BLACK_KING = {
        {{0, 4}}};
}  //namespace coordinates

namespace nDirections
{
    const int STRAIGHT = 4;
    const int DIAGONAL = 4;
    const int TOTAL    = STRAIGHT + DIAGONAL;
}  //namespace nDirections

namespace directions
{
    const std::array< std::pair< int, int >, nDirections::TOTAL > KING = {
        {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}}};
    const std::array< std::pair< int, int >, nDirections::STRAIGHT > ROOK = {
        {{1, 0}, {0, 1}, {0, -1}, {-1, 0}}};
    const std::array< std::pair< int, int >, nDirections::DIAGONAL > BISHOP = {
        {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}};
    const std::array< std::pair< int, int >, nDirections::TOTAL > QUEEN = {
        {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}}};
    const std::array< std::pair< int, int >, nDirections::TOTAL > KNIGHT = {
        {{2, 1},
         {2, -1},
         {-2, 1},
         {-2, -1},
         {1, 2},
         {1, -2},
         {-1, 2},
         {-1, -2}}};
}  //namespace directions

namespace promotionWindow
{
    const QSize SIZE = QSize(500, 200);
}  //namespace promotionWindow

namespace controlButton
{
    const QSize SIZE = QSize(0, 50);
}  //namespace controlButton
