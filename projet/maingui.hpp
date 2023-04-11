#pragma once

#include "board.hpp"
#include "libraries.hpp"

class MainGui : public QMainWindow
{
	Q_OBJECT

public:
	MainGui(QWidget* parent = nullptr);
	~MainGui();

private:
	void makeBoard();
    void connectSignals();

	bool         isDark(const std::pair<int, int> coordinates) const;
	QPushButton* makeSquare(const std::pair<int, int> coordinates,
	                        const QString&            bgColor);
	QPushButton& getSquare(const std::pair<int, int> coordinates);
	void placePiece(const std::shared_ptr<Piece>& piece);
	void removePiece(QPushButton& square);

	QWidget*     boardWidget_;
	QGridLayout* boardLayout_;

	Board                  board_;
	std::shared_ptr<Piece> selectedPiece_ = nullptr;

private slots:
	void unHighlightSquares();
	void movePieceIfValid(std::pair<int, int> coordinates);
	void highlightSquare(std::pair<int, int> coordinates);
	void highlightValidMoves(std::pair<int, int> coordinates);

signals:
	void squareSelected(std::pair<int, int> coordinates);
};
