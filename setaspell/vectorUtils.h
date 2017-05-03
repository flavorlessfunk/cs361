#ifndef VECTORUTILS_H
#define VECTORUTILS_H

#include <vector>




// Add value into vectr[index], shifting all elements already in positions
//    index..size-1 up one, to make room.

template <typename T>
void addElement (std::vector<T>& vectr, int& size, int index, T value)
{
  // Make room for the insertion
  int toBeMoved = vectr.size() - 1;
  vectr.push_back(value);

  // Shift elements up to make room
  while (toBeMoved >= index) {
    vectr[toBeMoved+1] = vectr[toBeMoved];
    --toBeMoved;
  }
  // Insert the new value
  vectr[index] = value;
}


// Assume the elements of the vector are already in order
// Find the position where value could be added to keep
//    everything in order, and insert it there.
// Return the position where it was inserted

template <typename T>
int addInOrder (std::vector<T>& vectr, T value)
{
  // Make room for the insertion
  int toBeMoved = vectr.size() - 1;
  vectr.push_back(value);

  // Shift elements up to make room
  while (toBeMoved >= 0 && value < vectr[toBeMoved]) {
    vectr[toBeMoved+1] = vectr[toBeMoved];
    --toBeMoved;
  }
  // Insert the new value
  vectr[toBeMoved+1] = value;
  return toBeMoved+1;
}


// Search a vector for a given value, returning the index where 
//    found or -1 if not found.
template <typename T>
int seqSearch(const std::vector<T>& list, T searchItem)
{
    int loc;

    for (loc = 0; loc < list.size(); loc++)
        if (list[loc] == searchItem)
            return loc;

    return -1;
}


// Search an ordered vector for a given value, returning the index where 
//    found or -1 if not found.
template <typename T>
int seqOrderedSearch(const std::vector<T> list, T searchItem)
{
    int loc = 0;

    while (loc < list.size() && list[loc] < searchItem)
      {
       ++loc;
      }
    if (loc < list.size() && list[loc] == searchItem)
       return loc;
    else
       return -1;
}


// Removes an element from the indicated position in the vector, moving
// all elements in higher positions down one to fill in the gap.
template <typename T>
void removeElement (T* vectr, int& size, int index)
{
  int toBeMoved = index + 1;
  while (toBeMoved < size) {
    vectr[toBeMoved] = vectr[toBeMoved+1];
    ++toBeMoved;
  }
  --size;
}



// Search an ordered vector for a given value, returning the index where 
//    found or -1 if not found.
template <typename T>
int binarySearch(const std::vector<T> list, T searchItem)
{
    int first = 0;
    int last = list.size() - 1;
    int mid;

    bool found = false;

    while (first <= last && !found)
    {
        mid = (first + last) / 2;

        if (list[mid] == searchItem)
            found = true;
        else 
            if (searchItem < list[mid])
                last = mid - 1;
            else
                first = mid + 1;
    }

    if (found) 
        return mid;
    else
        return -1;
}





#endif
