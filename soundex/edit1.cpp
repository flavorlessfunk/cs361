#include "edit1.h"

using namespace std;

bool oneEditAway (const std::string& word1,
		  const std::string& word2)
// returns true if word1 can be formed from word2 by a single character
// change, which could be any of the following:
//  - by deleting a single character (from anywhere in word1), 
//  - adding a single character (anywhere in word1), 
//  - replacing any single existing character in word1 with a different 
//     character, or
  //  - by transposing (exchanging) any pair of adjacent characters in word1
{
  // Find the first character
  // position where the two words
  // are different
  unsigned firstDifferencePos = 0;
  while ((firstDifferencePos
	  < word1.length())
	 && (firstDifferencePos
	     < word2.length())
	 && (word1[firstDifferencePos] == word2[firstDifferencePos]))
    ++firstDifferencePos;

  if ((firstDifferencePos >= word1.length())
      && (firstDifferencePos >= word2.length()))
    return false;   // words are identical


  // Tests for the 4 possible edits are all fairly simple.
  // Copy one of the words into a temporary string. Make a single
  // change (at the position where the two words differ). Check to
  // see if that change produced the second word.

  // Check: deleting from word1
  if (firstDifferencePos < word1.length())
    {
      string temp = word1;
      temp.erase(firstDifferencePos, 1);
      if (temp == word2)
	return true;
    }

  // Check: deleting from word2 (same as inserting into word1)
  if (firstDifferencePos < word2.length())
    {
      string temp = word2;
      temp.erase(firstDifferencePos, 1);
      if (temp == word1)
	return true;
    }


  // Check: replacing in word1
  if ((firstDifferencePos < word1.length())
      && (firstDifferencePos < word2.length()))
    {
      string temp = word1;
      temp[firstDifferencePos] = word2[firstDifferencePos];
      if (temp == word2)
	return true;
    }

  // Check: transposing in word1
  if (firstDifferencePos + 1 < word1.length())
    {
      string temp = word1;
      temp[firstDifferencePos] = word1[firstDifferencePos+1];
      temp[firstDifferencePos+1] = word1[firstDifferencePos];
      if (temp == word2)
	return true;
    }

  return false;
}

