#include <dtg/Chess.hpp>
namespace dtg {
	const ChessBoard& Chess::GetBoard() const noexcept {
		return m_Board;
	}
	ChessBoard& Chess::GetBoard() noexcept {
		return m_Board;
	}
}//namespace dtg
