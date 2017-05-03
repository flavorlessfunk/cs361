#ifndef CS361SET_H
#define CS361SET_H

#include <string>
#include <iostream>
#include <cassert>

#include "arrayops.h"



template <class Element>
class CS361Set
{
public:
  typedef const Element* const_iterator;
  typedef const Element* iterator;


  CS361Set ();
  CS361Set (unsigned int maxSizeDesired);
  CS361Set (const CS361Set<Element>&);
  
  ~CS361Set();
  
  CS361Set<Element>& operator= (const CS361Set<Element>& ws);
  //pre: maxSize() <= ws.size()
  
  unsigned int size() const;
  // How many words in the set?

  unsigned int maxSize() const;
  // How many words could be put into a set?
  
  void add (const Element& word);
  //pre: contains(word) || size() < maxSize()
  
  bool contains (const Element& word) const;

  const_iterator find (const Element& key) const;
  
  const_iterator begin() const;
  const_iterator end() const;
  

  void print(std::ostream& out) const;

  bool operator== (const CS361Set<Element>&) const;
  bool operator< (const CS361Set<Element>&) const;

private:
  const unsigned int maxNumberOfElements;
  unsigned int numberOfElements;
  Element *elements;
};

template <class Element>
inline
std::ostream& operator<< (std::ostream& out, const CS361Set<Element>& set)
{
  set.print (out);
  return out;
}

template <class Element>
inline
unsigned int CS361Set<Element>::size() const
{
  return numberOfElements;
}

template <class Element>
inline
unsigned int CS361Set<Element>::maxSize() const
{
  return maxNumberOfElements;
}



template <class Element>
CS361Set<Element>::CS361Set ()
  : maxNumberOfElements(500)
{
  numberOfElements = 0;
  elements = new Element [maxNumberOfElements];
}


template <class Element>
CS361Set<Element>::CS361Set (unsigned int maxSizeDesired)
  : maxNumberOfElements(maxSizeDesired)
{
  numberOfElements = 0;
  elements = new Element [maxSizeDesired];
}


template <class Element>
CS361Set<Element>::~CS361Set()
{
  delete [] elements;
}

template <class Element>
CS361Set<Element>::CS361Set (const CS361Set<Element>& oldSet)
  : maxNumberOfElements(oldSet.maxNumberOfElements),
    numberOfElements(oldSet.numberOfElements)
{
  elements = new Element[maxNumberOfElements];
  for (int i = 0; i < numberOfElements; ++i)
    elements[i] = oldSet.elements[i];
}


template <class Element>
CS361Set<Element>& CS361Set<Element>::operator= (const CS361Set<Element>& oldSet)
{
  if (this != &oldSet)
  {
    assert (maxNumberOfElements >= oldSet.numberOfElements);
    numberOfElements = oldSet.numberOfElements;
    
    for (int i = 0; i < numberOfElements; ++i)
    elements[i] = oldSet.elements[i];
  }
  return *this;
}


template <class Element>
void CS361Set<Element>::add (const Element& word)
{
  if (((size() > 0) && (elements[size()-1] < word))
      ||  (!contains(word)))
    {
      assert (size() < maxSize());
      sequentialInsert (elements, numberOfElements, word);
    }
}

template <class Element>
bool CS361Set<Element>::contains (const Element& word) const
{
  if (numberOfElements > 0)
    {
      int pos = binarySearch (elements, numberOfElements, word);
      return ((pos >= 0) && (elements[pos] == word));
    }
  else
    return false;
}


template <class Element>
typename CS361Set<Element>::const_iterator
  CS361Set<Element>::find (const Element& key) const
{
  if (numberOfElements > 0)
    {
      int pos = binarySearch (elements, numberOfElements, key);
      if ((pos >= 0) && (elements[pos] == key))
	{
	  return elements+pos;
	}
      else
	return end();
    }
  else
    return end();
}



template <class Element>
inline
typename CS361Set<Element>::const_iterator
  CS361Set<Element>::begin () const
{
  return elements;
}


template <class Element>
inline
typename CS361Set<Element>::const_iterator
  CS361Set<Element>::end () const
{
  return elements + numberOfElements;
}






template <class Element>
void CS361Set<Element>::print(std::ostream& out) const
{
  using namespace std;

  string separator = "";
  out << "{";
  for (int i = 0; i < numberOfElements; ++i)
    {
      out << separator << elements[i];
      separator = ", ";
    }
  out << "}";
}


template <class Element>
bool CS361Set<Element>::operator== (const CS361Set<Element>& ws) const
{
  if (numberOfElements == ws.numberOfElements)
    {	
     for (int i = 0; i < numberOfElements; ++i)
       {
         if (!(elements[i] == ws.elements[i]))
           return false;
       }
     return true;
    }
  else
    return false;
}


template <class Element>
bool CS361Set<Element>::operator< (const CS361Set<Element>& ws) const
{
  if (numberOfElements == ws.numberOfElements)
    {	
     for (int i = 0; i < numberOfElements; ++i)
       {
         if (elements[i] != ws.elements[i])
           return elements[i] < ws.elements[i];
       }
     return false;
    }
  else
    return numberOfElements < ws.numberOfElements;
}

#endif
