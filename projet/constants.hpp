#pragma once

#include "libraries.hpp"

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

namespace coordinates
{
    const std::vector< std::pair< int, int > > WHITE_PAWN = {
        {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 7}};
    const std::vector< std::pair< int, int > > WHITE_KNIGHT = {{7, 1}, {7, 6}};
    const std::vector< std::pair< int, int > > WHITE_BISHOP = {{7, 2}, {7, 5}};
    const std::vector< std::pair< int, int > > WHITE_ROOK   = {{7, 0}, {7, 7}};
    const std::pair< int, int >                WHITE_QUEEN  = {7, 3};
    const std::pair< int, int >                WHITE_KING   = {7, 4};

    const std::vector< std::pair< int, int > > BLACK_PAWN = {
        {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}};
    const std::vector< std::pair< int, int > > BLACK_KNIGHT = {{0, 1}, {0, 6}};
    const std::vector< std::pair< int, int > > BLACK_BISHOP = {{0, 2}, {0, 5}};
    const std::vector< std::pair< int, int > > BLACK_ROOK   = {{0, 0}, {0, 7}};
    const std::pair< int, int >                BLACK_QUEEN  = {0, 3};
    const std::pair< int, int >                BLACK_KING   = {0, 4};
}  //namespace coordinates
