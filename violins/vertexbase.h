#ifndef VERTEXBASE_H
#define VERTEXBASE_H

#include <list>

struct VertexBase
{
  bool occupied;
  std::list<unsigned> inEdges;
  std::list<unsigned> outEdges;

  VertexBase(): occupied(false) {}
};

#endif

