//Grace Meilen 
//James DiLorenzo
//Israel Hilerio

#include "stdafx.h"
#include "Gomoku.h"
using namespace std;

// A construtor that takes in a piece_color, string and string 
// and creates a game piece with those values assigned to them. 
//game_piece::game_piece(piece_color c, string n, string d)
//: color_(c), name_(n), display_(d){};
Gomoku::Gomoku(Gomoku &g){
	(*this) = g;
}
Gomoku::Gomoku(){
	// Constructor for Game. Fills the board with blank pieces.
	// Sets the game so it always starts out as Player X's turn. 
	// Initializes a counter of how many moves have been made to 0
	this->longest_display = gomokuDisp;
	this->min_valid = minVal;
	this->max_valid = gomokuMax;
	this->player1_display = "Black Stone";
	this->player2_display = "White Stone";
	this->dimensions = gomokuDim;
	this->player1_turn = true;
	this->moves = 0;
	this->name = "Gomoku";
	for (unsigned int i = 0; i < dimensions; i++){
		for (unsigned int k = 0; k < dimensions; k++){
			this->board.push_back(game_piece(no_color, " ", "  ", true));
		}
	}

	ifstream ifs;
	ifs.open("Gomoku.txt");
	if (!ifs.eof()){
		string gamename = "";

		getline(ifs, gamename);


		string data = "";
		getline(ifs, data);


		if (gamename == "Gomoku"){
			if (data != "NODATA"){
				int counter = 0;
				while (counter < (int) board.size()){
					char color = data[counter];
					char space = ' ';
					char b = 'b';
					char w = 'w';
					stringstream s;
					string colorstr;
					s << color;
					s >> colorstr;
					if (color != space){
						moves++;
						board[counter].name_ = colorstr;
						if (color == b){
							board[counter].display_ = "Black Stone";
						}
						else if (color == w){
							board[counter].display_ = "White Stone";
						}
					}
					counter++;
				}
			}
		}

	}
}

void Gomoku::print(){
	cout << (*this) << endl;
}

// Overload the << operator so that when we call it on a Game object, it
// prints out the current status of the game board. 
ostream& operator<<(ostream &o, const Gomoku &g){
	if (g.board.size() == g.dimensions * g.dimensions){
		// Print so lower left corner is 0,0 and top right is 4,4
		for (int i = (g.dimensions - 1); i >= 0; --i){
			for (unsigned int k = 0; k <= (g.dimensions - 1); ++k){
				// handles the edge cases so the board is numbered
				if (k == 0){
					if (i != 0){
						o << setw(g.longest_display + 1) << i;
					}
					else{
						o << setw(g.longest_display + 1) << i;
					}

				}
				else if (i == 0){
					o << setw(g.longest_display + 1) << k;
				}
				else {
					o << setw(g.longest_display + 1) << g.board[(g.dimensions * i) + k].display_;
				}

			}
			o << endl;
		}
	}
	return o;
}

// Iterates through the board in different orders to see if a player has made a 
// move that would win them the game. It has to check the horizontal, diagonoal 
// and vertical win cases. 
bool Gomoku::done() {
	bool done = false;
	for (int i = gomokuMax; i >= minVal; --i){
		for (int k = minVal; k <= gomokuMax; k++){
			//Check horizontal cases
			if (this->board[i*this->dimensions + k].display_.compare("  ") != 0 && k <= 15){
				if (this->board[i*this->dimensions + k].display_.compare(this->board[i*this->dimensions + k + 1].display_) == 0 &&
					this->board[i*this->dimensions + k].display_.compare(this->board[i*this->dimensions + k + 2].display_) == 0 &&
					this->board[i*this->dimensions + k].display_.compare(this->board[i*this->dimensions + k + 3].display_) == 0 &&
					this->board[i*this->dimensions + k].display_.compare(this->board[i*this->dimensions + k + 4].display_) == 0){
					done = true;
				}

				//Check vertical cases
				if (this->board[i*this->dimensions + k].display_.compare("  ") != 0 && i <= 15){
					if (this->board[i*this->dimensions + k].display_.compare(this->board[(i + 1)*this->dimensions + k].display_) == 0 &&
						this->board[i*this->dimensions + k].display_.compare(this->board[(i + 2)*this->dimensions + k].display_) == 0 &&
						this->board[i*this->dimensions + k].display_.compare(this->board[(i + 3)*this->dimensions + k].display_) == 0 &&
						this->board[i*this->dimensions + k].display_.compare(this->board[(i + 4)*this->dimensions + k].display_) == 0){
						done = true;
					}

					//Check diagonal cases
					if (i <= 15 && i >= 5 && k <= 15 && i >= 5 && this->board[i*this->dimensions + k].display_.compare("  ") != 0){

						//Upper right
						if (this->board[i*this->dimensions + k].display_.compare(this->board[(i + 1)*this->dimensions + k + 1].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i + 2)*this->dimensions + k + 2].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i + 3)*this->dimensions + k + 3].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i + 4)*this->dimensions + k + 4].display_) == 0){
							done = true;
						}

						//Upper left
						if (this->board[i*this->dimensions + k].display_.compare(this->board[(i + 1)*this->dimensions + k - 1].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i + 2)*this->dimensions + k - 2].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i + 3)*this->dimensions + k - 3].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i + 4)*this->dimensions + k - 4].display_) == 0){
							done = true;
						}

						//Bottom right
						if (this->board[i*this->dimensions + k].display_.compare(this->board[(i - 1)*this->dimensions + k + 1].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i - 2)*this->dimensions + k + 2].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i - 3)*this->dimensions + k + 3].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i - 4)*this->dimensions + k + 4].display_) == 0){
							done = true;
						}

						//Bottom left
						if (this->board[i*this->dimensions + k].display_.compare(this->board[(i - 1)*this->dimensions + k - 1].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i - 2)*this->dimensions + k - 2].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i - 3)*this->dimensions + k - 3].display_) == 0 &&
							this->board[i*this->dimensions + k].display_.compare(this->board[(i - 4)*this->dimensions + k - 4].display_) == 0){
							done = true;
						}
					}
				}
			}
		}
	}
	return done;
}

// Checks to see if the game will end in a stalemate  
bool Gomoku::draw(){
	if (done()){
		return false;
	}
	else if (this->moves == ((max_valid - min_valid + 1) * (max_valid - min_valid + 1))){
		return true;
	}
	else {
		return false;
	}
}


// Informs the players whose turn it is and prompts that player to enter a move
// If the player quits, the method passes that along, if they make a move, 
// it creates a new game piece and places it in the board and prints out the 
// board including that move as well as a list of of the moves that player has 
// made. 
int Gomoku::turn() {
	// Whose turn is it?
	if (this->player1_turn){
		cout << "It is Player 1's turn" << endl;
	}
	else {
		cout << "It is Player 2's turn" << endl;
	}
	unsigned int hor = 0;
	unsigned int vert = 0;
	unsigned int& horizontal = hor;
	unsigned int& vertical = vert;
	// get the user to make a move
	int turn = prompt(horizontal, vertical);
	if (turn == 1){
		return quit_game;
	}
	// create the game piece corresponding to that moves. 
	else {
		if (this->player1_turn){
			game_piece current(no_color, "b", this->player1_display, true);
			this->board[(this->dimensions * vert) + hor] = current;
			if (current.display_.length() > this->longest_display){
				this->longest_display = current.display_.length();
			}
		}
		else {
			game_piece current(no_color, "w", this->player2_display, true);
			this->board[(this->dimensions * vert) + hor] = current;
			if (current.display_.length() > this->longest_display){
				this->longest_display = current.display_.length();
			}
		}
		cout << (*this) << endl;
		// Print all the moves the current player has ever made. And updates the
		// tracker of whose turn it is. 
		if (this->player1_turn){
			this->player1_turn = false;
			cout << "Player 1: ";
			for (unsigned int i = this->max_valid; i >= this->min_valid; --i){
				for (unsigned int k = this->min_valid; k <= this->max_valid; k++){
					if (this->board[(this->dimensions * i) + k].display_.compare(this->player1_display) == 0){
						cout << ", " << k << ", " << i;
					}
				}
			}
		}
		else {
			this->player1_turn = true;
			cout << "Player 2: ";
			for (unsigned int i = this->max_valid; i >= this->min_valid; --i){
				for (unsigned int k = this->min_valid; k <= this->max_valid; k++){
					if (this->board[(this->dimensions * i) + k].display_.compare(this->player2_display) == 0){
						cout << ", " << k << ", " << i;
					}
				}
			}
		}
		// Increment the number of moves made. 
		this->moves++;
		cout << endl;
		return success;
	}
}
