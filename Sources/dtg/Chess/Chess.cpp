#include <dtg/Chess.hpp>
#include <iostream>
namespace dtg {
	static bool InboundsX(uint8_t from, uint8_t to) {
		return (from < 64 && to < 64) &&
		(ChessConstants::ROW[from] == ChessConstants::ROW[to]);
	}
	static bool InboundsY(uint8_t from, uint8_t to) {
		return (from < 64 && to < 64) &&
		(ChessConstants::COLUMN[from] == ChessConstants::COLUMN[to]);
	}
	static bool Indiagonal(uint8_t from, uint8_t to) {
		return (from < 64 && to < 64) &&
		(ChessConstants::DIAGONAL[from] == ChessConstants::DIAGONAL[to]);
	}
	static bool Inbackdiagonal(uint8_t from, uint8_t to) {
		return (from < 64 && to < 64) &&
		(ChessConstants::BDIAGONAL[from] == ChessConstants::BDIAGONAL[to]);
	}
	Chess::Chess():m_Board(ChessConstants::STANDART_POSITION),
	m_Pinned({NO_PIN}),
	m_WhiteKing(ChessConstants::STANDART_POSITION_WHITE_KING),
	m_BlackKing(ChessConstants::STANDART_POSITION_BLACK_KING),
	m_Attacks(0),
	m_WhiteTurn(true){}
	const ChessBoard& Chess::GetBoard() const noexcept {
		return m_Board;	
	}
	ChessBoard& Chess::GetBoard() noexcept {
		return m_Board;
	}
	bool Chess::Move(uint8_t fromx, uint8_t fromy, uint8_t tox, uint8_t toy) {
		return Move(fromy * 8 + fromx, toy * 8 + tox);
	}
	bool Chess::Move(uint8_t from, uint8_t to) {
		if (m_Moves.empty()) {
			CalculateMoves();
		}
		std::cout << ChessMove(from,to);
		uint16_t i = ChessMove(from,to);
		if (m_Moves.find(ChessMove(from, to)) != m_Moves.end()) {
			return MoveInternal(from, to);
		}
		return false;
	}
	void Chess::SwitchTurn() {
		m_WhiteTurn ^= 1;	
	}
	/*	private:*/
	bool Chess::MoveInternal(uint8_t from, uint8_t to) {
		switch (m_Board.GetPiece(from).GetType()) {
		case ChessPiece::Type::K:
			m_Board.Move(from, to);
			if (abs((int)ChessConstants::COLUMN[from] - ChessConstants::COLUMN[to]) > 1) {
				switch (ChessConstants::COLUMN[to]) {
					case 1:
						m_Board.Move(to - 1, to + 1);
						SwitchTurn();
						return true;
					case 2:
						m_Board.Move(to - 2, to + 1);
						SwitchTurn();
						return true;
					case 5:
						m_Board.Move(to + 2, to - 1);
						SwitchTurn();
						return true;
					case 6:
						m_Board.Move(to + 1, to - 1);
						SwitchTurn();
						return true;
				}
			}
			break;
		case ChessPiece::Type::P:
			if (ChessConstants::COLUMN[from] == ChessConstants::COLUMN[to]) {

			}
		}
		return false;
	}
	static bool CheckProtectedImplLane(ChessPiece piece) {
		switch(piece.GetType()) {
			case ChessPiece::Type::R:
			case ChessPiece::Type::Q:
			return true;
			case ChessPiece::Type::P:
			case ChessPiece::Type::N:
			case ChessPiece::Type::B:
			case ChessPiece::Type::K:
			default:;
		}
		return false;
	}
	static bool CheckProtectedImplDiagonal(ChessPiece piece) {
		switch(piece.GetType()) {
			case ChessPiece::Type::B:
			case ChessPiece::Type::Q:
			return true;
			case ChessPiece::Type::P:
			case ChessPiece::Type::N:
			case ChessPiece::Type::R:
			case ChessPiece::Type::K:
			default:;
		}
		return false;
	}
	void Chess::FillPins(uint8_t begin, uint8_t end, int inc, Pin pin) {
		for (;begin != end; begin += inc) {
			m_Pinned[begin] = pin;
		}
	}
	bool Chess::Protected(uint8_t from, ChessPiece::Color color) const {
		ChessPiece piece;
		for (uint8_t to = from + 1; InboundsX(from, to); to += 1) {
			if ((piece = m_Board.GetPiece(to)).GetColor() == color)
				return CheckProtectedImplLane(piece);
		}
		for (uint8_t to = from - 1; InboundsX(from, to); to -= 1) {
			if ((piece = m_Board.GetPiece(to)).GetColor() == color)
				return CheckProtectedImplLane(piece);
		}
		for (uint8_t to = from + 8; InboundsX(from, to); to += 8) {
			if ((piece = m_Board.GetPiece(to)).GetColor() == color)
				return CheckProtectedImplLane(piece);
		}
		for (uint8_t to = from - 8; InboundsX(from, to); to -= 8) {
			if ((piece = m_Board.GetPiece(to)).GetColor() == color)
				return CheckProtectedImplLane(piece);
		}

		for (uint8_t to = from - 9; Indiagonal(from, to); to -= 9) {
			if ((piece = m_Board.GetPiece(to)).GetColor() == color)
				return CheckProtectedImplLane(piece);
		}
		for (uint8_t to = from + 7; Inbackdiagonal(from, to); to += 7) {
			if ((piece = m_Board.GetPiece(to)).GetColor() == color)
				return CheckProtectedImplDiagonal(piece);
		}
		for (uint8_t to = from - 7; Inbackdiagonal(from, to); to -= 7) {
			if ((piece = m_Board.GetPiece(to)).GetColor() == color)
				return CheckProtectedImplDiagonal(piece);
		}
		return false;
	}
	bool __attribute__((always_inline))
	Chess::CalculateChecksIteration(CheckAgrs& args)
	{
		args.piece = m_Board.GetPiece(args.to);
		if (!args.piece)
			return true;
		if (args.piece.GetColor() == args.color) {
			if (args.found_friendly)
				return false;
			else args.found_friendly = true;
		} else {
			if (args.found_friendly)
				m_Pinned[args.friendly_location] = Pin::HORIZONTAL;
			else {
				FillPins(args.from, args.to, args.inc, Pin::ATTACK);
				m_Pinned[args.to] = Pin::CHECK;
				++m_Attacks;
			}
			return false;
		}

		return true;
	}
	void __attribute__((always_inline)) Chess::CalculateChecksIterate(CheckAgrs& args) {
		for (args.to = args.from + args.inc; InboundsX(args.from, args.to) &&
			CalculateChecksIteration(args); args.to += args.inc) {
		}
		args.found_friendly = 0;
		args.friendly_location = 0;
	}//
	void Chess::CalculateChecksKnight(uint8_t pos, ChessPiece::Color color) {
		if (m_Board.GetPiece(pos).GetPiece() == ChessPiece::Piece::N &&
		m_Board.GetPiece(pos).GetColor() != color)
		{
			m_Pinned[pos] = CHECK;
			++m_Attacks;
		}
	}
	void Chess::CalculateChecks(uint8_t from, ChessPiece::Color color) {
		CheckAgrs args = {from, 0, ChessConstants::NO, color, 0, 0, 1};
		CalculateChecksIterate(args);
		args.inc = -1;
		CalculateChecksIterate(args);
		args.inc = 8;
		CalculateChecksIterate(args);
		args.inc = -8;
		CalculateChecksIterate(args);
		args.inc = 9;
		CalculateChecksIterate(args);
		args.inc = -9;
		CalculateChecksIterate(args);
		args.inc = 7;
		CalculateChecksIterate(args);
		args.inc = -7;
		CalculateChecksIterate(args);
		if (ChessConstants::COLUMN[from] > 0) {
			if (ChessConstants::ROW[from] < 6)
				CalculateChecksKnight(from + 15, color);
			if (ChessConstants::ROW[from] > 1)
				CalculateChecksKnight(from - 17, color);
		}
		if (ChessConstants::COLUMN[from] > 1) {
			if (ChessConstants::ROW[from] < 7)
				CalculateChecksKnight(from + 6, color);
			if (ChessConstants::ROW[from] > 0)
				CalculateChecksKnight(from - 10, color);
		}
		if (ChessConstants::COLUMN[from] < 7) {
			if (ChessConstants::ROW[from] < 6)
				CalculateChecksKnight(from + 17, color);
			if (ChessConstants::ROW[from] > 1)
				CalculateChecksKnight(from - 15, color);
		}
		if (ChessConstants::COLUMN[from] < 6) {
			if (ChessConstants::ROW[from] < 7)
				CalculateChecksKnight(from + 10, color);
			if (ChessConstants::ROW[from] > 0)
				CalculateChecksKnight(from - 6, color);
		}
	}
#if 0
	bool Chess::CheckUnderAttack(uint8_t from, ChessPiece::Color color){
		bool figure = 0;
		uint8_t figure_position;
		for(uint8_t i = from + 1; InboundsX(from, i); ++i){
			auto piece = m_Board.GetPiece(i);
			if(piece && piece.GetColor() != color){
				switch (piece.GetType()){
					case ChessPiece::Type::Q:
					case ChessPiece::Type::R:
						if(figure)
							m_Pinned[figure_position] = Chess::Pin::HORIZONTAL;
						else {
							for(uint8_t j = i; j < from; ++j){
								m_Pinned[j] = Chess::Pin::ATTACK;
							}
							m_Attacks++;
						}
					default:;
				}
			}
			else{
				if(figure){
					m_Pinned[figure_position] = Chess::Pin::CHECK;
					m_Pinned[i] = Chess::Pin::CHECK;
				}
				else{
					figure_position = i;
					figure = 1;
				}
			}
		}
		figure = 0;
		for(uint8_t i = from - 1; InboundsX(from, i); --i){
			auto piece = m_Board.GetPiece(i);
			if(piece && piece.GetColor() != color){
				switch (piece.GetType()){
					case ChessPiece::Type::Q:
					case ChessPiece::Type::R:
						if(figure)
							m_Pinned[figure_position] = Chess::Pin::HORIZONTAL;
						else {
							for(uint8_t j = i; j < from; ++j){
								m_Pinned[j] = Chess::Pin::ATTACK;
							}
							m_Attacks++;
						}
					default:;
				}
			}
			else{
				if(figure){
					m_Pinned[figure_position] = Chess::Pin::CHECK;
					m_Pinned[i] = Chess::Pin::CHECK;
				}
				else{
					figure_position = i;
					figure = 1;
				}
			}
		}
		figure = 0;
		for(uint8_t i = from + 8; InboundsY(from, i); i += 8){
			auto piece = m_Board.GetPiece(i);
			if(piece && piece.GetColor() != color){
				switch (piece.GetType()){
					case ChessPiece::Type::Q:
					case ChessPiece::Type::R:
						if(figure)
							m_Pinned[figure_position] = Chess::Pin::VERTICAL;
						else {
							for(uint8_t j = i; j < from; ++j){
								m_Pinned[j] = Chess::Pin::ATTACK;
							}
							m_Attacks++;
						}
					default:;
				}
			}
			else{
				if(figure){
					m_Pinned[figure_position] = Chess::Pin::CHECK;
					m_Pinned[i] = Chess::Pin::CHECK;
				}
				else{
					figure_position = i;
					figure = 1;
				}
			}
		}
		figure = 0;
		for(uint8_t i = from - 8; InboundsY(from, i); i -= 8){
			auto piece = m_Board.GetPiece(i);
			if(piece && piece.GetColor() != color){
				switch (piece.GetType()){
					case ChessPiece::Type::Q:
					case ChessPiece::Type::R:
						if(figure)
							m_Pinned[figure_position] = Chess::Pin::VERTICAL;
						else {
							for(uint8_t j = i; j < from; ++j){
								m_Pinned[j] = Chess::Pin::ATTACK;
							}
							m_Attacks++;
						}
					default:;
				}
			}
			else{
				if(figure){
					m_Pinned[figure_position] = Chess::Pin::CHECK;
					m_Pinned[i] = Chess::Pin::CHECK;
				}
				else{
					figure_position = i;
					figure = 1;
				}
			}
		}
		figure = 0;
		for(uint8_t i = from + 9; InboundsX(from, i); i += 9){
			auto piece = m_Board.GetPiece(i);
			if(piece && piece.GetColor() != color){
				switch (piece.GetType()){
					case ChessPiece::Type::Q:
					case ChessPiece::Type::B:
						if(figure)
							m_Pinned[figure_position] = Chess::Pin::DIAGONAL;
						else {
							for(uint8_t j = i; j < from; ++j){
								m_Pinned[j] = Chess::Pin::ATTACK;
							}
							m_Attacks++;
						}
					default:;
				}
			}
			else{
				if(figure){
					m_Pinned[figure_position] = Chess::Pin::CHECK;
					m_Pinned[i] = Chess::Pin::CHECK;
				}
				else{
					figure_position = i;
					figure = 1;
				}
			}
		}
		figure = 0;
		for(uint8_t i = from - 9; InboundsX(from, i); i -= 9){
			auto piece = m_Board.GetPiece(i);
			if(piece && piece.GetColor() != color){
				switch (piece.GetType()){
					case ChessPiece::Type::Q:
					case ChessPiece::Type::B:
						if(figure)
							m_Pinned[figure_position] = Chess::Pin::DIAGONAL;
						else {
							for(uint8_t j = i; j < from; ++j){
								m_Pinned[j] = Chess::Pin::ATTACK;
							}
							m_Attacks++;
						}
					default:;
				}
			}
			else{
				if(figure){
					m_Pinned[figure_position] = Chess::Pin::CHECK;
					m_Pinned[i] = Chess::Pin::CHECK;
				}
				else{
					figure_position = i;
					figure = 1;
				}
			}
		}
		figure = 0;
		for(uint8_t i = from + 7; InboundsX(from, i); i += 7){
			auto piece = m_Board.GetPiece(i);
			if(piece && piece.GetColor() != color){
				switch (piece.GetType()){
					case ChessPiece::Type::Q:
					case ChessPiece::Type::B:
						if(figure)
							m_Pinned[figure_position] = Chess::Pin::BDIAGONAL;
						else {
							for(uint8_t j = i; j < from; ++j){
								m_Pinned[j] = Chess::Pin::ATTACK;
							}
							m_Attacks++;
						}
					default:;
				}
			}
			else{
				if(figure){
					m_Pinned[figure_position] = Chess::Pin::CHECK;
					m_Pinned[i] = Chess::Pin::CHECK;
				}
				else{
					figure_position = i;
					figure = 1;
				}
			}
		}
		figure = 0;
		for(uint8_t i = from - 7; InboundsX(from, i); i -= 7){
			auto piece = m_Board.GetPiece(i);
			if(piece && piece.GetColor() != color){
				switch (piece.GetType()){
					case ChessPiece::Type::Q:
					case ChessPiece::Type::B:
						if(figure)
							m_Pinned[figure_position] = Chess::Pin::BDIAGONAL;
						else {
							for(uint8_t j = i; j < from; ++j){
								m_Pinned[j] = Chess::Pin::ATTACK;
							}
							m_Attacks++;
						}
					default:;
				}
			}
			else{
				if(figure){
					m_Pinned[figure_position] = Chess::Pin::CHECK;
					m_Pinned[i] = Chess::Pin::CHECK;
				}
				else{
					figure_position = i;
					figure = 1;
				}
			}
		}
		figure_position = from + 17;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				m_Pinned[figure_position] = Chess::Pin::ATTACK;
				++m_Attacks;
			}
		}
		figure_position = from + 15;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				m_Pinned[figure_position] = Chess::Pin::ATTACK;
				++m_Attacks;
			}
		}
		figure_position = from + 10;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				m_Pinned[figure_position] = Chess::Pin::ATTACK;
				++m_Attacks;
			}
		}
		figure_position = from + 6;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				m_Pinned[figure_position] = Chess::Pin::ATTACK;
				++m_Attacks;
			}
		}
		figure_position = from - 17;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				m_Pinned[figure_position] = Chess::Pin::ATTACK;
				++m_Attacks;
			}
		}
		figure_position = from - 15;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				m_Pinned[figure_position] = Chess::Pin::ATTACK;
				++m_Attacks;
			}
		}
		figure_position = from - 10;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				m_Pinned[figure_position] = Chess::Pin::ATTACK;
				++m_Attacks;
			}
		}
		figure_position = from - 6;
		if(auto piece = m_Board.GetPiece(figure_position)){
			if(piece.GetType() == ChessPiece::Type::N && piece.GetColor() != color){
				m_Pinned[figure_position] = Chess::Pin::ATTACK;
				++m_Attacks;
			}
		}
		if (m_Attacks > 0)
			return 0;
		else
			return 1;
	}
#endif

	inline void Chess::VerticalLane(uint8_t from, ChessPiece::Color color) {
		uint8_t to;
		for (to = from + 8; to < 64; to += 8) {
			if (!m_Attacks && !m_Board.GetPiece(to))
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
		for (to = from + 1; InboundsX(from, to); to += 1) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
			if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
				m_Moves.insert(ChessMove(from, to));


		for (to = from - 1; InboundsX(from, to); to -= 1) {
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
		for (to = from + 7; InboundsX(from, to); to += 7) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
		if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
			m_Moves.insert(ChessMove(from, to));

		for (to = from - 7; InboundsX(from, to); to -= 7) {
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
		for (to = from + 9; InboundsX(from, to); to += 9) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
			if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
				m_Moves.insert(ChessMove(from, to));

		for (to = from - 9; InboundsX(from, to); to -= 9) {
			if (!m_Board.GetPiece(to))
				m_Moves.insert(ChessMove(from, to));
			else
				break;
		}
			if (to < 64 && m_Board.GetPiece(to).GetColor() != color)
				m_Moves.insert(ChessMove(from, to));
	}
	void Chess::KingMoves(ChessPiece::Color color){
		uint8_t from, to;
		if(color == ChessPiece::Color::WHITE)
			from = m_WhiteKing;
		else
			from = m_BlackKing;
		to = from + 1;
		if(!Protected(to, color))
			m_Moves.insert(ChessMove(from, to));
		to = from - 1;
		if(!Protected(to, color))
			m_Moves.insert(ChessMove(from, to));
		to = from + 8;
		if(!Protected(to, color))
			m_Moves.insert(ChessMove(from, to));
		to = from - 8;
		if(!Protected(to, color))
			m_Moves.insert(ChessMove(from, to));
		to = from + 9;
		if(!Protected(to, color))
			m_Moves.insert(ChessMove(from, to));
		to = from - 9;
		if(!Protected(to, color))
			m_Moves.insert(ChessMove(from, to));
		to = from + 7;
		if(!Protected(to, color))
			m_Moves.insert(ChessMove(from, to));
		to = from - 7;
		if(!Protected(to, color))
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

	void Chess::CalculateWhitePieceMoves(uint8_t from, ChessPiece::Type piece){
		switch(piece){
			case ChessPiece::Type::P:
				if(m_Pinned[from] == Chess::Pin::NO_PIN || m_Pinned[from] == Chess::Pin::VERTICAL)
					CalculatePawn(from);
				break;
			case ChessPiece::Type::R:
				switch (m_Pinned[from]) {
					case Chess::Pin::VERTICAL:
						VerticalLane(from, ChessPiece::Color::WHITE);
						break;
					case Chess::Pin::HORIZONTAL:
						HorizontalLane(from, ChessPiece::Color::WHITE);
						break;
					case Chess::Pin::NO_PIN:
						VerticalLane(from, ChessPiece::Color::WHITE);
						HorizontalLane(from, ChessPiece::Color::WHITE);
						break;
					default:;
				}
				break;
			case ChessPiece::Type::K:
				break;
			case ChessPiece::Type::N:
			if(m_Pinned[from] == Chess::Pin::NO_PIN)
					Knight(from, ChessPiece::Color::WHITE);
				break;
			case ChessPiece::Type::B:
			switch (m_Pinned[from]) {
				case Chess::Pin::DIAGONAL:
					DiagonalLane(from, ChessPiece::Color::WHITE);
					break;
				case Chess::Pin::BDIAGONAL:
					BackDiagonalLane(from, ChessPiece::Color::WHITE);
					break;
				case Chess::Pin::NO_PIN:
					DiagonalLane(from, ChessPiece::Color::WHITE);
					BackDiagonalLane(from, ChessPiece::Color::WHITE);
					break;
				default:;
			}
				break;
			case ChessPiece::Type::Q:
				switch (m_Pinned[from]) {
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
					case Chess::Pin::NO_PIN:
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
			if(m_Pinned[from] == Chess::Pin::NO_PIN || m_Pinned[from] == Chess::Pin::VERTICAL)
				CalculatePawn(from);
			break;
		case ChessPiece::Type::R:
			switch (m_Pinned[from]) {
				case Chess::Pin::VERTICAL:
					VerticalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::HORIZONTAL:
					HorizontalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::NO_PIN:
					VerticalLane(from, ChessPiece::Color::BLACK);
					HorizontalLane(from, ChessPiece::Color::BLACK);
					break;
				default:;
			}
			break;
		case ChessPiece::Type::K:
			break;
		case ChessPiece::Type::N:
			if(m_Pinned[from] == Chess::Pin::NO_PIN)
				Knight(from, ChessPiece::Color::BLACK);
			break;
		case ChessPiece::Type::B:
			switch (m_Pinned[from]) {
				case Chess::Pin::DIAGONAL:
					DiagonalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::BDIAGONAL:
					BackDiagonalLane(from, ChessPiece::Color::BLACK);
					break;
				case Chess::Pin::NO_PIN:
					DiagonalLane(from, ChessPiece::Color::BLACK);
					BackDiagonalLane(from, ChessPiece::Color::BLACK);
					break;
				default:;
		}
			break;
		case ChessPiece::Type::Q:
			switch (m_Pinned[from]) {
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
				case Chess::Pin::NO_PIN:
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

	void Chess::CalculatePawnForward(uint8_t from, uint8_t to) {
		if (!m_Board.GetPiece(to) && InboundsY(from, to))
			m_Moves.insert(ChessMove(from, to));
	}
	void Chess::CalculatePawnTake(uint8_t from, uint8_t to, ChessPiece::Color color) {
		to -= 1;
		if(InboundsX(from, to)) {
			auto piece = m_Board.GetPiece(to);
			if (piece && piece.GetColor() != color)
				m_Moves.insert(ChessMove(from, to));
		}
		to += 2;
		if (InboundsX(from, to)) {
			auto piece = m_Board.GetPiece(to);
			if (piece && piece.GetColor() != color)
				m_Moves.insert(ChessMove(from, to));
		}
	}

	void Chess::CalculatePawn(uint8_t from) {
		if (m_WhiteTurn) {
			CalculatePawnForward(from, from + 8);
			CalculatePawnTake(from, from + 8, ChessPiece::Color::WHITE);
			if (ChessConstants::ROW[from] == 1)
				CalculatePawnForward(from, from + 16);
		} else {

			CalculatePawnForward(from, from - 8);
			CalculatePawnTake(from, from - 8, ChessPiece::Color::BLACK);
			if (ChessConstants::ROW[from] == 6)
				CalculatePawnForward(from, from - 16);
		}

	}

	void Chess::CalculateWhiteMoves() {
		ChessPiece piece;
		CalculateChecks(m_WhiteKing, ChessPiece::Color::WHITE);
		if(m_Attacks > 1){
			KingMoves(ChessPiece::Color::WHITE);
		}
		else {
			for (uint8_t from = 0; from != 64; ++from) {
				piece = m_Board.GetPiece(from);
				if(piece && piece.GetColor() == ChessPiece::Color::WHITE) {
					CalculateWhitePieceMoves(from, piece.GetType());
				}
			}
		}
	}
	void Chess::CalculateBlackMoves() {
		ChessPiece piece;
		Protected(m_BlackKing, ChessPiece::Color::BLACK);
		if(m_Attacks > 1){
			KingMoves(ChessPiece::Color::BLACK);
		}
		else {
			for (uint8_t from = 0; from != 64; ++from){
				piece = m_Board.GetPiece(from);
				if(piece && piece.GetColor() == ChessPiece::Color::BLACK) {
					CalculateBlackPieceMoves(from, piece.GetType());
				}
			}
		}
	}
void Chess::CalculateMoves() {
	if (m_WhiteTurn)
		CalculateWhiteMoves();
	else
		CalculateBlackMoves();
}
}//dtg
