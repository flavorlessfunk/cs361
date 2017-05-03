#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include <iostream>
#include <string>

class Replacement 
{
public:
  Replacement () {}
  Replacement (const std::string& missp, const std::string& repl);

  void setMisspelledWord (const std::string& mw) {_misspelledWord = mw;}
  std::string getMisspelledWord() const          {return _misspelledWord;}
  
  void setReplacement (const std::string& r)     {_replacement = r;}
  std::string getReplacement() const             {return _replacement;}
  
  void put (std::ostream&) const;
  
private:
  std::string _misspelledWord;
  std::string _replacement;
};

inline
std::ostream& operator<< (std::ostream& out, const Replacement& r)
{
  r.put (out);
  return out;
}


bool operator== (const Replacement& left, const Replacement& right);
bool operator< (const Replacement& left, const Replacement& right);



#endif
