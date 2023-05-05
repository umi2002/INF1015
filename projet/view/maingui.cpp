/**
 * Programme qui implémente la vue d'un jeu d'échecs.
 * \file maingui.cpp
 * \author Hoang et Ibarissen
 * \date 5 mai 2023
 * Créé le 12 avril 2023
 */

#include "maingui.hpp"

MainGui::MainGui(QWidget* parent) : QMainWindow(parent)
{
    setFixedSize(square::SIZE * board::SIZE + controlButton::SIZE);
    makeMainGui();
    connectSignals();

    setCentralWidget(mainGuiWidget_);
    show();
}

MainGui::~MainGui() { }

void MainGui::makeMainGui()
{
    mainGuiWidget_->setLayout(mainGuiLayout_);
    mainGuiLayout_->addWidget(controlButtonsWidget_);
    mainGuiLayout_->addWidget(boardGui_);
    controlButtonsWidget_->setLayout(controlButtonsLayout_);
    controlButtonsLayout_->addWidget(newButton_);
    controlButtonsLayout_->addWidget(quitButton_);
}

void MainGui::connectSignals()
{
    QObject::connect(boardGui_,
                     SIGNAL(promotion(std::pair< int, int >, bool)),
                     this,
                     SLOT(selectPromotionPiece(std::pair< int, int >, bool)));
    QObject::connect(newButton_, SIGNAL(clicked()), this, SLOT(makeNewGame()));
    QObject::connect(quitButton_, SIGNAL(clicked()), this, SLOT(close()));
}

void MainGui::selectPromotionPiece(std::pair< int, int > coordinates,
                                   bool                  player)
{
    using std::shared_ptr, std::make_shared;

    promoteGui_->display(player);
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

void MainGui::makeNewGame()
{
    positionsGui_->exec();
    delete boardGui_;
    boardGui_ = new BoardGui(this, positionsGui_->getFen());
    connect(boardGui_,
            SIGNAL(promotion(std::pair< int, int >, bool)),
            this,
            SLOT(selectPromotionPiece(std::pair< int, int >, bool)));
    mainGuiLayout_->addWidget(boardGui_);
}
