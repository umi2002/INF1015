#pragma once

#include "../libraries.hpp"
#include "../constants.hpp"

class PositionsGui : public QDialog
{
    Q_OBJECT

public:
    PositionsGui(QWidget* parent = nullptr);

    std::string getFen() const;

private slots:
    void onPositionSelected(int index);
    void onButtonClicked();

private:
    QVBoxLayout* layout_ = new QVBoxLayout(this);
    QLabel* label_ = new QLabel("Choose a starting position:", this);
    QComboBox*   positionComboBox_ = new QComboBox(this);
    QPushButton* selectButton_ = new QPushButton("Select", this);
    std::string      selectedFen_;
};
