#include <iostream>
#include <fstream>
using namespace std;

int spot(int k, int l);
int mainboardwin(char** ptr2);

class ticTacToe {
private:
	char** ptr;
	int N;

public:
	ticTacToe() {
		this->N = 3;
		ptr = new char* [N];
		for (int i = 0; i < N; i++) {
			ptr[i] = new char[N];
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				ptr[i][j] = '\0';
			}
		}
	}

	ticTacToe(int s) {
		this->N = s;
		ptr = new char* [N];
		for (int i = 0; i < N; i++) {
			ptr[i] = new char[N];
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				ptr[i][j] = '\0';
			}
		}
	}

	ticTacToe(const ticTacToe& t) {
		this->N = t.N;
		ptr = nullptr;
		if (t.ptr != nullptr) {
			this->ptr = new char* [N];
			for (int i = 0; i < N; i++) {
				this->ptr[i] = new char[N];
			}
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					this->ptr[i][j] = t.ptr[i][j];
				}
			}
		}
	}

	~ticTacToe() {
		if (ptr != nullptr) {
			for (int i = 0; i < N; i++) {
				delete[] ptr[i];
			}
			ptr = nullptr;
		}
	}

	friend ostream& operator<< (ostream& out, const ticTacToe& t) {
		for (int i = 0; i < t.N; i++) {
			for (int j = 0; j < t.N; j++) {
				if (t.ptr[i][j] != '\0') {
					out << t.ptr[i][j] << " ";
				}
				else {
					out << "- ";
				}
			}
			out << endl;
		}
		return out;
	}

	void UltimatePrint(int r) {
		for (int i = 0; i <= 2; i++) {
			if (i != 2) {
				if (ptr[r][i] == '\0') {
					cout << "-" << "  ";
				}
			}
			else {
				if (ptr[r][i] == '\0') {
					cout << "-" << "\t""\t";
				}
			}
		}
	}

	void Move(char play) {
		bool flag = true;
		while (flag == true) {
			int row = -1;
			int col = -1;
			while (row < 1 || row > N) {
				cout << "Enter the Row number: ";
				cin >> row;
				if (row < 1 || row > N) {
					cout << "Please enter a Row number in the range 1 to " << N << " !" << endl;
				}
				cout << endl;
			}
			while (col < 1 || col > N) {
				cout << "Enter the Collumn number: ";
				cin >> col;
				if (col < 1 || col > N) {
					cout << "Please enter a Collumn number in the range 1 to " << N << " !" << endl;
				}
				cout << endl;
			}
			row--;
			col--;
			if (ptr[row][col] == '\0') {
				ptr[row][col] = play;
				flag = false;
			}
			else {
				cout << "The selected space is already occupied !" << endl << "Please enter a valid set of row and column !" << endl << endl;
			}
		}
	}

	int Winner() {
		char pattern = '0';
		bool w = false;
		for (int c = 0; c < N && w == false; c++) {
			bool f = true;
			for (int r = 1; r < N && f == true; r++) {
				if (ptr[r][c] != ptr[0][c] || ptr[r][c] == '\0') {
					f = false;
				}
			}
			if (f == true && w == false) {
				w = true;
				pattern = ptr[0][c];
			}
		}

		for (int r = 0; r < N && w == false; r++) {
			bool f = true;
			for (int c = 1; c < N && f == true; c++) {
				if (ptr[r][c] != ptr[r][0] || ptr[r][c] == '\0') {
					f = false;
				}
			}
			if (f == true && w == false) {
				w = true;
				pattern = ptr[r][0];
			}
		}

		bool f = true;
		for (int i = 1; i < N && w == false && f == true; i++) {
			if (ptr[i][i] != ptr[0][0] || ptr[i][i] == '\0') {
				f = false;
			}
		}
		if (f == true && w == false) {
			w = true;
			pattern = ptr[0][0];
		}

		for (int r = 1, c = (N - 2); r < N && c >= 0 && w == false; r++, c--) {
			if (ptr[r][c] != ptr[0][N - 2] || ptr[r][c] == '\0') {
				f = false;
			}
		}
		if (f == true && w == false) {
			w = true;
			pattern = ptr[0][N - 2];
		}

		bool end = false;
		if (w != true) {
			end = true;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (ptr[i][j] == '\0') {
						end = false;
						j = N;
						i = N;
					}
				}
			}
		}
		if (end == true) {
			pattern = 'd';
		}

		if (pattern == 'x') {
			return 1;
		}
		else if (pattern == 'o') {
			return 2;
		}
		else if (pattern == 'd') {
			return 3;
		}
		else {
			return 0;
		}
	}

	void getptr(char** temp) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				temp[i][j] = ptr[i][j];
			}
		}
	}

	void setptr(char** temp) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				ptr[i][j] = temp[i][j];
			}
		}
	}
};

class ultimate_ticTacToe {
private:
	ticTacToe** basic;
	char** bptr;

public:
	ultimate_ticTacToe() :basic() {
		basic = new ticTacToe * [3];
		for (int i = 0; i < 3; i++) {
			basic[i] = new ticTacToe[3];
		}

		bptr = new char* [3];
		for (int i = 0; i < 3; i++) {
			bptr[i] = new char[3];
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				bptr[i][j] = '\0';
			}
		}

	}

	ultimate_ticTacToe(const ultimate_ticTacToe& t) {
		basic = new ticTacToe * [3];
		for (int l = 0; l < 3; l++) {
			basic[l] = new ticTacToe[3];
		}

		for (int a = 0; a < 3; a++) {
			for (int b = 0; b < 3; b++) {
				basic[a][b] = t.basic[a][b];
			}
		}

		bptr = new char* [3];
		for (int l = 0; l < 3; l++) {
			bptr[l] = new char[3];
		}

		for (int a = 0; a < 3; a++) {
			for (int b = 0; b < 3; b++) {
				bptr[a][b] = t.bptr[a][b];
			}
		}
	}

	~ultimate_ticTacToe() {
		if (basic != nullptr) {
			for (int i = 0; i < 3; i++) {
				delete[] basic[i];
			}
			for (int i = 0; i < 3; i++) {
				delete[] bptr[i];
			}

			delete[] basic;
			basic = nullptr;
			delete[] bptr;
			bptr = nullptr;
		}
	}

	friend void operator << (ostream& out, const ultimate_ticTacToe& ub) {
		char** ptr = new char* [3];
		for (int i = 0; i < 3; i++) {
			ptr[i] = new char[3];
		}

		cout << "----- All 9 SubBoards: -----" << endl;
		for (int e = 0; e < 3; e++) {
			for (int f = 0; f < 3; f++) {
				for (int g = 0; g < 3; g++) {
					ub.basic[e][g].getptr(ptr);
					for (int h = 0; h < 3; h++) {
						if (ptr[f][h] != '\0')
							out << ptr[f][h] << " ";
						else
							out << "- ";
					}
					out << " ";
				}
				out << endl;
			}
			out << endl;
		}

		cout << "----- Main Board: ----- " << endl;
		for (int k = 0; k < 3; k++) {
			for (int l = 0; l < 3; l++) {
				if (ub.bptr[k][l] != '\0') {
					out << ub.bptr[k][l] << " ";
				}
				else {
					out << "- ";
				}
			}
			out << endl;
		}
	}

	void Umove(char move, const ultimate_ticTacToe& ub, int& br, int& bc, int barr[3][3]) {
		char** ptr = new char* [3];
		for (int i = 0; i < 3; i++) {
			ptr[i] = new char[3];
		}

		bool flag = true;
		while (flag == true) {
			int row = -1;
			int col = -1;
			while (row < 1 || row > 3) {
				cout << "Enter the Row number: ";
				cin >> row;
				if (row < 1 || row > 3) {
					cout << "Please enter a Row number in the range 1 to " << 3 << " !" << endl;
				}
				cout << endl;
			}
			while (col < 1 || col > 3) {
				cout << "Enter the Collumn number: ";
				cin >> col;
				if (col < 1 || col > 3) {
					cout << "Please enter a Collumn number in the range 1 to " << 3 << " !" << endl;
				}
				cout << endl;
			}
			row--;
			col--;
			ub.basic[br][bc].getptr(ptr);
			if (ptr[row][col] == '\0') {
				ptr[row][col] = move;
				ub.basic[br][bc].setptr(ptr);
				if (barr[row][col] == 0) {
					br = row;
					bc = col;
				}
				else {
					bool f = false;
					while (f == false) {
						bool f1 = false;
						cout << "Board already fully filled, Player will choose row and collumn for another board which is unfilled !" << endl;
						while (f1 == false) {
							f1 = true;
							cout << "Enter row number for the board: ";
							cin >> br;
							cout << endl;
							if (br <= 0 || br > 3) {
								f1 = false;
							}
							br--;
							cout << "Enter collumn number for the board:  ";
							cin >> bc;
							cout << endl;
							if (bc <= 0 || bc > 3) {
								f1 = false;
							}
							bc--;
							if (f1 == false) {
								cout << "Row / Column value is out of ranage ! .... Try again !" << endl;
							}
						}
						if (barr[br][bc] == 0) {
							f = true;
						}
						else {
							cout << "Board can not be chosen ! .... Try again !" << endl;
							f = false;
						}
					}
				}
				flag = false;
			}
			else {
				cout << "The selected spot is already filled !" << endl << "Please enter set of row and column which is unfilled !" << endl << endl;
			}
		}

		int success;
		int bn;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				success = ub.basic[i][j].Winner();
				bn = spot(i, j);
				if (success == 1) {
					if (barr[i][j] != 1) {
						cout << "Player 1 has won board number: " << bn << "!" << endl;
					}
					barr[i][j] = 1;
					ub.bptr[i][j] = 'x';
				}
				else if (success == 2) {
					if (barr[i][j] != 1) {
						cout << "Player 2 has won board number: " << bn << "!" << endl;
					}
					barr[i][j] = 1;
					ub.bptr[i][j] = 'o';
				}
				else if (success == 3) {
					if (barr[i][j] != 1) {
						cout << "Match Drawn on board number: " << bn << "!" << endl;
					}
					barr[i][j] = 1;
					ub.bptr[i][j] = 'd';
				}
			}
		}
	}

	void updatemainboard(char** fptr) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				fptr[i][j] = bptr[i][j];
			}
		}
	}

	void saveptr(char** tptr, const ultimate_ticTacToe& ub, int a, int b) {
		ub.basic[a][b].getptr(tptr);
	}

	void loadptr(char** tptr, ultimate_ticTacToe& ub, int a, int b) {
		ub.basic[a][b].setptr(tptr);
	}

};

int main() {
	cout << "------ WELCOME ------" << endl;
	bool f2 = false;
	int gchoice;
	while (f2 == false) {
		cout << "Select your Game Mode: " << endl;
		cout << "Enter (1) to play Basic Tic Tac Toe !" << endl;
		cout << "Enter (2) to play Ultimate Tic Tac Toe !" << endl;
		cout << "Enter your Option: ";
		cin >> gchoice;
		cout << endl;
		f2 = true;
		if (gchoice < 1 || gchoice>2) {
			cout << "Enter a valid option !" << endl;
			f2 = false;
		}
	}

	if (gchoice == 2) {
		ultimate_ticTacToe ultimateb;

		int barr[3][3] = { 0 };
		int br;
		int	bc;
		bool flag = false;
		int c = 1;
		int mainw = 0;
		int uchoice = -1;
		char usave;

		char** winresult = new char* [3];
		for (int i = 0; i < 3; i++) {
			winresult[i] = new char[3];
		}

		char** savesmallptr = new char* [3];
		for (int i = 0; i < 3; i++) {
			savesmallptr[i] = new char[3];
		}

		bool f2 = false;
		while (f2 == false) {
			cout << "----- Choose one of the following Game Modes -----" << endl;
			cout << "Press (1) to Start a New Game" << endl;
			cout << "Press (2) to Load a Previously Saved Game" << endl;
			cout << "Enter your Option: ";
			cin >> uchoice;
			cout << endl;

			if (uchoice == 1 || uchoice == 2) {
				f2 = true;
			}
			else {
				cout << "Invalid Option !" << endl;
			}
		}

		cout << "Instructions for Ultimate Tic Tac Toe: " << endl;
		cout << "Player 1 will be assigned the character 'x' as input for the board." << endl;
		cout << "Player 2 will be assigned the character 'o' as input for the board." << endl;
		cout << "The game will start in the box which is in the center of main big board." << endl;
		cout << "The game will start with Player 1 getting the first turn." << endl << endl << endl;

		if (uchoice == 1) {
			while (flag == false && mainw == 0) {
				if (c == 1) {
					br = 1;
					bc = 1;
				}

				if (c % 2 == 1) {
					cout << "Player 1's turn !" << endl;
					cout << "Enter the values for the respective Row and Collumn to make your Move: " << endl;
					ultimateb.Umove('x', ultimateb, br, bc, barr);
					ultimateb.updatemainboard(winresult);
					mainw = mainboardwin(winresult);
				}

				else if (c % 2 == 0) {
					cout << "Player 2's turn !" << endl;
					cout << "Enter the values for the respective Row and Collumn to make your Move: " << endl;
					ultimateb.Umove('o', ultimateb, br, bc, barr);
					ultimateb.updatemainboard(winresult);
					mainw = mainboardwin(winresult);
				}

				cout << ultimateb;
				cout << endl << "----- 'x' Represents Player 1 AND 'o' Represents Player 2 -----" << endl << endl;
				c++;

				if (flag == false) {
					cout << "Press 's' to save game OR Press any other character to continue: ";
					cin >> usave;
				}
				if (usave == 's') {
					ofstream in;
					in.open("saveultimategame.txt");
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							ultimateb.saveptr(savesmallptr, ultimateb, i, j);
							for (int a = 0; a < 3; a++) {
								for (int b = 0; b < 3; b++)
								{
									in << savesmallptr[a][b] << endl;
								}
							}
						}
					}
					in.close();

					in.open("saveultimateboard.txt");
					ultimateb.updatemainboard(winresult);
					for (int a = 0; a < 3; a++) {
						for (int b = 0; b < 3; b++) {
							in << winresult[a][b] << endl;
						}
					}
					in.close();

					in.open("savevariables.txt");
					in << c << endl;
					in << br << endl;
					in << bc << endl;
					in.close();

					in.open("saveboxstatus.txt");
					for (int a = 0; a < 3; a++) {
						for (int b = 0; b < 3; b++) {
							in << barr[a][b] << endl;
						}
					}
					in.close();
					cout << endl << "The game has been saved !" << endl;
				}

				if (mainw == 1) {
					cout << "---- Player 1 has won the main board ----" << endl;
				}
				else if (mainw == 2) {
					cout << "---- Player 2 has won the main board ----" << endl;
				}
				else if (mainw == 3) {
					cout << "---- The board is Draw ----" << endl;
				}
			}
		}

		else if (uchoice == 2) {
			ifstream out;
			out.open("saveboxstatus.txt");
			for (int a = 0; a < 3; a++) {
				for (int b = 0; b < 3; b++) {
					out >> barr[a][b];
				}
			}
			out.close();

			out.open("savevariables.txt");
			out >> c;
			out >> br;
			out >> bc;
			out.close();

			out.open("saveultimateboard.txt");
			for (int a = 0; a < 3; a++) {
				for (int b = 0; b < 3; b++) {
					out >> winresult[a][b];
				}
			}
			out.close();

			out.open("saveultimategame.txt");
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int a = 0; a < 3; a++) {
						for (int b = 0; b < 3; b++) {
							out >> savesmallptr[a][b];
						}
					}
					ultimateb.loadptr(savesmallptr, ultimateb, i, j);
				}
			}
			out.close();
			cout << "Your Previously saved Board: " << endl;
			cout << ultimateb;

			while (flag == false && mainw == 0) {
				if (c == 1) {
					br = 1;
					bc = 1;
				}

				if (c % 2 == 1) {
					cout << "Player 1's turn !" << endl;
					cout << "Enter the values for the respective Row and Collumn to make your Move: " << endl;
					ultimateb.Umove('x', ultimateb, br, bc, barr);
					ultimateb.updatemainboard(winresult);
					mainw = mainboardwin(winresult);
				}

				else if (c % 2 == 0) {
					cout << "Player 2's turn !" << endl;
					cout << "Enter the values for the respective Row and Collumn to make your Move: " << endl;
					ultimateb.Umove('o', ultimateb, br, bc, barr);
					ultimateb.updatemainboard(winresult);
					mainw = mainboardwin(winresult);
				}

				cout << ultimateb;
				cout << endl << "----- 'x' Represents Player 1 AND 'o' Represents Player 2 -----" << endl << endl;
				c++;

				if (flag == false) {
					cout << "Press 's' to save game OR Press any other character to continue: ";
					cin >> usave;
				}
				if (usave == 's') {
					ofstream in;
					in.open("SaveUltimategame.txt");
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							ultimateb.saveptr(savesmallptr, ultimateb, i, j);
							for (int a = 0; a < 3; a++) {
								for (int b = 0; b < 3; b++)
								{
									in << savesmallptr[a][b] << endl;
								}
							}
						}
					}
					in.close();

					in.open("Saveultimateboard.txt");
					ultimateb.updatemainboard(winresult);
					for (int a = 0; a < 3; a++) {
						for (int b = 0; b < 3; b++) {
							in << winresult[a][b] << endl;
						}
					}
					in.close();

					in.open("SaveVariables.txt");
					in << c << endl;
					in << br << endl;
					in << bc << endl;
					in.close();

					in.open("SaveBoxStatus.txt");
					for (int a = 0; a < 3; a++) {
						for (int b = 0; b < 3; b++) {
							in << barr[a][b] << endl;
						}
					}
					in.close();
					cout << endl << "The game has been saved !" << endl;
				}

				if (mainw == 1) {
					cout << "---- Player 1 has won the main board ----" << endl;
				}
				else if (mainw == 2) {
					cout << "---- Player 2 has won the main board ----" << endl;
				}
				else if (mainw == 3) {
					cout << "---- The board is Draw ----" << endl;
				}
			}
		}
	}


	else if (gchoice == 1) {
		int win = 0;
		int c = 1;
		int choice;
		char save = '0';

		bool flag = false;
		while (flag == false) {
			cout << "----- Choose one of the following Game Modes -----" << endl;
			cout << "Press (1) to Start a New Game" << endl;
			cout << "Press (2) to Load a Previously Saved Game" << endl;
			cout << "Enter your Option: ";
			cin >> choice;
			cout << endl;
			if (choice == 1 || choice == 2) {
				flag = true;
			}
			else {
				cout << "Invalid Option !" << endl;
			}
		}

		if (choice == 1) {
			int size;
			bool flag = false;
			while (flag == false) {
				cout << "Enter the Size for the Board: ";
				cin >> size;
				cout << endl;
				flag = true;
				if (size < 3) {
					cout << "Invalid Size !" << endl;
					cout << "Minimum Size for the Board is 3 !" << endl << endl;
					flag = false;
				}
			}

			char** temp = new char* [size];
			for (int i = 0; i < size; i++) {
				temp[i] = new char[size];
			}

			ticTacToe board(size);

			cout << "Instructions for Basic Tic Tac Toe: " << endl;
			cout << "Player 1 will be assigned the character 'x' as input for the board." << endl;
			cout << "Player 2 will be assigned the character 'o' as input for the board." << endl;
			cout << "The game will start with Player 1 getting the first turn." << endl << endl << endl;

			while (win == 0) {
				if (c % 2 == 1) {
					cout << "Player 1's turn !" << endl;
					cout << "Enter the values for the respective Row and Collumn to make your Move: " << endl;
					board.Move('x');
					cout << board << endl;
					cout << "----- 'x' Represents Player 1 AND 'o' Represents Player 2 -----" << endl << endl;
					win = board.Winner();
				}
				else if (c % 2 == 0) {
					cout << "Player 2's turn !" << endl;
					cout << "Enter the values for the respective Row and Collumn to make your Move: " << endl;
					board.Move('o');
					cout << board << endl;
					cout << "----- 'x' Represents Player 1 AND 'o' Represents Player 2 -----" << endl << endl;
					win = board.Winner();
				}
				c++;
				if (win == 0) {
					cout << "Enter 's' to Save the game OR enter any other character to continue: ";
					cin >> save;
					cout << endl;
				}
				if (save == 's') {
					board.getptr(temp);
					ofstream write;
					write.open("BasicGame.txt");
					write << size << endl;
					write << c << endl;
					for (int i = 0; i < size; i++) {
						for (int j = 0; j < size; j++) {
							write << temp[i][j] << endl;
						}
					}
					write.close();
					cout << "The Game has been Saved !" << endl;
				}
			}

			cout << endl;
			if (win == 1) {
				cout << "---------- Player 1 is the Winner ! ----------" << endl;
			}
			else if (win == 2) {
				cout << "---------- Player 2 is the Winner ! ----------" << endl;
			}
			else if (win == 3) {
				cout << "---------- Match Draw ! ----------" << endl;
			}
			cout << endl;
		}

		else if (choice == 2) {
			int size;

			ifstream read;
			read.open("BasicGame.txt");
			read >> size;
			read >> c;

			char** temp = new char* [size];
			for (int i = 0; i < size; i++) {
				temp[i] = new char[size];
			}
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					read >> temp[i][j];
				}
			}
			read.close();

			cout << "Your Previously saved Board: " << endl;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (temp[i][j] == '\0') {
						cout << "- ";
					}
					else {
						cout << temp[i][j] << " ";
					}
				}
				cout << endl;
			}
			cout << endl;

			ticTacToe board(size);
			board.setptr(temp);

			cout << "Instructions: " << endl;
			cout << "Player 1 will be assigned the character 'x' as input for the board." << endl;
			cout << "Player 2 will be assigned the character 'o' as input for the board." << endl << endl << endl;

			while (win == 0) {
				if (c % 2 == 1) {
					cout << "Player 1's turn !" << endl;
					cout << "Enter the values for the respective Row and Collumn to make your Move: " << endl;
					board.Move('x');
					cout << board << endl;
					cout << "----- 'x' Represents Player 1 AND 'o' Represents Player 2 -----" << endl << endl;
					win = board.Winner();
				}
				else if (c % 2 == 0) {
					cout << "Player 2's turn !" << endl;
					cout << "Enter the values for the respective Row and Collumn to make your Move: " << endl;
					board.Move('o');
					cout << board << endl;
					cout << "----- 'x' Represents Player 1 AND 'o' Represents Player 2 -----" << endl << endl;
					win = board.Winner();
				}
				c++;
				if (win == 0) {
					cout << "Enter 's' to Save the game OR enter any other character to continue: ";
					cin >> save;
					cout << endl;
				}
				if (save == 's') {
					board.getptr(temp);
					ofstream write;
					write.open("BasicGame.txt");
					write << size << endl;
					write << c << endl;
					for (int i = 0; i < size; i++) {
						for (int j = 0; j < size; j++) {
							write << temp[i][j] << endl;
						}
					}
					write.close();
					cout << "The Game has been Saved !" << endl;
				}
			}

			cout << endl;
			if (win == 1) {
				cout << "---------- Player 1 is the Winner ! ----------" << endl;
			}
			else if (win == 2) {
				cout << "---------- Player 2 is the Winner ! ----------" << endl;
			}
			else if (win == 3) {
				cout << "---------- Match Draw ! ----------" << endl;
			}
			cout << endl;
		}
	}

	cout << endl << endl << "------ BYE ! ------" << endl << endl;

}

int spot(int k, int l) {
	int boardspot = -1;
	if (k == 0 && l == 0) {
		boardspot = 1;
	}
	else if (k == 0 && l == 1) {
		boardspot = 2;
	}
	else if (k == 0 && l == 2) {
		boardspot = 3;
	}
	else if (k == 1 && l == 0) {
		boardspot = 4;
	}
	else if (k == 1 && l == 1) {
		boardspot = 5;
	}
	else if (k == 1 && l == 2) {
		boardspot = 6;
	}
	else if (k == 2 && l == 0) {
		boardspot = 7;
	}
	else if (k == 2 && l == 1) {
		boardspot = 8;
	}
	else if (k == 2 && l == 2) {
		boardspot = 9;
	}
	return boardspot;
}

int mainboardwin(char** ptr) {
	int c = 0;
	int s = 3;
	char last;
	char pattern = 'g';
	bool complete = false;
	bool victory = false;

	for (int a = 0; a < s; a++) {
		c = 1;
		last = ptr[a][0];
		for (int b = 1; b < s; b++) {
			if (ptr[a][b] == last && ptr[a][b] != '\0') {
				c++;
				last = ptr[a][b];
			}
		}
		if (c == s) {
			pattern = last;
			victory = true;
			a = s;
		}
	}

	for (int a = 0; a < s; a++) {
		c = 1;
		last = ptr[0][a];
		for (int b = 1; b < s; b++) {
			if (ptr[b][a] == last && ptr[b][a] != '\0') {
				c++;
				last = ptr[b][a];
			}
		}
		if (c == s) {
			pattern = last;
			victory = true;
			a = s;
		}
	}

	c = 1;
	last = ptr[0][0];
	for (int a = 1; a < s; a++) {
		if (ptr[a][a] == last && ptr[a][a] != '\0') {
			c++;
			last = ptr[a][a];
		}
		if (c == s) {
			pattern = last;
			victory = true;
			a = s;
		}
	}

	c = 1;
	last = ptr[0][s - 1];
	for (int a = 1, b = s - 2; a < s; a++, b--) {
		if (ptr[a][b] == last && ptr[a][b] != '\0') {
			c++;
			last = ptr[a][b];
		}
		if (c == s) {
			pattern = last;
			victory = true;
			a = s;
		}
	}

	if (victory != true) {
		complete = true;
		for (int a = 0; a < s; a++) {
			for (int b = 0; b < s; b++) {
				if (ptr[a][b] == '\0') {
					complete = false;
					b = s;
					a = s;
				}
			}
		}
	}

	if (complete == true) {
		pattern = 'd';
	}
	if (pattern == 'x') {
		return 1;
	}
	else if (pattern == 'o') {
		return 2;
	}
	else if (pattern == 'd') {
		return 3;
	}
	else {
		return 0;
	}

}