#pragma once
#ifndef DTG_CHESS_HPP
#define DTG_CHESS_HPP
#endif
#include "Chess/ChessBoard.hpp"
#include "Chess/ChessConstants.hpp"
#include "Chess/ChessPiece.hpp"
#include "Chess/ChessMoveDecoder.hpp"
#include "Chess/NeuronsInput.hpp"
#include "Chess/PrintBoard.hpp"

#include <unordered_set>
namespace dtg {
	class Chess {
		private:
			enum Pin {
				NO_PIN,
				HORIZONTAL,
				VERTICAL,
				DIAGONAL,
				BDIAGONAL,
				ATTACK,
				CHECK
			};
		public:
			Chess();
		public:
			const ChessBoard& GetBoard() const noexcept;
			ChessBoard& GetBoard() noexcept;
			bool Move(uint8_t from, uint8_t to);
			bool Move(uint8_t fromx, uint8_t fromy, uint8_t tox, uint8_t toy);
			void SwitchTurn();
			const std::unordered_set<uint16_t>& GetMoves() const {
				return m_Moves;
			}
		private:
			struct CheckAgrs {
				uint8_t from;
				uint8_t to;
				ChessPiece piece;
				ChessPiece::Color color;
				bool found_friendly;
				uint8_t friendly_location;
				int inc;
			};
			bool MoveInternal(uint8_t from, uint8_t to);
			void FillPins(uint8_t begin, uint8_t end, int inc, Pin pin);
			bool __attribute__((always_inline))
			CalculateChecksIteration(CheckAgrs&);
			bool Protected(uint8_t from, ChessPiece::Color color) const;
			void __attribute__((always_inline)) CalculateChecksIterate(CheckAgrs& args);
			void CalculateChecksKnight(uint8_t pos, ChessPiece::Color color);
			void CalculateChecks(uint8_t from, ChessPiece::Color color);
			inline void VerticalLane(uint8_t from, ChessPiece::Color color);
			inline void HorizontalLane(uint8_t from, ChessPiece::Color color);
			inline void BackDiagonalLane(uint8_t from, ChessPiece::Color color);
			inline void DiagonalLane(uint8_t from, ChessPiece::Color color);
			inline void Knight(uint8_t from, ChessPiece::Color color);
		private:
			void CalculatePawnTake(uint8_t from, uint8_t to, ChessPiece::Color color);
			void CalculatePawnForward(uint8_t from, uint8_t to);
			void CalculatePawn(uint8_t from);
			void KingMoves(ChessPiece::Color color);
//			bool CheckUnderAttack(uint8_t from, ChessPiece::Color color);
//			bool InboundsX(uint8_t from, uint8_t to)const;
//			bool InboundsY(uint8_t from, uint8_t to)const;
			void CalculateWhitePieceMoves(uint8_t from, ChessPiece::Type piece);
			void CalculateBlackPieceMoves(uint8_t from, ChessPiece::Type piece);
			void CalculateWhiteMoves();
			void CalculateBlackMoves();
			void CalculateMoves();
			private:
			//State state;
			//uint8_t enpassat;
			std::unordered_set<uint16_t> m_Moves;
			ChessBoard m_Board;
			//	std::string history;
			Pin m_Pinned[64];
			uint8_t m_WhiteKing;
			uint8_t m_BlackKing;
			int m_Attacks;
			bool m_WhiteTurn = true;
			//static const uint8_t black_mask = 0x3;
			//static const uint8_t white_mask = 0xC;
	};
}
