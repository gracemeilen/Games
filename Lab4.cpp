// lab4.cpp : Defines the entry point for the console application.
//
//Grace Meilen
//James DiLorenzo
//Israel Hilerio

#include "stdafx.h"
#include "TicTacToe.h"

// returns a message specifying the proper execution of this program. 
int usage_message(const string &program_name, const string &usage){
	cout << "usage: " << program_name << " " << usage << endl;
	return fail_proper_use;
}

int main(int argc, char* argv[])
{

	try{
		GameBase::args_check(argc, argv);
	}
	catch (exceptions i){
		if (i == exceptions::bad_game_name){
			return usage_message(argv[program_name], "Invalid Game Name");
		}
		if (i == exceptions::bad_num_args){
			return usage_message(argv[program_name], "Too many or too few arguments");
		}
		if (i == exceptions::already_a_game){
			return usage_message(argv[program_name], "A game already exists in this location.");
		}
		else{
			return usage_message(argv[program_name], "Unspecified Fail");
		}
	}

	shared_ptr<GameBase>shared_game = GameBase::instance();
	return shared_game->play();
	//return 0;
}
