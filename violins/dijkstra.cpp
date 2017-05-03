#include "dijkstra.h"
#include <limits>
#include <queue>
#include <iostream>

// Change the // below to # to enable debugging output
//define DEBUGGING

using namespace std;


struct VertexAndDistance {
  Vertex v;
  Edge from;
  double dist;

  VertexAndDistance (Vertex vert, Edge frm, double d)
    : v(vert), from(frm), dist(d) {}
  VertexAndDistance () {}

  bool operator< (const VertexAndDistance& right) const
  {
    return dist > right.dist;
  }
};


double findWeightedShortestPath (
   DiGraph& g,
   list<Edge>& path,
   Vertex start,
   Vertex finish,
   map<Edge, double>& weight)
{      // Dijkstra's Algorithm

  const double MaxDouble = numeric_limits<double>::max();

  map<Vertex, Edge> cameFrom;
  map<Vertex, double> dist;   

  for (AllVertices vi = g.vbegin(); vi != g.vend(); ++vi)
    {
      dist[*vi] = MaxDouble;
    }
  priority_queue<VertexAndDistance> pq;
  pq.push (VertexAndDistance(start, Edge(), 0.0));
  
  // Compute distance from start to finish
  while (!pq.empty())
    {
      Vertex v = pq.top().v;
      Edge from = pq.top().from;
      double d = pq.top().dist;
#ifdef DEBUGGING
      cerr << "From pq: " << from.id() << "=>" << v.id() << ": " << d << endl;
#endif
      pq.pop();

      if (d < dist[v])
	{
	  dist[v] = d;
	  cameFrom[v] = from;
	  if (v == finish)
	    break;

	  for (AllOutgoingEdges e = g.outbegin(v); e != g.outend(v); ++e)
	    {
	      Edge edge = *e;
	      Vertex w = edge.dest();
	      double edgeWeight = weight[edge];
	      if (dist[w] > d+edgeWeight)
		{
#ifdef DEBUGGING
		  cerr << "Pushing " << v.id() << "=>" << w.id()
		       << ": " << d+edgeWeight << endl;
#endif
		  pq.push (VertexAndDistance(w, edge, d + edgeWeight));
		}
#ifdef DEBUGGING
	      else 
		cerr << "Ignoring " << v.id() << "=>" << w.id()
		     << ": " << d+edgeWeight << endl;
#endif
	    }        
	}
    }
  // Extract path
  Vertex v = finish;
  if (dist[v] != MaxDouble)
    {
     while (!(v == start))
       {
	 Edge e = cameFrom[v];
         path.push_front(e);  
         v = e.source();
       }
    }
  return dist[finish];
}
