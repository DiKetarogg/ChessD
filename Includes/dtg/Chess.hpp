#pragma once
#ifndef DTG_CHESS_HPP
#define DTG_CHESS_HPP
#endif
#include "Chess/ChessBoard.hpp"
#include "Chess/ChessConstants.hpp"
#include "Chess/ChessPiece.hpp"
#include "Chess/ChessMoveDecoder.hpp"
namespace dtg {
	class Chess {
		public:
		const ChessBoard& GetBoard() const noexcept;
		ChessBoard& GetBoard() noexcept;
		private:
		void CalculateWhitePieceMoves(uint8_t x, uint8_t y, ChessPiece::Piece piece)
		void CalculateWhiteMoves() {
			ChessPiece piece;
			for (uint8_t x = 0; x != 8; ++x) {
				for (uint8_t y = 0; y != 8; ++y) {
					piece = m_Board[y][x];
					if(piece && piece.GetColor() == ChessPiece::Color::WHITE) {
						CalculateWhitePieceMoves(x, y, piece);
					}
				}
			}
		}
		CalculateBlackMoves() {
			for (uint8_t x = 0; x != 8; ++x) {
				for (uint8_t y = 0; y != 8; ++y) {
					if(m_Board[y][x].GetPiece() != ChessPiece::Get) {

					}
				}
			}
		}
		CalculateMoves() {
			if (white_turn)
				CalculateWhiteMoves();
			else
				CalculateBlackMoves();
		}
		//State state;
		//uint8_t enpassat;
		std::unordered_set<ChessMoveXY> m_Moves;
		ChessBoard m_Board;
		//	std::string history;
		uint8_t white_king;
		uint8_t black_king;
		bool WhiteTurn = true;
		//static const uint8_t black_mask = 0x3;
		//static const uint8_t white_mask = 0xC;
	};
}
