#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <vector>
#include <algorithm>

class BackTrack {
public:
  typedef std::vector<unsigned>::const_iterator const_iterator;
  typedef std::vector<unsigned>::const_iterator iterator;

  BackTrack (unsigned nVariables, unsigned arity=2);
  // Create a backtracking state for a problem with
  // nVariables variables, each of which has the same
  // number of possible values (arity).

  template <class Iterator>
  BackTrack (Iterator arityBegin,
	     Iterator arityEnd);
  // Create a backtracking state in which each variable may have
  // a different number of possible values. The values are obtained
  // as integers stored in positions arityBegin .. arityEnd as per
  // the usual conventions for C++ iterators. The number of
  // variables in the system are inferred from the number of
  // positions in the given range.

  unsigned operator[] (unsigned variableNumber) const;
  // Returns the current value associated with the indicated
  // variable.

  unsigned numberOfVariables() const;
  // Returns the number of variables in the backtracking system.

  unsigned arity (unsigned variableNumber) const;
  // Returns the number of potential values that can be assigned
  // to the indicated variable.

  bool more() const;
  // Indicates whether additional candidate solutions exist that
  // can be reached by subsequent ++ or prune operaations.

  void prune (unsigned level);
  // Indicates that the combination of values associated with
  // variables 0 .. level-1 (inclusive) has been judged unacceptable
  // (regardless of the values that could be given to variables
  // level..numberOfVariables()-1.  The backtracking state will advance
  // to the next solution in which at least one of the values in the
  // variables 0..level-1 will have changed.

  BackTrack& operator++();
  // Indicates that the combination of values associated with
  // variables 0 .. nVariables-1 (inclusive) has been judged unacceptable.
  // The backtracking state will advance
  // to the next solution in which at least one of the values in the
  // variables 0..level-1 will have changed.

  BackTrack operator++(int);
  // Same as other operator++, but returns a copy of the old backtrack state


  // Iterator operations for easy access to the currently assigned values
  const_iterator begin() const {return values.begin();}
  iterator begin()             {return values.begin();}

  const_iterator end() const {return values.end();}
  iterator       end()       {return values.end();}

private:
  bool done;
  std::vector<unsigned> arities;
  std::vector<unsigned> values;

};




inline
unsigned BackTrack::operator[] (unsigned variableNumber) const
  // Returns the current value associated with the indicated
  // variable.
{
  return values[variableNumber];
}

inline
unsigned BackTrack::numberOfVariables() const
  // Returns the number of variables in the backtracking system.
{
  return values.size();
}

inline
unsigned BackTrack::arity (unsigned variableNumber) const
  // Returns the number of potential values that can be assigned
  // to the indicated variable.
{
  return arities[variableNumber];
}


inline
bool BackTrack::more() const
  // Indicates whether additional candidate solutions exist that
  // can be reached by subsequent ++ or prune operaations.
{
  return !done;
}

template <class Iterator>
BackTrack::BackTrack (Iterator arityBegin,
		      Iterator arityEnd):
  // Create a backtracking state in which each variable may have
  // a different number of possible values. The values are obtained
  // as integers stored in positions arityBegin .. arityEnd as per
  // the usual conventions for C++ iterators. The number of
  // variables in the system are inferred from the number of
  // positions in the given range.
  done(false), arities(arityBegin, arityEnd)
{
  fill_n (back_inserter(values), arities.size(), 0);
}


#endif
