#include <fstream>

void Move(std::ofstream& stream, int start, int end, const char *eval) {
	const char *pawn_b = "1.0,0.0,0.0,0.0,0.0,0.0,0.0";
	const char *pawn_w = "1.0,0.0,0.0,0.0,0.0,0.0,1.0";
	const char *rook_b = "0.0,1.0,0.0,0.0,0.0,0.0,0.0";
	const char *rook_w = "0.0,1.0,0.0,0.0,0.0,0.0,1.0";
	const char *knight_b = "0.0,0.0,1.0,0.0,0.0,0.0,0.0";
	const char *knight_w = "0.0,0.0,1.0,0.0,0.0,0.0,1.0";
	const char *bishop_b = "0.0,0.0,0.0,1.0,0.0,0.0,0.0";
	const char *bishop_w = "0.0,0.0,0.0,1.0,0.0,0.0,1.0";
	const char *queen_b = "0.0,0.0,0.0,0.0,1.0,0.0,0.0";
	const char *queen_w = "0.0,0.0,0.0,0.0,1.0,0.0,1.0";
	const char *king_b = "0.0,0.0,0.0,0.0,0.0,1.0,0.0";
	const char *king_w = "0.0,0.0,0.0,0.0,0.0,1.0,1.0";
	const char *empty = "0.0,0.0,0.0,0.0,0.0,0.0,0.0";

	stream << rook_w << ',';
	stream << knight_w << ',';
	stream << bishop_w << ',';
	stream << queen_w << ',';
	stream << king_w << ',';
	stream << bishop_w << ',';
	stream << knight_w << ',';
	stream << rook_w << ',';

	stream << pawn_w << ',';
	stream << pawn_w << ',';
	stream << pawn_w << ',';
	stream << pawn_w << ',';
	stream << pawn_w << ',';
	stream << pawn_w << ',';
	stream << pawn_w << ',';
	stream << pawn_w << ',';
	for (int i = 0; i != 32; ++i)
		stream << empty << ',';
	stream << rook_b << ',';
	stream << knight_b << ',';
	stream << bishop_b << ',';
	stream << queen_b << ',';
	stream << king_b << ',';
	stream << bishop_b << ',';
	stream << knight_b << ',';
	stream << rook_b << ',';

	stream << pawn_b << ',';
	stream << pawn_b << ',';
	stream << pawn_b << ',';
	stream << pawn_b << ',';
	stream << pawn_b << ',';
	stream << pawn_b << ',';
	stream << pawn_b << ',';
	stream << pawn_b;
	for (int i = 0; i != 64; ++i) {
		if (i == start)
			stream << ",1.0";
		else
			stream << ",0.0";
	}
	for (int i = 0; i != 64; ++i) {
		if (i == end)
			stream << ",1.0";
		else
			stream << ",0.0";
	}
	stream << "," << eval;
}

int main() {

	int start = 12;
	int end = 28;
	std::ofstream stream("chess_game.csv");
	stream << "pos_1_p,";
	stream << "pos_1_r,";
	stream << "pos_1_n,";
	stream << "pos_1_b,";
	stream << "pos_1_q,";
	stream << "pos_1_k,";
	stream << "white_1";
	for (int i = 2; i != 65; ++i) {
		stream << ",pos_" << i << "_p";
		stream << ",pos_" << i << "_r";
		stream << ",pos_" << i << "_n";
		stream << ",pos_" << i << "_b";
		stream << ",pos_" << i << "_q";
		stream << ",pos_" << i << "_k";
		stream << ",white_" << i;
	}
	for (int i = 1; i != 65; ++i) {
		stream << ",from_" << i;
	}
	for (int i = 1; i != 65; ++i) {
		stream << ",to_" << i;
	}
	stream << ",evaluation\n";
	Move(stream, 12, 28, "0.7");
	stream << '\n';
	Move(stream, 11, 27, "0.67");
	stream << '\n';
	Move(stream, 10, 26, "0.5");
}
