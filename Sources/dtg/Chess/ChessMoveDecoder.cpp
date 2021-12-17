#include <dtg/Chess/ChessMoveDecoder.hpp>
#include <cstring>
namespace dtg {
//CLASS -------------------
	ChessMoveDecoder::ChessMoveDecoder(const ChessMoveDecoder& other)
	:m_Board(other.m_Board){}
	ChessMoveDecoder::ChessMoveDecoder(const ChessBoard* other)
	:m_Board(other){}

	inline void ChessMoveDecoder::HorizontalLaneCheck
		(ChessMoveXY& move, ChessPiece::Piece target) const
	{
		ChessPiece::Piece type = ChessPiece::Piece::NO;
		if (move.toy != 0)
			for (uint8_t i = move.tox - 1; i != 255; --i) {
				type  = (*m_Board)[move.toy][i].GetPiece();
				if (type != ChessPiece::Piece::NO) {
					if (type == target) {
						move.fromy = move.toy;
						move.fromx = i;
					}
					break;
				}
			}
		bool ambiguos = type == target;
		for (uint8_t i = move.tox + 1; i < 8; ++i) {
			type  = (*m_Board)[move.toy][i].GetPiece();
			if (type != ChessPiece::Piece::NO) {
				if (type == target) {
					if (ambiguos)
						throw "ambiguos move";
					move.fromy = move.toy;
					move.fromx = i;
				}
				break;
			}
		}
	}
	inline void ChessMoveDecoder::VerticalLaneCheck(ChessMoveXY& move, ChessPiece::Piece target) const {
		ChessPiece::Piece type;
		if (move.toy != 0)
			for (uint8_t i = move.toy - 1; i != 255; --i) {
				type  = (*m_Board)[i][move.tox].GetPiece();
				if (type != ChessPiece::Piece::NO) {
					if (type == target) {
						move.fromy = i;
						move.fromx = move.tox;
					};
					break;
				}
			}
		bool ambiguos = type == target;
		for (uint8_t i = move.toy + 1; i < 8; ++i) {
			type  = (*m_Board)[i][move.tox].GetPiece();
			if (type != ChessPiece::Piece::NO) {
				if (type == target) {
					if (ambiguos)
						throw "ambiguos move";
					move.fromy = i;
					move.fromx = move.tox;
				}
				break;
			}
		}
	}

	inline void ChessMoveDecoder::BackDiagonalLaneCheck(ChessMoveXY& move, ChessPiece::Piece target) const {
		ChessPiece::Piece type;
		if (move.toy != 0 && move.tox != 0)
			for (uint8_t i = move.toy - 1, j = move.tox - 1; i != 255 && j != 255; --i, --j) {
				type  = (*m_Board)[i][j].GetPiece();
				if (type != ChessPiece::Piece::NO) {
					if (type == target) {
						move.fromy = i;
						move.fromx = j;
					};
					break;
				}
			}
		bool ambiguos = type == target;
		//Yeah, im too lazy to low optimize this.
		//Hope, compiler is smart enough to figure it out.
		for (uint8_t i = move.toy + 1, j = move.tox + 1; i < 8 && j < 8; ++i, ++j) {
			type  = (*m_Board)[i][j].GetPiece();
			if (type != ChessPiece::Piece::NO) {
				if (type == target) {
					if (ambiguos)
						throw "ambiguos move";
					move.fromy = i;
					move.fromx = j;
				}
				break;
			}
		}
	}

	inline void ChessMoveDecoder::DiagonalLaneCheck(ChessMoveXY& move, ChessPiece::Piece target) const {
		ChessPiece::Piece type;
		if (move.toy != 0 && move.tox != 0)
			for (uint8_t i = move.toy - 1, j = move.tox + 1; i != 255 && j != 255; --i, ++j) {
				type  = (*m_Board)[i][j].GetPiece();
				if (type != ChessPiece::Piece::NO) {
					if (type == target) {
						move.fromy = i;
						move.fromx = j;
					};
					break;
				}
			}
		bool ambiguos = type == target;
		//Yeah, im too lazy to low optimize this.
		//Hope, compiler is smart enough to figure it out.
		for (uint8_t i = move.toy + 1, j = move.tox - 1; i < 8 && j < 8; ++i, --j) {
			type  = (*m_Board)[i][j].GetPiece();
			if (type != ChessPiece::Piece::NO) {
				if (type == target) {
					if (ambiguos)
						throw "ambiguos move";
					move.fromy = i;
					move.fromx = j;
				}
				break;
			}
		}
	}

	inline void ChessMoveDecoder::RookCheck(ChessMoveXY& move, ChessPiece::Piece target) const {
		if (move.fromx < 8) {
			if (move.fromy < 8)
				return;
			VerticalLaneCheck(move, target);
		}
		else if (move.fromy < 8) {
			if (move.fromx < 8)
				return;
			HorizontalLaneCheck(move, target);
		}
		else {
			HorizontalLaneCheck(move, target);
			if (move.fromx > 7 || move.fromy > 7)
				VerticalLaneCheck(move, target);
		}
	}

	inline void ChessMoveDecoder::BishopCheck(ChessMoveXY& move, ChessPiece::Piece target) const {
		if (move.fromx < 8) {
			uint8_t temp = (move.fromx > move.tox) ?
				move.fromx - move.tox :
				move.tox - move.fromx;
			if (move.toy + temp < 8 && (*m_Board)[move.toy + temp][move.fromx].GetPiece() == target)
				move.fromy = move.toy + temp;
			if (move.toy > temp && (*m_Board)[move.toy - temp][move.fromx].GetPiece() == target) {
				if (move.fromy != 255)
					throw "ambiguos move";
				else
					move.fromy = move.toy - temp;
			}
		}
		else if (move.fromy < 8) {
			uint8_t temp = (move.fromy > move.toy) ?
				move.fromy - move.toy :
				move.toy - move.fromy;
			if (move.tox + temp < 8 && (*m_Board)[move.tox + temp][move.fromy].GetPiece() == target)
				move.fromx = move.tox + temp;
			if (move.tox > temp && (*m_Board)[move.tox - temp][move.fromy].GetPiece() == target) {
				if (move.fromx != 255)
					throw "ambiguos move";
				else
					move.fromx = move.tox - temp;
			}
		}
		else {
			DiagonalLaneCheck(move, target);
			if (move.fromx > 7 || move.fromy > 7)
				BackDiagonalLaneCheck(move, target);
		}
	}
	inline bool ChessMoveDecoder::Check(uint8_t x, uint8_t y,
	ChessMoveXY& move, ChessPiece::Piece target, bool ambiguos) const {
		if ((*m_Board)[y][x].GetPiece() == target) {
			move.fromx = x;
			move.fromy = y;
			if (ambiguos)
				throw "ambiguos move";
			return true;
		}
		return false;
	}
	inline void ChessMoveDecoder::KingCheck(ChessMoveXY& move, ChessPiece::Piece target) const {
		bool ambiguos = false;
		if (move.fromx < 8) {
			if (move.toy < 7)
				ambiguos |= Check(move.fromx, move.toy + 1, move, target, ambiguos);
			if (move.toy > 0)
				ambiguos |= Check(move.fromx, move.toy - 1, move, target, ambiguos);
			return;
		}
		if (move.fromy < 8) {
			if (move.tox < 7)
				ambiguos |= Check(move.tox + 1, move.fromy, move, target, ambiguos);
			if (move.tox > 0)
				ambiguos |= Check(move.tox - 1, move.fromy, move, target, ambiguos);
			return;
		}
		if (move.toy < 7)
			ambiguos |= Check(move.tox, move.toy + 1, move, target, ambiguos);
		if (move.toy > 0)
			ambiguos |= Check(move.tox, move.toy - 1, move, target, ambiguos);
		if (move.tox < 7) {
			ambiguos |= Check(move.tox + 1, move.toy, move, target, ambiguos);
			if (move.toy < 7)
				ambiguos |= Check(move.tox + 1, move.toy + 1, move, target, ambiguos);
			if (move.toy > 0)
				ambiguos |= Check(move.tox + 1, move.toy - 1, move, target, ambiguos);
		}
		if (move.tox > 0) {
			ambiguos |= Check(move.tox - 1, move.toy, move, target, ambiguos);
			if (move.toy < 7)
				ambiguos |= Check(move.tox - 1, move.toy + 1, move, target, ambiguos);
			if (move.toy > 0)
				ambiguos |= Check(move.tox - 1, move.toy - 1, move, target, ambiguos);
		}
	}
	inline void ChessMoveDecoder::KnightCheck(ChessMoveXY& move, ChessPiece::Piece target) const {
		bool ambiguos = false;
		if (move.fromx < 7) {
			int difference = abs(static_cast<int>(move.fromx) - static_cast<int>(move.tox));
			if (difference > 2)
				return;
			difference = difference == 2 ? 1 : 2;
			if (move.toy < 7 - difference)
				ambiguos |= Check(move.fromx, move.toy + difference, move, target, ambiguos);
			if (move.toy > difference)
				ambiguos |= Check(move.fromx, move.toy - difference, move, target, ambiguos);
			return;
		}
		if (move.fromy < 7) {
			int difference = abs(static_cast<int>(move.fromy) - static_cast<int>(move.toy));
			if (difference > 2)
				return;
			difference = difference == 2 ? 1 : 2;
			if (move.tox < 7 - difference)
				ambiguos |= Check(move.tox + difference, move.fromy, move, target, ambiguos);
			if (move.tox > difference)
				ambiguos |= Check(move.tox - difference, move.fromy, move, target, ambiguos);
			return;
		}
		if (move.tox > 0) {
			if (move.toy < 6)
				ambiguos |= Check(move.tox - 1, move.toy + 2, move, target, ambiguos);
			if (move.toy > 1)
				ambiguos |= Check(move.tox - 1, move.toy - 2, move, target, ambiguos);
		}
		if (move.tox > 1) {
			if (move.toy < 7)
				ambiguos |= Check(move.tox - 1, move.toy + 2, move, target, ambiguos);
			if (move.toy > 0)
				ambiguos |= Check(move.tox - 1, move.toy - 2, move, target, ambiguos);
		}
		if (move.tox < 7) {
			if (move.toy < 6)
				ambiguos |= Check(move.tox + 1, move.toy + 2, move, target, ambiguos);
			if (move.toy > 1)
				ambiguos |= Check(move.tox + 1, move.toy - 2, move, target, ambiguos);
		}
		if (move.tox < 6) {
			if (move.toy < 7)
				ambiguos |= Check(move.tox + 2, move.toy + 1, move, target, ambiguos);
			if (move.toy > 0)
				ambiguos |= Check(move.tox + 2, move.toy - 1, move, target, ambiguos);
		}
	}
	inline void ChessMoveDecoder::QueenCheck(ChessMoveXY& move, ChessPiece::Piece target) const {
		uint8_t fx = move.fromx;
		uint8_t fy = move.fromy;
		bool ambiguos;
		BishopCheck(move, target);
		if (move.fromx == 255 || move.fromy == 255)  {
			ambiguos = false;
			move.fromx = fx;
			move.fromy = fy;
		}
		else {
			fx = move.fromx;
			fy = move.fromy;
			ambiguos = true;
		}
		RookCheck(move, target);
		if (ambiguos && (move.fromx != fx || move.fromy != fy))
			throw "ambiguos move";
	}
	ChessMoveXY ChessMoveDecoder::DecodeWhite
		(const char *str) const {
		ChessMoveXY move;
		try {
			move = ParseMove(str);
		}
		catch (const char *exc) {
			if (!strcmp(exc, "invalid format")) {
				switch (ParseCastle(str)) {
					case 1:
					move.fromx = 4;
					move.tox = 6;
					move.fromy = 0;
					move.toy = 0;
					return move;
					case 2:
					move.fromx = 4;
					move.tox = 2;
					move.fromy = 0;
					move.toy = 0;
					return move;
				}
			}
			throw exc;
		}
		if (move.tox == 255 || move.toy == 255)
			throw "invalid format";
		if (move.fromx < 8 && move.fromy < 8)
			return move;
		ChessPiece::Piece type = ChessPiece::Piece::NO;
		switch (move.piece) {
			case ChessPiece::Type::P:
				if (move.fromx == 255)
					move.fromx = move.tox;
				if (move.fromx != move.tox) {
					move.fromy = move.toy + 1;
					break;
				}
				for (uint8_t i = 1; i != 3; ++i) {
					type = (*m_Board)[move.toy - i][move.fromx].GetPiece();
					if (type != ChessPiece::Piece::NO) {
						if (type == ChessPiece::Piece::WP)
							move.fromy = move.toy - i;
						break;
					}
				}
			break;
			case ChessPiece::Type::R:
				RookCheck(move, ChessPiece::Piece::WR);
			break;
			case ChessPiece::Type::N:
				KnightCheck(move, ChessPiece::Piece::WN);
			break;
			case ChessPiece::Type::B:
				BishopCheck(move, ChessPiece::Piece::WB);
			break;
			case ChessPiece::Type::Q:
			{

			}
			break;
			case ChessPiece::Type::K:
				KingCheck(move, ChessPiece::Piece::WK);
			break;
			default:
			throw "unexpected piece";
		}
		return move;
	}

	ChessMoveXY ChessMoveDecoder::DecodeBlack
	(const char *str) const {
		ChessMoveXY move = ParseMove(str);
		switch (move.piece) {
			case ChessPiece::Type::P:

			break;
			case ChessPiece::Type::R:

			break;
			case ChessPiece::Type::N:

			break;
			case ChessPiece::Type::B:

			break;
			case ChessPiece::Type::Q:

			break;
			case ChessPiece::Type::K:

			break;
			default:
			throw "unexpected piece";
		}
		return move;
	}

	ChessMoveXY ChessMoveDecoder::DecodeWhite
	(const std::string& str) const {
		ChessMoveXY move = ParseMove(str.c_str());
		return move;
	}

	ChessMoveXY ChessMoveDecoder::DecodeBlack
	(const std::string& str) const {
		ChessMoveXY move = ParseMove(str.c_str());
		return move;
	}
	//e4d5
	//eda invalid!!
	//ed41 invalid!!
	ChessMoveXY ChessMoveDecoder::Decode(const std::string& str, bool white) {
		return white ? DecodeWhite(str) : DecodeBlack(str);
	}

	ChessMoveXY ChessMoveDecoder::Decode(const char* str, bool white) {
		return white ? DecodeWhite(str) : DecodeBlack(str);
	}
	static ChessPiece::Type ObtainPiece(char c) {
		switch(c) {
			case 'p':
				return ChessPiece::Type::P;
				break;
			case 'r':
				return ChessPiece::Type::R;
				break;
			case 'n':
				return ChessPiece::Type::N;
				break;
			case 'b':
				return ChessPiece::Type::B;
				break;
			case 'q':
				return ChessPiece::Type::Q;
				break;
			case 'k':
				return ChessPiece::Type::K;
				break;
		}
		return ChessPiece::Type::NO;
	}

	//private:
	void ParseX(ChessMoveXY& move, char c) {
		c = tolower(c);
		if (c == 'x') {
			if (move.fromx == 255 && move.fromy == 255)
				throw "invalid format";
			return;
		}
		if (
			move.fromx == 255 &&
			move.tox == 255 &&
			move.piece == ChessPiece::Type::NO &&
			ObtainPiece(c) != ChessPiece::Type::NO
		) move.piece = ObtainPiece(c);

		else if (c >= 'a' && c <= 'h')
			if (move.fromx == 255)
				move.fromx = 'h' - c;
			else if (move.tox == 255) {

				move.tox = 'h' - c;
			}
			else throw "invalid format";

		else throw "invalid format";
	}
//	const ChessBoard* m_Board;
//CLASS END =========================
	int ParseCastle(const char *str) {
		for (;isspace(*str);++str);
		if (!*str)
			return 0;
		if (*str != '0')
			return 0;
		for (;isspace(*str);++str);
		if (*str != '0' && !isdigit(*str) && isprint(*str))
			++str;
		if (*str != '0')
			return 0;
		for (;isspace(*str);++str);
		if (*str != '0' && !isdigit(*str) && isprint(*str))
			++str;
		if (*str != '0')
			return 1;
		return 2;
	}

	void ParseY(ChessMoveXY& move, char c) {
		if (move.fromx != 255 || move.piece == ChessPiece::Type::NO) {
			if (move.tox != 255) {
				move.toy = c - '1';
				if (move.toy > 7)
					throw "invalid format";
			}
			else {
				move.fromy = c - '1';
				if (move.fromy > 7)
					throw "invalid format";
			}
		} else if (move.tox != 255) {
			move.toy = c - '1';
			if (move.toy > 7)
				throw "invalid format";
		} else throw "invalid format";
	}

	ChessMoveXY ParseMove(const char *str) {
		ChessMoveXY move  = {255, 255, 255, 255, ChessPiece::Type::NO};
		for (;isspace(*str);++str);
		if (!*str)
			throw "invalid format";
		do {
			if (isalpha(*str))
				ParseX(move, *str);
			else if (isdigit(*str))
				ParseY(move, *str);
			else throw "invalid format";
			++str;
		} while (*str);
		if (move.piece == ChessPiece::Type::NO)
			move.piece = ChessPiece::Type::P;
		if (move.tox == 255) {
			move.tox = move.fromx;
			move.toy = move.fromy;
			move.fromx = 255;
			move.fromy = 255;
		}
		return move;
	}

	ChessMoveXY Decode(const ChessBoard& board, const char *str);
	ChessMoveXY Decode(const ChessBoard& board, const std::string& str);
}//namespace dtg
