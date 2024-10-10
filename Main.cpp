#include <iostream>
#include "Center.h"

using namespace std;


bool solve();
bool checkValidity(int row, int colm);
bool placeNumber(int row, int colm);



//Enter sudoku here
// ignore the secound slot for each number
int Grid[9][9][2] = {
	{ {0,0},{4,0},{0,0},{0,0},{0,0},{9,0},{3,0},{1,0},{0,0}},
	{ {1,0},{0,0},{9,0},{3,0},{4,0},{0,0},{0,0},{2,0},{6,0}},
	{ {3,0},{0,0},{6,0},{0,0},{0,0},{1,0},{4,0},{0,0},{0,0}},
	{ {9,0},{1,0},{4,0},{0,0},{8,0},{0,0},{2,0},{7,0},{0,0}},
	{ {7,0},{6,0},{8,0},{1,0},{0,0},{2,0},{0,0},{0,0},{0,0}},
	{ {0,0},{3,0},{0,0},{9,0},{7,0},{4,0},{1,0},{6,0},{8,0}},
	{ {0,0},{0,0},{1,0},{0,0},{0,0},{0,0},{6,0},{0,0},{0,0}},
	{ {6,0},{9,0},{3,0},{0,0},{1,0},{5,0},{0,0},{0,0},{2,0}},
	{ {4,0},{0,0},{7,0},{2,0},{0,0},{0,0},{0,0},{3,0},{1,0}}
};

int main() {

	


	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (Grid[i][j][0] != 0) {
				Grid[i][j][1] = 1;
			}
		}
	}

	
	
	if (solve()) {
		cout << "Solvable" << endl;
	}
	else {
		cout << "UnSolvable" << endl;
		return 0;
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			
			cout << Grid[i][j][0] << ", ";
		}
		cout << endl;
	}
	



	return 0;
}

bool solve() {

	return placeNumber(0, 0);

}

bool placeNumber(int row, int colm) {

	

	if (row >= 9) {
		row = 0;
		colm++;
	}
	//cout << row << ", " << colm << endl;
	if (colm >= 9) {
		return true;
	}
	
	int count = 1;
	do {
		

		if (Grid[row][colm][1] == 1) {
			//cout << "Fixed number of " << Grid[row][colm][0] << " at " << row << ", " << colm << endl;
			if (!checkValidity(row, colm)) return false;
			return placeNumber(row + 1, colm);
		}
		else {

			
			do {
				if (count > 9) {
					Grid[row][colm][0] = -1;
					//cout << "Falied to put anything at " << row << ", " << colm << endl;
					return false;
					
				}
				//cout << "Putting " << count << " at " << row << ", " << colm;
				Grid[row][colm][0] = count;
				//cout << " put " << Grid[row][colm][0] << endl;
				count++;

				

			} while (!checkValidity(row, colm));

		}

	} while (!placeNumber(row + 1, colm));

	return true;


}

bool checkValidity(int row, int colm) {

	int temp = Grid[row][colm][0];
	Center a = Center(1, 1);
	Center b = Center(1, 4);
	Center c = Center(1, 7);
	Center d = Center(4, 1);
	Center e = Center(4, 4);
	Center f = Center(4, 7);
	Center g = Center(7, 1);
	Center h = Center(7, 4);
	Center i = Center(7, 7);

	Center centers[9] = { a,b,c,d,e,f,g,h,i };
	Center nearCenter = Center(-1,-1);

	for (int i = 0; i < 9; i++) {
		if (i == colm) continue;
		if (Grid[row][i][0] == temp) {
			
			return false;
		}
	}

	for (int i = 0; i < 9; i++) {
		if (i == row) continue;
		if (Grid[i][colm][0] == temp) {
			
			return false;
		}
	}

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			for (int k = 0; k < 9; k++) {
				if ((row + i) == centers[k].row && (colm + j) == centers[k].colm) {
					nearCenter = centers[k];
					break;
				}
			}
		}
	}

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if ((nearCenter.row + i) == row && (nearCenter.colm + j) == colm) continue;
			if (Grid[nearCenter.row + i][nearCenter.colm + j][0] == temp) {
				
				return false;
			}
		}
	}


	return true;
}