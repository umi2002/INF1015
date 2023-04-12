#pragma once

#include "../constants.hpp"
#include "../libraries.hpp"

class Board;

class Piece
{
public:
	Piece(const std::pair<int, int> coordinates, const bool player);
	virtual ~Piece() = default;
	virtual std::shared_ptr<Piece> clone() const = 0;
	std::pair<int, int> getCoordinates() const;
	bool                getPlayer() const;
	void                move(const std::pair<int, int> coordinates);
	bool                threatensKing(const Board& board) const;

	virtual std::vector<std::pair<int, int>>
						  getValidMoves(const Board& board) const = 0;
	virtual const QString getName() const                         = 0;

	void removeSuicideMoves(const Board&                      board,
	                        std::vector<std::pair<int, int>>& validMoves) const;

private:
    std::vector<std::pair<int, int>> validMoves_;
	std::pair<int, int> coordinates_;
	bool                player_;
};
