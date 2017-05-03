#include "allinedges.h"
#include "digraph.h"
#include <cassert>

using namespace std;

AllIncomingEdges::AllIncomingEdges(): graph(nullptr), pos(0) {}


AllIncomingEdges::AllIncomingEdges (const DiGraph* g,
				    list<unsigned>::const_iterator p)
  : graph(g), pos(p)
{
}



// Get the data element at this position
Edge AllIncomingEdges::operator*() const
{
  return Edge(graph, *pos,
	      graph->edges[*pos].source,
	      graph->edges[*pos].dest);
}






// Move position forward 1 place
AllIncomingEdges& AllIncomingEdges::operator++()
{
  assert (graph != 0);
  ++pos;
  return *this;
}

AllIncomingEdges AllIncomingEdges::operator++(int)
{
  AllIncomingEdges clone = *this;
  operator++();
  return clone;
}


// Move position backward 1 place
AllIncomingEdges& AllIncomingEdges::operator--()
{
  assert (graph != 0);
  --pos;
  return *this;
}

AllIncomingEdges AllIncomingEdges::operator--(int)
{
  AllIncomingEdges clone = *this;
  operator--();
  return clone;
}


// Comparison operators
bool AllIncomingEdges::operator== (const AllIncomingEdges& av) const
{
  return (graph == av.graph) && (pos == av.pos);
}

bool AllIncomingEdges::operator!= (const AllIncomingEdges& av) const
{
  return (graph != av.graph) || (pos != av.pos);
}



