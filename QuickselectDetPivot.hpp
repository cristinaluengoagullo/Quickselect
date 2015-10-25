#ifndef QUICKSELECT_DETPIVOT 
#define QUICKSELECT_DETPIVOT

#include <iostream>
#include <vector>

#include "Quickselect.hpp"

class QuickselectDetPivot : public Quickselect
{

public:
  
  QuickselectDetPivot();
  
private:

  int pivotSelection(vector<int> input, int l, int r);

};

#endif
