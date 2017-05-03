#include "node.h"
#include <cassert>

using namespace std;

// write the tree whose root is given.
// Note: the form written out by this function should be something
//   that read(...) will accept, recreating the original tree.
void node::write (std::ostream& out, const node* root)
{
  if (root != NULL)
    {
      char nodeType =  (root->ifYes != 0) ? 'Q' : 'A';
      out << nodeType << " " << root->question << endl;
      if (root->ifYes != NULL)
	{
	  write (out, root->ifYes);
	  write (out, root->ifNo);
	}
    }
}


// read a tree from in storing the tree root in t
void node::read (istream& in, node*& root)
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
      read (in, yes);
      read (in, no);
    }
  root = new node(question, yes, no);
}