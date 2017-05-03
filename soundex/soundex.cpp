#include "soundex.h"
#include <algorithm>

// 
// The Soundex code is a rather primitive way of encoding the way words
// (especially names) sound so that variant spellings of the same word may
// be identified by the same code.
//
// Traditional Soundex codes have 4 alphanumeric characters
//   1 Letter and 3 Digits 
//  - The Letter of the word is the first character of the Soundex code. 
//  - The 3 digits are defined sequentially from the word using the 
//    Soundex Key below. 
//  - Adjacent letters in the word which belong to the same Soundex Key
//    code number are assigned a single digit.
//  - If the end of the word is reached prior to filling 3 digits, 
//    use zeroes to complete the code. All codes have only 4 characters, 
//    even if the word is long enough to yield more. 
//
//    The Soundex Key:
//     1: b p f v 
//     2: c s k g j q x z 
//     3: d t 
//     4: l 
//     5: m n 
//     6: r 
//     no code: a e h i o u y w 


// This function computes an "extended" Soundex code of k code characters
// If k<0, the code returned contains as many characters as can be obtained
// from the word by the above rules without adding zeroes at the end.


using namespace std;

string extendedSoundex (const string& word, int k)
{
  //                   "abcdefghijklmnopqrstuvwxyz";
  static const char* keys  = " 123 12  22455 12623 1 2 2";

  string soundexCode;

  char lastCode = ' ';
  for (unsigned i = 0; i < word.size(); ++i)
    {
      char c = word[i];
      //convert to lowercase, if necessary
      if (c >= 'A' && c <= 'Z')
	c += 'a' - 'A';

      if (i == 0)
	// First char of soundex code is the unencoded character
	soundexCode += c;
      else if (c >= 'a' && c <= 'z')
	{
	  // append the soundex character code
	  char soundexChar = keys[c - 'a'];
	  if (soundexChar != lastCode && soundexChar != ' ')
	    soundexCode += soundexChar;
	  lastCode = soundexChar;
	}
    }

  if (k >= 0)
    {
      if (soundexCode.size() > (unsigned)k)
	// truncate code to k characters
	soundexCode = soundexCode.substr(0, k);
      else
	// pad code with zeros
	soundexCode += string(k-soundexCode.size(), '0');
    }

  return soundexCode;
}


