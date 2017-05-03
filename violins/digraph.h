#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <vector>

#include "edgebase.h"
#include "vertexbase.h"
#include "vertex.h"
#include "edge.h"
#include "allvertices.h"
#include "alledges.h"
#include "alloutedges.h"
#include "allinedges.h"

class DiGraph
{
public:
  DiGraph();

  Vertex addVertex();
  void removeVertex(const Vertex& v);

  virtual Edge addEdge(const Vertex& source,
		       const Vertex& dest);
  virtual void removeEdge (const Edge& e);


  unsigned int numVertices() const;
  unsigned int numEdges() const;


  unsigned indegree (Vertex) const;
  unsigned outdegree (Vertex) const;



  virtual bool isAdjacent(const Vertex& v, const Vertex& w) const;

  // Fetch an existing edge. Returns Edge() if no edge from v to w is in
  // the graph.
  Edge getEdge(const Vertex& v, const Vertex& w) const;

  void clear();

  // iterators

  AllVertices vbegin() const;
  AllVertices vend() const;

  AllEdges ebegin() const;
  AllEdges eend() const;

  AllOutgoingEdges outbegin(Vertex source) const;
  AllOutgoingEdges outend(Vertex source)   const;

  AllIncomingEdges inbegin(Vertex dest) const;
  AllIncomingEdges inend(Vertex dest)   const;


protected:

  std::vector<VertexBase> vertices;
  std::vector<EdgeBase> edges;

  unsigned numberOfVertices;
  unsigned numberOfEdges;
  
  unsigned maxVertexID;
  unsigned maxEdgeID;
  std::vector<unsigned> recycledVertexIDs;
  std::vector<unsigned> recycledEdgeIDs;
  
  
  friend class AllVertices;
  friend class AllEdges;
  friend class AllIncomingEdges;
  friend class AllOutgoingEdges;
};


//////////////////////////////////////////

inline
unsigned int DiGraph::numVertices() const
{
  return numberOfVertices;
}

inline
unsigned int DiGraph::numEdges() const
{
  return numberOfEdges;
}


#endif


