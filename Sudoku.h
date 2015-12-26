//Grace Meilen
//James DiLorenzo
//Israel Hilerio

#ifndef __SUDOKU_H
#define __SUDOKU_H

#include "game.h"

class Sudoku : public GameBase {
public:
	Sudoku();
	Sudoku::Sudoku(Sudoku &s);
	virtual void print();
	friend ostream &operator<<(ostream &o, const Sudoku &g);
	virtual int turn();
	virtual bool done();
	virtual bool draw();
	void prompt(unsigned int &x, unsigned int &y, unsigned int &num);
private:
	Sudoku(Sudoku &&s) = delete;
	Sudoku&& Sudoku::operator=(Sudoku &&) = delete;
	bool checkVect(vector<string> v);
};


#endif