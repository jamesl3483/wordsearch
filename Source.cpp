#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>
using namespace std;


//The main thing is how to solve the puzzle. In the file that the program is saved,
//perhaps there is a board first, and then the answers afterwards, and all the program
//does is find those words. It's doable.

//Also, looking at the example, there is no overlap between the correct answers.

const char alphabets[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

class WordSearchBoard
{
public:
	WordSearchBoard();
	void BuildBoard(int row, int col, int numWords, vector<string> wordList);
	bool isPlaceValid(vector<vector <char>> board, int orientation, string word, int startRow, int startCol);
	void open();	//Open a word search txt file
	void save();	//Save the generated word search
	void solve();
	void display();
	void setDim(int row, int col) {
		this->row = row;
		this->col = col;
	};
	int getRow() {
		return row;
	}
	int getCol() {
		return col;
	}

	void setBoard(vector<vector <char>> board) {
		this->board = board;
	}

	vector<vector <char>> getBoard() {
		return board;
	}

	void setAnswers(vector<string> answerlist) {

		this->answerlist = answerlist;
	}

	vector <string> getAnswers() {
		return answerlist;
	}

private:
	int col, row;
	vector<vector <char>> board;  // row and column spaces  
	vector <string> answerlist;

	//int rowVsColumn();
	//int direction();
	//int orientation();
	//int randomPosition();
	//char randomalpha();



};

WordSearchBoard::WordSearchBoard() {}

//Generation of random words and words in the search
void WordSearchBoard::BuildBoard(int row, int col, int numWords, vector<string> wordList)
{

	vector<vector<char>> board;

	for (int i = 0; i < row; i++)
	{
		board.push_back(vector<char>());
		for (int n = 0; n < col; n++)
		{
			/*int alphaNum = rand() % 26;*/
			board[i].push_back('*'); //Fill the grid with 1 to determine which space is open or not
		}
	}


	//Word Orientation and placement
	for (int i = 0; i < wordList.size(); i++) {
		int orientation = rand() % 4;
		int randRow, randCol = 0;

		//Needs need to protect the words
		// horizontal
		if (orientation == 0) {
			//check if placement is valid
			do
			{
				randRow = rand() % (row - 1);
				randCol = rand() % (col - wordList[i].length() - 1);
			} while (!isPlaceValid(board, 0, wordList[i], randRow, randCol));

			//place the word
			for (int j = 0; j < wordList[i].length(); j++)
				board[randRow][randCol + j] = wordList[i][j];

		}

		// vertical
		if (orientation == 1) {
			//check if placement is valid
			do
			{
				randRow = rand() % (row - wordList[i].length() - 1);
				randCol = rand() % (col - 1);
			} while (!isPlaceValid(board, 1, wordList[i], randRow, randCol));

			//place the word
			for (int j = 0; j < wordList[i].length(); j++)
				board[randRow + j][randCol] = wordList[i][j];

		}

		// left to right Downward Diagonal
		if (orientation == 2) {
			//check if placement is valid
			do
			{
				randRow = rand() % (row - wordList[i].length() - 1);
				randCol = rand() % (col - wordList[i].length() - 1);
			} while (!isPlaceValid(board, 2, wordList[i], randRow, randCol));

			//place the word
			for (int j = 0; j < wordList[i].length(); j++)
				board[randRow + j][randCol + j] = wordList[i][j];

		}



		// right to left Downward Diagonal
		if (orientation == 3) {
			//check if placement is valid
			do
			{
				randRow = rand() % (row - wordList[i].length() - 1);
				randCol = col - rand() % (col - wordList[i].length() - 1);
			} while (!isPlaceValid(board, 3, wordList[i], randRow, randCol));

			//place the word
			for (int j = 0; j < wordList[i].length(); j++)
				board[randRow + j][randCol - j] = wordList[i][j];

		}

	}


	//fill in the random words
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == '*') {
				int alphaNum = rand() % 26;
				board[i][j] = alphabets[alphaNum]; //Fill the grid 

			}
		}
	}

	//Put wordlist in an answer sheet
	setAnswers(wordList);
	setBoard(board);
	setDim(row, col);

}

// Checks if placement of words is valid
bool WordSearchBoard::isPlaceValid(vector<vector <char>> board, int orientation, string word, int startRow, int startCol) {
	if (orientation == 0) {
		for (int j = 1; j <= word.length(); j++) {
			//double check that that the startRow and startCol are within the bounds
			//probably unneccessary
			if (startRow > getRow() || startRow < 0)
				if (startCol > getCol() || startCol < 0)
					return false;

			//check if it is occupied then check if the occupied word could be overlapped
			if (board[startRow][startCol + j] != '*')
				if (board[startRow][startCol + j] != word[j])
					return false;
		}
		return true;
	}
	if (orientation == 1) {
		for (int j = 1; j <= word.length(); j++) {
			if (startRow > getRow() || startRow < 0)
				if (startCol > getCol() || startCol < 0)
					return false;
			if (board[startRow + j][startCol] != '*')
				if (board[startRow + j][startCol] != word[j])
					return false;
		}
		return true;
	}
	if (orientation == 2) {
		for (int j = 1; j <= word.length(); j++) {
			if (startRow > getRow() || startRow < 0)
				if (startCol > getCol() || startCol < 0)
					return false;
			if (board[startRow + j][startCol + j] != '*')
				if (board[startRow + j][startCol + j] != word[j])
					return false;
		}
		return true;
	}
	if (orientation == 3) {
		for (int j = 0; j < word.length(); j++) {
			if (startRow > getRow() || startRow < 0)
				if (startCol > getCol() || startCol < 0)
					return false;
			if (board[startRow + j][startCol - j] != '*')
				if (board[startRow + j][startCol - j] != word[j])
					return false;
		}
		return true;
	}

}

void WordSearchBoard::display() {
	row = getRow();
	col = getCol();

	for (int i = 0; i < row; i++)
	{
		for (int n = 0; n < col; n++)
		{
			cout << board[i][n] << " ";


		}
		cout << endl;
		//cout << "iteration 1";
	}

	cout << endl;
	for (int i = 0; i < answerlist.size(); i++)
	{
		cout << answerlist[i] << endl;
	}
}

void WordSearchBoard::save()
{
	string filename;
	cout << "Enter the filename: \n";
	cin >> filename;

	ofstream fout;
	fout.open(filename);

	cout << "Saving...";

	row = getRow();
	col = getCol();
	for (int i = 0; i < row; i++)
	{
		for (int n = 0; n < col; n++)
		{
			fout.put(board[i][n]);
			fout.put(' ');
		}
		fout.put('\n');
	}


	fout.put('#');
	fout.put('\n');

	for (int i = 0; i < answerlist.size(); i++)
	{
		fout << answerlist[i] << endl;
	}

	fout.close();
	cout << "Save Complete!";
}

void WordSearchBoard::open()
{
	string filename;
	cout << "Enter the file name to be opened: \n";
	cin >> filename;
	ifstream fin;
	fin.open(filename, ios::in);

	if (fin.fail())
	{
		cout << "Input error:\n";
		exit(1);
	}


	string answer;
	vector<string> answerList;
	vector<vector<char>> openedBoard;

	int counter = 0;
	char c;
	int index = 0;
	int openedSize = 0;

	string line;
	while (getline(fin, line))
	{
		vector <char> row;
		bool breakpoint = false;
		for (char c : line)
		{
			if (c == '#')
			{
				breakpoint = true;
				break;
			}
			else if (c != ' ')
			{
				row.push_back(c);
			}
		}
		if (breakpoint)
			break;
		openedBoard.push_back(row);
		openedSize++;
	}

	while (!fin.eof())
	{
		if (fin >> answer) {
			answerList.push_back(answer);
		}
	}

	//update all values
	setAnswers(answerList);
	setBoard(openedBoard);
	setDim(openedBoard[0].size(), openedSize);

}

void WordSearchBoard::solve()
{
	open();
	vector<vector <char>> solvedBoard;
	for (int i = 0; i < row; i++)
	{
		solvedBoard.push_back(vector<char>());
		for (int n = 0; n < col; n++)
		{
			solvedBoard[i].push_back(' ');
		}
	}


	for (int i = 0; i < row; i++)
	{
		for (int n = 0; n < col; n++)
		{
			bool solved = false;
			for (int index = 0; index < answerlist.size(); index++)
			{
				string answer = answerlist[index];
				int answerSize = answer.length();
				int counter = 0;
				if (board[i][n] == answer[counter])
				{
					counter++;
					//Horizontal
					if ((answerSize + n < col) && board[i][n + 1] == answer[counter])
					{
						int indexOne = n + 1;
						char x = board[i][indexOne], y = answer[counter];
						while (counter < answerSize && x == y)
						{
							indexOne++;
							counter++;
							if (counter == answerSize)
								solved = true;
							x = board[i][indexOne];
							y = answer[counter];
						}
						if (solved) {
							for (int j = n; j < n + counter; j++) {
								solvedBoard[i][j] = board[i][j];
							}
						}


					}

					//For backwards detection
					/*if ((n - answerSize > 0))
					{
						if (board[i][n - 1] == answer[counter])
						{
							int indexOne = n - 1;
							char x = board[i][indexOne], y = answer[counter];
							while (counter < answerSize && x == y)
							{
								indexOne--;
								counter++;
								if (counter == answerSize)
									possible = true;

							}
							if (possible)
							{
								direction[index] = 1;
								orient[index] = 2;
								startingpos[index][0] = i;
								startingpos[index][1] = n;
							}
						}*/


						//Vertical
					if ((answerSize + i < row) && board[i + 1][n] == answer[counter])
					{
						int indexOne = i + 1;
						char x = board[indexOne][n], y = answer[counter];
						while (counter < answerSize && x == y)
						{
							indexOne++;
							counter++;
							if (counter == answerSize)
								solved = true;
							x = board[indexOne][n];
							y = answer[counter];
						}
						if (solved) {
							for (int j = i; j < i + counter; j++) {
								solvedBoard[j][n] = board[j][n];
							}
						}
					}
					//reversed
					/*if ((i - answerSize > 0))
					{
						if (board[i - 1][n] == answer[counter])
						{
							int indexOne = i - 1;
							char x = board[indexOne][n], y = answer[counter];
							while (counter < answerSize && x == y)
							{
								indexOne--;
								counter++;
								if (counter == answerSize)
									possible = true;

							}
							if (possible)
							{
								direction[index] = 2;
								orient[index] = 2;
								startingpos[index][0] = i;
								startingpos[index][1] = n;
							}
						}
					}*/

					//Diagonal
					if ((answerSize + i < row) && (answerSize + n < col) && board[i + 1][n + 1] == answer[counter])
					{
						int indexOne = i + 1;
						int indexTwo = n + 1;
						char x = board[indexOne][indexTwo], y = answer[counter];
						while (counter < answerSize && x == y)
						{
							indexOne++;
							indexTwo++;
							counter++;
							if (counter == answerSize)
								solved = true;
							x = board[indexOne][indexTwo];
							y = answer[counter];
						}
						if (solved) {
							int j = i;
							int a = n;
							while (j < i + counter) {
								solvedBoard[j][a] = board[j][a];
								a++;
								j++;
							}
						}
					}

					if ((answerSize + i < row) && (n - answerSize > 0) && board[i + 1][n - 1] == answer[counter])
					{
						if (board[i + 1][n - 1] == answer[counter])
						{
							int indexOne = i + 1;
							int indexTwo = n - 1;
							char x = board[indexOne][indexTwo], y = answer[counter];
							while (counter < answerSize && x == y)
							{
								indexOne++;
								indexTwo--;
								counter++;
								if (counter == answerSize)
									solved = true;
								x = board[indexOne][indexTwo];
								y = answer[counter];
							}
							if (solved) {
								int j = i;
								int a = n;
								while (j < i + counter) {
									solvedBoard[j][a] = board[j][a];
									a--;
									j++;
								}
							}
						}
					}


				}
			}
		}
	}

	for (int i = 0; i < row; i++)
	{
		for (int n = 0; n < col; n++)
		{
			cout << solvedBoard[i][n];
		}
		cout << endl;
	}
}


int Menu();
void create();

int main()
{
	srand(time(NULL));
	int reply = 0;
	WordSearchBoard mainBoard;
	while (reply != 4)
	{
		reply = Menu();
		switch (reply)
		{
		case 1: {
			create();
			break;
		}
		case 2: {
			WordSearchBoard x;
			x.open();
			x.display();
			break;
		}
		case 3: {
			mainBoard.solve();
			break;
		}
		default: break;
		}
	}

}


// menu of options in the beginning
int Menu()
{
	int reply;
	cout << "Choose an option:\n"
		<< "(1) Create a new puzzle.\n"
		<< "(2) Open an existing puzzle.\n"
		<< "(3) Solve an existing puzzle.\n"
		<< "(4) Exit\n";
	cin >> reply;
	return reply;
}

// Create the crossword
void create()
{
	int numWords;
	cout << "Enter the number of words you\n would like in the puzzle:\n";
	cin >> numWords;

	vector<string> wordList;
	int minSize = 0;	// minimum size of the board

	string wordinput;;
	for (int i = 0; i < numWords; i++)
	{
		cout << "Enter the word: ";
		cin >> wordinput;
		bool letters = true;
		wordList.push_back(wordinput);
		if (wordinput.length() > minSize)
		{
			minSize = wordinput.length();
		}
		cin.ignore();

	}



	// Board Creation
	WordSearchBoard wordboard;
	wordboard.BuildBoard(minSize + 4, minSize + 4, numWords, wordList);
	wordboard.display();
	char reply;
	cout << "Would you like to save the puzzle? [y/n]\n";
	cin >> reply;

	if (reply == 'y' || reply == 'Y')
	{
		wordboard.save();
	}

}

