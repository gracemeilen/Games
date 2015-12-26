#ifndef __GAME_H
#define __GAME_H

//Grace Meilen
//James DiLorenzo
//Israel Hilerio
#include "Header.h"

//  An enumerator to keep track of the possible colors of game pieces
enum piece_color{ red, black, white, no_color, invalid_color };

// A struct to store the relevant information about a piece for any given game
struct game_piece{
	game_piece(piece_color c, string n, string d, bool b);
	piece_color color_;
	string name_;
	string display_;
	bool userMade;
};

// The class that stores the TicTacToe game and contains the method that allow 
// for game play. 
class GameBase {
public:
	GameBase();
	GameBase(const GameBase &g);
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	friend ostream &operator<<(ostream &o, const GameBase &g);
	int prompt(unsigned int &hor, unsigned int &vert);
	void prompt(unsigned int &hor, unsigned int &vert, unsigned int &num);
	virtual int turn() = 0;
	int play();
	static void args_check(int argc, char* arg_vector[]);
	static shared_ptr<GameBase> instance();
	string name;
protected:
	GameBase&& GameBase::operator=(GameBase &&) = delete;
	GameBase(GameBase &&g) = delete;
	static shared_ptr<GameBase> pointy;
	vector<game_piece> board;
	unsigned int longest_display;
	unsigned int dimensions;
	unsigned int min_valid;
	unsigned int max_valid;
	string player1_display;
	string player2_display;
	bool player1_turn;
	int moves;
};

#endif