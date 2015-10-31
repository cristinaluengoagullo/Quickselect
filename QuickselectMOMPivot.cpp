#include "QuickselectMOMPivot.hpp"

QuickselectMOMPivot::QuickselectMOMPivot() {}

int QuickselectMOMPivot::pivotSelection(vector<int> input, int l, int r)
{
  return medianOfMedians(input,l,r);
}

int QuickselectMOMPivot::medianOfMedians(vector<int> input, int l, int r) 
{
  int n = r-l+1;
  int nGroups = n/5;
  for(int i = 0; i < nGroups; i++) {
    int shift = i*5;
    int subRight = shift+4;
    if(subRight > r) subRight = r;
    int median5 = median(input,l+shift,l+subRight);
    input[l+n] = input[floor(float(l+shift)/5)];
    input[floor(float(l+shift)/5)] = median5;
  }
  return quickselect(input,l,l+nGroups-1,nGroups/2);
}

int QuickselectMOMPivot::median(vector<int> input, int l, int r) {
  sort(input.begin()+l,input.begin()+r);
  int n = float(r-l+1) / 2;
  return input[l+n];
}
