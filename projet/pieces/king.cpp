#include "king.hpp"

#include "../board.hpp"

King::King(const std::pair<int, int>& coordinates, const bool& player) :
	Piece(coordinates, player)
{ }

King::~King() { }

const std::vector<std::pair<int, int>>
King::getValidMoves(const Board& board) const
{
	std::vector<std::pair<int, int>> validMoves;
	const std::pair<int, int>        coordinates = getCoordinates();

	for (int i : iter::range(-1, 2))
	{
		for (int j : iter::range(-1, 2))
		{
			if (i == 0 && j == 0)
			{
				continue;
			}

			std::pair<int, int> destination =
				std::make_pair(coordinates.first + i, coordinates.second + j);
			if (board.isValidMove(destination, getPlayer()))
			{
				validMoves.push_back(destination);
			}
		}
	}

	return validMoves;
}

const QString King::getName() const
{
	return getPlayer() ? piece::WHITE_KING : piece::BLACK_KING;
}
