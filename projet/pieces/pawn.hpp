#pragma once

#include "piece.hpp"

class Pawn : public Piece
{
public:
	Pawn(const std::pair<int, int>& coordinates, const bool& player);
	~Pawn();
	bool isStartingPosition() const;

	std::vector<std::pair<int, int>>
				  getValidMoves(const Board& board) const override;
	const QString getName() const override;
};
