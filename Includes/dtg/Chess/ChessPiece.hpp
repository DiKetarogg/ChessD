#pragma once
#ifndef DTG_CHESS_CHESSPIECE_HPP
#define DTG_CHESS_CHESSPIECE_HPP
#endif
#include <cstdint>
namespace dtg {
	class ChessPiece {
		public:
		enum RawType : uint8_t {
			NO     = 0,

			BLACK  = 0x0,
			WHITE  = 0x1,

			P      = 2,
			PAWN   = P,
			R      = 4,
			ROOK   = R,
			K      = 6,
			KING   = K,
			N      = 8,
			KNIGHT = N,
			B      = 10,
			BISHOP = B,
			Q      = 12,//0xC
			QUEEN  = Q,

			BP  = P  | BLACK,
			BR  = R  | BLACK,
			BK  = K  | BLACK,
			BN  = N  | BLACK,
			BB  = B  | BLACK,
			BQ  = Q  | BLACK,
			WP  = P  | WHITE,
			WR  = R  | WHITE,
			WK  = K  | WHITE,
			WN  = N  | WHITE,
			WB  = B  | WHITE,
			WQ  = Q  | WHITE,

			MOVED      = 0x10,

			PM      = MOVED | P,
			PAWNM   = MOVED | PAWN,
			RM      = MOVED | R,
			ROOKM   = MOVED | ROOK,
			KM      = MOVED | K,
			KINGM   = MOVED | KING,
			NM      = MOVED | N,
			KNIGHTM = MOVED | KNIGHT,
			BM      = MOVED | B,
			BISHOPM = MOVED | BISHOP,
			QM      = MOVED | Q,
			QUEENM  = MOVED | QUEEN,
			BPM = MOVED | BP,
			BRM = MOVED | BR,
			BKM = MOVED | BK,
			BNM = MOVED | BN,
			BBM = MOVED | BB,
			BQM = MOVED | BQ,
			WPM = MOVED | WP,
			WRM = MOVED | WR,
			WKM = MOVED | WK,
			WNM = MOVED | WN,
			WBM = MOVED | WB,
			WQM = MOVED | WQ,
		};//RawType
		enum Attribute : uint8_t {
			PINNED     = 0x20,
			PIN        = PINNED,
			SPECIAL1   = 0x40,
			SPEC1      = SPECIAL1,
			SPECIAL2   = 0x80,
			SPEC2      = SPECIAL2,
			PINV       = PIN | SPECIAL1,
			PINH       = PIN | SPECIAL2,
			ENPASSAT_LEFT  = SPECIAL1 | P,
			EN_LEFT        = ENPASSAT_LEFT,
			ENL            = EN_LEFT,
			ENPASSAT_RIGHT = SPECIAL2 | P,
			EN_RIGHT       = ENPASSAT_RIGHT,
			ENR            = EN_RIGHT
		};
		enum class Piece : uint8_t {
			BLACK  = RawType::BLACK,
			WHITE  = RawType::WHITE,
			NO     = RawType::NO,
			P      = RawType::P,
			PAWN   = RawType::PAWN,
			R      = RawType::R,
			ROOK   = RawType::ROOK,
			K      = RawType::K,
			KING   = RawType::KING,
			N      = RawType::N,
			KNIGHT = RawType::KNIGHT,
			B      = RawType::B,
			BISHOP = RawType::BISHOP,
			Q      = RawType::Q,//0xC
			QUEEN  = RawType::QUEEN,
			BP  = RawType::BP,
			BR  = RawType::BR,
			BK  = RawType::BK,
			BN  = RawType::BN,
			BB  = RawType::BB,
			BQ  = RawType::BQ,
//			BEN = RawType::BEN,
//			BPU = RawType::BPU,
//			BRU = RawType::BRU,
//			BKU = RawType::BKU,
			WP  = RawType::WP,
			WR  = RawType::WR,
			WK  = RawType::WK,
			WN  = RawType::WN,
			WB  = RawType::WB,
			WQ  = RawType::WQ,
//			WEN = RawType::WEN,
//			WPU = RawType::WPU,
//			WRU = RawType::WRU,
//			WKU = RawType::WKU
		};
		enum class Color : uint8_t {
			BLACK  = RawType::BLACK,
			B = BLACK,
			WHITE  = RawType::WHITE,
			W = WHITE
		};
		enum class Type : uint8_t {
			NO     = RawType::NO,
			P      = RawType::P,
			PAWN   = RawType::PAWN,
			R      = RawType::R,
			ROOK   = RawType::ROOK,
			K      = RawType::K,
			KING   = RawType::KING,
			N      = RawType::N,
			KNIGHT = RawType::KNIGHT,
			B      = RawType::B,
			BISHOP = RawType::BISHOP,
			Q      = RawType::Q,
			QUEEN  = RawType::QUEEN
		};
		enum class Pin : uint8_t {
			PINV     = Attribute::PINV,
			PINH     = Attribute::PINH,
		};
		enum class En : uint8_t {
			ENPASSAT_LEFT  = Attribute::ENPASSAT_LEFT,
			EN_LEFT        = Attribute::EN_LEFT,
			ENL            = Attribute::ENL,
			ENPASSAT_RIGHT = Attribute::ENPASSAT_RIGHT,
			EN_RIGHT       = Attribute::EN_RIGHT,
			ENR            = Attribute::ENR,
		};
		enum class Spec : uint8_t {
			SPECIAL1 = Attribute::SPECIAL1,
			SPEC1    = Attribute::SPEC1,
			SPECIAL2 = Attribute::SPECIAL2,
			SPEC2    = Attribute::SPEC2
		};
		public:
		ChessPiece();
		ChessPiece(const ChessPiece&);
		ChessPiece(RawType);

		ChessPiece& operator = (const ChessPiece&) noexcept;
		ChessPiece& operator = (RawType) noexcept;
		operator bool()const noexcept;
		public:
		RawType GetRawType() const noexcept;
		uint8_t GetRaw() const noexcept;
		Piece GetPiece() const noexcept;
		Color GetColor() const noexcept;
		Type GetType() const noexcept;
		Pin GetPin() const noexcept;
		En GetEnpassat() const noexcept;
		Spec GetSpecial() const noexcept;

		bool CanEnpassat() const noexcept;
		bool CanEnpassatRight() const noexcept;
		bool CanEnpassatLeft() const noexcept;
		bool Pinned() const noexcept;
		bool IsPinned() const noexcept;
		private:
		RawType data;
		static const uint8_t RAW_MASK      = 0x1F;
		static const uint8_t COLOR_MASK    = WHITE | BLACK;
		static const uint8_t TYPE_MASK     = P | R | K | N | B | Q;
		static const uint8_t PIECE_MASK    = TYPE_MASK | COLOR_MASK;
		static const uint8_t PINNED_MASK   = PIN | SPEC1 | SPEC2;
		static const uint8_t ENPASSAT_MASK = ENL | ENR;
		static const uint8_t SPECIAL_MASK  = SPEC1 | SPEC2;
};

}//namespace dtg




