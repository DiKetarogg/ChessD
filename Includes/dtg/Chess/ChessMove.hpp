#pragma once
#ifndef DTG_CHESS_CHESSMOVE_HPP
#define DTG_CHESS_CHESSMOVE_HPP
#endif

#include "ChessPiece.hpp"

namespace dtg {
	struct ChessMove {
		ChessMove(uint8_t from, uint8_t to):from(from), to(to){}
		ChessMove(uint16_t t){
			*this = t;	
		}
		ChessMove& operator = (const uint16_t t) {
			*reinterpret_cast<uint16_t*>(&from) = t;
			return *this;
		}
		operator uint16_t&() {
			return *reinterpret_cast<uint16_t*>(&from);
		}
		operator const uint16_t&() const {
			return *reinterpret_cast<const uint16_t*>(&from);
		}
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
