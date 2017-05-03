/**
 *  makemake.exe foo.cpp 
 *    Emits a make dependency rule for determining when to compile foo.cpp
 *    by analyzing and listing all .h files #included by foo.cpp (and by 
 *    other .h files #included by it, in the order they would be loaded
 *    by the compiler.
 **/

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "cs361set.h"


using namespace std;

typedef CS361Set<string> FileNameSet;
typedef queue<string> FileNameCollection;

void processSourceCodeFile (string fileName,
			    FileNameSet& alreadyProcessed,
			    FileNameCollection& stillToBeProcessed)
{
  const string INCLUDE = "#include";
  const string PATHSEP = "/";  // "\\" for Windows compilers
  //
  // Most of this function is involved with scanning a file of C++
  // source code, looking for lines containing #include directives.
  //

  string pathToThisFile = (fileName.find(PATHSEP) != string::npos) ?
    fileName.substr(0, fileName.rfind(PATHSEP)+1) : string();

  ifstream sourceIn (fileName.c_str());
  while (sourceIn) {
    // Read line of source code
    string line;
    getline (sourceIn, line);
    // Does it begin with #include?
    string::size_type includeStart = line.find_first_not_of(" \t");
    if (includeStart != string::npos &&
	line.substr(includeStart,INCLUDE.length()) == INCLUDE) {
      // Isthefilename inside < > or " " ?
      string::size_type filenameStart =
	line.find_first_of("<\"",
			   includeStart+INCLUDE.length());
      if (filenameStart != string::npos && line[filenameStart] == '"') {
	// We have located a file name inside a #include "..."
	// Extract the filename.
	++filenameStart;
	string::size_type filenameEnd = line.find(string(1,'"'), filenameStart);
	if (filenameEnd != string::npos) {
	  string includedFileName =
	    pathToThisFile +
	    line.substr(filenameStart, filenameEnd-filenameStart);

	  // We have located a file name inside a #include "..."
	  if (!alreadyProcessed.contains(includedFileName)) {
	    alreadyProcessed.add(includedFileName);
	    stillToBeProcessed.push (includedFileName);
	  }
	}
      }
    }
  }
}


int main(int argc, char** argv)
{
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " cppFileName" << endl;
    return -1;
  }

  string cppFileName (argv[1]);

  cout << cppFileName << ": " << flush;

  FileNameSet alreadyProcessed;
  FileNameCollection stillToBeProcessed;

  processSourceCodeFile (cppFileName, alreadyProcessed, stillToBeProcessed);

  while (!stillToBeProcessed.empty()) {
    string headerFileName = stillToBeProcessed.front();

    cout << "\\\n    " << headerFileName << flush;
    processSourceCodeFile (headerFileName,
			   alreadyProcessed,
			   stillToBeProcessed);

    stillToBeProcessed.pop();
  }
  cout << endl;
  return 0;
}