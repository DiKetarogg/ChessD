#include <dtg/Chess/ChessPiece.hpp>
namespace dtg {
	ChessPiece::ChessPiece(): data(NO){};
	ChessPiece::ChessPiece(const ChessPiece& other): data(other.data){};
	ChessPiece::ChessPiece(RawType data):data(data){};

	ChessPiece& ChessPiece::operator = (const ChessPiece& other) noexcept {
		data = other.data;
		return *this;
	}

	ChessPiece& ChessPiece::operator = (ChessPiece::RawType data) noexcept {
		this->data = data;
		return *this;
	}
	ChessPiece::operator bool () const noexcept {
		return data;
	}

	ChessPiece::RawType ChessPiece::GetRawType() const noexcept {
		return static_cast<RawType>(data & RAW_MASK);
	}

	uint8_t ChessPiece::GetRaw() const noexcept {
		return data;
	}

	ChessPiece::Piece ChessPiece::GetPiece() const noexcept {
		return static_cast<Piece>(data & PIECE_MASK);
	}

	ChessPiece::Color ChessPiece::GetColor() const noexcept {
		return static_cast<Color>(data & COLOR_MASK);
	}

	ChessPiece::Type ChessPiece::GetType() const noexcept {
		return static_cast<Type>(data & TYPE_MASK);
	}

	ChessPiece::Pin ChessPiece::GetPin() const noexcept {
		return static_cast<Pin>(data & PINNED_MASK);
	}

	ChessPiece::En ChessPiece::GetEnpassat() const noexcept {
		return static_cast<En>(data & ENPASSAT_MASK);
	}

	ChessPiece::Spec ChessPiece::GetSpecial() const noexcept {
		return static_cast<Spec>(data & SPECIAL_MASK);
	}

	bool ChessPiece::CanEnpassat() const noexcept {
		return static_cast<bool>(data & ENPASSAT_MASK);
	}

	bool ChessPiece::CanEnpassatRight() const noexcept {
		return static_cast<bool>((data & ENPASSAT_MASK) == ENR);
	}

	bool ChessPiece::CanEnpassatLeft() const noexcept {
		return (data & ENPASSAT_MASK) == ENL;
	}

	bool ChessPiece::Pinned() const noexcept {
		return data & PIN;
	}

	bool ChessPiece::IsPinned() const noexcept {
		return data & PIN;
	}
}
