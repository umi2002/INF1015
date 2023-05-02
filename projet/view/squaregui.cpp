#include "squaregui.hpp"

SquareGui::SquareGui(const QString& bgColor, QWidget* parent) :
    QPushButton(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setFont(square::FONT);
    this->setFixedSize(square::SIZE);
    this->setStyleSheet(bgColor);
}

SquareGui::~SquareGui() { }
