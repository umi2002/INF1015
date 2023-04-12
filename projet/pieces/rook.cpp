#include "rook.hpp"

#include "../board.hpp"

Rook::Rook(const std::pair<int, int>& coordinates, const bool& player) :
	Piece(coordinates, player)
{ }

Rook::~Rook() { }

std::shared_ptr<Piece> Rook::clone() const
{
	return std::make_shared<Rook>(*this);
}

std::vector<std::pair<int, int>> Rook::getValidMoves(const Board& board) const
{
	std::vector<std::pair<int, int>>   validMoves;
	std::pair<int, int>                coordinates = getCoordinates();
	std::array<std::pair<int, int>, 4> directions  = {
        {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}
    };

	for (std::pair<int, int> direction : directions)
	{
		for (int i : iter::range(1, board::SIZE))
		{
			std::pair<int, int> destination = {
				coordinates.first + i * direction.first,
				coordinates.second + i * direction.second};
			if (!board.isValidMove(destination, getPlayer()))
			{
				break;
			}

			validMoves.push_back(destination);

			if (board.isOccupied(destination))
			{
				break;
			}
		}
	}

	return validMoves;
}

const QString Rook::getName() const
{
	return getPlayer() ? piece::WHITE_ROOK : piece::BLACK_ROOK;
}
