/**
 * Programme qui implémente l'affichage de la promotion d'un pion.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "promotegui.hpp"

PromoteGui::PromoteGui(QWidget* parent) : QDialog(parent)
{
    using namespace piece;

    setWindowTitle("Promotion");
    setFixedSize(promotionWindow::SIZE);

    layout_->addWidget(queenButton_);
    layout_->addWidget(rookButton_);
    layout_->addWidget(bishopButton_);
    layout_->addWidget(knightButton_);
}

char PromoteGui::getPromotionPiece() const
{
    return promotionPiece_;
}

void PromoteGui::connectButtons()
{
    connect(queenButton_, SIGNAL(clicked()), this, SLOT(onQueenClicked()));
    connect(rookButton_, SIGNAL(clicked()), this, SLOT(onRookClicked()));
    connect(bishopButton_, SIGNAL(clicked()), this, SLOT(onBishopClicked()));
    connect(knightButton_, SIGNAL(clicked()), this, SLOT(onKnightClicked()));
}

void PromoteGui::onQueenClicked()
{
    promotionPiece_ = 'Q';
    accept();
}

void PromoteGui::onRookClicked()
{
    promotionPiece_ = 'R';
    accept();
}

void PromoteGui::onBishopClicked()
{
    promotionPiece_ = 'B';
    accept();
}

void PromoteGui::onKnightClicked()
{
    promotionPiece_ = 'N';
    accept();
}
