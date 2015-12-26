#ifndef __HEADER_H
#define __HEADER_H

//Grace Meilen
//James DiLorenzo
//Israel Hilerio

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;
//all the return values used throughout the program. 
enum exceptions{ success, quit_game, game_over_player_quit, there_is_a_draw, fail_proper_use, never, null_pointy, bad_game_name, bad_num_args, already_a_game};
enum inputs{ program_name, game_name, correct_args };
enum displays{ gomokuDisp = 11, tttDisp = 1, minVal = 1, gomokuMax = 19, tttMax = 3, gomokuDim = 21, tttDim = 5, sudokuDim = 9, sudokuDisp = 2};
// Prints a usage message to the console that specifies how the progam should be 
// run if there was an error in its execution. Returns the value 6, which indicates 
// failure of proper use. 
int usage_message(const string &program_name, const string &usage);

#endif