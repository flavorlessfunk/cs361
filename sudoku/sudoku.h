#ifndef SUDOKU_H
#define SUDOKU_H

#include "backtrack.h"

#include <iostream>
#include <vector>

class Sudoku {
public:
  // Create a new puzzle, given a vector of 81 ints
  // in the range 0-9 (0 denotes an initially empty square)
  Sudoku (std::vector<int> initialProblem);

  // Attempt to solve the puzzle.
  void solve();

  bool hasBeenSolved() const {return solved;}


  // Print the puzzle state
  void print (std::ostream&) const;

private:
  std::vector<int> initial;
  bool solved;
  BackTrack problem;

  /* ********************************************** */
  // Utility functions to interpret positions in the 
  // vectors in terms of the squares, rows, and columns
  // of a sudoku puzzle

  // Given a vector position k in the range 0..80

  int square(int k) const;
  // Which of the 9 large squares:
  //    0 1 2
  //    3 4 5
  //    6 7 8

  int innerSquare(int k) const;
  // Which of the 9 small squares with a large square:
  //    0 1 2
  //    3 4 5
  //    6 7 8

  int row(int k) const;
  // Which row (0..8) in the entire puzzle

  int column(int k) const;
  // Which column (0..8) in the entire puzzle


  // Given a outer square # ou and an inner square # in:
  int posBySquare(int ou, int in) const; 
  // returns the equivalent vector position in the range 0..80

  // Given a column and row
  int posByColRow(int col, int row) const;
  // returns the equivalent vector position in the range 0..80
};

inline
std::ostream& operator<< (std::ostream& out, const Sudoku& puzzle)
{
  puzzle.print(out);
  return out;
}


#endif
