#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

class Token 
//
// A "token" is a meaningful unit extracted from a text file.
// For example, a C++ compile would consider the keyword "class" 
// and the identifier "Token" in the line above to each be a single 
// token. In most applications, tokens can be formed from different numbers 
// of characters, usually do not  include white space (blanks, new lines,
// etc.), but the exact definition of a "token" is highly
// application-dependent.
{
public:
  typedef long unsigned Location;
  
  Token();
  //post: getLexeme()=="" && getLocation()==0

  Token (const std::string& lexeme,
	 Location location);

  // A "lexeme" is the string of characters that has been identified
  // as constituting a token.
  std::string getLexeme() const          {return _lexeme;}
  void putLexeme (const std::string& lex) {_lexeme = lex;}

  // The location indicates where in the original file the first character of
  // a token's lexeme was found.
  Location getLocation() const;
  void putLocation (const Location&);

  // Read a token from a stream. A token is recognized as a consecutive
  // string of 1 or more characters beginning with some character from
  // startingCharacters, followed by zero or more characters from
  // middleCharacters, and ending with a character from endingCharacters (which
  // may be the same character as the beginning character).
  // Returns true if a token was found. Returns false if no token could
  // be found (i.e., an input error occurred or end-of-file was reached
  // before finding an acceptable token).
  //
  // Warning: this function may read and discard an arbitrary number of extra
  // startingCharacters and middleCharacters until finding a valid token (followed
  // by a non-middleCharacter).  
  virtual bool readToken(std::istream& input,
			 const std::string& startingCharacters,
			 const std::string& middleCharacters,
			 const std::string& endingCharacters);

  // Output (mainly for debugging purposes)
  void put (std::ostream&) const;
  
private:
  std::string _lexeme;
  Location _location;
};


bool operator< (const Token& left, const Token& right);
bool operator== (const Token& left, const Token& right);

inline
std::ostream& operator<< (std::ostream& out, const Token& t)
{
  t.put(out);
  return out;
}

inline
Token::Location Token::getLocation() const
{
  return _location;
}

inline
void Token::putLocation (const Token::Location& loc)
{
  _location = loc;
}





#endif
