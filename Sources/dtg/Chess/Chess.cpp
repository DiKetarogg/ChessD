#include <dtg/Chess.hpp>
namespace dtg {
	const ChessBoard& Chess::GetBoard() const noexcept {
		return m_Board;	
	}
	ChessBoard& Chess::GetBoard() noexcept {
		return m_Board;
	}
	bool Move(uint8_t from, uint8_t to) {
		if (m_Moves.empty()) {
			CalculateMoves();
		}
		if (m_Moves.find(ChessMove(from, to)) != m_Moves.end()) {
			return InternalMove(from, to);
		}
		return false;
	}
	void SwitchTurn() {
		whiteTurn = whiteTurn ? 0 : 1;	
	}
	/*	private:*/
	bool InternalMove(uint8_t from, uint8_t to) {
		switch(m_Board.GetPiece(from).GetType()) {
			case ChessPiece::Type::P:
				abs(ChessConstants)
		}
	}
	bool Chess::CheckUnderAttack(uint8_t from, ChessPiece::Color color){
		bool figure = 0;
		uint8_t figure_position;
		for(uint8_t i = from + 1; CheckXOutOfBounds(from, i); ++i){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::R:
							if(figure)
								Pinned[figure_position] = Chess::Pin::HORIZONTAL;
							else {
								for(uint8_t j = i; j < from; ++j){
									Pinned[j] = Chess::Pin::ATTACK;
								}
								attacks++;
							}
						default:;
					}
				}
				else{
					if(figure){
						Pinned[figure_position] = Chess::Pin::CHECK;
						Pinned[i] = Chess::Pin::CHECK;
					}
					else{
						figure_position = i;
						figure = 1;
					}
				}
			}
		}
		figure = 0;
		for(uint8_t i = from - 1; CheckXOutOfBounds(from, i); --i){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::R:
							if(figure)
								Pinned[figure_position] = Chess::Pin::HORIZONTAL;
							else {
								for(uint8_t j = i; j < from; ++j){
									Pinned[j] = Chess::Pin::ATTACK;
								}
								attacks++;
							}
						default:;
					}
				}
				else{
					if(figure){
						Pinned[figure_position] = Chess::Pin::CHECK;
						Pinned[i] = Chess::Pin::CHECK;
					}
					else{
						figure_position = i;
						figure = 1;
					}
				}
			}
		}
		figure = 0;
		for(uint8_t i = from + 8; CheckYOutOfBounds(from, i); i += 8){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::R:
							if(figure)
								Pinned[figure_position] = Chess::Pin::VERTICAL;
							else {
								for(uint8_t j = i; j < from; ++j){
									Pinned[j] = Chess::Pin::ATTACK;
								}
								attacks++;
							}
						default:;
					}
				}
				else{
					if(figure){
						Pinned[figure_position] = Chess::Pin::CHECK;
						Pinned[i] = Chess::Pin::CHECK;
					}
					else{
						figure_position = i;
						figure = 1;
					}
				}
			}
		}
		figure = 0;
		for(uint8_t i = from - 8; CheckYOutOfBounds(from, i); i -= 8){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::R:
							if(figure)
								Pinned[figure_position] = Chess::Pin::VERTICAL;
							else {
								for(uint8_t j = i; j < from; ++j){
									Pinned[j] = Chess::Pin::ATTACK;
								}
								attacks++;
							}
						default:;
					}
				}
				else{
					if(figure){
						Pinned[figure_position] = Chess::Pin::CHECK;
						Pinned[i] = Chess::Pin::CHECK;
					}
					else{
						figure_position = i;
						figure = 1;
					}
				}
			}
		}
		figure = 0;
		for(uint8_t i = from + 9; CheckXOutOfBounds(from, i); i += 9){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::B:
							if(figure)
								Pinned[figure_position] = Chess::Pin::DIAGONAL;
							else {
								for(uint8_t j = i; j < from; ++j){
									Pinned[j] = Chess::Pin::ATTACK;
								}
								attacks++;
							}
						default:;
					}
				}
				else{
					if(figure){
						Pinned[figure_position] = Chess::Pin::CHECK;
						Pinned[i] = Chess::Pin::CHECK;
					}
					else{
						figure_position = i;
						figure = 1;
					}
				}
			}
		}
		figure = 0;
		for(uint8_t i = from - 9; CheckXOutOfBounds(from, i); i -= 9){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::B:
							if(figure)
								Pinned[figure_position] = Chess::Pin::DIAGONAL;
							else {
								for(uint8_t j = i; j < from; ++j){
									Pinned[j] = Chess::Pin::ATTACK;
								}
								attacks++;
							}
						default:;
					}
				}
				else{
					if(figure){
						Pinned[figure_position] = Chess::Pin::CHECK;
						Pinned[i] = Chess::Pin::CHECK;
					}
					else{
						figure_position = i;
						figure = 1;
					}
				}
			}
		}
		figure = 0;
		for(uint8_t i = from + 7; CheckXOutOfBounds(from, i); i += 7){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::B:
							if(figure)
								Pinned[figure_position] = Chess::Pin::BDIAGONAL;
							else {
								for(uint8_t j = i; j < from; ++j){
									Pinned[j] = Chess::Pin::ATTACK;
								}
								attacks++;
							}
						default:;
					}
				}
				else{
					if(figure){
						Pinned[figure_position] = Chess::Pin::CHECK;
						Pinned[i] = Chess::Pin::CHECK;
					}
					else{
						figure_position = i;
						figure = 1;
					}
				}
			}
		}
		figure = 0;
		for(uint8_t i = from - 7; CheckXOutOfBounds(from, i); i -= 7){
			if(auto piece = m_Board.GetPiece(i)){
				if(piece.GetColor() != color){
					switch (piece.GetType()){
						case ChessPiece::Type::Q:
						case ChessPiece::Type::B:
							if(figure)
								Pinned[figure_position] = Chess::Pin::BDIAGONAL;
							else {
								for(uint8_t j = i; j < from; ++j){
									Pinned[j] = Chess::Pin::ATTACK;
								}
								attacks++;
							}
						default:;
					}
				}
				else{
					if(figure){
						Pinned[figure_position] = Chess::Pin::CHECK;
						Pinned[i] = Chess::Pin::CHECK;
					}
					else{
						figure_position = i;
						figure = 1;
					}
				}
			}
		}

		figure_position = from + 17;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				Pinned[figure_position] = Chess::Pin::ATTACK;
				++attacks;
			}
		}
		figure_position = from + 15;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				Pinned[figure_position] = Chess::Pin::ATTACK;
				++attacks;
			}
		}
		figure_position = from + 10;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				Pinned[figure_position] = Chess::Pin::ATTACK;
				++attacks;
			}
		}
		figure_position = from + 6;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				Pinned[figure_position] = Chess::Pin::ATTACK;
				++attacks;
			}
		}
		figure_position = from - 17;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				Pinned[figure_position] = Chess::Pin::ATTACK;
				++attacks;
			}
		}
		figure_position = from - 15;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				Pinned[figure_position] = Chess::Pin::ATTACK;
				++attacks;
			}
		}
		figure_position = from - 10;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				Pinned[figure_position] = Chess::Pin::ATTACK;
				++attacks;
			}
		}
		figure_position = from - 6;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				Pinned[figure_position] = Chess::Pin::ATTACK;
				++attacks;
			}
		}
		if (attacks > 0)
			return 0;
		else
			return 1;
	}

	inline void Chess::VerticalLane(uint8_t from, ChessPiece::Color color) {
		uint8_t to;
		for (to = from + 8; to < 64; to += 8) {
			if (!attacks && !m_Board.GetPiece(to))
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
				if(Pinned[from] == Chess::Pin::CHECK)
					CalculateWhitePawn(from);
				break;
			case ChessPiece::Type::R:
				switch (Pinned[from]) {
					case Chess::Pin::VERTICAL:
						VerticalLane(from, ChessPiece::Color::WHITE);
						break;
					case Chess::Pin::HORIZONTAL:
						HorizontalLane(from, ChessPiece::Color::WHITE);
						break;
					case Chess::Pin::CHECK:
						VerticalLane(from, ChessPiece::Color::WHITE);
						HorizontalLane(from, ChessPiece::Color::WHITE);
						break;
					default:;
				}
				break;
			case ChessPiece::Type::K:
				break;
			case ChessPiece::Type::N:
			if(Pinned[from] == Chess::Pin::CHECK)
					Knight(from, ChessPiece::Color::WHITE);
				break;
			case ChessPiece::Type::B:
			switch (Pinned[from]) {
				case Chess::Pin::DIAGONAL:
					DiagonalLane(from, ChessPiece::Color::WHITE);
					break;
				case Chess::Pin::BDIAGONAL:
					BackDiagonalLane(from, ChessPiece::Color::WHITE);
					break;
				case Chess::Pin::CHECK:
					DiagonalLane(from, ChessPiece::Color::WHITE);
					BackDiagonalLane(from, ChessPiece::Color::WHITE);
					break;
				default:;
			}
				break;
			case ChessPiece::Type::Q:
				switch (Pinned[from]) {
					case Chess::Pin::VERTICAL:
						VerticalLane(from, ChessPiece::Color::WHITE);
						break;
					case Chess::Pin::HORIZONTAL:
						HorizontalLane(from, ChessPiece::Color::WHITE);
						break;
					case Chess::Pin::DIAGONAL:
						DiagonalLane(from, ChessPiece::Color::WHITE);
						break;
					case Chess::Pin::BDIAGONAL:
						BackDiagonalLane(from, ChessPiece::Color::WHITE);
						break;
					case Chess::Pin::CHECK:
						VerticalLane(from, ChessPiece::Color::WHITE);
						HorizontalLane(from, ChessPiece::Color::WHITE);
						DiagonalLane(from, ChessPiece::Color::WHITE);
						BackDiagonalLane(from, ChessPiece::Color::WHITE);
						break;
					default:;
			}
				break;
			case ChessPiece::Type::NO:;
		}
	}

	void Chess::CalculateBlackPieceMoves(uint8_t from, ChessPiece::Type piece){
		switch(piece){
		case ChessPiece::Type::P:
			if(Pinned[from] == Chess::Pin::CHECK)
				CalculateBlackPawn(from);
			break;
		case ChessPiece::Type::R:
			switch (Pinned[from]) {
				case Chess::Pin::VERTICAL:
					VerticalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::HORIZONTAL:
					HorizontalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::CHECK:
					VerticalLane(from, ChessPiece::Color::BLACK);
					HorizontalLane(from, ChessPiece::Color::BLACK);
					break;
				default:;
			}
			break;
		case ChessPiece::Type::K:
			break;
		case ChessPiece::Type::N:
			if(Pinned[from] == Chess::Pin::CHECK)
				Knight(from, ChessPiece::Color::BLACK);
			break;
		case ChessPiece::Type::B:
			switch (Pinned[from]) {
				case Chess::Pin::DIAGONAL:
					DiagonalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::BDIAGONAL:
					BackDiagonalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::CHECK:
					DiagonalLane(from, ChessPiece::Color::BLACK);
					BackDiagonalLane(from, ChessPiece::Color::BLACK);
					break;
				default:;
		}
			break;
		case ChessPiece::Type::Q:
			switch (Pinned[from]) {
				case Chess::Pin::VERTICAL:
					VerticalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::HORIZONTAL:
					HorizontalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::DIAGONAL:
					DiagonalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::BDIAGONAL:
					BackDiagonalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::CHECK:
					VerticalLane(from, ChessPiece::Color::BLACK);
					HorizontalLane(from, ChessPiece::Color::BLACK);
					DiagonalLane(from, ChessPiece::Color::BLACK);
					BackDiagonalLane(from, ChessPiece::Color::BLACK);
					break;
				default:;
		}
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
		CheckUnderAttack(whiteKing, ChessPiece::Color::WHITE);
		for (uint8_t from = 0; from != 64; ++from) {
			piece = m_Board.GetPiece(from);
			if(piece && piece.GetColor() == ChessPiece::Color::WHITE) {
				CalculateWhitePieceMoves(from, piece.GetType());
			}
		}
	}
void Chess::CalculateBlackMoves() {
	ChessPiece piece;
	CheckUnderAttack(blackKing, ChessPiece::Color::BLACK);
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
