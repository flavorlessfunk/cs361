#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H


template <class Etype>
int sequentialSearch (const Etype* a, unsigned n, const Etype& x)
//
//  Search the array a[] for x, given that a contains n elements.
//  Return the position where x is found, or -1 if not found.
//  Assumes a[] is sorted, i.e., for all i in 0..n-2, a[i] <= a[i+1]
//
{
  int i = 0;
  while ((i < n) && (a[i] < x))
    ++i;
  if ((i >= n) || (x < a[i]))
    return -1;
  else
    return i;
}


template <class Etype>
int sequentialInsert (Etype* a, unsigned n, const Etype& x)
//
//  Insert x into the array a[], given that a contains n elements.
//  Assumes a[] is sorted, i.e., for all i in 0..n-2, a[i] <= a[i+1]
//  x is inserted into a position that leaves a still sorted.
//  Return the position where x was inserted.
//
{
  int i;
  for (i = n; (i > 0) && (x < a[i]); --i)
    a[i] = a[i-1];
  a[i] = x;
  return i;
}


#endif
