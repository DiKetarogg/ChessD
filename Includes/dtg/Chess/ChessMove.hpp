#pragma once
#ifndef DTG_CHESS_CHESSMOVE_HPP
#define DTG_CHESS_CHESSMOVE_HPP
#endif

#include "ChessPiece.hpp"

namespace dtg {
	struct ChessMove {
		uint8_t from;
		uint8_t to;
	};

	struct ChessMoveXY {
		uint8_t fromx;
		uint8_t fromy;
		uint8_t tox;
		uint8_t toy;
		ChessPiece::Type piece;
	};
}
