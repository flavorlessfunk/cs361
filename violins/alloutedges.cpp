#include "alloutedges.h"
#include "digraph.h"
#include <cassert>

using namespace std;

AllOutgoingEdges::AllOutgoingEdges(): graph(nullptr), pos(0) {}


AllOutgoingEdges::AllOutgoingEdges (const DiGraph* g,
				    list<unsigned>::const_iterator p)
  : graph(g), pos(p)
{
}



// Get the data element at this position
Edge AllOutgoingEdges::operator*() const
{
  return Edge(graph, *pos,
	      graph->edges[*pos].source,
	      graph->edges[*pos].dest);
}






// Move position forward 1 place
AllOutgoingEdges& AllOutgoingEdges::operator++()
{
  assert (graph != 0);
  ++pos;
  return *this;
}

AllOutgoingEdges AllOutgoingEdges::operator++(int)
{
  AllOutgoingEdges clone = *this;
  operator++();
  return clone;
}


// Move position backward 1 place
AllOutgoingEdges& AllOutgoingEdges::operator--()
{
  assert (graph != 0);
  --pos;
  return *this;
}

AllOutgoingEdges AllOutgoingEdges::operator--(int)
{
  AllOutgoingEdges clone = *this;
  operator--();
  return clone;
}


// Comparison operators
bool AllOutgoingEdges::operator== (const AllOutgoingEdges& av) const
{
  return (graph == av.graph) && (pos == av.pos);
}

bool AllOutgoingEdges::operator!= (const AllOutgoingEdges& av) const
{
  return (graph != av.graph) || (pos != av.pos);
}



