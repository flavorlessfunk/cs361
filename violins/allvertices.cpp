#include "allvertices.h"
#include "digraph.h"
#include <cassert>


AllVertices::AllVertices(): graph(nullptr), pos(0) {}


AllVertices::AllVertices (const DiGraph* g, unsigned p)
  : graph(g), pos(p)
{
  while ((pos < graph->numVertices()) && !graph->vertices[pos].occupied)
  {
    ++pos;
  } 
}



// Get the data element at this position
Vertex AllVertices::operator*() const
{
  return Vertex(graph, pos);
}







// Move position forward 1 place
AllVertices& AllVertices::operator++()
{
  assert ((graph != 0) && (pos < graph->vertices.size()));
  do
    {
      ++pos;
    } while ((pos < graph->numVertices()) && !graph->vertices[pos].occupied);
  return *this;
}

AllVertices AllVertices::operator++(int)
{
  AllVertices clone = *this;
  operator++();
  return clone;
}


// Move position backward 1 place
AllVertices& AllVertices::operator--()
{
  assert ((graph != 0) && (pos > 0));
  do
    {
      --pos;
    } while ((pos > 0) && !graph->vertices[pos].occupied);
  return *this;
}

AllVertices AllVertices::operator--(int)
{
  AllVertices clone = *this;
  operator--();
  return clone;
}


// Comparison operators
bool AllVertices::operator== (const AllVertices& av) const
{
  return (graph == av.graph) && (pos == av.pos);
}

bool AllVertices::operator!= (const AllVertices& av) const
{
  return (graph != av.graph) || (pos != av.pos);
}



