#ifndef QUICKSELECT_MOMPIVOT 
#define QUICKSELECT_MOMPIVOT

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "Quickselect.hpp"

class QuickselectMOMPivot : public Quickselect
{

public:
  
  QuickselectMOMPivot();
  
private:

  int pivotSelection(vector<int> input, int l, int r);

  int medianOfMedians(vector<int> input, int l, int r);

  int median(vector<int> input, int l, int r);

};

#endif
