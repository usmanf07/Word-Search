# CPP Word Search Generator and Searcher by Usman

  [![Word Search](https://i.ibb.co/981H4tD/words.jpg) ](https://en.wikipedia.org/wiki/Word_search)

## Working
* A simple word search game written with c++ code supported to run on Visual Studio 2012. The grids are outputted with words hidden in various ways such as diagonal, vertical, or horizontal with randomly generated characters in empty spaces. 
* Similarly, the search sequence is *case-insensitive* and finds all of the words in the list in all possible 8 directions in the grid. It also saves a list of the words found with their indexes to point to towards their location.

## Usage
* How to run the tool?
  * This tool can be run on Visual Studio 2012 by creating a new CPP project.
  ### Operation:
  * Upon running the program, you will be prompted to choose an option.
  * You can select any of the options from the list by inputting their first letter, i.e, for creating a grid, type "C" or "c".
  * After choosing an option, enter the appropriate file names in which the data is stored.
    ## Note: 
      * File Contents for creating a grid should only contain words.
      * File Contents for searching in a grid should only contain grid in the grid input file and grid dimensions, number of words to be searched, and words in the Data file respectively.
  * Input the other options and your program will start to create or search words in the grid
  * Upon pressing "Q" the program will close and deallocate all of the memory stored on heap.
  
