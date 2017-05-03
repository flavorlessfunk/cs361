#ifndef ALLINEDGES_H
#define ALLINEDGES_H

#include "edge.h"
#include <cstddef>
#include <iterator>
#include <list>

class DiGraph;

// AllIncomingEdges is an iterator for DiGraphs allowing one to visit
// every edge with a given node as its destination.  It is, effectively, 
// a const iterator because edges are immutable (they have no properties 
// that can be changed once initialized).
//
// AllIncomingEdges iterators retain their value even as edges are added 
// or removed from the graph with the following exceptions:
//   1) If pos is an AllIncomingEdges iterator pointing to an edge that 
//      is removed, then all functions on pos are undefined.
//   2) If pos is an AllIncomingEdges iterator pointing to an edge and
//      another edge is added with the same destination, that new edge 
//      will be reachable from pos by some sequence of
//      ++ or -- operations, but it is undefined whether that sequence will
//      employ ++ only or -- only.
//
class AllIncomingEdges
{
public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef Edge                       value_type;
  typedef ptrdiff_t                  difference_type;
  typedef const Edge*                pointer;
  typedef const Edge&                reference;

  AllIncomingEdges();

  // Get the data element at this position
  Edge operator*() const;

  // Move position forward 1 place
  AllIncomingEdges& operator++();
  AllIncomingEdges operator++(int);

  // Move position backward 1 place
  AllIncomingEdges& operator--();
  AllIncomingEdges operator--(int);

  // Comparison operators
  bool operator== (const AllIncomingEdges&) const;
  bool operator!= (const AllIncomingEdges&) const;
private:
  friend class DiGraph;
  const DiGraph* graph;
  std::list<unsigned>::const_iterator pos;


  AllIncomingEdges(const DiGraph*, std::list<unsigned>::const_iterator);
};


#endif

