/**
 * Programme qui implémente la vue d'un jeu d'échecs.
 * \file maingui.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "maingui.hpp"

MainGui::MainGui(QWidget* parent) : QMainWindow(parent)
{
    setFixedSize(square::SIZE * board::SIZE);

    QObject::connect(boardGui_,
                     SIGNAL(promotion(std::pair< int, int >, bool)),
                     this,
                     SLOT(selectPromotionPiece(std::pair< int, int >, bool)));

    setCentralWidget(boardGui_);
    show();
}

MainGui::~MainGui()
{
    delete boardGui_;
}

void MainGui::selectPromotionPiece(std::pair< int, int > coordinates,
                                   bool                  player)
{
    using std::shared_ptr, std::make_shared;

    promoteGui_->exec();
    char promotionPiece = promoteGui_->getPromotionPiece();

    switch (promotionPiece)
    {
        case 'Q' :
            boardGui_->addPiece< Queen >(coordinates, player);
            break;
        case 'R' :
            boardGui_->addPiece< Rook >(coordinates, player);
            break;
        case 'B' :
            boardGui_->addPiece< Bishop >(coordinates, player);
            break;
        case 'N' :
            boardGui_->addPiece< Knight >(coordinates, player);
            break;
        default :
            break;
    }
}
