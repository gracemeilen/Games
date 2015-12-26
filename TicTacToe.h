//Grace Meilen 
//James DiLorenzo
//Israel Hilerio

#ifndef __TICTACTOE_H
#define __TICTACTOE_H

#include "game.h"

class TicTacToe : public GameBase {
public:
	TicTacToe();
	TicTacToe(TicTacToe &t);
	virtual void print();
	friend ostream &operator<<(ostream &o, const TicTacToe &g);
	virtual int turn();
	virtual bool done();
	virtual bool draw();
	TicTacToe(TicTacToe &&g) = delete;
	TicTacToe&& TicTacToe::operator=(TicTacToe &&) = delete;
};

#endif