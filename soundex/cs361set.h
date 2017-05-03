#ifndef CS361SET_H
#define CS361SET_H

#include <string>
#include <iostream>
#include <cassert>
#include <list>


template <class Element>
class CS361Set
{
public:
  typedef typename std::list<Element>::const_iterator const_iterator;
  typedef typename std::list<Element>::const_iterator iterator;


  CS361Set ();

  unsigned int size() const;
  // How many words in the set?

  void add (const Element& word);
  //pre: contains(word) || size() < maxSize()
  
  bool contains (const Element& word) const;
  // Is word in this set?

  const_iterator find (const Element& key) const;
  // Find the location of key in the set
  
  const_iterator begin() const;
  // Returns the position of the first element in the set

  const_iterator end() const;
  // Returns the position just _after_ the last element in the set

  // You can loop through all elements of the set like this:
  //  for (typename CS361Set<T>::const_iterator p = mySet.begin();
  //          p != mySet.end(); ++p)
  //    {
  //     T data = *p;
  //     doSomethingTo(data);
  //    }
  // The elements of the set will be visited in sorted order.


  void print(std::ostream& out) const;

  bool operator== (const CS361Set<Element>&) const;
  // Compare two sets to see if they contain the same elements


  bool operator< (const CS361Set<Element>&) const;
  // Compare two sets to see if one comes before the other

private:
  unsigned int numberOfElements;
  std::list<Element> elements;
};


template <class Element>
inline
std::ostream& operator<< (std::ostream& out, const CS361Set<Element>& set)
{
  set.print (out);
  return out;
}


//===================================



template <class Element>
inline
unsigned int CS361Set<Element>::size() const
{
  return numberOfElements;
}



template <class Element>
CS361Set<Element>::CS361Set ()
{
  numberOfElements = 0;
}





template <class Element>
void CS361Set<Element>::add (const Element& word)
{
  if (numberOfElements > 0)
    {
      typename std::list<Element>::iterator pos = elements.begin();
      while (pos != elements.end() && *pos < word)
	++pos;
      if (pos == elements.end() || !(*pos == word))
	{
	  elements.insert (pos, word);
	  ++numberOfElements;
	}
    }
  else
    {
      elements.push_back (word);
      numberOfElements = 1;
    }
}

template <class Element>
bool CS361Set<Element>::contains (const Element& word) const
{
  return find(word) != elements.end();
}


template <class Element>
typename CS361Set<Element>::const_iterator
  CS361Set<Element>::find (const Element& key) const
{
  if (numberOfElements > 0)
    {
      typename std::list<Element>::const_iterator pos = elements.begin();
      while (pos != elements.end() && *pos < key)
	++pos;
      if (pos != elements.end() && *pos == key)
	return pos;
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
  return elements.begin();
}


template <class Element>
inline
typename CS361Set<Element>::const_iterator
  CS361Set<Element>::end () const
{
  return elements.end();
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
  typename std::list<Element>::const_iterator i = elements.begin();
  typename std::list<Element>::const_iterator j = ws.elements.begin();
  while (i != elements.end() && j != ws.elements.end())
    {
      if (!(*i == *j))
	return false;
      ++i;
      ++j;
    }
  if (i == elements.end() && j == ws.elements.end())
    return true;
  else
    return false;
}


template <class Element>
bool CS361Set<Element>::operator< (const CS361Set<Element>& ws) const
{
  typename std::list<Element>::const_iterator i = elements.begin();
  typename std::list<Element>::const_iterator j = ws.elements.begin();
  while (i != elements.end() && j != ws.elements.end())
    {
      if (!(*i == *j))
	return (*i < *j);
      ++i;
      ++j;
    }
  if (i == elements.end() && j == ws.elements.end())
    return false;
  else if (i == elements.end())
    return true;
  else
    return false;
}

#endif
