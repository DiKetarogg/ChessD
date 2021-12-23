#pragma once
#ifndef DTG_CHESS_HPP
#define DTG_CHESS_HPP
#endif
#include "Chess/ChessBoard.hpp"
#include "Chess/ChessConstants.hpp"
#include "Chess/ChessPiece.hpp"
#include "Chess/ChessMoveDecoder.hpp"

#include <unordered_set>
namespace dtg {
	class Chess {
		private:
			enum Pin {
				HORIZONTAL,
				VERTICAL,
				DIAGONAL,
				BDIAGONAL,
				ATTACK,
				CHECK
			};
		public:
			const ChessBoard& GetBoard() const noexcept;
			ChessBoard& GetBoard() noexcept;
			bool Move(uint8_t from, uint8_t to);
			void SwitchTurn();
		private:
			bool MoveInternal(uint8_t from, uint8_t to);
			inline void VerticalLane(uint8_t from, ChessPiece::Color color);
			inline void HorizontalLane(uint8_t from, ChessPiece::Color color);
			inline void BackDiagonalLane(uint8_t from, ChessPiece::Color color);
			inline void DiagonalLane(uint8_t from, ChessPiece::Color color);
			inline void Knight(uint8_t from, ChessPiece::Color color);
		private:
			//bool KingUnderAttack(uint8_t from, ChessPiece::Color color);
			bool CheckUnderAttack(uint8_t from, ChessPiece::Color color);
			bool CheckXOutOfBounds(uint8_t from, uint8_t to)const;
			bool CheckYOutOfBounds(uint8_t from, uint8_t to)const;
			void CalculateWhitePieceMoves(uint8_t from, ChessPiece::Type piece);
			void CalculateBlackPieceMoves(uint8_t from, ChessPiece::Type piece);
			void CalculateWhitePawn(uint8_t from);
			void CalculateBlackPawn(uint8_t from);
			void CalculateWhiteMoves();
			void CalculateBlackMoves();
			void CalculateMoves();
			void CalculateChecks();
			//State state;
			//uint8_t enpassat;
			std::unordered_set<uint16_t> m_Moves;
			ChessBoard m_Board;
			//	std::string history;
			Pin Pinned[64];
			uint8_t whiteKing;
			uint8_t blackKing;
			short attacks;
			bool whiteTurn = true;
			//static const uint8_t black_mask = 0x3;
			//static const uint8_t white_mask = 0xC;
	};
}
