#include <dtg/Chess.hpp>
#include <iostream>
namespace dtg {
std::ostream& operator <<(std::ostream& stream, const dtg::ChessMoveXY other) {
	if (other.piece != dtg::ChessPiece::Type::NO) {
		switch (other.piece) {
			case dtg::ChessPiece::Type::P:
				stream << "Pawn: ";
			break;
			case dtg::ChessPiece::Type::R:
				stream << "Rook: ";
			break;
			case dtg::ChessPiece::Type::N:
				stream << "Knight: ";
			break;
			case dtg::ChessPiece::Type::B:
				stream << "Bishop: ";
			break;
			case dtg::ChessPiece::Type::Q:
				stream << "Queen: ";
			break;
			case dtg::ChessPiece::Type::K:
				stream << "King: ";
			break;
			default:;
		}
	}
	if (other.fromx < 8)
	stream << "[fX: " << (char)('h' - other.fromx) << ']';
	if (other.fromy < 8)
	stream << "[fY: " << (char)(other.fromy + '1') << ']';
	if (other.tox < 8)
	stream << "[tX: " << (char)('h' - other.tox) << ']';
	if (other.toy < 8)
	stream << "[tY: " << (char)(other.toy + '1') << ']';
	return stream;
}

void printBoard(const dtg::ChessBoard& board) {
	const static char table[14] {
		'#', 'P', 'R', 'K', 'N', 'B', 'Q'
	};
	const static char white[] {
		"\033[34;47m"
	};
	const static char black[] {
		"\033[35;40m"
	};
	const static char reset[] {
		"\033[0m"
	};
	uint8_t color = 4;
	uint8_t oldColor = 4;
	bool someColor = false;
	uint8_t i = static_cast<uint8_t>(-1);
	uint8_t type;
	char row = '8';
	std::cout << "\n\t\t0:ABCDEFGH:0\n\t\t8:";
	for (int index = 56; index != -8; index -= 8)
	for (int inc = 0; inc != 8; ++inc)
	{
		const auto e = board.GetPiece(index + inc);
		if (++i == 8) {
			std::cout << reset << ':' << row;
			std::cout << "\n\t\t" << --row << ':';
			someColor = false;
			i = 0;
		}
		type = static_cast<uint8_t>(e.GetType()) >> 1;
		if (!type) {
			if (someColor) {
				std::cout << reset;
				someColor = false;
				oldColor = 4;
			}
		}
		else if ( ((color = static_cast<uint8_t>(e.GetColor())) != oldColor) ) {
			if (color)
				std::cout << white;
			else 
				std::cout << black;
			someColor = true;
		}
		std::cout << table[type];

	}
	std::cout << reset << ":1\n\t\t0:ABCDEFGH:0\n";
}
void printBoardInverted(const dtg::ChessBoard& board) {
	const static char table[14] {
		'#', 'P', 'R', 'K', 'N', 'B', 'Q'
	};
	const static char white[] {
		"\033[34;47m"
	};
	const static char black[] {
		"\033[35;40m"
	};
	const static char reset[] {
		"\033[0m"
	};
	uint8_t color = 4;
	uint8_t oldColor = 4;
	bool someColor = false;
	uint8_t i = static_cast<uint8_t>(-1);
	uint8_t type;
	char row = '1';
	std::cout << "\n\t\t0:HGFEDCBA:0\n\t\t1:";
	for (const auto& e : board) {
		if (++i == 8) {
			std::cout << reset << ':' << row;
			std::cout << "\n\t\t" << ++row << ':';
			someColor = false;
			i = 0;
		}
		type = static_cast<uint8_t>(e.GetType()) >> 1;
		if (!type) {
			if (someColor) {
				std::cout << reset;
				someColor = false;
				oldColor = 4;
			}
		}
		else if ( ((color = static_cast<uint8_t>(e.GetColor())) != oldColor) ) {
			if (color)
				std::cout << white;
			else 
				std::cout << black;
			someColor = true;
		}
		std::cout << table[type];

	}
	std::cout << reset << ":8\n\t\t0:HGFEDCBA:0\n";
}
}
