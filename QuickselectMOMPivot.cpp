#include "QuickselectMOMPivot.hpp"

QuickselectMOMPivot::QuickselectMOMPivot() {}

int QuickselectMOMPivot::pivotSelection(vector<int> input, int l, int r)
{
  return medianOfMedians(input,l,r);
}

int QuickselectMOMPivot::medianOfMedians(vector<int> input, int l, int r) 
{
  if(r - l <= 5) {
    sort(input.begin()+l,input.begin()+r);
    int n = (r - l) / 2; 
    return input[n];
  }
  // 1. Divide the vector in groups of 5
  // 2. Compute the median of each group
  // 3. Return the median of all medians
  vector<int> medians;
  for(int i = l; i < r; i+=5) {
    int m = medianOfMedians(input,i,i+5);
    medians.push_back(m);
  }
  return medianOfMedians(medians,0,medians.size()-1);
}

int QuickselectMOMPivot::median(vector<int> input, int l, int r) {
  sort(input.begin()+l,input.end()+r);
  int n = input.size() / 2;
  return input[n];
}
