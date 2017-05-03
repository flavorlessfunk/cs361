#include "graph.h"
#include <algorithm>


Edge Graph::addEdge(const Vertex& source,
		    const Vertex& dest)
{
  if (source.id() != dest.id())
    DiGraph::addEdge(dest, source);
  return DiGraph::addEdge(source, dest);
}


void Graph::removeEdge(const Edge& e)
{
    DiGraph::removeEdge(e);
    EdgeBase mirror;
    mirror.source = e.dest().id();
    mirror.dest = e.source().id();
    if (mirror.source !=  mirror.dest)
	{
	  unsigned mirrorImagePos = find(edges.begin(), edges.end(), mirror)
	      - edges.begin();
	  if (mirrorImagePos < edges.size())
	      {
		  Edge e2 (this, mirrorImagePos, mirror.source, mirror.dest);
		  DiGraph::removeEdge(e2);
	      }
	}
}





