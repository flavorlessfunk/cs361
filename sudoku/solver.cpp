#include <iostream>


#include "sudoku.h"

using namespace std;

int main()
{
  // Reads a sudoku problem from std input as 9 lines of 9 integers.
  // A zero represents a blank square in the original problem.
  // 
  // The program attempts to find and print a solution to the problem.


  vector<int> squares;
  int k;
  for (int line = 0; line < 9; ++line)
    {
      for (int col = 0; col < 9; ++col)
	{
	  cin >> k;
	  squares.push_back(k);
	}
    }

  Sudoku puzzle (squares);
  puzzle.solve();

  if (puzzle.hasBeenSolved())
    cout << puzzle;
  else
    cout << "Unable to solve this puzzle" << endl;

  return 0;
}


