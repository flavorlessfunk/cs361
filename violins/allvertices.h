#ifndef ALLVERTICES_H
#define ALLVERTICES_H

#include "vertex.h"
#include <cstddef>
#include <iterator>
#include <vector>

class DiGraph;

// AllVertices is an iterator for DiGraphs allowing one to visit
// every vertex in a graph.  It is, effectively, a const iterator because
// vertices are immutable (they have no properties that can be changed once
// initialized).
//
// AllVertices iterators retain their value even as vertices are added or
// removed from the graph with the following exceptions:
//   1) If pos is an AllVertices iterator pointing to an vertex that is 
//      removed, then *pos is undefined.
//   2) If pos is an AllVertices iterator pointing to an vertex and another 
//      vertex is added, that new vertex will be reachable from pos by some 
//      sequence of ++ or -- operations, but it is undefined whether that
//       sequence will employ ++ only or -- only.
//
class AllVertices
{
public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef Vertex                     value_type;
  typedef ptrdiff_t                  difference_type;
  typedef const Vertex*              pointer;
  typedef const Vertex&              reference;

  AllVertices();

  // Get the data element at this position
  Vertex operator*() const;

  // Move position forward 1 place
  AllVertices& operator++();
  AllVertices operator++(int);

  // Move position backward 1 place
  AllVertices& operator--();
  AllVertices operator--(int);

  // Comparison operators
  bool operator== (const AllVertices&) const;
  bool operator!= (const AllVertices&) const;
private:
  friend class DiGraph;
  const DiGraph* graph;
  unsigned pos;

  AllVertices (const DiGraph* g, unsigned p);
};


#endif

