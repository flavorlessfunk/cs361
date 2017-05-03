#include "replchoices.h"
#include "soundex.h"

#include <algorithm>
#include <map>

using namespace std;

// This class implements a policy for choosing "plausible"
// replacements for a misspelled word. Many such policies are possible.
// For example, we might choose words from the system dictionary that
// "look like" the misspelled word, or words from the system dictionary that
// "sound like" the misspelled word, or some combination of these.
//



struct ReplacementChooserData
{
  typedef multimap<string, string> SoundexMap;
  SoundexMap soundexMap;
};



ReplacementChooser::ReplacementChooser(const Dictionaries& dictionary)
{
  d = new ReplacementChooserData;
  for (Dictionaries::const_iterator i = dictionary.begin();
       i != dictionary.end(); ++i)
    {
      string word = *i;
      string soundex = extendedSoundex(word, -1);
      d->soundexMap.insert
	(ReplacementChooserData::SoundexMap::value_type(soundex,word));
    }
}

ReplacementChooser::~ReplacementChooser()
{
  delete d;
}

  

// Choose some number of "plausible" replacements for the given word,
// returning them in the order we want them listed to the user.
vector<string> ReplacementChooser::getPlausibleReplacements
  (const string& word) const
{
  vector<string> replacements;
  string soundex = extendedSoundex(word, -1);

  // Copy all words with the same soundex code into a vector
  pair<ReplacementChooserData::SoundexMap::iterator,
    ReplacementChooserData::SoundexMap::iterator> srange
    = d->soundexMap.equal_range(soundex);
  
  for (ReplacementChooserData::SoundexMap::iterator p
	 = srange.first;  p != srange.second; ++p)
	replacements.push_back ((*p).second);

  sort (replacements.begin(), replacements.end());
  
  // If more than 10 words were found, truncate
  if (replacements.size() > 10)
    replacements.erase(replacements.begin()+10, replacements.end());

  return replacements;
}