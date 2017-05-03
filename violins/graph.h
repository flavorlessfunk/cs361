#ifndef GRAPH_H
#define GRAPH_H

#include "digraph.h"

class Graph: public DiGraph
{
public:

  virtual Edge addEdge(const Vertex& source,
		       const Vertex& dest);

  virtual void removeEdge(const Edge&);

};



#endif


