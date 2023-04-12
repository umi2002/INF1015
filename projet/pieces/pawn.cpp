#include "pawn.hpp"

#include "../board.hpp"

Pawn::Pawn(const std::pair<int, int>& coordinates, const bool& player) :
	Piece(coordinates, player)
{ }

Pawn::~Pawn() { }

std::shared_ptr<Piece> Pawn::clone() const
{
	return std::make_shared<Pawn>(*this);
}

bool Pawn::isStartingPosition() const
{
	return getPlayer()
	         ? getCoordinates().first == coordinates::WHITE_PAWN_COORDS[0].first
	         : getCoordinates().first
	               == coordinates::BLACK_PAWN_COORDS[0].first;
}

std::vector<std::pair<int, int>> Pawn::getValidMoves(const Board& board) const
{
	std::vector<std::pair<int, int>> validMoves;
	std::pair<int, int>              coordinates = getCoordinates();

	bool player    = getPlayer();
	int  direction = player ? -1 : 1;

	if (isStartingPosition())
	{
		std::pair<int, int> destination  = {coordinates.first + 2 * direction,
		                                    coordinates.second};
		std::pair<int, int> intermediate = {coordinates.first + direction,
		                                    coordinates.second};
		if (!board.isOccupied(destination) && !board.isOccupied(intermediate))
		{
			validMoves.push_back(destination);
		}
	}

	for (int i : iter::range(-1, 2))
	{
		std::pair<int, int> destination = {coordinates.first + direction,
		                                   coordinates.second + i};
		if (board.isOutOfBounds(destination))
		{
			continue;
		}

		if (destination.second == coordinates.second)
		{
			if (!board.isOccupied(destination))
			{
				validMoves.push_back(destination);
			}
		}
		else
		{
			if (board.isOccupied(destination)
			    && board.isEnemy(destination, player))
			{
				validMoves.push_back(destination);
			}
		}
	}

	return validMoves;
}

const QString Pawn::getName() const
{
	return getPlayer() ? piece::WHITE_PAWN : piece::BLACK_PAWN;
}
