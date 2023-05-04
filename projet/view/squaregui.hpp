#pragma once

#include "../constants.hpp"
#include "../libraries.hpp"

class SquareGui : public QPushButton
{
    Q_OBJECT

public:
    SquareGui(const QString& bgColor, QWidget* parent = nullptr);
    ~SquareGui();
};
