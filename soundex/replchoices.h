#ifndef REPLCHOICES_H
#define REPLCHOICES_H

// Spellcheck program: choosing replacements for misspelled words

#include "cs361set.h"
#include <string>
#include <vector>


// This class implements a policy for choosing "plausible"
// replacements for a misspelled word. Many such policies are possible.
// For example, we might choose words from the system dictionary that
// "look like" the misspelled word, or words from the system dictionary that
// "sound like" the misspelled word, or some combination of these.
//



struct ReplacementChooserData;


class ReplacementChooser 
{
public:
  typedef CS361Set<std::string> Dictionaries;

  // Plan for replacements to be suggested from the
  // given dictionary.
  ReplacementChooser(const Dictionaries& dictionary);
  ~ReplacementChooser();
  

  // Choose some number of "plausible" replacements for the given word,
  // returning them in the order we want them listed to the user.
  std::vector<std::string> getPlausibleReplacements(const std::string& word)
    const;
  
private:
  ReplacementChooserData* d;
  // This is an ilustration of a common programming idiom in C++. Normally,
  // the implementing data structure for an ADT is visible in the private
  // portion of a class's .h file. Thus if the ADT designer wants to later
  // change the data structure, he/she must edit the .h file as well as the
  // .cpp file.  We can, at a slight cost, however, hide the data structure
  // from the .h file by placing the implementing data structure inside
  // another class/struct, and simply having a pointer to that class/struct
  // in the ADT. 


  // Don't allow copying and assignment of this ADT
  ReplacementChooser(const ReplacementChooser&) {}
  void operator= (const ReplacementChooser&) {}
  
};


#endif
