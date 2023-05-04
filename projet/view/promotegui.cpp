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

    makeSquares();
    connectSquares();

    layout_ = new QHBoxLayout(this);
    layout_->addWidget(queenButton_);
    layout_->addWidget(rookButton_);
    layout_->addWidget(bishopButton_);
    layout_->addWidget(knightButton_);
}

PromoteGui::~PromoteGui() { }

char PromoteGui::getPromotionPiece() const
{
    return promotionPiece_;
}

void PromoteGui::display(bool player)
{
    using namespace piece;

    if (player)
    {
        queenButton_->setText(WHITE_QUEEN);
        rookButton_->setText(WHITE_ROOK);
        bishopButton_->setText(WHITE_BISHOP);
        knightButton_->setText(WHITE_KNIGHT);
    }
    else
    {
        queenButton_->setText(BLACK_QUEEN);
        rookButton_->setText(BLACK_ROOK);
        bishopButton_->setText(BLACK_BISHOP);
        knightButton_->setText(BLACK_KNIGHT);
    }
    exec();
}

void PromoteGui::connectSquares()
{
    connect(queenButton_, SIGNAL(clicked()), this, SLOT(onQueenClicked()));
    connect(rookButton_, SIGNAL(clicked()), this, SLOT(onRookClicked()));
    connect(bishopButton_, SIGNAL(clicked()), this, SLOT(onBishopClicked()));
    connect(knightButton_, SIGNAL(clicked()), this, SLOT(onKnightClicked()));
}

void PromoteGui::makeSquares()
{
    using namespace square;

    queenButton_  = new SquareGui(LIGHT_BG, this);
    rookButton_   = new SquareGui(LIGHT_BG, this);
    bishopButton_ = new SquareGui(LIGHT_BG, this);
    knightButton_ = new SquareGui(LIGHT_BG, this);
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
