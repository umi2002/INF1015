/**
 * Programme qui implémente l'affichage d'un échiquier.
 * \file boardgui.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "boardgui.hpp"

using iter::range, std::shared_ptr, std::pair, std::vector;

BoardGui::BoardGui(QWidget* parent) : QWidget(parent)
{
    boardLayout_ = new QGridLayout(this);

    QString bgColor = "";
    for (int i : range(board::SIZE))
    {
        for (int j : range(board::SIZE))
        {
            bgColor = isDark({i, j}) ? square::DARK_BG : square::LIGHT_BG;
            SquareGui* square = new SquareGui(bgColor, this);
            connectSquare({i, j}, square);
            boardLayout_->addWidget(square, i, j);

            const shared_ptr< Piece >& piece = board_.getPiece({i, j});
            placePiece(piece);
        }
        boardLayout_->setRowStretch(i, 1);
        boardLayout_->setColumnStretch(i, 1);
    }
    boardLayout_->setSpacing(0);
    boardLayout_->setContentsMargins(0, 0, 0, 0);

    setLayout(boardLayout_);
    connectSignals();
}

BoardGui::~BoardGui()
{
    for (int i : range(board::SIZE))
    {
        for (int j : range(board::SIZE))
        {
            delete boardLayout_->itemAtPosition(i, j)->widget();
        }
    }
}

void BoardGui::connectSignals()
{
    QObject::connect(this,
                     SIGNAL(squareSelected(std::pair< int, int >)),
                     this,
                     SLOT(movePieceIfValid(std::pair< int, int >)));
    QObject::connect(this,
                     SIGNAL(squareSelected(std::pair< int, int >)),
                     this,
                     SLOT(highlightSquare(std::pair< int, int >)));
    QObject::connect(this,
                     SIGNAL(squareSelected(std::pair< int, int >)),
                     this,
                     SLOT(highlightValidMoves(std::pair< int, int >)));
    QObject::connect(
        this, SIGNAL(invalidMove()), this, SLOT(indicateInvalidMove()));
}

bool BoardGui::isDark(const pair< int, int > coordinates) const
{
    return (coordinates.first + coordinates.second) % 2 != 0;
}

void BoardGui::connectSquare(const pair< int, int > coordinates,
                             SquareGui*             square)
{
    QObject::connect(
        square, SIGNAL(clicked()), this, SLOT(unHighlightSquares()));
    QObject::connect(square,
                     &SquareGui::clicked,
                     [this, coordinates]
                     {
                         emit squareSelected(coordinates);
                         selectedPiece_ = board_.getPiece(coordinates);
                     });
}

SquareGui& BoardGui::getSquare(const pair< int, int > coordinates)
{
    return *static_cast< SquareGui* >(
        boardLayout_->itemAtPosition(coordinates.first, coordinates.second)
            ->widget());
}

void BoardGui::placePiece(const shared_ptr< Piece >& piece)
{
    if (!piece)
    {
        return;
    }

    SquareGui& square = getSquare(piece->getCoordinates());
    square.setText(piece->getName());
}

void BoardGui::removePiece(SquareGui& square)
{
    square.setText("");
}

bool BoardGui::isLegalMove(const pair< int, int > coordinates) const
{
    vector< pair< int, int > > selectedPieceValidMoves =
        selectedPiece_->getValidMoves(board_);
    selectedPiece_->removeSuicideMoves(board_, selectedPieceValidMoves);
    auto validMovesIterator = std::find(selectedPieceValidMoves.begin(),
                                        selectedPieceValidMoves.end(),
                                        coordinates);

    return validMovesIterator != selectedPieceValidMoves.end();
}

void BoardGui::movePiece(const pair< int, int > coordinates)
{
    const pair< int, int > selectedPieceCoords =
        selectedPiece_->getCoordinates();
    SquareGui& selectedSquare = getSquare(selectedPieceCoords);
    board_.movePiece(selectedPiece_, coordinates);
    removePiece(selectedSquare);
    placePiece(selectedPiece_);
}

void BoardGui::checkPromotion()
{
    shared_ptr< Pawn > pawn = std::dynamic_pointer_cast< Pawn >(selectedPiece_);

    if (!pawn)
    {
        return;
    }

    pair< int, int > coordinates = selectedPiece_->getCoordinates();
    bool             player      = selectedPiece_->getPlayer();

    if (pawn->canBePromoted())
    {
        emit promotion(coordinates, player);
    }
}

void BoardGui::unHighlightSquares()
{
    QString bgColor = "";
    for (int i : range(board::SIZE))
    {
        for (int j : range(board::SIZE))
        {
            SquareGui& square = getSquare({i, j});
            bgColor = isDark({i, j}) ? square::DARK_BG : square::LIGHT_BG;
            square.setStyleSheet(bgColor);
        }
    }
}

void BoardGui::movePieceIfValid(pair< int, int > coordinates)
{
    if (!selectedPiece_)
    {
        return;
    }

    if (!board_.isTurn(selectedPiece_->getPlayer()))
    {
        return;
    }

    if (!isLegalMove(coordinates))
    {
        emit invalidMove();
        return;
    }

    movePiece(coordinates);
    checkPromotion();
}

void BoardGui::highlightSquare(pair< int, int > coordinates)
{
    SquareGui& square = getSquare(coordinates);
    if (square.text() != "")
    {
        square.setStyleSheet(square::SELECTED_BG);
    }
}

void BoardGui::highlightValidMoves(pair< int, int > coordinates)
{
    const shared_ptr< Piece >& piece = board_.getPiece(coordinates);

    if (!piece)
    {
        return;
    }

    if (!board_.isTurn(piece->getPlayer()))
    {
        return;
    }

    vector< pair< int, int > > validMoves = piece->getValidMoves(board_);

    piece->removeSuicideMoves(board_, validMoves);

    for (const pair< int, int >& move : validMoves)
    {
        SquareGui& square = getSquare(move);
        square.setStyleSheet(square::VALID_MOVE_BG);
    }
}

void BoardGui::indicateInvalidMove()
{
    pair< int, int > coordinates = selectedPiece_->getCoordinates();
    SquareGui&       square      = getSquare(coordinates);
    square.setStyleSheet(square::INVALID_MOVE_BG);
}
