#ifndef ALLEDGES_H
#define ALLEDGES_H

#include "edge.h"
#include <cstddef>
#include <iterator>
#include <vector>

class DiGraph;

// AllEdges is an iterator for DiGraphs allowing one to visit
// every edge in a graph.  It is, effectively, a const iterator because
// edges are immutable (they have no properties that can be changed once
// initialized).
//
// AllEdges iterators retain their value even as edges are added or removed
// from the graph with the following exceptions:
//   1) If pos is an AllEdges iterator pointing to an edge that is removed,
//      then *pos is undefined.
//   2) If pos is an AllEdges iterator pointing to an edge and another edge
//      is added, that new edge will be reachable from pos by some sequence of
//      ++ or -- operations, but it is undefined whether that sequence will
//      employ ++ only or -- only.
//
class AllEdges
{
public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef Edge                       value_type;
  typedef ptrdiff_t                  difference_type;
  typedef const Edge*                pointer;
  typedef const Edge&                reference;

  AllEdges();

  // Get the data element at this position
  Edge operator*() const;

  // Move position forward 1 place
  AllEdges& operator++();
  AllEdges operator++(int);

  // Move position backward 1 place
  AllEdges& operator--();
  AllEdges operator--(int);

  // Comparison operators
  bool operator== (const AllEdges&) const;
  bool operator!= (const AllEdges&) const;
private:
  friend class DiGraph;
  const DiGraph* graph;
  unsigned pos;

  AllEdges (const DiGraph* g, unsigned p);

};


#endif

