#include "graph.h"
#include "dijkstra.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>


using namespace std;




typedef std::map<Vertex, string> MapVerticesToString;
typedef std::map<string, Vertex> MapStringToVertices;
typedef std::map<Edge, string>   MapEdgesToString;
typedef std::map<Edge, double>   MapEdgesToDouble;



Vertex getCity (string cityName, Graph& g,
		MapStringToVertices& byName, MapVerticesToString& byVertex)
{
  MapStringToVertices::iterator pos = byName.find(cityName);
  if (pos != byName.end())
    return pos->second;
  else
    {
      // Never seen this city before. Create a vertex for it.
      Vertex v = g.addVertex();
      byName[cityName] = v;
      byVertex[v] = cityName;
      return v;
    }
}


int main(int argc, char** argv)
{
  if (argc != 4)
    {
      cerr << "Usage: " << argv[0]
	   << " fileName startingCity endingCity" << endl;
      return 1;
    }

  Graph g;


  // For any city name, get the vertex representing that ciy
  // in the graph
  MapStringToVertices verticesByName;


  // For any vertex in the graph, get the name of the city
  // represented by that vertex
  MapVerticesToString namesOfVertices;

  // For any edge, get the name of the road represented by that edge
  MapEdgesToString roadNames;

  // For any edge, get the distance of the road represented by that edge
  MapEdgesToDouble distances;

  string city1, city2, road;
  double distance;

  // Read in the roads data
  ifstream roadsIn (argv[1]);
  while (roadsIn.good())
    {
      string line;
      getline (roadsIn, line);
      if (roadsIn.good() && line.length() > 0)
	{
	  istringstream in (line);
	  in >> road >> city1;
	  while (in >> distance)
	    {
	      in >> city2;
	      // road runs from city1 to city2 in distance miles
	      //** Insert your code here to build the graph and associated maps
	      Vertex v1 = getCity(city1, g, verticesByName, namesOfVertices);
	      Vertex v2 = getCity(city2, g, verticesByName, namesOfVertices);
	      Edge e = g.addEdge(v1, v2);
	      roadNames[e] = road;
	      distances[e] = distance;
	      e = g.getEdge(v2, v1);
	      roadNames[e] = road;
	      distances[e] = distance;

	      city1 = city2;
	    }
	}
    }

  string startingCityName = argv[2];
  string destinationCityName = argv[3];


  if (startingCityName == destinationCityName)
    cout << "You are already at " << startingCityName << endl;
  else
    {
      double tripLength;
      list<Edge> path;
      //** Insert your code here to find the shortest path between 
      //     the two cities

      Vertex startingCity = getCity(startingCityName, g,
				    verticesByName, namesOfVertices);

      Vertex destinationCity = getCity(destinationCityName, g,
				       verticesByName, namesOfVertices);

      tripLength = findWeightedShortestPath (g, path,
					     startingCity,
					     destinationCity, distances);

      if (path.size() > 0)
	{
	  //** Insert your code here to print the selected path

	  string lastRoadTaken;
	  for (Edge e: path)
	    {
	      string road = roadNames[e];
	      if (lastRoadTaken != road)
		{
		  if (lastRoadTaken == "")
		    cout << "From " << namesOfVertices[e.source()];
		  else
		    {
		      cout << "to " << namesOfVertices[e.source()] << endl;
		      cout << "From " << namesOfVertices[e.source()];
		    }
		  cout << " take " << road << " ";
		  lastRoadTaken = road;
		}
	    }
	  cout << "to " << destinationCityName << endl;
	  
	  cout << "Trip length: " << tripLength << endl;
	}
      else
	cout << "You can't get from " << startingCityName
	     << " to " << destinationCityName << endl;
    }
  return 0;
}