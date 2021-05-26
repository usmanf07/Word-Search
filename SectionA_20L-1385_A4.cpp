#include <iostream>

#include <fstream>

#include <cstring>

#include <string>

#include <cstdlib>

using namespace std;
 
class WordSearch
{

private:

	char ** bufferToChar(int size1, char tempBuffer[][50]);
	bool diagonalTopLeft(char ** Grid, char * word, int rows, int cols, int Row, int Col);
	bool diagonalTopRight(char ** Grid, char * word, int rows, int cols, int Row, int Col);
	bool diagonalBottomRight(char ** Grid, char * word, int rows, int cols, int Row, int Col);
	bool diagonalBottomLeft(char ** Grid, char * word, int rows, int cols, int Row, int Col);
	bool horizontalLeft(char ** Grid, char * word, int rows, int cols, int Row, int Col);
	bool horizontalRight(char ** Grid, char * word, int rows, int cols, int Row, int Col);
	bool verticalUp(char ** Grid, char * word, int rows, int cols, int Row, int Col);
	bool verticalDown(char ** Grid, char * word, int rows, int cols, int Row, int Col);

	bool searchWords(char** Grid, int row, int col, string word, int gridRows, int gridCols,int& positionFound);
	void saveWordPosition(int **savePositions, int size, string outputFile, string dataFile);
	
public:

	WordSearch();
	~WordSearch();
	void initializeGrid(char ** Grid, int rows, int cols);
	void outputGrid(char ** Grid, int rows, int cols);
	char ** inputWords(int & size, int & wordLength, string fileName);
	void makeGrid(char ** Grid, char ** Words, int rows, int cols, int totalwords);
	void fillEmptySpace(char ** Grid, int rows, int cols);
	void saveGrid(char ** Grid, int rows, int cols, string fileName);
	void deallocateMemory(char ** Grid, int size);
	char ** inputGrid(int &rows, int &cols, int &totalWords, string dataFile, string gridFile);
	void searchWords(char ** Grid, int rows, int cols, int totalWords, string dataFile, string outputFile);
	
};


WordSearch::WordSearch() {
  //Constructor
}

//Function requires 2D array and its rows to return pointer array allocated on heap
char ** WordSearch::bufferToChar(int size, char tempBuffer[][50]) {
  //Getting String from buffer and allocating space on stack and heap
  char ** pointer = new char * [size];

  char ** tempDest = pointer;

  for (int i = 0; i < size; i++) {
    int strLen = strlen(tempBuffer[i]);
    pointer[i] = new char[strLen + 1];

    int j = 0;

    for (char * tempSrc = tempBuffer[i];* tempSrc != '\0'; tempSrc++, j++) {

      tempDest[i][j] = * tempSrc;

    }
    tempDest[i][j] = '\0'; //Placing null element at the end

  }

  return tempDest;
}

//Function requires size and word length passed as reference and returns the Words Grid
char ** WordSearch::inputWords(int & size, int & wordLength, string fileName) {

  char tempGrid[50][50] = {}; //Making a temp grid
  char temp[80];
  int maxLength = 0;
  int charLen = 0;

  int count = 0;

  ifstream fin(fileName);

  if (fin.is_open()) {

    while (count < size) {

      fin.getline(temp, 80);
      int length = strlen(temp);
      // Converting uppercase characters to lowercase
      for (int i = 0; i < length; i++) {
        if (islower(temp[i]))

          temp[i] = temp[i] - 32;
      }

      length = strlen(temp);
      //Removing spaces from words if any
      int j = 0;
      for (int i = 0; i < length; i++) {

        if (temp[i] != ' ') {
          tempGrid[count][j] = temp[i];
          j++;
        }
      }

      charLen = strlen(tempGrid[count]);

      count++;
      
      if (charLen > maxLength)
        maxLength = charLen;

    }
    fin.close();
  } 

  else
  {
    cout << "Error:	Cannot open the file! Make sure the file exists in the same folder and the format is TXT." << endl;
	return 0;
  }

  WordSearch buffer;
  char ** newGrid = buffer.bufferToChar(size, tempGrid); //Allocating and storing words in dynamic pointer array

  wordLength = maxLength;

  return newGrid;
}

//Function to initialize the Grid to * before storing words
//This function requires a Pointer Char Array and its Size to initialize it
void WordSearch::initializeGrid(char ** Grid, int rows, int cols) {

  int i, j;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      Grid[i][j] = '*';
	}
    Grid[i][j] = '\0';
  }

}

//Function to output the Grid on console
//This function requires a Pointer Char Array and its Size to display it
void WordSearch::outputGrid(char ** Grid, int rows, int cols) {

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << Grid[i][j] << " ";
    }
    cout << endl;
  }

}

//Function to make the grid by inputing words and generating random letters
//This function requires a Grid, Grid Size, Words List and total Words to make a Word Search Grid
void WordSearch::makeGrid(char ** Grid, char ** Words, int rows, int cols, int totalWords) {

  WordSearch Generate;

  bool flag = false;
  int check = 0;
  int noSpaceCheck = 0;

  //loop for inputting words in the grid
  while (check < totalWords) 
  {
	  int placementRow = rand() % rows; //Random Row and Column placement
	  int placementCol = rand() % cols;
	  int direction = rand()%8;  

    if (direction == 0 && !flag) 
	{
		if (Generate.diagonalTopLeft(Grid, Words[check], rows, cols, placementRow, placementCol) == true) 
		{
			flag = true;
			direction = 1;
		} 

		else{ 
			flag = false;
			direction = 1;
		}
    }

    if (direction == 1 && !flag) 
	{

      if (Generate.verticalDown(Grid, Words[check], rows, cols, placementRow, placementCol) == true) 
	  {
        flag = true;
		direction = 2;
      }

	  else{ 
			flag = false;
			direction = 2;
		}
      
    }

    if (direction == 2 && !flag) 
	{
      if (Generate.horizontalLeft(Grid, Words[check], rows, cols, placementRow, placementCol) == true) 
	  {
        flag = true;
        direction = 3;
      } 

	 else{ 
			flag = false;
			direction = 3;
		}

    }

    if (direction == 3 && !flag) 
	{
      if (Generate.diagonalBottomLeft(Grid, Words[check], rows, cols, placementRow, placementCol) == true) 
	  {
        flag = true;
        direction = 4;
      } 

	  else{ 
			flag = false;
			direction = 4;
		}

    }

    if (direction == 4 && !flag) 
	{

      if (Generate.horizontalRight(Grid, Words[check], rows, cols, placementRow, placementCol) == true) 
	  {
        flag = true;
        direction = 5;
      } 

	  else{ 
			flag = false;
			direction = 5;
		}
      
    }

    if (direction == 5 && !flag) 
	{
      if (Generate.diagonalTopRight(Grid, Words[check], rows, cols, placementRow, placementCol) == true) 
	  {
        flag = true;
        direction = 6;
      } 

	  else{ 
			flag = false;
			direction = 6;
		}
    }

    if (direction == 6 && !flag) 
	{

      if (Generate.verticalUp(Grid, Words[check], rows, cols, placementRow, placementCol) == true) 
	  {
        flag = true;
        direction = 7;
	  }

	  else{ 
			flag = false;
			direction = 7;
		}

    }

    if (direction == 7 && !flag) 
	{
      if (Generate.diagonalBottomRight(Grid, Words[check], rows, cols, placementRow, placementCol) == true) 
	  {
        flag = true;
        direction = rand()%8;
      } 

	  else{ 
			flag = false;
			direction = rand()%8;
		}
    }

    //If the word isn't placed anywhere, generate new random rows and cols
    if (!flag) 
	{
	  noSpaceCheck++;
      placementRow = rand() % rows;
      placementCol = rand() % cols;
	  direction = rand()%8;
    } 
	else{
      check++;
	  noSpaceCheck = 0;
	}

	if(noSpaceCheck == 1000)
	{
		cout<<"The word "<<Words[check]<<" cannot be placed in the grid due to not enough space available!"<<endl;
		check++;
		noSpaceCheck = 0;
	}

	flag = false;

  }

  if(check == totalWords)
	cout << "Word Search Generated Successfully!" << endl << endl;

}

//Function to input a word in the Grid Vertically from Up to Down
//This function requires a Grid, Word, grid Size, random rows and cols
bool WordSearch::verticalUp(char ** Grid, char * word, int rows, int cols, int Row, int Col) {

  int strLen = strlen(word);

  int rowLength = Row + strLen;

  int colLength = Col;

  int counter = 0;

  //Loop to calculate if the length is same as found in the grid
  if (rowLength <= rows && colLength < cols)
    for (int i = Row; i < rowLength; i++)
      if (Grid[i][Col] == '*')
        counter++;

  if (counter == strLen && rowLength <= rows && colLength < cols) 
  {
    int k = 0;
		//Loop for placing the word in the grid
		for (int i = Row; i < rowLength; i++) 
		{
		  Grid[i][Col] = word[k];
		  k++;
		}

    return true; //Return True if the word is placed, else return false
  }

  return false;

}

//Function to input a word in the Grid Vertically from Down to Up
//This function requires a Grid, Word, grid Size, random rows and cols
bool WordSearch::verticalDown(char ** Grid, char * word, int rows, int cols, int Row, int Col) {

  int strLen = strlen(word);

  int rowLength = Row - strLen;

  int colLength = Col;

  int counter = 0;

  //Loop to calculate if the length is same as found in the grid
  if (rowLength >= -1 && colLength < cols)
    for (int i = Row; i > rowLength; i--)
      if (Grid[i][Col] == '*')
        counter++;

  //Loop for placing the word in the grid
  if (counter == strLen && rowLength >= -1 && colLength < cols) 
  {
		int k = 0;

		for (int i = Row; i > rowLength; i--) 
		{
		  Grid[i][Col] = word[k];
		  k++;
		}

    return true; //Return True if the word is placed, else return false
  }

  return false;

}

//Function to input a word in the Grid Diagonally from Top Left to Bottom Right
//This function requires a Grid, Word, grid Size, random rows and cols
bool WordSearch::diagonalTopLeft(char ** Grid, char * word, int rows, int cols, int Row, int Col) {

  int strLen = strlen(word);

  int rowLength = Row + strLen;

  int colLength = Col + strLen;

  int counter = 0;

  //Loop to calculate if the length is same as found in the grid
  if (rowLength <= rows && colLength <= cols)
    for (int i = Row, j = Col; i < rowLength; i++, j++)
      if (Grid[i][j] == '*')
        counter++;

  if (rowLength <= rows && colLength <= cols && counter == strLen) 
  {

		int j = Col;
		int k = 0;
		 //Loop for placing the word in the grid
		for (int i = Row, k = 0, j = Col; i < rowLength; i++) 
		{
		  Grid[i][j] = word[k];
		  j++;
		  k++;
		}
    return true; //Return True if the word is placed, else return false
  }

  return false;

}

//Function to input a word in the Grid Diagonally from Top Right to Bottom Left
//This function requires a Grid, Word, grid Size, random rows and cols
bool WordSearch::diagonalTopRight(char ** Grid, char * word, int rows, int cols, int Row, int Col) {

  int strLen = strlen(word);

  int rowLength = Row + strLen;

  int colLength = Col - strLen;

  int counter = 0;

  //Loop to calculate if the length is same as found in the grid
  if (rowLength <= rows && colLength >= -1)
    for (int i = Row, j = Col; j > colLength; i++, j--)
      if (Grid[i][j] == '*')
        counter++;

  if (rowLength <= rows && colLength >= -1 && counter == strLen) 
  {

    int j = Col;
    int k = 0;

    //Loop for placing the word in the grid
    for (int i = Row, k = 0, j = Col; j > colLength; i++) 
	{
      Grid[i][j] = word[k];
      j--;
      k++;
    }
    return true; //Return True if the word is placed, else return false
  }

  return false;

}

//Function to input a word in the Grid Diagonally from Bottom Right to Top Left
//This function requires a Grid, Word, grid Size, random rows and cols
bool WordSearch::diagonalBottomRight(char ** Grid, char * word, int rows, int cols, int Row, int Col) {

  int strLen = strlen(word);

  int rowLength = Row - strLen;

  int colLength = Col - strLen;

  int counter = 0;

  //Loop to calculate if the length is same as found in the grid
  if (rowLength >= -1 && colLength >= -1)
    for (int i = Row, j = Col; i > rowLength; i--, j--)
      if (Grid[i][j] == '*')
        counter++;

  if (rowLength >= -1 && colLength >= -1 && counter == strLen) 
  {

    int j = Col;
    int k = 0;

    //Loop for placing the word in the grid

    for (int i = Row, k = 0, j = Col; i > rowLength; i--) 
	{
      Grid[i][j] = word[k];
      j--;
      k++;
    }
    return true; //Return True if the word is placed, else return false
  }

  return false;

}

//Function to input a word in the Grid Diagonally from Bottom Left to Top Right
//This function requires a Grid, Word, grid Size, random rows and cols
bool WordSearch::diagonalBottomLeft(char ** Grid, char * word, int rows, int cols, int Row, int Col) {

  int strLen = strlen(word);

  int rowLength = Row - strLen;

  int colLength = Col + strLen;

  int counter = 0;

  //Loop to calculate if the length is same as found in the grid
  if (rowLength >= -1 && colLength <= cols)
    for (int i = Row, j = Col; i > rowLength; i--, j++)
      if (Grid[i][j] == '*')
        counter++;

  if (rowLength >= -1 && colLength <= cols && counter == strLen) 
  {

    int j = Col;
    int k = 0;
    //Loop for placing the word in the grid
    for (int i = Row, k = 0, j = Col; i > rowLength; i--) 
	{
      Grid[i][j] = word[k];
      j++;
      k++;
    }
    return true; //Return True if the word is placed, else return false
  }

  return false;

}

//Function to input a word in the Grid Horizontally from Left to Right
//This function requires a Grid, Word, grid Size, random rows and cols
bool WordSearch::horizontalLeft(char ** Grid, char * word, int rows, int cols, int Row, int Col) {

  int strLen = strlen(word);

  int rowLength = Row;

  int colLength = Col + strLen;

  int counter = 0;
  //Loop to calculate if the length is same as found in the grid
  if (rowLength <rows && colLength <= cols)
    for (int j = Col; j < colLength; j++)
      if (Grid[Row][j] == '*')
        counter++;

  if (counter == strLen && rowLength < rows && colLength <= cols) 
  {
    int k = 0;
    //Loop for placing the word in the grid
    for (int j = Col; j < colLength; j++) 
	{
      Grid[Row][j] = word[k];
      k++;
    }

    return true; //Return True if the word is placed, else return false
  }

  return false;

}
//Function to input a word in the Grid Horizontally from Right to Left
//This function requires a Grid, Word, grid Size, random rows and cols
bool WordSearch::horizontalRight(char ** Grid, char * word, int rows, int cols, int Row, int Col) {

  int strLen = strlen(word);

  int rowLength = Row;

  int colLength = Col - strLen;

  int counter = 0;
  //Loop to calculate if the length is same as found in the grid
  if (rowLength < rows && colLength >= -1)
    for (int j = Col; j > colLength; j--)
      if (Grid[Row][j] == '*')
        counter++;

  if (counter == strLen && rowLength < rows && colLength >= -1) {
    int k = 0;
    //Loop for placing the word in the grid
    for (int j = Col; j > colLength; j--) {
      Grid[Row][j] = word[k];
      k++;
    }

    return true; //Return True if the word is placed, else return false
  }

  return false;

}

//Function to fill the empty space in the Grid by generating random chars
//This function requires a Grid and its Size
void WordSearch::fillEmptySpace(char ** Grid, int rows, int cols) {

  char randomChar;
  int smallChar = 0;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      randomChar = 'a' + rand() % 26 - 32;
      if (Grid[i][j] == '*')
        Grid[i][j] = randomChar;
    }
  }
}

//Function to save the generated Word Search in a file named output.txt
//This function requires a Grid and its size and File Name
void WordSearch::saveGrid(char ** Grid, int rows, int cols, string fileName) {

  ofstream fout(fileName);

  if (fout.fail()) 
  {
    cout << "Error:	Cannot save the file! Make Sure the format is correct." << endl;
  } 

  else 
  {
    for (int i = 0; i < rows; i++) 
	{
      for (int j = 0; j < cols; j++) 
	  {
		  if (j == cols - 1)
			  fout << Grid[i][j];
		  else
		  fout << Grid[i][j] << " ";
      }
	  if (i != rows - 1)
		fout << endl;
    }
    cout << "\nWord Search Saved Successfully in the file named " << fileName <<endl;
  }
  fout.close();
}

//Function for Deallocating Memory of dynamic arrays
void WordSearch::deallocateMemory(char ** Grid, int size) {

  for (int i = 0; i < size; i++)
    delete[] Grid[i];

  delete[] Grid;
}

//Function for inputting the Grid stored in a file named "inputGrid.txt"
//It requires rows, cols and total Words passed as reference
char ** WordSearch::inputGrid(int & rows, int & cols, int & totalWords, string dataFile, string gridFile) {

  char tempGrid[50][50] = {
    '\0'
  };;

  ifstream dimensions(dataFile);

  if (dimensions.is_open()) {
    dimensions >> rows >> cols >> totalWords;
  }

  ifstream fin(gridFile);

  if (fin.is_open()) {
    cout << "Grid Loaded Successfully!" << endl;
    while (!fin.eof()) {

      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          fin >> tempGrid[i][j];
        }
      }

    }

    fin.close();

    WordSearch buffer;
    char ** newGrid = buffer.bufferToChar(rows, tempGrid);
    return newGrid;

  } 

  else 
  {
    cout << "Error:	Cannot open the file! Make sure the file exists in the same folder and the format is TXT." << endl;
    return 0;
  }

}

bool WordSearch::searchWords(char ** Grid, int row, int col, string word, int gridRows, int gridCols, int & positionFound) {
  //Initializing All Directions for a word
  int x_dir[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int y_dir[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  //If the grid row and col doesnot match with first letter return false
  if (Grid[row][col] != word[0])
	  if (Grid[row][col] != toupper(word[0]))
			return false;
  
  int strLen = word.length();

  for (int i = 0; i < 8; i++) {

    int j, RandomRow = row + x_dir[i], RandomCol = col + y_dir[i];

    //Continuing loop in same direction for all remaining letters
    for (j = 1; j < strLen; j++) {

      if (RandomRow >= gridRows || RandomRow < 0 || RandomCol >= gridCols || RandomCol < 0)
        break;

      if ((Grid[RandomRow][RandomCol]) != word[j])
		  if(Grid[RandomRow][RandomCol] != toupper(word[j]))
			 break;

      RandomRow += x_dir[i], RandomCol += y_dir[i];
    }

    //If length is same as the word's change its position and return true
    if (j == strLen) {
      positionFound = i;
      return true;
    }
  }
  return false;
}

//Function for inputting the Grid stored in a file named "WordsFound.txt"
//It requires Dynamic Coordinates Array, its size
void WordSearch::saveWordPosition(int ** savePositions, int size, string outputFile, string dataFile) {
	
  ofstream fout(outputFile);
  ifstream Words(dataFile);

  WordSearch WordsFound;
  int ignore;
  string SearchString;
  
  //Ignorning the dimensions as they were already used
  Words >> ignore;
  Words >> ignore;
  Words >> ignore;
  
  for (int i = 0; i < size; i++) {
	   Words >> SearchString;
	   cout << SearchString <<" is ";
    if (savePositions[i][0] == 99) {
      fout << "Not Found";
      fout << endl;
	  cout << "cannot be found";
      cout << endl;
    } else {
      fout << "{" << savePositions[i][0] << "," << savePositions[i][1] << "}" << "{" << savePositions[i][2] << "," << savePositions[i][3] << "}" << endl;
	  cout << "at index : {" << savePositions[i][0] << "," << savePositions[i][1] << "}" << "{" << savePositions[i][2] << "," << savePositions[i][3] << "}" << endl;
    }
  }
  
  //Deallocating Memory of integer array
   for (int i = 0; i < size; i++)
		delete[] savePositions[i];

  delete[] savePositions;

  fout.close();
}

//Function for searching the words stored in file "Data.txt" in the Grid
//It requires Dynamic Coordinates Array, its rows and columns, and total Words passed as referrence
void WordSearch::searchWords(char ** Grid, int rows, int cols, int totalWords, string dataFile, string outputFile) {

  int StartingRow = 0, StartingCol = 0, EndingRow = 0, EndingCol = 0;
  WordSearch SearchWords;
  string SearchString;
  int Dir = 0;
  int count = 0;
  int check = 0;
  int ignore;

  ifstream Words(dataFile);

  //Ignorning the dimensions as they were already used
  Words >> ignore;
  Words >> ignore;
  Words >> ignore;

  if (Words.is_open()) {

    //Allocating Dynamic array to save words coordinates
    int ** savePositions = new int * [totalWords];

    for (int x = 0; x < totalWords; x++)
      savePositions[x] = new int[4];

    int i = 0, j = 0;
    while (count < totalWords) {
      check = 0;
	  Words >> SearchString;
      Dir = 0;
      for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
          if (searchWords(Grid, row, col, SearchString, rows, cols, Dir)) {
            check = 1;

            StartingRow = row;
            StartingCol = col;
            //Conditions to check the word at which direction it is found to store the ending row and col
            if (Dir == 0) {
              EndingRow = StartingRow - SearchString.length() + 1;
              EndingCol = StartingCol - SearchString.length() + 1;

            }
            if (Dir == 1) {
              EndingRow = StartingRow - SearchString.length() + 1;
              EndingCol = StartingCol;

            }
            if (Dir == 2) {
              EndingRow = StartingRow - SearchString.length() + 1;
              EndingCol = StartingCol;

            }
            if (Dir == 3) {
              EndingRow = StartingRow;
              EndingCol = StartingCol - SearchString.length() + 1;

            }
            if (Dir == 4) {
              EndingRow = StartingRow;
              EndingCol = StartingCol + SearchString.length() - 1;

            }
            if (Dir == 5) {
              EndingRow = StartingRow + SearchString.length() - 1;
              EndingCol = StartingCol - SearchString.length() + 1;

            }
            if (Dir == 6) {
              EndingRow = StartingRow + SearchString.length() - 1;
              EndingCol = StartingCol;

            }

            if (Dir == 7) {
              EndingRow = StartingRow + SearchString.length() - 1;
              EndingCol = StartingCol + SearchString.length() - 1;;

            }

            savePositions[i][j] = row;
            j++;
            savePositions[i][j] = col;
            j++;
            savePositions[i][j] = EndingRow;
            j++;
            savePositions[i][j] = EndingCol;
            i++;
            j = 0;
          }

        }

      }

      if (check == 0) {

        savePositions[i][j] = 99;
        j++;
        savePositions[i][j] = 99;
        j++;
        savePositions[i][j] = 99;
        j++;
        savePositions[i][j] = 99;
        i++;
        j = 0;
      }

      count++;
    }
    //Svaing each word's position
    saveWordPosition(savePositions, totalWords, outputFile, dataFile);
    cout << "\nAll Words Coordinates saved in the file named WordsFound.txt" << endl << endl;
    Words.close();
  } else {
    cout << "Error:	Cannot open the file! Make sure the file exists in the same folder and the format is TXT." << endl;
  }

}

WordSearch::~WordSearch() {
  //Destructor
}

int main() 
{

	string option;
	int optionCheck = 0;
	
	if(islower(option[0]))
		option[0] = option[0] - 32;

option = "x";
while(option != "Q")
{
	system("Color 07");
	cout<<"\t\t\t\t---------------------------------"<<endl;
	cout<<"\t\t\t\t\t  !WORD SEARCH!"<<endl<<endl;
	cout<<"\t\t\t\t\tChoose an option:"<<endl<<endl;
	cout<<"\t\t\t\t\t1) Create Grid\n\t\t\t\t  2) Search words from grid\n\t\t\t\t\t  3) Quit"<<endl;
	cout<<"\t\t\t\t---------------------------------"<<endl;
	cout<<"Enter your option: "<<endl;
	cin>>option;
	if(islower(option[0]))
			option[0] = option[0] - 32;
	while(option != "Q"  && option != "C" && option != "S" ){
		cout<<"No such option exists, Please try again!"<<endl;
		cin>>option;
		if(islower(option[0]))
			option[0] = option[0] - 32;
	}

	if(option == "Q")
		break;

  if(option == "C")
  {
	  system("cls");
	  system("Color 70");
	  cout<<"Option Selected: Create Grid!"<<endl;
	  string inputFileName;
	  string outputFileName;
	  int rows = 0, cols = 0;
	  cout<<"Please enter the name of the input file: "<<endl;
	  cin>>inputFileName;

	  int totalWords = 0;
	  cout<<"Please enter the number of total words in the file: "<<endl;
	  cin>>totalWords;
	  cout<<"Number of rows in the grid\n";
	  cin>>rows;
	  cout<<"Number of cols in the grid\n";
	  cin>>cols;
	  cout<<"Please enter the name of the output file: "<<endl;
	  cin>>outputFileName;
	  WordSearch Search;
	
	  int largestWord = 0;
	
	  char ** loadedGrid = Search.inputWords(totalWords, largestWord, inputFileName);
	  if(rows < largestWord && cols < largestWord)
		  cout<<"The grid cannot be formed with the given dimensions"<<endl<<endl;

	  else
	  {
		  char ** wordSearch = new char * [rows];
	
		  for (int i = 0; i < rows; i++)
			wordSearch[i] = new char[cols + 1];
	
		  Search.initializeGrid(wordSearch, rows, cols);
	  
		  Search.makeGrid(wordSearch, loadedGrid, rows, cols, totalWords);
		  Search.fillEmptySpace(wordSearch, rows, cols);
		  Search.outputGrid(wordSearch, rows, cols);
		  Search.saveGrid(wordSearch, rows, cols, outputFileName);
		  //Deallocating Memory
  		  Search.deallocateMemory(wordSearch, rows);
  		  Search.deallocateMemory(loadedGrid, totalWords);
	  }
   }

  if(option == "S")
  {
	  system("cls");
	  system("Color 20");
	  cout<<"Option Selected: Search Words!"<<endl;
	  WordSearch Find;
	  string inputGridFile;
	  cout<<"Please enter the name of the input file which contains the grid: "<<endl;
	  cin>>inputGridFile;

	  string dataFile;
	  cout<<"Please enter the name of the input file which contains the dimensions and words: "<<endl;
	  cin>>dataFile;

	  string outputWords;
	  cout<<"Please enter the name of the output file which will contain the words found: "<<endl;
	  cin>>outputWords;

	  int totalWords = 0;
	  int rows = 0, cols = 0;
	
	  char ** charGrid = Find.inputGrid(rows, cols, totalWords, dataFile, inputGridFile);
	  cout<<"\nWords Found: "<<endl;
	  Find.searchWords(charGrid, rows, cols, totalWords, dataFile, outputWords);
	  Find.outputGrid(charGrid, rows, cols);
	  //Deallocating Memory
	  Find.deallocateMemory(charGrid, rows);

  }
	cout<<"Press any key to return to the Main Menu or Press Q to quit the program: "<<endl;
	cin>>option;

	if(option == "q" || option == "Q")
		break;
	else
		system("cls");
	
}
  cout<<"Thank you for using Our Word Search Program, See soon again!"<<endl;
  return 0;
}
