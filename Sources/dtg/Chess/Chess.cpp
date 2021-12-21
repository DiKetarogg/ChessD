#include <dtg/Chess.hpp>
namespace dtg {
	const ChessBoard& Chess::GetBoard() const noexcept {
		return m_Board;	
	}
	ChessBoard& Chess::GetBoard() noexcept {
		return m_Board;
	}
	/*	private:*/


	bool Chess::KingUnderAttack(uint8_t from, ChessPiece::Color color){
		for(uint8_t i = from + 1; CheckXOutOfBounds(from, i); ++i){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::R:
							return 0;
						default:;
					}
				}
			}
		}
		for(uint8_t i = from - 1; CheckXOutOfBounds(from, i); --i){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::R:
							return 0;
						default:;
					}
				}
			}
		}
		for(uint8_t i = from + 8; CheckYOutOfBounds(from, i); i += 8){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::R:
							return 0;
						default:;
					}
				}
			}
		}
		for(uint8_t i = from - 8; CheckYOutOfBounds(from, i); i -= 8){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::R:
							return 0;
						default:;
					}
				}
			}
		}
		for(uint8_t i = from + 7; CheckYOutOfBounds(from, i); i += 7){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::B:
							return 0;
						default:;
					}
				}
			}
		}
		for(uint8_t i = from - 7; CheckYOutOfBounds(from, i); i -= 7){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::B:
							return 0;
						default:;
					}
				}
			}
		}
		for(uint8_t i = from + 9; CheckYOutOfBounds(from, i); i += 9){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::B:
							return 0;
						default:;
					}
				}
			}
		}
		for(uint8_t i = from - 9; CheckYOutOfBounds(from, i); i -= 9){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::B:
							return 0;
						default:;
					}
				}
			}
		}
		uint8_t pos;
		if(color == ChessPiece::Color::WHITE){
			pos = from + 7;
			if(auto piece = m_Board.GetPiece(pos))
				if(pos < 64 && piece.GetType() == ChessPiece::Type::P && piece.GetColor() == ChessPiece::Color::BLACK)
					return 0;
			pos = from + 9;
			if(auto piece = m_Board.GetPiece(pos))
				if(pos < 64 && piece.GetType() == ChessPiece::Type::P && piece.GetColor() == ChessPiece::Color::BLACK)
					return 0;
		}
		else {
			pos = from - 7;
			if(auto piece = m_Board.GetPiece(pos))
				if(pos > 0 && piece.GetType() == ChessPiece::Type::P && piece.GetColor() == ChessPiece::Color::WHITE)
					return 0;
			pos = from - 9;
			if(auto piece = m_Board.GetPiece(pos))
				if(pos > 0 && piece.GetType() == ChessPiece::Type::P && piece.GetColor() == ChessPiece::Color::WHITE)
					return 0;
		}
		pos = from + 17;
		if(auto piece = m_Board.GetPiece(pos)){
			if(pos < 64 && piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color)
				return 0;
		}
		pos = from + 15;
		if(auto piece = m_Board.GetPiece(pos)){
			if(pos < 64 && piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color)
				return 0;
		}
		pos = from + 10;
		if(auto piece = m_Board.GetPiece(pos)){
			if(pos < 64 && piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color)
				return 0;
		}
		pos = from + 6;
		if(auto piece = m_Board.GetPiece(pos)){
			if(pos < 64 && piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color)
				return 0;
		}
		pos = from - 17;
		if(auto piece = m_Board.GetPiece(pos)){
			if(pos > 0 && piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color)
				return 0;
		}
		pos = from - 15;
		if(auto piece = m_Board.GetPiece(pos)){
			if(pos > 0 && piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color)
				return 0;
		}
		pos = from - 10;
		if(auto piece = m_Board.GetPiece(pos)){
			if(pos > 0 && piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color)
				return 0;
		}
		pos = from - 6;
		if(auto piece = m_Board.GetPiece(pos)){
			if(pos > 0 && piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color)
				return 0;
		}
		return 1;
	}



	inline void Chess::VerticalLane(uint8_t from, ChessPiece::Color color)
	{
		if(ChessConstants::ROW[color == ChessPiece::Color::WHITE ? whiteKing : blackKing]
				== ChessConstants::ROW[from])
		{
			if (whiteKing > from) {
				for (uint8_t i = from - 1; CheckXOutOfBounds(from, i); --i)
					if (auto piece = m_Board.GetPiece(i)) {
						if (piece.GetColor() != color) {
							switch (piece.GetType()) {
								case ChessPiece::Type::Q:
								case ChessPiece::Type::R:
									return;
								default:;
							}
						}
						break;
					}
			}

			else {
				for (uint8_t i = from + 1; CheckXOutOfBounds(from, i); ++i)
					if (auto piece = m_Board.GetPiece(i)) {
						if (piece.GetColor() != color) {
							switch (piece.GetType()) {
								case ChessPiece::Type::Q:
								case ChessPiece::Type::R:
									return;
								default:;
							}
						}
						break;
					}
			}
		}
		uint8_t to;
		for (to = from + 8; to < 64; to += 8) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
			if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
				m_Moves.insert(ChessMove(from, to));

		for (to = from - 8; to < 64; to -= 8) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
			if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
				m_Moves.insert(ChessMove(from, to));
			}
	inline void Chess::HorizontalLane(uint8_t from, ChessPiece::Color color) {
		if(ChessConstants::COLUMN[color == ChessPiece::Color::WHITE ? whiteKing : blackKing] == ChessConstants::COLUMN[from])
		{
			if (whiteKing > from) {
				for (uint8_t i = from - 1; CheckYOutOfBounds(from, i); --i)
					if (auto piece = m_Board.GetPiece(i)) {
						if (piece.GetColor() != color) {
							switch (piece.GetType()) {
								case ChessPiece::Type::Q:
								case ChessPiece::Type::R:
									return;
								default:;
							}
						}
						break;
					}
			}

			else {
				for (uint8_t i = from + 1; CheckYOutOfBounds(from, i); ++i)
					if (auto piece = m_Board.GetPiece(i)) {
						if (piece.GetColor() != color) {
							switch (piece.GetType()) {
								case ChessPiece::Type::Q:
								case ChessPiece::Type::R:
									return;
								default:;
							}
						}
						break;
					}
			}
		}
		uint8_t to;
		for (to = from + 1; CheckXOutOfBounds(from, to); to += 1) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
			if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
				m_Moves.insert(ChessMove(from, to));


		for (to = from - 1; CheckXOutOfBounds(from, to); to -= 1) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
			if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
				m_Moves.insert(ChessMove(from, to));

	}

	inline void Chess::BackDiagonalLane(uint8_t from, ChessPiece::Color color) {
		if(ChessConstants::COLUMN[color == ChessPiece::Color::WHITE ? whiteKing : blackKing] == ChessConstants::COLUMN[from])
		{
			if (whiteKing > from) {
				for (uint8_t i = from + 7; CheckYOutOfBounds(from, i); --i)
					if (auto piece = m_Board.GetPiece(i)) {
						if (piece.GetColor() != color) {
							switch (piece.GetType()) {
								case ChessPiece::Type::Q:
								case ChessPiece::Type::B: //R to B
									return;
								default:;
							}
						}
						break;
					}
			}

			else {
				for (uint8_t i = from - 7; CheckYOutOfBounds(from, i); ++i)
					if (auto piece = m_Board.GetPiece(i)) {
						if (piece.GetColor() != color) {
							switch (piece.GetType()) {
								case ChessPiece::Type::Q:
								case ChessPiece::Type::B: //R to B
									return;
								default:;
							}
						}
						break;
					}
			}
		}
		uint8_t to;
		for (to = from + 7; CheckXOutOfBounds(from, to); to += 7) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
		if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
			m_Moves.insert(ChessMove(from, to));

		for (to = from - 7; CheckXOutOfBounds(from, to); to -= 7) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
		if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
			m_Moves.insert(ChessMove(from, to));

	}

	inline void Chess::DiagonalLane(uint8_t from, ChessPiece::Color color) {
		if(ChessConstants::COLUMN[color == ChessPiece::Color::WHITE ? whiteKing : blackKing] == ChessConstants::COLUMN[from])
		{
			if (whiteKing > from) {
				for (uint8_t i = from + 9; CheckYOutOfBounds(from, i); --i)
					if (auto piece = m_Board.GetPiece(i)) {
						if (piece.GetColor() != color) {
							switch (piece.GetType()) {
								case ChessPiece::Type::Q:
								case ChessPiece::Type::B: //R to B
									return;
								default:;
							}
						}
						break;
					}
			}

			else {
				for (uint8_t i = from - 9; CheckYOutOfBounds(from, i); ++i)
					if (auto piece = m_Board.GetPiece(i)) {
						if (piece.GetColor() != color) {
							switch (piece.GetType()) {
								case ChessPiece::Type::Q:
								case ChessPiece::Type::B: //R to B
									return;
								default:;
							}
						}
						break;
					}
			}
		}
		uint8_t to;
		for (to = from + 9; CheckXOutOfBounds(from, to); to += 9) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
			if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
				m_Moves.insert(ChessMove(from, to));

		for (to = from - 9; CheckXOutOfBounds(from, to); to -= 9) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
			if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
				m_Moves.insert(ChessMove(from, to));
	}
	//16 +- 1
	inline void Chess::Knight(uint8_t from, ChessPiece::Color color) {
		uint8_t to = from + 17;
		if (to < 64 && ChessConstants::ROW[to - 16] == ChessConstants::ROW[from])
			if (m_Board.GetPiece(to).GetColor() != color)
				m_Moves.insert(ChessMove(from, to));
		to = from + 15;
		if (to < 64 && ChessConstants::ROW[to - 16] == ChessConstants::ROW[from])
			m_Moves.insert(ChessMove(from, to));

		to = from + 10;
		if (to < 64 && ChessConstants::ROW[to - 8] == ChessConstants::ROW[from])
			m_Moves.insert(ChessMove(from, to));

		to = from + 6;
		if (to < 64 && ChessConstants::ROW[to - 8] == ChessConstants::ROW[from])
			m_Moves.insert(ChessMove(from, to));
		to = from - 17;
		if (to < 64 && ChessConstants::ROW[to + 16] == ChessConstants::ROW[from])
			if (m_Board.GetPiece(to).GetColor() != color)
				m_Moves.insert(ChessMove(from, to));
		to = from - 15;
		if (to < 64 && ChessConstants::ROW[to + 16] == ChessConstants::ROW[from])
			m_Moves.insert(ChessMove(from, to));
		to = from - 6;
		if (to < 64 && ChessConstants::ROW[to + 8] == ChessConstants::ROW[from])
			m_Moves.insert(ChessMove(from, to));
		to = from -10;
		if (to < 64 && ChessConstants::ROW[to + 8] == ChessConstants::ROW[from])
			m_Moves.insert(ChessMove(from, to));
	}
//	private:
	bool Chess::CheckXOutOfBounds(uint8_t from, uint8_t to) const {
		return (from >= 64 && to >= 64) || (ChessConstants::ROW[from] != ChessConstants::ROW[to]);
	}
	bool Chess::CheckYOutOfBounds(uint8_t from, uint8_t to) const {
		return (from >= 64 && to >= 64) || (ChessConstants::COLUMN[from] != ChessConstants::COLUMN[to]);
	}
	void Chess::CalculateWhitePieceMoves(uint8_t from, ChessPiece::Type piece){
		switch(piece){
			case ChessPiece::Type::P:
				CalculateWhitePawn(from);
				break;
			case ChessPiece::Type::R:
				VerticalLane(from, ChessPiece::Color::WHITE);
				HorizontalLane(from, ChessPiece::Color::WHITE);
				break;
			case ChessPiece::Type::K:
				break;
			case ChessPiece::Type::N:
				Knight(from, ChessPiece::Color::WHITE);
				break;
			case ChessPiece::Type::B:
				DiagonalLane(from, ChessPiece::Color::WHITE);
				BackDiagonalLane(from, ChessPiece::Color::WHITE);
				break;
			case ChessPiece::Type::Q:
				VerticalLane(from, ChessPiece::Color::WHITE);
				HorizontalLane(from, ChessPiece::Color::WHITE);
				DiagonalLane(from, ChessPiece::Color::WHITE);
				BackDiagonalLane(from, ChessPiece::Color::WHITE);
				break;
			case ChessPiece::Type::NO:;
		}
	}

	void Chess::CalculateBlackPieceMoves(uint8_t from, ChessPiece::Type piece){
		switch(piece){
			case ChessPiece::Type::P:
				CalculateBlackPawn(from);
				break;
			case ChessPiece::Type::R:
				VerticalLane(from, ChessPiece::Color::BLACK);
				HorizontalLane(from, ChessPiece::Color::BLACK);
				break;
			case ChessPiece::Type::K:
				break;
			case ChessPiece::Type::N:
				Knight(from, ChessPiece::Color::BLACK);
				break;
			case ChessPiece::Type::B:
				DiagonalLane(from, ChessPiece::Color::BLACK);
				BackDiagonalLane(from, ChessPiece::Color::BLACK);
				break;
			case ChessPiece::Type::Q:
				VerticalLane(from, ChessPiece::Color::BLACK);
				HorizontalLane(from, ChessPiece::Color::BLACK);
				DiagonalLane(from, ChessPiece::Color::BLACK);
				BackDiagonalLane(from, ChessPiece::Color::BLACK);
				break;
			case ChessPiece::Type::NO:;
		}
	}

	void Chess::CalculateWhitePawn(uint8_t from){
		uint8_t to = from + 8;
		if (!m_Board.GetPiece(to) && !CheckYOutOfBounds(from, to))
			m_Moves.insert(ChessMove(from, to));
		to -= 1;
		if(!CheckXOutOfBounds(from, to)){
			auto piece = m_Board.GetPiece(to);
			if (piece && piece.GetColor() == ChessPiece::Color::BLACK)
				m_Moves.insert(ChessMove(from, to));
		}
		to += 2;
		if (!CheckXOutOfBounds(from, to)) {
			auto piece = m_Board.GetPiece(to);
			if (piece && piece.GetColor() == ChessPiece::Color::BLACK)
				m_Moves.insert(ChessMove(from, to));
		}
	}

	void Chess::CalculateBlackPawn(uint8_t from) {
		uint8_t to = from - 8;
		if (!m_Board.GetPiece(to) && !CheckYOutOfBounds(from, to))
			m_Moves.insert(ChessMove(from, to));
		to -= 1;
		if(!CheckXOutOfBounds(from, to)){
			auto piece = m_Board.GetPiece(to);
			if (piece && piece.GetColor() == ChessPiece::Color::WHITE)
				m_Moves.insert(ChessMove(from, to));
		}
		to += 2;
		if (!CheckXOutOfBounds(from, to)) {
			auto piece = m_Board.GetPiece(to);
			if (piece && piece.GetColor() == ChessPiece::Color::WHITE)
				m_Moves.insert(ChessMove(from, to));
		}
	}

	void Chess::CalculateWhiteMoves() {
		ChessPiece piece;
		for (uint8_t from = 0; from != 64; ++from) {
			piece = m_Board.GetPiece(from);
			if(piece && piece.GetColor() == ChessPiece::Color::WHITE) {
				CalculateWhitePieceMoves(from, piece.GetType());
			}
		}
	}
void Chess::CalculateBlackMoves() {
	ChessPiece piece;
	for (uint8_t from = 0; from != 64; ++from){
		piece = m_Board.GetPiece(from);
		if(piece && piece.GetColor() == ChessPiece::Color::BLACK) {
			CalculateBlackPieceMoves(from, piece.GetType());
		}
	}
}
void Chess::CalculateMoves() {
	if (whiteTurn)
		CalculateWhiteMoves();
	else
		CalculateBlackMoves();
}
}//dtg
