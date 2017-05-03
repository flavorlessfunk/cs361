#ifndef VERTEX_H
#define VERTEX_H

class DiGraph;

class Vertex
{
private:
  const DiGraph* graph;
  unsigned vID;
  


  Vertex (const DiGraph* g, unsigned theID): graph(g), vID(theID) {}

  friend class DiGraph;
  friend class AllVertices;
  friend class AllEdges;
  friend class AllOutgoingEdges;
  friend class AllIncidentEdges;
  friend class AllIncomingEdges;
  friend class Edge;

public:
  // To get a non-trivial vertex, you must ask a DiGraph to generate one.
  Vertex(): graph(0), vID(0) {}

  unsigned id() const {return vID;}

  bool operator< (const Vertex& v) const
     {return vID < v.vID;}

  bool operator== (const Vertex& v) const
     {return (graph == v.graph) && (vID == v.vID);}

  bool operator!= (const Vertex& v) const
     {return (graph != v.graph) || (vID != v.vID);}

};



struct VertexHash
{
  unsigned operator() (Vertex v) const {return v.id();}
};


#endif

