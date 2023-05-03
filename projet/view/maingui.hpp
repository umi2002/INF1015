#pragma once

#include "../model/pieces/bishop.hpp"
#include "../model/pieces/knight.hpp"
#include "../model/pieces/queen.hpp"
#include "../model/pieces/rook.hpp"
#include "boardgui.hpp"
#include "promotegui.hpp"

class MainGui : public QMainWindow
{
    Q_OBJECT

public:
    MainGui(QWidget* parent = nullptr);
    ~MainGui();

private:
    BoardGui*   boardGui_ = new BoardGui(this);
    PromoteGui* promoteGui_ = new PromoteGui(this);

private slots:
    void selectPromotionPiece(std::pair< int, int > coordinates, bool player);
};
