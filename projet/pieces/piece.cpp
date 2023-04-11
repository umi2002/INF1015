#include "piece.hpp"

#include "../board.hpp"
#include "king.hpp"

#include <iostream>

Piece::Piece(const std::pair<int, int> coordinates, const bool player) :
	coordinates_(coordinates),
	player_(player)
{ }

Piece::~Piece() { }

std::pair<int, int> Piece::getCoordinates() const
{
	return coordinates_;
}

bool Piece::getPlayer() const
{
	return player_;
}

void Piece::move(const std::pair<int, int> coordinates)
{
	this->coordinates_ = coordinates;
}

bool Piece::threatensKing(const Board& board) const
{
	const std::vector<std::pair<int, int>> validMoves = getValidMoves(board);
	for (const std::pair<int, int>& move : validMoves)
	{
		const std::shared_ptr<King> piece =
			std::dynamic_pointer_cast<King>(board.getPiece(move));
		if (piece != nullptr)
		{
			return true;
		}
	}
	return false;
}
