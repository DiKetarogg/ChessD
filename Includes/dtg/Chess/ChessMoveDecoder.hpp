#pragma once
#ifndef DTG_CHESS_CHESSMOVEDECODER_HPP
#define DTG_CHESS_CHESSMOVEDECODER_HPP
#endif
#include "ChessBoard.hpp"
#include "ChessMove.hpp"
#include <string>
namespace dtg {
	class ChessMoveDecoder {
		public:
		ChessMoveDecoder() = delete;
		ChessMoveDecoder(const ChessMoveDecoder&);
		ChessMoveDecoder(const ChessBoard*);
		public:
		ChessMoveXY Decode(const char* str, bool white);
		ChessMoveXY Decode(const std::string& str, bool white);
		ChessMoveXY DecodeWhite(const char* str) const;
		ChessMoveXY DecodeWhite(const std::string& str) const;
		ChessMoveXY DecodeBlack(const char* str) const;
		ChessMoveXY DecodeBlack(const std::string& str) const;
		private:
		inline void VerticalLaneCheck(ChessMoveXY& move, ChessPiece::Piece target) const;
		inline void HorizontalLaneCheck(ChessMoveXY& move, ChessPiece::Piece target) const;
		inline void DiagonalLaneCheck(ChessMoveXY& move, ChessPiece::Piece target) const;
		inline void BackDiagonalLaneCheck(ChessMoveXY& move, ChessPiece::Piece target) const;
		inline void RookCheck(ChessMoveXY& move, ChessPiece::Piece target) const;
		inline void BishopCheck(ChessMoveXY& move, ChessPiece::Piece target) const;
		inline void KingCheck(ChessMoveXY& move, ChessPiece::Piece target) const;
		inline void KnightCheck(ChessMoveXY& move, ChessPiece::Piece target) const;
		inline bool Check(uint8_t x, uint8_t y, ChessMoveXY& move,
		ChessPiece::Piece target, bool ambiguos) const;
		inline void QueenCheck(ChessMoveXY& move, ChessPiece::Piece target) const;
		private:
		const ChessBoard* m_Board;
	};
	void ParseY(ChessMoveXY& move, char c);
	ChessMoveXY ParseMove(const char *str);
	ChessMoveXY Decode(const ChessBoard& board, const char *str);
	ChessMoveXY Decode(const ChessBoard& board, const std::string& str);
	int ParseCastle(const char *str);
}

