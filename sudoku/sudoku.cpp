#include "sudoku.h"
#include "backtrack.h"

using namespace std;

// Create a new puzzle, given a vector of 81 ints
// in the range 0-9 (0 denotes an initially empty square)
Sudoku::Sudoku (std::vector<int> initialProblem)
  : initial(initialProblem), solved(false), problem(81, 9)
{}




// Attempt to solve the puzzle.
void Sudoku::solve()
{
  // Note - values 0..8 in Backtrack correspond to values 1..9 in the 
  // usual puzzle.
  solved = false;
  int count = 0;
  while ((!solved) && problem.more())
    {
      ++count;
      if (count % 10000 == 0)
	cerr << "Tried " << count << " combinations so far" << endl;

      int pruneAt = -1; 
      for (int k = 0; k < 81 && pruneAt < 0; ++k)
	{
	  // Check to see if assignment to k is consistent with
	  //   initial setup and with assignments to variables 0..k-1
	  
	  // 1: If this square was assigned in the initial problem
	  // reject any attempt to assign it any other value
	  if (initial[k] != 0U && problem[k] != initial[k]-1U)
	    pruneAt = k;

	  // 2: Compare to all other inner squares in the 
	  //    same outer square
	  int nOuterSquare = square(k);
	  int nInnerSquare = innerSquare(k);
	  int krow = row(k);
	  int kcol = column(k);

	  for (int inner = 0; inner < 9 && pruneAt < 0; ++inner)
	    {
	      if (nInnerSquare != inner)
		{
		  int k2 = posBySquare(nOuterSquare, inner);
		  unsigned value = (k2 < k) ? problem[k2] : initial[k2]-1;
		  if (problem[k] == value)
		    pruneAt = k;
		}
	    }
	  
	  // 3: Compare to all other squares in the same row
	  for (int icol = 0; icol < 9 && pruneAt < 0; ++icol)
	    {
	      if (kcol != icol)
		{
		  int k2 = posByColRow(icol, krow);
		  unsigned value = (k2 < k) ? problem[k2] : initial[k2]-1;
		  if (problem[k] == value)
		    pruneAt = k;
		}
	    }

	  // 4: Compare to all other squares in the same column
	  for (int irow = 0; irow < 9 && pruneAt < 0; ++irow)
	    {
	      if (krow != irow)
		{
		  int k2 = posByColRow(kcol, irow);
		  unsigned value = (k2 < k) ? problem[k2] : initial[k2]-1;
		  if (problem[k] == value)
		    pruneAt = k;
		}
	    }
	}

      /*
	 cerr << "pruneAt=" << pruneAt << endl;
	 print(cerr);
      */

      if (pruneAt < 0)
        solved = true;
      else
        problem.prune(pruneAt+1);
    }
}


// Print the puzzle state
void Sudoku::print (std::ostream& out) const
{
  int k = 0;
  for (int line = 0; line < 9; ++line)
    {
      for (int col = 0; col < 9; ++col)
	{
	  out << problem[k]+1 << ' ';
	  if (col % 3 == 2)
	    cout << ' ';
	  k++;
	}
      cout << endl;
      if (line % 3 == 2)
	cout << endl;
    }
}



// Utility functions to interpret positions in the 
// vectors in terms of the squares, rows, and columns
// of a sudoku puzzle

// Given a vector position k in the range 0..80

int Sudoku::square(int k) const
// Which of the 9 large squares:
//    0 1 2
//    3 4 5
//    6 7 8
{
  int r = row(k) / 3;
  int c = column(k) / 3;
  return c + 3 * r;
}

int Sudoku::innerSquare(int k) const
// Which of the 9 small squares with a large square:
//    0 1 2
//    3 4 5
//    6 7 8
{
  int r = row(k) % 3;
  int c = column(k) % 3;
  return c + 3 * r;
}
  

int Sudoku::row(int k) const
  // Which row (0..8) in the entire puzzle
{
  return k / 9;
}

int Sudoku::column(int k) const
  // Which column (0..8) in the entire puzzle
{
  return k % 9;
}

// Given a outer square # ou and an inner square # in:
int Sudoku::posBySquare(int ou, int in) const
  // returns the equivalent vector position in the range 0..80
{
  int r = (ou / 3) * 3;
  int c = (ou % 3) * 3;
  r += in / 3;
  c += in % 3;
  return posByColRow(c, r);
}

// Given a column and row
int Sudoku::posByColRow(int col, int row) const
  // returns the equivalent vector position in the range 0..80
{
  return 9 * row + col;
}