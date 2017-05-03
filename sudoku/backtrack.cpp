#include "backtrack.h"

#include <vector>
#include <algorithm>

BackTrack::BackTrack (unsigned nVariables, unsigned arity)
  // Create a backtracking state for a problem with
  // nVariables variables, each of which has the same
  // number of possible values (arity).
  : done(false), arities(nVariables, arity), values(nVariables, 0)
{
}


void BackTrack::prune (unsigned level)
  // Indicates that the combination of values associated with
  // variables 0 .. level-1 (inclusive) has been judged unacceptable
  // (regardless of the values that could be given to variables
  // level..numberOfVariables()-1.  The backtracking state will advance
  // to the next solution in which at least one of the values in the
  // variables 0..level-1 will have changed.
{
  level = (level > numberOfVariables()) ? numberOfVariables() : level;
  fill (values.begin()+level, values.end(), 0);
 

  // Treat the top level-1 values as a level-1 digit number. Add one
  // to the rightmost "digit". If this digit goes too high, reset it to
  // zero and "carry one to the left".
  int k = level-1;
  bool carry = true;
  while (k >= 0 && carry)
    {
      values[k] += 1;
      if (values[k] >= arities[k])
	values[k] = 0;
      else
	carry = false;
      --k;
    }
  done = carry;
}
  

BackTrack& BackTrack::operator++()
  // Indicates that the combination of values associated with
  // variables 0 .. nVariables-1 (inclusive) has been judged unacceptable.
  // The backtracking state will advance
  // to the next solution in which at least one of the values in the
  // variables 0..level-1 will have changed.
{
  prune(numberOfVariables());
  return *this;
}

BackTrack BackTrack::operator++(int)
  // Same as other operator++, but returns a copy of the old backtrack state
{
  BackTrack oldValue = *this;
  prune(numberOfVariables());
  return oldValue;
}

