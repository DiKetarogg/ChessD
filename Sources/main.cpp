#if 1
#include <iostream>
#include <dtg/Chess.hpp>
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
/*
int main() {
	dtg::Chess game;
	dtg::ChessBoard& board = game.GetBoard();
	dtg::ChessMoveDecoder decoder(&game.GetBoard());
	board[6][5] = dtg::ChessPiece::WB;
	printBoard(board);
	dtg::ChessMoveXY s0;
	dtg::ChessMoveXY s1;
	dtg::ChessMoveXY s2;
	dtg::ChessMoveXY s3;
	dtg::ChessMoveXY s4;
	dtg::ChessMoveXY s5;
	try {
		s0 = decoder.DecodeWhite("ee4");
		s1 = decoder.DecodeWhite("e4");
		s2 = decoder.DecodeWhite("ba5");
		s3 = decoder.DecodeWhite("kd2");
		s4 = decoder.DecodeWhite("ra2");
		s5 = decoder.DecodeWhite("nh3");
	}
	catch(const char *s) {
		std::cout << "Exception: " << s << '\n';
	}
	std::cout << s0 << '\n';
	std::cout << s1 << '\n';
	std::cout << s2 << '\n';
	std::cout << s3 << '\n';
	std::cout << s4 << '\n';
	std::cout << s5 << '\n';
	board[s0.toy][s0.tox] = dtg::ChessPiece::BP;
	printBoard(board);
	printBoardInverted(board);
	std::cout << "---------------------------------\n\n";
	
	try {
		s0 = decoder.DecodeBlack("ee5");
		s1 = decoder.DecodeBlack("e5");
		s2 = decoder.DecodeBlack("ba5");
		s3 = decoder.DecodeBlack("kd7");
		s4 = decoder.DecodeBlack("ra7");
		s5 = decoder.DecodeBlack("nh5");
	}
	catch(const char *s) {
		std::cout << "Exception: " << s << '\n';
	}
	std::cout << s0 << '\n';
	std::cout << s1 << '\n';
	std::cout << s2 << '\n';
	std::cout << s3 << '\n';
	std::cout << s4 << '\n';
	std::cout << s5 << '\n';
	board[s0.toy][s0.tox] = dtg::ChessPiece::BP;
	printBoard(board);
}
*/
#include <string>
int main() {
	dtg::Chess game;
	//game.CalculateMoves();
	dtg::ChessBoard& board = game.GetBoard();
	dtg::ChessMoveDecoder decoder(&game.GetBoard());
	dtg::ChessMoveXY s;
//	board[2][3] = dtg::ChessConstants::BP;
	std::string string = "ba5";
	bool white = 1;
	for (;;) {
		printBoard(board);
		std::getline(std::cin, string);
		try {
			if (white) {
				s = decoder.DecodeWhite(string.c_str());
				white = 0;
			}
			else {
				s = decoder.DecodeBlack(string.c_str());
				white = 1;
			}
			if  (s.fromx == 255 || s.fromy == 255 || s.tox == 255 || s.toy == 255)
				throw "move not found";
		}
		catch(const char *str) {
			std::cout << "Parser error: " << str << '\n';
			continue;
		}
		auto piece = board[s.fromy][s.fromx];
		board.SetPiece(s.toy, s.tox, piece);
		board.SetPiece(s.fromy, s.fromx, dtg::ChessConstants::NO);
	}
	//lal
}
#else

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <time.h>

// OpenNN includes

#include <opennn.h>


int main()
{
	using namespace OpenNN;
	using namespace std;
	using namespace Eigen;
	try
	{
		srand(static_cast<unsigned>(time(nullptr)));

		// Data set

		DataSet data_set("chess_game.csv", ',', true);

		const Index input_variables_number = data_set.get_input_variables_number();
		const Index target_variables_number = data_set.get_target_variables_number();
		std::cout << "vars:targets [" << input_variables_number << ":" <<  target_variables_number << "]\n";
		return 0;

		// Neural network

		const Index hidden_neurons_number = 2048;

		NeuralNetwork neural_network(
			NeuralNetwork::ProjectType::Approximation,
			{input_variables_number, hidden_neurons_number, target_variables_number}
		);

		// Training strategy

		TrainingStrategy training_strategy(&neural_network, &data_set);

		training_strategy.set_loss_method(TrainingStrategy::LossMethod::CROSS_ENTROPY_ERROR);
		training_strategy.perform_training();

		// Testing analysis

		const TestingAnalysis testing_analysis(&neural_network, &data_set);

		Tensor<type, 2> inputs(1, 576);

		inputs.setValues({{type(5.1),type(3.5),type(1.4),type(0.2)},
				{type(6.4),type(3.2),type(4.5),type(1.5)},
				{type(6.3),type(2.7),type(4.9),type(1.8)}});

		const Tensor<Index, 2> confusion = testing_analysis.calculate_confusion();

		cout << "\nConfusion matrix:\n" << confusion << endl;

		// Save results

		neural_network.save("./data/neural_network.xml");
		neural_network.save_expression_c("./data/neural_network.c");
		neural_network.save_expression_python("./data/neural_network.py");

		return 0;
	}
	catch(exception& e)
	{
		cout << e.what() << endl;

		return 1;
	}
}  
#endif
