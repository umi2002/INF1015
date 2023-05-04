#pragma once

#include "../constants.hpp"
#include "../libraries.hpp"

class Piece;

class Board
{
public:
    Board(std::string simplifiedFEN =
              "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w");
    ~Board();

    void convertFEN(std::string simplifiedFEN);

    bool isTurn(bool player) const;
    bool isOutOfBounds(const std::pair< int, int > coordinates) const;
    bool isOccupied(const std::pair< int, int > coordinates) const;
    bool isEnemy(const std::pair< int, int > coordinates, bool player) const;
    bool isValidMove(const std::pair< int, int > coordinates,
                     bool                        player) const;
    bool isCheck(bool player) const;

    const std::shared_ptr< Piece >&
         getPiece(const std::pair< int, int > coordinates) const;
    void removePiece(const std::shared_ptr< Piece >& piece);
    void movePiece(std::shared_ptr< Piece >&   piece,
                   const std::pair< int, int > coordinates);
    const std::vector< std::shared_ptr< Piece > >& getActivePieces() const;

    template< typename T >
    void makePiece(const std::pair< int, int > coordinates, const bool player);

private:
    std::array< std::array< std::shared_ptr< Piece >, board::SIZE >,
                board::SIZE >
                                            board_;
    std::vector< std::shared_ptr< Piece > > activePieces_;

    bool turn_ = true;
};

template< typename T >
void Board::makePiece(const std::pair< int, int > coordinates,
                      const bool                  player)
{
	std::shared_ptr< Piece > piece =
		std::make_shared< T >(coordinates, player);
	board_[coordinates.first][coordinates.second] = piece;
	activePieces_.push_back(piece);
}
