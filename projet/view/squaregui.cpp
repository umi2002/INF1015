/**
 * Programme qui implémente l'affichage d'une case d'un échiquier.
 * \file squaregui.cpp
 * \author Hoang et Ibarissen
 * \date 5 mai 2023
 * Créé le 12 avril 2023
 */

#include "squaregui.hpp"

SquareGui::SquareGui(const QString& bgColor, QWidget* parent) :
    QPushButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFont(square::FONT);
    setFixedSize(square::SIZE);
    setStyleSheet(bgColor);
}

SquareGui::~SquareGui() { }
