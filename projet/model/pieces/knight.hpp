#pragma once

#include "piece.hpp"

class Knight : public Piece
{
public:
    Knight(const std::pair< int, int >& coordinates, const bool& player);
    std::shared_ptr< Piece > clone() const override;

    std::vector< std::pair< int, int > >
                  getValidMoves(const Board& board) const override;
    const QString getName() const override;
};
