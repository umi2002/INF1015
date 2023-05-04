#pragma once

#include "../constants.hpp"
#include "../libraries.hpp"
#include "squaregui.hpp"

class PromoteGui : public QDialog
{
    Q_OBJECT

public:
    PromoteGui(QWidget* parent = nullptr);
    ~PromoteGui();
    char getPromotionPiece() const;
    void display(bool player);

private:
    void connectSquares();
    void makeSquares();

    char         promotionPiece_;
    QHBoxLayout* layout_;
    SquareGui*   queenButton_;
    SquareGui*   rookButton_;
    SquareGui*   bishopButton_;
    SquareGui*   knightButton_;

private slots:
    void onQueenClicked();
    void onRookClicked();
    void onBishopClicked();
    void onKnightClicked();
};
