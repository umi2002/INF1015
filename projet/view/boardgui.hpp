#pragma once

#include "../model/board.hpp"
#include "../model/pieces/pawn.hpp"
#include "squaregui.hpp"

class BoardGui : public QWidget
{
    Q_OBJECT

public:
    BoardGui(QWidget* parent = nullptr, std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w");
    ~BoardGui();

    template< typename T >
    void addPiece(std::pair< int, int > coordinates, bool player);

private:
    void connectSignals();

    bool       isDark(const std::pair< int, int > coordinates) const;
    void       connectSquare(const std::pair< int, int > coordinates,
                             SquareGui*                  square);
    SquareGui& getSquare(const std::pair< int, int > coordinates);
    void       placePiece(const std::shared_ptr< Piece >& piece);
    void       removePiece(SquareGui& square);
    bool       isLegalMove(const std::pair< int, int > coordinates) const;
    void       movePiece(const std::pair< int, int > coordinates);
    void       checkPromotion();

    QGridLayout* boardLayout_;

    Board                    board_;
    std::shared_ptr< Piece > selectedPiece_ = nullptr;

private slots:
    void unHighlightSquares();
    void movePieceIfValid(std::pair< int, int > coordinates);
    void highlightSquare(std::pair< int, int > coordinates);
    void highlightValidMoves(std::pair< int, int > coordinates);
    void indicateInvalidMove();

signals:
    void squareSelected(std::pair< int, int > coordinates);
    void invalidMove();
    void promotion(std::pair< int, int > coordinates, bool player);
};

template< typename T >
void BoardGui::addPiece(std::pair< int, int > coordinates, bool player)
{
    std::shared_ptr< Piece > piece = board_.getPiece(coordinates);
    board_.removePiece(piece);
    board_.makePiece< T >(coordinates, player);
    placePiece(board_.getPiece(coordinates));
}
