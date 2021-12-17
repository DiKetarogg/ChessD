#pragma once
#ifndef DTG_CHESS_CHESSCONSTANTS_HPP
#define DTG_CHESS_CHESSCONSTANTS_HPP
#endif
#include "ChessPiece.hpp"
namespace dtg::ChessConstants {
	extern const ChessPiece BP;
	extern const ChessPiece BR;
	extern const ChessPiece BN;
	extern const ChessPiece BB;
	extern const ChessPiece BK;
	extern const ChessPiece BQ;


	extern const ChessPiece WP;
	extern const ChessPiece WR;
	extern const ChessPiece WN;
	extern const ChessPiece WB;
	extern const ChessPiece WK;
	extern const ChessPiece WQ;

	extern const ChessPiece BPU;
	extern const ChessPiece BEN;
	extern const ChessPiece BRU;
	extern const ChessPiece BKU;

	extern const ChessPiece WPU;
	extern const ChessPiece WEN;
	extern const ChessPiece WRU;
	extern const ChessPiece WKU;

	extern const ChessPiece BLACKPAWN;
	extern const ChessPiece BLACKROOK;
	extern const ChessPiece BLACKKNIGHT;
	extern const ChessPiece BLACKBISHOP;
	extern const ChessPiece BLACKKING;
	extern const ChessPiece BLACKQUEEN;

	extern const ChessPiece BLACKPAWN_UNMOVED;
	extern const ChessPiece BLACK_ENPASSAT;
	extern const ChessPiece BLACKROOK_UNMOVED;
	extern const ChessPiece BLACKKING_UNMUVED;


	extern const ChessPiece WHITEPAWN;
	extern const ChessPiece WHITEROOK;
	extern const ChessPiece WHITEKNIGHT;
	extern const ChessPiece WHITEBISHOP;
	extern const ChessPiece WHITEKING;
	extern const ChessPiece WHITEQUEEN;

	extern const ChessPiece WHITEPAWN_UNMOVED;
	extern const ChessPiece WHITE_ENPASSAT;
	extern const ChessPiece WHITEROOK_UNMOVED;
	extern const ChessPiece WHITEKING_UNMUVED;

	extern const ChessPiece NO;
	
	extern const ChessPiece STANDART_POSITION[64];

	extern const uint8_t STANDART_WHITEKING_POSITION;
	extern const uint8_t STANDART_BLACKKING_POSITION;

	extern const uint8_t COLUMN[64];
	extern const uint8_t ROW[64];
	extern const uint8_t DIAGONAL[64];
	extern const uint8_t BDIAGONAL[64];
};
