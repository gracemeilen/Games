//Grace Meilen 
//James DiLorenzo
//Israel Hilerio


#include "stdafx.h"
#include "TicTacToe.h"
#include "Gomoku.h"
#include "Sudoku.h"
#include <sstream>
using namespace std;

// A construtor that takes in a piece_color, string and string 
// and creates a game piece with those values assigned to them. 
game_piece::game_piece(piece_color c, string n, string d, bool b)
: color_(c), name_(n), display_(d), userMade(b){};

// Overload the << operator so that when we call it on a Game object, it
// prints out the current status of the gane board. 
ostream& operator<<(ostream &o, const GameBase &g){
	if (g.board.size() == g.dimensions * g.dimensions){
		// Print so lower left corner is 0,0 and top right is 4,4
		for (int i = (g.dimensions - 1); i >= 0; --i){
			for (int k = 0; k <= (int)(g.dimensions - 1); ++k){
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

void GameBase::args_check(int argc, char* args_vector[]){
	if (pointy == nullptr){
		if (argc == correct_args){
			if (string(args_vector[game_name]) == "TicTacToe"){
				GameBase* play_me = new TicTacToe();
				shared_ptr<GameBase> a(play_me);
				pointy = a;
			}
			else if (string(args_vector[game_name]) == "Gomoku"){
				GameBase* play_me = new Gomoku();
				shared_ptr<GameBase> a(play_me);
				pointy = a;
			}
			else if (string(args_vector[game_name]) == "Sudoku"){
				GameBase* play_me = new Sudoku();
				shared_ptr<GameBase> a(play_me);
				pointy = a;
			}
			else{
				throw exceptions::bad_game_name;
			}
		}
		else {
			throw exceptions::bad_num_args;
		}
	}
	else {
		throw exceptions::already_a_game;
	}

}

GameBase::GameBase(const GameBase &g){
	(*this) = g;
}

GameBase::GameBase(){
	// Constructor for Game. Fills the board with blank pieces.
	// Sets the game so it always starts out as Player X's turn. 
	// Initializes a counter of how many moves have been made to 0
	for (int i = 0; i < (int)this->dimensions; i++){
		for (int k = 0; k < (int)this->dimensions; k++){
			this->board.push_back(game_piece(no_color, " ", "  ", true));
		}
	}
	this->player1_turn = true;
	this->moves = 0;
}
shared_ptr<GameBase> GameBase::pointy = nullptr;

// Prompt the player whose turn it is to make a move. Keep prompting them until 
// they either (1) supply a well formed coordinate and make valid move or (2) they
// quit the game. 
int GameBase::prompt(unsigned int &hor, unsigned int &vert){
	bool valid_move = false;
	bool quit = false;
	string move;
	string fail;
	// Just keep prompting
	while (!valid_move && !quit){
		cout << "Please enter the coordinates at which you want to move or the word quit. Correct formation is _,_. " << endl;
		cout << endl;
		cin >> move;
		if (move.compare("quit") == 0){
			// quit the program
			char c;
			cout << "Would you like to save? (y/n): " << flush;
			cin >> c;
			ofstream of(this->name + ".txt");
			of << this->name << endl;
			while (c != 'y' && c != 'n'){
				cout << endl << "Would you like to save? (y/n): " << endl;
				cin >> c;
			}
			if (c == 'y'){
				for (vector<game_piece>::iterator it = board.begin(); it != board.end(); it++){
					of << (*it).name_;
				}
			}
			else if (c == 'n'){
				of << "NODATA" << endl;
			}
			return quit_game;
		}
		else{
			// Replace the comma in the arugement with a space so we can 
			// use an extraction operator and an istringstream.
			for (string::iterator it = move.begin(); it != move.end(); it++){
				if ((*it) == ','){
					(*it) = ' ';
				}
			}
			istringstream iss(move);
			if (iss >> hor){
				if (iss >> vert){
					if (!(iss >> fail)){
						if (hor <= this->max_valid && vert <= this->max_valid){
							if (hor >= min_valid && vert >= min_valid){
								if (this->board[(this->dimensions * vert) + hor].display_.compare("  ") == 0){
									valid_move = true;
								}
								else{
									cout << "There is already a piece there!" << endl;
								}
							}
							// make sure that the coordinates are in the correct range. 
							else {
								cout << "Invalid Coordinates" << endl;
							}
						}
						// make sure that the coordinates are in the correct range.  
						else {
							cout << "Invalid Coordinates" << endl;
						}
					}
				}
			}
		}
	}
	if (valid_move){
		return success;
	}
	else {
		return quit_game;
	}
}

void GameBase::prompt(unsigned int &x, unsigned int &y, unsigned int &num){
	bool valid_move = false;
	bool quit = false;
	string move;
	string fail;
	// Just keep prompting
	while (!valid_move && !quit){
		cout << "Please enter the coordinates at which you want to move and the piece you want to play (x,y,num), or the word 'quit'. Correct formation is _,_,_. " << endl;
		cout << endl;
		cin >> move;
		if (move.compare("quit") == 0){
			// quit the program
			char c;
			cout << "Would you like to save? (y/n): " << flush;
			cin >> c;
			ofstream of(this->name + ".txt");
			of << this->name << endl;
			while (c != 'y' && c != 'n'){
				cout << endl << "Would you like to save? (y/n): " << endl;
				cin >> c;
			}
			if (c == 'y'){
				for (vector<game_piece>::iterator it = board.begin(); it != board.end(); it++){
					of << (*it).name_;
				}
			}
			else if (c == 'n'){
				of << "NODATA" << endl;
			}
			throw quit_game;
		}
		else{

			// Replace the comma in the arugement with a space so we can 
			// use an extraction operator and an istringstream.
			for (string::iterator it = move.begin(); it != move.end(); it++){
				if ((*it) == ','){
					(*it) = ' ';
				}
			}
			istringstream iss(move);
			if (iss >> x){
				if (iss >> y){
					if (iss >> num){
						if (!(iss >> fail)){
							if (x <= this->max_valid && y <= this->max_valid){
								if (x >= min_valid && y >= min_valid){
									if (this->board[(this->dimensions * y) + x].userMade && num >= minVal && num <= sudokuDim){
										valid_move = true;
									}
									else if (num < minVal || num > sudokuDim){
										cout << "Value out of range. Please select sudoku piece. (1-9)" << endl;
									}
									else{
										cout << "Cannot overwrite computer generated pieces." << endl;
									}
								}
								// make sure that the coordinates are in the correct range. 
								else {
									cout << "Invalid Coordinates" << endl;
								}
							}
							// make sure that the coordinates are in the correct range.  
							else {
								cout << "Invalid Coordinates" << endl;
							}
						}
					}
				}
			}
		}
	}
	if (valid_move){
		string s = to_string((int)num);
		board[y*sudokuDim + x].color_ = red;
		board[y*sudokuDim + x].display_ = s;
		board[y*sudokuDim + x].name_ = s;
	}
}


// Ties all the previous methods together and actually handles the whole game
// until someone quits or a win/draw is reached. 
int GameBase::play(){
	cout << "Begin Play" << endl;
	// print out board initially 
	this->print();
	bool over = false;
	int playing;
	// keep playing until someone quits or the game ends. 

	if (this->name != "Sudoku"){
			while (!over){
				playing = turn();
				// Did someone win?
				if (done()){
					cout << "The game has completed in " << this->moves << " moves. " << endl;
					if (this->player1_turn){
						cout << "Player 2 has won" << endl;
					}
					else{
						cout << "Player 1 has won" << endl;
					}
					over = true;
					return success;
				}
				// Is there a draw?
				if (draw()){
					cout << "There is a draw! " << this->moves << " moves were played" << endl;
					over = true;
					return there_is_a_draw;
				}
				// Did someone quit?
				if (playing == 1){
					over = true;
					cout << "A player has quit the game. There were " << this->moves << " turns played" << endl;
					return game_over_player_quit;
				}
		}
	}
	else if (this->name == "Sudoku"){
		while (!done()){
			unsigned int x = 0;
			unsigned int y = 0;
			unsigned int num = 0;
			try{
				this->prompt(x, y, num);


			}
			catch (exceptions i){
				if (i == 1){
					over = true;
					cout << " You have quit!" << endl;
						return game_over_player_quit;
				}
			}
			print();
			if (done()) break;
			bool track = false;
			for (int i = 0; i < 81; i++){
				if (this->board[i].color_ != red){
					track = true;
				}
			}

			if (track == false){
				cout << "The board is full but the game is not over. Check your answer and overwrite incorrect values." << endl;
			}
		}
		cout << "You beat the game! Congratulations!" << endl;
	}
	// This should never be reached, the method should always return before this.
	// But the build process warned me that not all paths lead to a return value 
	// so I added this. 
	return never;
}

shared_ptr<GameBase> GameBase::instance(){
	if (pointy == nullptr){
		throw exceptions::null_pointy;
	}
else 
	return pointy;
}