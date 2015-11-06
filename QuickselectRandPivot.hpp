#ifndef QUICKSELECT_RANDPIVOT 
#define QUICKSELECT_RANDPIVOT

#include <iostream>
#include <vector>
#include <random>

#include "Quickselect.hpp"

class QuickselectRandPivot : public Quickselect
{

public:
  
  QuickselectRandPivot();
  
private:

  int pivotSelection(vector<int>& input, int l, int r);

};

#endif
