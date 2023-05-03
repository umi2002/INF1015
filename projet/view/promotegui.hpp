#pragma once

#include "../constants.hpp"
#include "../libraries.hpp"

class PromoteGui : public QDialog
{
    Q_OBJECT

public:
    PromoteGui(QWidget* parent = nullptr);
    char getPromotionPiece() const;

private:
    void connectButtons();

    char         promotionPiece_;
    QHBoxLayout* layout_       = new QHBoxLayout(this);
    QPushButton* queenButton_  = new QPushButton(this);
    QPushButton* rookButton_   = new QPushButton(this);
    QPushButton* bishopButton_ = new QPushButton(this);
    QPushButton* knightButton_ = new QPushButton(this);

private slots:
    void onQueenClicked();
    void onRookClicked();
    void onBishopClicked();
    void onKnightClicked();
};
