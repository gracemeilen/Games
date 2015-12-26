//Grace Meilen
//James DiLorenzo
//Israel Hilerio
#ifndef __GOMOKU_H
#define __GOMOKU_H

#include "game.h"

class Gomoku : public GameBase {
public:
	Gomoku();
	Gomoku(Gomoku &g);
	virtual void print();
	friend ostream &operator<<(ostream &o, const Gomoku &g);
	virtual int turn();
	virtual bool done();
	virtual bool draw();
	Gomoku(Gomoku &&g) = delete;
	Gomoku&& Gomoku::operator=(Gomoku &&) = delete;
};

#endif