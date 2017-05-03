#include "alledges.h"
#include "digraph.h"
#include <cassert>


AllEdges::AllEdges(): graph(nullptr), pos(0) {}


AllEdges::AllEdges (const DiGraph* g, unsigned p)
  : graph(g), pos(p)
{
  while ((pos < graph->numEdges()) && !graph->edges[pos].occupied)
  {
    ++pos;
  } 
}



// Get the data element at this position
Edge AllEdges::operator*() const
{
  return Edge(graph, pos, graph->edges[pos].source, graph->edges[pos].dest);
}






// Move position forward 1 place
AllEdges& AllEdges::operator++()
{
  assert ((graph != 0) && (pos < graph->edges.size()));
  do
    {
      ++pos;
    } while ((pos < graph->numEdges()) && !graph->edges[pos].occupied);
  return *this;
}

AllEdges AllEdges::operator++(int)
{
  AllEdges clone = *this;
  operator++();
  return clone;
}


// Move position backward 1 place
AllEdges& AllEdges::operator--()
{
  assert ((graph != 0) && (pos > 0));
  do
    {
      --pos;
    } while ((pos > 0) && !graph->edges[pos].occupied);
  return *this;
}

AllEdges AllEdges::operator--(int)
{
  AllEdges clone = *this;
  operator--();
  return clone;
}


// Comparison operators
bool AllEdges::operator== (const AllEdges& av) const
{
  return (graph == av.graph) && (pos == av.pos);
}

bool AllEdges::operator!= (const AllEdges& av) const
{
  return (graph != av.graph) || (pos != av.pos);
}



