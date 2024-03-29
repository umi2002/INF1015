#pragma once

#include "piece.hpp"

class Pawn : public Piece
{
public:
    Pawn(const std::pair< int, int >& coordinates, const bool& player);
    std::shared_ptr< Piece > clone() const override;
    bool                     isStartingPosition() const;

    std::vector< std::pair< int, int > >
                  getValidMoves(const Board& board) const override;
    const QString getName() const override;
};
