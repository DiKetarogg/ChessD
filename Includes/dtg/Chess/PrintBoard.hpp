#pragma once
#include <ostream>
#include "ChessBoard.hpp"
namespace dtg {
	std::ostream& operator <<(std::ostream& stream, const dtg::ChessMoveXY other);
	void printBoard(const dtg::ChessBoard& board);
	void printBoardInverted(const dtg::ChessBoard& board);
}
