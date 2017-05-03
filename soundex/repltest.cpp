/**
   This is a simple test driver for the ReplacementChooser class.
   It simply reads a set of words from a file named on the command line, 
   inserts them all into a dictionary, creates a ReplacementChooser on 
   that dictionary, then re-reads the input file, listing each word and all
   of its potential replacements.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "replchoices.h"

using namespace std;

ReplacementChooser::Dictionaries d;

void readDictionary (string fileName)
{
  ifstream in (fileName.c_str());
  string w;
  while (in >> w)
    {
      d.add (w);
    }
  cout << "Read " << d.size() << " words" << endl;
}

void checkReplacements (string fileName)
{
  ReplacementChooser choice (d);
  ifstream in (fileName.c_str());
  string w;
  while (in >> w)
    {
      cout << w << ":" << flush;
      vector<string> replacements = choice.getPlausibleReplacements(w);
      for (int i = 0; i < replacements.size(); ++i)
	cout << " " <<  replacements[i];
      cout << endl;
    }
  cout << "***" << endl;
}



int main(int argc, char** argv)
{
  string fileName = argv[1];
  readDictionary (fileName);
  checkReplacements (fileName);
  return 0;
}