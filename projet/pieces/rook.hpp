#pragma once

#include "piece.hpp"

class Rook : public Piece
{
public:
	Rook(const std::pair<int, int>& coordinates, const bool& player);
	~Rook();
	std::shared_ptr<Piece> clone() const override;

	std::vector<std::pair<int, int>>
				  getValidMoves(const Board& board) const override;
	const QString getName() const override;
};
