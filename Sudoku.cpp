//Grace Meilen
//James DiLorenzo
//Israel Hilerio

#include "stdafx.h"
#include "Sudoku.h"

Sudoku::Sudoku(Sudoku &s){
	(*this) = s;
}
Sudoku::Sudoku(){
	this->longest_display = sudokuDisp;
	this->min_valid = minVal -1 ;
	this->max_valid = sudokuDim-1;
	this->dimensions = sudokuDim;
	this->player1_turn = true;
	this->moves = 0;
	this->name = "Sudoku";
	for (unsigned int i = 0; i < dimensions; i++){
		for (unsigned int k = 0; k < dimensions; k++){
			this->board.push_back(game_piece(no_color, " ", "  ", true));
		}
	}

	ifstream ifs;
	ifs.open("Sudoku.txt");
	if (ifs){
		string gamename = "";

		getline(ifs, gamename);


		string data = "";
		getline(ifs, data);


		if (gamename == "Sudoku"){
				if (data != "NODATA"){
					int counter = 0;
					while (counter < (int)board.size()){
						char color = data[counter];
						char space = ' ';
						stringstream s;
						string colorstr;
						s << color;
						s >> colorstr;
						if (color != space){
							moves++;
							board[counter].color_ = red;
							board[counter].display_ = colorstr;
							board[counter].name_ = colorstr;
							board[counter].userMade = false;
						}
						counter++;
					}
				}
				else {

					ifs.close();
					ifstream ifs2;
					ifs2.open("sudoku0.txt");
					int counter = 0;
					string s = "";
					char c1 = ' ';
					char c2 = '\n';
					char c3 = '\t';
					char c4 = '0';
					while (!ifs2.eof()){
						string temp = "";
						getline(ifs2, temp);
						for (int i = 0; i < (int) temp.length(); ++i) {
							if (isdigit(temp[i])){
								s += temp[i];
							}
						}
					}
					while (counter < (int)(dimensions)*(int)(dimensions)){
						char color = s[counter];
						char zero = '0';
						stringstream ss;
						string colorstr;
						ss << color;
						ss >> colorstr;
						if (color != zero && isdigit(color)){
							moves++;
							board[counter].display_ = colorstr;
							board[counter].name_ = colorstr;
							board[counter].userMade = false;
						}
						counter++;
					}
				}
			}
		}
	else {

		ifs.close();
		ifstream ifs2;
		ifs2.open("Sudoku0.txt");
		int counter = 0;
		string s = "";
		char c1 = ' ';
		char c2 = '\n';
		char c3 = '\t';
		char c4 = '0';
		while (!ifs2.eof()){
			string temp = "";
			getline(ifs2, temp);
			for (int i = 0; i < (int) temp.length(); ++i) {
				if (isdigit(temp[i])){
					s += temp[i];
				}
			}
		}
		while (counter < (int)(dimensions)*(int)(dimensions)){
			char color = s[counter];
			char zero = '0';
			stringstream ss;
			string colorstr;
			ss << color;
			ss >> colorstr;
			if (color != zero){
				moves++;
				board[counter].display_ = colorstr;
				board[counter].name_ = colorstr;
				board[counter].userMade = false;
			}
			counter++;
		}
	}
}

void Sudoku::print(){
	cout << (*this) << endl;
}

// Overload the << operator so that when we call it on a Game object, it
// prints out the current status of the game board. 
ostream& operator<<(ostream &o, const Sudoku &g){
	//	// Print so lower left corner is 0,0 and top right is 4,4

	for (int i = g.dimensions - 1; i >= 0; i--){
		o << setw(sudokuDisp) << i;
		o << setw(sudokuDisp) << "||";

		for (int k = 0; k < (int) g.dimensions; k++){
			o << setw(sudokuDisp) << g.board[sudokuDim *i + k].display_;
			if ((k + 1) % 3 == 0){
				o << setw(sudokuDisp) << "||";
			}
			else {
				o << setw(sudokuDisp) << "|";
			}
		}
		o << endl;
		for (int j = 0; j <= sudokuDim; j++){
			if (i % 3 == 0){
				o << setw(sudokuDisp) << "====";
			}
			else {
				o << setw(sudokuDisp) << "----";
			}
		}
		o << endl;
	}

	for (int i = 0; i <= sudokuDim; i++){
		if (i == 0){
			o << setw(sudokuDisp) << " ";
			o << setw(sudokuDisp) << "|";
		}
		else {
			o << setw(sudokuDisp) << i - 1;
			if (i % 3 == 0){
				o << setw(sudokuDisp) << "||";
			}
			else {
				o << setw(sudokuDisp) << "|";
			}
		}
	}
	return o;
}

bool Sudoku::done(){

	bool done = true;
	//check horizontal
	for (int i = 0; i < (int) dimensions; i++){
		vector<string> v;
		for (int j = 0; j < (int) dimensions; j++){
			v.push_back(this->board[i*dimensions + j].display_);
		}
		if (!checkVect(v)) done = false;
	}
	//check vert
	for (int i = 0; i < (int) dimensions; i++){
		vector<string> v;
		for (int j = 0; j < (int) dimensions; j++){
			v.push_back(this->board[i + j*dimensions].display_);
		}
		if (!checkVect(v)) done = false;
	}

	//check box
	vector<string> v1;
	vector<string> v2;
	vector<string> v3;
	vector<string> v4;
	vector<string> v5;
	vector<string> v6;
	vector<string> v7;
	vector<string> v8;
	vector<string> v9;


	for (int i = 0; i < sudokuDim; i++){ //row
		for (int j = 0; j < sudokuDim; j++){ //column

			string s = this->board[i*sudokuDim + j].name_;
			int boxI = (int)floor((double)(i) / 3);
			int boxJ=(int)ceil((double)(j+1)/3);
			int boxNum = 3*(boxI)+boxJ;
			switch (boxNum) {
			case 1:
				v1.push_back(s);
				break;
			case 2:
				v2.push_back(s);
				break;
			case 3:
				v3.push_back(s);
				break;
			case 4:
				v4.push_back(s);
				break;
			case 5:
				v5.push_back(s);
				break;
			case 6:
				v6.push_back(s);
				break;
			case 7:
				v7.push_back(s);
				break;
			case 8:
				v8.push_back(s);
				break;
			case 9:
				v9.push_back(s);
				break;
			default:
				std::cout << "Shouldn't get here." << endl;
				break;
			}
		}
	}



	if (!checkVect(v1)) done = false;
	if (!checkVect(v2)) done = false;
	if (!checkVect(v3)) done = false;
	if (!checkVect(v4)) done = false;
	if (!checkVect(v5)) done = false;
	if (!checkVect(v6)) done = false;
	if (!checkVect(v7)) done = false;
	if (!checkVect(v8)) done = false;
	if (!checkVect(v9)) done = false;
	
	return done;

}

bool Sudoku::checkVect(vector<string> v){
	sort(v.begin(), v.end());
	if (v.size() == 9){
		for (int i = 1; i < 9; i++){
			if (v[i-1].compare(to_string(i)) != 0){
				return false;
			}
	}
		return true;
		cout << endl;
}
	return false;
}

bool Sudoku::draw(){
	return 0;
}

int Sudoku::turn(){
	return 0;
}