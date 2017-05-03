#include "token.h"

//
// A "token" is a meaningful unit extracted from a text file.
// For example, a C++ compile would consider the keyword "class" 
// and the identifier "Token" in the line above to each be a single 
// token. In most applications, tokens can be formed from different numbers 
// of characters, usually do not  include white space (blanks, new lines,
// etc.), but the exact definition of a "token" is highly
// application-dependent.



using namespace std;

Token::Token(): _location(0)
  //post: getLexeme()=="" && getLocation()==0
{}

    

Token::Token (const std::string& lexeme,
	      Location location)
  : _lexeme(lexeme), _location(location)
{}


  // Read a token from a stream. A token is recognized as a consecutive
  // string of 1 or more characters beginning with some character from
  // startingCharacters, followed by zero or more characters from
  // middleCharacters, and ending with a character from endingCharacters.
  // Returns true if a token was found. Returns false if no token could
  // be found (i.e., an input error occurred or end-of-file was reached
  // before finding an acceptable token).
bool Token::readToken(std::istream& input,
		      const std::string& startingCharacters,
		      const std::string& middleCharacters,
		      const std::string& endingCharacters)
{
  string lexeme;
  Location location;
  char c;
  bool done = false;

  while (!done)
    {
	  // Hunt for a starting character
      c = input.get();
	  // cerr << c << " is at " << startingCharacters.find(c) << endl;
	  while ((input) && (startingCharacters.find(c) == string::npos))
	  {
		c = input.get();
	  }
      if (!input) return false;  // Could not find starting character

	  lexeme = c;
	  location = (Location)input.tellg() - (Location)1;

	  // Now read forward until we come to something that is not a middle character
      c = input.get();
	  while ((input) && (middleCharacters.find(c) != string::npos))
	  {
		lexeme += c;
		c = input.get();
	  }

	  if ((input) && (endingCharacters.find(c) == string::npos))
	  {
		  // If the last character we read was not an endingCharacter, put
		  // it back into the input stream.
		  input.unget();
	  } else if (input) {
		  lexeme += c;
	  }

	  // Did we find an ending character anywhere in the characters we read?
	  auto endingPos = lexeme.find_last_of(endingCharacters);
	  if (endingPos == string::npos) {
		  // No: keep trying (if there's more input available)
		  done = !input;
	  }
	  else 
	  {
		  // Yes: return the lexeme we have found
		  _location = location;
		  _lexeme = lexeme.substr(0, endingPos+1);
		  return true;
	  }
  }
  return false;
}


// Output (mainly for debugging purposes)
void Token::put (std::ostream& out) const
{
  out << _lexeme << '@' << _location;
}


bool operator< (const Token& left, const Token& right)
{
  if (left.getLocation() < right.getLocation())
    return true;
  else if (left.getLocation() == right.getLocation())
    return (left.getLexeme() < right.getLexeme());
  else
    return false;
}

bool operator== (const Token& left, const Token& right)
{
  return ((left.getLocation() == right.getLocation())
	  && (left.getLexeme() == right.getLexeme()));
}


