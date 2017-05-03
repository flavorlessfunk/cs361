#include <cassert>
#include "digraph.h"


using namespace std;


DiGraph::DiGraph()
  : numberOfVertices(0), numberOfEdges(0),
    maxVertexID(0), maxEdgeID(0)
{
}


Vertex DiGraph::addVertex()
{
  unsigned newID;
  if (recycledVertexIDs.empty())
    {
      newID = maxVertexID + 1;
      ++maxVertexID;
      while (vertices.size() <= maxVertexID)
	vertices.push_back(VertexBase());
    }
  else
    {
      newID = recycledVertexIDs.back();
      recycledVertexIDs.pop_back();
    }
  ++numberOfVertices;
  vertices[newID].occupied = true;
  return Vertex(this, newID);
}

void DiGraph::removeVertex(const Vertex& v)
{
  // Remove all incoming edges to this vertex
  list<unsigned> inEdges;
  inEdges.swap (vertices[v.vID].inEdges);
  for (list<unsigned>::iterator e = inEdges.begin(); e != inEdges.end(); e++)
    {
      removeEdge (Edge(this, *e, edges[*e].source, edges[*e].dest));
    }

  // Remove all outgoing edges from this vertex
  list<unsigned> outEdges;
  outEdges.swap (vertices[v.vID].outEdges);
  for (list<unsigned>::iterator e = outEdges.begin(); e != outEdges.end(); e++)
    {
      removeEdge (Edge(this, *e, edges[*e].source, edges[*e].dest));
    }
  
  // indicate that this vertex ID is no longer in use
  vertices[v.vID].occupied = false;
  recycledVertexIDs.push_back (v.vID);
  --numberOfVertices;
}


Edge DiGraph::addEdge(const Vertex& source,
		      const Vertex& dest)
{
  unsigned newID;
  if (recycledEdgeIDs.empty())
    {
      newID = maxEdgeID + 1;
      ++maxEdgeID;
      while (edges.size() <= maxEdgeID)
	edges.push_back(EdgeBase());
    }
  else
    {
      newID = recycledEdgeIDs.back();
      recycledEdgeIDs.pop_back();
    }
  edges[newID].occupied = true;
  edges[newID].source = source.vID;
  edges[newID].dest = dest.vID;

  vertices[source.vID].outEdges.push_back (newID);
  vertices[dest.vID].inEdges.push_back (newID);
  
  ++numberOfEdges;
  return Edge(this, newID, source.vID, dest.vID);
}


void DiGraph::removeEdge (const Edge& e)
{
  if (edges[e.eID].occupied)
    {
      vertices[e.sourceNode].outEdges.remove (e.eID);
      vertices[e.destNode].inEdges.remove (e.eID);
      edges[e.eID].occupied = false;
      recycledEdgeIDs.push_back (e.eID);
      --numberOfEdges;
    }
}


unsigned DiGraph::indegree (Vertex v) const
{
  return vertices[v.vID].inEdges.size();
}


unsigned DiGraph::outdegree (Vertex v) const
{
  return vertices[v.vID].outEdges.size();
}




bool DiGraph::isAdjacent(const Vertex& v, const Vertex& w) const
{
  return getEdge(v,w) != Edge();
}



Edge DiGraph::getEdge(const Vertex& v, const Vertex& w) const
{
  const list<unsigned>& v_edges = vertices[v.vID].outEdges;
  const list<unsigned>& w_edges = vertices[w.vID].inEdges;
  if (v_edges.size() < w_edges.size())
    {
      for (list<unsigned>::const_iterator e = v_edges.begin();
	   e != v_edges.end(); e++)
	if (edges[*e].dest == w.vID)
	  {
	    unsigned eid = *e;
	    return Edge(this, eid, edges[eid].source, edges[eid].dest);
	  }
    }
  else
    {
      for (list<unsigned>::const_iterator e = w_edges.begin();
	   e != w_edges.end(); e++)
	if (edges[*e].source == v.vID)
	  {
	    unsigned eid = *e;
	    return Edge(this, eid, edges[eid].source, edges[eid].dest);
	  }
    }
  return Edge();
}




void DiGraph::clear()
{
  vertices.clear();
  edges.clear();
  recycledVertexIDs.clear();
  recycledEdgeIDs.clear();
  numberOfVertices = 0;
  numberOfEdges = 0;
  maxVertexID = 0;
  maxEdgeID = 0;
}




AllVertices DiGraph::vbegin() const
{
  return AllVertices (this, 0);
}


AllVertices DiGraph::vend() const
{
  return AllVertices(this, vertices.size());
}


AllEdges DiGraph::ebegin() const
{
  return AllEdges (this, 0);
}


AllEdges DiGraph::eend() const
{
  return AllEdges(this, edges.size());
}



AllOutgoingEdges DiGraph::outbegin(Vertex source) const
{
  const list<unsigned>& theOutgoingEdges = vertices[source.vID].outEdges;
  return AllOutgoingEdges(this, theOutgoingEdges.begin());
}


AllOutgoingEdges DiGraph::outend(Vertex source)   const
{
  const list<unsigned>& theOutgoingEdges = vertices[source.vID].outEdges;
  return AllOutgoingEdges(this, theOutgoingEdges.end());
}


AllIncomingEdges DiGraph::inbegin(Vertex dest) const
{
  return AllIncomingEdges(this, vertices[dest.vID].outEdges.begin());
}


AllIncomingEdges DiGraph::inend(Vertex dest)   const
{
  return AllIncomingEdges(this, vertices[dest.vID].outEdges.end());
}



