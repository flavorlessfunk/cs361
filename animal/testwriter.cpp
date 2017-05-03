#include "node.h"

#include <cassert>
#include <fstream>
#include <string>

using namespace std;


bool isomorphic (const node* a, const node* b)
{
  // Two trees are isomorphic if they have the same shape and data
  if (a == NULL)
    return (b == NULL);
  else if (b == NULL)
    return false;
  else if (a->question == b->question)
    return isomorphic(a->ifYes, b->ifYes) && isomorphic(a->ifNo, b->ifNo);
  else
    return false;
}

void myReader (istream& in, node*& root)
{
  char nodeType;
  in >> nodeType;
  char firstCharOfQuestion;
  string question;
  in >> firstCharOfQuestion; // skips over any blanks
  getline (in, question);
  question = string(1,firstCharOfQuestion) + question;
  
  node* yes = NULL;
  node* no = NULL;
  if (nodeType == 'Q')
    {
      myReader (in, yes);
      myReader (in, no);
    }
  root = new node(question, yes, no);
}




int main (int argc, char** argv)
{
  // test driver for student writers
  node* root1 = 0;
  {
    ifstream in (argv[1]);
    myReader (in,  root1);
  }

  {
    ofstream out (argv[1]);
    out << root1;
  }

  node* root2 = 0;
  {
    ifstream in (argv[1]);
    myReader (in,  root2);
  }

  if (isomorphic(root1, root2))
    cout << "OK" << endl;
  else
    cout << "Failed" << endl;

  return 0;
}