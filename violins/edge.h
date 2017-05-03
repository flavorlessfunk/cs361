#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

class DiGraph;

class Edge
{
private:
  const DiGraph* graph;
  unsigned eID;
  unsigned sourceNode;
  unsigned destNode;
  
  Edge (const DiGraph* g, unsigned theID, unsigned source, unsigned dest)
    : graph(g), eID(theID), sourceNode(source), destNode(dest)
    {}

  friend class DiGraph;
  friend class Graph;
  friend class AllEdges;
  friend class AllIncidentEdges;
  friend class AllIncomingEdges;
  friend class AllOutgoingEdges;

public:
  Edge(): graph(nullptr), eID(0), sourceNode(0), destNode(0) {}


  const Vertex source() const        {return Vertex(graph, sourceNode);}
  const Vertex dest() const          {return Vertex(graph, destNode);}

  unsigned id() const {return eID;}


  bool operator< (const Edge& e) const
    {return eID < e.eID;}

  bool operator== (const Edge& e) const
    {return (graph == e.graph) && (eID == e.eID);}

  bool operator!= (const Edge& e) const
    {return (graph != e.graph) || (eID != e.eID);}

};


struct EdgeHash
{
  unsigned operator() (Edge e) const {return e.id();}
};



#endif

