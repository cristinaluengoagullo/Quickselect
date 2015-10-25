#include "QuickselectMOMPivot.hpp"

QuickselectMOMPivot::QuickselectMOMPivot() {}

int QuickselectMOMPivot::pivotSelection(vector<int> input, int l, int r)
{
  return medianOfMedians(input,l,r);
}

int QuickselectMOMPivot::medianOfMedians(const vector<int>& input, int l, int r) 
{
}
