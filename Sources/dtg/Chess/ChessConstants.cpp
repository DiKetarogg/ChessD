#include <dtg/Chess/ChessConstants.hpp>
namespace dtg::ChessConstants {
	const ChessPiece BP = ChessPiece::BP;
	const ChessPiece BR = ChessPiece::BR;
	const ChessPiece BN = ChessPiece::BN;
	const ChessPiece BB = ChessPiece::BB;
	const ChessPiece BK = ChessPiece::BK;
	const ChessPiece BQ = ChessPiece::BQ;

	const ChessPiece WP = ChessPiece::WP;
	const ChessPiece WR = ChessPiece::WR;
	const ChessPiece WN = ChessPiece::WN;
	const ChessPiece WB = ChessPiece::WB;
	const ChessPiece WK = ChessPiece::WK;
	const ChessPiece WQ = ChessPiece::WQ;


	const ChessPiece BLACKPAWN   = BP;
	const ChessPiece BLACKROOK   = BR;
	const ChessPiece BLACKKNIGHT = BN;
	const ChessPiece BLACKBISHOP = BB;
	const ChessPiece BLACKKING   = BK;
	const ChessPiece BLACKQUEEN  = BQ;

	const ChessPiece WHITEPAWN   = WP;
	const ChessPiece WHITEROOK   = WR;
	const ChessPiece WHITEKNIGHT = WN;
	const ChessPiece WHITEBISHOP = WB;
	const ChessPiece WHITEKING   = WK;
	const ChessPiece WHITEQUEEN  = WQ;


	const ChessPiece NO = ChessPiece::NO;
		
	const ChessPiece STANDART_POSITION[64] {
		WR,  WN,  WB,  WQ,  WK,  WB,  WN,  WR,

		WP,  WP,  WP,  WP,  WP,  WP,  WP,  WP,

		NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,

		NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,

		NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,

		NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,

		BP,  BP,  BP,  BP,  BP,  BP,  BP,  BP,

		BR,  BN,  BB,  BQ,  BK,  BB,  BN,  BR,
	};

	const uint8_t STANDART_WHITEKING_POSITION = 60;
	const uint8_t STANDART_BLACKKING_POSITION = 4;
#if 0
		0,   1,   2,   3,   4,   5,   6,   7,
		8,   9,   10,  11,  12,  13,  14,  15,
		16,  17,  18,  19,  20,  21,  22,  23,
		24,  25,  26,  27,  28,  29,  30,  31,
		32,  33,  34,  35,  36,  37,  38,  39,
		40,  41,  42,  43,  44,  45,  46,  47,
		48,  49,  50,  51,  52,  53,  54,  55,
		56,  57,  58,  59,  60,  61,  62,  63
#endif

	const uint8_t COLUMN[64] {
		0,   1,   2,   3,   4,   5,   6,   7,
		0,   1,   2,   3,   4,   5,   6,   7,
		0,   1,   2,   3,   4,   5,   6,   7,
		0,   1,   2,   3,   4,   5,   6,   7,
		0,   1,   2,   3,   4,   5,   6,   7,
		0,   1,   2,   3,   4,   5,   6,   7,
		0,   1,   2,   3,   4,   5,   6,   7,
		0,   1,   2,   3,   4,   5,   6,   7
	};
	const uint8_t ROW[64] {
		0,   0,   0,   0,   0,   0,   0,   0,
		8,   8,   8,   8,   8,   8,   8,   8,
		16,  16,  16,  16,  16,  16,  16,  16,
		24,  24,  24,  24,  24,  24,  24,  24,
		32,  32,  32,  32,  32,  32,  32,  32,
		40,  40,  40,  40,  40,  40,  40,  40,
		48,  48,  48,  48,  48,  48,  48,  48,
		56,  56,  56,  56,  56,  56,  56,  56
	};
	const uint8_t BDIAGONAL[64] {
		0,   1,   2,   3,   4,   5,   6,   7,
		8,   0,   1,   2,   3,   4,   5,   6,
		16,  8,   0,   1,   2,   3,   4,   5,
		24,  16,  8,   0,   1,   2,   3,   4,
		32,  24,  16,  8,   0,   1,   2,   3,
		40,  32,  24,  16,  8,   0,   1,   2,
		48,  40,  32,  24,  16,  8,   0,   1,
		56,  48,  40,  32,  24,  16,  8,   0
	};
	const uint8_t DIAGONAL[64] {
		0,   1,   2,   3,   4,   5,   6,   7,
		1,   2,   3,   4,   5,   6,   7,   15,
		2,   3,   4,   5,   6,   7,   15,  23,
		3,   4,   5,   6,   7,   15,  23,  31,
		4,   5,   6,   7,   15,  23,  31,  39,
		5,   6,   7,   15,  23,  31,  39,  47,
		6,   7,   15,  23,  31,  39,  47,  55,
		7,   15,  23,  31,  39,  47,  55,  63
	};
} //namespace dtg::ChessConstants
