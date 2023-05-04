#include "positionsgui.hpp"

PositionsGui::PositionsGui(QWidget* parent) : QDialog(parent)
{
    using namespace fenPositions;

    layout_->addWidget(label_);
    layout_->addWidget(positionComboBox_);
    layout_->addWidget(selectButton_);

    positionComboBox_->addItem(STANDARD.first, STANDARD.second);
    positionComboBox_->addItem(ITALIAN.first, ITALIAN.second);
    positionComboBox_->addItem(SCOTCH.first, SCOTCH.second);
    positionComboBox_->addItem(VIENNA.first, VIENNA.second);

    connect(positionComboBox_,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(onPositionSelected(int)));
    connect(selectButton_, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

    QString fen = positionComboBox_->itemData(0).toString();
    selectedFen_ = fen.toStdString();
}

std::string PositionsGui::getFen() const
{
    return selectedFen_;
}

void PositionsGui::onPositionSelected(int index)
{
    QString fen = positionComboBox_->itemData(index).toString();
    selectedFen_ = fen.toStdString();
}

void PositionsGui::onButtonClicked()
{
    accept();
}
