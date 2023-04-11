#include "board.hpp"

#include "constants.hpp"
#include "pieces/king.hpp"
#include "pieces/pawn.hpp"
#include "pieces/rook.hpp"

#include <iostream>

Board::Board()
{
	for (int i : iter::range(board::SIZE))
	{
		for (int j : iter::range(board::SIZE))
		{
			board_[i][j] = nullptr;
		}
	}
	std::shared_ptr<Piece> piece;

	std::pair<int, int> whiteKingCoords = coordinates::WHITE_KING_COORDS;
	piece = std::make_shared<King>(whiteKingCoords, true);
	board_[whiteKingCoords.first][whiteKingCoords.second] = piece;
	activePieces_.push_back(piece);

	std::pair<int, int> blackKingCoords = coordinates::BLACK_KING_COORDS;
	piece = std::make_shared<King>(blackKingCoords, false);
	board_[blackKingCoords.first][blackKingCoords.second] = piece;
	activePieces_.push_back(piece);

	std::vector<std::pair<int, int>> whitePawnCoords =
		coordinates::WHITE_PAWN_COORDS;
	for (std::pair<int, int>& coord : whitePawnCoords)
	{
		piece                             = std::make_shared<Pawn>(coord, true);
		board_[coord.first][coord.second] = piece;
		activePieces_.push_back(piece);
	}

	std::vector<std::pair<int, int>> blackPawnCoords =
		coordinates::BLACK_PAWN_COORDS;
	for (std::pair<int, int>& coord : blackPawnCoords)
	{
		piece = std::make_shared<Pawn>(coord, false);
		board_[coord.first][coord.second] =
			std::make_shared<Pawn>(coord, false);
		activePieces_.push_back(piece);
	}

	std::vector<std::pair<int, int>> whiteRookCoords =
		coordinates::WHITE_ROOK_COORDS;
	for (std::pair<int, int>& coord : whiteRookCoords)
	{
		piece                             = std::make_shared<Rook>(coord, true);
		board_[coord.first][coord.second] = piece;
		activePieces_.push_back(piece);
	}

	std::vector<std::pair<int, int>> blackRookCoords =
		coordinates::BLACK_ROOK_COORDS;
	for (std::pair<int, int>& coord : blackRookCoords)
	{
		piece = std::make_shared<Rook>(coord, false);
		board_[coord.first][coord.second] = piece;
		activePieces_.push_back(piece);
	}
}

Board::~Board() { }

bool Board::isTurn(bool player) const
{
	return turn_ == player;
}

bool Board::isOutOfBounds(const std::pair<int, int> coordinates) const
{
	return coordinates.first < 0 || coordinates.first >= board::SIZE
	    || coordinates.second < 0 || coordinates.second >= board::SIZE;
}

bool Board::isOccupied(const std::pair<int, int> coordinates) const
{
	return board_[coordinates.first][coordinates.second] != nullptr;
}

bool Board::isEnemy(const std::pair<int, int> coordinates, bool player) const
{
	return board_[coordinates.first][coordinates.second]->getPlayer() != player;
}

bool Board::isValidMove(const std::pair<int, int> coordinates,
                        bool                      player) const
{
	if (isOutOfBounds(coordinates))
	{
		return false;
	}
	if (isOccupied(coordinates))
	{
		return isEnemy(coordinates, player);
	}
	return true;
}

void Board::checkForCheck(bool player)
{
	for (const std::shared_ptr<Piece>& piece : activePieces_)
	{
		if (piece->getPlayer() == player)
		{
			return;
		}

		if (!piece->threatensKing(*this))
		{
			return;
		}

		if (player)
		{
			whiteKingInCheck_ = true;
		}
		else
		{
			blackKingInCheck_ = true;
		}
	}
}

bool Board::isWhiteKingInCheck() const
{
    return whiteKingInCheck_;
}

bool Board::isBlackKingInCheck() const
{
    return blackKingInCheck_;
}

const std::shared_ptr<Piece>&
Board::getPiece(const std::pair<int, int> coordinates) const
{
	return board_[coordinates.first][coordinates.second];
}

void Board::movePiece(std::shared_ptr<Piece>&   piece,
                      const std::pair<int, int> coordinates)
{
	const std::shared_ptr<Piece>& targetPiece =
		board_[coordinates.first][coordinates.second];
	auto activePiecesIterator =
		std::find(activePieces_.begin(), activePieces_.end(), targetPiece);

	if (targetPiece != *activePieces_.end())
	{
		activePieces_.erase(activePiecesIterator);
	}

	board_[coordinates.first][coordinates.second] = piece;
	std::pair<int, int> oldCoords                 = piece->getCoordinates();
	board_[oldCoords.first][oldCoords.second]     = nullptr;
	piece->move(coordinates);
	turn_ = !turn_;
}