#ifndef WORDOCCURRENCE_H
#define WORDOCCURRENCE_H

#include "token.h"


class WordOccurrence 
//
// A "word" is a string that beings with an alphnumberic character,
// continues with 0 or more of the same characters, hyphens, or apostrophes,
// and ends with an alphanumeric character. For example,
//    the 2nd wasn't how-do-you-do
// are all words, but
//    ./? Yes? 123 multi-
// are not.
//
// A word occurrence describes a word within a document, combining a 
// "lexeme" (the string of characters) that comprise a word with the
// location within the document where the word was found.

{
public:
  typedef Token::Location Location;
  
  WordOccurrence();
  //post: getLexeme()=="" && getLocation()==0

  WordOccurrence (const std::string& lexeme,
		  Location location);

  // A "lexeme" is the string of characters that has been identified
  // as constituting a token.
  std::string getLexeme() const           {return tok.getLexeme();}
  void putLexeme (const std::string& lex) {tok.putLexeme (lex);}

  // The location indicates where in the original file the first character of
  // a token's lexeme was found.
  Location getLocation() const {return tok.getLocation();}
  void putLocation (const Location& loc)  {tok.putLocation(loc);}



  // Read a word from a stream.
  bool read(std::istream& input);
  

  // Output (mainly for debugging purposes)
  void put (std::ostream& out) const  {tok.put(out);}

private:
  Token tok;

  static const std::string startingChars;
  static const std::string middleChars;
  static const std::string endingChars;

  friend bool operator< (const WordOccurrence& left, 
			 const WordOccurrence& right);
  friend bool operator== (const WordOccurrence& left, 
			  const WordOccurrence& right);

};

inline
bool operator< (const WordOccurrence& left, const WordOccurrence& right)
{
  return left.tok < right.tok;
}

inline
bool operator== (const WordOccurrence& left, const WordOccurrence& right)
{
  return left.tok == right.tok;
}

inline
std::ostream& operator<< (std::ostream& out, const WordOccurrence& t)
{
  t.put(out);
  return out;
}


#endif
