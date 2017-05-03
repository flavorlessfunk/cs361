#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;


// We will represent our subway as a graph using
// an adjacency matrix to indicate which stations are
// adjacent to which other stations.

struct Subway {
  bool** connected;
  int nStations;

  Subway (int N);

private:
  // No copying allowed
  Subway (const Subway&) {}
  void operator= (const Subway&) {}
};


Subway::Subway(int N)
{
  nStations = N;
  connected = new bool*[N];
  for (int i = 0; i < N; ++i)
	{
	  connected[i] = new bool[N];
	  fill_n (connected[i], N, false);
	}
}


/**
 * Count the number of ways we can go from station 0 to station destination
 * traversing exactly nSteps edges.
 */
unsigned long long int tripCounter (const Subway& subway, int destination, int nSteps)
{
  // We can envision this as a 2D array, nTickets*nStation.
  // But, in fact, we compute the number of trips for k tickets
  // using only the previously number of trips for k-1 tickets,
  // so we only need two "columns" of the array.


  unsigned long long int* prevColumn 
	= new unsigned long long int[subway.nStations];
  unsigned long long int* column 
	= new unsigned long long int[subway.nStations];

  int k = 1;
  // initialize the k=1 case.
  for (int s = 0; s < subway.nStations; ++s)
	prevColumn[s] = (subway.connected[0][s])? 1 : 0;

  // Now run forward by the desired number of steps
  while (k < nSteps)
	{
	  ++k;

	  for (int s = 0; s < subway.nStations; ++s)
		{
		  // Sum up the # of trips using k-1 tickets to
		  // each station that connects to s.
		  column[s] = 0;
		  for (int s2 = 0; s2 < subway.nStations; ++s2)
			{
			  if (subway.connected[s][s2])
				{
				  column[s] += prevColumn[s2];
				  assert (column[s] >= prevColumn[s2]); // watch for overflow
				}
			}
		}

	  swap (prevColumn, column);
	}

  auto answer = prevColumn[destination];
  
  delete [] column;
  delete [] prevColumn;

  return answer;
}


// Read the subway description and
// print the number of possible trips.
void solve (istream& input)
{
  int N, k;
  input >> N >> k;
  Subway subway(N);
  int station1, station2;
  while (input >> station1)
	{
	  input >> station2;
	  subway.connected[station1][station2] = true;
	  subway.connected[station2][station1] = true;
	}
  cout << tripCounter(subway, 0, k) << endl;
}




int main (int argc, char** argv)
{
  // This is a trick I often use to aid in debugging.
  // Even though the program is supposed to normally 
  // use standard in (cin) for its input, I add an option
  // to read from a file if a filename is given as a
  // command-line argument.
  // The point is that all autoatic debuggers allow you
  // to supply command line arguments when launching
  // your program, but almost none allow you to
  // redirect standard input.
  //
  if (argc > 1) 
	{
	  ifstream in (argv[1]);
	  solve (in);
	}
  else
	{
	  solve (cin);
	}
  return 0;
}
