#include "Quickselect.hpp"

Quickselect::Quickselect() {}

int Quickselect::quickselect(vector<int> input, int l, int r, int k)
{
  if(r-l+1 <= 10) {
    sort(input.begin()+l,input.begin()+r);
    return input[l+k-1];
  }
  if (l >= r) return input[l];
  int p = partition(input,l,r);
  int length = p - l + 1;
  if (length == k) return input[p];
  else if (k < length) return quickselect(input,l,p-1,k);
  else return quickselect(input,p+1,r,k-length);
}

int Quickselect::partition(vector<int> input, int l, int r)
{
  int pivot = pivotSelection(input,l,r);
  while (l < r) {
    while (input[l] < pivot)
      l++;
    while (input[r] > pivot)
      r--;
    if (input[l] == input[r])
      l++;
    else if (l < r) {
      int tmp = input[l];
      input[l] = input[r];
      input[r] = tmp;
    }
  }
  return r;
}

