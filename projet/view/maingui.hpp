#pragma once

#include "../model/pieces/bishop.hpp"
#include "../model/pieces/knight.hpp"
#include "../model/pieces/queen.hpp"
#include "../model/pieces/rook.hpp"
#include "boardgui.hpp"
#include "positionsgui.hpp"
#include "promotegui.hpp"

class MainGui : public QMainWindow
{
    Q_OBJECT

public:
    MainGui(QWidget* parent = nullptr);
    ~MainGui();

private:
    void makeMainGui();
    void connectSignals();

    QWidget*     mainGuiWidget_ = new QWidget(this);
    QVBoxLayout* mainGuiLayout_ = new QVBoxLayout(mainGuiWidget_);

    BoardGui*     boardGui_     = new BoardGui(this);
    PromoteGui*   promoteGui_   = new PromoteGui(this);
    PositionsGui* positionsGui_ = new PositionsGui(this);

    QWidget*     controlButtonsWidget_ = new QWidget(this);
    QHBoxLayout* controlButtonsLayout_ = new QHBoxLayout(controlButtonsWidget_);
    QPushButton* newButton_  = new QPushButton("New", controlButtonsWidget_);
    QPushButton* quitButton_ = new QPushButton("Quit", controlButtonsWidget_);

private slots:
    void makeNewGame();
    void selectPromotionPiece(std::pair< int, int > coordinates, bool player);
};
