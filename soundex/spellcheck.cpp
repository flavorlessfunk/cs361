// Spellcheck program

#include <fstream>
#include "wordoccurrence.h"
#include "correction.h"
#include "replacement.h"
#include "cs361set.h"
#include <vector>
#include "vectorUtils.h"

#include "replchoices.h"



typedef CS361Set<std::string> WordSet;
typedef CS361Set<Replacement> ReplacementSet;
typedef std::vector<WordOccurrence> WordOccurrenceOrderedSequence;
typedef std::vector<Correction> CorrectionOrderedSequence;





std::string promptForAction (const WordOccurrence& misspelled);


std::string get_replacement_spelling(const std::string& word,
				     const WordSet& dictionary,
				     const ReplacementChooser& chooser);


std::string getSaveFileName();





using namespace std;

#ifdef GRADING
string saveFileName;
#endif


void readDictionary (const string& dictionaryFileName,
		     WordSet& dictionary);


void collectMisspelledWords (const string& targetFileName,
			     const WordSet& dictionary, 
			     WordOccurrenceOrderedSequence& misspellings);

void promptUserForCorrections
  (const string& targetFileName,
   const WordSet& dictionary, 
   const WordOccurrenceOrderedSequence& misspellings,
   const ReplacementChooser& chooser,
   CorrectionOrderedSequence& corrections);


void produceCorrectedDocument(const string& targetFileName,
			      /*const*/CorrectionOrderedSequence& corrections,
			      const string& correctedFileName);





int main (int argc, char** argv)
{
#ifndef GRADING
  if (argc != 3) {
    cerr << "Usage: " << argv[0]
	 << " dictionaryFileName documentFileName"
	 << endl;
    return 1;
  }
#else
  if (argc != 4) {
    cerr << "Usage: " << argv[0]
	 << " dictionaryFileName documentFileName saveFileName"
	 << endl;
    return 1;
  }
  saveFileName = argv[3];
#endif

  string dictionaryFileName = argv[1];
  string targetFileName = argv[2];

  
  
  // main spellcheck routine
  WordSet dictionary;
  readDictionary (dictionaryFileName, dictionary);

  ReplacementChooser replacementChooser(dictionary);

  WordOccurrenceOrderedSequence misspellings;
  collectMisspelledWords (targetFileName, dictionary, misspellings);


  CorrectionOrderedSequence corrections;
  promptUserForCorrections(targetFileName, dictionary,
			   misspellings, replacementChooser,
			   corrections);

#ifndef GRADING
  if (!corrections.empty())
#endif
    {
      string correctedFileName = getSaveFileName();
      if (correctedFileName[0] != ' ')
	produceCorrectedDocument(targetFileName, corrections,
				 correctedFileName);
    }

  return 0;
}



void readDictionary (const string& dictionaryFileName,
		     WordSet& dictionary)
{
  ifstream dictin (dictionaryFileName.c_str());
  string word;
  while (dictin >> word)
    {
      dictionary.add (word);
    }
}





void collectMisspelledWords (const string& targetFileName,
			     const WordSet& dictionary, 
			     WordOccurrenceOrderedSequence& misspellings)
{
  ifstream targetFile (targetFileName.c_str());
  cout << "Checking " << targetFileName << endl;
  
  WordOccurrence w;
  while (w.read(targetFile))
    {
     if (!dictionary.contains(w.getLexeme()))
       {
	 addInOrder (misspellings, w);
     }
  }
  cout << misspellings.size() << " possible misspellings found." << endl;
}



void display_in_context (const WordOccurrence& occur, istream& inFile)
{
  static const WordOccurrence::Location ContextSize = 20;

   WordOccurrence::Location start = (occur.getLocation() >= ContextSize) ?
    occur.getLocation() - ContextSize : (WordOccurrence::Location)0;
  WordOccurrence::Location stop = occur.getLocation() + ContextSize
    + (WordOccurrence::Location)occur.getLexeme().length();


  string beforeMisspelling;
  string afterMisspelling;
  inFile.seekg(start);
  for (; start < occur.getLocation(); start+=1)
    beforeMisspelling += (char)inFile.get();

  start = occur.getLocation() + (WordOccurrence::Location)occur.getLexeme().length();
  inFile.seekg(start);
  for (; start < stop; start+=1)
    afterMisspelling += (char)inFile.get();
  
  // If there is a line break (\c or \n) more than 2 chars from
  // this misspelling, terminate the context there.

  auto loc = beforeMisspelling.substr(0, beforeMisspelling.length()-2)
    .find_last_of("\r\n");
  if (loc != string::npos) {
    beforeMisspelling = beforeMisspelling.substr(loc+1);
  }
  loc = afterMisspelling.find_first_of("\r\n", 2);
  if (loc != string::npos) {
    afterMisspelling = afterMisspelling.substr(0, loc-1);
  }

  cout << beforeMisspelling << "\n   "
       << occur.getLexeme() << "\n"
       << afterMisspelling << endl;
}






void promptUserForCorrections
  (const string& targetFileName,
   const WordSet& dictionary, 
   const WordOccurrenceOrderedSequence& misspellings,
   const ReplacementChooser& chooser,
   CorrectionOrderedSequence& corrections)
{
  // assume misspellings are in order of occurrence within the
  // target file (if not, sort them)
  ifstream targetFile (targetFileName.c_str());

  WordSet globalIgnoredSet;
  ReplacementSet globalReplacementSet;
  
  for (WordOccurrenceOrderedSequence::const_iterator m =  misspellings.begin();
       m != misspellings.end(); ++m)
    {
      WordOccurrence misspelling = *m;
      string mword = misspelling.getLexeme();
      //WordOccurrence::Location mloc = misspelling.getLocation();
      
      if (!globalIgnoredSet.contains(mword))
	{
	  Replacement grepl;
	  ReplacementSet::iterator repl =
	    globalReplacementSet.find(Replacement(mword,""));
	  if (repl != globalReplacementSet.end())
	    {
	      addInOrder(corrections,Correction(misspelling,
						(*repl).getReplacement()));
	    }
	  else
	    {
	      display_in_context(misspelling, targetFile);
	      string response = promptForAction(misspelling);
	      if (response == "ignore")
		{
		  // do nothing
		}
	      else if (response == "ignore every time")
		{
		  globalIgnoredSet.add(mword);
		}
	      else if (response == "replace")
		{
		  string r = get_replacement_spelling(mword, dictionary,
						      chooser);
		  addInOrder (corrections, Correction(misspelling, r));
		}
	      else if (response == "replace every time")
		{
		  string r = get_replacement_spelling(mword, dictionary,
						      chooser);
		  addInOrder (corrections, Correction(misspelling, r));
		  globalReplacementSet.add (Replacement(mword, r));
		}
	      else if (response == "quit")
		{
		  break;
		}
	    }
	}
    }
}





void produceCorrectedDocument(const string& targetFileName,
			      /*const*/CorrectionOrderedSequence& corrections,
			      const string& correctedFileName)
{
  cout << "Corrected document saving to " << correctedFileName << endl;

  // assume corrections are in order of occurrence within the
  // target file (if not, sort them)
  ifstream targetFile (targetFileName.c_str());
  ofstream correctedFile (correctedFileName.c_str());

  for (CorrectionOrderedSequence::iterator c = corrections.begin();
       c != corrections.end(); ++c)
    {
      // copy into the correctedFile all characters from 
      //   current location of the targetFile up to 
      //   the location of c;
      for (long offset = (*c).getMisspelling().getLocation()
	                 - targetFile.tellg();
	   offset > 0; --offset) {
	correctedFile.put ((char)targetFile.get());
      }

      // read and discard the misspelled word from the targetFile;
      WordOccurrence misspelled;
      misspelled.read(targetFile);

      // write the corrected spelling from c into the correctedFile;
      correctedFile << (*c).getReplacement();
    }
  
  // copy any remaining characters from the targetFile into the
  //   correctedFile;
  char ch = targetFile.get();
  while ((targetFile) && (ch >= 0))
    {
      correctedFile.put(ch);
      ch = targetFile.get();
    }
  cout << "Corrected document saved in " << correctedFileName << endl;
}



/***************************
     Interactive routines for the spellcheck program

  When compiled with GRADING flag set, these are replaced by 
  noninteractive code for auto-testing purposes.
****************************/

string promptForAction (const WordOccurrence& misspelled)
{
#ifndef GRADING
  cout << "\n" << misspelled.getLexeme() << ":\n"
       << " (r)eplace this word, just this once\n"
       << " (R)eplace this word every time\n"
       << " (i)gnore this word, just this once\n"
       << " (I)gnore this word every time\n"
       << " (Q)uit\n"
       << ">" << flush;
  
  char response;

  while (1)
    {
      cin >> response;
      switch (response) {
	case 'r': return "replace";
	case 'R': return "replace every time";
	case 'i': return "ignore";
	case 'I': return "ignore every time";
	case 'Q': return "quit";
      }
      if (response > ' ')
	cout << "Please respond with one of: rRiIQ\n>" << flush;
    }
#else
  return "replace every time";
#endif
}


string get_replacement_spelling(const string& word,
				const WordSet& dictionary,
				const ReplacementChooser& chooser)
{
  cout << "\n" << word << ":" << endl;
  
  // Get a list of potential replacement strings
  // (not yet implemented)
  vector<string> replacements = chooser.getPlausibleReplacements(word);
  int nReplacements = replacements.size();
  int replacementChoice = -1;
  
  if (nReplacements > 0)
    {
      cout << "Choose a corrected spelling:\n";
      for (int i = 0; i < nReplacements; ++i)
	cout << i+1 << ' ' << replacements[i] << "\n";
      cout << "0 None of the above";

#ifndef GRADING
      while (replacementChoice < 0 || replacementChoice > nReplacements)
	{
	  cout << "\n Enter your choice: " << flush;
	  cin >> replacementChoice;
	}
#endif
    }
  
#ifndef GRADING
  if (replacementChoice > 0)
    return replacements[replacementChoice-1];
  else
    {
      // Prompt user directly for corrected spelling
      string corrected;
      getline(cin, corrected);
      while (corrected == "")
	{
	  cout << "\nEnter correct spelling: " << flush;
	  getline(cin, corrected);
	}
      return corrected;
    }
#else
  string repl = "[" + word + "=>";
  for (int k = 0; k < nReplacements; ++k)
    {
      repl += replacements[k];
      repl += '|';
    }
  repl += ']';
  return repl;
#endif
}







string getSaveFileName()
{
#ifndef GRADING
  string fileName;
  cout << "Enter name of file to contain the corrected document, or blank\n"
       << "to discard all corrections:\n"
       << "> " << flush;
  while (fileName == "")
    {
      getline(cin, fileName);
    }
  return fileName;
#else
  return saveFileName;
#endif
}
