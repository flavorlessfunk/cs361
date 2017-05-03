#include "wordoccurrence.h"

using namespace std;


const string WordOccurrence::endingChars
  = string("abcdefghijklmnopqrstuvwxyz")
    + "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const string WordOccurrence::startingChars
  = endingChars + "0123456789";

const string WordOccurrence::middleChars
  = startingChars + "-'";


WordOccurrence::WordOccurrence()
//post: getLexeme()=="" && getLocation()==0
{}

WordOccurrence::WordOccurrence (const std::string& lexeme,
				Location location)
  : tok(lexeme, location)
{}




// Read a word from a stream.
bool WordOccurrence::read(std::istream& input)
{
  return tok.readToken(input, startingChars, middleChars, endingChars);
}




