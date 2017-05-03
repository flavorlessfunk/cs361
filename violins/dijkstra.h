#ifndef DIJKSTRA_H
#define DIJKSTRA_H


#include <map>
#include "digraph.h"


double findWeightedShortestPath (
   DiGraph& g,
   std::list<Edge>& path,
   Vertex start,
   Vertex finish,
   std::map<Edge, double>&);


#endif
