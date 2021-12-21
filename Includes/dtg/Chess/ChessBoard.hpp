#pragma once
#ifndef DTG_CHESS_CHESSBOARD_HPP
#define DTG_CHESS_CHESSBOARD_HPP
#endif

#include <cstring>
#include "ChessPiece.hpp"
#include "ChessConstants.hpp"
namespace dtg {
	class ChessBoard {
		public:
			ChessBoard(const ChessPiece (&data)[64]) {
				memcpy(
				reinterpret_cast<void*>(this->data),
				reinterpret_cast<const void*>(data), sizeof(ChessPiece) * 64);
			}
			ChessBoard(const ChessBoard& data) {
				memcpy(
				reinterpret_cast<void*>(this->data),
				reinterpret_cast<const void*>(data.data), sizeof(ChessPiece) * 64);
			}
			ChessBoard() {

				memcpy(
				reinterpret_cast<void*>(this->data),
				reinterpret_cast<const void*>(ChessConstants::STANDART_POSITION),
				sizeof(ChessPiece) * 64);
			}

			inline void Move(uint8_t from, uint8_t to) {
				data[to] = data[from];
				data[from] = ChessPiece::NO;
			}

			inline ChessPiece GetPiece(uint8_t x, uint8_t y) const {
				return data[x * 8 + y];
			}

			inline ChessPiece GetPiece(uint8_t index) const {
				return data[index];
			}
			
			inline ChessPiece& GetPiece(uint8_t x, uint8_t y) {
				return data[x * 8 + y];
			}

			inline ChessPiece& GetPiece(uint8_t index) {
				return data[index];
			}

			inline void Remove(uint8_t index) {
				data[index] = ChessPiece::NO;
			}

			inline void SetPiece(uint8_t x, uint8_t y, ChessPiece piece) {
				data[x * 8 + y] = piece;;
			}

			inline void SetPiece(uint8_t index, ChessPiece piece) {
				data[index] = piece;
			}

			inline ChessPiece* operator [](uint8_t index) {
				return data + index * 8;
			}

			inline const ChessPiece* operator [](uint8_t index) const {
				return data + index * 8;
			}

			const inline ChessPiece* begin() const {
				return data;
			}

			const inline ChessPiece* end() const {
				return data + 64;
			}

			const inline ChessPiece* rbegin() const {
				return data + 63;
			}

			const inline ChessPiece* rend() const {
				return data - 1;
			}

			inline ChessPiece* begin() {
				return data;
			}

			inline ChessPiece* end() {
				return data + 64;
			}

			inline ChessPiece* rbegin() {
				return data + 63;
			}

			inline ChessPiece* rend() {
				return data - 1;
			}

			ChessBoard& operator=(const ChessBoard& other) {
				memcpy(
				reinterpret_cast<void*>(this->data),
				reinterpret_cast<const void*>(other.data), sizeof(ChessPiece) * 64);
				return *this;
			}

		private:
			ChessPiece data[64];
	};
}//namespace dtg
