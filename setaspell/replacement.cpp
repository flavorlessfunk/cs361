#include "replacement.h"

using namespace std;

Replacement::Replacement (const std::string& missp, const std::string& repl)
  : _misspelledWord(missp), _replacement(repl)
{}

void Replacement::put (ostream& out) const
{
  out << _misspelledWord << "=>" << _replacement;
}

bool operator== (const Replacement& left, const Replacement& right)
{
  return (left.getMisspelledWord() == right.getMisspelledWord());
}

bool operator< (const Replacement& left, const Replacement& right)
{
  return (left.getMisspelledWord() < right.getMisspelledWord());
}

