#include "maingui.hpp"

#include "constants.hpp"
#include "pieces/piece.hpp"

MainGui::MainGui(QWidget* parent) : QMainWindow(parent)
{
	this->setFixedSize(square::SIZE * board::SIZE);
	makeBoard();
	connectSignals();
	this->show();
}

MainGui::~MainGui() { }

void MainGui::makeBoard()
{
	boardWidget_ = new QWidget(this);
	boardLayout_ = new QGridLayout(boardWidget_);

	QString bgColor = "";
	for (int i : iter::range(board::SIZE))
	{
		for (int j : iter::range(board::SIZE))
		{
			bgColor = isDark({i, j}) ? square::DARK_BG : square::LIGHT_BG;
			QPushButton* square = makeSquare({i, j}, bgColor);
			boardLayout_->addWidget(square, i, j);

			const std::shared_ptr<Piece>& piece = board_.getPiece({i, j});
			placePiece(piece);
		}
		boardLayout_->setRowStretch(i, 1);
		boardLayout_->setColumnStretch(i, 1);
	}
	boardLayout_->setSpacing(0);
	boardLayout_->setContentsMargins(0, 0, 0, 0);

	boardWidget_->setLayout(boardLayout_);
	this->setCentralWidget(boardWidget_);
}

void MainGui::connectSignals()
{
	QObject::connect(this,
	                 SIGNAL(squareSelected(std::pair<int, int>)),
	                 this,
	                 SLOT(movePieceIfValid(std::pair<int, int>)));
	QObject::connect(this,
	                 SIGNAL(squareSelected(std::pair<int, int>)),
	                 this,
	                 SLOT(highlightSquare(std::pair<int, int>)));
	QObject::connect(this,
	                 SIGNAL(squareSelected(std::pair<int, int>)),
	                 this,
	                 SLOT(highlightValidMoves(std::pair<int, int>)));
}

bool MainGui::isDark(const std::pair<int, int> coordinates) const
{
	return (coordinates.first + coordinates.second) % 2 != 0;
}

QPushButton* MainGui::makeSquare(const std::pair<int, int> coordinates,
                                 const QString&            bgColor)
{
	QPushButton* square = new QPushButton();
	square->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	square->setFont(square::FONT);
	square->setFixedSize(square::SIZE);
	square->setStyleSheet(bgColor);
	QObject::connect(
		square, SIGNAL(clicked()), this, SLOT(unHighlightSquares()));
	QObject::connect(square,
	                 &QPushButton::clicked,
	                 [this, coordinates]
	                 {
						 emit squareSelected(coordinates);
						 selectedPiece_ = board_.getPiece(coordinates);
					 });
	return square;
}

QPushButton& MainGui::getSquare(const std::pair<int, int> coordinates)
{
	return *static_cast<QPushButton*>(
		boardLayout_->itemAtPosition(coordinates.first, coordinates.second)
			->widget());
}

void MainGui::placePiece(const std::shared_ptr<Piece>& piece)
{
	if (!piece)
	{
		return;
	}

	QPushButton& square = getSquare(piece->getCoordinates());
	square.setText(piece->getName());
}

void MainGui::removePiece(QPushButton& square)
{
	square.setText("");
}

void MainGui::unHighlightSquares()
{
	QString bgColor = "";
	for (int i : iter::range(board::SIZE))
	{
		for (int j : iter::range(board::SIZE))
		{
			QPushButton& square = getSquare({i, j});
			bgColor = isDark({i, j}) ? square::DARK_BG : square::LIGHT_BG;
			square.setStyleSheet(bgColor);
		}
	}
}

void MainGui::movePieceIfValid(std::pair<int, int> coordinates)
{
	if (!selectedPiece_)
	{
		return;
	}

	if (!board_.isTurn(selectedPiece_->getPlayer()))
	{
		return;
	}

	const std::pair<int, int> selectedPieceCoords =
		selectedPiece_->getCoordinates();
	const std::vector<std::pair<int, int>>& selectedPieceValidMoves =
		selectedPiece_->getValidMoves(board_);

	if (selectedPieceValidMoves.empty())
	{
		return;
	}
	auto validMovesIterator = std::find(selectedPieceValidMoves.begin(),
	                                    selectedPieceValidMoves.end(),
	                                    coordinates);
	bool isValidMove        = *validMovesIterator == coordinates;

	if (isValidMove)
	{
		QPushButton& selectedSquare = getSquare(selectedPieceCoords);
		board_.movePiece(selectedPiece_, coordinates);
		removePiece(selectedSquare);
		placePiece(selectedPiece_);
	}
}

void MainGui::highlightSquare(std::pair<int, int> coordinates)
{
	QPushButton& square = getSquare(coordinates);
	if (square.text() != "")
	{
		square.setStyleSheet(square::SELECTED_BG);
	}
}

void MainGui::highlightValidMoves(std::pair<int, int> coordinates)
{
	const std::shared_ptr<Piece>& piece = board_.getPiece(coordinates);
	if (!piece)
	{
		return;
	}

	if (!board_.isTurn(piece->getPlayer()))
	{
		return;
	}

	const std::vector<std::pair<int, int>>& validMoves =
		piece->getValidMoves(board_);

	for (const std::pair<int, int>& move : validMoves)
	{
		QPushButton& square = getSquare(move);
		square.setStyleSheet(square::VALID_MOVE_BG);
	}
}
