#pragma once

#include "../libraries.hpp"
#include "../model/constants.hpp"

class SquareGui : public QPushButton
{
    Q_OBJECT

public:
    SquareGui(const QString& bgColor, QWidget* parent = nullptr);
    ~SquareGui();
};
