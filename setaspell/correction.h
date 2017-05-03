#ifndef CORRECTION_H
#define CORRECTION_H

#include "wordoccurrence.h"


class Correction
//
// A correction consists of a word occurrence that has been judged to
// be misspelled and a string representing the replacement spelling.
// (Note that the replacement is not necessarily a "word" as the 
// correction might involve other characters, for example correcting "tothe"
// to "to the".)

{
public:

  Correction();
  //post: getMisspelling() == WordOccurrence()
  //      && getReplacement() == ""

  Correction (const WordOccurrence& wo,
	      const std::string& replacement);
  //post: getMisspelling() == wo
  //      && getReplacement() == replacement


  WordOccurrence getMisspelling() const             {return _misspelling;}
  void putMisspelling (const WordOccurrence& missp) {_misspelling = missp;}

  std::string getReplacement() const            {return _replacement;}
  void putReplacement (const std::string& repl) {_replacement = repl;}


  // Output (mainly for debugging purposes)
  void put (std::ostream&) const;


private:
  WordOccurrence _misspelling;
  std::string _replacement;
};


inline
std::ostream& operator<< (std::ostream& out,
			  const Correction& correction)
{
  correction.put (out);
  return out;
}



bool operator< (const Correction& left, const Correction& right);
bool operator== (const Correction& left, const Correction& right);



#endif
