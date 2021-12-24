#pragma once
#include "ChessBoard.hpp"
#include <cstdlib>
//#include <cstring>
//#include <cstdio>

#ifndef EVIL_COMMA_SEPARATOR
# define EVIL_COMMA_SEPARATOR ','
#endif

class NeuronsMoveInput {
	public:
	NeuronsMoveInput() {
		Clear();
		SetEvilCommas();
	}
	NeuronsMoveInput(uint8_t from, uint8_t to) {
		Clear();
		SetEvilCommas();
		ActivatePos(from, to);
	}
	void Clear() {
		for (int i = 0; i != 256; i += 2) {
			m_Data[i] = '0';
		}
	}
	void DeactivatePos(uint8_t from, uint8_t to) {
		m_Data[from * 2] = '0';
		m_Data[128 + to * 2] = '0';
	}
	void ActivatePos(uint8_t from, uint8_t to) {
		m_Data[from * 2] = '1';
		m_Data[128 + to * 2] = '1';
	}
	private:
	void SetEvilCommas() {
		for (int i = 1; i != 257; i += 2) {
			m_Data[i] = EVIL_COMMA_SEPARATOR;
		}

	}
	uint8_t m_Data[256];
};
#if 0
class NeuronsPieceInput {
	public:
		NeuronsPieceInput() = default;
		NeuronsPieceInput(dtg::ChessPiece piece) {
			*this = piece;
		}
		NeuronsPieceInput& operator = (dtg::ChessPiece piece) {
			switch(piece.GetPiece()) {
				case dtg::ChessPiece::Piece::BP:
					m_BlackPawn = '1';
					m_BlackRook = '0';
					m_BlackKnight = '0';
					m_BlackBishop = '0';
					m_BlackQueen= '0';
					m_BlackKing = '0';
					SetWhiteZero();
					break;
				case dtg::ChessPiece::Piece::BR:
					m_BlackPawn = '0';
					m_BlackRook = '1';
					m_BlackKnight = '0';
					m_BlackBishop = '0';
					m_BlackQueen= '0';
					m_BlackKing = '0';
					SetWhiteZero();
					break;
				case dtg::ChessPiece::Piece::BK:
					m_BlackPawn = '0';
					m_BlackRook = '0';
					m_BlackKnight = '0';
					m_BlackBishop = '0';
					m_BlackQueen= '0';
					m_BlackKing = '1';
					SetWhiteZero();
					break;
				case dtg::ChessPiece::Piece::BN:
					m_BlackPawn = '0';
					m_BlackRook = '0';
					m_BlackKnight = '1';
					m_BlackBishop = '0';
					m_BlackQueen= '0';
					m_BlackKing = '0';
					SetWhiteZero();
					break;
				case dtg::ChessPiece::Piece::BB:
					m_BlackPawn = '0';
					m_BlackRook = '0';
					m_BlackKnight = '0';
					m_BlackBishop = '1';
					m_BlackQueen= '0';
					m_BlackKing = '0';
					SetWhiteZero();
					break;
				case dtg::ChessPiece::Piece::BQ:
					m_BlackPawn = '0';
					m_BlackRook = '0';
					m_BlackKnight = '0';
					m_BlackBishop = '0';
					m_BlackQueen= '1';
					m_BlackKing = '0';
					SetWhiteZero();
					break;
				case dtg::ChessPiece::Piece::WP:
					m_WhitePawn = '1';
					m_WhiteRook = '0';
					m_WhiteKnight = '0';
					m_WhiteBishop = '0';
					m_WhiteQueen= '0';
					m_WhiteKing = '0';
					SetBlackZero();
					break;
				case dtg::ChessPiece::Piece::WR:
					m_WhitePawn = '0';
					m_WhiteRook = '1';
					m_WhiteKnight = '0';
					m_WhiteBishop = '0';
					m_WhiteQueen= '0';
					m_WhiteKing = '0';
					SetBlackZero();
					break;
				case dtg::ChessPiece::Piece::WK:
					m_WhitePawn = '0';
					m_WhiteRook = '0';
					m_WhiteKnight = '0';
					m_WhiteBishop = '0';
					m_WhiteQueen= '0';
					m_WhiteKing = '1';
					SetBlackZero();
					break;
				case dtg::ChessPiece::Piece::WN:
					m_WhitePawn = '0';
					m_WhiteRook = '0';
					m_WhiteKnight = '1';
					m_WhiteBishop = '0';
					m_WhiteQueen= '0';
					m_WhiteKing = '0';
					SetBlackZero();
					break;
				case dtg::ChessPiece::Piece::WB:
					m_WhitePawn = '0';
					m_WhiteRook = '0';
					m_WhiteKnight = '0';
					m_WhiteBishop = '1';
					m_WhiteQueen= '0';
					m_WhiteKing = '0';
					SetBlackZero();
					break;
				case dtg::ChessPiece::Piece::WQ:
					m_WhitePawn = '0';
					m_WhiteRook = '0';
					m_WhiteKnight = '0';
					m_WhiteBishop = '0';
					m_WhiteQueen= '1';
					m_WhiteKing = '0';
					SetBlackZero();
					break;
				case dtg::ChessPiece::Piece::NO:
				case dtg::ChessPiece::Piece::WHITE:
					SetBlackZero();
					SetWhiteZero();
			}
			return *this;
		}
	private:
		void SetBlackZero() {
			m_BlackPawn = '0';
			m_BlackRook = '0';
			m_BlackKnight = '0';
			m_BlackBishop = '0';
			m_BlackQueen= '0';
			m_BlackKing = '0';
		}
		void SetWhiteZero() {
			m_WhitePawn = '0';
			m_WhiteRook = '0';
			m_WhiteKnight = '0';
			m_WhiteBishop = '0';
			m_WhiteQueen= '0';
			m_WhiteKing = '0';
		}
	uint8_t m_BlackPawn;
	uint8_t m_EvilComma1 = EVIL_COMMA_SEPARATOR;
	uint8_t m_BlackRook;
	uint8_t m_EvilComma2 = EVIL_COMMA_SEPARATOR;
	uint8_t m_BlackKnight;
	uint8_t m_EvilComma3 = EVIL_COMMA_SEPARATOR;
	uint8_t m_BlackBishop;
	uint8_t m_EvilComma4 = EVIL_COMMA_SEPARATOR;
	uint8_t m_BlackQueen;
	uint8_t m_EvilComma5 = EVIL_COMMA_SEPARATOR;
	uint8_t m_BlackKing;
	uint8_t m_EvilComma6 = EVIL_COMMA_SEPARATOR;

	uint8_t m_WhitePawn;
	uint8_t m_EvilComma7 = EVIL_COMMA_SEPARATOR;
	uint8_t m_WhiteRook;
	uint8_t m_EvilComma8 = EVIL_COMMA_SEPARATOR;
	uint8_t m_WhiteKnight;
	uint8_t m_EvilComma9 = EVIL_COMMA_SEPARATOR;
	uint8_t m_WhiteBishop;
	uint8_t m_EvilCommaA = EVIL_COMMA_SEPARATOR;
	uint8_t m_WhiteQueen;
	uint8_t m_EvilCommaB = EVIL_COMMA_SEPARATOR;
	uint8_t m_WhiteKing;
	uint8_t m_EvilCommaC = EVIL_COMMA_SEPARATOR;
};
#else
class NeuronsPieceInput {
	public:
		NeuronsPieceInput() = default;
		NeuronsPieceInput(dtg::ChessPiece piece) {
			*this = piece;
		}
		NeuronsPieceInput& operator = (dtg::ChessPiece piece) {
			switch(piece.GetPiece()) {
				case dtg::ChessPiece::Piece::BP:
					m_Piece[0] = 'B';
					m_Piece[1] = 'P';
					m_Piece[2] = ',';
					break;
				case dtg::ChessPiece::Piece::BR:
					m_Piece[0] = 'B';
					m_Piece[1] = 'R';
					m_Piece[2] = ',';
					break;
				case dtg::ChessPiece::Piece::BK:
					m_Piece[0] = 'B';
					m_Piece[1] = 'K';
					m_Piece[2] = EVIL_COMMA_SEPARATOR;
					break;
				case dtg::ChessPiece::Piece::BN:
					m_Piece[0] = 'B';
					m_Piece[1] = 'N';
					m_Piece[2] = EVIL_COMMA_SEPARATOR;
					break;
				case dtg::ChessPiece::Piece::BB:
					m_Piece[0] = 'B';
					m_Piece[1] = 'B';
					m_Piece[2] = EVIL_COMMA_SEPARATOR;
					break;
				case dtg::ChessPiece::Piece::BQ:
					m_Piece[0] = 'B';
					m_Piece[1] = 'Q';
					m_Piece[2] = EVIL_COMMA_SEPARATOR;
					break;
				case dtg::ChessPiece::Piece::WP:
					m_Piece[0] = 'W';
					m_Piece[1] = 'P';
					m_Piece[2] = EVIL_COMMA_SEPARATOR;
					break;
				case dtg::ChessPiece::Piece::WR:
					m_Piece[0] = 'W';
					m_Piece[1] = 'R';
					m_Piece[2] = EVIL_COMMA_SEPARATOR;
					break;
				case dtg::ChessPiece::Piece::WK:
					m_Piece[0] = 'W';
					m_Piece[1] = 'K';
					m_Piece[2] = EVIL_COMMA_SEPARATOR;
					break;
				case dtg::ChessPiece::Piece::WN:
					m_Piece[0] = 'W';
					m_Piece[1] = 'N';
					m_Piece[2] = EVIL_COMMA_SEPARATOR;
					break;
				case dtg::ChessPiece::Piece::WB:
					m_Piece[0] = 'W';
					m_Piece[1] = 'B';
					m_Piece[2] = EVIL_COMMA_SEPARATOR;
					break;
				case dtg::ChessPiece::Piece::WQ:
					m_Piece[0] = 'W';
					m_Piece[1] = 'Q';
					m_Piece[2] = EVIL_COMMA_SEPARATOR;
					break;
				case dtg::ChessPiece::Piece::NO:
					m_Piece[0] = 'N';
					m_Piece[1] = 'O';
					m_Piece[2] = EVIL_COMMA_SEPARATOR;
					break;
				case dtg::ChessPiece::Piece::WHITE:
					break;
			}
			return *this;
		}
	private:
	char m_Piece[3];
};
#endif

class NeuronsBoardInput {
	public:
	NeuronsBoardInput(const dtg::ChessBoard& board) {
		int i = -1;
		for (const auto& e : board) {
			m_Sets[++i] = e;
		}
	}
	NeuronsPieceInput m_Sets[64];
};

class NeuronsInput {
	public:
	NeuronsInput(dtg::ChessBoard board, uint8_t from, uint8_t to, dtg::ChessPiece promote, float eval)
	:m_Board(board), m_Move(from, to), m_Promote(promote) {
		gcvt(eval, 255, m_EvilEval);
	}
	//evil operator
	operator const char *() const {
		return reinterpret_cast<const char *>(&m_Board);
	}
	private:
		NeuronsBoardInput m_Board;
		NeuronsMoveInput m_Move;
		NeuronsPieceInput m_Promote;
		char m_EvilEval[255];
};
