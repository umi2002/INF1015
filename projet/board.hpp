#pragma once

#include "constants.hpp"
#include "libraries.hpp"

class Piece;

class Board
{
public:
	Board();
	~Board();

	bool isTurn(bool player) const;
	bool isOutOfBounds(const std::pair<int, int> coordinates) const;
	bool isOccupied(const std::pair<int, int> coordinates) const;
	bool isEnemy(const std::pair<int, int> coordinates, bool player) const;
	bool isValidMove(const std::pair<int, int> coordinates, bool player) const;
	void checkForCheck(bool player);
    bool isWhiteKingInCheck() const;
    bool isBlackKingInCheck() const;

	const std::shared_ptr<Piece>&
		 getPiece(const std::pair<int, int> coordinates) const;
	void movePiece(std::shared_ptr<Piece>&   piece,
	               const std::pair<int, int> coordinates);

private:
	std::shared_ptr<Piece>              board_[board::SIZE][board::SIZE];
	std::vector<std::shared_ptr<Piece>> activePieces_;

	bool turn_             = true;
	bool whiteKingInCheck_ = false;
	bool blackKingInCheck_ = false;
};