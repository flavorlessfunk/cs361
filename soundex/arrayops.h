#ifndef ARRAYOPS_H
#define ARRAYOPS_H

template <class T>
int sequentialInsert 
  (T a[], unsigned& n, const T& x)
// insert x into sorted position within a,
//   with a already containing n items.
//   Return the position where inserted.
{
  int i = n;
  while ((i > 0) && (x < a[i-1]))
      {
       a[i] = a[i-1];
       i = i - 1;
      }
  a[i] = x;
  ++n;
  return i;
}   


template <class T>
int sequentialSearch 
  (const T a[], unsigned n, const T& x)
// Look for x within a sorted array a, containing n items.
// Return the position where found, or -1 if not found.
{
  int i;
  for (i = 0; ((i < n) && (a[i] < x)); i++) ;
  if ((i >= n) || (a[i] != x)) 
    i = -1;
  return i;
}


template <class T>
int unorderedSearch 
  (const T a[], unsigned n, const T& x)
// Look for x within an unsorted array a, containing n items.
// Return the position where found, or -1 if not found.
{
  int i;
  for (i = 0; ((i < n) && (a[i] != x)); i++) ;
  if (i >= n) 
    i = -1;
  return i;
}


template <class T>
unsigned int binarySearch (T v[], unsigned int n, const T& value)
    // search for value in ordered array of data
    // return index of value, or index of
    // next smaller value if not in collection
{
  unsigned int low = 0;
  unsigned int high = n;

  // repeatedly reduce the area of search
  // until it is just one value
  while (low < high) {
     unsigned mid = (low + high) / 2;
     if (v[mid] < value)
        low = mid + 1;  
     else
        high = mid;     
     }

  // return the lower value
  return low;
}

#endif
