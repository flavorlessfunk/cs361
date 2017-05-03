#include "correction.h"

using namespace std;

Correction::Correction()
  //post: getMisspelling() == WordOccurrence()
  //      && getReplacement() == ""
{}

  
Correction::Correction (const WordOccurrence& wo,
			const string& replacement)
  //post: getMisspelling() == wo
  //      && getReplacement() == replacement
  : _misspelling(wo), _replacement(replacement)
{}



// Output (mainly for debugging purposes)
void Correction::put (std::ostream& out) const
{
  out << _misspelling << "=>" << _replacement;
}



bool operator< (const Correction& left, const Correction& right)
{
  return (left.getMisspelling() < right.getMisspelling())
    || ((left.getMisspelling() == right.getMisspelling())
	&& (left.getReplacement() < right.getReplacement()));
}



bool operator== (const Correction& left, const Correction& right)
{
  return (left.getMisspelling() == right.getMisspelling())
    && (left.getReplacement() == right.getReplacement());
}




