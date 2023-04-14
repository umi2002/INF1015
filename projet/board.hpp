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
	bool isCheck(bool player) const;

	const std::shared_ptr<Piece>&
		 getPiece(const std::pair<int, int> coordinates) const;
	void movePiece(std::shared_ptr<Piece>&   piece,
	               const std::pair<int, int> coordinates);

private:
	std::array<std::array<std::shared_ptr<Piece>, 8>, 8> board_;
	std::vector<std::shared_ptr<Piece>>                  activePieces_;

	bool turn_ = true;
};
