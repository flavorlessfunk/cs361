#include <string>
#include <iostream>
#include <sstream>
#include "hash_set.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include "unittest.h"

using namespace std;

unsigned sz;

struct StringHash
{
  int operator() (const string& str) const
    {
      int h = 0;
      for (unsigned i = 0; i < str.size(); ++i)
    	  h = 7*h + str[i];
      return h;
    }

};


struct IntHash
{
  int operator() (const int k) const
    {
      return k % 20;  // a deliberately poor choice to be sure it works with lots of collisions
    }

};


template <class Container>
void testDefaultConstructor (const Container& set0)
{
  Container v;
  assertEqual (v.size(), 0U);
  assertTrue (v.empty());
  assertEqual (v.begin(), v.end());
}

template <class Container, class T>
void testCopyConstructor (const Container& set0, unsigned sz, T data)
{
  Container v(set0);
  assertEqual (v.size(), set0.size());
  assertEqual (v.size(), sz);
  assertEqual (v, set0);
  assertEqual (set0, v);

  v.insert (data);
  assertEqual (set0.size(), sz);
  assertEqual (0U, set0.count(data));
  assertNotEqual (set0, v);
}

template <class Container, class T>
void testAssignment (const Container& set0, unsigned sz, T data)
{
  Container v;
  Container w (v = set0);
  assertEqual (v.size(), set0.size());
  assertEqual (v.size(), sz);
  assertEqual (v, set0);
  assertEqual (set0, v);
  assertEqual (w, v);

  v.insert (data);
  assertEqual (set0.size(), sz);
  assertEqual (0U, set0.count(data));
  assertNotEqual (set0, v);
}

template <class Container, class T>
class CountIsOne {
	const Container& set;
	T exception;
public:
	CountIsOne (const Container& container, T except)
	: set(container), exception(except) {}

	void operator() (const T& x) {
		if (! (x == exception))
			assertEqual(1U, set.count(x));
	}
};

template <class Container, class T>
void testInsertNew (const Container& set0, unsigned sz, T data)
{
  Container v = set0;
  v.insert (data);
  assertFalse (v.empty());
  assertEqual (v.size(), sz+1);
  assertEqual (v.count(data), 1U);
  assertEqual (set0.count(data), 0U);
  assertEqual (set0.end(), set0.find(data));
  assertNotEqual (v.end(), v.find(data));
  assertEqual (data, *(v.find(data)));

  assertEqual (find(set0.begin(), set0.end(), data), set0.end());
  assertNotEqual (find(v.begin(), v.end(), data), v.end());
  for_each (set0.begin(), set0.end(), CountIsOne<Container,T>(v, data));
}

template <class Container, class T>
void testInsertDuplicate (const Container& set0, unsigned sz, T data)
{
  Container v = set0;
  v.insert (data);
  assertFalse (v.empty());
  assertEqual (v.size(), sz);
  assertEqual (v.count(data), 1U);
  assertEqual (set0.count(data), 1U);
  assertNotEqual (set0.end(), set0.find(data));
  assertNotEqual (v.end(), v.find(data));
  assertEqual (data, *(v.find(data)));

  assertNotEqual (find(set0.begin(), set0.end(), data), set0.end());
  assertNotEqual (find(v.begin(), v.end(), data), v.end());
  for_each (set0.begin(), set0.end(), CountIsOne<Container,T>(v, data));
}


template <class Container, class T>
void testEraseNew (const Container& set0, unsigned sz, T data)
{
  Container v = set0;
  v.erase (data);
  assertEqual (v.empty(), set0.empty());
  assertEqual (v.size(), sz);
  assertEqual (v.count(data), 0U);
  assertEqual (set0.count(data), 0U);
  assertEqual (set0.end(), set0.find(data));
  assertEqual (v.end(), v.find(data));

  assertEqual (find(set0.begin(), set0.end(), data), set0.end());
  assertEqual (find(v.begin(), v.end(), data), v.end());
  for_each (set0.begin(), set0.end(), CountIsOne<Container,T>(v, data));
}


template <class Container, class T>
void testEraseDuplicate (const Container& set0, unsigned sz, T data)
{
  Container v = set0;
  v.erase (data);
  assertEqual (v.empty(), sz == 1U);
  assertEqual (v.size(), sz-1U);
  assertEqual (v.count(data), 0U);
  assertEqual (set0.count(data), 1U);
  assertNotEqual (set0.end(), set0.find(data));
  assertEqual (v.end(), v.find(data));

  assertNotEqual (find(set0.begin(), set0.end(), data), set0.end());
  assertEqual (find(v.begin(), v.end(), data), v.end());
  for_each (set0.begin(), set0.end(), CountIsOne<Container,T>(v, data));
}

template <class Container, typename T>
void testClear (const Container& set0, unsigned sz, T data)
{
  Container v (set0);
  assertEqual (v.size(), set0.size());
  v.clear();
  assertEqual (v.size(), 0U);
  assertEqual (set0.size(), sz);
  assertTrue (v.empty());
  assertEqual (v.begin(), v.end());
  
  if (sz > 0U)
    assertNotEqual (set0.end(), set0.find(data));
  assertEqual (v.end(), v.find(data));

  if (sz > 0)
    assertNotEqual (find(set0.begin(), set0.end(), data), set0.end());

}


template <class Container, class T>
void testCollisions (const Container& set0, unsigned sz, T data)
{
  Container v;
  vector<T> values (set0.begin(), set0.end());
  unsigned oneThird = sz / 3;
  unsigned twoThirds = 2 * sz / 3;

  for (int i = 0; i < twoThirds; ++i) {
	  v.insert(values[i]);
  }
  for (int i = oneThird; i < twoThirds; ++i) {
	  v.erase(values[i]);
  }
  for (int i = sz-1; i >= 0; i--) {
	  v.insert(values[i]);
  }
  assertEqual (set0.empty(), v.empty());
  assertEqual (sz, v.size());
  for_each (set0.begin(), set0.end(), CountIsOne<Container,T>(v, data));
  assertEqual (set0, v);
}





template <class Container, class T>
void testSet (const Container& set0, unsigned sz, T includedData, T newData, 
	      string key)
{
  if (key.find('a') != string::npos)
    {
      assertEqual (sz, set0.size());
      set0.printStats(cout);
    }
  if (key.find('b') != string::npos)
    testDefaultConstructor(set0);
  if (key.find('c') != string::npos)
    testCopyConstructor(set0, sz, newData);
  if (key.find('d') != string::npos)
    testAssignment (set0, sz, newData);
  if (key.find('e') != string::npos)
    testInsertNew (set0, sz, newData);
  if (key.find('f') != string::npos)
    if (sz > 0)
      testInsertDuplicate (set0, sz, includedData);
  if (key.find('g') != string::npos)
    testEraseNew (set0, sz, newData);
  if (key.find('h') != string::npos)
    if (sz > 0)
      testEraseDuplicate (set0, sz, includedData);
  if (key.find('i') != string::npos)
    testClear (set0, sz, includedData);
  if (key.find('j') != string::npos)
    testCollisions (set0, sz, includedData);
}



class NextInt 
{
  int k;
public:
  NextInt(): k(-1) {}

  int operator() () {++k; return k;}
};


string intToStr (int i)
{
  string s;
  while (i > 0)
    {
      s += (char)('a' + i % 26);
      i = i / 26;
    }
  return s;
}








void doTest (int testSize,
	     const vector<int>& intKeys,
	     const vector<string>& strKeys, 
	     int containedDataIndex,
	     int excludedDataIndex,
	     string key)
{
  sz = testSize;

  hash_set<int, IntHash> s1;
  for (int i = 0; i < testSize; ++i)
    s1.insert (intKeys[i]);
    testSet (s1, testSize,
	   intKeys[containedDataIndex], 
	   intKeys[excludedDataIndex],
	   key);
  
  hash_set<string> s2;
  for (int i = 0; i < testSize; ++i)
    s2.insert (strKeys[i]);
    testSet (s2, testSize,
	   strKeys[containedDataIndex],
	   strKeys[excludedDataIndex],
	   key);
}




//
// This program tests the implementation of hash_set
//
// Optional parameters:
//   key: alphabetic code indicating which tests to run. Defaults to
//          a-z, running all tests.
//   firstTest: smallest set size that will be tested (defaults to 0)
//   lastTest: largest set size that will be tested (defaults to 10,000)
//
int main (int argc, char **argv)
{
  int maxTestSize = 10000;
  string key = "abcdefghijklmnopqrstuvwxyz";
  int firstTest = 0;
  int lastTest = maxTestSize;
  if (argc > 1) 
    {
      key = argv[1];
      if (argc > 2)
	{
	  istringstream in (argv[2]);
	  in >> firstTest;
	}
      if (argc > 3)
	{
	  istringstream in (argv[3]);
	  in >> lastTest;
	}
    }    

  vector<int> intKeys;
  generate_n (back_inserter(intKeys), lastTest+1, NextInt());
  random_shuffle(intKeys.begin(), intKeys.end());

  vector<string> strKeys;
  transform (intKeys.begin(), intKeys.end(), back_inserter(strKeys), intToStr);
  
  cout << "Running tests " << key << " on set sizes " 
       << firstTest << "..." << lastTest << endl;

  for (int testNum = firstTest; testNum <= lastTest; testNum = 2*testNum+1)
    {
      
      doTest (testNum, intKeys, strKeys, testNum/2, lastTest, key);
    }

  UnitTest::report (cout);
  return 0;
}
