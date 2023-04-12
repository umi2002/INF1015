#pragma once

#include "piece.hpp"

class King : public Piece
{
public:
	King(const std::pair<int, int>& coordinates, const bool& player);
	~King();
	bool isInCheck(const Board& board) const;

	std::vector<std::pair<int, int>>
				  getValidMoves(const Board& board) const override;
	const QString getName() const override;
};
