#ifndef EDIT1_H
#define EDIT1_H

#include <string>

bool oneEditAway (const std::string& word1,
		  const std::string& word2);

// returns true if word1 can be formed from word2 by a single character
// change, which could be any of the following:
//  - by deleting a single character (from anywhere in word1), 
//  - adding a single character (anywhere in word1), 
//  - replacing any single existing character in word1 with a different 
//     character, or
//  - by transposing (exchanging) any pair of adjacent characters in word1
#endif
